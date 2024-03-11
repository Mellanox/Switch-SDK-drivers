#!/usr/bin/env python3


import sys
import os
import xml.etree.ElementTree as ET
import subprocess


# SXD_KERNEL = "sxd_kernel/"
# MLX_SW_DRIVER = "drivers/net/"
# MLX_SW_INCLUDE = "include/linux/mlx_sx/"
# SX_SPICE_DIR = "sx_spice_dump/"
SDK_BASE_DIR = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + '/../../../../../')

OUTPUT_DIR = ""
INDENT = " " * 4

HEADER_CHECKER_CMD = "sudo docker run  -t  --rm --user $(id -u):$(id -g) -v " + SDK_BASE_DIR + "/:/git-repo harbor.mellanox.com/toolbox/header_check:latest " \
    "--config sxd_kernel/drivers/net/sx_spice_dump/generator/spice.yaml --path sxd_kernel/drivers/net/sx_spice_dump/ --repair"

# List of files to be generated
SX_SPICE_TREE_AUTO_H = "sx_spice_tree_auto.h"
SX_SPICE_TREE_AUTO_C = "sx_spice_tree_auto.c"

# SPICE TREE GENERATOR DBs:

# Tree Dictionary: key: tree name, value: tree root node
TREE_DICT = {}

# Indexes DB - holds indexes information used for global declarations.
# This DB is shared for both IB and ETH.
# The DB is consist of:
# 1. Sequence index list - holds the sequence index names
# 2. Enum index dictionary - key: index name + reg, value: list of (string, value) tuples which represents index possible values.
# 3. hidden index list - holds the hidden indexes names
INDEXES_DB = {'seq_idxs': {}, 'enum_idxs': {}, 'hidden_idxs': set()}

INDEX_SET_DB = {'eth': {}, 'ib': {}}

AUTO_GENERATION_DICT = {
    SX_SPICE_TREE_AUTO_H: "spice_tree_auto_header_gen()",
    SX_SPICE_TREE_AUTO_C: "spice_tree_auto_source_gen()"}

SPICE_TREE_H_AUTO_PATTERN = """
#include <linux/netdevice.h>
#include "sx_spice_wrapper.h"

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
"""

SPICE_TREE_C_AUTO_PATTERN = """
#include <linux/mlx_sx/kernel_user.h>
#include "sx_spice_tree_auto.h"
#include "sx_spice_access_reg.h"
#include "sx_spice_access_reg_auto.h"
#include "sx_spice_tree_dynamic.h"
#include "sx_spice_bulk_cntr.h"

/************************************************
 *  Global variables
 ***********************************************/


/************************************************
 *  Local variables
 ***********************************************/
%s

/************************************************
 *  Local function declarations
 ***********************************************/
%s

/************************************************
 *  Function implementations
 ***********************************************/
%s

"""

INDEX_TYPE_ENUM_PATTERN = """
typedef enum {\n%s%sMAX_INDEX_TYPE
} index_type_e;
"""


def spice_tree_index_enum_gen():
    """
    Geneartes index type enum declaration
    :return: enum declaration code.
    """
    pattern = """%s%s,\n"""

    code = ""

    for idx in INDEXES_DB['seq_idxs']:
        code += pattern % (INDENT, idx.upper())

    for idx in INDEXES_DB['hidden_idxs']:
        code += pattern % (INDENT, idx.upper())

    for idx in INDEXES_DB['enum_idxs']:
        idx_name = idx[0]
        code += pattern % (INDENT, idx_name.upper())

    code = INDEX_TYPE_ENUM_PATTERN % (code, INDENT)

    return code


def spice_tree_index_struct_gen():
    """
     Geneartes index type structure declaration
    :return: index type structure declaration code
    """
    pattern = """typedef struct index_type_data {
%schar    field_name[50];
%suint8_t field_value;
} index_type_data_t;\n\n"""

    code = ""

    code = pattern % (INDENT, INDENT)

    return code


def spice_tree_func_declaration_gen():
    """
    Generates public function declaration
    :return: public function declaration code.
    """
    create_func_pattern = """int sx_spice_tree_%s_create(dev_private_data_t *dev_data);\n"""
    init_func_pattern = """int sx_spice_tree_init(void);\n"""
    deinit_func_pattern = """void sx_spice_tree_deinit(void);\n"""
    index_get_func_pattern = """uint16_t sx_spice_tree_index_value_get(index_type_e index);\n"""
    create_app_dir_func_pattern = """int sx_spice_tree_%s_app_dir_create(void);\n"""

    code = ""

    code += init_func_pattern + deinit_func_pattern
    code += index_get_func_pattern

    for tree_name, tree_root in TREE_DICT.items():
        code += create_app_dir_func_pattern % tree_name
        for protocol in tree_root:
            str = tree_name + '_' + protocol.get('name')
            code += create_func_pattern % str

    return code


