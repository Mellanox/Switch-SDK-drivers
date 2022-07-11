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

TREE_DICT = {}   # Contains tree name and its root
INDEXES_DB = {'seq_idxs': set(), 'enum_idxs': {}, 'hidden_idxs': set()}

AUTO_GENERATION_DICT = {
    SX_SPICE_TREE_AUTO_H: "spice_tree_auto_header_gen()",
    SX_SPICE_TREE_AUTO_C: "spice_tree_auto_source_gen()"}

SPICE_TREE_H_AUTO_PATTERN = """
#include <linux/netdevice.h>

/************************************************
 *  Defines
 ***********************************************/

/************************************************
 *  Macros
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/

typedef struct index_type_data {
\tchar    field_name[50];
\tuint8_t field_value;
} index_type_data_t;

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
#include "sx_spice_access_reg_auto.h"

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
typedef enum {
%s\tMAX_INDEX_TYPE
} index_type_e;
"""


def spice_tree_index_enum_gen():
    pattern = """\t%s,\n """

    code = ""

    for idx in INDEXES_DB['seq_idxs']:
        code += pattern % idx.upper()

    for idx in INDEXES_DB['hidden_idxs']:
        code += pattern % idx.upper()

    for idx in INDEXES_DB['enum_idxs']:
        idx_name = idx[0]
        code += pattern % idx_name.upper()

    code = INDEX_TYPE_ENUM_PATTERN % code

    return code


def spice_tree_func_declaration_gen():
    create_func_pattern = """int sx_spice_tree_%s_create(void);\n"""
    destroy_func_pattern = """void sx_spice_tree_%s_destroy(void);\n"""
    init_func_pattern = """int sx_spice_tree_init(void);\n"""
    deinit_func_pattern = """void sx_spice_tree_deinit(void);\n"""
    index_get_func_pattern = """uint16_t sx_spice_tree_index_value_get(index_type_e index);\n"""

    code = ""

    code += init_func_pattern + deinit_func_pattern
    code += index_get_func_pattern

    for tree_name, tree_root in TREE_DICT.items():
        code += create_func_pattern % tree_name
        code += destroy_func_pattern % tree_name

    return code


def spice_tree_auto_header_gen():
    code = ""

    enum_code = spice_tree_index_enum_gen()
    func_dec_code = spice_tree_func_declaration_gen()

    code = SPICE_TREE_H_AUTO_PATTERN % (enum_code, func_dec_code)

    return code


def spice_tree_debugfs_dir_pointer_gen():
    pattern = """static struct dentry * %s_p;\n"""

    code = ""

    code += pattern % 'root'

    for tree_name, root in TREE_DICT.items():
        app = (tree_name.split('_')[0]).lower()
        code += pattern % app

    for idx in INDEXES_DB['seq_idxs']:
        code += pattern % idx.lower()

    for idx_name, reg in INDEXES_DB['enum_idxs']:
        if reg == "":
            prefix = idx_name.lower()
        else:
            prefix = reg.lower() + '_' + idx_name.lower()
        code += pattern % prefix

    return code


def spice_tree_dir_iterator_dec_gen():
    pattern = """static int %s_it = 0;\n"""

    code = ""

    for idx in INDEXES_DB['seq_idxs']:
        code += pattern % idx.lower()

    for idx_name, reg in INDEXES_DB['enum_idxs']:
        if reg == "":
            prefix = idx_name.lower()
        else:
            prefix = reg.lower() + '_' + idx_name.lower()
        code += pattern % prefix

    return code


def spice_tree_index_type_array_gen():

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


def spice_tree_src_local_vars_gen():
    code = ""

    code = spice_tree_index_type_array_gen()
    code += '\n' + spice_tree_string_value_declaration_gen()
    code += '\n' + spice_tree_debugfs_dir_pointer_gen()
    code += '\n' + spice_tree_dir_iterator_dec_gen()

    return code


def spice_tree_string_value_func_declaration_gen():
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


def spice_tree_func_dec_gen():
    enum_index_arr_init = """static void enum_index_arr_init(void);\n"""

    code = ""

    code += spice_tree_string_value_func_declaration_gen() + '\n' + enum_index_arr_init

    return code


def spice_tree_string_value_func_impl_gen():

    pattern1 = """static void %s_arr_init(void)\n{\n"""
    pattern2 = """\tmemset(&%s_data_arr_g, 0, sizeof(index_type_data_t) * %s);\n\n"""
    pattern3 = """\t%s_data_arr_g[%s].field_value = %s;\n"""
    pattern4 = """\tsprintf(%s_data_arr_g[%d].field_name, "%s");\n"""

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
        code += pattern2 % (arr_prefix, idx_num)

        for k, v in INDEXES_DB['enum_idxs'][idx].items():
            code += pattern3 % (arr_prefix, count, k)
            code += pattern4 % (arr_prefix, count, v)
            count = count + 1

        code += "\n}\n\n"

    return code


