#include <linux/debugfs.h>

/************************************************
 *  Local variables
 ***********************************************/

/************************************************
 *  Type definitions
 ***********************************************/
#define KERNEL_BUFFER_SIZE 10000

typedef struct pmdr_data {
    uint16_t local_port;
    uint8_t pnat;
    struct list_head pmdr_list;
} pmdr_data_t;

typedef struct mvcap_data {
    uint8_t slot_index;
    struct list_head mvcap_list;
} mvcap_data_t;

typedef struct pddr_data {
    uint16_t local_port;
    sxd_pddr_pnat_t pnat;
    sxd_pddr_port_type_t port_type;
    sxd_pddr_page_select_t page_select;
    struct list_head pddr_list;
} pddr_data_t;

typedef struct mgir_data {
    struct list_head mgir_list;
} mgir_data_t;

typedef struct ppcnt_data {
    uint8_t swid;
    uint16_t local_port;
    sxd_ppcnt_pnat_t pnat;
    uint8_t port_type;
    sxd_ppcnt_grp_t grp;
    uint8_t prio_tc;
    struct list_head ppcnt_list;
} ppcnt_data_t;

typedef struct spzr_data {
    uint8_t swid;
    struct list_head spzr_list;
} spzr_data_t;

typedef struct mtcap_data {
    uint8_t slot_index;
    struct list_head mtcap_list;
} mtcap_data_t;

typedef struct ptys_data {
    uint16_t local_port;
    sxd_ptys_pnat_t pnat;
    sxd_ptys_port_type_t port_type;
    sxd_ptys_proto_mask_t proto_mask;
    struct list_head ptys_list;
} ptys_data_t;

typedef struct mdir_data {
    struct list_head mdir_list;
} mdir_data_t;

typedef struct spad_data {
    struct list_head spad_list;
} spad_data_t;

typedef struct msgi_data {
    struct list_head msgi_list;
} msgi_data_t;

/************************************************
 * Functions                                    *
 ***********************************************/

int sx_spice_access_reg_pmdr_file_create(struct dentry *parent);
void sx_spice_access_reg_pmdr_list_free(void);
int sx_spice_access_reg_mvcap_file_create(struct dentry *parent);
void sx_spice_access_reg_mvcap_list_free(void);
int sx_spice_access_reg_pddr_file_create(struct dentry *parent);
void sx_spice_access_reg_pddr_list_free(void);
int sx_spice_access_reg_mgir_file_create(struct dentry *parent);
void sx_spice_access_reg_mgir_list_free(void);
int sx_spice_access_reg_ppcnt_file_create(struct dentry *parent);
void sx_spice_access_reg_ppcnt_list_free(void);
int sx_spice_access_reg_spzr_file_create(struct dentry *parent);
void sx_spice_access_reg_spzr_list_free(void);
int sx_spice_access_reg_mtcap_file_create(struct dentry *parent);
void sx_spice_access_reg_mtcap_list_free(void);
int sx_spice_access_reg_ptys_file_create(struct dentry *parent);
void sx_spice_access_reg_ptys_list_free(void);
int sx_spice_access_reg_mdir_file_create(struct dentry *parent);
void sx_spice_access_reg_mdir_list_free(void);
int sx_spice_access_reg_spad_file_create(struct dentry *parent);
void sx_spice_access_reg_spad_list_free(void);
int sx_spice_access_reg_msgi_file_create(struct dentry *parent);
void sx_spice_access_reg_msgi_list_free(void);

