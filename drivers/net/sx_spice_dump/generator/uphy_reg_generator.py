#!/usr/bin/env python3

import json
import optparse
import sys
import os
import subprocess

SDK_BASE_DIR = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + '/../../../../../')

HEADER_CHECKER_CMD = "sudo docker run  -t  --rm --user $(id -u):$(id -g) -v " + SDK_BASE_DIR + "/:/git-repo harbor.mellanox.com/toolbox/header_check:latest " \
    "--config sxd_kernel/drivers/net/sx_spice_dump/generator/spice.yaml --path sxd_kernel/drivers/net/sx_spice_dump/ --repair"

CLN_REG_LIST = list()
DLN_REG_LIST = list()

DLN_RX_ADDR_LIST = list()
DLN_TX_ADDR_LIST = list()
CLN_ADDR_LIST = list()

REG_DB = [CLN_REG_LIST, DLN_REG_LIST]

# List of files to be generated
SX_SPICE_UPHY_REG_AUTO_H = "sx_spice_uphy_reg_auto.h"
SX_SPICE_UPHY_REG_AUTO_C = "sx_spice_uphy_reg_auto.c"

AUTO_GENERATION_DICT = {
    SX_SPICE_UPHY_REG_AUTO_H: "uphy_reg_auto_header_gen()",
    SX_SPICE_UPHY_REG_AUTO_C: "uphy_reg_auto_source_gen()"}

DLN_MAX_ADDRESS = 0
CLN_MAX_ADDRESS = 0
INDENT = " " * 4

UPHY_REG_H_AUTO_PATTERN = """
#ifndef SX_SPICE_UPHY_REG_AUTO_H_
#define SX_SPICE_UPHY_REG_AUTO_H_

#include "sx_spice_uphy_reg_infra.h"

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 *  Macros
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/
%s
/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Function declarations
 ***********************************************/

%s
int sx_spice_uphy_reg_init(void);
void sx_spice_uphy_reg_deinit(void);

#endif /* SX_SPICE_UPHY_REG_AUTO_H_ */
"""

UPHY_REG_C_AUTO_PATTERN = """

#include "sx_spice_uphy_reg_auto.h"

/************************************************
 *  Global variables
 ***********************************************/

/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Local function declarations
 ***********************************************/

/************************************************
 *  Function implementations
 ***********************************************/
%s

"""


def ParseCmdLine():
    global CMD_OPTIONS
    usage = "usage: %prog [options]"
    desc = "DESCRIPTION:"
    cmdparser = optparse.OptionParser(usage=usage, description=desc)
    try:
        cmdparser.add_option("-c", "--cln_json_file", help="Path to CLN json input file",
                             dest="CLNJsonInputFile", default=None)
        cmdparser.add_option("-d", "--dln_json_file", help="Path to DLN json input file",
                             dest="DLNJsonInputFile", default=None)
        (CMD_OPTIONS, args) = cmdparser.parse_args()

    except Exception as exp:
        raise Exception("Failed to parse command line: %s" % exp)


def uphy_reg_db_cln_init(cln_path):
    """
    Initialize CLN list
    """
    with open(cln_path, 'r') as f:
        data = json.load(f)

    registers = data.get('registers')
    for reg in registers:
        addr = reg.get('addr')
        dumps = reg.get('dumps')

        for d in dumps:
            if d == 'pll_short':
                CLN_REG_LIST.append(reg)
                CLN_ADDR_LIST.append(reg.get('addr'))

        global CLN_MAX_ADDRESS
        CLN_MAX_ADDRESS = addr

    print("\nCLN_MAX_ADDRESS:  ")
    print(CLN_MAX_ADDRESS)

    print("\nCLN addresses list:\n")
    print(CLN_ADDR_LIST)


def uphy_reg_db_dln_init(dln_path):
    """
    Initialize DLN RX and TX lists
    """

    with open(dln_path, 'r') as f:
        data = json.load(f)

    add_to_dln = False

    registers = data.get('registers')
    for reg in registers:
        addr = reg.get('addr')
        dumps = reg.get('dumps')
        for d in dumps:
            if d == 'rx_short':
                DLN_RX_ADDR_LIST.append(addr)
                add_to_dln = True
            elif d == 'tx_short':
                DLN_TX_ADDR_LIST.append(addr)
                add_to_dln = True

        if (add_to_dln):
            DLN_REG_LIST.append(reg)

        global DLN_MAX_ADDRESS
        DLN_MAX_ADDRESS = addr

    print("\nDLN_MAX_ADDRESS:  ")
    print(DLN_MAX_ADDRESS)

    print("\nDLN RX addresses list:\n")
    print(DLN_RX_ADDR_LIST)
    print("\nDLN TX addresses list:\n")
    print(DLN_TX_ADDR_LIST)