def spice_tree_enum_index_arr_init_func_impl_gen():

    pattern1 = """static void enum_index_arr_init(void)\n{\n"""
    pattern2 = """\t%s_arr_init();\n"""

    code = ""
    code += pattern1

    for idx in INDEXES_DB['enum_idxs']:
        idx_name = idx[0]
        idx_reg = idx[1]
        if idx_reg == "":
            arr_prefix = idx_name.lower()
        else:
            arr_prefix = idx_reg + "_" + idx_name.lower()

        code += pattern2 % arr_prefix

    return code + "\n}\n\n"


def seq_index_code_generate(node, parent, nest_level):
    pattern = """%sfor (%s_it = %s; %s_it <= %s; %s_it++) {
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
    mod_sign = "%"
    index_name = node.get('name')
    parent_str = parent.get('name')

    if parent.tag == 'enum_index':
        parent_str += '_' + parent.get('reg')

    code = pattern % (nest0, index_name, node.get('min'), index_name, node.get('max'), index_name,
                      nest1, index_name, mod_sign, index_name,
                      nest1, index_name, parent_str,
                      nest1, index_name,
                      nest2, nest1,
                      nest1, index_name.upper(), index_name)

    return code


def enum_index_code_generate(node, parent, nest_level):
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

    code = ""

    nest0 = nest_level * INDENT
    nest1 = (nest_level + 1) * INDENT
    nest2 = (nest_level + 2) * INDENT
    mod_sign = "%"
    index_name = node.get('name')
    reg = node.get('reg')
    dir_num = len(INDEXES_DB['enum_idxs'][(index_name, reg)])
    parent_str = parent.get('name')

    if parent.tag == 'enum_index' and parent.get('reg') != "":
        parent_str = parent.get('reg') + '_' + parent_str

    if reg == "":
        prefix = index_name
    else:
        prefix = reg + '_' + index_name

    code = pattern % (nest0, prefix, prefix, dir_num, prefix,
                      nest1, index_name, mod_sign, mod_sign,
                      nest2, prefix, prefix,
                      nest2, prefix, prefix,
                      nest1, prefix, parent_str,
                      nest1, prefix,
                      nest2, nest1,
                      nest1, index_name.upper(), prefix, prefix)

    return code


def hidden_index_code_generate(node, nest_level):
    pattern = """indexes_arr_g[%s] = %s;\n"""
    code = ""

    code = (INDENT * nest_level) + pattern % ((node.get('name')).upper(), node.get('value'))

    return code


def reg_code_generate(node, parent, nest_level):
    pattern = """%serr = sx_spice_access_reg_%s_file_create(%s_p);