def spice_tree_auto_header_gen():
    """
    Generates SPICE tree header code
    :return: SPICE tree header code
    """
    code = ""

    type_def_code = spice_tree_index_struct_gen() + spice_tree_index_enum_gen()
    func_dec_code = spice_tree_func_declaration_gen()

    code = SPICE_TREE_H_AUTO_PATTERN % (type_def_code, func_dec_code)

    return code


def spice_tree_debugfs_global_dir_pointer_gen():
    """
    Generates global debugFS declaration (root and app directories).
    :return: global debugFS global directories declaration code
    """
    pattern = """static struct dentry * %s_p;\n"""

    code = ""

    code += pattern % 'root'

    for tree_name, root in TREE_DICT.items():
        code += pattern % tree_name

    return code


def spice_tree_debugfs_local_dir_pointer_gen(local_idxs_list):
    """
    Generates local debugFS declaration.
    :param local_idxs_list:
    :return: local debugFS global directories declaration code
    """
    pattern = """struct dentry * %s_p;\n"""

    code = ""

    code += INDENT + pattern % 'asic'

    for idx in local_idxs_list:
        code += INDENT + pattern % idx.lower()

    return code


def spice_tree_dir_iterator_dec_gen(local_idxs_list):
    """
    Generates local directory iterators declaration.
    :param local_idxs_list: list of indexes per current tree.
    :return: local directory iterators declaration code.
    """
    pattern = """int %s_it = 0;\n"""

    code = ""

    for idx in local_idxs_list:
        code += INDENT + pattern % idx.lower()

    return code


def spice_tree_index_type_array_gen():
    """
    Generates indexes array declaration.
    :return: ndexes array declaration code.
    """

    return """static uint16_t indexes_arr_g[MAX_INDEX_TYPE];\n"""


def spice_tree_string_value_declaration_gen():
    pattern1 = """static index_type_data_t %s_data_arr_g"""
    pattern2 = """[%s];\n"""

    code = ""

    for idx in INDEXES_DB['enum_idxs']:
        idx_name = idx[0]
        idx_reg = idx[1]
        if idx_reg == "":
            prefix = idx_name.lower()
        else:
            prefix = idx_reg + '_' + idx_name.lower()
        code += pattern1 % prefix
        idx_num = len(INDEXES_DB['enum_idxs'][idx])
        code += pattern2 % idx_num

    return code


def spice_tree_index_set_array_declaration_gen():
    pattern = """static char index_set_%s_%s_%s_arr_g[%s][%s];\n"""

    code = ""

    enum_idx_dict = INDEXES_DB['enum_idxs']
    seq_idx_dict = INDEXES_DB['seq_idxs']

    for protocol in INDEX_SET_DB:
        for idx1, idx2 in INDEX_SET_DB[protocol]:
            (reg1, reg2), val_list = INDEX_SET_DB[protocol][(idx1, idx2)]

            # Get idx1 num of values
            if (idx1, reg1) in enum_idx_dict:
                idx1_val_num = len(enum_idx_dict[(idx1, reg1)])

                if reg1 == "":
                    prefix1 = idx1
                else:
                    prefix1 = idx1 + '_' + reg1
            elif idx1 in seq_idx_dict:

                (min, max) = seq_idx_dict[idx1]
                idx1_val_num = int(max) + 1
                prefix1 = idx1
            else:
                print("Error - Index %s does not exist in INDEXES_DB\n" % idx1)

            # Get idx2 num of values
            if (idx2, reg2) in enum_idx_dict:
                idx2_val_num = len(enum_idx_dict[(idx2, reg2)])

                if reg2 == "":
                    prefix2 = idx2
                else:
                    prefix2 = idx2 + '_' + reg2
            elif idx2 in seq_idx_dict:
                (min, max) = seq_idx_dict[idx2]
                idx2_val_num = int(max) + 1
                prefix2 = idx2
            else:
                print("Error - Index %s does not exist in INDEXES_DB\n" % idx2)

            code += pattern % (protocol, prefix1, prefix2, idx1_val_num, idx2_val_num)

    return code


def spice_tree_src_local_vars_gen():
    """
    Generates SPICE tree C file local variables declarations.
    :return: SPICE tree C file local variables declarations code.
    """
    code = ""

    code = spice_tree_index_type_array_gen()
    code += '\n' + spice_tree_string_value_declaration_gen()
    code += '\n' + spice_tree_index_set_array_declaration_gen()
    code += '\n' + spice_tree_debugfs_global_dir_pointer_gen()

    return code