def uphy_reg_db_init(cln_path, dln_path):
    """
    Initialize CLN and DLN lists
    """
    uphy_reg_db_cln_init(cln_path)

    uphy_reg_db_dln_init(dln_path)


def uphy_reg_src_func_impl_get_macro_gen(reg_list):
    """

    :param reg_list:
    :return:
    """
    pattern8 = """UPHY_ITEM8(%s, %s, 0x%s, %s, %s);\n"""
    pattern16 = """UPHY_ITEM16(%s, %s, 0x%s, %s, %s);\n"""

    code = ""

    for reg in reg_list:
        reg_name = reg.get("name").lower()
        fields = reg.get("fields")
        for field in fields:
            field_name = field.get("name")
            if field_name.find("reserved") == -1:
                width = field.get("width")
                if width > 8 or (field.get("range_start") >= 8 and field.get("range_end") < 8):
                    # uint16 pattern
                    offset = 0
                    shift = field.get("range_end")

                    code += pattern16 % (reg_name, field_name, offset, shift, width)
                else:
                    # uint8 pattern
                    if (field.get("range_start") >= 8):
                        offset = 1
                        shift = field.get("range_end") - 8
                    else:
                        offset = 0
                        shift = field.get("range_end")

                    code += pattern8 % (reg_name, field_name, offset, shift, width)

    return code


def uphy_reg_src_func_impl_deparse_gen(reg_list):
    """

    :param reg_list:
    :return:
    """
    pattern = """\nstatic int __%s_reg_deparse(uint16_t *reg_buff, struct uphy_reg_%s *reg_data)
{
%sconst uphy_common_reg_t *uphy_reg = (const uphy_common_reg_t*)reg_buff;

%s
%sreturn 0;
}\n"""
    field_pattern = """%sreg_data->%s = uphy_reg_%s_%s_get(uphy_reg->reg);\n"""
    casting_field_pattern = """%sreg_data->%s = (uint8_t)uphy_reg_%s_%s_get(uphy_reg->reg);\n"""

    code = ""
    fields_code = ""

    for reg in reg_list:
        reg_name = reg.get("name").lower()
        fields = reg.get("fields")
        for field in fields:
            if field.get("name").find("reserved") == -1:
                if field.get("range_start") >= 8 and field.get("range_end") < 8 and field.get("width") <= 8:
                    fields_code += casting_field_pattern % (INDENT, field.get("name"), reg_name, field.get("name"))
                else:
                    fields_code += field_pattern % (INDENT, field.get("name"), reg_name, field.get("name"))

        code += pattern % (reg_name, reg_name, INDENT, fields_code, INDENT)
        fields_code = ""

    return code


def uphy_reg_src_func_impl_print_gen(reg_list):
    """

    :param reg_list:
    :return:
    """
    pattern = """\nint %s_data_to_buffer_print(char **buffer, size_t buffer_length, int *buffer_size, uint16_t *reg)
{
%sstruct uphy_reg_%s reg_data;
%sint snp_res = 0;

%s__%s_reg_deparse(reg, &reg_data);

%s
%sreturn *buffer_size;
}\n"""
    field_pattern = """%ssnp_res = snprintf(*buffer, buffer_length - *buffer_size, "%s.%s: 0x%sx\\n", reg_data.%s);
%sVALIDATE_ROLLBACK(snp_res, buffer_length, *buffer_size);
%s*buffer += snp_res;
%s*buffer_size += snp_res;\n"""

    code = ""
    fields_code = ""
    mod_sign = "%"

    for reg in reg_list:
        reg_name = reg.get("name").lower()
        fields = reg.get("fields")
        for field in fields:
            if field.get("name").find("reserved") == -1:
                fields_code += field_pattern % (INDENT, reg_name, field.get("name"), mod_sign, field.get("name"),
                                                INDENT, INDENT, INDENT)

        code += pattern % (reg_name, INDENT, reg_name, INDENT, INDENT, reg_name, fields_code, INDENT)
        fields_code = ""

    return code