%sif (err) {
%sgoto allocation_failed;
%s}\n"""

    code = ""

    index_name = parent.get('name')
    if parent.tag == 'enum_index' and parent.get('reg') != "":
        prefix = parent.get('reg') + '_' + index_name
    else:
        prefix = index_name

    code = pattern % (nest_level * INDENT, (node.get('name')).lower(), prefix,
                      nest_level * INDENT, (nest_level + 1) * INDENT, nest_level * INDENT)

    return code


def spice_tree_create_rec(node, parent, nest_level):
    code = ""

    if node.tag == 'hidden_index':
        code += hidden_index_code_generate(node, nest_level)
    elif node.tag == 'enum_index':
        code += enum_index_code_generate(node, parent, nest_level)
        for child in node:
            code += spice_tree_create_rec(child, node, nest_level + 1)
        code += nest_level * INDENT + '}\n'
    elif node.tag == 'seq_index':
        code += seq_index_code_generate(node, parent, nest_level)
        for child in node:
            code += spice_tree_create_rec(child, node, nest_level + 1)
        code += nest_level * INDENT + '}\n'
    elif node.tag == 'reg':
        code += reg_code_generate(node, parent, nest_level)
    else:
        raise Exception("%s xml tag is not supported" % node.tag)
        return 1

    return code


def spice_tree_create_impl_gen(tree_name, tree_node):
    pattern = """int sx_spice_tree_%s_create(void)
{
\tint  err;
\tchar dname[60] = { 0 };

\tprintk(KERN_INFO \"sx_spice_tree_%s_create\\n\");

\t%s_p = debugfs_create_dir(\"%s\", root_p);
\tif (!%s_p) {
\t\tgoto allocation_failed;
\t}

%s
\treturn 0;

allocation_failed:
\tdebugfs_remove_recursive(%s_p);
\treturn -ENOMEM;
}\n
"""

    code = ""

    for child in tree_node:
        code += spice_tree_create_rec(child, tree_node, 1)

    app_name = tree_node.get('name')

    code = pattern % (tree_name, tree_name, app_name, app_name, app_name, code, app_name)

    return code


def spice_tree_destroy_impl_gen(tree_name, tree_node):
    pattern = """void sx_spice_tree_%s_destroy(void)
{
\tprintk(KERN_ERR \"In sx_spice_tree_%s_destroy function \\n\");
\tdebugfs_remove_recursive(%s_p);
}\n
"""
    code = ""

    app_name = tree_node.get('name')

    code = pattern % (tree_name, tree_name, tree_node.get('name'))

    return code


def spice_tree_src_func_impl_iterate():
    code = ""

    for tree_name, root in TREE_DICT.items():
        code += spice_tree_create_impl_gen(tree_name, root.find('tree'))
        code += spice_tree_destroy_impl_gen(tree_name, root.find('tree'))

    return code


def spice_tree_index_value_get_func_gen():
    pattern = """uint16_t sx_spice_tree_index_value_get(index_type_e index)
{
\treturn indexes_arr_g[index];
}\n\n"""

    return pattern


def spice_tree_src_func_impl_gen():

    code = ""

    code += spice_tree_index_value_get_func_gen()
    code += spice_tree_string_value_func_impl_gen()
    code += spice_tree_enum_index_arr_init_func_impl_gen()
    code += spice_tree_module_init_func_gen()
    code += spice_tree_src_func_impl_iterate()

    return code


def spice_tree_module_init_func_gen():
    pattern_init = """int sx_spice_tree_init(void)
{
\tprintk(KERN_INFO \"sx_spice_tree_init\\n\");

\tenum_index_arr_init();

\troot_p = debugfs_create_dir(\"nvswitch\", NULL);
\tif (!root_p) {
\t\tgoto allocation_failed;
\t}

\treturn 0;

allocation_failed:
\tdebugfs_remove_recursive(root_p);
\treturn -ENOMEM;
}\n
"""
    pattern_deinit = """void sx_spice_tree_deinit(void)
{
\tprintk(KERN_ERR \"In sx_spice_tree_deinit function \\n\");
\tdebugfs_remove_recursive(root_p);
}\n
"""

    code = ""

    code += pattern_init + pattern_deinit

    return code


def spice_tree_auto_source_gen():
    code = ""

    local_vars_code = spice_tree_src_local_vars_gen()

    local_func = spice_tree_func_dec_gen()

    impl_func = spice_tree_src_func_impl_gen()

    code += SPICE_TREE_C_AUTO_PATTERN % (local_vars_code, local_func, impl_func)

    return code


def spice_tree_db_add(file_name, tree):

    tree_name = (file_name.split('.')[0]).replace("sx_spice_", "")
    TREE_DICT[tree_name] = tree.getroot()


def spice_tree_db_init():
    # lookup ADB files
    xml_dir = os.path.realpath(os.path.dirname(os.path.realpath(__file__)) + '/../adb/')

    for root, dirs, files in os.walk(xml_dir):
        for file in files:
            if file.endswith('.adb'):
                tree = ET.parse(xml_dir + os.sep + file)
                spice_tree_db_add(file, tree)


def spice_enum_indexes_db_update(idx_node):

    # Iterate over enum indexes and populate the enum_idxs dictionary
    for enum_idx in idx_node.iter('enum_index'):
        enum_idx_dict = {}
        for idx_type in enum_idx.iter('index_type'):
            enum_idx_dict[idx_type.attrib['value']] = idx_type.attrib['name']

        INDEXES_DB['enum_idxs'][(enum_idx.attrib['name'], enum_idx.attrib['reg'])] = enum_idx_dict


def spice_tree_indexes_db_update(node):
    for idx in node.iter('seq_index'):
        INDEXES_DB['seq_idxs'].add(idx.attrib['name'])

    for idx in node.iter('hidden_index'):
        INDEXES_DB['hidden_idxs'].add(idx.attrib['name'])


def spice_indexes_db_init():

    for tree_name, root in TREE_DICT.items():
        for child in root:
            if child.tag == 'indexes':
                spice_enum_indexes_db_update(child)
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

            print("[%s] - created successfuly.\n" % (fullFileName))

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