def spice_tree_string_value_func_declaration_gen():
    """
    Generates enum index string value function declaration.
    :return: enum index string value function declaration code.
    """
    pattern = """static void %s_arr_init(void);\n"""

    code = ""

    for idx in INDEXES_DB['enum_idxs']:
        idx_name = idx[0]
        idx_reg = idx[1]
        if idx_reg == "":
            prefix = idx_name.lower()
        else:
            prefix = idx_reg + '_' + idx_name.lower()
        code += pattern % prefix

    return code


def spice_tree_index_set_arr_func_declaration_gen():
    """
    Generates index set array function declaration.
    :return: index set array function declaration code.
    """
    pattern = """static void index_set_%s_%s_%s_arr_init(void);\n"""

    code = ""

    for protocol in INDEX_SET_DB:
        for idx1, idx2 in INDEX_SET_DB[protocol]:
            (reg1, reg2), val_list = INDEX_SET_DB[protocol][(idx1, idx2)]
            if reg1 == "":
                prefix1 = idx1
            else:
                prefix1 = idx1 + '_' + reg1

            if reg2 == "":
                prefix2 = idx2
            else:
                prefix2 = idx2 + '_' + reg2

            code += pattern % (protocol, prefix1, prefix2)

    return code


def enum_dictionary_item_index_get(dict, item):
    index = 0

    for k, v in dict.items():
        if k == item:
            return index
        index = index + 1

    return -1


def spice_tree_index_set_arr_func_impl_gen():
    pattern1 = """static void index_set_%s_%s_%s_arr_init(void)\n{\n"""
    pattern2 = """memset(&index_set_%s_%s_%s_arr_g, 0, sizeof(index_set_%s_%s_%s_arr_g));\n\n"""
    pattern3 = """index_set_%s_%s_%s_arr_g[%s][%s] = 1;\n"""
    code = ""

    for protocol in INDEX_SET_DB:
        for idx1, idx2 in INDEX_SET_DB[protocol]:
            (reg1, reg2), val_list = INDEX_SET_DB[protocol][(idx1, idx2)]
            if reg1 == "":
                prefix1 = idx1
            else:
                prefix1 = idx1 + '_' + reg1

            if reg2 == "":
                prefix2 = idx2
            else:
                prefix2 = idx2 + '_' + reg2

            code += pattern1 % (protocol, prefix1, prefix2)
            code += INDENT + pattern2 % (protocol, prefix1, prefix2, protocol, prefix1, prefix2)

            for v1, v2 in val_list:
                if (idx1, reg1) in INDEXES_DB['enum_idxs']:
                    dict1 = INDEXES_DB['enum_idxs'][(idx1, reg1)]
                    pos1 = enum_dictionary_item_index_get(dict1, v1)

                    if pos1 == -1:
                        print("ERROR - item [%s] does not exists in (%s) dictionary\n" %
                              (v1, idx1))
                elif idx1 in INDEXES_DB['seq_idxs']:
                    pos1 = v1
                else:
                    print("ERROR - index [%s] does not exists in seq index DB or enum index DB\n" %
                          idx1)

                if (idx2, reg2) in INDEXES_DB['enum_idxs']:
                    dict2 = INDEXES_DB['enum_idxs'][(idx2, reg2)]
                    pos2 = enum_dictionary_item_index_get(dict2, v2)

                    if pos2 == -1:
                        print("ERROR - item [%s] does not exists in (%s, %s) dictionary\n" %
                              (v2, idx2, reg2))
                elif idx2 in INDEXES_DB['seq_idxs']:
                    pos2 = v2
                else:
                    print("ERROR - index [%s] does not exists in seq index DB or enum index DB\n" %
                          idx2)

                code += INDENT + pattern3 % (protocol, prefix1, prefix2, str(pos1), str(pos2))

            code += "}\n\n"

    return code


def spice_tree_func_dec_gen():
    """
    Generates SPICE tree C local function declaration
    :return: SPICE tree C local function declaration code.
    """
    enum_index_arr_init = """static void enum_index_arr_init(void);\n"""
    index_sets_arr_init = """static void index_sets_arr_init(void);\n"""

    code = ""

    code += spice_tree_string_value_func_declaration_gen()
    code += '\n' + enum_index_arr_init
    code += '\n' + spice_tree_index_set_arr_func_declaration_gen()
    code += '\n' + index_sets_arr_init

    return code


def spice_tree_string_value_func_impl_gen():
    """
    Generates enum index string value function implementation.
    :return: enum index string value function implementation code.
    """

    pattern1 = """static void %s_arr_init(void)\n{\n"""
    pattern2 = """%smemset(&%s_data_arr_g, 0, sizeof(index_type_data_t) * %s);\n\n"""
    pattern3 = """%s%s_data_arr_g[%s].field_value = %s;\n"""
    pattern4 = """%ssprintf(%s_data_arr_g[%d].field_name, "%s");\n"""

    code = ""

    for idx in INDEXES_DB['enum_idxs']:
        count = 0
        idx_name = idx[0]
        idx_reg = idx[1]
        idx_num = len(INDEXES_DB['enum_idxs'][idx])
        if idx_reg == "":
            arr_prefix = idx_name.lower()
        else:
            arr_prefix = idx_reg + "_" + idx_name.lower()

        code += pattern1 % arr_prefix
        code += pattern2 % (INDENT, arr_prefix, idx_num)

        for k, v in INDEXES_DB['enum_idxs'][idx].items():
            code += pattern3 % (INDENT, arr_prefix, count, k)
            code += pattern4 % (INDENT, arr_prefix, count, v)
            count = count + 1

        code += "\n}\n\n"

    return code