def uphy_reg_src_func_impl_infra_gen():
    """

    :param reg_list:
    :return:
    """
    get_reg_info_pattern = """\nconst struct sx_spice_uphy_reg_info* sx_spice_uphy_reg_info_get(uphy_reg_type_e reg_type, uint16_t reg_id)
{
%sif (reg_type == UPHY_REG_TYPE_DLN){
%sif (DLN_VALID_REG_ID(reg_id) && __uphy_dln_registers_info_g[reg_id].valid) {
%sreturn &__uphy_dln_registers_info_g[reg_id];
%s}
%s} else {
%sif (CLN_VALID_REG_ID(reg_id) && __uphy_cln_registers_info_g[reg_id].valid) {
%sreturn &__uphy_cln_registers_info_g[reg_id];
%s}
%s}

%sreturn NULL;
}\n"""
    init_reg_pattern = """\nint __uphy_reg_init(uphy_reg_type_e reg_type, uint16_t reg_id, sx_spice_uphy_reg_data_to_buffer_cb_t print_cb)
{
%sint err = 0;
%sstruct sx_spice_uphy_reg_info *entry;

%sif (reg_type == UPHY_REG_TYPE_DLN) {
%sif (!DLN_VALID_REG_ID(reg_id)) {
%sprintk(KERN_ERR "Fail to init: invalid reg-id: 0x%sx\\n", reg_id);
%serr = -EFAULT;
%sgoto out;
%s}
%sentry = &__uphy_dln_registers_info_g[reg_id];
%s} else { /* CLN */
%sif (!CLN_VALID_REG_ID(reg_id)) {
%sprintk(KERN_ERR "Fail to init: invalid reg-id: 0x%sx\\n", reg_id);
%serr = -EFAULT;
%sgoto out;
%s}
%sentry = &__uphy_cln_registers_info_g[reg_id];
%s}

%smemset(entry, 0, sizeof(*entry));

%sentry->valid = true;
%sentry->print_cb = print_cb;
out:
%sreturn err;
}\n"""

    code = ""
    mod_sign = "%"

    code += init_reg_pattern % (INDENT, INDENT, INDENT, INDENT * 2, INDENT * 3, mod_sign,
                                INDENT * 3, INDENT * 3, INDENT * 2, INDENT * 2, INDENT,
                                INDENT * 2, INDENT * 3, mod_sign,
                                INDENT * 3, INDENT * 3, INDENT * 2, INDENT * 2, INDENT,
                                INDENT, INDENT, INDENT, INDENT)
    code += get_reg_info_pattern % (INDENT, INDENT * 2, INDENT * 3, INDENT * 2,
                                    INDENT, INDENT * 2, INDENT * 3, INDENT * 2, INDENT, INDENT)

    return code


def uphy_reg_src_func_impl_reg_init_gen():
    """

    :return:
    """
    pattern = """\nint sx_spice_uphy_reg_init(void)
{
%sint err = 0;
%sstatic bool is_initialized = false;

%sif (is_initialized) {
%sgoto out;
%s}

%serr = sx_spice_uphy_infra_init();
%sif (err) {
%sprintk(KERN_ERR "failed to initialize uPhy registers infrastructure \\n");
%sgoto out;
%s}

%sis_initialized = true;

%s
%sgoto out;

reg_init_failed:
%ssx_spice_uphy_infra_deinit();

out:
%sreturn err;
}\n"""
    reg_pattern = """%serr = sx_spice_uphy_infra_reg_init(UPHY_REG_TYPE_%s, %s, %s_data_to_buffer_print);
%sif (err) {
%sgoto reg_init_failed;
%s}\n"""

    code = ""
    reg_code = ""

    for reg_list in REG_DB:

        if reg_list == CLN_REG_LIST:
            reg_type = "CLN"
        else:
            reg_type = "DLN"

        for reg in reg_list:
            reg_name = reg.get("name").lower()
            reg_code += reg_pattern % (INDENT, reg_type, reg.get("addr"), reg_name,
                                       INDENT, INDENT * 2, INDENT)

    code += pattern % (INDENT, INDENT, INDENT, INDENT * 2, INDENT,
                       INDENT, INDENT, INDENT * 2, INDENT * 2, INDENT,
                       INDENT, reg_code, INDENT, INDENT, INDENT)

    return code


def uphy_reg_src_func_impl_reg_deinit_gen():
    """

    :return:
    """
    pattern = """\nvoid sx_spice_uphy_reg_deinit(void)
{
%ssx_spice_uphy_infra_deinit();
}\n"""
    code = ""

    code = pattern % (INDENT)

    return code


def uphy_reg_src_func_impl_gen():
    """
    Generates UPHY reg C function implementation segment.
    :return: UPHY reg C function implementation segment code.
    """

    code = ""

    code += uphy_reg_src_func_impl_reg_init_gen()
    code += uphy_reg_src_func_impl_reg_deinit_gen()

    for reg_list in REG_DB:
        code += uphy_reg_src_func_impl_get_macro_gen(reg_list)
        code += uphy_reg_src_func_impl_deparse_gen(reg_list)
        code += uphy_reg_src_func_impl_print_gen(reg_list)

    return code