def spice_tree_enum_index_arr_init_func_impl_gen():

    pattern1 = """static void enum_index_arr_init(void)\n{\n"""
    pattern2 = """%s%s_arr_init();\n"""

    code = ""
    code += pattern1

    for idx in INDEXES_DB['enum_idxs']:
        idx_name = idx[0]
        idx_reg = idx[1]
        if idx_reg == "":
            arr_prefix = idx_name.lower()
        else:
            arr_prefix = idx_reg + "_" + idx_name.lower()

        code += pattern2 % (INDENT, arr_prefix)

    return code + "\n}\n\n"


def spice_tree_index_sets_arr_init_func_impl_gen():

    pattern1 = """static void index_sets_arr_init(void)\n{\n"""
    pattern2 = """%sindex_set_%s_%s_%s_arr_init();\n"""

    code = ""
    code += pattern1

    for protocol in INDEX_SET_DB:
        for idx1, idx2 in INDEX_SET_DB[protocol]:
            (reg1, reg2), val_list = INDEX_SET_DB[protocol][(idx1, idx2)]
            if reg1 == "":
                prefix1 = idx1
            else:
                prefix1 = idx1 + '_' + reg1

            if reg2 == "":
                prefix2 = idx2
            else:
                prefix2 = idx2 + '_' + reg2

            code += pattern2 % (INDENT, protocol, prefix1, prefix2)

    return code + "\n}\n\n"


def seq_index_code_generate(protocol, node, parent, nest_level):
    """
    Generates the code pattern for sequence index node.
    :param protocol: protocol string - eth or ib
    :param node: current node - sequence index type
    :param parent: direct parent node
    :param nest_level: nest level fot indentation purposes.
    :return: sequence index code for given index
    """
    basic_for_pattern = """%sfor (%s_it = %s; %s_it <= %s; %s_it++) {"""
    system_for_pattern = """%sfor (%s_it = %s; %s_it <= dev_data->max_%s; %s_it++) {"""
    pattern = """\n%ssnprintf(dname, sizeof(dname), \"%s.%sd\", %s_it );
%s%s_p = debugfs_create_dir(dname, %s_p);
%sif (!%s_p) {
%sgoto allocation_failed;
%s}
%sindexes_arr_g[%s] = %s_it;\n
"""
    index_set_pattern = """\n%sif (index_set_%s_arr_g[%s_it][%s_it]) {
%ssnprintf(dname, sizeof(dname), \"%s.%sd\", %s_it );
%s%s_p = debugfs_create_dir(dname, %s_p);
%sif (!%s_p) {
%sgoto allocation_failed;
%s}
%sindexes_arr_g[%s] = %s_it;\n
"""
    code = ""

    nest0 = nest_level * INDENT
    nest1 = (nest_level + 1) * INDENT
    nest2 = (nest_level + 2) * INDENT
    nest3 = (nest_level + 3) * INDENT
    mod_sign = "%"
    index_name = node.get('name')
    parent_str = parent.get('name')

    if parent.tag == 'tree':
        parent_str = 'asic'

    if (node.get('system') == 'true'):
        code += system_for_pattern % (nest0, index_name, node.get('min'), index_name, index_name, index_name)
    else:
        code += basic_for_pattern % (nest0, index_name, node.get('min'), index_name, node.get('max'), index_name)

    for idx1, idx2 in INDEX_SET_DB[protocol]:
        if index_name == idx2 and parent_str == idx1:
            (reg1, reg2), val_list = INDEX_SET_DB[protocol][(idx1, idx2)]
            if reg1 == "":
                prefix1 = idx1
            else:
                prefix1 = idx1 + '_' + reg1

            if reg2 == "":
                prefix2 = idx2
            else:
                prefix2 = idx2 + '_' + reg2

            arr_prefix = protocol + '_' + prefix1 + '_' + prefix2

            code += index_set_pattern % (nest1, arr_prefix, idx1, idx2,
                                         nest2, index_name, mod_sign, index_name,
                                         nest2, index_name, parent_str,
                                         nest2, index_name,
                                         nest3, nest2,
                                         nest2, index_name.upper(), index_name)

            return code, True

    code += pattern % (nest1, index_name, mod_sign, index_name,
                       nest1, index_name, parent_str,
                       nest1, index_name,
                       nest2, nest1,
                       nest1, index_name.upper(), index_name)

    return code, False


def enum_index_code_generate(protocol, node, parent, nest_level):
    """
    Generates the code pattern for enum index node.
    :param protocol: protocol string - eth or ib
    :param node: current node - enum index type
    :param parent: direct parent node
    :param nest_level: nest level fot indentation purposes.
    :return: enum index code for given index
    """

    pattern = """%sfor (%s_it = 0; %s_it < %s; %s_it++) {
%ssnprintf(dname, sizeof(dname), \"%s.%ss.0x%sX\",
%s%s_data_arr_g[%s_it].field_name,
%s%s_data_arr_g[%s_it].field_value);
%s%s_p = debugfs_create_dir(dname, %s_p);

%sif (!%s_p) {
%sgoto allocation_failed;
%s}
%sindexes_arr_g[%s] = %s_data_arr_g[%s_it].field_value;\n
"""

    index_set_pattern = """%sfor (%s_it = 0; %s_it < %s; %s_it++) {
%sif (index_set_%s_arr_g[%s_it][%s_it]) {
%ssnprintf(dname, sizeof(dname), \"%s.%ss.0x%sX\",
%s%s_data_arr_g[%s_it].field_name,
%s%s_data_arr_g[%s_it].field_value);
%s%s_p = debugfs_create_dir(dname, %s_p);

%sif (!%s_p) {
%sgoto allocation_failed;
%s}
%sindexes_arr_g[%s] = %s_data_arr_g[%s_it].field_value;\n
"""

    code = ""

    nest0 = nest_level * INDENT
    nest1 = (nest_level + 1) * INDENT
    nest2 = (nest_level + 2) * INDENT
    nest3 = (nest_level + 3) * INDENT
    mod_sign = "%"
    index_name = node.get('name')
    reg = node.get('reg')
    dir_num = len(INDEXES_DB['enum_idxs'][(index_name, reg)])
    parent_str = parent.get('name')

    if parent.tag == 'tree':
        parent_str = 'asic'

    if reg == "":
        prefix = index_name
    else:
        prefix = reg + '_' + index_name

    for idx1, idx2 in INDEX_SET_DB[protocol]:
        if index_name == idx2:
            (reg1, reg2), val_list = INDEX_SET_DB[protocol][(idx1, idx2)]
            if reg1 == "":
                prefix1 = idx1
            else:
                prefix1 = idx1 + '_' + reg1

            if reg2 == "":
                prefix2 = idx2
            else:
                prefix2 = idx2 + '_' + reg2

            arr_prefix = protocol + '_' + prefix1 + '_' + prefix2

            code = index_set_pattern % (nest0, index_name, index_name, dir_num, index_name,
                                        nest1, arr_prefix, idx1, idx2,
                                        nest2, index_name, mod_sign, mod_sign,
                                        nest3, prefix, index_name,
                                        nest3, prefix, index_name,
                                        nest2, index_name, parent_str,
                                        nest2, index_name,
                                        nest3, nest2,
                                        nest2, index_name.upper(), prefix, index_name)

            return code, True

    code = pattern % (nest0, index_name, index_name, dir_num, index_name,
                      nest1, index_name, mod_sign, mod_sign,
                      nest2, prefix, index_name,
                      nest2, prefix, index_name,
                      nest1, index_name, parent_str,
                      nest1, index_name,
                      nest2, nest1,
                      nest1, index_name.upper(), prefix, index_name)

    return code, False


def hidden_index_code_generate(node, nest_level):
    """
    Generates the code pattern for hidden index node.
    :param node: current node - hidden index type
    :param nest_level: nest level fot indentation purposes.
    :return: hidden index code for given index
    """
    pattern = """indexes_arr_g[%s] = %s;\n"""
    code = ""

    code = (INDENT * nest_level) + pattern % ((node.get('name')).upper(), node.get('value'))

    return code


def reg_code_generate(node, parent, nest_level):
    """
    Generates the code pattern for register node.
    :param node: current node - register type
    :param parent: direct parent node
    :param nest_level: nest level fot indentation purposes.
    :return: register code pattern
    """
    pattern = """%serr = sx_spice_access_reg_%s_file_create(%s_p, dev_data);
%sif (err) {
%sgoto allocation_failed;
%s}\n"""

    code = ""

    index_name = parent.get('name')

    if parent.tag == 'tree':
        prefix = 'asic'
    else:
        prefix = index_name

    code = pattern % (nest_level * INDENT, (node.get('name')).lower(), prefix,
                      nest_level * INDENT, (nest_level + 1) * INDENT, nest_level * INDENT)

    return code