def uphy_reg_header_struct_list_gen(reg_list):
    """
    Generates UPHY reg H Uphy registers structure definition per list.
    :param reg_list: UPHY registers list (CLN | DLN_RX | DLN_TX)
    :return: UPHY reg H Uphy registers structure definition per list.
    """
    struct_pattern = """struct uphy_reg_%s {
%s};\n\n"""
    field_8_pattern = """%suint8_t    %s;\n"""
    field_16_pattern = """%suint16_t    %s;\n"""

    code = ""
    fields_code = ""

    for reg in reg_list:
        reg_name = reg.get("name").lower()
        fields = reg.get("fields")
        for field in fields:
            if field.get("name").find("reserved") == -1:
                if field.get("width") <= 8:
                    fields_code += field_8_pattern % (INDENT, field.get("name"))
                else:
                    fields_code += field_16_pattern % (INDENT, field.get("name"))

        code += struct_pattern % (reg_name, fields_code)
        fields_code = ""

    return code


def uphy_reg_header_struct_gen():
    """
    Generates UPHY reg H Uphy registers structure definition segment.
    :return: UPHY reg H Uphy registers structure definition segment.
    """

    code = ""

    for reg_list in REG_DB:
        code += uphy_reg_header_struct_list_gen(reg_list)

    return code


def uphy_reg_header_func_dec_list_gen(reg_list):
    """
    Generates UPHY reg H Uphy registers function declaration per registers list.
    :param reg_list:  UPHY registers list (CLN | DLN_RX | DLN_TX)
    :return: UPHY reg H Uphy registers function declaration per registers list.
    """
    get_field_8_func_pattern = """uint8_t uphy_reg_%s_%s_get(const char *buf);\n"""
    get_field_16_func_pattern = """uint16_t uphy_reg_%s_%s_get(const char *buf);\n"""
    print_reg_func_pattern = """int %s_data_to_buffer_print(char **buffer, size_t buffer_length,  int *buffer_size, uint16_t *reg);\n\n"""

    code = ""

    for reg in reg_list:
        reg_name = reg.get("name").lower()
        fields = reg.get("fields")
        for field in fields:
            if field.get("name").find("reserved") == -1:
                if field.get("width") > 8 or (field.get("range_start") >= 8 and field.get("range_end") < 8):
                    code += get_field_16_func_pattern % (reg_name, field.get("name"))
                else:
                    code += get_field_8_func_pattern % (reg_name, field.get("name"))

        code += print_reg_func_pattern % reg_name

    return code


def uphy_reg_header_func_dec_gen():
    """
    Generates UPHY reg H Uphy registers function declaration code segment.
    :return: Uphy registers function declaration code segment.
    """
    code = ""

    for reg_list in REG_DB:
        code += uphy_reg_header_func_dec_list_gen(reg_list)

    return code


def uphy_reg_auto_header_gen():
    """
    Generates UPHY reg header code
    :return: UPHY reg header code
    """
    code = ""

    struct_def_code = uphy_reg_header_struct_gen()
    func_dec_code = uphy_reg_header_func_dec_gen()

    code += UPHY_REG_H_AUTO_PATTERN % (struct_def_code, func_dec_code)

    return code


def uphy_reg_auto_source_gen():
    """
    Generates UPHY reg source file.
    :return: returns UPHY reg automated source file.
    """
    code = ""

    impl_func = uphy_reg_src_func_impl_gen()

    code += UPHY_REG_C_AUTO_PATTERN % (impl_func)

    return code


def Main():

    # Parse cmd line
    ParseCmdLine()

    try:

        if CMD_OPTIONS.CLNJsonInputFile and CMD_OPTIONS.DLNJsonInputFile:

            cln_path = CMD_OPTIONS.CLNJsonInputFile
            dln_path = CMD_OPTIONS.DLNJsonInputFile

            uphy_reg_db_init(cln_path, dln_path)

            OUTPUT_DIR = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + '/../')

            for fileName, command in AUTO_GENERATION_DICT.items():
                fullFileName = OUTPUT_DIR + os.sep + fileName
                with open(fullFileName, "w") as fileDesc:
                    code = eval(command)
                    fileDesc.write(code)

                print("\n[%s] - created successfully.\n" % (fullFileName))

            proc = subprocess.Popen([HEADER_CHECKER_CMD], stdout=subprocess.PIPE, shell=True, universal_newlines=True)
            (out, err) = proc.communicate()

            print("\nHeader checker finished successfully.\n")

            return 0

    except SystemExit:
        return 0

    except Exception as exp:
        sys.stderr.write("-E- %s\n" % exp)
        return 1
    return 0


if __name__ == "__main__":
    rc = 0
    try:
        rc = Main()
    except SystemExit as e:
        rc = e.code
    except Exception as e:
        sys.stderr.write("-E- %s\n" % e)
        traceback.print_exc()
        rc = 1
    sys.exit(rc)