def dynamic_tree_code_generate(protocol, node, parent, nest_level):
    """
    Generates dynamic tree code patterns.

    Dynamic tree ADB nodes holds the following structure:
    <dynamic_tree type="index \ system" index="<index name>"(optinal field)>
        SUB_TREE_1
        SUB_TREE_2
           ...
        DEFAULT_TREE (register node)
    </dynamic_tree>

    This function generates the following pattern:
    1. boolean function calls
    2. if else clause:
          if (<bool SUB_TREE_1>) {
              <recursive call on SUB_TREE_1>
          } else if (<bool SUB_TREE_2>) {
               <recursive call on SUB_TREE_2>
          } ......
          } else {
              <recursive call on DEFAULT_TREE>
          }
    :param protocol: protocol string - eth or ib
    :param node: dynamic tree node
    :param parent: direct parent node
    :param nest_level:  nest level fot indentation purposes.
    :return: dynamic tree code according to the given dynamic tree nodes.
    """
    system_bool_func_call_pattern = """is_%s_dir_supported(dev_data)"""
    index_bool_seq_idx_func_call_pattern = """is_%s_dir_supported(dev_data, %s_it)"""
    index_bool_enum_idx_func_call_pattern = """is_%s_dir_supported(dev_data, %s_arr_g[%s_it].field_value)"""
    if_clause_pattern = """%sif (%s) {
%s %s}"""
    else_if_clause_pattern = """ else if (%s) {
%s %s}"""
    else_clause_pattern = """ else {
%s %s}\n"""

    func_call_seg_code = ""
    dynamic_tree_code = ""
    code = ""

    first_child = True
    for child in node:
        if child.tag == 'enum_index' or child.tag == 'seq_index':
            str = child.get('name')
            if (child.tag == 'enum_index' and child.get('reg') != ""):
                str += '_' + child.get('reg')

            if (node.get('type') == 'system'):
                func_call_seg_code += system_bool_func_call_pattern % (str)
            elif (node.get('type') == 'index'):
                index_str = node.get('index')
                if parent.tag == 'seq_index':
                    func_call_seg_code += index_bool_seq_idx_func_call_pattern % (str, index_str)
                elif parent.tag == 'enum_index':
                    parent_str = parent.get('name')
                    if parent.get('reg') != "":
                        parent_str += parent.get('reg')
                    func_call_seg_code += index_bool_enum_idx_func_call_pattern % (str, parent_str, index_str)
            else:
                raise Exception("%s dynamic tree node type is not supported" % node.get('type'))
                return 1

            # recursive call on node children
            code = spice_tree_create_rec(protocol, child, parent, nest_level + 1)

            if (first_child):
                dynamic_tree_code += if_clause_pattern % (nest_level * INDENT, func_call_seg_code, code, nest_level * INDENT)
                first_child = False
            else:
                dynamic_tree_code += else_if_clause_pattern % (func_call_seg_code, code, nest_level * INDENT)
        elif (child.tag == 'reg'):
            code = spice_tree_create_rec(protocol, child, parent, nest_level + 1)
            dynamic_tree_code += else_clause_pattern % (code, nest_level * INDENT)

    return (dynamic_tree_code + "\n")


def spice_tree_create_rec(protocol, node, parent, nest_level):
    """
    Recursive function which iterates over the ADB SPICE tree and generates the SPICE tree directory structure code.
    :param protocol: protocol string - eth or ib
    :param node: tree current node
    :param parent: direct parent node
    :param nest_level: nest level fot indentation purposes.
    :return:
    """
    code = ""

    if node.tag == 'hidden_index':
        code += hidden_index_code_generate(node, nest_level)
    elif node.tag == 'enum_index':
        (tmp_code_buff, flag) = enum_index_code_generate(protocol, node, parent, nest_level)
        code += tmp_code_buff
        if flag:
            for child in node:
                code += spice_tree_create_rec(protocol, child, node, nest_level + 2)
            code += (nest_level + 1) * INDENT + '}\n'
        else:
            for child in node:
                code += spice_tree_create_rec(protocol, child, node, nest_level + 1)
        code += nest_level * INDENT + '}\n'
    elif node.tag == 'seq_index':
        (tmp_code_buff, flag) = seq_index_code_generate(protocol, node, parent, nest_level)
        code += tmp_code_buff
        if flag:
            for child in node:
                code += spice_tree_create_rec(protocol, child, node, nest_level + 2)
            code += (nest_level + 1) * INDENT + '}\n'
        else:
            for child in node:
                code += spice_tree_create_rec(protocol, child, node, nest_level + 1)
        code += nest_level * INDENT + '}\n'
    elif node.tag == 'reg':
        code += reg_code_generate(node, parent, nest_level)
    elif node.tag == 'dynamic_tree':
        code += dynamic_tree_code_generate(protocol, node, parent, nest_level)
    else:
        raise Exception("%s xml tag is not supported" % node.tag)
        return 1

    return code


def spice_tree_create_impl_gen(tree_name, protocol, tree_node):
    """
    Generates SPICE tree create function implementation
    :param tree_name:
    :param protocol: protocol string - eth or ib
    :param tree_node: root tree node
    :return: create tree implementation code.
    """
    pattern = """int sx_spice_tree_%s_%s_create(dev_private_data_t *dev_data)
{
%sint  err;
%schar dname[60] = { 0 };

%s
%sprintk(KERN_INFO \"sx_spice_tree_%s_%s_create\\n\");

%ssnprintf(dname, sizeof(dname), \"ASIC.%sd\", dev_data->dev->device_id);
%sasic_p = debugfs_create_dir(dname, %s_p);
%sif (!asic_p) {
%sgoto allocation_failed;
%s}

%sdev_data->%s_root_inode_p = asic_p;

%s
%sreturn 0;

allocation_failed:
%sdebugfs_remove_recursive(asic_p);
%sreturn -ENOMEM;
}\n
"""

    code = ""
    dec_code = ""

    local_idxs_list = set()

    spice_tree_local_idxs_list_populate(tree_node, local_idxs_list)

    # Generates debugFS directory pointers declaration.
    dec_code += spice_tree_debugfs_local_dir_pointer_gen(local_idxs_list)

    # Generates debugFS directory iterators declaration.
    dec_code += '\n' + spice_tree_dir_iterator_dec_gen(local_idxs_list) + '\n'

    # Generates directory tree creation code
    for child in tree_node:
        code += spice_tree_create_rec(protocol, child, tree_node, 1)

    mod_sign = "%"

    code = pattern % (tree_name, protocol, INDENT, INDENT,
                      dec_code, INDENT,
                      tree_name, protocol,
                      INDENT, mod_sign,
                      INDENT, tree_name,
                      INDENT, INDENT * 2, INDENT, INDENT,
                      tree_name, code,
                      INDENT, INDENT, INDENT)

    return code


def spice_tree_create_app_dir_impl_gen(tree_name):
    """
    Generates application debugFS directory creation function.
    :param tree_name:
    :return: application debugFS directory creation function code.
    """
    pattern = """int sx_spice_tree_%s_app_dir_create(void)
{
%s%s_p = debugfs_create_dir(\"%s\", root_p);
%sif (!%s_p) {
%sgoto allocation_failed;
%s}

%sreturn 0;

allocation_failed:
%sreturn -ENOMEM;
}\n
"""

    code = ""

    code = pattern % (tree_name, INDENT, tree_name, tree_name,
                      INDENT, tree_name,
                      INDENT * 2, INDENT, INDENT, INDENT)

    return code


def spice_tree_src_func_impl_iterate():
    """
    Generates SPICE tree create and destroy function implementation.
    :return: SPICE tree create and destroy function implementation code.
    """
    code = ""

    for tree_name, root in TREE_DICT.items():
        code += spice_tree_create_app_dir_impl_gen(tree_name)
        for protocol in root:
            code += spice_tree_create_impl_gen(tree_name, protocol.get('name'), protocol.find('tree'))

    return code


def spice_tree_index_value_get_func_gen():
    pattern = """uint16_t sx_spice_tree_index_value_get(index_type_e index)
{
%sreturn indexes_arr_g[index];
}\n\n"""

    code = ""

    code = pattern % INDENT

    return code


def spice_tree_src_func_impl_gen():
    """
    Generates SPICE tree C function implementation segment.
    :return: SPICE tree C function implementation segment code.
    """

    code = ""

    code += spice_tree_index_value_get_func_gen()
    code += spice_tree_string_value_func_impl_gen()
    code += spice_tree_index_set_arr_func_impl_gen()
    code += spice_tree_enum_index_arr_init_func_impl_gen()
    code += spice_tree_index_sets_arr_init_func_impl_gen()
    code += spice_tree_module_init_func_gen()
    code += spice_tree_src_func_impl_iterate()

    return code


def spice_tree_module_init_func_gen():
    pattern_init = """int sx_spice_tree_init(void)
{
%sprintk(KERN_INFO \"sx_spice_tree_init\\n\");

%senum_index_arr_init();
%sindex_sets_arr_init();

%sroot_p = debugfs_create_dir(\"nvswitch\", NULL);
%sif (!root_p) {
%sgoto allocation_failed;
%s}

%sreturn 0;

allocation_failed:
%sdebugfs_remove_recursive(root_p);
%sreturn -ENOMEM;
}\n
"""
    pattern_deinit = """void sx_spice_tree_deinit(void)
{
%sprintk(KERN_INFO \"In sx_spice_tree_deinit function \\n\");
%sdebugfs_remove_recursive(root_p);
}\n
"""

    code = ""

    code += pattern_init % (INDENT, INDENT, INDENT, INDENT, INDENT, INDENT * 2,
                            INDENT, INDENT, INDENT, INDENT)
    code += pattern_deinit % (INDENT, INDENT)

    return code


def spice_tree_auto_source_gen():
    """
    Generates SPICE tree source file.
    :return: returns spice tree auto,ated source file.
    """
    code = ""

    local_vars_code = spice_tree_src_local_vars_gen()

    local_func = spice_tree_func_dec_gen()

    impl_func = spice_tree_src_func_impl_gen()

    code += SPICE_TREE_C_AUTO_PATTERN % (local_vars_code, local_func, impl_func)

    return code


def spice_tree_db_add(tree):

    root = tree.getroot()
    tree_name = root.attrib['name'].lower()
    TREE_DICT[tree_name] = tree.getroot()


def spice_tree_db_init():
    """
    Initialize SPICE TREE DB
    """
    # lookup ADB files
    xml_dir = os.path.realpath(os.path.dirname(os.path.realpath(__file__)) + '/../adb/')

    for root, dirs, files in os.walk(xml_dir):
        for file in files:
            if file.endswith('.adb'):
                tree = ET.parse(xml_dir + os.sep + file)
                spice_tree_db_add(tree)


def spice_enum_indexes_db_update(idx_node):
    """
    Updates INDEXES_DB with enum indexes data.
    :param idx_node: adabe indexes node which consist all enum indexes data
    """

    # Iterate over enum indexes and populate the enum_idxs dictionary
    for enum_idx in idx_node.iter('enum_index'):
        enum_idx_dict = {}
        for idx_type in enum_idx.iter('index_type'):
            enum_idx_dict[idx_type.attrib['value']] = idx_type.attrib['name']

        INDEXES_DB['enum_idxs'][(enum_idx.attrib['name'], enum_idx.attrib['reg'])] = enum_idx_dict


def spice_index_set_db_update(protocol, idx_node):
    """
    Updates INDEX_SET_DB with index set data.
    :param protocol: protocol string - eth or ib
    :param idx_node: adabe indexes node which consist all index sets data
    """

    for idx_set in idx_node.iter('index_set'):
        idx_set_list = set()
        reg1 = idx_set.attrib['reg1']
        reg2 = idx_set.attrib['reg2']
        for idx_val in idx_set.iter('index_set_values'):
            idx_set_list.add((idx_val.attrib['idx1'], idx_val.attrib['idx2']))

        INDEX_SET_DB[protocol][(idx_set.attrib['idx1_name'], idx_set.attrib['idx2_name'])] = ((reg1, reg2), idx_set_list)


def spice_tree_indexes_db_update(tree):
    """
    Updates INDEXES_DB with sequence and hidden indexes data.
    :param tree: tree node
    """

    for idx in tree.iter('seq_index'):
        INDEXES_DB['seq_idxs'][idx.attrib['name']] = (idx.attrib['min'], idx.attrib['max'])

    for idx in tree.iter('hidden_index'):
        INDEXES_DB['hidden_idxs'].add(idx.attrib['name'])


def spice_tree_local_idxs_list_populate(tree, local_idxs_list):
    """
    Updates local_idxs_list with sequence and enum indexes data.
    :param node: tree node
    """

    for idx in tree.iter('seq_index'):
        local_idxs_list.add(idx.attrib['name'])

    for idx in tree.iter('enum_index'):
        local_idxs_list.add(idx.attrib['name'])


def spice_indexes_db_init():
    """
    Initialize indexes databases.
    :return: 0 - success 1 - in case of error.
    """

    for tree_name, root in TREE_DICT.items():
        for protocol in root:
            for child in protocol:
                if child.tag == 'indexes':
                    spice_enum_indexes_db_update(child)
                    spice_index_set_db_update(protocol.attrib['name'], child)
                elif child.tag == 'tree':
                    spice_tree_indexes_db_update(child)
                else:
                    raise Exception("%s xml tag is not supported." % child.tag)
                    return 1

    return 0


def Main():

    try:
        # Initilaize XML Tree DB and Indexes DB
        spice_tree_db_init()
        spice_indexes_db_init()

        OUTPUT_DIR = os.path.normpath(os.path.dirname(os.path.abspath(__file__)) + '/../')

        for fileName, command in AUTO_GENERATION_DICT.items():
            fullFileName = OUTPUT_DIR + os.sep + fileName
            with open(fullFileName, "w") as fileDesc:
                code = eval(command)
                fileDesc.write(code)

            print("[%s] - created successfully.\n" % (fullFileName))

        proc = subprocess.Popen([HEADER_CHECKER_CMD], stdout=subprocess.PIPE, shell=True, universal_newlines=True)
        (out, err) = proc.communicate()

        print("Header checker finished successfully.\n")

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
        rc = 1
    sys.exit(rc)
