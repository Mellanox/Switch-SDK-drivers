/*
 * Copyright (C) 2010-2023 NVIDIA CORPORATION & AFFILIATES, Ltd. ALL RIGHTS RESERVED.
 *
 * This software product is a proprietary product of NVIDIA CORPORATION & AFFILIATES, Ltd.
 * (the "Company") and all right, title, and interest in and to the software product,
 * including all associated intellectual property rights, are and shall
 * remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
 *
 */

#ifndef KERNEL_USER_H_
#define KERNEL_USER_H_

#ifdef __KERNEL__
#include <linux/uio.h>
#include <linux/version.h>
#if !defined(PAGE_SIZE)
#include <linux/vmalloc.h>
#endif /* PAGE_SIZE */
#else
#include <sys/uio.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>
#endif
#if !defined(__cplusplus)
#pragma GCC diagnostic ignored "-Wdeclaration-after-statement"
#endif
#pragma GCC diagnostic push
#if defined(__GNUC__) && __GNUC__ >= 7 && defined(__KERNEL__)
#define FALL_THROUGH __attribute__ ((__fallthrough__))
#else
#define FALL_THROUGH ((void)0)
#endif /* defined(__GNUC__) && __GNUC__ >= 7 && defined(__KERNEL__) */
#pragma GCC diagnostic pop
/************************************************
 *  Define
 ***********************************************/
#define     SXD_GENERATE_ENUM(ENUM, VAL, STR)   ENUM VAL, /* VAL is optional, should be =<number> */
#define     SXD_GENERATE_STRING(ENUM, VAL, STR) [ENUM] = STR,
#define     DBG_ALL_IRICS (255)

/* Based on tests on blackbird, FW crs_dump actually costs ~110us per 1KB on average, and the first several transactions may cost less time (60~80us/KB).
 *  Therefore we use 80us/KB as a base, together with mem-blk size, we can get the minimum sleeping time.
 *  We use 3 x minimum as a Layer1 timeout value. If it is expired, we will not wait any longer, and will return to user space caller to release the system
 *  call. User space caller can do other checks, before calling back to wait/check FW status again. */
#define  SX_CR_DUMP_FW_LEAST_US_PER_KB (80)
/* Based on tests on blackbird, GDB dump triggered by FW is 800us/KB */
#define  SX_GDB_DUMP_FW_LEAST_US_PER_KB (800)
#define  SX_SECURE_DUMP_MIN_WAIT_FW_DUMP_MS(blk_size, is_gdb_mode)               \
    (is_gdb_mode ? (((blk_size) / 1024) * SX_GDB_DUMP_FW_LEAST_US_PER_KB / 1000) \
                 : (((blk_size) / 1024) * SX_CR_DUMP_FW_LEAST_US_PER_KB / 1000))

#define  SX_SECURE_DUMP_MAX_WAIT_FW_DUMP_MS(blk_size, is_gdb_mode) \
    (SX_SECURE_DUMP_MIN_WAIT_FW_DUMP_MS(blk_size, is_gdb_mode) * 3)

#define SXD_STATEFUL_RAW_KEY_MAX  56  /*Key is 54B byte, add 2 B for alignment */
#define SXD_ACL_MAX_FIELDS_IN_KEY 48
#define SXD_HTACG_STATUS_DONE     2

/**
 * MPCIR enum is used for opcode in the MPCIR register parameters
 */
typedef enum sxd_mpcir_op {
    SXD_MPCIR_OP_NOP_E     = 0x0,
    SXD_MPCIR_OP_ENABLE_E  = 0x1,
    SXD_MPCIR_OP_DISABLE_E = 0x2,
    SXD_MPCIR_OP_STATUS_E  = 0x3,
} sxd_mpcir_op_t;

/**
 * DEFAULT_DEVICE_ID defines the default value for
 * device ID for local devices.
 */
#define DEFAULT_DEVICE_ID   255
#define LOCAL_DEVICE_ID_MIN 254
#define LOCAL_DEVICE_ID_MAX DEFAULT_DEVICE_ID
#define DEFAULT_DEVICE_ID_CHECK(dev_id) (dev_id >= LOCAL_DEVICE_ID_MIN)

#define REDECN_NUM_HW_PROFILES 3
/**
 * SWID_NUM_DONT_CARE define the don't care value for swids
 * when registering a listener.
 */
#define SWID_NUM_DONT_CARE 255

/* SWID_NUM_DONT_CARE defines the don't care value for target-process-id. */
#define TARGET_PID_DONT_CARE 0

/**
 * NUMBER_OF_SWIDS define the number of possible swids
 * in the system.
 */
#define NUMBER_OF_SWIDS 8
/**
 * Router Port Swid
 */
#define ROUTER_PORT_SWID 1
/**
 * NUMBER_OF_ETCLASSES define the number of possible etclasses
 * in the system.
 */
#define NUMBER_OF_ETCLASSES 17
/**
 * NUMBER_OF_STCLASSES define the number of possible stclasses
 * in the system.
 */
#define NUMBER_OF_STCLASSES 8
/**
 * NUMBER_OF_RDQS define the number of possible rdqs
 * in the system.
 */
#define NUMBER_OF_RDQS 57
/**
 * NUMBER_OF_SDQS define the number of possible sdqs
 * in the system.
 */
#define NUMBER_OF_SDQS 24

/**
 * RDQ_INVALID_ID define the invalid rdq number
 */
#define RDQ_INVALID_ID 0xFF

enum {
    SX_SEND_DQ_DB_BASE     = 0,
    SX_RECV_DQ_DB_BASE     = 0x200,
    SX_MAX_LOG_DQ_SIZE     = 10,
    SX_MAX_LOG_CQ_SIZE     = 10,
    SX_CQE_VER_OFFSET      = 4,
    SX_DBELL_CQ_CI_OFFSET  = 0x400,
    SX_DBELL_CQ_ARM_OFFSET = 0x800
};

/**
 * NUMBER_OF_SERDESS define the number of possible serdeses
 * in the system.
 */
#define NUMBER_OF_SERDESES 8
/**
 * SX_BOARD_ID_LEN define the length of the board id
 * string.
 */
#define SX_BOARD_ID_LEN 64
/**
 * SX_XM_MAX_LOCAL_PORTS_LEN define the length of XM local ports
 * array.
 */
#define SX_XM_MAX_LOCAL_PORTS_LEN 4

/**
 * SX_IB_NODE_DESCRIPTION_LEN define the length of the IB node description string
 */
#define SX_IB_NODE_DESCRIPTION_LEN 64

/**
 * ETHER_ADDR_LENGTH define the length of the ethernet
 * address in bytes
 */
#define ETHER_ADDR_LENGTH 6

/**
 * MTBR_MAX_TEMPERATURE_RECORDS define maximum temperature records supported by one MTBR
 * This number is limited by the max num of dwords supported on CMD IFC.
 * Fixed according to bug #903521
 */
#define MTBR_MAX_TEMPERATURE_RECORDS 47

#define NUM_SW_SYNDROMES 64
#define NUM_HW_SYNDROMES (1024 + NUM_SW_SYNDROMES)

#define NUM_OF_TRAP_GROUPS 34

/**
 * NUM_BINS_SBHBR define the amount of bins for SBHBR
 * */
#define NUM_BINS_SBHRR 10

/**
 * NUM_COUNTERS_SBDCC define the amount of counters for SBDCC
 * */
#define NUM_COUNTERS_SBDCC 64

/* NETLINK unit for EMAD dump */
#define NETLINK_EMAD_DUMP NETLINK_NFLOG

/**
 * SYND_NUM_DONT_CARE define the don't care value for synd
 * when registering a listener.
 */
#define SYND_NUM_DONT_CARE NUM_HW_SYNDROMES

/**
 * SXD_VENDOR_SN_LEN define the length of the vendor serial number
 * string.
 */
#define SXD_VENDOR_SN_LEN 4
/**
 * SXD_VENDOR_PN_LEN define the length of the vendor part number
 * string.
 */

#define SXD_VENDOR_PN_LEN 4
/**
 * SXD_VENDOR_NAME_LEN define the length of the vendor name
 * string.
 */

#define SXD_VENDOR_NAME_LEN 4


#define SXD_ACL_INFO_SIZE_BYTES               16
#define SXD_MAX_ACL_IN_GROUP                  16
#define SXD_PACL_TCAM_REGIONS                 4
#define SXD_TCAM_REGION_INFO_SIZE_BYTES       16
#define SXD_TCAM_REGOIN_ID_DUP                15
#define SXD_FLEXIBLE_KEY_ID_SIZE_BYTES        16
#define SXD_FLEXIBLE_KEY_BLOCK_REG_SIZE_BYTES 12
#define SXD_ACL_FLEX_KEY_BLOCK_SIZE_BYTES     96
#define SXD_ACL_BLOOM_FILTER_ENTRIES          256
#define SXD_ACL_NUM_OF_ACTION_SLOTS           5
#define SXD_ACL_NUM_OF_EXTRACTION_POINT       256

/**
 * MAX_TRANSACTIONS_NUM define the max number of mjtag register
 * transactions.
 */
#define MAX_TRANSACTIONS_NUM 40


/**
 * DSCP_CODES_NUMBER defines the DSCP codes number
 */
#define DSCP_CODES_NUMBER  64
#define EXP_CODES_NUMBER   8
#define ECN_CODES_NUMBER   4
#define COLOR_CODES_NUMBER 3

#define SX_IFNAMSIZ 16

/*
 * MAX num of records to retrieve from rauhtd
 * */
#define SXD_RAUHTD_MAX_REC_NUM 32

/*
 * MAX num of ports to set/retrieve from SFDT - 8 per line * 90 lines
 * */
#define SXD_SFDT_MAX_PORT_NUM 720
/*
 * MAX num of records to retrieve from ratrad
 * */
#define SXD_RATRAD_MAX_REC_NUM 4096

/*
 * Max dir length
 * */
#define SXD_DIR_NAME_MAX_LEN 128

/**
 * Shared buffers statistics and pools
 */
#define SXD_EMAD_SBSR_PORT_MASK_SIZE 8
#define SXD_EMAD_SBSR_TC_MASK_SIZE   2
#define SXD_EMAD_SBSR_MAX_RET_SIZE   120
#define SXD_EMAD_PBSR_BUFFER_NUM     10

/**
 * ACL key blocks
 */
#define SXD_ACL_KEY_BLOCK_NULL                   0x00
#define SXD_ACL_KEY_BLOCK_QOS                    0x01
#define SXD_ACL_KEY_BLOCK_L2_DMAC                0x10
#define SXD_ACL_KEY_BLOCK_L2_SMAC                0x11
#define SXD_ACL_KEY_BLOCK_L2_SMAC_EX             0x12
#define SXD_ACL_KEY_BLOCK_ETHERNET_ETH_PAYLOAD0  0x13
#define SXD_ACL_KEY_BLOCK_CUSTOM_ETH_PAYLOAD1    0x14
#define SXD_ACL_KEY_BLOCK_ETHERTYPE_ETH_PAYLOAD2 0x17
#define SXD_ACL_KEY_BLOCK_ETHERTYPE_ETH_PAYLOAD3 0x15
#define SXD_ACL_KEY_BLOCK_VID                    0x16
#define SXD_ACL_KEY_BLOCK_IPV4_SIP               0x30
#define SXD_ACL_KEY_BLOCK_IPV4_DIP               0x31
#define SXD_ACL_KEY_BLOCK_IPV4                   0x32
#define SXD_ACL_KEY_BLOCK_IPV4_EX                0x33
#define SXD_ACL_KEY_BLOCK_IPV4_5TUPLE            0x34
#define SXD_ACL_KEY_BLOCK_IPV4_12TUPLE           0x35
#define SXD_ACL_KEY_BLOCK_IPV4_12TUPLE_EX        0x36
#define SXD_ACL_KEY_BLOCK_IPV4_CUSTOM            0x37
#define SXD_ACL_KEY_BLOCK_IPV4_CUSTOM_EX         0x38
#define SXD_ACL_KEY_BLOCK_INNER_IPV4_DIP         0x39
#define SXD_ACL_KEY_BLOCK_INNER_IPV4_5TUPLE      0x3A
#define SXD_ACL_KEY_BLOCK_INNER_IPV4_12TUPLE     0x3B
#define SXD_ACL_KEY_BLOCK_INNER_IPV4_12TUPLE_EX  0x3C
#define SXD_ACL_KEY_BLOCK_RPF                    0x3D
#define SXD_ACL_KEY_BLOCK_ROCE                   0x40
#define SXD_ACL_KEY_BLOCK_ROCE_EX                0x41
#define SXD_ACL_KEY_BLOCK_IPV6_DIP               0x60
#define SXD_ACL_KEY_BLOCK_IPV6_DIP_EX            0x61
#define SXD_ACL_KEY_BLOCK_IPV6_SIP               0x62
#define SXD_ACL_KEY_BLOCK_IPV6_SIP_EX            0x63
#define SXD_ACL_KEY_BLOCK_IPV6                   0x64
#define SXD_ACL_KEY_BLOCK_IPV6_EX1               0x65
#define SXD_ACL_KEY_BLOCK_IPV6_EX2               0x66
#define SXD_ACL_KEY_BLOCK_IPV6_EX3               0x67
#define SXD_ACL_KEY_BLOCK_IPV6_EX4               0x68
#define SXD_ACL_KEY_BLOCK_INNER_IPV6             0x69
#define SXD_ACL_KEY_BLOCK_INNER_IPV6_EX1         0x70
#define SXD_ACL_KEY_BLOCK_INNER_IPV6_EX2         0x71
#define SXD_ACL_KEY_BLOCK_INNER_IPV6_EX3         0x72
#define SXD_ACL_KEY_BLOCK_TUNNEL                 0x80
#define SXD_ACL_KEY_BLOCK_IPSEC                  0x81
#define SXD_ACL_KEY_BLOCK_MPLS                   0x90
#define SXD_ACL_KEY_BLOCK_MPLS_EX                0x91
#define SXD_ACL_KEY_BLOCK_FIBER_CHANNEL          0xA0
#define SXD_ACL_KEY_BLOCK_FIBER_CHANNEL_EX       0xA1
#define SXD_ACL_KEY_BLOCK_LOADBALANCING          0xA2
#define SXD_ACL_KEY_BLOCK_LOADBALANCING_EX       0xA3
#define SXD_ACL_KEY_BLOCK_PACKETTYPE             0xB0
#define SXD_ACL_KEY_BLOCK_RX_LIST                0xB1

#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_0             0x10
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_1             0x11
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_2             0x12
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_3             0x13
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_4             0x14
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_5             0x15
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_5B            0x1A
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_6             0x16
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_6B            0x1B
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_7             0x17
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_8             0x18
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_8B            0x1C
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_9             0x19
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_0       0x20
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_1       0x21
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_2       0x22
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_3       0x23
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_4       0x24
#define SXD_ACL_KEY_BLOCK_IPV4_EX2                0x2C
#define SXD_ACL_KEY_BLOCK_IPV4_EX3                0x2D
#define SXD_ACL_KEY_BLOCK_FLEX2_IP_0              0x30
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_0            0x38
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_0_SYMM       0x38
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_1            0x39
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_1B           0x3F
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_1B_SYMM      0x3F
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_1_OPT        0x3E
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_2            0x3A
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_3            0x3B
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_4            0x3C
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_4B           0x35
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_5            0x3D
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_5B           0x36
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_6B           0x37
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_0            0x40
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_1            0x41
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_2            0x42
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_2B           0x47
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_3            0x43
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_4            0x44
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_5            0x45
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_6            0x46
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_0_SYMM       0x40
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_1_SYMM       0x41
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_2_SYMM       0x42
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_2B_SYMM      0x47
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_3_SYMM       0x43
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_4_SYMM       0x44
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_5_SYMM       0x45
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_6_SYMM       0x46
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_0      0x50
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_1      0x51
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_2      0x52
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_0      0x58
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_1      0x59
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_2      0x5A
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_3      0x5B
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_4      0x5C
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_5      0x5D
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_6      0x5E
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_0_SYMM 0x50
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_1_SYMM 0x51
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_2_SYMM 0x52
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_0_SYMM 0x58
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_1_SYMM 0x59
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_2_SYMM 0x5A
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_3_SYMM 0x5B
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_4_SYMM 0x5C
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_5_SYMM 0x5D
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_6_SYMM 0x5E

#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_0       0x60
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_1       0x61
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_1B      0x67
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_2       0x62
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_2B      0x6C
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_3       0x63
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_3B      0x6D
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_4       0x64
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_5       0x65
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_6       0x66
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MPLS_0 0x68
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MPLS_1 0x69
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MPLS_2 0x6A
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MPLS_3 0x6B
#define SXD_ACL_KEY_BLOCK_FLEX2_IB_0         0x70
#define SXD_ACL_KEY_BLOCK_FLEX2_IB_1         0x71
#define SXD_ACL_KEY_BLOCK_FLEX2_L3_0         0x80
#define SXD_ACL_KEY_BLOCK_FLEX2_L3_1         0x81
#define SXD_ACL_KEY_BLOCK_FLEX2_L3_2         0x82
#define SXD_ACL_KEY_BLOCK_FLEX2_L3_3         0x83
#define SXD_ACL_KEY_BLOCK_FLEX2_L3_4         0x84
#define SXD_ACL_KEY_BLOCK_FLEX2_L3_5         0x85
#define SXD_ACL_KEY_BLOCK_FLEX2_L4_0         0x90
#define SXD_ACL_KEY_BLOCK_FLEX2_L4_0_OPT     0x95
#define SXD_ACL_KEY_BLOCK_FLEX2_L4_0_SWAP    0x96
#define SXD_ACL_KEY_BLOCK_FLEX2_L4_1         0x91
#define SXD_ACL_KEY_BLOCK_FLEX2_L4_2         0x92
#define SXD_ACL_KEY_BLOCK_FLEX2_L4_3         0x93
#define SXD_ACL_KEY_BLOCK_FLEX2_IP_L4_0      0x94
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_L4_0   0x98
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_L4_1   0x99
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_L4_2   0x9A
#define SXD_ACL_KEY_BLOCK_FLEX2_TUNNELS_0    0xA0
#define SXD_ACL_KEY_BLOCK_FLEX2_TUNNELS_1    0xA1
#define SXD_ACL_KEY_BLOCK_FLEX2_TUNNELS_2    0xA2
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_0       0xB0
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_1       0xB1
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_2       0xB2
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_2B      0xB5
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_3       0xB3
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_4       0xB4
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_4B      0xB6
#define SXD_ACL_KEY_BLOCK_FLEX2_STATEFUL_0   0xB8
#define SXD_ACL_KEY_BLOCK_FLEX2_STATEFUL_0B  0xB9
#define SXD_ACL_KEY_BLOCK_FLEX2_STATEFUL_1B  0xBA
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_0  0xC0
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_1  0xC1
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_2  0xC2
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_3  0xC3
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_4  0xC4
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_5  0xC5
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_6  0xC6
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_7  0xC7
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_8  0xC8
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_9  0xC9
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_10 0xCA
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_11 0xCB
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_12 0xCC
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_13 0xCD
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_14 0xCE
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_15 0xCF
#define SXD_ACL_KEY_BLOCK_FLEX2_QOS_0        0xD0
#define SXD_ACL_KEY_BLOCK_FLEX2_QOS_1        0xD1
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_0     0xE0
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_1     0xE1
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_2     0xE2
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_3     0xE3
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_4     0xE4
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_5     0xE5
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_6     0xE6

#define SXD_ACL_KEY_BLOCK_MACSEC_MAC_0       0x10
#define SXD_ACL_KEY_BLOCK_MACSEC_MAC_1       0x11
#define SXD_ACL_KEY_BLOCK_MACSEC_MAC_2       0x12
#define SXD_ACL_KEY_BLOCK_MACSEC_MAC_3       0x13
#define SXD_ACL_KEY_BLOCK_MACSEC_ETHERTYPE_0 0x14
#define SXD_ACL_KEY_BLOCK_MACSEC_VLAN_0      0x15
#define SXD_ACL_KEY_BLOCK_MACSEC_TUNNELS_0   0x60
#define SXD_ACL_KEY_BLOCK_MACSEC_MACSEC_0    0x80
#define SXD_ACL_KEY_BLOCK_MACSEC_MACSEC_1    0x81
#define SXD_ACL_KEY_BLOCK_MACSEC_MACSEC_2    0x82
#define SXD_ACL_KEY_BLOCK_MACSEC_MACSEC_3    0x83
#define SXD_ACL_KEY_BLOCK_MACSEC_MACSEC_4    0x84

typedef  union utce_action utce_action_t;

/**
 * MTUTC register operation
 */
#define SXD_MTUTC_OP_SET_TIME_NEXT_SEC  0x00
#define SXD_MTUTC_OP_SET_TIME_IMMEDIATE 0x01
#define SXD_MTUTC_OP_ADJUST_TIME        0x02
#define SXD_MTUTC_OP_ADJUST_FREQ        0x03

/**
 * SX_DBG_DUMP_PROC_DIR defines the directory for driver debug proc files
 */
#define SX_DBG_DUMP_PROC_DIR         "dbg_dump"
#define DEVICE_ID_STRING_MAX_LEN     16
#define DBG_PROC_FOLDER_MAX_NAME_LEN (DEVICE_ID_STRING_MAX_LEN + 32)

#define SXD_RMFTAD_ACTIVITIES_VECTOR_SIZE 128
#define SXD_PTCEAD_ACTIVITIES_VECTOR_SIZE 128

#define MAX_NUM_OF_REMOTE_SWITCHES 256
#define DEV_ID_IS_VALID(dev_id) ((dev_id) > 0 && ((int)(dev_id)) < MAX_NUM_OF_REMOTE_SWITCHES)

#define MAX_SYSTEM_PORTS_IN_FILTER 256
#define MAX_LAG_PORTS_IN_FILTER    256
#define MAX_SYSPORT_NUM            65536
#define MAX_PHYPORT_NUM            258
#define MAX_LAG_NUM                256
#define MAX_LAG_MEMBERS_NUM        128
#define SXD_MAX_VLAN_NUM           4096
#define MAX_PRIO_NUM               15
#define MAX_IBPORT_NUM             MAX_PHYPORT_NUM
#define MAX_NUM_TRAPS_TO_REGISTER  256

#define INVALID_LOCAL_PORT  0xFFFF
#define INVALID_HW_FID_ID   0xFFFF
#define MAX_FIDS_NUM        0x5000 /* 20K (CAP_FID+VLANs) ==> it is the maximum allowed among all
                                   *  spectrum devices but not on the specific spectrum device.
                                   *  the actual chip-specific value is fid_manager_g.max_fid. */
#define MAX_RIFS_NUM        8000
#define MAX_MONITOR_RDQ_NUM 5

#define KU_CAP_MAX_MTU_SPECTRUM  (10240)
#define KU_CAP_MAX_MTU_SWITCH_IB (4222)

#define SXD_BULK_CNTR_SB_TYPE_INVALID (0xFF)
#define SXD_BULK_CNTR_POOL_ID_INVALID (0xFFFFFFFF)

#define SXD_BULK_CNTR_PORT_NUM                 (MAX_PHYPORT_NUM)
#define SXD_BULK_CNTR_PHY_PORT_MIN             (1)
#define SXD_BULK_CNTR_PG_NUM                   (10)
#define SXD_BULK_CNTR_TC_NUM                   (17)
#define SXD_BULK_CNTR_POOL_NUM                 (16)
#define SXD_BULK_CNTR_SP_NUM                   (16)
#define SXD_BULK_CNTR_CPU_TC_NUM               (32)
#define SXD_BULK_CNTR_SHARED_HEADROOM_POOL_NUM (1)
#define SXD_BULK_CNTR_LOCAL_PORT_MASK_BIT_POSITTION(local_port) (local_port - 1)
#define SXD_BULK_CNTR_LOCAL_PORT_VALID(local_port) \
    SX_CHECK_RANGE(SXD_BULK_CNTR_PHY_PORT_MIN,     \
                   local_port,                     \
                   SXD_BULK_CNTR_PORT_NUM)

#define SXD_BULK_CNTR_TOTAL_POOL_MAX_NUM (SXD_BULK_CNTR_POOL_NUM * 4 + SXD_BULK_CNTR_SHARED_HEADROOM_POOL_NUM)

#define SXD_BULK_CNTR_PORT_MASK_NUM ((SXD_BULK_CNTR_PORT_NUM / 32) + 1)

#define SXD_CR_DUMP_HOST_MEM_ALIGN (4 * 1024)

/**
 * Elephant detection
 */
#define SXD_COS_ELEPHANT_FLOW_ID_NUM_MAX     (128)
#define SXD_COS_ELEPHANT_MPLS_LABELS_MAX_CNT (5)
#define SXD_COS_ELEPHANT_PORT_NUM_MAX        MAX_PHYPORT_NUM
#define SXD_COS_ELEPHANT_PORT_MASK_NUM       ((SXD_COS_ELEPHANT_PORT_NUM_MAX / 32) + 1)

/**
 * Builds physical port id from lsb and msb parts
 * To be used to handle the registers fields 'local_port' and 'lp_msb'
 */
#define SX_PORT_BUILD_PHY_ID_FROM_LSB_MSB(phy_id, lsb, msb) \
    (phy_id) = ((lsb) & 0xFF);                              \
    (phy_id) |= (((msb) & 0x3) << 8)

/**
 * Extracts lsb and msb parts from physical port id
 * To be used to handle the registers fields 'local_port' and 'lp_msb'
 */
#define SX_PORT_EXTRACT_LSB_MSB_FROM_PHY_ID(lsb, msb, phy_id) \
    (lsb) = ((phy_id) & 0x0FF);                               \
    (msb) = (((phy_id) & 0x300) >> 8)

/************************************************
 *  Enum
 ***********************************************/

/* sx_core netlink multicast groups */
enum sx_core_nl_groups {
    SX_NL_GRP_NONE,
    SX_NL_GRP_EMAD_DUMP,

    __SX_NL_GRP_MAX,
    SX_NL_GRP_MAX = (__SX_NL_GRP_MAX - 1)
};

struct sx_emad_dump_nl_msghdr {
    uint32_t devindex;
    uint32_t reserved;
};

/**
 * ku_pkt_type enumerated type is used to note the possible
 * packet types.
 */
enum ku_pkt_type {
    SX_PKT_TYPE_ETH_CTL_UC, /**< Eth control unicast */
    SX_PKT_TYPE_ETH_CTL_MC, /**< Eth control multicast */
    SX_PKT_TYPE_ETH_DATA, /**< Eth data */
    SX_PKT_TYPE_DROUTE_EMAD_CTL, /**< Directed route emad */
    SX_PKT_TYPE_EMAD_CTL, /**< Emad */
    SX_PKT_TYPE_FC_CTL_UC, /**< FC control unicast */
    SX_PKT_TYPE_FC_CTL_MC, /**< FC control multicast */
    SX_PKT_TYPE_FCOE_CTL_UC, /**< FC over Eth control unicast */
    SX_PKT_TYPE_FCOE_CTL_MC, /**< FC over Eth control multicast */
    SX_PKT_TYPE_IB_RAW_CTL, /**< IB raw control */
    SX_PKT_TYPE_IB_TRANSPORT_CTL, /**< IB transport control */
    SX_PKT_TYPE_IB_RAW_DATA, /**< IB raw data */
    SX_PKT_TYPE_IB_TRANSPORT_DATA, /**< IB transport data */
    SX_PKT_TYPE_EOIB_CTL, /**< Eth over IB control */
    SX_PKT_TYPE_FCOIB_CTL, /**< FC over IB control */
    SX_PKT_TYPE_LOOPBACK_CTL, /**< Loopback control */
    SX_PKT_TYPE_IB_CTL_2, /**< IBGen2 control */
    SX_PKT_TYPE_IB_NVLINK, /**< IB NVLink packet */
    SX_PKT_TYPE_MIN = SX_PKT_TYPE_ETH_CTL_UC, /**< Minimum enum value */
    SX_PKT_TYPE_MAX = SX_PKT_TYPE_IB_NVLINK /**< Maximum enum value */
};

/**
 * ku_ctrl_cmd enumerated type is used to note the possible
 * ioctl control commands.
 */
enum ku_ctrl_cmd {
    CTRL_CMD_GET_CAPABILITIES, /**< Get system capabilities */
    CTRL_CMD_SET_PCI_PROFILE, /**< Set the PCI profile */
    CTRL_CMD_INVALID, /**< Invalid */
    CTRL_CMD_GET_DEVICE_PROFILE, /**< Get the device profile */
    CTRL_CMD_ADD_SYND, /**< Add a new syndrome */
    CTRL_CMD_REMOVE_SYND, /**< Remove an existing syndrome */
    CTRL_CMD_MONITOR_SW_QUEUE_SYND, /**< Add/Remove listener for monitor trap group syndrome */
    CTRL_CMD_MULTI_PACKET_ENABLE, /**< Enable multi packets read operation */
    CTRL_CMD_BLOCKING_ENABLE, /**< Enable blocking read operation */
    CTRL_CMD_PCI_REGISTER_DRIVER,
    CTRL_CMD_RESET, /**< System reset */
    CTRL_CMD_PCI_DEVICE_RESTART, /**< PCI device restart */
    CTRL_CMD_RAISE_EVENT, /**< Raise an event */
    CTRL_CMD_ENABLE_SWID, /**< Enable a swid */
    CTRL_CMD_DISABLE_SWID, /**< Disable a swid */

    /* looks like CTRL_CMD_GET_SYNDROME_STATUS is not used anywhere but
     * we keep its enumeration not to break binary compatibility  */
    CTRL_CMD_GET_SYNDROME_STATUS, /**< Get syndrome statue */

    CTRL_CMD_QUERY_FW, /**< Run query FW command */
    CTRL_CMD_MAD_DEMUX, /**< MAD Demux command */
    CTRL_CMD_QUERY_RSRC, /**< Run query FW command */
    CTRL_CMD_QUERY_BOARD_INFO, /**< Run query board info command */
    CTRL_CMD_SET_SYSTEM_MKEY, /**< Set system mkey */
    CTRL_CMD_GET_SYSTEM_MKEY, /**< Get system mkey */
    CTRL_CMD_ISSU_FW, /**< Perform ISSU FW */
    CTRL_CMD_ADD_DEV_PATH, /**< Add a device path to the DPT */
    CTRL_CMD_REMOVE_DEV_PATH, /**< Remove a device path from the DPT */
    CTRL_CMD_REMOVE_DEV, /**< Remove a device from the DPT */
    CTRL_CMD_SET_CMD_PATH, /**< Set a device's command path in the DPT */
    CTRL_CMD_SET_EMAD_PATH, /**< Set a device's emad path in the DPT */
    CTRL_CMD_SET_MAD_PATH, /**< Set a device's mad path in the DPT */
    CTRL_CMD_SET_CR_ACCESS_PATH, /**< Set a device's CR access path in the DPT */
    CTRL_CMD_GET_PCI_PROFILE, /**< Get the PCI profile */
    CTRL_CMD_GET_SWID_2_RDQ, /**< Get swid to RDQ mapping */
    CTRL_CMD_SET_DEFAULT_VID, /**< Update default vid of a port or lag */
    CTRL_CMD_SET_VID_MEMBERSHIP, /**< Update vid membership of a port or lag */
    CTRL_CMD_SET_PRIO_TAGGING, /**< Update prio tagging mode of a port or lag */
    CTRL_CMD_SET_PRIO_TO_TC, /**< Update prio tagging mode of a port or lag */
    CTRL_CMD_SET_DEVICE_PROFILE, /**< Set the device profile */
    CTRL_CMD_SET_RDQ_RATE_LIMITER, /**< Set a rate limiter on one of the RDQs */
    CTRL_CMD_SET_RDQ_TIMESTAMP_STATE, /**< enable/disable time stamp on one of the RDQs */
    CTRL_CMD_SET_RDQ_CPU_PRIORITY, /**< set RDQ CPU priority */
    CTRL_CMD_SET_TRUNCATE_PARAMS, /**< Enable/Disable truncate on one of the RDQs */
    CTRL_CMD_CR_SPACE_READ, /**< Read a buffer from CR space */
    CTRL_CMD_CR_SPACE_WRITE, /**< Write a buffer to CR space */
    CTRL_CMD_CR_DUMP, /**< trigger FW to dump CR space */
    CTRL_CMD_SET_LOCAL_PORT_TO_SWID, /**< Set local port to swid db */
    CTRL_CMD_SET_IB_TO_LOCAL_PORT, /**< Set local port to swid db */
    CTRL_CMD_SET_SYSTEM_TO_LOCAL_PORT, /**< Set local port to swid db */
    CTRL_CMD_SET_PORT_RP_MODE,
    CTRL_CMD_SET_LOCAL_PORT_TO_LAG, /**< Set local port to swid db */
    CTRL_CMD_LAG_OPER_STATE_SET, /**< Set lag operating state db */
    CTRL_CMD_PORT_BER_MONITOR_STATE_SET, /**< Set port ber monitor operational state in db */
    CTRL_CMD_PORT_BER_MONITOR_BITMASK_SET, /**< Set port ber monitor configuration in db */
    CTRL_CMD_TELE_THRESHOLD_SET, /**< Set telemetry threshold configuration in db */
    CTRL_CMD_TRAP_FILTER_ADD, /**< Add a port or a LAG to a trap filter */
    CTRL_CMD_TRAP_FILTER_REMOVE, /**< Remove a port or a LAG from a trap filter */
    CTRL_CMD_TRAP_FILTER_REMOVE_ALL, /**< Remove all ports and LAGs from a trap filter */
    CTRL_CMD_SET_VID_2_IP, /**< Update vid membership of a port or lag */
    CTRL_CMD_SET_PORT_VID_TO_FID_MAP,
    CTRL_CMD_SET_SGMII_SYSTEM_CFG,
    CTRL_CMD_INIT_SGMII_DEV,
    CTRL_CMD_SET_SGMII_DEFAULT_DEV,
    CTRL_CMD_SET_SGMII_MFT_INFO,
    CTRL_CMD_GET_COUNTERS,
    CTRL_CMD_SET_PTP_MODE,
    CTRL_CMD_SET_MONITOR_RDQ, /**< Enable/Disable monitor mode of the RDQs */
    CTRL_CMD_READ_MULTI, /**< Read monitor RDQs data */
    CTRL_CMD_GET_RDQ_STAT,  /**< Read monitor RDQ statistics */
    CTRL_CMD_SET_SKB_OFFLOAD_FWD_MARK_EN,   /**< Enable/disable setting the offload_fwd_mark bit of SKB */
    CTRL_CMD_SAVE_SX_CORE_DB,
    CTRL_CMD_RESTORE_SX_CORE_DB,
    CTRL_CMD_GET_SX_CORE_DB_RESTORE_ALLOWED,
    CTRL_CMD_SET_FID_TO_HWFID_MAP,          /**< Update FID to HW_FID map */
    CTRL_CMD_SET_PCI_PROFILE_DRIVER_ONLY, /**< Set the PCI profile driver only */
    CTRL_CMD_FLUSH_EVLIST, /**< Flush the evlist associated with a file descriptor */
    CTRL_CMD_SET_SW_IB_NODE_DESC, /**< set SW IB node description */
    CTRL_CMD_SET_RDQ_FILTER_EBPF_PROG, /**< Attach/detach the filter eBPF program to/from an RDQ */
    CTRL_CMD_SET_RDQ_AGG_EBPF_PROG, /**< Attach/detach the aggregation eBPF program to/from an RDQ */
    CTRL_CMD_PSAMPLE_PORT_SAMPLE_RATE_UPDATE, /**< update psample-port-sample-rate info to sx-netdev module */
    CTRL_CMD_SET_SW_IB_SWID_UP_DOWN, /**< IB swid went up or down */
    CTRL_CMD_SET_WARM_BOOT_MODE, /**< set sdk boot mode : normal, issu , ... */
    CTRL_CMD_SET_FD_ATTRIBUTES, /**< set FD attributes: head drop, tail drop */
    CTRL_CMD_GET_FD_ATTRIBUTES, /**< set FD attributes: head drop, tail drop */
    CTRL_CMD_BULK_CNTR_TR_ADD, /**< add bulk-counter transaction */
    CTRL_CMD_BULK_CNTR_TR_DEL, /**< delete bulk-counter transaction */
    CTRL_CMD_BULK_CNTR_TR_CANCEL, /**< cancel bulk-counter transaction */
    CTRL_CMD_BULK_CNTR_TR_ACK, /**< SDK acknowledgement to complete a transaction */
    CTRL_CMD_BULK_CNTR_TR_CONTINUE_ACK, /**< SDK acknowledgement for partial-complete transaction */
    CTRL_CMD_BULK_CNTR_TR_IN_PROGRESS, /**< get bulk-counter transaction in progress status */
    CTRL_CMD_BULK_CNTR_PER_PRIO_CACHE_SET, /**< Notify driver about the shared memory used by per prio counter cache */
    CTRL_CMD_BULK_STATEFUL_DB_KEYS_WRITE,  /**< Write translated acl keys to shared memory */
    CTRL_CMD_BUFFER_DROP_PARAMS, /**< Set the WJH buffer drop parameters */
    CTRL_CMD_CLIENT_PID_GET, /**< Get client's process ID */
    CTRL_CMD_SDK_HEALTH_SET, /**< Enable/disable sdk health event */
    CTRL_CMD_SDK_HEALTH_GET, /**< Get sdk health event enablement status */
    CTRL_CMD_SEND_ISSU_NOTIFICATION, /**< send notification to HW-Mng that FW is accessible/inaccessible */
    CTRL_CMD_FW_MEMORY_TO_CPU_MAP, /**< Map CPU memory to FW (used for port profiles) */
    CTRL_CMD_SET_KVH_CACHE_PARAMS, /**< set KVH cache configuration parameters */
    CTRL_CMD_GET_KVH_CACHE_PARAMS, /**< get KVH cache configuration parameters */
    CTRL_CMD_ACCUFLOW_COUNTERS_SET,
    CTRL_CMD_SEND_FATAL_FAILURE_DETECT_INFO_SET,/**< Set health check sample params and update trap_groups status */
    CTRL_CMD_PORT_MODULE_UPDATE,
    CTRL_CMD_PORT_MODULE_MAP_SET,
    CTRL_CMD_GET_DEV_INFO,
    CTRL_CMD_SET_DEV_INFO,
    CTRL_CMD_REARM_MODULE_EVENT,
    CTRL_CMD_READ_HOST_MEM_PAGE,  /**< Read a page from host memory*/
    CTRL_CMD_CR_DUMP_NOTIFY_DUMP_COMPLETE,
    CTRL_CMD_MIN_VAL = CTRL_CMD_GET_CAPABILITIES, /**< Minimum enum value */
    CTRL_CMD_MAX_VAL = CTRL_CMD_CR_DUMP_NOTIFY_DUMP_COMPLETE, /**< Maximum enum value */
#ifdef SW_PUDE_EMULATION /* PUDE WA for NOS (PUDE events are handled by SDK). Needed for BU. */
    CTRL_CMD_SET_PORT_ADMIN_STATUS, /**< Update port admin status */
#endif /* SW_PUDE_EMULATION */
};

/**
 * ku_ctrl_cmd_access_reg enumerated type is used to note the
 * possible ioctl control commands and to differ between access
 * register control commands and other commands .
 */
enum ku_ctrl_cmd_access_reg {
    CTRL_CMD_ACCESS_REG_PSPA = CTRL_CMD_MAX_VAL + 1,  /**< Run access register PSPA command */
/* Please, do not move this include.
 *  It includes auto generated code which adds new cases to this enum statement. */
#ifdef __KERNEL__
#include <linux/mlx_sx/auto_registers/kernel_cmd_access_auto.h>
#else
#include "auto_registers/kernel_cmd_access_auto.h"
#endif

    CTRL_CMD_ACCESS_REG_PMLP, /**< Run access register PMLP command */
    CTRL_CMD_ACCESS_REG_PLIB, /**< Run access register PLIB command */
    CTRL_CMD_ACCESS_REG_PPLM, /**< Run access register PPLM command */
    CTRL_CMD_ACCESS_REG_PLPC, /**< Run access register PLPC command */
    CTRL_CMD_ACCESS_REG_PMPC, /**< Run access register PMPC command */
    CTRL_CMD_ACCESS_REG_PMPR, /**< Run access register PMPR command */
    CTRL_CMD_ACCESS_REG_PELC, /**< Run access register PELC command */
    CTRL_CMD_ACCESS_REG_PFCA, /**< Run access register PFCA command */
    CTRL_CMD_ACCESS_REG_PFCNT, /**< Run access register PFCNT command */
    CTRL_CMD_ACCESS_REG_PFSC, /**< Run access register PFSC command */
    CTRL_CMD_ACCESS_REG_HTGT, /**< Run access register HTGT command */
    CTRL_CMD_ACCESS_REG_MFSC, /**< Run access register MFSC command */
    CTRL_CMD_ACCESS_REG_MFSM, /**< Run access register MFSM command */
    CTRL_CMD_ACCESS_REG_MFSL, /**< Run access register MFSL command */
    CTRL_CMD_ACCESS_REG_MJTAG, /**< Run access register MJTAG command */
    CTRL_CMD_ACCESS_REG_PPSC, /**< Run access register PPSC command */
    CTRL_CMD_ACCESS_REG_PVLC, /**< Run access register PVLC command */
    CTRL_CMD_ACCESS_REG_MCIA, /**< Run access register MCIA command */
    CTRL_CMD_ACCESS_REG_HPKT, /**< Run access register HPKT command */
    CTRL_CMD_ACCESS_REG_HCAP, /**< Run access register HCAP command */
    CTRL_CMD_ACCESS_REG_HDRT, /**< Run access register HDRT command */
    CTRL_CMD_ACCESS_REG_HCTR, /**< Run access register HCTR command */
    CTRL_CMD_ACCESS_REG_MFCR, /**< Run access register MFCR command */
    CTRL_CMD_ACCESS_REG_FORE, /**< Run access register FORE command */
    CTRL_CMD_ACCESS_REG_MTBR, /**< Run access register MTBR command */
    CTRL_CMD_ACCESS_REG_MMDIO, /**< Run access register MMDIO command */
    CTRL_CMD_ACCESS_REG_MMIA, /**< Run access register MMIA command */
    CTRL_CMD_ACCESS_REG_MFPA, /**< Run access register MFPA command */
    CTRL_CMD_ACCESS_REG_MFBE, /**< Run access register MFBE command */
    CTRL_CMD_ACCESS_REG_MFBA, /**< Run access register MFBA command */
    CTRL_CMD_ACCESS_REG_RAW, /**< Run access register command for a RAW register */
    CTRL_CMD_ACCESS_REG_RAW_BUFF, /**< Run access register command with a RAW buffer */
    CTRL_CMD_ACCESS_REG_MFM, /**< Run access register MFM command */
    CTRL_CMD_ACCESS_REG_SSPR, /**< Run access register SSPR command */
    CTRL_CMD_ACCESS_REG_SLCR_V2, /**< Run access register SLCR_V2 command */
    CTRL_CMD_ACCESS_REG_SPMCR, /**< Run access register SPMCR command */
    CTRL_CMD_ACCESS_REG_SMID, /**< Run access register SMID command */
    CTRL_CMD_ACCESS_REG_SPMS, /**< Run access register SPMS command */
    CTRL_CMD_ACCESS_REG_SPVC, /**< Run access register SPVC command */
    CTRL_CMD_ACCESS_REG_SVER, /**< Run access register SVER command */
    CTRL_CMD_ACCESS_REG_QPBR, /**< Run access register QPBR command */
    CTRL_CMD_ACCESS_REG_PLBF, /**< Run access register PLBF command */
    CTRL_CMD_ACCESS_REG_MHSR, /**< Run access register MHSR command */
    CTRL_CMD_ACCESS_REG_MSCI, /**< Run access register MSCI command */
    CTRL_CMD_ACCESS_REG_MRSR, /**< Run access register MRSR command */
    CTRL_CMD_ACCESS_REG_SBPM, /**< Run access register SBPM command */
    CTRL_CMD_ACCESS_REG_SBMM, /**< Run access register SBMM command */
    CTRL_CMD_ACCESS_REG_CWTP, /**< Run access register CWTP command */
    CTRL_CMD_ACCESS_REG_CWPP, /**< Run access register CWPP command */
    CTRL_CMD_ACCESS_REG_CWPPM, /**< Run access register CWPPM command */
    CTRL_CMD_ACCESS_REG_MPSC, /**< Run access register MPSC command */
    CTRL_CMD_ACCESS_REG_MLCR, /**< Run access register MLCR command */
    CTRL_CMD_ACCESS_REG_MPGCR, /**< Run access register MPGCR command */
    CTRL_CMD_ACCESS_REG_MPILM, /**< Run access register MPILM command */
    CTRL_CMD_ACCESS_REG_MRRR, /**< Run access register MRRR command */
    CTRL_CMD_ACCESS_REG_MDRI, /**< Run access register MDRI command */
    CTRL_CMD_ACCESS_REG_HTAC, /**< Run access register HTAC command */
    CTRL_CMD_ACCESS_REG_SBHBR, /**< Run access register SBHBR command */
    CTRL_CMD_ACCESS_REG_SBHRR, /**< Run access register SBHRR command */
    CTRL_CMD_ACCESS_REG_SBDCC, /**< Run access register SBDCC command */
    CTRL_CMD_ACCESS_REG_SBDCM, /**< Run access register SBDCM command */
    CTRL_CMD_ACCESS_REG_SBCTC, /**< Run access register SBCTC command */
    CTRL_CMD_ACCESS_REG_PPBMI, /**< Run access register PPBMI command */
    CTRL_CMD_ACCESS_REG_RGCR, /**< RGCR - tmp patch since FW needs it in Baz IB Router*/
    CTRL_CMD_ACCESS_REG_RTCA, /**< RTCA - for IB Router*/
    CTRL_CMD_ACCESS_REG_RTPS, /**< RTPS - for IB Router*/
    CTRL_CMD_ACCESS_REG_RUFT, /**< RUFT - for IB Router*/
    CTRL_CMD_ACCESS_REG_PPAOS, /**< Run access register PPAOS command */
    CTRL_CMD_ACCESS_REG_PCMR, /**< Run access register PCMR command */
    CTRL_CMD_ACCESS_REG_PCNR, /**< Run access register PCNR command */
    CTRL_CMD_ACCESS_REG_PPBMP, /**< Run access register PPBMP command */
    CTRL_CMD_ACCESS_REG_PPBMC, /**< Run access register PPBMC command */
    CTRL_CMD_ACCESS_REG_PPBME, /**< Run access register PPBME command */
    CTRL_CMD_ACCESS_REG_PTCE3, /**< Run access register PTCE_V3 command */
    CTRL_CMD_ACCESS_REG_PERPT, /**< Run access register PERPT command */
    CTRL_CMD_ACCESS_REG_PERCR, /**< Run access register PERCR command */
    CTRL_CMD_ACCESS_REG_PERERP, /**< Run access register PERCR command */
    CTRL_CMD_ACCESS_REG_PEABFE, /**< Run access register PEABFE command */
    CTRL_CMD_ACCESS_REG_QHLL, /**< Run access register QHLL command */
    CTRL_CMD_ACCESS_REG_MTPPTR, /**< Run access register MTPPTR command */
    CTRL_CMD_ACCESS_REG_QPSC, /**< Run access register QPSC command */
    CTRL_CMD_ACCESS_REG_MTPPPC, /**< Run access register MTPPPC command */
    CTRL_CMD_ACCESS_REG_QPCR, /**< Run access register QPCR command */
    CTRL_CMD_ACCESS_REG_IBSNI, /**< Run access register IBSNI command */
    CTRL_CMD_ACCESS_REG_SLCR,  /**< Run access register SLCR command */
    CTRL_CMD_ACCESS_REG_SFN, /**< Run access register SFN command */
    CTRL_CMD_ACCESS_REG_SPVTR,  /**< Run access register SPVTR command */
    CTRL_CMD_ACCESS_REG_QPEM, /**< Run access register QPEM command */
    CTRL_CMD_ACCESS_REG_PFCC, /**< Run access register PFCC command */
    CTRL_CMD_ACCESS_REG_QPPM, /**< Run access register QPPM command */
    CTRL_CMD_ACCESS_REG_SLECR, /**< Run access register SLECR command */
    CTRL_CMD_ACCESS_REG_MONI, /**< Run access register MONI command */
    CTRL_CMD_ACCESS_REG_RDPM, /**< Run access register RDPM command */
    CTRL_CMD_ACCESS_REG_MNVDA_NV_SWITCH_CONF, /**< Run access register MNVDA_NV_SWITCH_CONF command */
    CTRL_CMD_ACCESS_REG_MIN = CTRL_CMD_ACCESS_REG_PSPA, /**< Minimum enum value */
    CTRL_CMD_ACCESS_REG_MAX = CTRL_CMD_ACCESS_REG_MNVDA_NV_SWITCH_CONF  /**< Maximum enum value */
};

/**
 * sx_iicr_op enumerated type is used to note the possible
 * iicr OPs.
 */
typedef enum sx_iicr_op {
    SX_IICR_OP_NOP = 0,
    SX_IICR_OP_MARK,
    SX_IICR_OP_CLEAR,
} sx_iicr_op_e;

/**
 * ku_l2_type enumerated type is used to note the possible
 * L2 types.
 */
enum ku_l2_type {
    SX_KU_L2_TYPE_DONT_CARE, /**< Don't care value for listeners */
    SX_KU_L2_TYPE_IB, /**< IB */
    SX_KU_L2_TYPE_ETH, /**< Eth */
    SX_KU_L2_TYPE_FC, /**< FC */
    SX_KU_L2_TYPE_ROUTER_PORT, /**< RP */
    SX_KU_L2_MIN = SX_KU_L2_TYPE_DONT_CARE, /**< Minimum enum value */
    SX_KU_L2_MAX = SX_KU_L2_TYPE_ROUTER_PORT /**< Maximum enum value */
};

/**
 * ku_swid_type enumerated type is used to note the possible
 * swid types.
 */
enum ku_swid_type {
    KU_SWID_TYPE_DISABLED    = 0, /**< Disabled */
    KU_SWID_TYPE_INFINIBAND  = 1, /**< IB */
    KU_SWID_TYPE_ETHERNET    = 2, /**< Eth */
    KU_SWID_TYPE_ROUTER_PORT = 8, /**< RP */
    KU_SWID_TYPE_MIN         = KU_SWID_TYPE_DISABLED, /**< Minimum enum value */
    KU_SWID_TYPE_MAX         = KU_SWID_TYPE_ROUTER_PORT /**< Maximum enum value */
};

/**
 * ku_command_ifc_ret_status enumerated type is used to note the possible
 * return values from command IFC.
 */
enum ku_command_ifc_ret_status {
    COMMAND_IFC_RET_STATUS_OK             = 0X00, /**< OK */
    COMMAND_IFC_RET_STATUS_INTERNAL_ERROR = 0X01, /**< Internal error */
    COMMAND_IFC_RET_STATUS_BAD_OP         = 0X02, /**< Bad operation */
    COMMAND_IFC_RET_STATUS_BAD_PARAM      = 0X03, /**< Bad parameter */
    COMMAND_IFC_RET_STATUS_BAD_SYS_STATE  = 0X04, /**< Bad system state */
    COMMAND_IFC_RET_STATUS_BAD_RESOURCE   = 0X05, /**< Bad resource */
    COMMAND_IFC_RET_STATUS_RESOURCE_BUSY  = 0X06, /**< Resource busy */
    COMMAND_IFC_RET_STATUS_EXCEED_LIM     = 0X08, /**< Exceeds limitation */
    COMMAND_IFC_RET_STATUS_BAD_RES_STATE  = 0X09, /**< Bad res state */
    COMMAND_IFC_RET_STATUS_BAD_INDEX      = 0X0A, /**< Bad index */
    COMMAND_IFC_RET_STATUS_BAD_NVMEM      = 0X0B, /**< Bad NVMEM */
    COMMAND_IFC_RET_STATUS_BAD_PKT        = 0X30, /**< Bad packet */
    COMMAND_IFC_RET_STATUS_MIN            = COMMAND_IFC_RET_STATUS_OK, /**< Minimum enum value */
    COMMAND_IFC_RET_STATUS_MAX            = COMMAND_IFC_RET_STATUS_BAD_PKT /**< Maximum enum value */
};

/**
 * ku_dpt_path_type enumerated type is used to note the possible
 * DPT path types.
 */
enum ku_dpt_path_type {
    DPT_PATH_INVALID, /**< Invalid */
    DPT_PATH_I2C, /**< I2C */
    DPT_PATH_SGMII, /**< SGMII */
    DPT_PATH_PCI_E, /**< PCI express */
    DPT_PATH_MST, /**< MST */
    DPT_PATH_MIN = DPT_PATH_INVALID, /**< Minimum enum value */
    DPT_PATH_MAX = DPT_PATH_MST /**< Maximum enum value */
};

/**
 * pci_profile_e enumerated type is used to note the possible
 * PCI profile types.
 */
enum pci_profile_e {
    PCI_PROFILE_IB_SINGLE_SWID, /**< Single IB swid */
    PCI_PROFILE_IB_NAR_SINGLE_SWID, /**< Single IB swid with Adaptive Routing enabled */
    PCI_PROFILE_IB_MULTI_SWID, /**< Multiple IB swids */
    PCI_PROFILE_EN_SINGLE_SWID, /**< Single eth swid */
    PCI_PROFILE_EN_MULTI_SWID, /**< Multiple Eth swids */
    PCI_PROFILE_VPI_SINGLE_SWID, /**< VPI single swid */
    PCI_PROFILE_VPI_MULTI_SWID, /**< VPI multiple swids */
};

/**
 * hpkt_action enumerated type is used to note the possible
 * actions in HPKT register.
 */
enum hpkt_action {
    HPKT_ACTION_IGNORE, /**< Ignore */
    HPKT_ACTION_TRAP_2_CPU, /**< Trap to CPU */
    HPKT_ACTION_MIRROR_2_CPU, /**< Mirror to CPU */
    HPKT_ACTION_DISCARD /**< Discard */
};

/**
 * htgt_path enumerated type is used to note the possible
 * paths in HTGT register.
 */
enum htgt_path {
    HTGT_LOCAL_PATH    = 0, /**< Local path */
    HTGT_STACKING_PATH = 1, /**< Stacking path */
    HTGT_DR_PATH       = 2, /**< Directed route path */
    HTGT_ETH_PATH      = 3, /**< Ethernet path */
    HTGT_NULL_PATH     = 0xF /**< NULL path */
};

typedef uint8_t sxd_boolean_t;

/**
 * sxd_port_ib_link_width_t enumerated type is used to store IB link width
 */
typedef enum sxd_port_ib_link_width {
    SXD_PORT_IB_LINK_WIDTH_1X  = (1 << 0),
    SXD_PORT_IB_LINK_WIDTH_2X  = (1 << 1),
    SXD_PORT_IB_LINK_WIDTH_4X  = (1 << 2),
    SXD_PORT_IB_LINK_WIDTH_8X  = (1 << 3),
    SXD_PORT_IB_LINK_WIDTH_12X = (1 << 4),
} sxd_port_ib_link_width_t;

/**
 * sxd_port_force_tx_aba_param enumerated type is used to store aba parameters usage status
 */
typedef enum sxd_port_force_tx_aba_param {
    SXD_PORT_FORCE_TX_ABA_PARAM_AN_DISABLE = 0,
    SXD_PORT_FORCE_TX_ABA_PARAM_PARALLEL_DETECT,
} sxd_port_force_tx_aba_param_t;

/**
 * sxd_port_an_disable_cap enumerated type is used to determine Auto-Negotiate disable capability
 */
typedef enum sxd_port_an_disable_cap {
    SXD_PORT_AN_DISABLE_CAP_NO_SUPPORT = 0,
    SXD_PORT_AN_DISABLE_CAP_SUPPORT,
} sxd_port_an_disable_cap_t;

/**
 * sxd_port_an_disable_admin enumerated type is used to store Auto-Negotiate admin status
 */
typedef enum sxd_port_an_disable_admin {
    SXD_PORT_AN_DISABLE_ADMIN_NORMAL_OPERATION = 0,
    SXD_PORT_AN_DISABLE_ADMIN_DISABLE_AN,
} sxd_port_an_disable_admin_t;

/**
 * sxd_port_an_disable_admin enumerated type is used to store Auto-Negotiate admin status
 */
typedef enum sxd_port_eth_proto_lp_valid {
    SXD_PORT_ETH_PROTO_LP_VALID_DISABLE = 0,
    SXD_PORT_ETH_PROTO_LP_VALID_ENABLE
} sxd_port_eth_proto_lp_valid_t;

/**
 * sxd_port_an_status enumerated type is used to store Auto-Negotiation status
 */
typedef enum sxd_port_an_status {
    SXD_PORT_AN_STATUS_UNAVAILABLE = 0,
    SXD_PORT_AN_STATUS_AN_COMPLETED_SUCCESSFULLY,
    SXD_PORT_AN_STATUS_AN_PERFORMED_BUT_FAILED,
    SXD_PORT_AN_STATUS_AN_NOT_PERFORMED_LINK_UP,
    SXD_PORT_AN_STATUS_AN_NOT_PERFORMED_LINK_DOWN,
} sxd_port_an_status_t;

/**
 * sxd_port_connector_type enumerated type is used to store the connector type
 */
typedef enum sxd_port_connector_type {
    SXD_PORT_CONNECTOR_TYPE_NO_CONNECTOR_OR_UNKNOWN = 0,
    SXD_PORT_CONNECTOR_TYPE_PORT_NONE,
    SXD_PORT_CONNECTOR_TYPE_PORT_TP,
    SXD_PORT_CONNECTOR_TYPE_PORT_AUI,
    SXD_PORT_CONNECTOR_TYPE_PORT_BNC,
    SXD_PORT_CONNECTOR_TYPE_PORT_MII,
    SXD_PORT_CONNECTOR_TYPE_PORT_FIBRE,
    SXD_PORT_CONNECTOR_TYPE_PORT_DA,
    SXD_PORT_CONNECTOR_TYPE_PORT_OTHER,
} sxd_port_connector_type_t;

/**
 * sxd_port_eth_proto_t enumerated type is used to store
 * Ethernet protocol.
 */
typedef enum sxd_port_eth_proto {
    SXD_PORT_ETH_PROTOCOL_1000_BASE_CX_SGMII = (1 << 0),
    SXD_PORT_ETH_PROTOCOL_1000_BASE_KX       = (1 << 1),
    SXD_PORT_ETH_PROTOCOL_10G_BASE_CX4_XAUI  = (1 << 2),
    SXD_PORT_ETH_PROTOCOL_10G_BASE_KX4       = (1 << 3),
    SXD_PORT_ETH_PROTOCOL_10G_BASE_KR4       = (1 << 4),
    SXD_PORT_ETH_PROTOCOL_20G_BASE_KR2       = (1 << 5),
    SXD_PORT_ETH_PROTOCOL_40G_BASE_CR4       = (1 << 6),
    SXD_PORT_ETH_PROTOCOL_40G_BASE_KR4       = (1 << 7),
    SXD_PORT_ETH_PROTOCOL_56G_BASE_KR4       = (1 << 8),
    SXD_PORT_ETH_PROTOCOL_56G_BASE_KX4       = (1 << 9),
} sxd_port_eth_proto_t;

/**
 * sxd_port_fc_proto_t enumerated type is used to store Fibre
 * Channel protocol.
 */
typedef enum sxd_port_fc_proto {
    SXD_PORT_FC_PROTOCOL_1GFC = (1 << 0),
    SXD_PORT_FC_PROTOCOL_2GFC = (1 << 1),
    SXD_PORT_FC_PROTOCOL_4GFC = (1 << 2),
    SXD_PORT_FC_PROTOCOL_8GFC = (1 << 3),
} sxd_port_fc_proto_t;

/**
 * sxd_port_ib_proto_t enumerated type is used to store
 * InfiniBand protocol.
 */
typedef enum sxd_port_ib_proto {
    SXD_PORT_IB_PROTOCOL_SDR      = (1 << 0),
    SXD_PORT_IB_PROTOCOL_DDR      = (1 << 1),
    SXD_PORT_IB_PROTOCOL_QDR      = (1 << 2),
    SXD_PORT_IB_PROTOCOL_FDR10    = (1 << 3),
    SXD_PORT_IB_PROTOCOL_FDR      = (1 << 4),
    SXD_PORT_IB_PROTOCOL_EDR      = (1 << 5),
    SXD_PORT_IB_PROTOCOL_HDR      = (1 << 6),
    SXD_PORT_IB_PROTOCOL_NDR      = (1 << 7),
    SXD_PORT_IB_PROTOCOL_FDR_8_10 = (1 << 8)
} sxd_port_ib_proto_t;

/**
 * sxd_prcr_op_type enumerated type is used copy or move
 * rules in tcam.
 */
typedef enum sxd_prcr_op_type {
    SXD_PRCR_OP_RULES_MOVE = 0,
    SXD_PRCR_OP_RULES_COPY = 1
} sxd_prcr_op_type_t;


/**
 * Counter set type
 */
typedef enum sxd_counter_set_type {
    SXD_COUNTER_SET_TYPE_NO_COUNT                    = 0x0,
    SXD_COUNTER_SET_TYPE_PACKET                      = 0x1,
    SXD_COUNTER_SET_TYPE_BYTE                        = 0x2,
    SXD_COUNTER_SET_TYPE_PACKET_AND_BYTE             = 0x3,
    SXD_COUNTER_SET_TYPE_BYTE_STATISTICAL            = 0x4,
    SXD_COUNTER_SET_TYPE_PACKET_AND_BYTE_STATISTICAL = 0x5,
    SXD_COUNTER_SET_TYPE_RIF                         = 0x8,
    SXD_COUNTER_SET_TYPE_RIF_BASIC                   = 0x9,
    SXD_COUNTER_SET_TYPE_RIF_ENHANCED                = 0xA,
    SXD_COUNTER_SET_TYPE_RIF_MIXED_1                 = 0xB,
    SXD_COUNTER_SET_TYPE_RIF_MIXED_2                 = 0xC,
    SXD_COUNTER_SET_TYPE_RIF_BASIC_REDUCED           = 0x19,
    SXD_COUNTER_SET_TYPE_RIF_ENHANCED_REDUCED        = 0x1A,
    SXD_COUNTER_SET_TYPE_RIF_MIXED_1_REDUCED         = 0x1B,
    SXD_COUNTER_SET_TYPE_RIF_MIXED_2_REDUCED         = 0x1C,
} sxd_counter_set_type_t;

/**
 * sxd_tunnel_type enumerated type is used to match tunnel type.
 */
typedef enum sxd_tunnel_type {
    SXD_TUNNEL_TYPE_NVGRE  = 0,
    SXD_TUNNEL_TYPE_VXLAN  = 1,
    SXD_TUNNEL_TYPE_MPLS   = 2,
    SXD_TUNNEL_TYPE_IPINIP = 3,
    SXD_TUNNEL_TYPE_GRE    = 4,
    SXD_TUNNEL_TYPE_FLEX   = 5,
} sxd_tunnel_type_t;

/**
 * sxd_nve_tubbel_type enumerated type is used to match tunnel type.
 */
typedef enum sxd_nve_tunnel_type {
    SXD_NVE_TUNNEL_TYPE_VXLAN     = (1 << 0),
    SXD_NVE_TUNNEL_TYPE_GENEVE    = (1 << 1),
    SXD_NVE_TUNNEL_TYPE_VXLAN_GPE = (1 << 2),
    SXD_NVE_TUNNEL_TYPE_NVGRE     = (1 << 3),
} sxd_nve_tunnel_type_t;

enum ku_queue_type {
    KU_QUEUE_TYPE_TAIL_DROP = 0,    /**< Head Drop */
    KU_QUEUE_TYPE_HEAD_DROP = 1,  /**< Tail Drop */
    KU_QUEUE_TYPE_MIN       = KU_QUEUE_TYPE_TAIL_DROP,   /**< Minimum enum value */
    KU_QUEUE_TYPE_MAX       = KU_QUEUE_TYPE_HEAD_DROP   /**< Maximum enum value */
};

/**
 * ku_fd_attributes is used to store the data of the fd_attributes_set ioctl
 */
struct ku_fd_attributes_data {
    enum ku_queue_type queue_type;
};

/**
 * Counter Set.
 */
typedef struct sxd_counter_set {
    sxd_counter_set_type_t type;
    uint32_t               index;
} sxd_counter_set_t;

/**
 * ku_port_vlan_params_type enumerated type is used to match port_vlan types.
 */
typedef enum ku_port_vlan_params_type {
    KU_PORT_VLAN_PARAMS_TYPE_GLOBAL = 0,
    KU_PORT_VLAN_PARAMS_TYPE_PORT   = 1,
    KU_PORT_VLAN_PARAMS_TYPE_LAG    = 2,
    KU_PORT_VLAN_PARAMS_TYPE_VLAN   = 3,
    KU_PORT_VLAN_PARAMS_TYPE_NONE   = 4,
} ku_port_vlan_params_type_t;

/**
 * Netlink parameters to create port netdev
 * ip link add NAME type sx_netdev [ swid SWID ] port PORT
 */
enum {
    IFLA_SX_NETDEV_UNSPEC,
    IFLA_SX_NETDEV_SWID,
    IFLA_SX_NETDEV_PORT,
    __IFLA_SX_NETDEV_MAX
};
#define IFLA_SX_NETDEV_MAX (__IFLA_SX_NETDEV_MAX - 1)

/*
 * ku_res_id_t is used to match the resource id type.
 */
typedef enum mlxsw_res_id {
    KU_RES_ID_KVD_SIZE                   = 0x1001,
    KU_RES_ID_KVD_SINGLE_MIN_SIZE        = 0x1002,
    KU_RES_ID_KVD_DOUBLE_MIN_SIZE        = 0x1003,
    KU_RES_ID_CAP_MAX_SWIDS              = 0x2001,
    KU_RES_ID_CAP_MAX_SWITCH_PORTS       = 0x2002,
    KU_RES_ID_MAX_TRAP_GROUPS            = 0x2201,
    KU_RES_ID_TAC_PG_BUFF_SIZE           = 0x2214,
    KU_RES_ID_COUNTER_POOL_SIZE          = 0x2410,
    KU_RES_ID_MAX_SPAN                   = 0x2420,
    KU_RES_ID_COUNTER_SIZE_PACKETS_BYTES = 0x2443,
    KU_RES_ID_COUNTER_SIZE_ROUTER_BASIC  = 0x2449,
    KU_RES_ID_CAP_PTP_FRC_RATE           = 0x2460,
    KU_RES_ID_MAX_SYSTEM_PORT            = 0x2502,
    KU_RES_ID_MAX_LAG                    = 0x2520,
    KU_RES_ID_MAX_LAG_MEMBERS            = 0x2521,
    KU_RES_ID_MAX_BUFFER_SIZE            = 0x2802,
    KU_RES_ID_CELL_SIZE                  = 0x2803,
    KU_RES_ID_ACL_MAX_TCAM_REGIONS       = 0x2901,
    KU_RES_ID_ACL_MAX_TCAM_RULES         = 0x2902,
    KU_RES_ID_ACL_MAX_REGIONS            = 0x2903,
    KU_RES_ID_ACL_MAX_GROUPS             = 0x2904,
    KU_RES_ID_ACL_MAX_GROUP_SIZE         = 0x2905,
    KU_RES_ID_ACL_FLEX_KEYS              = 0x2910,
    KU_RES_ID_ACL_MAX_ACTION_PER_RULE    = 0x2911,
    KU_RES_ID_ACL_ACTIONS_PER_SET        = 0x2912,
    KU_RES_ID_MAX_CPU_POLICERS           = 0x2A13,
    KU_RES_ID_MAX_VRS                    = 0x2C01,
    KU_RES_ID_MAX_RIFS                   = 0x2C02,
    KU_RES_ID_MAX_LPM_TREES              = 0x2C30,
    KU_RES_ID_FW_ROUTER_SUP              = 0x2C51,

    /* Internal resources.
     *   * Determined by the SW, not queried from the HW.
     *       */

    __KU_RES_ID_MAX,
} ku_res_id_t;

typedef enum {
    KU_CHASSIS_TYPE_BARRACUDA, /* working with CQEv0 */
    KU_CHASSIS_TYPE_MANTARAY,  /* working with CQEv2 */
    KU_CHASSIS_TYPE_INVALID
} ku_chassis_type_t;

typedef enum {
    KU_MGMT_BOARD_1,
    KU_MGMT_BOARD_2,
    KU_MGMT_BOARD_INVALID
} ku_mgmt_board_t;

enum sx_netdev_user_channel_type {
    USER_CHANNEL_L3_NETDEV       = 0,
    USER_CHANNEL_LOG_PORT_NETDEV = 1,
    USER_CHANNEL_PHY_PORT_NETDEV = 2,
    NUM_OF_NET_DEV_TYPE
};

typedef enum {
    SXD_PARSER_HEADER_SOP          = 0x0,
    SXD_PARSER_HEADER_MAC          = 0x1,
    SXD_PARSER_HEADER_IPV4         = 0x10,
    SXD_PARSER_HEADER_IPV6         = 0x14,
    SXD_PARSER_HEADER_UDP          = 0x20,
    SXD_PARSER_HEADER_TCP          = 0x21,
    SXD_PARSER_HEADER_GRE          = 0x30,
    SXD_PARSER_HEADER_VXLAN_GPE    = 0x41,
    SXD_PARSER_HEADER_GENEVE       = 0x42,
    SXD_PARSER_HEADER_MPLS         = 0x50,
    SXD_PARSER_HEADER_FPH0         = 0x80,
    SXD_PARSER_HEADER_FPH1         = 0x81,
    SXD_PARSER_HEADER_FPH2         = 0x82,
    SXD_PARSER_HEADER_FPH3         = 0x83,
    SXD_PARSER_HEADER_FPH4         = 0x84,
    SXD_PARSER_HEADER_FPH5         = 0x85,
    SXD_PARSER_HEADER_FPH6         = 0x86,
    SXD_PARSER_HEADER_FPH7         = 0x87,
    SXD_PARSER_HEADER_IPV6_HBH_EXT = 0xE0,
    SXD_PARSER_HEADER_IPV6_EXT     = 0xF0,
} sxd_parser_header_e;

typedef enum {
    SXD_EMT_COMMAND_IMMEDIATE_E                      = 0x0,
    SXD_EMT_COMMAND_SPAN_MIRROR_INGRESS_PORT_LABEL_E = 0x4,
    SXD_EMT_COMMAND_SPAN_MIRROR_EGRESS_PORT_LABEL_E  = 0x5,
    SXD_EMT_COMMAND_INGRESS_TIMESTAMP_SEC_MSB_E      = 0x10,
    SXD_EMT_COMMAND_INGRESS_TIMESTAMP_SEC_LSB_E      = 0x11,
    SXD_EMT_COMMAND_INGRESS_TIMESTAMP_NSEC_MSB_E     = 0x12,
    SXD_EMT_COMMAND_INGRESS_TIMESTAMP_NSEC_LSB_E     = 0x13,
    SXD_EMT_COMMAND_EGRESS_TIMESTAMP_SEC_MSB_E       = 0x14,
    SXD_EMT_COMMAND_EGRESS_TIMESTAMP_SEC_LSB_E       = 0x15,
    SXD_EMT_COMMAND_EGRESS_TIMESTAMP_NSEC_MSB_E      = 0x16,
    SXD_EMT_COMMAND_EGRESS_TIMESTAMP_NSEC_LSB_E      = 0x17,
    SXD_EMT_COMMAND_TCLASS_E                         = 0x20,
    SXD_EMT_COMMAND_EGRESS_BUFFER_FILL_LEVEL_MSB_E   = 0x30,
    SXD_EMT_COMMAND_EGRESS_BUFFER_FILL_LEVEL_LSB_E   = 0x31,
    SXD_EMT_COMMAND_LATENCY_MSB_E                    = 0x40,
    SXD_EMT_COMMAND_LATENCY_LSB_E                    = 0x41,
    SXD_EMT_COMMAND_GP_REGISTER_0_E                  = 0x80,
    SXD_EMT_COMMAND_GP_REGISTER_1_E                  = 0x81,
    SXD_EMT_COMMAND_GP_REGISTER_2_E                  = 0x82,
    SXD_EMT_COMMAND_GP_REGISTER_3_E                  = 0x83,
    SXD_EMT_COMMAND_GP_REGISTER_4_E                  = 0x84,
    SXD_EMT_COMMAND_GP_REGISTER_5_E                  = 0x85,
    SXD_EMT_COMMAND_GP_REGISTER_6_E                  = 0x86,
    SXD_EMT_COMMAND_GP_REGISTER_7_E                  = 0x87,
    SXD_EMT_COMMAND_SRAM_0_D0_E                      = 0x90,
    SXD_EMT_COMMAND_SRAM_0_D1_E                      = 0x91,
    SXD_EMT_COMMAND_SRAM_0_D2_E                      = 0x92,
    SXD_EMT_COMMAND_SRAM_0_D3_E                      = 0x93,
    SXD_EMT_COMMAND_SRAM_1_D0_E                      = 0x94,
    SXD_EMT_COMMAND_SRAM_1_D1_E                      = 0x95,
    SXD_EMT_COMMAND_SRAM_1_D2_E                      = 0x96,
    SXD_EMT_COMMAND_SRAM_1_D3_E                      = 0x97,
} sxd_emt_command_e;

/************************************************
 *  Structs
 ***********************************************/

typedef struct ib_addr1 {
    u_int8_t addr_octet[16];
} __attribute__ ((__packed__)) sxd_gid_t;

struct sx_ether_addr {
    uint8_t ether_addr_octet[ETHER_ADDR_LENGTH];
};

/**
 * ku_dpt_i2c_info structure is used to store I2C
 * info in the DPT.
 */
struct ku_dpt_i2c_info {
    int sx_i2c_dev; /**< sx_i2c_dev - I2C info */
};

typedef enum sxd_chip_types {
    SXD_CHIP_TYPE_UNKNOWN     = 0,
    SXD_CHIP_TYPE_SWITCHX_A2  = 1,
    SXD_CHIP_TYPE_SWITCHX_A1  = 3,
    SXD_CHIP_TYPE_SWITCHX_A0  = 4,
    SXD_CHIP_TYPE_SWITCH_IB   = 5,
    SXD_CHIP_TYPE_SPECTRUM    = 6,
    SXD_CHIP_TYPE_SWITCH_IB2  = 7,
    SXD_CHIP_TYPE_SPECTRUM_A1 = 8,
    SXD_CHIP_TYPE_SPECTRUM2   = 9,
    SXD_CHIP_TYPE_QUANTUM     = 10,
    SXD_CHIP_TYPE_SPECTRUM3   = 11,
    SXD_CHIP_TYPE_QUANTUM2    = 12,
    SXD_CHIP_TYPE_SPECTRUM4   = 13,
    SXD_CHIP_TYPE_QUANTUM3    = 14,
    SXD_CHIP_TYPES_MAX        = SXD_CHIP_TYPE_QUANTUM3,
    /* Do not change this value, it can break ISSU !*/
    SXD_CHIP_TYPES_MAX_ISSU = SXD_CHIP_TYPE_SPECTRUM3 /* need to check this !!! */
} sxd_chip_types_t;

/**
 * ku_sgmii_mft_info stores all FW tools information for device enumeration
 */
struct ku_sgmii_mft_info {
    uint16_t version;
    uint16_t chip_type; /* value taken from MGIR register */
    char     fru_name[16];
    uint16_t fru_modifier;
    int      dev_id;
};

/**
 * ku_dpt_sgmii_info structure is used to store SGMII
 * info in the DPT.
 */
struct ku_dpt_sgmii_info {
    uint8_t  dmac[6];
    uint16_t vid;
};

/**
 * ku_dpt_pcie_info structure is used to store PCI express
 * info in the DPT.
 */
struct ku_dpt_pcie_info {
    unsigned int                       pci_id; /* redundant! field is kept here for backward compatibility */
    void __attribute__((aligned(8))) * sx_dev; /* redundant! field is kept here for backward compatibility */
};

/**
 * ku_dpt_mst_info structure is used to store MST info in the DPT.
 */
struct ku_dpt_mst_info {
    /* right now, no information */
};

/**
 * ku_dpt_path_info union is used to store the path
 * info in the DPT.
 */
union ku_dpt_path_info {
    struct ku_dpt_i2c_info   sx_i2c_info; /**< sx_i2c_info - I2C info */
    struct ku_dpt_pcie_info  sx_pcie_info; /**< sx_pcie_info - PCI info */
    struct ku_dpt_sgmii_info sx_sgmii_info; /**< sx_sgmii_info - PCI info */
    struct ku_dpt_mst_info   sx_mst_info; /**< sx_mst_info - MST info */
};

/**
 * ku_dpt_path_add structure is used to store the add path
 * parameters.
 */
struct ku_dpt_path_add {
    uint8_t                dev_id; /**< dev_id - device ID */
    enum  ku_dpt_path_type path_type; /**< path_type - the path type */
    union ku_dpt_path_info path_info; /**< path_info - the path info */
    uint8_t                is_local; /**< is_local - is it the local device */
};

/**
 * ku_dpt_path_modify structure is used to store the modify path
 * parameters.
 */
struct ku_dpt_path_modify {
    uint8_t                dev_id; /**< dev_id - device ID */
    enum  ku_dpt_path_type path_type; /**< path_type - the path type */
};

/**
 * ku_swid_2_rdq_query structure is used to store the swid to RDQ
 * query parameters.
 */
struct ku_swid_2_rdq_query {
    int swid; /**< swid - the swid */
    int rdq; /**< rdq - the RDQ */
};

/**
 * sx_dev_cap structure is used to store the device capabilities
 * info.
 */
struct sx_dev_cap {
    int     log_max_rdq_sz; /**< log_max_rdq_sz - log max RDQ size */
    int     log_max_sdq_sz; /**< log_max_sdq_sz - log max SDQ size */
    int     log_max_cq_sz; /**< log_max_cq_sz - log max CQ size */
    int     log_max_eq_sz; /**< log_max_eq_sz - log max EQ size */
    uint8_t max_num_rdqs; /**< max_num_rdqs - maximum number of RDQs */
    uint8_t max_num_sdqs; /**< max_num_sdqs - maximum number of SDQs */
    uint8_t max_num_cqs; /**< max_num_cqs - maximum number of CQs */
    uint8_t max_num_eqs; /**< max_num_eqs - maximum number of EQs */
    uint8_t max_num_cpu_egress_tcs; /**< max_num_cpu_egress_tcs - maximum number of CPU egress tclasses */
    uint8_t max_num_cpu_ingress_tcs; /**< max_num_cpu_ingress_tcs - maximum number of CPU ingress tclasses */
    uint8_t max_sg_sq; /**< max_sg_sq - maximum number scatter gather entries in SDQs */
    uint8_t max_sg_rq; /**< max_sg_rq - maximum number scatter gather entries in RDQs */
    uint8_t dev_id; /**< dev_id - device ID */
};

/**
 * ku_timespec structure is used to store timespec in 32/64 compatible form
 */
struct ku_timespec {
    int32_t tv_sec;
    int32_t tv_nsec;
};

enum {
    /* following values are taken from PRM: */
    SXD_TS_TYPE_CQE_NONE       = 0,
    SXD_TS_TYPE_CQE_FRC        = 1,
    SXD_TS_TYPE_CQE_UTC        = 2,
    SXD_TS_TYPE_CQE_MIRROR_UTC = 3,
    SXD_TS_TYPE_CQE_MAX        = SXD_TS_TYPE_CQE_MIRROR_UTC,

    /* internal driver values */
    SXD_TS_TYPE_NONE  = SXD_TS_TYPE_CQE_NONE,
    SXD_TS_TYPE_LINUX = SXD_TS_TYPE_CQE_MAX + 1
};

enum sxd_mirror_elph {
    /* Following values are taken from PRM: */
    SXD_MIRROR_ELPH_NO_INDICATION_E = 0,
    SXD_MIRROR_ELPH_NOT_ELEPHANT_E  = 1,
    SXD_MIRROR_ELPH_ELEPHANT_E      = 3,
};

/**
 * ku_read structure is used to store the read
 * info.
 */
struct ku_read {
    uint16_t system_port; /**< system_port - system port on which the packet was received */
    uint16_t trap_id;  /**< trap_id - TrapID(=syndrome id) that captured the packet */
    uint8_t  is_lag; /**< is_lag - was the packet received from a port which is a LAG */
    uint16_t lag_subport;   /**< lag_subport - For LAGs this field describe the port index within the LAG */
    uint8_t  swid; /**< swid - swid */
    uint32_t original_packet_size; /**<the original size of packet,
                                    *        if packet wasn't truncated packet_size=original_packet_size*/
    uint8_t                                          has_timestamp; /**< does packet have timestamp */
    uint32_t                                         user_def_val; /**< for ACL trap id describe acl user ID */
    uint16_t                                         dest_sysport; /**< Destination sysport (for mirrored packets) */
    uint8_t                                          dest_is_lag; /**< Destination is LAG port */
    uint16_t                                         dest_lag_subport;   /**< For LAG destination port: index within LAG */
    uint64_t __attribute__((aligned(8)))             length; /**< length - packet size (if 0 - no more packets) */
    struct   ku_timespec __attribute__((aligned(8))) timestamp; /**< timestamp of packet */
    uint8_t                                          mirror_reason;
    uint8_t                                          mirror_tclass;
    uint16_t                                         mirror_cong;
    uint32_t                                         mirror_lantency;
    uint8_t                                          mirror_elephant;
    uint8_t                                          timestamp_type;
    uint8_t                                          dev_id; /**< device id from which this was received */
    uint8_t                                          channel_experienced_drop; /**< The channel experienced a drop due to overflow */
};

/**
 * loopback_data structure is used to store the data of a sent loopback packet.
 */
struct loopback_data {
    uint16_t trap_id;    /**< trap_id - the trap ID in case of a loopback packet */
    uint8_t  is_lag;    /**< is the system port member of a lag. */
    uint16_t lag_subport;      /**< lag sub-port when applicable */
};

enum ku_ext_fwd_mode {
    SX_EXT_FWD_MODE_REGULAR_AND_MIRROR_AGENT = 1,
    SX_EXT_FWD_MODE_MIRROR_AGENT             = 2
};

/**
 * Defines SPAN oob destination attributes
 */
struct span_oob_data {
    uint8_t ext_fwd_mode;
    uint8_t mirror_reason_id;     /** HOST_BASED_MIRROR_REASON_ID_1/2/3 */
    uint8_t span_session_id;
};


/**
 * isx_meta structure is used to store the ISX meta
 * data of a sent packet.
 */
struct isx_meta {
    uint8_t              etclass; /**< etclass - egress tclass */
    uint8_t              swid; /**< swid - swid */
    uint16_t             system_port_mid; /**< system_port_mid - system port or multicast ID */
    uint8_t              rdq; /**< rdq - RDQ */
    uint8_t              to_cpu; /**< to_cpu - should the packet go to the CPU */
    uint8_t              lp; /**< lp - should the packet be processed locally */
    enum ku_pkt_type     type; /**< type - packet type */
    uint8_t              dev_id; /**< dev_id - device ID */
    struct loopback_data loopback_data;    /**< loopback_data - loopback packets data */
    uint8_t              rx_is_router;
    uint8_t              fid_valid;
    uint16_t             fid;
    uint8_t              rx_is_tunnel;
    uint8_t              span_oob_data_valid;
    struct span_oob_data span_oob_data;     /**< span_oob_data - packets data for sending packets to SPAN session*/
};

/**
 * ku_raise_trap structure is used to store the raise trap ioctl info
 */
struct ku_raise_trap {
    uint16_t                           trap_id; /**< trap_id - the trap ID */
    uint32_t                           buffer_size; /**< buffer_size - the buffer size */
    uint8_t                            swid; /**< swid - switch partition ID */
    uint16_t                           sysport; /**< sysport - system port or LAG ID */
    uint8_t                            is_lag; /**< is the source logical port member of a lag. */
    uint16_t                           lag_subport;   /**< source lag port when applicable */
    void __attribute__((aligned(8))) * buffer_p;    /**< buffer_p - a pointer to the buffer */
};

/**
 * iovec compat
 */
struct ku_iovec {
    size_t                             iov_len;
    void * __attribute__((aligned(8))) iov_base;
};

/**
 * ku_write structure is used to store the write
 * info.
 */
struct ku_write {
    struct isx_meta                               meta; /**< meta - the ISX meta data */
    uint32_t                                      vec_entries; /**< vec_entries - iovec entries number */
    struct ku_iovec * __attribute__((aligned(8))) iov;    /**< iov - an array of iovec, each one point to one of a packet buffer */
};

/**
 * ku_filter_critireas union is used to store the filter critireas
 * info.
 */
union ku_filter_critireas {
    struct {
        uint16_t                             ethtype; /**< ethtype - filter Eth pkts according to ethtype or 0 for ALL */
        uint64_t __attribute__((aligned(8))) dmac;   /**< dmac - filter Eth pkts according to dmac or 0 for ALL */
        uint32_t                             emad_tid; /**< emad_tid - filter emads according to tid */
        uint8_t                              from_rp; /**< from_rp - is packet received from router port */
        uint8_t                              from_bridge; /**< from_bridge - is packet received from bridge */
    } eth; /**< eth - ETH filter critireas */
    struct  {
        uint16_t TBD; /**< TBD - TBD */
    } fc; /**< FC - FC filter critireas */
    struct {
        uint32_t qpn; /**< qpn - filter IB pkt according to destination qpn */
        uint8_t  is_oob_originated_mad; /**< is this mad originated from OOB driver? */
        uint64_t mad_tid; /**< mad transaction ID (host order) */
    } ib; /**< ib - IB filter critireas */
    struct {
        uint16_t sysport;
        uint8_t  drop_enable; /**< drop_enable - filter events in driver */
    } dont_care;
};

/**
 * ku_port_vlan_params structure is used to store port vlan parameters.
 */
struct ku_port_vlan_params {
    ku_port_vlan_params_type_t port_vlan_type;
    uint16_t                   sysport;
    uint16_t                   lag_id;
    uint16_t                   vlan;
};

/**
 * ku_l2_tunnel_params structure is used to store L2 tunnel channel parameters.
 */
struct ku_l2_tunnel_params {
    uint64_t __attribute__((aligned(8))) dmac; /**< dmac - destination MAC address */
    uint16_t                             vid; /** vid - VLAN ID */
    uint8_t                              prio; /** prio - priority */
};

/**
 * ku_psample_params structure is used to store PSAMPLE channel parameters.
 */
struct ku_psample_params {
    uint32_t group_id;
};

/**
 * ku_user_channel_type enumerated type is used to note the possible user channels types.
 */
enum ku_user_channel_type {
    SX_KU_USER_CHANNEL_TYPE_FD,
    SX_KU_USER_CHANNEL_TYPE_L3_NETDEV,
    SX_KU_USER_CHANNEL_TYPE_L2_NETDEV,
    SX_KU_USER_CHANNEL_TYPE_PHY_NETDEV,
    SX_KU_USER_CHANNEL_TYPE_L2_TUNNEL,
    SX_KU_USER_CHANNEL_TYPE_PSAMPLE,
    SX_KU_USER_CHANNEL_TYPE_DROP_MONITOR
};

/**
 * ku_synd_ioctl structure is used to store the syndrome
 * info.
 */
struct ku_synd_ioctl {
    uint16_t                   syndrome_num; /**< syndrome_num - syndrome num (0-511, 512=Don't care) */
    uint8_t                    swid; /**< swid - swid (0-7, or 255=Don't care) */
    enum  ku_l2_type           type; /**< type - L2 type (ib, eth, fc, dont-care */
    uint8_t                    is_default; /**< is_default - is default listener (0=false, 1=true) */
    uint8_t                    is_register; /**< is_register - te action requested is register or filter (0=filter, 1=register) */
    union ku_filter_critireas  critireas;  /**< critireas - additional filter critireas  */
    enum ku_user_channel_type  channel_type;  /**< channel_type - channel type */
    struct ku_l2_tunnel_params l2_tunnel_params;  /**< l2_tunnel_params - L2 tunnel parameters when channel type is L2 tunnel */
    struct ku_port_vlan_params port_vlan_params;  /**< port / vlan parameters for per port registration*/
    struct ku_psample_params   psample_params; /**< psample_params - PSAMPLE parameters when channel type is PSAMPLE */
};
struct ku_monitor_synd_ioctl {
    uint8_t                    swid;                  /**< swid - swid (0-7, or 255=Don't care) */
    uint16_t                   syndrome_num;          /**< syndrome_num - syndrome num (0-511, 512=Don't care) */
    uint16_t                   monitor_hw_trap_group; /**< HW trap group - represents relevant RDQ */
    uint8_t                    cmd;                   /**< cmd to execute - True == Add, false == Remove */
    enum  ku_l2_type           type;                  /**< type - L2 type (ib, eth, fc, dont-care */
    struct ku_port_vlan_params port_vlan_params;      /**< port / vlan parameters for per port registration*/
    union ku_filter_critireas  critireas;             /**< critireas - additional filter critireas  */
};
struct ku_monitor_trap_group_stat_ioctl {
    uint16_t      monitor_hw_trap_group;
    sxd_boolean_t clear_after_read;
    uint32_t      discarded_pkts_total_num;
};

/**
 * tx_resources structure is used to store the tx resources
 * info.
 */
struct tx_resources {
    uint8_t stclass; /**< stclass - stacking tclass */
    uint8_t sdq; /**< sdq - SDQ */
};

/**
 * rdq_properties structure is used to store the RDQ properties
 */
struct rdq_properties {
    uint16_t number_of_entries;  /**< number_of_entries - number of entries */
    uint16_t entry_size; /**< entry_size - entry size */
    uint16_t rdq_weight; /**< rdq_weight - rdq weight */
    uint8_t  priority; /**< priority - priority */
};
enum sxd_chip_rev {
    SXD_CHIP_REV_UNKNOWN = 0,
    SXD_CHIP_REV_A0      = 1 << 1,
    SXD_CHIP_REV_A1      = 1 << 2,
    SXD_CHIP_REV_A2      = 1 << 3,
};
struct sxd_chip_ver {
    enum sxd_chip_types chip_type;
    enum sxd_chip_rev   chip_rev;
};

/**
 * sx_pci_profile structure is used to store the PCI profile info
 */
struct sx_pci_profile {
    enum pci_profile_e    pci_profile;   /**< pci_profile - PCI profile type */
    struct tx_resources   tx_prof[NUMBER_OF_SWIDS][NUMBER_OF_ETCLASSES];   /**< tx_prof - tx profile per swid and etclass */
    struct tx_resources   emad_tx_prof;   /**< emad_tx_prof - tx profile for emads */
    enum ku_l2_type       swid_type[NUMBER_OF_SWIDS];   /**< swid_type - L2 type for each swid */
    uint8_t               ipoib_router_port_enable[NUMBER_OF_SWIDS];   /**< ipoib_router_port_enable - For IB swids IPoIB Router Port Enable */
    uint16_t              max_pkey;   /**< max_pkey - Maximum per port pkey table size (for pkey enforcement) */
    uint8_t               rdq_count[NUMBER_OF_SWIDS];   /**< rdq_count - RDQ count for each swid */
    uint8_t               rdq[NUMBER_OF_SWIDS][NUMBER_OF_RDQS];   /**< rdq - RDQ per swid and index */
    uint8_t               emad_rdq;   /**< emad_rdq - emad RDQ */
    struct rdq_properties rdq_properties[NUMBER_OF_RDQS];   /**< rdq_properties - properties of each RDQ */
    uint8_t               cpu_egress_tclass[NUMBER_OF_SDQS];   /**< cpu_egress_tclass - CPU egress tclass per SDQ */
    uint8_t               dev_id;   /**< dev_id - device ID */
    uint8_t               dont_register_to_ib_router_traps;   /**< dont_register_to_ib_router_traps - IB router traps registration */
};

/**
 * ku_set_rdq_rate_limiter structure is used to store the per RDQ rate limiter info
 */
struct ku_set_rdq_rate_limiter {
    unsigned int time_interval;    /**< time_interval - Time interval in milliseconds between each credit addition phase (shared for all RDQs) */
    int          rdq;    /**< rdq - RDQ */
    uint8_t      use_limiter;    /**< use_limiter - Should a rate limiter be used for this RDQ */
    int          max_credit;    /**< max_credit - The Maximum credit for the RDQ */
    int          interval_credit;    /**< interval_credit - The credit added in each interval */
};

/**
 * ku_rdq_timestamp_state structure is used to enable/disable time stamp per RDQ
 */
struct ku_rdq_timestamp_state {
    uint8_t dev_id;
    int     rdq;    /**< rdq - RDQ */
    uint8_t enable; /**< enable - 0-disable, 1-enable */
    uint8_t hw_utc_enable; /**< hw_utc_enable - 0-disable, 1-enable */
};

/**
 * ku_rdq_cpu_priority structure is used to set priority to LOW/HIGH depends on HW policer existence
 */
struct ku_rdq_cpu_priority {
    uint8_t dev_id;
    int     rdq;    /**< rdq - RDQ */
    uint8_t high_prio; /**< 1=high priority, 0=low priority */
};

/**
 * ku_set_truncate_params structure is used to store the per RDQ truncate parameters
 */
struct ku_set_truncate_params {
    uint8_t  dev_id;
    int      rdq;    /**< rdq - the RDQ */
    uint8_t  truncate_enable;    /**< truncate_enable - Should packets received on this RDQ be truncated */
    uint16_t truncate_size;    /**< truncate_size - The Maximum size of the truncated packets */
};

/**
 * ku_set_truncate_params structure is used to set RDQ is_monitor mode
 */
struct ku_set_monitor_rdq_params {
    uint8_t dev_id;
    int     rdq;            /**< rdq - the RDQ */
    uint8_t is_monitor;     /**< is_monitor: 1 - RDQ is Monitor RDQ , 0 - RDQ is generic RDQ */
    uint8_t cpu_tclass;
    uint8_t del_all_fd_listeners; /**< if set to 1, will delete all monitoring RDQ owner FD listeners */
};

/**
 * ku_set_rdq_filter_ebpf_prog_params is used to attach/detach the ebpf program to/from an RDQ
 */
struct ku_set_rdq_filter_ebpf_prog_params {
    int     rdq; /**< rdq - the RDQ */
    int     ebpf_prog_fd; /**< ebpf_prog_fd - The filter eBPF program file descriptor */
    uint8_t is_attach; /** is_attach: 1 - attach the program to RDQ, 0 - detach the program from RDQ */
};

/**
 * ku_set_rdq_agg_ebpf_prog_params is used to attach/detach the aggregation ebpf program to/from an RDQ
 */
struct ku_set_rdq_agg_ebpf_prog_params {
    int     rdq; /**< rdq - the RDQ */
    int     index; /**< index - the ebpf program index */
    int     ebpf_prog_fd; /**< ebpf_prog_fd - The aggregation eBPF program file descriptor */
    uint8_t is_attach; /** is_attach: 1 - attach the program to RDQ, 0 - detach the program from RDQ */
};

#define READ_MULTI_BUFFS_MAX 1024

enum SX_FILE_OP {
    SX_FILE_OP_READ = 1,
    SX_FILE_OP_COUNT,
    SX_FILE_OP_FLUSH,
};

/**
 * ku_set_truncate_params structure is used to set RDQ is_monitor mode
 */
struct ku_read_multi_params {
    int             buffer_count;                               /**< INOUT: number of provided buffers, if 0 - count of ready buffers requested*/
    enum SX_FILE_OP file_op;
    uint8_t       * buffer_list[READ_MULTI_BUFFS_MAX];          /**< IN: list of buffers for a packets */
    size_t          buffer_size_list[READ_MULTI_BUFFS_MAX];     /**< INOUT: size of buffers for a packets */
};

/**
 * ku_cr_space_read structure is used to store the CR space read parameters
 */
struct ku_cr_space_read {
    uint8_t                               dev_id; /**< dev_id - Device ID */
    unsigned int                          address; /**< address - Address to read from */
    int                                   size; /**< size - size in bytes to read */
    uint8_t __attribute__((aligned(8))) * data;   /**< data - Buffer to read into */
};

/**
 * ku_cr_space_write structure is used to store the CR space write parameters
 */
struct ku_cr_space_write {
    uint8_t                               dev_id; /**< dev_id - Device ID */
    unsigned int                          address; /**< address - Address to write to */
    int                                   size; /**< size - size in bytes to write */
    uint8_t __attribute__((aligned(8))) * data;   /**< data - Data to write */
};

#define SX_CR_DUMP_MEMBLK_SIZE       (512 * 1024)
#define SX_CR_DUMP_MIN_MEMBLK_SIZE   (128 * 1024)
#define SX_CR_DUMP_CANARY_MAGIC_WORD (0xCAFECAFE)
#define SX_CR_DUMP_CANARY_BYTE_NUM   (8)

enum {
    SX_CR_DUMP_RET_NOT_SUPPORTED             = 100,
    SX_CR_DUMP_RET_CANCEL_GENERAL            = 101,
    SX_CR_DUMP_RET_CANCEL_OLD_DUMP           = 102,
    SX_CR_DUMP_RET_CANCEL_MESS_FW            = 103,
    SX_CR_DUMP_RET_CANCEL_FW_PARAM_MISALIGN  = 104,
    SX_CR_DUMP_RET_CANCEL_DUMP_SIZE_OVERFLOW = 105,
    SX_CR_DUMP_RET_CANCEL_DUMPSN_ERR         = 106,
    SX_CR_DUMP_RET_CANCEL_TRANSSN_ERR        = 107,
    SX_CR_DUMP_RET_CANCEL_FW_WRITE_OVERWRITE = 108,
    SX_CR_DUMP_RET_CANCEL_CANARY_ERR         = 109,
    SX_CR_DUMP_RET_FATAL_FW_ERR              = 110,
    SX_CR_DUMP_RET_LAYER1_TIMEOUT            = 111,
    SX_CR_DUMP_RET_FINISH                    = 112,
    SX_CR_DUMP_RET_TO_BE_CONT                = 113,
};

enum {
    SX_CR_DUMP_OP_NOP                = 0,
    SX_CR_DUMP_OP_START_FLAT         = 1,
    SX_CR_DUMP_OP_START_GW           = 2,
    SX_CR_DUMP_OP_START_GDB          = 3,
    SX_CR_DUMP_OP_CONT               = 4,
    SX_CR_DUMP_OP_START_WAIT         = 5,
    SX_CR_DUMP_OP_CONT_WAIT          = 6,
    SX_CR_DUMP_OP_CANCEL             = 15,
    SX_CR_DUMP_OP_GET_GDB_DUMP_LIMIT = 20,
    SX_CR_DUMP_OP_INVALID            = 0xFF,
};

/**
 * sx_cr_dump_cmd_mem structure is used to store the CR dump parameters
 */
struct sx_cr_dump_cmd_mem {
    uint8_t                              opcode;
    uint16_t                             trans_sn;
    uint8_t                              dump_sn;
    uint8_t                              status;
    uint64_t __attribute__((aligned(8))) host_base_addr;
    uint64_t __attribute__((aligned(8))) host_size_allocated;
    uint64_t __attribute__((aligned(8))) host_size_used;
};

/**
 * sx_cr_dump_ret structure is used to store the CR dump return code and cr_dump_cmd memory
 */
struct sx_cr_dump_ret {
    int                       ret_code;
    struct sx_cr_dump_cmd_mem ret_cmd_mem;
};

/**
 * ku_cr_dump structure is used to store the CR dump parameters
 */
struct ku_cr_dump {
    uint8_t                               dev_id; /**< dev_id - Device ID */
    uint8_t                               opcode; /**< opcode - Opcode of Cr_dump command */
    pid_t                                 pid; /**< pid - Caller PID */
    unsigned int                          dumped_size; /**< dumped_size - Mark dumped number in a dump session */
    unsigned int                          size; /**< size - size in bytes to read */
    uint8_t __attribute__((aligned(8))) * data;   /**< data - Buffer to read into */
    struct sx_cr_dump_ret                 ret; /**< ret - fw cr_dump return values */
};


typedef enum fw_dump_completion_state {
    FW_DUMP_COMPLETION_STATE_IDLE = 0,
    FW_DUMP_COMPLETION_STATE_REQUEST_SENT,
    FW_DUMP_COMPLETION_STATE_DONE,
} fw_dump_completion_state_t;

/**
 * ku_cr_dump_completion_state structure is used query and configure the fw_dump_completion_state
 */
struct ku_cr_dump_completion_state {
    uint8_t                    dev_id;            /**< dev_id - Device ID */
    sxd_boolean_t              query; /**< query - Should query value or configure */
    fw_dump_completion_state_t state; /**< state - actual state value or value to configure */
};

/**
 * ku_rearm_module_event_ret structure is used to return result of re-arm module event
 */
struct ku_rearm_module_event_ret {
    uint8_t oper_status;         /**< pmaos.oper_status */
    uint8_t error_type;          /**< pmaos.error_type */
};

/**
 * ku_rearm_module_event structure is used to re-arm module event
 */
struct ku_rearm_module_event {
    uint8_t                          dev_id; /**< dev_id - Device ID */
    uint8_t                          slot;
    uint8_t                          module;
    uint8_t                          gen_mode;
    struct ku_rearm_module_event_ret ret;
};

/**
 * ku_port_netdev structure is used to store the port netdevice parameters
 */
struct ku_port_netdev {
    char     name[SX_IFNAMSIZ];    /**< name - interface name, will be the name of the net device */
    uint16_t sysport;    /**< sysport - system port or LAG ID */
    uint8_t  is_lag;    /**< is_lag - a boolean indicating if the port is a LAG port */
    uint8_t  swid;    /**< swid - swid (0-7) */
};

/**
 * ku_get_pci_profile structure is used to store the PCI profile info
 */
struct ku_get_pci_profile {
    uint8_t               dev_id; /**< dev_id - device ID */
    enum pci_profile_e    pci_profile; /**< pci_profile - the PCI profile */
    struct sx_pci_profile profile;
};

enum sxd_fw_boot_status_e {
    SXD_FW_BOOT_STATUS_OK_E,
    SXD_FW_BOOT_STATUS_IN_FLASH_RECOVERY_E,
    SXD_FW_BOOT_STATUS_RMA_E
};

/**
 * ku_synd_query_ioctl structure is used to store the query syndrome ioctl info
 */
struct ku_synd_query_ioctl {
    uint16_t syndrome_num;    /**< syndrome_num - syndrome num (0-511, 512=Don't care)*/
    uint8_t  is_registered;    /**< is_registered - anyone is registered on syndrome_num? */
};

/**
 * ku_query_fw structure is used to store the query FW info
 */
struct ku_query_fw {
    uint64_t __attribute__((aligned(8))) fw_rev;    /**< fw_rev - Firmware Revision - Major, Minor, Subminor */
    uint16_t                             core_clk; /**< core_clk - Internal Clock Frequency (in MHz) */
    uint8_t                              dt; /**< dt - If set, Debug Trace is supported */
    uint8_t                              smkey; /**< smk - is system M Key supported in this FW version */
    uint8_t                              fw_hour; /**< fw_hour - Firmware timestamp - hour (displayed as a hexadecimal number) */
    uint8_t                              fw_minutes; /**< fw_minutes - Firmware timestamp - minutes (displayed as a hexadecimal number) */
    uint8_t                              fw_seconds; /**< fw_seconds - Firmware timestamp - seconds (displayed as a hexadecimal number) */
    uint16_t                             fw_year; /**< fw_year - Firmware timestamp - year (displayed as a hexadecimal number) */
    uint8_t                              fw_month; /**< fw_month - Firmware timestamp - month (displayed as a hexadecimal number) */
    uint8_t                              fw_day; /**< fw_day - Firmware timestamp - day (displayed as a hexadecimal number) */
    sxd_boolean_t                        fw_cap_ind_mod; /* fw supports independent-module */
    uint8_t                              dev_id; /**< dev_id - device id */
    uint64_t __attribute__((aligned(8))) frc_offset;
    uint8_t                              frc_bar;
    uint64_t __attribute__((aligned(8))) utc_sec_offset;
    uint8_t                              utc_sec_bar;
    uint64_t __attribute__((aligned(8))) utc_nsec_offset;
    uint8_t                              utc_nsec_bar;
    uint64_t __attribute__((aligned(8))) cr_dump_offset;
    uint8_t                              cr_dump_bar;
    uint32_t                             cap_dump_host_size_flat;
    uint32_t                             cap_dump_host_size_gw;
    uint32_t                             cap_dump_host_size_gdb;
};
struct ku_query_cq {
    uint8_t  eq_num;     /* 0 or 1 */
    uint8_t  reserved1;
    uint8_t  st;
    uint8_t  log_cq_size;
    uint16_t reserved2;
    uint16_t producer_counter;
    uint16_t reserved3;
    uint16_t last_notified_index;
    uint32_t reserved5;
    uint64_t dma_addr[8];     /* CQE buffer dma addresses */
};

/**
 * ku_mad_demux structure is used to store the mad demux info
 */
struct ku_mad_demux {
    uint8_t dev_id;     /**< dev_id - device id */
    uint8_t enable;     /**< enable - 1: enable, 0: disable */
};

/**
 * ku_ib_node_description structure is used to set IB node description in driver
 */
struct ku_ib_node_description {
    uint8_t dev_id; /**< dev_id - device id */
    uint8_t swid; /**< swid - Switch partition ID */
    uint8_t node_description[SX_IB_NODE_DESCRIPTION_LEN]; /**< IB node description string */
};

/**
 * ku_ib_swid_up_down structure is used to set IB swid up down events
 */
struct ku_ib_swid_up_down {
    uint8_t dev_id; /**< dev_id - device id */
    uint8_t swid; /**< swid - Switch partition ID */
    uint8_t up; /**<  True if swid went up, false if went down */
};


/**
 * ku_query_board_info structure is used to store the query board info parameters
 */
struct ku_query_board_info {
    sxd_boolean_t xm_exists;                      /**< Is XM connected */
    uint8_t       xm_num_local_ports;              /**< Number of ports connected to the XM */
    uint8_t       xm_local_ports[SX_XM_MAX_LOCAL_PORTS_LEN];     /**< List of ports connected to XM */
    uint16_t      vsd_vendor_id;                  /**< vsd_vendor_id - PCISIG Vendor ID */
    char          board_id[SX_BOARD_ID_LEN];      /**< board_id - The board id string */
    uint8_t       dev_id;                         /**< dev_id - device id */
    uint8_t       inta_pin;                       /**< Interrupt ack pin */
};

/**
 * ku_query_board_info structure is used to store the query board info parameters
 */
struct ku_system_m_key {
    uint64_t __attribute__((aligned(8))) system_m_key;  /**< system_m_key - system mkey  */
    uint8_t                              dev_id; /**< dev_id - device id */
};


/*
 * ku_query_rsrc structure is used to store the resource information
 */
struct ku_query_rsrc {
    ku_res_id_t                          rsrc_id; /* Resource ID */
    uint64_t __attribute__((aligned(8))) rsrc_val; /* Resource ID val */
    uint8_t                              dev_id; /**< dev_id - device id */
};

/**
 * ku_operation_tlv structure is used to store the operation TLV parameters
 */
struct ku_operation_tlv {
    uint8_t                              type; /**< type - operation */
    uint16_t                             length; /**< length - Length of TLV on DWORDs (4) */
    uint8_t                              dr; /**< dr - Direct route */
    uint8_t                              status; /**< status - Returned status. Must be 0 on Query/Write methods requests and Send/Traps. */
    uint16_t                             register_id; /**< register_id - Register ID within class */
    uint8_t                              r; /**< r - response (1) / request (0) */
    uint8_t                              method; /**< method - Method */
    uint8_t                              op_class; /**< op_class - Class of operation */
    uint64_t __attribute__((aligned(8))) tid;    /**< tid - Transaction ID */
};

/**
 * mhsr_health_mode enumerated type is used to note the MHSR health state.
 */
enum mhsr_health_mode {
    MHSR_HEALTH_MODE_FAILURE          = 0,
    MHSR_HEALTH_MODE_RESERVED         = 1,
    MHSR_HEALTH_MODE_NORMAL_OPERATION = 2,
    MHSR_HEALTH_MODE_DEFAULT_STATE    = 3,   /*boot/init*/
    MHSR_HEALTH_MODE_MIN              = MHSR_HEALTH_MODE_FAILURE,
    MHSR_HEALTH_MODE_MAX              = MHSR_HEALTH_MODE_DEFAULT_STATE,
};

/**
 * ku_mhsr_reg structure is used to store the MHSR register parameters
 */
struct ku_mhsr_reg {
    enum mhsr_health_mode health; /**< Software health state */
};

/**
 * profile_flood_mode_type enumerated type is used to note flood mode in profile
 */
enum profile_flood_mode_type {
    PROFILE_FLOOD_MODE_TYPE_SINGLE_ENTRY = 0,
    PROFILE_FLOOD_MODE_TYPE_USE_FID      = 1,
    PROFILE_FLOOD_MODE_TYPE_USE_VID      = 2,
    PROFILE_FLOOD_MODE_TYPE_MIXED_MODE   = 3,
    PROFILE_FLOOD_MODE_TYPE_CONTROL_MODE = 4,
    PROFILE_FLOOD_MODE_TYPE_CFF_MODE     = 5,
    PROFILE_FLOOD_MODE_TYPE_MAX,
};

typedef enum sxd_sftr_table_type {
    SXD_SFTR_TABLE_TYPE_ANY_TYPE_E = 0x0,
    SXD_SFTR_TABLE_TYPE_FID_E      = 0x4
} sxd_sftr_table_type_t;

/**
 * SFTR_MAX_PORTS define maximum ports supported by one SFTR reg access
 */
#define SFTR_MAX_PORTS 256

/**
 * ku_sftr_reg structure is used to store the SFTR register
 * parameters
 *
 */
struct ku_sftr_reg {
    uint8_t                  swid; /** swid - Switch partition ID */
    uint8_t                  flood_table; /**F-table index per type per switch*/
    uint16_t                 index;
    enum sxd_sftr_table_type table_type;
    uint16_t                 range; /**Range of entries to update*/
    uint16_t                 ports_bitmap[SFTR_MAX_PORTS];
    uint16_t                 mask_bitmap[SFTR_MAX_PORTS];
};

/**
 * ku_svpe_reg structure is used to store the SVPE register parameters
 */
struct ku_svpe_reg {
    uint8_t local_port; /** local_port - Local port number */
    uint8_t lp_msb; /**< lp_msb - local port MSBs */
    uint8_t vp_en;      /** vp_en - Virtual Port Enable */
};

/**
 * svpe_virtual_port_enable enumerated type is used to note
 * the virtual port enable.
 */
enum svpe_virtual_port_enable {
    SVPE_VIRTUAL_PORT_802_1Q = 0,
    SVPE_VIRTUAL_PORT_802_1D = 1,
};

/**
 * ku_slecr_reg structure is used to store the SLECR register parameters
 */
struct ku_slecr_reg {
    uint8_t swid; /** swid - Switch partition ID */
    uint8_t independent_learning; /** independent_learning - Independent Learning */
    uint8_t roaming_enable; /** roaming_enable - Roaming Enable */
};

/**
 * ku_spmlr_reg structure is used to store the SPMLR register parameters
 */
struct ku_spmlr_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb; /**< lp_msb - local port MSBs */
    uint8_t learn_enable; /** learn_enable - Enable learning on this port */
};

/**
 * ku_smid_reg_op enumerated type is used to note the
 * SMID operation.
 */
enum ku_smid_reg_op {
    SXD_SMID_OP_UPDATE = 0,
    SXD_SMID_OP_WRITE  = 1,
};

/**
 * SMID_MAX_PORTS define maximum ports supported by one SMID reg access
 */
#define SMID_MAX_PORTS 256

/**
 * ku_smid_reg structure is used to store the SMID register parameters
 */
struct ku_smid_reg {
    uint8_t  swid; /** swid - Switch partition ID */
    uint16_t mid; /** mid - Multicast Identifier */
    uint16_t ports_bitmap[SMID_MAX_PORTS]; /** ports_bitmap - Local port <i> sub port <j> membership */
    uint16_t mask_bitmap[SMID_MAX_PORTS]; /** mask_bitmap - Local port <i> sub port <j> mask */
    uint8_t  op; /** op - op == 0 legacy (SET), op == 1 CLEAR ALL*/
    uint8_t  smpe_valid; /** smpe_valid - SMPE validity bit */
    uint16_t smpe; /** smpe - Switch Multicast Port Egress */
};

/**
 * ku_svmlr_reg structure is used to store the SVMLR register parameters
 */
struct ku_svmlr_reg {
    uint8_t  swid; /** swid - Switch partition ID */
    uint16_t vid; /** vid - VLAN ID */
    uint8_t  learn_enable; /** learn_enable - Enable learning on this VLAN */
};

/**
 * SPVMLR_MAX_RECORDS define maximum records supported by one SPVMLR reg access
 */
#define SPVMLR_MAX_RECORDS 255

/**
 * ku_spvmlr_reg structure is used to store the SPVMLR register parameters
 */
typedef struct spvmlr_vlan_data {
    uint16_t vid;           /** vid - VLAN ID */
    uint8_t  learn_enable; /** learn_enable - Enable learning on this VLAN */
} spvmlr_vlan_data_t;

struct ku_spvmlr_reg {
    uint8_t            local_port; /** local_port - Local port to send the packet */
    uint8_t            lp_msb; /**< lp_msb - local port MSBs */
    uint8_t            num_rec; /** number of VLAN learm_mode records    */
    spvmlr_vlan_data_t vlan_data[SPVMLR_MAX_RECORDS];
};

/**
 * sxd_flow_counter_op enumerated type is used to note the
 * PFCA operation.
 */
enum sxd_flow_counter_op {
    SXD_PFCA_OP_NOP      = 0,
    SXD_PFCA_OP_ALLOCATE = 1,
    SXD_PFCA_OP_TEST     = 2,
    SXD_PFCA_OP_FREE     = 3,
};


/**
 * spgt_operation enumerated type is used to note the SPGT operation.
 */
enum spgt_operation {
    SPGT_OPERATION_ADD    = 0,
    SPGT_OPERATION_DELETE = 1,
    SPGT_OPERATION_EDIT   = 2,
};

/**
 * SPGT_MAX_PORTS define maximum ports supported by one SPGT reg access
 */
#define SPGT_MAX_PORTS 256

/**
 * ku_spgt_reg structure is used to store the SPGT register parameters
 */
struct ku_spgt_reg {
    enum spgt_operation operation;
    uint16_t            pgi;
    uint16_t            ports_bitmap[SPGT_MAX_PORTS];
    uint16_t            mask_bitmap[SPGT_MAX_PORTS];
};

/**
 * sfn_type enumerated type is used to note the SFN data type.
 */
enum sfn_type {
    SFN_TYPE_LEARNT_MAC            = 5,
    SFN_TYPE_LEARNT_MAC_LAG        = 6,
    SFN_TYPE_LEARNT_UNICAST_TUNNEL = 0xD,
    SFN_TYPE_AGED_MAC              = 7,
    SFN_TYPE_AGED_MAC_LAG          = 8,
    SFN_TYPE_AGED_UNICAST_TUNNEL   = 0xE,
};

/**
 * sfn_learnt_mac_data structure is used to store learnt MAC data.
 */
struct sfn_learnt_mac_data {
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              sub_port;
    uint16_t             fid;
    uint16_t             system_port;
    sxd_counter_set_t    counter_set;
};

/**
 * sfn_learnt_mac_lag_data structure is used to store learnt MAC LAG data.
 */
struct sfn_learnt_mac_lag_data {
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              sub_port;
    uint16_t             fid;
    uint16_t             lag_id;
    sxd_counter_set_t    counter_set;
};

/**
 * sfn_learnt_uc_tunnel_data structure is used to store learnt UC TUNNEL data.
 */
struct sfn_learnt_uc_tunnel_data {
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              udip_msb;
    uint16_t             fid;
    uint32_t             udip_lsb;
    sxd_counter_set_t    counter_set;
};


/**
 * sfn_aged_mac_data structure is used to store aged out MAC data.
 */
struct sfn_aged_mac_data {
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              sub_port;
    uint16_t             fid;
    uint16_t             system_port;
    sxd_counter_set_t    counter_set;
};

/**
 * sfn_aged_mac_lag_data structure is used to store aged out MAC LAG data.
 */
struct sfn_aged_mac_lag_data {
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              sub_port;
    uint16_t             fid;
    uint16_t             lag_id;
    sxd_counter_set_t    counter_set;
};

/**
 * sfn_aged_uc_tunnel_data structure is used to store aged out MAC tunnel data.
 */
struct sfn_aged_uc_tunnel_data {
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              udip_msb;
    uint16_t             fid;
    uint8_t              protocol;
    uint32_t             udip_lsb;
    sxd_counter_set_t    counter_set;
};


/**
 * sfn_record_data structure is used to store one SFN record data.
 */
struct sfn_record_data {
    enum sfn_type sfn_type;
    union {
        struct sfn_learnt_mac_data       lrnt_mac;
        struct sfn_learnt_mac_lag_data   lrnt_mac_lag;
        struct sfn_learnt_uc_tunnel_data lrnt_uc_tunnel;
        struct sfn_aged_mac_data         aged_mac;
        struct sfn_aged_mac_lag_data     aged_mac_lag;
        struct sfn_aged_uc_tunnel_data   aged_uc_tunnel;
    } sx_sfn_type;
};

/**
 * SFN_MAX_RECORDS define maximum records supported by one SFN
 */
#define SFN_MAX_RECORDS 64

/**
 * ku_sfn_reg structure is used to store the SFN register parameters
 */
struct ku_sfn_reg {
    uint8_t                swid;
    uint8_t                rec_type;
    uint8_t                end;
    uint8_t                num_records;
    struct sfn_record_data records[SFN_MAX_RECORDS];
};

/**
 * SFD_MAX_RECORDS define maximum records supported by one SFD
 */
#define SFD_MAX_RECORDS    SFN_MAX_RECORDS
#define SFD_MAX_RECORDS_32 32

/**
 * sfd_rec_type enumerated type is used to note the SFD/SFN rec
 * type.
 */
enum sfd_rec_type {
    SFD_REC_TYPE_0 = 0,
    SFD_REC_TYPE_1 = 1,
};

/**
 * sfd_type_t enumerated type is used to note the SFD data type.
 */
enum sfd_type {
    SFD_TYPE_UNICAST             = 0,
    SFD_TYPE_UNICAST_LAG         = 1,
    SFD_TYPE_MULTICAST           = 2,
    SFD_TYPE_LEARNT_MAC_E        = 5,
    SFD_TYPE_LEARNT_MAC_LAG_E    = 6,
    SFD_TYPE_AGED_MAC_E          = 7,
    SFD_TYPE_AGED_MAC_LAG_E      = 8,
    SFD_TYPE_UNICAST_TUNNEL      = 0xC,
    SFD_TYPE_LEARNT_MAC_TUNNEL_E = 0xD,
    SFD_TYPE_AGED_MAC_TUNNEL_E   = 0xE,
    SFD_TYPE_MULTICAST_TUNNEL    = 0xF,
};

/**
 * sfd_operation enumerated type is used to note the SFD operation.
 */
enum sfd_operation {
    SFD_OPERATION_DUMP_FDB                 = 0,
    SFD_OPERATION_QUERY                    = 1,
    SXD_OPERATION_QUERY_AND_CLEAR_ACTIVITY = 2,
    SFD_OPERATION_TEST                     = 0,
    SFD_OPERATION_ADD                      = 1,
    SFD_OPERATION_DELETE                   = 2,
    SXD_OPERATION_REMOVE_NOTIFICATION      = 3,
};

/**
 * sfd_policy enumerated type is used to note the SFD data replace policy.
 */
enum sfd_policy {
    SFD_POLICY_STATIC          = 0,
    SFD_POLICY_DYNAMIC_REMOTE  = 1,
    SFD_POLICY_DYNAMIC_LEARN   = 1, /**< Applicable for MC and MC tunnel records only, while it is equal to
                                     *    SFD_POLICY_DYNAMIC_REMOTE, applibs does not require updates,
                                     *    and POLICY_TO_MAC_TYPE can be used */
    SFD_POLICY_DYNAMIC_AGEABLE = 3,
    SFD_POLICY_INVALID         = -1,
};

/**
 * sfd_action enumerated type is used to note the SFD frame
 * action.
 */
enum sfd_action {
    SFD_ACTION_FORWARD_ONLY         = 0,
    SFD_ACTION_FORWARD_AND_TRAP     = 1,
    SFD_ACTION_TRAP_ONLY            = 2,
    SFD_ACTION_FORWARD_TO_IP_ROUTER = 3,
    SFD_ACTION_FORWARD_TO_FCF       = 4,
    SFD_ACTION_DISCARD              = 15,
    SFD_ACTION_INVALID              = -1,
};

/**
 * sfd_unicast_data structure is used to store
 * unicast data.
 */
struct sfd_unicast_data {
    enum sfd_policy      policy;
    uint8_t              activity;
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              set_vid;
    uint8_t              sub_port;
    union {
        uint16_t fid;
        uint16_t vid;
    } fid_vid_type;
    enum sfd_action   action;
    uint16_t          vid;
    uint16_t          system_port;
    sxd_counter_set_t counter_set;
};

/**
 * sfd_unicast_lag_data structure is used to store
 * unicast LAG data.
 */
struct sfd_unicast_lag_data {
    enum sfd_policy      policy;
    uint8_t              activity;
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              set_vid;
    uint8_t              sub_port;
    union {
        uint16_t fid;
        uint16_t vid;
    } fid_vid_type;
    enum sfd_action   action;
    uint16_t          lag_vid;
    uint16_t          lag_id;
    sxd_counter_set_t counter_set;
};

/**
 * sfd_multicast_data structure is used to store multicast data.
 */
struct sfd_multicast_data {
    enum sfd_policy      policy;
    struct sx_ether_addr mac;      /**< mac - Base MAC address */
    uint8_t              activity;
    uint16_t             pgi;
    uint16_t             vid;
    uint8_t              action;
    uint16_t             mid;
    sxd_counter_set_t    counter_set;
};

/**
 * sfd_uc_tunnel_data structure is used to store unicast tunnel data.
 */
struct sfd_uc_tunnel_data {
    enum sfd_policy      policy;
    uint8_t              activity;
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              udip_msb; /* if protocol is IPv4 - msb of dest IP; reserved for Ipv6 */
    uint16_t             fid;
    uint8_t              action;
    uint8_t              protocol;
    uint8_t              gen_enc;
    uint16_t             tunnel_port_lbf_bitmap;
    uint16_t             ecmp_size;
    uint32_t             udip_lsb; /* if protocol is IPv4 - lsb of dest IP; if IPv6 - pointer to dest IP */
    sxd_counter_set_t    counter_set;
};

/**
 * sfd_uc_tunnel_protocol enumerated type is used to note the SFD UC Tunnel protocol type.
 */
enum sfd_uc_tunnel_protocol {
    SFD_UC_TUNNEL_PROTOCOL_IPV4 = 0,
    SFD_UC_TUNNEL_PROTOCOL_IPV6 = 1,
};

/**
 * sfd_mc_tunnel_data structure is used to store multicast data.
 */
struct sfd_mc_tunnel_data {
    enum sfd_policy      policy;
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              activity;
    uint16_t             mid;
    uint16_t             fid;
    uint8_t              action;
    uint32_t             underlay_mc_ptr;
    uint16_t             tunnel_port_lbf_bitmap;
    uint16_t             ecmp_size;
    sxd_counter_set_t    counter_set;
};

/**
 * ku_sfd_reg structure is used to store the SFD register parameters
 */
struct ku_sfd_reg {
    uint8_t            swid;
    uint8_t            rec_type;
    uint8_t            offset;
    enum sfd_operation operation;
    uint32_t           record_locator;
    enum sfd_type      sfd_type[SFD_MAX_RECORDS];
    uint8_t            num_records;
    union sfd_data {
        struct sfd_unicast_data     uc;
        struct sfd_unicast_lag_data uc_lag;
        struct sfd_multicast_data   mc;
        struct sfd_uc_tunnel_data   uc_tunnel;
        struct sfd_mc_tunnel_data   mc_tunnel;
    } sfd_data_type[SFD_MAX_RECORDS];
};

/**
 * spvm_vlan_data structure is used to store SPVM vlan data
 * vlan data.
 */
typedef struct spvm_vlan_data {
    uint8_t  ingress_membership; /**< ingress_membership - Ingress membership in VLAN ID vid<i> */
    uint8_t  egress_membership; /**< egress_membership - Egress membership in VLAN ID vid<i> */
    uint8_t  untagged_membership; /**< untagged_membership - Untagged - port is an untagged member - egress transmission uses untagged frames on VID<i> */
    uint16_t vid; /** VLAN ID to be added/removed from port or for querying */
} spvm_vlan_data_t;

/**
 * ku_spvm_reg structure is used to store the SPVM register parameters
 */
struct ku_spvm_reg {
    uint8_t          prio_tagged;      /** untagged packets are being transmitted untagged OR priority-tagged */
    uint8_t          local_port;      /**< local_port - Chip local port ID */
    uint8_t          lp_msb;      /**< lp_msb - local port MSBs */
    uint8_t          num_vlans;      /**< num_vlans - Number of records to update. Each record contains: i, e, u, vid */
    spvm_vlan_data_t vlan_data[256];      /**< vlan_data - VLAN data */
};

/**
 * ku_spvid_reg structure is used to store the SPVID register parameters
 */
struct ku_spvid_reg {
    uint8_t  tport;
    uint8_t  local_port; /**< local_port - Chip local port ID */
    uint8_t  lp_msb; /**< lp_msb - local port MSBs */
    uint8_t  egr_et_set;
    uint8_t  et_vlan;  /**< EtherType used for when VLAN is pushed at ingress - 0 - Ethertype0 (default), 1 - Ethertype1 */
    uint16_t port_default_vid; /**< port_default_vid - Port default VID (default PVID is 001h) */
};

#define SXD_ETHERTYPE_MAX_COUNT (3)

/**
 * ku_spvc_reg structure is used to store the SPVC register parameters
 */
struct ku_spvc_reg {
    uint8_t local_port;      /**< local_port - Chip local port ID */
    uint8_t lp_msb; /**< lp_msb - local port MSBs */
    uint8_t inner_et[SXD_ETHERTYPE_MAX_COUNT];     /**< Inner Ethertype enabled*/
    uint8_t et[SXD_ETHERTYPE_MAX_COUNT];     /**< Ethertype enabled*/
};


/**
 * ku_sver_reg structure is used to store the SVER register parameters
 */
struct ku_sver_reg {
    uint16_t ether_type[SXD_ETHERTYPE_MAX_COUNT];
};

/* Ethertype 0 is always 0x8100 */
#define SXD_VLAN_ETHERTYPE_0 0x8100
/* Default Ethertype 1 is 0x88a8  */
#define SXD_VLAN_ETHERTYPE_1 0x88a8

/**
 * ku_spvtr_reg structure is used to store the SPVTR register parameters
 */
struct ku_spvtr_reg {
    uint8_t tport;
    uint8_t lp_msb; /**< lp_msb - local port MSBs */
    uint8_t local_port; /**< local_port - Chip local port ID */
    uint8_t ipprio_enable; /**< ipprio_enable - set to 1 to configure ipprio_mode */
    uint8_t ipvid_enable;  /**< ipvid_enable - set to 1 to configure ipvid_mode */
    uint8_t epvid_enable;  /**< epvid_enable - set to 1 to configure epvid_mode */
    uint8_t ipprio_mode; /**< ipprio_mode - Ingress Port Priority Mode */
    uint8_t epvid_mode; /**< epvid_mode - Egress Port VLAN-ID Mode */
    uint8_t ipvid_mode; /**< ipvid_mode - Ingress Port VLAN-ID Mode */
};

/**
 * PIFR_MAX_PORTS define maximum ports supported by one PIFR reg access
 */
#define PIFR_MAX_PORTS 256

/**
 * ku_pifr_reg structure is used to store the PIFR register parameters
 */
struct ku_pifr_reg {
    uint8_t table_id;   /**< table_id - 1 = BRIDGE_ONLY (L2) filter table, 0 = GLOBAL(L2/L3) filter table */
    uint8_t local_port; /**< local_port - Chip local port ID */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t ports_bitmap[PIFR_MAX_PORTS]; /**< 1 = filter packets coming from port[i], 0 = don't filter */
    uint8_t mask_bitmap[PIFR_MAX_PORTS];  /**< 1 = set port[i], 0 = don't set */
};

/**
 * ku_sspr_reg structure is used to store the SSPR register parameters
 */
struct ku_sspr_reg {
    uint8_t  is_master; /**< is_master - if set then this record describes the Master System Port */
    uint8_t  local_port; /**< local_port - Chip local port ID */
    uint8_t  lp_msb;     /**< local_port msb */
    uint8_t  sub_port; /**< sub_port - VEPA channel on Local Port */
    uint16_t system_port; /**< system_port - Multi SwitchX environment port ID */
};

/**
 * ku_scar_reg structure is used to store the SCAR register parameters
 */
struct ku_scar_reg {
    uint8_t log2_fdb_size; /**< log2_fdb_size - Capability: Log (base2) of the maximum FDB entries that are supported by the device */
};

typedef enum spms_mstp_state {
    SPMS_MSTP_STATE_DISCARDING = 1,
    SPMS_MSTP_STATE_LEARNING   = 2,
    SPMS_MSTP_STATE_FORWARDING = 3,
} spms_mstp_state_t;

/**
 * ku_spms_reg structure is used to store the SPMS register parameters
 */
struct ku_spms_reg {
    uint8_t           local_port;    /**< local_port - local port number */
    uint8_t           lp_msb;    /**< lp_msb - local port MSBs */
    spms_mstp_state_t state[4096];    /**< state - MSTP/RSTP State on VID<i> */
};

typedef enum sxd_span_sbib_buff_status {
    SXD_SBIB_MIRROR_BUFF_STATUS_NOT_REACH_SIZE_E = 0,
    SXD_SBIB_MIRROR_BUFF_STATUS_REACH_SIZE_E     = 1
} sxd_span_sbib_buff_status_t;

/**
 * ku_sbib_reg structure is used to store the SBIB register parameters
 */
struct ku_sbib_reg {
    uint8_t  type;      /**< type 0- Internal buffer allocated (Other values not supported) */
    uint8_t  local_port;    /**< local_port  */
    uint8_t  lp_msb;        /**< local_port msb */
    uint8_t  int_buff_index; /**< int_buff_index - Spectrum support only value = 0   */
    uint8_t  status;        /**< 0-buff status was NOT reach the requested size / 1-buff status reach target size */
    uint32_t buff_size;  /**< buffer size */
};


/**
 * ku_mpar_reg structure is used to store the MPAR register
 * parameters
 */
struct ku_mpar_reg {
    uint8_t  mngr_type; /**<  mngr_type - Manager Type*/
    uint8_t  local_port; /**< local_port   */
    uint8_t  lp_msb;     /**< local_port msb */
    uint8_t  i_e;    /**<  Ingress / Egress */
    uint8_t  enable; /**<  indicating the Port Analyzer enable*/
    uint8_t  pa_id;  /**< pa_id - port analyzer id */
    uint32_t probability_rate; /**< Sampling rate = 1 out of rate packets */
};

/**
 * ku_slcor_reg structure is used to store the SLCOR register parameters
 */
struct ku_slcor_reg {
    uint8_t  collector; /**< collector - Collector configuration */
    uint8_t  local_port; /**< local_port - local port number */
    uint8_t  lp_msb; /**< lp_msb - local port MSBs */
    uint16_t lag_id; /**< lag_id - LAG Identifier. Index into the LAG Descriptor table */
    uint8_t  port_index; /**< port index - port index in the LAG list.*/
};

/**
 * ku_slcr_reg structure is used to store the SLCR register parameters
 */
struct ku_slcr_reg {
    uint8_t  pp;
    uint8_t  local_port; /**< local_port - local port number */
    uint8_t  lp_msb;     /**< local_port msb */
    uint8_t  sh; /**< sh - Symmetric Hash */
    uint8_t  hash_type; /**< hash_type - Hash Type */
    uint32_t hash_configuration; /**< hash_configuration - LAG Hashing Configuration */
    uint32_t seed; /**< seed - LAG seed value */
};

/**
 * ku_slcr_v2_reg structure is used to store the SLCR_V2 register parameters
 */

typedef enum slcr_v2_hash_type {
    SXD_SLCR_V2_HASH_TYPE_CRC    = 0,
    SXD_SLCR_V2_HASH_TYPE_XOR    = 1,
    SXD_SLCR_V2_HASH_TYPE_RANDOM = 2,
    SXD_SLCR_V2_HASH_TYPE_CRC2   = 3, /* For Spectrum-2 and on */
} slcr_v2_hash_type_e;

typedef struct ku_slcr_v2_reg {
    uint8_t             pp; /**< pp - Per Port Configuration */
    uint8_t             local_port; /**< local_port - local port number */
    uint8_t             lp_msb; /**< lp_msb - local port MSBs */
    uint8_t             sh; /**< sh - Symmetric Hash */
    slcr_v2_hash_type_e type;        /**< type - Hash Type */
    uint32_t            seed; /**< seed - LAG seed value */
    uint32_t            general_fields; /**< general_fields - bitmask enabling fields */
    uint16_t            outer_header_enables;
    uint32_t            outer_header_fields_enable[5];
    uint16_t            inner_header_enables;
    uint64_t            inner_header_fields_enable;
} ku_slcr_v2_reg_t;

enum sldr_operation {
    SLDR_OPERATION_CREATE_LAG             = 0,
    SLDR_OPERATION_DESTROY_LAG            = 1,
    SLDR_OPERATION_ADD_PORT_LIST          = 2,
    SLDR_OPERATION_DEL_PORT_LIST          = 3,
    SLDR_OPERATION_LAG_REDIRECT           = 4,
    SLDR_OPERATION_FINE_GRAIN_LAG_ENABLE  = 5,
    SLDR_OPERATION_FINE_GRAIN_LAG_DISABLE = 6,
};

/**
 * ku_sldr_reg structure is used to store the SLDR register parameters
 */
struct ku_sldr_reg {
    enum sldr_operation operation; /**< operation - Operation */
    uint16_t            lag_id; /**< lag_id - LAG Identifier, the lag_id is the index into the LAG Descriptor table */
    uint16_t            dst_lag; /**< dst_lag - In Redirection, the destination LAG which lag_id points to */
    uint32_t            num_ports; /**< num_ports - The number of member ports of the LAG */
    uint16_t            ports[16]; /**< ports - Final destination of the packet */
    uint16_t            fgl_ptr; /**<  fgl_ptr - A pointer to the PGT table for fine grain LAG */
    uint16_t            fgl_size; /**<  fgl_size - PGT table allocation size for fine grain LAG */
};

/**
 * ku_sfdt_reg structure is used to store the SFDT register parameters
 */
struct ku_sfdt_reg {
    uint16_t fgl_ptr;            /**<  fgl_ptr - A pointer to the PGT table for fine grain LAG */
    uint8_t  size;            /**< size - number of port_member_lists */
    uint8_t  port_member_list[SXD_SFDT_MAX_PORT_NUM];            /**< port member list */
};

/**
 * ku_qprt_reg structure is used to store the QPRT register parameters
 */
struct ku_qprt_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t dei; /**< dei - DEI */
    uint8_t prio; /**< prio - PCP */
    uint8_t color; /**< color */
    uint8_t rprio; /**< rprio - Regenerated priority for received priority=<prio> */
};

/**
 * ku_qpdp_reg structure is used to store the QPDP register parameters
 */
struct ku_qpdp_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t color; /**< color - 0-green, 1-yellow, 2-red */
    uint8_t default_priority; /**< default_priority - Default Port priority (default 0) */
};

/**
 * ku_qpfcr_reg structure is used to store the QPFCR register parameters
 */
struct ku_qpfcr_reg {
    uint8_t local_port;
    uint8_t lp_msb;    /**< local_port msb */
    uint8_t traffic_class;
    uint8_t traffic_class_group;
    uint8_t min_threshold;
    uint8_t max_threshold;
};

/**
 * ku_qpcr_reg structure is used to store the QPCR register parameters
 */
struct ku_qpcr_reg {
    uint8_t port;   /**< local_port - Policer port number */
    uint8_t lp_msb; /**< local_port msb */
    uint8_t global_policer; /**< global -   1 - Global policer configuration
                             *  0 - Per port policer configuration */
    uint16_t pid; /**< policer_id - Policer ID */
    uint8_t  clear_counter; /**<clear_counter - 1-clear, 0-don't clear */
    uint8_t  add_counter; /**>add_counter - 1 - add violate_count to the counter*/
    uint8_t  color_aware; /**< color_aware - 1-color-aware, 0-no color-aware */
    uint8_t  use_bytes; /**< use_bytes -     1 - Meter based on bytes/sec
                         *  0 - Meter based on packets/sec */
    uint8_t ir_units; /**< cir and eir units. Supported devices: SwitchEN
                       *    0 - 10^6
                       *    1 - 10^3 */
    uint8_t type; /**< 00 - single-rate three color marking
                   *   01 - single-rate dual color
                   *   10 - dual-rate three color */
    uint8_t                              mode; /** < Operation Mode 00 - Policer 01 - Packet Sampling*/
    uint8_t                              committed_burst_size; /**< committed_burst_size - Committed Burst Size */
    uint8_t                              extended_burst_size; /**< extended_burst_size - Extended Burst Size */
    uint32_t                             committed_information_rate; /**< committed_information_rate - Committed Information Rate */
    uint32_t                             excess_information_rate; /**< excess_information_rate - Excess Information Rate */
    uint8_t                              exceed_action; /**< exceed_action - Action for exceed packets */
    uint8_t                              violate_action; /**< violate_action - Action for violate packets */
    uint64_t __attribute__((aligned(8))) violate_count; /**< violate_count - count the num of times violate_actions happened */
};

/**
 * ku_access_qpcr_reg structure is used to store the access
 * register QPCR command parameters
 */
struct ku_access_qpcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qpcr_reg      qpcr_reg; /**< qpcr_reg - qpcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_qpbr_reg structure is used to store the QPBR register parameters
 */
struct ku_qpbr_reg {
    uint8_t operation; /**< policer_operation - Operation */
    uint8_t port;      /**< local_port - Policer port number */
    uint8_t lp_msb;    /**< local_port msb */
    uint8_t global_policer; /**< global -   1 - Global policer configuration
                             *   0 - Per port policer configuration */
    uint16_t pid; /**< pid - Policer ID */
    uint8_t  unicast; /**< unicast - Meter ingress unicast packets */
    uint8_t  multicast; /**< multicast - Meter ingress multicast packets */
    uint8_t  broadcast; /**< broadcast - Meter ingress broadcast packets */
    uint8_t  unknown_unicast; /**< unknown_unicast - Meter ingress unknown unicast packets */
    uint8_t  unregistered_multicast; /**< unregistered_multicast - Meter ingress unregistered multicast packets */
};

/**
 * ku_plbf_reg structure is used to store the PLBF register
 * parameters
 */
struct ku_plbf_reg {
    uint8_t port;     /**< local_port - local port number */
    uint8_t lp_msb;   /**< local_port msb */
    uint8_t lbf_mode; /**< lbf_mode - Port loopback filtering state  */
};

/**
 * ku_qpts_reg structure is used to store the QPTS register parameters
 */
struct ku_qpts_reg {
    uint8_t port; /**< port - Port number */
    uint8_t lp_msb; /**< local_port msb */
    uint8_t trust_level; /**< trust_level -
                          *  0 - Trust Port
                          *  1 - Trust User Priority - this is the default value / trust L2
                          *  2 - Trust DSCP / trust L3
                          *  3 - Trust Both
                          *  Otherwise - reserved */
};

/**
 * ku_qpdpm_reg structure is used to store the QPDPM register parameters
 */
struct ku_qpdpm_reg {
    uint8_t local_port; /**< port - Port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t dscp_update[DSCP_CODES_NUMBER];    /**< dscp_update - whether to update this DSCP mapping in HW */
    uint8_t color[DSCP_CODES_NUMBER]; /**< color mapping per DSCP value */
    uint8_t priority[DSCP_CODES_NUMBER];       /**< priority mapping per DSCP value - Priority */
};

/**
 * ku_qepm_reg structure is used to store the QEPM register parameters
 */
struct ku_qepm_reg {
    uint8_t local_port; /**< port - Port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t exp_update[EXP_CODES_NUMBER];    /**< exp_update - whether to update this EXP mapping in HW */
    uint8_t ecn[EXP_CODES_NUMBER]; /**< the new packet ecn value */
    uint8_t color[EXP_CODES_NUMBER]; /**< color mapping per EXP value */
    uint8_t priority[EXP_CODES_NUMBER];       /**< priority mapping per EXP value - Priority */
};

/**
 * ku_qrwe_reg structure is used to store the QRWE register parameters
 */
struct ku_qrwe_reg {
    uint8_t local_port; /**local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t exp_rewrite; /**rewrite EXP enable */
    uint8_t dscp_rewrite; /**rewrite DSCP enable */
    uint8_t pcp_rewrite; /**rewrite PCP enable */
};

/**
 * qpem_color structure is used to store the QPEM register color parameter
 */
struct qpem_color {
    uint8_t enable_exp; /**< enable EXP mapping update */
    uint8_t exp; /**< EXP field in the outer level of the MPLS packet */
};

/**
 * qpem_ecn structure is used to store the QPEM register ecn parameter
 */
struct qpem_ecn {
    struct qpem_color color[3]; /**< EXP mapping for color */
};

/**
 * qpem_switch_prio structure is used to store the QPEM register switch prio parameter
 */
struct qpem_switch_prio {
    struct qpem_ecn ecn[4]; /**< EXP mapping for ECN */
};

/**
 * ku_qpem_reg structure is used to store the QPEM register parameters
 */
struct ku_qpem_reg {
    uint8_t                 local_port; /**local port number */
    uint8_t                 lp_msb;     /**< local_port msb */
    struct qpem_switch_prio switch_prio[16]; /** switch prio mapping */
};

/**
 * qpdsm_color structure is used to store the QPDSM register color parameter
 */
struct qpdsm_color {
    uint8_t enable_dscp; /**< enable DSCP mapping update */
    uint8_t dscp; /**< DSCP */
};

/**
 * qpdsm_switch_prio structure is used to store the QPDSM register switch prio parameter
 */
struct qpdsm_switch_prio {
    struct qpdsm_color color[3]; /**< DSCP mapping for ECN */
};

/**
 * ku_qpdsm_reg structure is used to store the QPDSM register parameters
 */
struct ku_qpdsm_reg {
    uint8_t                  local_port; /**local port number */
    uint8_t                  lp_msb;     /**< local_port msb */
    struct qpdsm_switch_prio switch_prio[16]; /** switch priority to dscp mapping */
};

/**
 * qppm_color structure is used to store the QPPM register color parameter
 */
struct qppm_color {
    uint8_t enable_pcp; /**< enable PCP mapping update */
    uint8_t dei; /**< DEI */
    uint8_t pcp; /**< PCP */
};

/**
 * qppm_switch_prio structure is used to store the QPPM register switch prio parameter
 */
struct qppm_switch_prio {
    struct qppm_color color[3]; /**< Switch Prio to PCP, DEI mapping */
};

/**
 * ku_qppm_reg structure is used to store the QPPM register parameters
 */
struct ku_qppm_reg {
    uint8_t                 local_port; /**local port number */
    uint8_t                 lp_msb;     /**< local_port msb */
    struct qppm_switch_prio switch_prio[16]; /** switch priority to pcp mapping */
};

/**
 * ku_qhll_reg structure is used to store the QHLL register parameters
 */
struct ku_qhll_reg {
    uint8_t local_port;
    uint8_t lp_msb;    /**< local_port msb */
    uint8_t hll_time;
    uint8_t stall_en;
    uint8_t stall_cnt;
};

/**
 * ku_access_qhll_reg structure is used to store the access
 * register QHLL command parameters
 */
struct ku_access_qhll_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qhll_reg      qhll_reg; /**< qhll_reg - QHLL register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};
/**
 * sxd_pvgt_operation_t enumerated type is used to note the
 * PVGT operation type.
 */
typedef enum sxd_pvgt_operation {
    SXD_PVGT_OP_ADD_VLAN_E    = 0,
    SXD_PVGT_OP_REMOVE_VLAN_E = 1,
} sxd_pvgt_operation_t;

/**
 * ku_msci_reg structure is used to store the MSCI register parameters
 */
struct ku_msci_reg {
    uint8_t  index;
    uint32_t version;
};

/**
 * sxd_mrsr_command enumerated type is used to note the MRSR command type
 */
enum sxd_mrsr_command {
    SXD_MRSR_CMD_DO_NOTHING           = 0,
    SXD_MRSR_CMD_SW_RESET             = 1,
    SXD_MRSR_CMD_ENCLOSURE_RESET      = 3,
    SXD_MRSR_CMD_SHUTDOWN             = 4,
    SXD_MRSR_CMD_RESET_AT_PCI_DISABLE = 6
};

/**
 * ku_mrsr_reg structure is used to store the MRSR register parameters
 */
struct ku_mrsr_reg {
    enum sxd_mrsr_command command;
};

/**
 * sxd_pagt_operation_t enumerated type is used to note the
 * PAGT operation type.
 */
typedef enum sxd_pagt_operation {
    SXD_PAGT_OP_CREATE_E     = 0,
    SXD_PAGT_OP_DEALLOCATE_E = 1,
} sxd_pagt_operation_t;

/**
 * pagt_acl_id_record structure is used to store the PAGT register acl id record parameter
 */
struct pagt_acl_id_record {
    uint8_t  multi; /**< multi ACL */
    uint8_t  commit; /**< ACL commit */
    uint16_t acl_id; /**< ACL identifier */
};

/**
 * ku_pagt_reg structure is used to store the PAGT register parameters
 */
typedef struct ku_pagt_reg {
    uint8_t                   egress;
    uint8_t                   size;
    uint16_t                  acl_group_id;
    struct pagt_acl_id_record acl_ids[SXD_MAX_ACL_IN_GROUP];
} ku_pagt_reg_t;

/**
 * sxd_pvbt_operation enumerated type is used to note the
 * PVBT operation type.
 */
typedef enum sxd_pvbt_operation {
    SXD_PVBT_OP_BIND_E   = 0,
    SXD_PVBT_OP_UNBIND_E = 1,
} sxd_pvbt_operation_t;

/**
 * sxd_ppbt_operation enumerated type is used to note the
 * PPBT operation type.
 */
typedef enum sxd_ppbt_operation {
    SXD_PPBT_OP_BIND_E   = 0,
    SXD_PPBT_OP_UNBIND_E = 1,
    SXD_PPBT_OP_ADD_E    = 2,
} sxd_ppbt_operation_t;

typedef enum sxd_flex_acl_action_type {
    SXD_ACTION_TYPE_NULL_E                     = 0,
    SXD_ACTION_TYPE_MAC_E                      = 1,
    SXD_ACTION_TYPE_VLAN_E                     = 2,
    SXD_ACTION_TYPE_TRAP_E                     = 3,
    SXD_ACTION_TYPE_TRAP_W_USER_DEF_VAL_E      = 4,
    SXD_ACTION_TYPE_PORT_FILTER_E              = 5,
    SXD_ACTION_TYPE_QOS_E                      = 6,
    SXD_ACTION_TYPE_FORWARD_E                  = 7,
    SXD_ACTION_TYPE_POLICING_COUNTING_E        = 8,
    SXD_ACTION_TYPE_META_DATA_E                = 9,
    SXD_ACTION_TYPE_UC_ROUTER_AND_MPLS_E       = 10,
    SXD_ACTION_TYPE_VXLAN_E                    = 11,
    SXD_ACTION_TYPE_MPLS_E                     = 12,
    SXD_ACTION_TYPE_HASH_E                     = 13,
    SXD_ACTION_TYPE_VIRTUAL_FORWARDING_E       = 14,
    SXD_ACTION_TYPE_IGNORE_E                   = 15,
    SXD_ACTION_TYPE_MC_E                       = 16,
    SXD_ACTION_TYPE_SIP_DIP_E                  = 17,
    SXD_ACTION_TYPE_L4_PORT_E                  = 18,
    SXD_ACTION_TYPE_MIRROR_SAMPLER_E           = 19,
    SXD_ACTION_TYPE_UNDEFINDED_E               = 20,
    SXD_ACTION_TYPE_PORT_FILTER_EXT_E          = 21,
    SXD_ACTION_TYPE_PORT_FILTER_EXT2_E         = 22,
    SXD_ACTION_TYPE_FLEX_MODIFIER_EMT_E        = 23,
    SXD_ACTION_TYPE_CUSTOM_BYTES_ALU_IMM_E     = 24,
    SXD_ACTION_TYPE_CUSTOM_BYTES_ALU_REG_E     = 25,
    SXD_ACTION_TYPE_CUSTOM_BYTES_ALU_FIELD_E   = 26,
    SXD_ACTION_TYPE_CUSTOM_BYTES_MOVE_E        = 27,
    SXD_ACTION_TYPE_FIELDS_SET_IMM_E           = 28,
    SXD_ACTION_TYPE_FIELDS_MOVE_E              = 29,
    SXD_ACTION_TYPE_BUFFER_SNAP_E              = 30,
    SXD_ACTION_TYPE_TRUNCATION_E               = 33,
    SXD_ACTION_TYPE_FS_DB_E                    = 34,
    SXD_ACTION_TYPE_POLICING_COUNTING_BY_REF_E = 36,
    SXD_ACTION_TYPE_FLOW_ESTIMATOR_E           = 37,
    SXD_ACTION_TYPE_LAST_E                     = 38
} sxd_flex_acl_action_type_t;

/**
 * sxd_acl_ptce_action_type enumerated type is used to
 * note the PTCE action type.
 */
typedef enum sxd_acl_ptce_action_type {
    SXD_PTCE_ACTION_TYPE_DEFAULT_E  = 0,
    SXD_PTCE_ACTION_TYPE_EXTENDED_E = 1,
} sxd_acl_ptce_action_type_t;

/**
 * sxd_acl_ptce_key_type enumerated type is used to note
 * the PTCE key type.
 */
typedef enum sxd_acl_ptce_key_type {
    SXD_PTCE_KEY_TYPE_IPV4_FULL_E     = 0,
    SXD_PTCE_KEY_TYPE_IPV6_FULL_E     = 1,
    SXD_PTCE_KEY_TYPE_MAC_FULL_E      = 2,
    SXD_PTCE_KEY_TYPE_MAC_IPV4_FULL_E = 3,
    SXD_PTCE_KEY_TYPE_MAC_SHORT_E     = 5,
    SXD_PTCE_KEY_TYPE_FCOE_FULL_E     = 32
} sxd_acl_ptce_key_type_t;

/**
 * sxd_ptce_trap_action enumerated type is used to note
 * the PTCE action trap action type.
 */
typedef enum sxd_ptce_trap_action {
    SXD_PTCE_TRAP_ACTION_PERMIT_E         = 0,
    SXD_PTCE_TRAP_ACTION_SOFT_DROP_E      = 1,
    SXD_PTCE_TRAP_ACTION_TRAP_E           = 2,
    SXD_PTCE_TRAP_ACTION_SOFT_DROP_TRAP_E = 3,
    SXD_PTCE_TRAP_ACTION_DENY_E           = 4,
} sxd_ptce_trap_action_t;

/**
 * sxd_ptce_vlan_action enumerated type is used to note
 * the PTCE action vlan action type.
 */
typedef enum sxd_ptce_vlan_action {
    SXD_PTCE_VLAN_ACTION_NOP_E                   = 0,
    SXD_PTCE_VLAN_ACTION_PUSH_VID_KEEP_PRIO_E    = 0x8,
    SXD_PTCE_VLAN_ACTION_PUSH_VLAN_E             = 0xC,
    SXD_PTCE_VLAN_ACTION_REPLACE_VID_KEEP_PRIO_E = 0x18,
    SXD_PTCE_VLAN_ACTION_REPLACE_VID_PRIO_E      = 0x1c,
} sxd_ptce_vlan_action_t;

/**
 * sxd_ptce_ipv4_full_key structure is used to store PTCE
 * IPv4 Full key.
 */
typedef struct sxd_ptce_ipv4_full_key {
    uint32_t dst_ip;
    uint32_t src_ip;
    uint16_t src_l4_port;
    uint16_t dst_l4_port;
    uint8_t  ttl;
    uint8_t  tcp_flags;
    uint8_t  ip_proto;
    uint8_t  ip_tos;
    uint16_t flags;
    uint8_t  ipv6_ext;
    uint16_t dst_sys_port;
    uint16_t src_sys_port;
    uint16_t l4_port_range;
    uint32_t flow_label;
} sxd_ptce_ipv4_full_key_t;

/**
 * sxd_ptce_ipv6_full_key structure is used to store PTCE
 * IPv6 Full key.
 */
typedef struct sxd_ptce_ipv6_full_key {
    uint32_t dst_ip[4];
    uint32_t src_ip[4];
    uint16_t src_l4_port;
    uint16_t dst_l4_port;
    uint8_t  ttl;
    uint8_t  tcp_flags;
    uint8_t  ip_proto;
    uint8_t  ip_tos;
    uint16_t flags;
    uint8_t  ipv6_ext;
    uint16_t dst_sys_port;
    uint16_t src_sys_port;
    uint16_t l4_port_range;
    uint32_t flow_label;
} sxd_ptce_ipv6_full_key_t;

/**
 * sxd_ptce_operation enumerated type is used to note the
 * op type.
 */
typedef enum sxd_ptce_operation {
    SXD_PTCE_OP_WRITE          = 0,
    SXD_PTCE_OP_READ           = 0,
    SXD_PTCE_OP_CLEAR_ON_READ  = 1,
    SXD_PTCE_OP_UPDATE         = 1,
    SXD_PTCE_OP_CLEAR_ACTIVITY = 2,
    SXD_PTCE_OP_WRITE_CLEAR    = 3
} sxd_ptce_operation_t;


/**
 * sxd_ptce_mac_full_key structure is used to store PTCE
 * MAC Full key.
 */
typedef struct sxd_ptce_mac_full_key {
    uint8_t  dmac[6];
    uint8_t  smac[6];
    uint16_t ethertype;
    uint16_t vid;
    uint8_t  cfi;
    uint8_t  prio;
    uint8_t  vlan_tagged;
    uint8_t  vlan_valid;
    uint8_t  dmac_type;
    uint32_t slag;
    uint16_t src_sys_port;
    uint16_t dst_sys_port;
} sxd_ptce_mac_full_key_t;

/**
 * sxd_ptce_mac_short_key structure is used to store PTCE
 * MAC short key.
 */
typedef struct sxd_ptce_mac_short_key {
    uint8_t  dmac[6];
    uint8_t  smac[6];
    uint16_t vid;
    uint8_t  cfi;
    uint8_t  prio;
    uint8_t  vlan_tagged;
    uint8_t  vlan_valid;
    uint8_t  dmac_type;
    uint32_t slag;
    uint16_t src_sys_port;
} sxd_ptce_mac_short_key_t;

/**
 * sxd_ptce_mac_full_key structure is used to store PTCE
 * MAC IPv4 Full key.
 */
typedef struct sxd_ptce_mac_ipv4_full_key {
    uint8_t  dmac[6];
    uint8_t  smac[6];
    uint16_t ethertype;
    uint16_t vid;
    uint8_t  prio;
    uint16_t mac_flags;
    uint8_t  vlan_type;
    uint8_t  vlan_valid;
    uint16_t src_sys_port;
    uint32_t dst_ip;
    uint32_t src_ip;
    uint16_t src_l4_port;
    uint16_t dst_l4_port;
    uint8_t  ip_flags;
    uint8_t  ip_proto;
    uint8_t  ip_tos;
    uint8_t  slag;
} sxd_ptce_mac_ipv4_full_key_t;

/**
 * sxd_ptce_fcoe_full_key structure is used to store PTCE
 * FCoE Full key.
 */
typedef struct sxd_ptce_fcoe_full_key {
    uint8_t  dmac[6];
    uint8_t  smac[6];
    uint16_t vid;
    uint8_t  prio;
    uint8_t  vlan_type;
    uint8_t  slag;
    uint8_t  vlan_valid;
    uint16_t src_sys_port;
    uint8_t  d_id[3];
    uint8_t  s_id[3];
    uint16_t ox_id;
    uint16_t rx_id;
    uint8_t  is_fc;
    uint8_t  r_ctl;
    uint8_t  type;
} sxd_ptce_fcoe_full_key_t;

/**
 * sxd_ptce_default_action structure is used to store
 * PTCE Default action set.
 */
typedef struct sxd_ptce_default_action {
    sxd_ptce_trap_action_t trap;
    uint8_t                trap_group;
    uint16_t               trap_id;
    uint8_t                mirror;
    uint8_t                mirror_dst;
    sxd_ptce_vlan_action_t vlan_prio_tclass_op;
    uint16_t               vid;
    uint8_t                prio;
    uint8_t                etclass;
    uint8_t                stclass;
    uint32_t               flow_counter;
    uint8_t                policer_port;
    uint8_t                g_policer;
    uint8_t                pid;
    uint8_t                nr;
    uint8_t                no_learning;
} sxd_ptce_default_action_t;


/**
 * sxd_ptce_extended_action_t structure is used to store PTCE
 * Extended action set.
 */
typedef struct sxd_ptce_extended_action {
    uint8_t  pbs_en;
    uint16_t pbs_index;
} sxd_ptce_extended_action_t;

/**
 * ku_ptce_reg structure is used to store the PTCE register parameters
 */
typedef struct ku_ptce_reg {
    sxd_acl_ptce_key_type_t    key_type;
    sxd_acl_ptce_action_type_t action_set_type;
    uint8_t                    valid;
    uint8_t                    activity;
    sxd_ptce_operation_t       op;
    uint16_t                   offset;
    uint8_t                    tcam_region_info[SXD_ACL_INFO_SIZE_BYTES];
    union {
        sxd_ptce_ipv4_full_key_t     ipv4;
        sxd_ptce_ipv6_full_key_t     ipv6;
        sxd_ptce_mac_full_key_t      mac_full;
        sxd_ptce_mac_short_key_t     mac_short;
        sxd_ptce_mac_ipv4_full_key_t mac_ipv4_full;
        sxd_ptce_fcoe_full_key_t     fcoe_full;
    } sxd_ptce_key;
    union {
        sxd_ptce_ipv4_full_key_t     ipv4;
        sxd_ptce_ipv6_full_key_t     ipv6;
        sxd_ptce_mac_full_key_t      mac_full;
        sxd_ptce_mac_short_key_t     mac_short;
        sxd_ptce_mac_ipv4_full_key_t mac_ipv4_full;
        sxd_ptce_fcoe_full_key_t     fcoe_full;
    } sxd_ptce_mask;
    struct {
        sxd_ptce_default_action_t  default_action;
        sxd_ptce_extended_action_t extended_action;
    } sxd_ptce_action_set;
    uint8_t  terminate;
    uint8_t  asbind;
    uint8_t  next_is_group;
    uint16_t next_acl_id_grp_id;
} ku_ptce_reg_t;

/**
 *  * ku_ptce2_reg structure is used to store the PTCE register parameters
 *   */

typedef enum sxd_flex_defer {
    SXD_FLEX_DEFER_ACTION_APPLIED_IMMEDITELY_E = 0,
    SXD_FLEX_DEFER_ACTION_WRITTEN_TO_ACTION_SET_E
} sxd_flex_defer_t;

typedef enum sxd_flex_acl_l2_dmac_type_ {
    SXD_FLEX_ACL_L2_DMAC_TYPE_MULTICAST = 0,
    SXD_FLEX_ACL_L2_DMAC_TYPE_BROADCAST = 1,
    SXD_FLEX_ACL_L2_DMAC_TYPE_UNICAST   = 2,
} sxd_flex_acl_l2_dmac_type_t;

typedef enum sxd_flex_acl_l3_type_ {
    SXD_FLEX_ACL_L3_TYPE_IPV4  = 0,
    SXD_FLEX_ACL_L3_TYPE_IPV6  = 1,
    SXD_FLEX_ACL_L3_TYPE_ARP   = 2,
    SXD_FLEX_ACL_L3_TYPE_OTHER = 3,
} sxd_flex_acl_l3_type_t;

typedef enum sxd_flex_acl_l4_type_ {
    SXD_FLEX_ACL_L4_TYPE_TCP      = 1 << 0,
    SXD_FLEX_ACL_L4_TYPE_UDP      = 1 << 1,
    SXD_FLEX_ACL_L4_TYPE_RESERVED = 1 << 2,
    SXD_FLEX_ACL_L4_TYPE_OTHER    = 1 << 3,
} sxd_flex_acl_l4_type_t;

typedef enum sxd_flex_acl_discard_state_ {
    SXD_FLEX_ACL_DISCARD_STATE_FORWARD            = 0,
    SXD_FLEX_ACL_DISCARD_STATE_SOFT_DISCARD_ERROR = 1,
    SXD_FLEX_ACL_DISCARD_STATE_DISCARD            = 2,
    SXD_FLEX_ACL_DISCARD_STATE_DICARD_ERROR       = 3,
    SXD_FLEX_ACL_DISCARD_STATE_LAST,
} sxd_flex_acl_discard_state_t;

typedef enum sxd_flex_acl_l4_type_extended_ {
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_NONE    = 0,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_RAW     = 1,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_TCP     = 2,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_UDP     = 3,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_BTH     = 4,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_BTHOUDP = 5,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_ICMP    = 6,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_IGMP    = 7,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_AH      = 8,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_ESP     = 9,
} sxd_flex_acl_l4_type_extended_t;

typedef enum sxd_flex_acl_nd_sll_or_tll_valid_ {
    SXD_FLEX_ACL_NO_ND_SLL_OR_TTL = 0,
    SXD_FLEX_ACL_ND_SLL           = 1,
    SXD_FLEX_ACL_ND_TLL           = 2,
} sxd_flex_acl_nd_sll_or_tll_valid;

typedef enum sxd_flex_acl_mc_bc_or_flood_type_ {
    SXD_FLEX_ACL_MC_TYPE_FLOOD_FOR_UC              = 1 << 0,
    SXD_FLEX_ACL_MC_TYPE_BC                        = 1 << 1,
    SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_NON_IP           = 1 << 2,
    SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_IPV4             = 1 << 3,
    SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_IPV4_LINK_LOCAL  = 1 << 4,
    SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_IPV6             = 1 << 5,
    SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_IPV6_NODES_LOCAL = 1 << 6,
    SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_ROCE_V1          = 1 << 7,
} sxd_flex_acl_mc_bc_or_flood_type;

typedef enum sxd_flex_acl_ipv6_extension_headers_ {
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_ROUTING             = 0,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_FRAGMENT            = 1,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_DESTINATION_OPTIONS = 2,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_AUTHENTICATION      = 3,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_ESP                 = 4,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_MOBILITY            = 5,
} sxd_flex_acl_ipv6_extension_headers_t;

typedef enum sxd_flex_ttl_cmd_ {
    SXD_FLEX_TTL_CMD_DO_NOTHING_E    = 0,
    SXD_FLEX_TTL_CMD_SET_TTL_VALUE_E = 1,
    SXD_FLEX_TTL_CMD_DECREMENT_E     = 2,
    SXD_FLEX_TTL_CMD_LAST_E,
} sxd_flex_ttl_cmd_t;

typedef enum sxd_flex_mac_cmd {
    SXD_FLEX_MAC_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_MAC_CMD_TYPE_SET_SMAC_E,
    SXD_FLEX_MAC_CMD_TYPE_SET_DMAC_E,
    SXD_FLEX_MAC_CMD_TYPE_LAST_E
} sxd_flex_mac_cmd_t;

typedef struct sxd_mac_flex_action {
    sxd_flex_defer_t   defer;
    sxd_flex_ttl_cmd_t ttl_cmd;
    uint8_t            ttl_value;
    sxd_flex_mac_cmd_t mac_cmd;
    uint8_t            mac[6];
} sxd_mac_flex_action_t;

typedef enum sxd_flex_vlan_tag_cmd {
    SXD_FLEX_VLAN_TAG_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_VLAN_TAG_CMD_TYPE_PUSH_OUTER_E,
    SXD_FLEX_VLAN_TAG_CMD_TYPE_POP_OUTER_E,
    SXD_FLEX_VLAN_TAG_CMD_TYPE_LAST_E,
} sxd_flex_vlan_tag_cmd_t;

typedef enum sxd_flex_vid_cmd {
    SXD_FLEX_VID_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_VID_CMD_TYPE_SET_OUTER_E,
    SXD_FLEX_VID_CMD_TYPE_SET_INNER_E,
    SXD_FLEX_VID_CMD_TYPE_COPY_FROM_OUTER_TO_INNER_E,
    SXD_FLEX_VID_CMD_TYPE_COPY_FROM_INNER_TO_OUTER_E,
    SXD_FLEX_VID_CMD_TYPE_SWAP_INNER_OUTER_E,
    SXD_FLEX_VID_CMD_TYPE_LAST_E
} sxd_flex_vid_cmd_t;

#define SXD_FLEX_ACL_VLAN_ETHERTYPE_FROM_EGRESS_PORT_INDEX 3

typedef enum sxd_flex_vlan_ethertype_cmd {
    SXD_FLEX_VLAN_ETHERTYPE_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_VLAN_ETHERTYPE_CMD_TYPE_SET_OUTER_E,
    SXD_FLEX_VLAN_ETHERTYPE_CMD_TYPE_SET_INNER_E,
    SXD_FLEX_VLAN_ETHERTYPE_CMD_TYPE_COPY_FROM_OUTER_TO_INNER_E,
    SXD_FLEX_VLAN_ETHERTYPE_CMD_TYPE_COPY_FROM_INNER_TO_OUTER_E,
    SXD_FLEX_VLAN_ETHERTYPE_CMD_TYPE_SWAP_INNER_OUTER_E,
    SXD_FLEX_VLAN_ETHERTYPE_CMD_TYPE_LAST_E
} sxd_flex_vlan_ethertype_cmd_t;

typedef enum sxd_flex_vlan_prio_cmd {
    SXD_FLEX_VLAN_PRIO_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_VLAN_PRIO_CMD_TYPE_SET_OUTER_E,
    SXD_FLEX_VLAN_PRIO_CMD_TYPE_SET_INNER_E,
    SXD_FLEX_VLAN_PRIO_CMD_TYPE_COPY_FROM_OUTER_TO_INNER_E,
    SXD_FLEX_VLAN_PRIO_CMD_TYPE_COPY_FROM_INNER_TO_OUTER_E,
    SXD_FLEX_VLAN_PRIO_CMD_TYPE_SWAP_INNER_OUTER_E,
    SXD_FLEX_VLAN_PRIO_CMD_TYPE_LAST_E
} sxd_flex_vlan_prio_cmd_t;

typedef enum sxd_flex_dei_cmd {
    SXD_FLEX_DEI_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_DEI_CMD_TYPE_SET_OUTER_E,
    SXD_FLEX_DEI_CMD_TYPE_SET_INNER_E,
    SXD_FLEX_DEI_CMD_TYPE_COPY_FROM_OUTER_TO_INNER_E,
    SXD_FLEX_DEI_CMD_TYPE_COPY_FROM_INNER_TO_OUTER_E,
    SXD_FLEX_DEI_CMD_TYPE_SWAP_INNER_OUTER_E,
    SXD_FLEX_DEI_CMD_TYPE_LAST_E
} sxd_flex_dei_cmd_t;

typedef enum sxd_flex_ether_type {
    SXD_FLEX_ETHER_TYPE_0_E = 0,
    SXD_FLEX_ETHER_TYPE_1_E,
    SXD_FLEX_ETHER_TYPE_2_E
} sxd_flex_ether_type_t;

typedef struct sxd_vlan_flex_action {
    sxd_flex_defer_t              defer;
    sxd_flex_vlan_tag_cmd_t       v_tag_cmd;
    sxd_flex_vid_cmd_t            vid_cmd;
    uint16_t                      vid_val;
    sxd_flex_vlan_ethertype_cmd_t ethertype_cmd;
    sxd_flex_ether_type_t         ethertype_val;
    uint8_t                       pcp_val;
    sxd_flex_vlan_prio_cmd_t      pcp_cmd;
    sxd_flex_dei_cmd_t            dei_cmd;
    uint8_t                       dei_val;
} sxd_vlan_flex_action_t;

typedef enum sxd_flex_trap_forward_action_val {
    SXD_FLEX_TRAP_FORWARD_ACTION_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_TRAP_FORWARD_ACTION_TYPE_FORWARD_DO_NOTHING_CLEAR_SOFT_DROP_E,
    SXD_FLEX_TRAP_FORWARD_ACTION_TYPE_SOFT_DROP_ERROR_E,
    SXD_FLEX_TRAP_FORWARD_ACTION_TYPE_DISCARD_HARD_DROP_E,
    SXD_FLEX_TRAP_FORWARD_ACTION_TYPE_DISCARD_HARD_DROP_ERROR_E,
    SXD_FLEX_TRAP_FORWARD_ACTION_TYPE_LAST_E,
} sxd_flex_trap_forward_action_val_t;

typedef enum sxd_flex_trap_action_val {
    SXD_FLEX_TRAP_ACTION_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_TRAP_ACTION_TYPE_SOFT_DISCARD_CLEAR_TRAP_E,
    SXD_FLEX_TRAP_ACTION_TYPE_TRAP_E,
    SXD_FLEX_TRAP_ACTION_TYPE_DISCARD_NO_TRAP_E,
    SXD_FLEX_TRAP_ACTION_TYPE_LAST_E,
} sxd_flex_trap_action_val_t;

typedef struct sxd_trap_flex_action {
    sxd_flex_defer_t                   defer;
    sxd_flex_trap_forward_action_val_t forward_action;
    sxd_flex_trap_action_val_t         trap_action;
    uint16_t                           trap_id;
    uint8_t                            mirror_agent;
    uint8_t                            mirror_enable;
    uint32_t                           user_def_val;
    uint8_t                            preserve_user_def_val;
} sxd_trap_flex_action_t;

typedef struct sxd_port_filter_flex_action {
    uint32_t egress_port_list_0_31;
    uint32_t egress_port_list_32_63;
    uint8_t  egress_port_list_64;
} sxd_port_filter_flex_action_t;

typedef struct sxd_port_filter_ext_flex_action {
    uint32_t egress_port_list_65_96;
    uint32_t egress_port_list_97_128;
} sxd_port_filter_ext_flex_action_t;

#define PORT_FILTER_EXT2_FLEX_ACTION_LIST_SIZE         32
#define PORT_FILTER_EXT2_FLEX_ACTION_NUM_LISTS_IN_PAGE 2
#define PORT_FILTER_EXT2_FLEX_ACTION_PAGE_SIZE \
    (PORT_FILTER_EXT2_FLEX_ACTION_LIST_SIZE * PORT_FILTER_EXT2_FLEX_ACTION_NUM_LISTS_IN_PAGE)
#define PORT_FILTER_EXT2_FLEX_ACTION_HW_PORT_TO_PAGE(hw_port) \
    (((hw_port) - 1) / PORT_FILTER_EXT2_FLEX_ACTION_PAGE_SIZE)
#define PORT_FILTER_EXT2_FLEX_ACTION_HW_PORT_TO_OFFSET_IN_PAGE(hw_port) \
    (((hw_port) - 1) % PORT_FILTER_EXT2_FLEX_ACTION_PAGE_SIZE)
#define PORT_FILTER_EXT2_FLEX_ACTION_HW_PORT_TO_LIST(hw_port) \
    (PORT_FILTER_EXT2_FLEX_ACTION_HW_PORT_TO_OFFSET_IN_PAGE(hw_port) / PORT_FILTER_EXT2_FLEX_ACTION_LIST_SIZE)
#define PORT_FILTER_EXT2_FLEX_ACTION_HW_PORT_TO_OFFSET_IN_LIST(hw_port) \
    (PORT_FILTER_EXT2_FLEX_ACTION_HW_PORT_TO_OFFSET_IN_PAGE(hw_port) % PORT_FILTER_EXT2_FLEX_ACTION_LIST_SIZE)

typedef struct sxd_port_filter_ext2_flex_action {
    uint8_t  page;
    uint32_t egress_port_list_0_31;
    uint32_t egress_port_list_32_63;
} sxd_port_filter_ext2_flex_action_t;

typedef enum sxd_flex_dscp_cmd {
    SXD_FLEX_DSCP_CMD_TYPE_DO_NOTHING_E      = 0,
    SXD_FLEX_DSCP_CMD_TYPE_SET_3_LSB_BITS_E  = 1,
    SXD_FLEX_DSCP_CMD_TYPE_SET_3_MSB_BITS_E  = 2,
    SXD_FLEX_DSCP_CMD_TYPE_SET_DSCP_6_BITS_E = 3,
    SXD_FLEX_DSCP_CMD_TYPE_LAST_E,
} sxd_flex_dscp_cmd_t;

typedef enum sxd_flex_ecn_cmd {
    SXD_FLEX_ECN_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_ECN_CMD_TYPE_SET_OUTER_ECN_E,
    SXD_FLEX_ECN_CMD_TYPE_SET_INNER_ECN_E,
    SXD_FLEX_ECN_CMD_TYPE_COPY_ENC_OUTER_TO_INNER_E,
    SXD_FLEX_ECN_CMD_TYPE_COPY_ENC_INNER_TO_OUTER_E,
    SXD_FLEX_ECN_CMD_TYPE_SWAP_INNER_AND_OUTER_E,
    SXD_FLEX_ECN_CMD_TYPE_LAST_E
} sxd_flex_ecn_cmd_t;

typedef enum sxd_flex_switch_prio_cmd {
    SXD_FLEX_SWITCH_PRIO_CMD_TYPE_DO_NOTHING_E          = 0,
    SXD_FLEX_SWITCH_PRIO_CMD_TYPE_SET_SWITCH_PRIORITY_E = 1,
    SXD_FLEX_SWITCH_PRIO_CMD_TYPE_LAST,
} sxd_flex_switch_prio_cmd_t;

typedef enum sxd_flex_color_cmd {
    SXD_FLEX_COLOR_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_COLOR_CMD_TYPE_SET_COLOR_E  = 1,
    SXD_FLEX_COLOR_CMD_TYPE_LAST_E,
} sxd_flex_color_cmd_t;

typedef enum sxd_flex_color_type {
    SXD_FLEX_COLOR_CMD_TYPE_GREEN_E = 0,
    SXD_FLEX_COLOR_CMD_TYPE_YELLOW_E,
    SXD_FLEX_COLOR_CMD_TYPE_RED_E,
    SXD_FLEX_COLOR_TYPE_LAST_E,
} sxd_flex_color_type_t;

typedef enum sxd_flex_rewrite_cmd {
    SXD_FLEX_REWRITE_CMD_TYPE_PRESERVE_VALUE_REWRITE_ENABLE_BIT_E = 0,
    SXD_FLEX_REWRITE_CMD_TYPE_SET_VALUE_REWRITE_ENABLE_BIT_E,
    SXD_FLEX_REWRITE_CMD_TYPE_CLEAR_VALUE_REWRITE_ENABLE_BIT_E,
    SXD_FLEX_REWRITE_CMD_TYPE_LAST_E,
} sxd_flex_rewrite_cmd_t;

typedef enum sxd_flex_traffic_class_cmd {
    SXD_FLEX_TRAFFIC_CLASS_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_TRAFFIC_CLASS_CMD_TYPE_SET_TRAFFIC_CLASS_E,
    SXD_FLEX_TRAFFIC_CLASS_CMD_TYPE_LAST_E
} sxd_flex_traffic_class_cmd_t;

typedef enum sxd_ptce2_next_type {
    SXD_FLEX_NEXT_POINTER_RECORD_E = 0,
    SXD_FLEX_GOTO_RECORD_E         = 1,
} sxd_ptce2_next_type_t;

typedef enum sxd_binding_cmd {
    SXD_FLEX_BINDING_NONE_E      = 0,
    SXD_FLEX_BINDING_JUMP_E      = 1,
    SXD_FLEX_BINDING_CALL_E      = 2,
    SXD_FLEX_BINDING_BREAK_E     = 3,
    SXD_FLEX_BINDING_TERMINATE_E = 4,
} sxd_binding_cmd_t;

typedef struct sxd_qos_flex_action {
    sxd_flex_defer_t             defer;
    sxd_flex_ecn_cmd_t           ecn_cmd;
    uint8_t                      ecn_val;
    sxd_flex_color_cmd_t         color_cmd;
    uint8_t                      color_val;
    sxd_flex_dscp_cmd_t          dscp_cmd;
    uint8_t                      dscp_val;
    sxd_flex_switch_prio_cmd_t   switch_prio_cmd;
    uint8_t                      switch_prio_val;
    sxd_flex_rewrite_cmd_t       rewrite_dscp_cmd;
    sxd_flex_rewrite_cmd_t       rewrite_pcp_cmd;
    sxd_flex_traffic_class_cmd_t traffic_class_cmd;
    uint8_t                      tc;
} sxd_qos_flex_action_t;
typedef enum sxd_forward_flex_action_type {
    SXD_FORWARD_FLEX_ACTION_TYPE_PBS_E = 0,
    SXD_FORWARD_FLEX_ACTION_TYPE_OUTPUT_E,
    SXD_FORWARD_FLEX_ACTION_TYPE_LAST_E,
} sxd_forward_flex_action_type_t;

typedef enum sxd_forward_output_record_defer {
    SXD_FORWARD_FLEX_ACTION_OUTPUT_DEFER_TYPE_APPLY_E = 0,
    SXD_FORWARD_FLEX_ACTION_OUTPUT_DEFER_TYPE_LIKE_PBS_E
} sxd_forward_output_record_defer_t;

typedef struct sxd_forward_output_record_flex_action {
    sxd_forward_output_record_defer_t defer;
    uint32_t                          pbs_ptr;
    uint8_t                           in_port;
} sxd_forward_output_record_flex_action_t;

typedef struct sxd_forward_flex_action {
    sxd_forward_flex_action_type_t type;
    union {
        uint32_t                                pbs_ptr;
        sxd_forward_output_record_flex_action_t output;
    } record;
} sxd_forward_flex_action_t;

typedef enum sxd_policing_monitoring_flex_action_type {
    SXD_POLIICING_MONITORING_FLEX_ACTION_COUNTER_E = 0,
    SXD_POLIICING_MONITORING_FLEX_ACTION_POLICER_E,
    SXD_POLIICING_MONITORING_FLEX_ACTION_LAST_E,
} sxd_policing_monitoring_flex_action_type_t;

typedef struct sxd_policing_monitoring_flex_action {
    sxd_policing_monitoring_flex_action_type_t c_p;
    sxd_counter_set_t                          counter_set;
    uint16_t                                   pid;
} sxd_policing_monitoring_flex_action_t;

typedef enum sxd_policing_monitoring_by_ref_flex_action_type {
    SXD_POLIICING_MONITORING_FLEX_ACTION_COUNTER_BY_REF_E = 0,
    SXD_POLIICING_MONITORING_FLEX_ACTION_POLICER_BY_REF_E,
    SXD_POLIICING_MONITORING_FLEX_ACTION_LAST_BY_REF_E,
} sxd_policing_monitoring_by_ref_flex_action_type_t;


typedef struct sxd_policing_monitoring_by_ref_flex_action {
    sxd_policing_monitoring_by_ref_flex_action_type_t type;
    uint8_t                                           cbset;
} sxd_policing_monitoring_by_ref_flex_action_t;


typedef struct sxd_metadata_flex_action {
    uint16_t meta_data;
    uint16_t mask;
} sxd_metadata_flex_action_t;

typedef struct sxd_trucation_flex_action {
    sxd_boolean_t trunc_en;
    uint16_t      trunc_profile_id;
} sxd_trucation_flex_action_t;

typedef enum sxd_flow_estimator_profile_id {
    SXD_FLOW_ESTIMATOR_PROFILE0_E = 0,
    SXD_FLOW_ESTIMATOR_PROFILE1_E,
    SXD_FLOW_ESTIMATOR_PROFILE2_E,
    SXD_FLOW_ESTIMATOR_PROFILE3_E,
} sxd_flow_estimator_profile_id_e;

typedef struct sxd_flow_estimator_profile_key {
    sxd_flow_estimator_profile_id_e profile_id;
} sxd_flow_estimator_profile_key_t;

typedef struct sxd_flow_estimator_flex_action {
    sxd_flow_estimator_profile_key_t profile_key;    /**< flow estimator profile key */
    sxd_counter_set_t                bulk_counter;   /**< flow estimator bulk counter */
} sxd_flow_estimator_flex_action_t;


typedef enum sxd_uc_router_flex_action_type {
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_IP_REMOTE_E = 0,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_IP_LOCAL_E,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_TUNNL_TERMINIATION_E,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_MPLS_ILM_E,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_MPLS_NHLFE_E,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_AR_E,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_LAST_E,
} sxd_uc_router_flex_action_type_t;

typedef struct sxd_uc_router_flex_action_ip_remote {
    uint32_t adjacency_index;
    uint16_t ecmp_size;
} sxd_uc_router_flex_action_ip_remote_t;

typedef struct sxd_uc_router_flex_action_ip_local {
    uint16_t local_erif;
} sxd_uc_router_flex_action_ip_local_t;

typedef struct sxd_uc_router_flex_action_tunnul_termination {
    uint32_t tunnul_ptr;
} sxd_uc_router_flex_action_tunnul_termination_t;

typedef struct sxd_uc_router_flex_action_mpls_ilm {
    uint32_t ilm_ptr;
} sxd_uc_router_flex_action_mpls_ilm_t;

typedef struct sxd_uc_router_flex_action_mpls_nhlfe {
    uint32_t nhlfe_ptr;
    uint16_t ecmp_size;
} sxd_uc_router_flex_action_mpls_nhlfe_t;

typedef struct sxd_uc_router_flex_action_ar {
    uint8_t  ar_lookup_prof_id;
    uint16_t ecmp_size;
    uint16_t arlpgt_pointer;
    uint32_t arft_pointer;
} sxd_uc_router_flex_action_ar_t;

typedef struct sxd_uc_router_flex_action {
    sxd_uc_router_flex_action_type_t type;
    union {
        sxd_uc_router_flex_action_ip_remote_t          ip_remote;
        sxd_uc_router_flex_action_ip_local_t           ip_local;
        sxd_uc_router_flex_action_tunnul_termination_t tunnul_termination;
        sxd_uc_router_flex_action_mpls_ilm_t           mpls_ilm;
        sxd_uc_router_flex_action_mpls_nhlfe_t         mpls_nhlfe;
        sxd_uc_router_flex_action_ar_t                 ar_uc_route;
    } structs;
} sxd_uc_router_flex_action_t;
typedef enum sxd_vni_flex_action_type {
    SXD_VNI_FLEX_ACTION_TYPE_NONE_E = 0,
    SXD_VNI_FLEX_ACTION_TYPE_SET_E
} sxd_vni_flex_action_type_t;

typedef struct sxd_vni_flex_action {
    enum sxd_vni_flex_action_type set_vni;
    uint32_t                      vni;
} sxd_vni_flex_action_t;

typedef enum sxd_mpls_action_ttl_cmd_type {
    SXD_MPLS_FLEX_ACTION_TTL_CMD_TYPE_DO_NOTING_E = 0,
    SXD_MPLS_FLEX_ACTION_TTL_CMD_TYPE_SET_TTL_E,
    SXD_MPLS_FLEX_ACTION_TTL_CMD_TYPE_DECREMENT_BY_TTL_E
} sxd_mpls_action_ttl_cmd_type_t;

typedef enum sxd_mpls_action_exp_cmd_type {
    SXD_MPLS_FLEX_ACTION_EXP_CMD_TYPE_DO_NOTING_E = 0,
    SXD_MPLS_FLEX_ACTION_EXP_CMD_TYPE_SET_EXP_E
} sxd_mpls_action_exp_cmd_type_t;

typedef enum sxd_mpls_action_exp_rw_type {
    SXD_MPLS_FLEX_ACTION_EXP_RW_TYPE_PRESERVE_VALUE_REWRITE_BIT_E = 0,
    SXD_MPLS_FLEX_ACTION_EXP_CMD_TYPE_SET_REWRITE_BIT_E,
    SXD_MPLS_FLEX_ACTION_EXP_CMD_TYPE_CLEAR_REWRITE_BIT_E
} sxd_mpls_action_exp_rw_type_t;

typedef struct sxd_mpls_flex_action {
    sxd_mpls_action_ttl_cmd_type_t ttl_cmd;
    uint8_t                        ttl;
    uint8_t                        ttl_code;
    sxd_mpls_action_exp_cmd_type_t exp_cmd;
    uint8_t                        exp;
    sxd_mpls_action_exp_rw_type_t  exp_rw;
} sxd_mpls_flex_action_t;

typedef enum sxd_hash_flex_action_type {
    SXD_HASH_FLEX_ACTION_TYPE_LAG = 0,
    SXD_HASH_FLEX_ACTION_TYPE_ECMP,
    SXD_HASH_FLEX_ACTION_TYPE_LAST
} sxd_hash_flex_action_type_t;

typedef enum sxd_hash_flex_action_cmd {
    SXD_HASH_FLEX_ACTION_CMD_NONE_E = 0,
    SXD_HASH_FLEX_ACTION_CMD_SET_E,
    SXD_HASH_FLEX_ACTION_CMD_XOR_E,
    SXD_HASH_FLEX_ACTION_CMD_RANDOM_E,
    SXD_HASH_FLEX_ACTION_CMD_COPY_E,
    SXD_HASH_FLEX_ACTION_CMD_SWAP_E,
    SXD_HASH_FLEX_ACTION_CMD_CRC_E,
    SXD_HASH_FLEX_ACTION_CMD_LAST_E
} sxd_hash_flex_action_cmd_t;
typedef enum sxd_hash_flex_action_hash_fields {
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SMAC_31_0_E            = 0,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DMAC_31_0_E            = 1,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DMAC_SMAC_47_32_E      = 2,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SMAC_DMAC_47_32_E      = 3,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SIP_31_0_E             = 4,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SIP_63_32_E            = 5,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SIP_95_64_E            = 6,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SIP_127_96_E           = 7,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DIP_31_0_E             = 8,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DIP_63_32_E            = 9,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DIP_95_64_E            = 10,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DIP_127_96_E           = 11,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_IP_PROTO_E             = 14,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_L4_SPORT_DPORT_E       = 15,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_L4_DPORT_SPORT_E       = 16,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SPI_E                  = 17,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_SIP_31_0_E       = 18,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_SIP_63_32_E      = 19,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_SIP_95_64_E      = 20,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_SIP_127_96_E     = 21,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_DIP_31_0_E       = 22,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_DIP_63_32_E      = 23,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_DIP_95_64_E      = 24,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_DIP_127_96_E     = 25,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_IP_PROTO_E       = 28,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_L4_SPORT_DPORT_E = 29,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_L4_DPORT_SPORT_E = 30,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_GP_REGISTER_1_0_E      = 31,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_GP_REGISTER_3_2_E      = 32,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_GP_REGISTER_5_4_E      = 33,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_GP_REGISTER_7_6_E      = 34,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_HASH_VALUE_E           = 35,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_LAST_E,
} sxd_hash_flex_action_hash_fields_t;

typedef struct sxd_hash_flex_action {
    sxd_hash_flex_action_type_t        type;
    sxd_hash_flex_action_cmd_t         hash_cmd;
    sxd_hash_flex_action_hash_fields_t hash_fields;
    uint16_t                           hash_value;
    uint32_t                           hash_mask;
} sxd_hash_flex_action_t;
typedef enum sxd_virtual_forward_flex_action_vr_cmd_type {
    SXD_VIRTUAL_FORWARD_FLEX_ACTION_VR_CMD_TYPE_DO_NOTING_E = 0,
    SXD_VIRTUAL_FORWARD_FLEX_ACTION_VR_CMD_TYPE_SET_VR_TO_PACKET_E,
    SXD_VIRTUAL_FORWARD_FLEX_ACTION_VR_CMD_TYPE_LAST,
} sxd_virtual_forward_flex_action_vr_cmd_type_t;

typedef enum sxd_virtual_forward_flex_action_fid_cmd_type {
    SXD_VIRTUAL_FORWARD_FLEX_ACTION_FID_CMD_TYPE_DO_NOTING_E = 0,
    SXD_VIRTUAL_FORWARD_FLEX_ACTION_FID_CMD_TYPE_SET_FID_TO_PACKET_E,
    SXD_VIRTUAL_FORWARD_FLEX_ACTION_FID_CMD_TYPE_LAST,
} sxd_virtual_forward_flex_action_fid_cmd_type_t;

typedef struct sxd_virtual_forward_flax_action {
    sxd_virtual_forward_flex_action_vr_cmd_type_t  vr_cmd;
    uint16_t                                       virtual_router;
    sxd_virtual_forward_flex_action_fid_cmd_type_t fid_cmd;
    uint16_t                                       fid;
} sxd_virtual_forward_flax_action_t;
typedef enum sxd_ignore_flex_action_ignore_stp_type {
    SXD_IGNORE_FLEX_ACTION_IGNORE_STP_TYPE_REGULAR_FLOW_E = 0,
    SXD_IGNORE_FLEX_ACTION_IGNORE_STP_TYPE_IGNORE_STP_E,
    SXD_IGNORE_FLEX_ACTION_IGNORE_STP_TYPE_LAST_E,
} sxd_ignore_flex_action_ignore_stp_type_t;
typedef enum sxd_ignore_flex_action_ignore_vl_filter_type {
    SXD_IGNORE_FLEX_ACTION_IGNORE_VL_TYPE_REGULAR_FLOW_E = 0,
    SXD_IGNORE_FLEX_ACTION_IGNORE_VL_TYPE_IGNORE_VLAN_E,
    SXD_IGNORE_FLEX_ACTION_IGNORE_VL_TYPE_LAST_E,
} sxd_ignore_flex_action_ignore_vl_filter_type_t;
typedef enum sxd_ignore_flex_action_disable_learning_type {
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_LEARNING_TYPE_REGULAR_FLOW_E = 0,
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_LEARNING_TYPE_DISABLE_LEARNING_E,
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_LEARNING_TYPE_LAST_E,
} sxd_ignore_flex_action_disable_learning_type_t;
typedef enum sxd_ignore_flex_action_disable_ovl_learning_type {
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_OVL_LEARNING_TYPE_REGULAR_FLOW_E = 0,
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_OVL_LEARNING_TYPE_DISABLE_LEARNING_E,
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_OVL_LEARNING_TYPE_LAST_E,
} sxd_ignore_flex_action_disable_ovl_learning_type_t;
typedef enum sxd_ignore_flex_action_disable_fdb_security_type {
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_FDB_SECURITY_TYPE_REGULAR_FLOW_E = 0,
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_FDB_SECURITY_TYPE_DISABLE_SECURITY_E,
    SXD_IGNORE_FLEX_ACTION_IGNORE_DISABLE_FDB_SECURITY_TYPE_LAST_E,
} sxd_ignore_flex_action_disable_fdb_security_type_t;

typedef enum sxd_ignore_flex_action_set_elephant_flow_type {
    SXD_IGNORE_FLEX_ACTION_IGNORE_ELEPHANT_FLOW_DO_NOT_SET_E = 0,
    SXD_IGNORE_FLEX_ACTION_IGNORE_ELEPHANT_FLOW_SET_ELEPHANT_STATE_E,
    SXD_IGNORE_FLEX_ACTION_IGNORE_ELEPHANT_FLOW_SET_MICE_STATE_E,
} sxd_ignore_flex_action_set_elephant_flow_type_t;

typedef enum sxd_ignore_flex_action_ar_packet_prof_cmd_type {
    SXD_IGNORE_FLEX_ACTION_IGNORE_AR_PACKET_PROF_DO_NOTHING_E = 0,
    SXD_IGNORE_FLEX_ACTION_IGNORE_AR_PACKET_PROF_SET_E        = 1,
} sxd_ignore_flex_action_ar_packet_prof_cmd_type_t;

/**
 * sxd_ralue_format_t enumerated type is used to note the
 * format for RALUE register.
 */
typedef enum sxd_ar_lookup_profile_id {
    SXD_AR_LOOKUP_PROFILE_ID_HBF = 0,
    SXD_AR_LOOKUP_PROFILE_ID_0   = 1,
    SXD_AR_LOOKUP_PROFILE_ID_1   = 2,
} sxd_ar_lookup_profile_id_t;

typedef struct sxd_ignore_flex_action_cond_mirroring_type {
    uint16_t cond_mirroring_mask;
    uint16_t cond_mirroring_val;
} sxd_ignore_flex_action_cond_mirroring_type_t;

typedef struct sxd_ignore_flex_action {
    sxd_ignore_flex_action_ignore_stp_type_t           ignore_stp;
    sxd_ignore_flex_action_ignore_vl_filter_type_t     ignore_vl_filter;
    sxd_ignore_flex_action_disable_learning_type_t     disable_learning;
    sxd_ignore_flex_action_disable_ovl_learning_type_t disable_ovl_learning;
    sxd_ignore_flex_action_disable_fdb_security_type_t disable_fdb_security;
    sxd_ignore_flex_action_set_elephant_flow_type_t    set_elephant_flow;
    sxd_ar_lookup_profile_id_t                         ar_packet_prof_id;
    sxd_ignore_flex_action_ar_packet_prof_cmd_type_t   ar_packet_prof_cmd;
    sxd_ignore_flex_action_cond_mirroring_type_t       cond_mirror;
} sxd_ignore_flex_action_t;

typedef enum sxd_group_or_acl_binding_type {
    SXD_GROUP_OR_ACL_BINDING_TYPE_ACL_E = 0,
    SXD_GROUP_OR_ACL_BINDING_TYPE_GROUP_E
} sxd_group_or_acl_binding_type_t;

typedef enum sxd_mc_flex_action_rpf_action_type {
    SXD_MC_FLEX_ACTION_RPF_ACTION_NOP_E             = 0,
    SXD_MC_FLEX_ACTION_RPF_ACTION_RPF_TRAP_E        = 1,
    SXD_MC_FLEX_ACTION_RPF_ACTION_RPF_DISCARD_ERR_E = 3,
    SXD_MC_FLEX_ACTION_RPF_ACTION_ASSERT_TRAP_E     = 6,
    SXD_MC_FLEX_ACTION_RPF_ACTION_LAST_E,
} sxd_mc_flex_action_rpf_action_type_t;

typedef enum sxd_mc_flex_action_eir_type {
    SXD_MC_FLEX_ACTION_EIR_TYPE_IRIF_E = 0,
    SXD_MC_FLEX_ACTION_EIR_TYPE_IRIF_LIST_E,
    SXD_MC_FLEX_ACTION_EIR_TYPE_LAST_E,
} sxd_mc_flex_action_eir_type_t;

typedef struct sxd_mc_flex_action {
    sxd_mc_flex_action_rpf_action_type_t rpf_action;
    sxd_mc_flex_action_eir_type_t        eir_type;
    uint16_t                             expected_irif;
    uint32_t                             expected_irif_list_index;
    uint16_t                             min_mtu;
    sxd_boolean_t                        vrmid;
    uint32_t                             rigr_rmid_index;
} sxd_mc_flex_action_t;

typedef enum sxd_sip_dip_flex_action_direction {
    SXD_SIP_DIP_FLEX_ACTION_DIRECTION_DESTINATION_E = 0,
    SXD_SIP_DIP_FLEX_ACTION_DIRECTION_SOURCE_E      = 1,
    SXD_SIP_DIP_FLEX_ACTION_DIRECTION_TYPE_LAST_E,
} sxd_sip_dip_flex_action_direction_t;

typedef enum sxd_sip_dip_flex_action_bytes {
    SXD_SIP_DIP_FLEX_ACTION_BYTES_LSB_E = 0,
    SXD_SIP_DIP_FLEX_ACTION_BYTES_MSB_E = 1,
    SXD_SIP_DIP_FLEX_ACTION_BYTES_TYPE_LAST_E,
} sxd_sip_dip_flex_action_bytes_t;

typedef struct sxd_sip_dip_flex_action {
    sxd_flex_defer_t                    defer;
    sxd_sip_dip_flex_action_direction_t direction;
    sxd_sip_dip_flex_action_bytes_t     bytes;
    uint32_t                            ip_63_32;
    uint32_t                            ip_31_0;
} sxd_sip_dip_flex_action_t;

typedef enum sxd_l4_port_flex_action_direction {
    SXD_L4_PORT_FLEX_ACTION_DIRECTION_SOURCE_E      = 0,
    SXD_L4_PORT_FLEX_ACTION_DIRECTION_DESTINATION_E = 1,
    SXD_L4_PORT_FLEX_ACTION_DIRECTION_TYPE_LAST_E,
} sxd_l4_port_flex_action_direction_t;

typedef enum sxd_l4_port_flex_action_hash {
    SXD_L4_PORT_FLEX_ACTION_HASH_NONE_E   = 0,
    SXD_L4_PORT_FLEX_ACTION_HASH_ROUTER_E = 1,
    SXD_L4_PORT_FLEX_ACTION_HASH_LAG_E    = 2,
    SXD_L4_PORT_FLEX_ACTION_HASH_TYPE_LAST_E,
} sxd_l4_port_flex_action_hash_t;

typedef struct sxd_l4_port_flex_action {
    sxd_flex_defer_t                    defer;
    sxd_l4_port_flex_action_direction_t direction;
    sxd_l4_port_flex_action_hash_t      hash;
    uint16_t                            l4_port;
} sxd_l4_port_flex_action_t;

typedef struct sxd_mirror_sampler_flex_action {
    uint8_t  mirror_agent;
    uint32_t mirror_probability_rate;
} sxd_mirror_sampler_flex_action_t;

typedef enum sxd_custom_bytes_alu_imm_action_opcode {
    SXD_CUSTOM_BYTES_ALU_IMM_ACTION_OPCODE_SET_E = 0,
    SXD_CUSTOM_BYTES_ALU_IMM_ACTION_OPCODE_ADD_E = 1,
    SXD_CUSTOM_BYTES_ALU_IMM_ACTION_OPCODE_AND_E = 2,
    SXD_CUSTOM_BYTES_ALU_IMM_ACTION_OPCODE_OR_E  = 3,
    SXD_CUSTOM_BYTES_ALU_IMM_ACTION_OPCODE_TYPE_LAST_E,
} sxd_custom_bytes_alu_imm_action_opcode_t;

typedef struct sxd_custom_bytes_alu_imm_flex_action {
    sxd_custom_bytes_alu_imm_action_opcode_t opcode;
    uint8_t                                  dest_cbset;
    uint16_t                                 imm;
    uint16_t                                 mask;
} sxd_custom_bytes_alu_imm_flex_action_t;

typedef enum sxd_custom_bytes_alu_reg_action_opcode {
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_SET_E  = 0,
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_ADD_E  = 1,
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_AND_E  = 2,
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_OR_E   = 3,
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_SUB_E  = 4,
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_XOR_E  = 5,
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_ADDC_E = 6,
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_SUBC_E = 7,
    SXD_CUSTOM_BYTES_ALU_REG_ACTION_OPCODE_TYPE_LAST_E,
} sxd_custom_bytes_alu_reg_action_opcode_t;

typedef struct sxd_custom_bytes_alu_reg_flex_action {
    sxd_custom_bytes_alu_reg_action_opcode_t opcode;
    uint8_t                                  dest_cbset;
    uint8_t                                  src_cbset;
    uint16_t                                 mask;
    uint8_t                                  shr;
} sxd_custom_bytes_alu_reg_flex_action_t;

typedef enum sxd_custom_bytes_flex_action_field_select {
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_ECMP_HASH_E  = 1,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_LAG_HASH_E   = 2,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_RANDOM_E     = 3,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_IP_LENGTH_E  = 4,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_VID_E        = 6,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_USER_TOKEN_E = 7,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_TTL_E        = 24,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DMAC_15_0_E  = 25,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DMAC_31_16_E = 26,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DMAC_47_32_E = 27,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SMAC_15_0_E  = 28,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SMAC_31_16_E = 29,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SMAC_47_32_E = 30,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DIP_15_0_E    = 31,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DIP_31_16_E   = 32,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DIP_47_32_E   = 33,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DIP_63_48_E   = 34,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DIP_79_64_E   = 35,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DIP_95_80_E   = 36,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DIP_111_96_E  = 37,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_DIP_127_112_E = 38,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SIP_15_0_E    = 39,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SIP_31_16_E   = 40,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SIP_47_32_E   = 41,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SIP_63_48_E   = 42,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SIP_79_64_E   = 43,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SIP_95_80_E   = 44,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SIP_111_96_E  = 45,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_SIP_127_112_E = 46,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_L4_SOURCE_PORT_E      = 47,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_L4_DESTINATION_PORT_E = 48,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_VNI_15_0_E  = 49,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_VNI_31_16_E = 50,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_FID_E           = 51,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_VRID_E          = 52,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_PORT_USER_MEM_E = 54,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_GP_REGISTER_0_OFFSET = 55,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_GP_REGISTER_1_OFFSET = 56,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_CQE_USER_DEF_VAL_15_0_E  = 62,
    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_CQE_USER_DEF_VAL_19_16_E = 63,

    SXD_CUSTOM_BYTES_FLEX_ACTION_FIELD_TYPE_LAST_E,
} sxd_custom_bytes_flex_action_field_select_t;

typedef enum sxd_custom_bytes_alu_field_action_opcode {
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_SET_E  = 0,
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_ADD_E  = 1,
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_AND_E  = 2,
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_OR_E   = 3,
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_SUB_E  = 4,
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_XOR_E  = 5,
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_ADDC_E = 6,
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_SUBC_E = 7,
    SXD_CUSTOM_BYTES_ALU_FIELD_ACTION_OPCODE_TYPE_LAST_E,
} sxd_custom_bytes_alu_field_action_opcode_t;

typedef struct sxd_custom_bytes_alu_field_flex_action {
    sxd_custom_bytes_alu_field_action_opcode_t  opcode;
    uint8_t                                     cbset;
    sxd_custom_bytes_flex_action_field_select_t field_select;
    uint16_t                                    mask;
    uint8_t                                     shr;
} sxd_custom_bytes_alu_field_flex_action_t;

typedef enum sxd_custom_bytes_move_action_opcode {
    SXD_CUSTOM_BYTES_MOVE_ACTION_OPCODE_MOVE_E  = 0,
    SXD_CUSTOM_BYTES_MOVE_ACTION_OPCODE_LOAD_E  = 1,
    SXD_CUSTOM_BYTES_MOVE_ACTION_OPCODE_STORE_E = 2,
    SXD_CUSTOM_BYTES_MOVE_ACTION_OPCODE_TYPE_LAST_E,
} sxd_custom_bytes_move_action_opcode_t;

typedef struct sxd_custom_bytes_move_flex_action {
    sxd_flex_defer_t                            defer;
    sxd_custom_bytes_move_action_opcode_t       opcode;
    uint8_t                                     size;
    uint8_t                                     dest_cbset;
    uint8_t                                     src_cbset;
    sxd_custom_bytes_flex_action_field_select_t field_select;
} sxd_custom_bytes_move_flex_action_t;

typedef struct sxd_fields_set_imm_action {
    sxd_flex_defer_t                            defer;
    sxd_custom_bytes_flex_action_field_select_t dest_field_select;
    uint8_t                                     size;
    uint16_t                                    imm;
} sxd_fields_set_imm_action_t;

typedef struct sxd_fields_move_action {
    sxd_flex_defer_t                            defer;
    sxd_custom_bytes_flex_action_field_select_t dest_field_select;
    sxd_custom_bytes_flex_action_field_select_t src_field_select;
    uint8_t                                     size;
} sxd_fields_move_action_t;

typedef enum sxd_flex_modifier_emt_action_opcode {
    SXD_FLEX_MODIFIER_EMT_ACTION_OPCODE_NOP_E     = 0,
    SXD_FLEX_MODIFIER_EMT_ACTION_OPCODE_PUSH_E    = 1,
    SXD_FLEX_MODIFIER_EMT_ACTION_OPCODE_EDIT_E    = 2,
    SXD_FLEX_MODIFIER_EMT_ACTION_OPCODE_DISABLE_E = 3,
    SXD_FLEX_MODIFIER_EMT_ACTION_OPCODE_POP_E     = 4,
    SXD_FLEX_MODIFIER_EMT_ACTION_OPCODE_TYPE_LAST_E,
} sxd_flex_modifier_emt_action_opcode_t;

typedef enum sxd_flex_modifier_emt_action_modify_offset {
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFY_OFFSET_GP_REG_0_E = 0,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFY_OFFSET_GP_REG_1_E = 1,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFY_OFFSET_LAST_E,
} sxd_flex_modifier_emt_action_modify_offset_t;

typedef enum sxd_flex_modifier_emt_action_offset_type {
    SXD_FLEX_MODIFIER_EMT_ACTION_OFFSET_TYPE_GP_REG_E   = 0,
    SXD_FLEX_MODIFIER_EMT_ACTION_OFFSET_TYPE_CONSTANT_E = 1,
    SXD_FLEX_MODIFIER_EMT_ACTION_OFFSET_TYPE_LAST_E,
} sxd_flex_modifier_emt_action_offset_type_t;

typedef enum sxd_flex_modifier_emt_action_modifier_base {
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_SOP_E             = 0,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_MAC_E             = 1,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_ETHERTYPE_E       = 2,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_IP_E              = 3,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_MPLS_E            = 4,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_NVE_E             = 5,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_GRE_E             = 6,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_UDP_E             = 7,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_FLEX_E            = 8,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_INNER_MAC_E       = 9,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_INNER_MPLS_E      = 10,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_INNER_ETHERTYPE_E = 11,
    SXD_FLEX_MODIFIER_EMT_ACTION_MODIFIER_BASE_LAST_E,
} sxd_flex_modifier_emt_action_modifier_base_t;

typedef struct sxd_flex_modifier_emt_record {
    sxd_flex_modifier_emt_action_opcode_t        emt_opcode;
    uint8_t                                      emt_pointer;
    sxd_flex_modifier_emt_action_modify_offset_t modify_offset;
    sxd_flex_modifier_emt_action_offset_type_t   offset_type;
    sxd_flex_modifier_emt_action_modifier_base_t modifier_base;
} sxd_flex_modifier_emt_record_t;

typedef struct sxd_flex_modifier_emt_action {
    sxd_flex_modifier_emt_record_t emt_record[2];
} sxd_flex_modifier_emt_action_t;

typedef struct sxd_buffer_snap_flex_action {
    uint8_t snap_id;
} sxd_buffer_snap_flex_action_t;


typedef enum sxd_flex_stateful_db_key_type {
    SXD_FLEX_STATEFUL_DB_KEY_TYPE_GROUP_ID_E     = 0,
    SXD_FLEX_STATEFUL_DB_KEY_TYPE_LINEAR_INDEX_E = 1,
} sxd_flex_stateful_db_key_type_t;

typedef enum sxd_flex_stateful_db_ticket_op {
    SXD_FLEX_STATEFUL_DB_TICKET_OP_NOP_E     = 0,
    SXD_FLEX_STATEFUL_DB_TICKET_OP_RELEASE_E = 1,
    SXD_FLEX_STATEFUL_DB_TICKET_OP_CHECK_E   = 2,
} sxd_flex_stateful_db_ticket_op_t;

typedef enum sxd_flex_stateful_db_db_op {
    SXD_FLEX_STATEFUL_DB_DB_OP_NOP_E                                     = 0,
    SXD_FLEX_STATEFUL_DB_DB_OP_READ_E                                    = 1,
    SXD_FLEX_STATEFUL_DB_DB_OP_WRITE_E                                   = 2,
    SXD_FLEX_STATEFUL_DB_DB_OP_REMOVE_ENTRY_WITH_FAILURE_INDICATION_E    = 3,
    SXD_FLEX_STATEFUL_DB_DB_OP_REMOVE_ENTRY_WITHOUT_FAILURE_INDICATION_E = 4,
} sxd_flex_stateful_db_db_op_t;

typedef enum sxd_flex_stateful_db_sem_op {
    SXD_FLEX_STATEFUL_DB_SEM_OP_NOP_E    = 0,
    SXD_FLEX_STATEFUL_DB_SEM_OP_LOCK_E   = 1,
    SXD_FLEX_STATEFUL_DB_SEM_OP_UNLOCK_E = 2,
} sxd_flex_stateful_db_sem_op_t;

typedef struct sxd_flex_stateful_db_action {
    uint16_t                         key_id;
    sxd_flex_stateful_db_key_type_t  key_type;
    uint8_t                          cbs_index;
    sxd_flex_stateful_db_ticket_op_t ticket_op;
    uint8_t                          partition_id;
    sxd_flex_stateful_db_db_op_t     db_op;
    sxd_flex_stateful_db_sem_op_t    sem_op;
} sxd_flex_stateful_db_action_t;

typedef struct sxd_action_slot {
    sxd_flex_acl_action_type_t type;
    union {
        sxd_mac_flex_action_t                        action_mac;
        sxd_vlan_flex_action_t                       action_vlan;
        sxd_trap_flex_action_t                       action_trap;      /** Used for trap and trap_w_user_def_val */
        sxd_port_filter_flex_action_t                action_port_filter;
        sxd_qos_flex_action_t                        action_qos;
        sxd_forward_flex_action_t                    action_forward;
        sxd_policing_monitoring_flex_action_t        action_policing_monitoring;
        sxd_policing_monitoring_by_ref_flex_action_t action_policing_monitoring_by_ref;
        sxd_metadata_flex_action_t                   action_metadata;
        sxd_uc_router_flex_action_t                  action_uc_router;
        sxd_vni_flex_action_t                        action_vni;
        sxd_mpls_flex_action_t                       action_mpls;
        sxd_hash_flex_action_t                       action_hash;
        sxd_virtual_forward_flax_action_t            action_virtual_forward;
        sxd_ignore_flex_action_t                     action_ignore;
        sxd_mc_flex_action_t                         action_mc;
        sxd_sip_dip_flex_action_t                    action_sip_dip;
        sxd_l4_port_flex_action_t                    action_l4_port;
        sxd_mirror_sampler_flex_action_t             action_mirror_sampler;
        sxd_port_filter_ext_flex_action_t            action_port_filter_ext;
        sxd_port_filter_ext2_flex_action_t           action_port_filter_ext2;
        sxd_custom_bytes_alu_imm_flex_action_t       action_custom_bytes_alu_imm;
        sxd_custom_bytes_alu_reg_flex_action_t       action_custom_bytes_alu_reg;
        sxd_custom_bytes_alu_field_flex_action_t     action_custom_bytes_alu_field;
        sxd_custom_bytes_move_flex_action_t          action_custom_bytes_move;
        sxd_fields_set_imm_action_t                  action_fields_set_imm;
        sxd_fields_move_action_t                     action_fields_move;
        sxd_flex_modifier_emt_action_t               action_flex_modifier_emt;
        sxd_buffer_snap_flex_action_t                action_buffer_snap;
        sxd_flex_stateful_db_action_t                action_flex_stateful_db;
        sxd_trucation_flex_action_t                  action_truncation;
        sxd_flow_estimator_flex_action_t             action_flow_estimator;
    } fields;
} sxd_action_slot_t;

typedef struct sxd_goto_set_action {
    uint16_t                           next_binding;
    uint8_t                            commit;
    enum sxd_group_or_acl_binding_type group_binding;
    enum sxd_binding_cmd               binding_cmd;
    uint8_t                            clear;
} sxd_goto_set_action_t;

typedef struct sxd_flex_action_set {
    struct sxd_action_slot   action_slots[SXD_ACL_NUM_OF_ACTION_SLOTS];
    enum sxd_ptce2_next_type next_type;
    union {
        uint32_t                   next_action_set_ptr;
        struct sxd_goto_set_action goto_set_action;
    } next_goto_record;
} sxd_flex_action_set_t;

typedef enum sxd_egress_or_igress_type {
    SXD_EGRESS_OR_IGRESS_TYPE_IGRESS = 0,
    SXD_EGRESS_OR_IGRESS_TYPE_EGRESS
} sxd_egress_or_igress_type_t;

typedef  struct ku_ptce2_reg {
    uint8_t               valid;
    uint8_t               activity;
    sxd_ptce_operation_t  op;
    uint16_t              offset;
    uint32_t              priority;
    uint8_t               tcam_region_info[SXD_TCAM_REGION_INFO_SIZE_BYTES];
    uint8_t               flex_key_blocks[SXD_ACL_FLEX_KEY_BLOCK_SIZE_BYTES];
    uint8_t               flex_mask_blocks[SXD_ACL_FLEX_KEY_BLOCK_SIZE_BYTES];
    sxd_flex_action_set_t action_set;
} ku_ptce2_reg_t;

/**
 *  * ku_ptce3_reg structure is used to store the PTCE_V3 register parameters
 *
 */

typedef enum sxd_ptce3_prune_ctcam {
    SXD_PTCE3_PRUNE_CTCAM_NEED = 0,
    SXD_PTCE3_PRUNE_CTCAM_PRUNE
} sxd_ptce3_prune_ctcam_t;

typedef enum sxd_ptce3_large_exists {
    SXD_PTCE3_LARGE_EXISTS_NOT_USED = 0,
    SXD_PTCE3_LARGE_EXISTS_IN_USE
} sxd_ptce3_large_exists_t;

typedef  struct ku_ptce3_reg {
    uint8_t                  valid;
    sxd_ptce_operation_t     op;
    uint8_t                  dup;
    uint32_t                 priority;
    uint8_t                  tcam_region_info[SXD_TCAM_REGION_INFO_SIZE_BYTES];
    uint8_t                  flex2_key_blocks[SXD_ACL_FLEX_KEY_BLOCK_SIZE_BYTES];
    uint8_t                  erp_id;
    uint16_t                 delta_start;
    uint8_t                  delta_mask;
    uint8_t                  delta_value;
    uint16_t                 prune_vector;
    sxd_ptce3_prune_ctcam_t  prune_ctcam;
    sxd_ptce3_large_exists_t large_exists;
    uint32_t                 large_entry_key_id;
    uint32_t                 action_pointer;
    uint16_t                 region_id_dup[SXD_TCAM_REGOIN_ID_DUP];
} ku_ptce3_reg_t;

typedef enum ku_prbt_reg_op_type {
    KU_PRBT_REG_OP_TYPE_BIND_ACL = 0,
    KU_PRBT_REG_OP_TYPE_UNBIND_ACL
} ku_prbt_reg_op_type_t;

typedef struct ku_prbt_reg {
    sxd_group_or_acl_binding_type_t group_binding;
    sxd_egress_or_igress_type_t     egress_indication;
    uint16_t                        acl_id_grp_id;
    uint16_t                        rif;
    ku_prbt_reg_op_type_t           op;
} ku_prbt_reg_t;

/**
 * sxd_pefa_ca_operation enumerates type of clear activity operation.
 */
typedef enum sxd_pefa_ca_operation {
    SXD_PEFA_CA_OP_SET      = 0,
    SXD_PEFA_CA_OP_CLEAR    = 1,
    SXD_PEFA_CA_OP_MAINTAIN = 2,
} sxd_pefa_ca_operation_t;

typedef struct ku_pefa_reg {
    uint8_t                 pind;
    uint32_t                index;
    sxd_pefa_ca_operation_t ca;
    uint8_t                 a;
    uint8_t                 a1;
    uint8_t                 ddd_en;
    uint16_t                as_user_val;
    sxd_flex_action_set_t   action_set;
} ku_pefa_reg_t;

#define SXD_ACL_CUSTOM_BYTE_SET0  0x0
#define SXD_ACL_CUSTOM_BYTE_SET1  0x1
#define SXD_ACL_CUSTOM_BYTE_SET2  0x2
#define SXD_ACL_CUSTOM_BYTE_SET3  0x3
#define SXD_ACL_CUSTOM_BYTE_SET4  0x4
#define SXD_ACL_CUSTOM_BYTE_SET5  0x5
#define SXD_ACL_CUSTOM_BYTE_SET6  0x6
#define SXD_ACL_CUSTOM_BYTE_SET7  0x7
#define SXD_ACL_CUSTOM_BYTE_SET8  0x8
#define SXD_ACL_CUSTOM_BYTE_SET9  0x9
#define SXD_ACL_CUSTOM_BYTE_SET10 0xa
#define SXD_ACL_CUSTOM_BYTE_SET11 0xb

#define SXD_ACL_EXTRACTION_POINT_MAC_HEADER         0x0
#define SXD_ACL_EXTRACTION_POINT_ETHER_TYPE         0x4
#define SXD_ACL_EXTRACTION_POINT_IPV4_HEADER        0x5
#define SXD_ACL_EXTRACTION_POINT_IPV4_PAYLOAD       0x6
#define SXD_ACL_EXTRACTION_POINT_ARP                0x9
#define SXD_ACL_EXTRACTION_POINT_IPV6_HEADER        0xA
#define SXD_ACL_EXTRACTION_POINT_IPV6_PAYLOAD       0xB
#define SXD_ACL_EXTRACTION_POINT_MPLS_HEADER        0x12
#define SXD_ACL_EXTRACTION_POINT_MPLS_PAYLOAD       0x13
#define SXD_ACL_EXTRACTION_POINT_ROCE_GRH_HEADER    0x14
#define SXD_ACL_EXTRACTION_POINT_GRE_HEADER         0x19
#define SXD_ACL_EXTRACTION_POINT_GRE_PAYLOLAD       0x1A
#define SXD_ACL_EXTRACTION_POINT_ROCE_BTH_HEADER    0x21
#define SXD_ACL_EXTRACTION_POINT_ICMP_HEADER        0x22
#define SXD_ACL_EXTRACTION_POINT_IGMP_HEADER        0x23
#define SXD_ACL_EXTRACTION_POINT_UDP_HEADER         0x24
#define SXD_ACL_EXTRACTION_POINT_UDP_PAYLOAD        0x25
#define SXD_ACL_EXTRACTION_POINT_TCP_HEADER         0x26
#define SXD_ACL_EXTRACTION_POINT_INNER_MAC_HEADER   0x27
#define SXD_ACL_EXTRACTION_POINT_INNER_ETHER_TYPE   0x28
#define SXD_ACL_EXTRACTION_POINT_INNER_IPV4_HEADER  0x29
#define SXD_ACL_EXTRACTION_POINT_INNER_IPV4_PAYLOAD 0x2A
#define SXD_ACL_EXTRACTION_POINT_INNER_IPV6_HEADER  0x2D
#define SXD_ACL_EXTRACTION_POINT_INNER_IPV6_PAYLOAD 0x2E
#define SXD_ACL_EXTRACTION_POINT_INNER_UDP_HEADER   0x39
#define SXD_ACL_EXTRACTION_POINT_INNER_UDP_PAYLOAD  0x3A
#define SXD_ACL_EXTRACTION_POINT_INNER_TCP_HEADER   0x3B
#define SXD_ACL_EXTRACTION_POINT_VXLAN_HEADER       0x50
#define SXD_ACL_EXTRACTION_POINT_VXLAN_GPE_HEADER   0x51
#define SXD_ACL_EXTRACTION_POINT_GENEVE_HEADER      0x52
#define SXD_ACL_EXTRACTION_POINT_FLEX_HEADER0       0x80
#define SXD_ACL_EXTRACTION_POINT_FLEX_HEADER1       0x81
#define SXD_ACL_EXTRACTION_POINT_FLEX_HEADER2       0x82
#define SXD_ACL_EXTRACTION_POINT_FLEX_HEADER3       0x83
#define SXD_ACL_EXTRACTION_POINT_FLEX_HEADER4       0x84
#define SXD_ACL_EXTRACTION_POINT_FLEX_HEADER5       0x85
#define SXD_ACL_EXTRACTION_POINT_FLEX_HEADER6       0x86
#define SXD_ACL_EXTRACTION_POINT_FLEX_HEADER7       0x87
#define SXD_ACL_EXTRACTION_POINT_INNER_FLEX_HEADER0 0xA0
#define SXD_ACL_EXTRACTION_POINT_INNER_FLEX_HEADER1 0xA1
#define SXD_ACL_EXTRACTION_POINT_INNER_FLEX_HEADER2 0xA2
#define SXD_ACL_EXTRACTION_POINT_INNER_FLEX_HEADER3 0xA3
#define SXD_ACL_EXTRACTION_POINT_INNER_FLEX_HEADER4 0xA4
#define SXD_ACL_EXTRACTION_POINT_INNER_FLEX_HEADER5 0xA5
#define SXD_ACL_EXTRACTION_POINT_INNER_FLEX_HEADER6 0xA6
#define SXD_ACL_EXTRACTION_POINT_INNER_FLEX_HEADER7 0xA7
#define SXD_ACL_EXTRACTION_POINT_HASH_SIG0          0xE0    /* SPC4 only */
#define SXD_ACL_EXTRACTION_POINT_HASH_SIG1          0xE1    /* SPC4 only */
#define SXD_ACL_EXTRACTION_POINT_HASH_SIG2          0xE2    /* SPC4 only */
#define SXD_ACL_EXTRACTION_POINT_HASH_SIG3          0xE3    /* SPC4 only */

typedef struct sxd_flex_extraction_point {
    uint8_t enable;
    uint8_t offset;
} sxd_flex_extraction_point_t;

typedef  struct ku_pecb_reg {
    uint8_t                     cbset;
    sxd_flex_extraction_point_t extraction_points[SXD_ACL_NUM_OF_EXTRACTION_POINT];
} ku_pecb_reg_t;

typedef struct sxd_pemb_recorde_multicast_egress {
    uint8_t  group_id;
    uint8_t  valid;
    uint32_t egress_port_list_63_32;
    uint32_t egress_port_list_31_0;
} sxd_pemb_recorde_multicast_egress_t;

typedef enum ku_pemb_entry_type {
    KU_PEMB_ENTRY_TYPE_SPREADING_E            = 0x1,
    KU_PEMB_ENTRY_TYPE_EGRESS_ACL_MULTICAST_E = 0x2,
    KU_PEMB_ENTRY_TYPE_RESERVED_E             = 0x3
} ku_pemb_entry_type_t;

typedef struct ku_pemb_reg {
    ku_pemb_entry_type_t type;
    union {
        sxd_pemb_recorde_multicast_egress_t multicast_egress;
    } record;
} ku_pemb_reg_t;


/**
 * ku_prcr_reg structure is used to store the PRCR register parameters
 */
typedef struct ku_prcr_reg {
    uint8_t  op;
    uint16_t offset;
    uint16_t size;
    uint8_t  tcam_region_info[SXD_ACL_INFO_SIZE_BYTES];
    uint16_t dest_offset;
    uint8_t  dest_tcam_region_info[SXD_ACL_INFO_SIZE_BYTES];
} ku_prcr_reg_t;

/**
 * sxd_acl_paclr_acl_type enumerated type is used to note
 * the PTAR operation.
 */
typedef enum sxd_acl_pacl_acl_type {
    SXD_PACL_ACL_TYPE_ALL = 0,
    SXD_PACL_ACL_TYPE_L3  = 1,
} sxd_acl_pacl_acl_type_t;

/**
 * ku_pacl_reg structure is used to store the PACL register parameters
 */
typedef struct ku_pacl_reg {
    uint8_t                 egress;
    uint8_t                 valid;
    sxd_acl_pacl_acl_type_t acl_type;
    uint16_t                acl_id;
    uint8_t                 tcam_region_info[SXD_PACL_TCAM_REGIONS][SXD_ACL_INFO_SIZE_BYTES];
} ku_pacl_reg_t;

/**
 * sxd_acl_ptar_op enumerated type is used to note the
 * PTAR operation.
 */
typedef enum sxd_acl_ptar_op {
    SXD_PTAR_OP_ALLOCATE_E      = 0,
    SXD_PTAR_OP_RESIZE_E        = 1,
    SXD_PTAR_OP_DEALLOCATE_E    = 2,
    SXD_PTAR_OP_TEST_ALLOCATE_E = 3,
} sxd_acl_ptar_op_t;


/**
 * sxd_acl_ptar_action_type enumerated type is used to
 * note the PTAR action type.
 */
typedef enum sxd_acl_ptar_action_type {
    SXD_PTAR_DEFAULT_ACTION_E  = 0,
    SXD_PTAR_EXTENDED_ACTION_E = 1,
    SXD_PTAR_FLEX_ACTION_E     = 2,
    SXD_PTAR_FLEX_2_ACTION_E   = 2
} sxd_acl_ptar_action_type_t;


/**
 * sxd_acl_ptar_action_type enumerated type is used to
 * note the PTAR action type.
 */
typedef enum sxd_acl_ptar_key_type {
    SXD_PTAR_KEY_IPv4_FULL_E         = 0,
    SXD_PTAR_KEY_IPv6_FULL_E         = 1,
    SXD_PTAR_KEY_MAC_FULL_E          = 2,
    SXD_PTAR_KEY_MAC_IPv4_FULL_E     = 3,
    SXD_PTAR_KEY_MAC_SHORT_E         = 4,
    SXD_PTAR_KEY_CONFIGURABLE_FULL_E = 16,
    SXD_PTAR_KEY_FCOE_FULL_E         = 32,
    SXD_PTAR_KEY_FLEX_KEY_E          = 0x50,
    SXD_PTAR_KEY_FLEX_2_KEY_E        = 0x51
} sxd_acl_ptar_key_type_t;

/**
 * sxd_ptar_optimization_type_t enumerated type is used to note the TCAM
 * optimization mode.
 */
typedef enum sxd_ptar_optimization_type {
    SXD_PTAR_TCAM_NO_OPTIMIZATION_E   = 0,
    SXD_PTAR_TCAM_SOFT_OPTIMIZATION_E = 1,
    SXD_PTAR_TCAM_HARD_OPTIMIZATION_E = 2,
    SXD_PTAR_TCAM_RESERVED_E          = 3,
} sxd_ptar_optimization_type_t;

/**
 * sxd_ptar_packet_rate_t enumerated type is used to note the packet rate
 * for TCAM optimization mode. Granularity is 5%. Duplication number is used.
 */
typedef enum sxd_ptar_packet_rate {
    SXD_PTAR_PACKET_RATE_0_PCT  = 0,
    SXD_PTAR_PACKET_RATE_10_PCT = 2,
    SXD_PTAR_PACKET_RATE_20_PCT = 4,
    SXD_PTAR_PACKET_RATE_40_PCT = 8,
    SXD_PTAR_PACKET_RATE_80_PCT = 16,
} sxd_ptar_packet_rate_t;

typedef enum sxd_acl_ptar_direction {
    SXD_PTAR_ACL_DIRECTION_INGRESS_E = 0,
    SXD_PTAR_ACL_DIRECTION_EGRESS_E  = 1
} sxd_acl_ptar_direction_t;

/**
 * ku_ptar_reg structure is used to store the PTAR register parameters
 */
typedef struct ku_ptar_reg {
    sxd_acl_ptar_op_t            op;
    sxd_acl_ptar_action_type_t   action_type;
    sxd_acl_ptar_key_type_t      key_type;
    sxd_boolean_t                stateful_db_region;
    uint16_t                     region_size;
    uint16_t                     region_id;
    uint8_t                      atcam_dup;
    uint8_t                      ctcam_dup;
    sxd_ptar_packet_rate_t       packet_rate;
    sxd_ptar_optimization_type_t op_type;
    uint8_t                      tcam_region_info[SXD_TCAM_REGION_INFO_SIZE_BYTES];
    uint8_t                      flexible_key_id[SXD_FLEXIBLE_KEY_BLOCK_REG_SIZE_BYTES];
    sxd_acl_ptar_direction_t     direction;
    uint16_t                     region_id_dup[SXD_TCAM_REGOIN_ID_DUP];
} ku_ptar_reg_t;


/**
 * ku_puet_reg structure is used to store the PUET register
 * parameters
 */
typedef struct ku_puet_reg {
    uint8_t  index;
    uint16_t ethertype;
} ku_puet_reg_t;

/**
 * sxd_acl_direction enumerated type is used to note the ACL direction.
 *
 * NOTE: Any change to this enum requires alignments at least in
 * the following components:
 * 1. ACL Drop DB (look for ACL_DROP_USR_DEF_VAL_SET)
 * 2. WJH library (look for ACL DROP reasons and ACL directions)
 * 3. Drop monitor (look for SXD ACL direction)
 *
 */
typedef enum sxd_acl_direction {
    SXD_ACL_DIRECTION_INGRESS_E          = 0,
    SXD_ACL_DIRECTION_EGRESS_E           = 1,
    SXD_ACL_DIRECTION_RIF_INGRESS_E      = 2,
    SXD_ACL_DIRECTION_RIF_EGRESS_E       = 3,
    SXD_ACL_DIRECTION_TPORT_INGRESS_E    = 4,
    SXD_ACL_DIRECTION_TPORT_EGRESS_E     = 5,
    SXD_ACL_DIRECTION_CPU_INGRESS_E      = 6,
    SXD_ACL_DIRECTION_CPU_EGRESS_E       = 7,
    SXD_ACL_DIRECTION_SINGLE_POINT_MIN_E = SXD_ACL_DIRECTION_INGRESS_E,
    SXD_ACL_DIRECTION_SINGLE_POINT_MAX_E = SXD_ACL_DIRECTION_CPU_EGRESS_E,
    SXD_ACL_DIRECTION_SINGLE_POINT_NUM_E = SXD_ACL_DIRECTION_SINGLE_POINT_MAX_E + 1,
    SXD_ACL_DIRECTION_MULTI_POINTS_E     = SXD_ACL_DIRECTION_SINGLE_POINT_MAX_E + 1
} sxd_acl_direction_t;

/**
 * sxd_router_arp_operation_t enumerated type is used to note the ARP
 * operation.
 */
typedef enum sxd_router_arp_operation {
    SXD_ROUTER_ARP_OPERATION_ALLOCATE        = 0,
    SXD_ROUTER_ARP_OPERATION_WRITE           = 1,
    SXD_ROUTER_ARP_OPERATION_DEALLOCATE      = 2,
    SXD_ROUTER_ARP_OPERATION_WRITE_A_CLEARED = 3,
    SXD_ROUTER_ARP_OPERATION_CLEAR_A         = 2
} sxd_router_arp_operation_t;

/**
 * Adjacency Index.
 */
typedef uint16_t sxd_adj_index_t;

/**
 * Adjacency Index MSB.
 */
typedef uint8_t sxd_adj_index_msb_t;

/**
 * ARP ID.
 */
typedef uint32_t sxd_arp_id_t;

/**
 * ARP Info.
 */
typedef uint32_t sxd_arp_info_t;

/**
 * Ethernet Adjacency Parameters Layout
 */
typedef struct ku_struct_eth_adj_parameters {
    uint8_t destination_mac[6];
} ku_eth_adj_parameters_t;

/**
 * IPoIB Unicast Adjacency Parameters Layout
 */
typedef struct ku_pkey_uni_without_grh_parameters {
    uint8_t  sl;
    uint16_t dlid;
    uint32_t dqpn;
    uint8_t  my_lid;
} ku_pkey_uni_without_grh_parameters_t;

/**
 * IPoIB Unicast GRH Adjacency Parameters Layout
 */
typedef struct ku_pkey_uni_with_grh_parameters {
    uint8_t   sl;
    uint16_t  dlid;
    uint32_t  dqpn;
    uint8_t   my_lid;
    sxd_gid_t dgid;
} ku_pkey_uni_with_grh_parameters_t;

/**
 * IPoIB Multicast Adjacency Parameters Layout
 */
typedef struct ku_pkey_multi_parameters {
    uint8_t  sl;
    uint16_t dlid;
    uint8_t  tclass;
} ku_pkey_multi_parameters_t;

/**
 * MPLS Adjacency Parameters Layout
 */
typedef struct ku_mpls_adj_parameters {
    uint32_t nhlfe_ptr;
    uint8_t  tqos_profile;
    uint16_t ecmp_size;
    uint16_t underlay_router_interface;
} ku_mpls_adj_parameters_t;

/**
 * Underlay Destination IP Types
 */
typedef enum sxd_udip_type {
    SXD_UDIP_TYPE_IPV4                     = 0,
    SXD_UDIP_TYPE_IPV6                     = 1,
    SXD_UDIP_TYPE_AUTO_TUNNEL_IPV6_TO_IPV4 = 2,
    SXD_UDIP_TYPE_AUTO_TUNNEL_ISATAP       = 3,
} sxd_udip_type_e;

/**
 * L3 Tunnel Encap Adjacency Parameters Layout
 */
typedef struct ku_l3_tunnel_encap_adj_parameters {
    sxd_udip_type_e udip_type;
    union {
        uint32_t ipv4_udip;
        uint32_t ipv6_ptr;
    } prefix;
} ku_l3_tunnel_encap_adj_parameters_t;

/**
 * The new header type added by the NAT
 */
typedef enum sxd_nat4to6_new_header_type {
    SXD_NAT4TO6_NEW_HEADER_TYPE_IPV4 = 0,
    SXD_NAT4TO6_NEW_HEADER_TYPE_IPV6 = 1,
} sxd_nat4to6_new_header_type_e;

/**
 * The expected L3 protocol to handle
 */
typedef enum sxd_nat4to6_exp_l3 {
    SXD_NAT4TO6_EXP_L3_ANY  = 0,
    SXD_NAT4TO6_EXP_L3_IPV4 = 1,
    SXD_NAT4TO6_EXP_L3_IPV6 = 2,
} sxd_nat4to6_exp_l3_e;

/**
 * NAT Ipv4/IPv6 Adjacency Parameters Layout
 */
typedef struct ku_nat4to6_adj_parameters {
    sxd_nat4to6_new_header_type_e new_header_type;
    uint16_t                      ingress_rif;
    uint8_t                       qos_profile;
    sxd_nat4to6_exp_l3_e          exp_l3;
    union {
        uint32_t ipv4_udip;
        uint32_t ipv6_ptr;
    } udip;
} ku_nat4to6_adj_parameters_t;

/**
 * Re-lookup ECMP Adjacency Parameters Layout
 */
typedef struct ku_relookup_ecmp_adj_parameters {
    uint32_t      next_adjacency_ptr;
    uint32_t      next_ecmp_size;
    sxd_boolean_t rd;
    uint32_t      rehash_seed;
} ku_relookup_ecmp_adj_parameters_t;

/**
 * Re-lookup LPM Adjacency Parameters Layout
 */
typedef struct ku_relookup_lpm_adj_parameters {
    uint32_t      virtual_router;
    sxd_boolean_t rd;
    uint32_t      rehash_seed;
} ku_relookup_lpm_adj_parameters_t;

/*
 * RATR - adjacency_parameters
 */
typedef union ku_adj_parameters {
    ku_eth_adj_parameters_t              eth_adj_parameters;
    ku_pkey_uni_without_grh_parameters_t pkey_uni_without_grh_parameters;
    ku_pkey_uni_with_grh_parameters_t    pkey_uni_with_grh_parameters;
    ku_pkey_multi_parameters_t           pkey_multi_parameters;
    ku_mpls_adj_parameters_t             mpls_adj_parameters;
    ku_l3_tunnel_encap_adj_parameters_t  l3_tunnel_encap_adj_parameters;
    ku_nat4to6_adj_parameters_t          nat4to6_adj_parameters;
    ku_relookup_ecmp_adj_parameters_t    relookup_ecmp_adj_parameters;
    ku_relookup_lpm_adj_parameters_t     relookup_lpm_adj_parameters;
} ku_adj_parameters_t;

/**
 * sxd_router_adjacency_table_type enumerated type is used to note the Adjacency Entry Type
 * operation.
 */
typedef enum sxd_router_adjacency_table_type {
    ETHERNET             = 0,
    PKEY_UNI_WITHOUT_GRH = 1,
    PKEY_UNI_WITH_GRH    = 2,
    PKEY_MULTI           = 3,
    MPLS                 = 4,
    L3_TUNNEL_ENCAP      = 5,
    NAT4TO6              = 7,
    RELOOKUP_ECMP        = 8,
    RELOOKUP_LPM         = 9,
} sxd_router_adjacency_table_type_t;

/**
 * sxd_router_adjacency_table enumerated is used to identify the table type
 */

typedef enum sxd_router_adjacency_table {
    ETHERNET_UNICAST_ADJACENCY            = 0,
    IPoIB_UNICAST_AND_MULTICAST_ADJACENCY = 1,
    IPoIB_ALL_ROUTERS_ADJACENCY           = 2,
    IPoIB_IP_BROADCAST_ADJACENCY          = 3,
    IB_ALGO_ROUTING                       = 4,
} sxd_router_adjacency_table_t;

/**
 * sxd_router_adjacency_validate type is used to note if an
 * adjacency entry should be added or subtracted.
 */
typedef enum sxd_router_adjacency_validate {
    SXD_ROUTE_ADJECENCY_DELETE = 0,
    SXD_ROUTE_ADJECENCY_WRITE  = 1,
} sxd_router_adjacency_validate_t;

/**
 * Router Interface Group.
 */
typedef uint16_t sxd_rif_group_t;

/**
 * Router Interface.
 */
typedef uint16_t sxd_rif_t;

/**
 * sxd_router_route_action_t enumerated type is used to note the route action.
 */
typedef enum sxd_router_action_type {
    SXD_ROUTER_ROUTE_ACTION_PERMIT         = 0,
    SXD_ROUTER_ROUTE_ACTION_SOFT_DROP      = 1,
    SXD_ROUTER_ROUTE_ACTION_TRAP           = 2,
    SXD_ROUTER_ROUTE_ACTION_SOFT_DROP_TRAP = 3,
    SXD_ROUTER_ROUTE_ACTION_DENY           = 4,
} sxd_router_route_action_t;

/**
 * sxd_router_en_route_action_t enumerated type is used to note the route action in RouterEN.
 */
typedef enum sxd_router_en_action {
    SXD_ROUTER_EN_ACTION_NOP           = 0,
    SXD_ROUTER_EN_ACTION_TRAP          = 1,
    SXD_ROUTER_EN_ACTION_MIRROR_TO_CPU = 2,
    SXD_ROUTER_EN_ACTION_MIRROR        = 3,
    SXD_ROUTER_EN_ACTION_DISCARD_ERROR = 4,
    SXD_ROUTER_EN_ACTION_MIN           = SXD_ROUTER_EN_ACTION_NOP,
    SXD_ROUTER_EN_ACTION_MAX           = SXD_ROUTER_EN_ACTION_DISCARD_ERROR,
} sxd_router_en_action_t;

/**
 * ku_ratr_reg structure is used to store the RATR register parameters
 */
struct ku_ratr_reg {
    sxd_router_arp_operation_t        operation;
    sxd_router_adjacency_validate_t   valid;
    uint8_t                           activity;
    uint16_t                          size;
    sxd_router_adjacency_table_type_t type;
    uint8_t                           table;
    sxd_adj_index_t                   adjacency_index;
    sxd_rif_t                         egress_rif;
    ku_adj_parameters_t               adj_parameters;
    sxd_router_en_action_t            trap_action;
    sxd_adj_index_msb_t               adjacency_index_msb;
    uint16_t                          trap_id;
    sxd_counter_set_t                 counter_set;
};

/**
 * operation for RATRAD
 */
typedef enum sxd_ratrad_operation {
    SXD_RATRAD_OP_READ_ACTIVITY       = 0,
    SXD_RATRAD_OP_READ_CLEAR_ACTIVITY = 1,
} sxd_ratrad_operation_t;

/**
 * ku_ratrad_reg structure is used to store the RATRAD register parameters
 */
struct ku_ratrad_reg {
    sxd_ratrad_operation_t op;
    uint16_t               ecmp_size;
    uint32_t               adjacency_index;
    uint8_t                activity_record[SXD_RATRAD_MAX_REC_NUM];
};

/**
 * Virtual Router ID.
 */
typedef uint16_t sxd_vrid_t;

/**
 * FCF instance ID.
 */
typedef uint8_t sxd_fcf_id_t;

#define SX_FC_ADDR_LEN 3

typedef struct sxd_fc_addr {
    uint8_t fc_addr[SX_FC_ADDR_LEN];
} sxd_fc_addr_t;

/**
 * sxd_router_route_type_t enumerated type is used to note the
 * route type.
 */
typedef enum sxd_router_route_type {
    SXD_ROUTER_ROUTE_TYPE_IPV4              = 0,
    SXD_ROUTER_ROUTE_TYPE_IPV6              = 1,
    SXD_ROUTER_ROUTE_TYPE_IB_GID_SITE_LOCAL = 2,
} sxd_router_route_type_t;

/**
 * sxd_router_mc_route_type_t enumerated type is used to note the
 * multicast route type.
 */
typedef enum sxd_router_mc_route_type {
    SXD_ROUTER_MC_ROUTE_TYPE_IPV4_G0 = 0,
    SXD_ROUTER_MC_ROUTE_TYPE_IPV6_G0 = 1,
    SXD_ROUTER_MC_ROUTE_TYPE_IPV4_G1 = 2,
    SXD_ROUTER_MC_ROUTE_TYPE_IPV6_G1 = 3,
} sxd_router_mc_route_type_t;

typedef enum sxd_router_tcam_write_operation {
    /*On write register*/
    SXD_ROUTER_TCAM_WRITE          = 0,
    SXD_ROUTER_TCAM_UPDATE         = 1,
    SXD_ROUTER_TCAM_CLEAR_ACTIVITY = 2,
    SXD_ROUTER_TCAM_WRITE_CLEAR    = 3,
    /*On read register*/
    SXD_ROUTER_TCAM_READ              = 0,
    SXD_ROUTER_ACTIVITY_CLEAR_ON_READ = 1,
} sxd_router_tcam_write_operation_t;

typedef enum sxd_kvd_hash_operation {
    /*On write register*/
    SXD_KVD_HASH_OPERATION_ADD = 0,
    SXD_KVD_HASH_OPERATION_UPDATE,
    SXD_KVD_HASH_OPERATION_CLEAR_ACTIVITY,
    SXD_KVD_HASH_OPERATION_DELETE,
    SXD_KVD_HASH_OPERATION_DELETE_ALL,
    /*On read register*/
    SXD_KVD_HASH_OPERATION_READ       = 0,
    SXD_KVD_HASH_OPERATION_READ_CLEAR = 1,
} sxd_kvd_hash_operation_t;

typedef enum sxd_fcf_tcam_write_operation {
    SXD_FCF_TCAM_WRITE          = 0,
    SXD_FCF_TCAM_UPDATE         = 1,
    SXD_FCF_TCAM_CLEAR_ACTIVITY = 2,
} sxd_fcf_tcam_write_operation_t;

/**
 * sxd_router_qos_t enumerated type is used to note the route
 * quality of service .
 */
typedef enum {
    SXD_ROUTER_QOS_MAP_PRIO_FROM_DSCP = 0,
    SXD_ROUTER_QOS_PRESERVE_PRIO      = 1,
} sxd_router_qos_t;

/*
 * Egress Port Type for Fibre Channel protocols
 */
typedef enum sxd_ept {
    SXD_FCF_FCOE_VF_PORT  = 0,
    SXD_FCF_FCOE_VE_PORT  = 1,
    SXD_FCF_FC_VF_PORT    = 2,
    SXD_FCF_FC_VE_PORT    = 3,
    SXD_FCF_FCOIB_VF_PORT = 4,
    SXD_FCF_FCOIB_VE_PORT = 5,
} sxd_ept_t;

typedef enum sxd_counter_opcode {
    SXD_COUNTER_OPCODE_NOP            = 0,
    SXD_COUNTER_OPCODE_ADD_COUNTERS   = 1,
    SXD_COUNTER_OPCODE_FLUSH_COUNTERS = 2,
    SXD_COUNTER_OPCODE_CLEAR_COUNTERS = 8,
} sxd_counter_opcode_t;

/**
 * ku_mgpc_reg structure is used to store the MGPC register
 * parameters
 */
struct ku_mgpc_reg {
    sxd_counter_set_t                    counter_set;
    uint8_t                              counter_opcode; /** counter opcode */
    uint64_t __attribute__((aligned(8))) byte_counter;         /**<  byte counter*/
    uint64_t __attribute__((aligned(8))) packet_counter;         /**< packet counter*/
};

/**
 * ku_ruft_reg structure is used to store the RUFT register parameters
 */
struct ku_ruft_reg {
    uint8_t                           valid;
    sxd_router_route_type_t           route_type;
    sxd_router_tcam_write_operation_t operation;
    uint8_t                           activity;
    uint16_t                          offset;
    sxd_vrid_t                        router;
    uint32_t                          destination_ip[4];
    uint32_t                          destination_ip_mask[4];
    uint32_t                          ecmp_hash;
    uint32_t                          ecmp_hash_mask;
    sxd_router_route_action_t         route_action;
    uint8_t                           trap_group;
    uint16_t                          trap_id;
    uint8_t                           mirror_enable;
    uint8_t                           mirror_dst;
    uint8_t                           prio;
    uint8_t                           qos;
    uint16_t                          egress_rif;
    uint32_t                          ecmp_size;
    uint8_t                           table;
    sxd_adj_index_t                   adjacency_index;
};

/**
 * ku_ruht_reg structure is used to store the RUHT register parameters
 */
struct ku_ruht_reg {
    uint16_t                          offset;
    uint8_t                           offset_enable;
    uint8_t                           valid;
    sxd_router_route_type_t           route_type;
    sxd_router_tcam_write_operation_t operation;
    uint8_t                           activity;
    sxd_vrid_t                        router;
    uint32_t                          destination_ip[4];
    uint32_t                          ecmp_hash;
    uint32_t                          ecmp_hash_mask;
    sxd_router_route_action_t         route_action;
    uint8_t                           trap_group;
    uint16_t                          trap_id;
    uint8_t                           qos;
    uint8_t                           table;
    sxd_adj_index_t                   adjacency_index;
};

/**
 * ku_ruht_reg structure is used to store the RAUHT register parameters
 */
struct ku_rauht_reg {
    sxd_router_route_type_t  route_type;
    sxd_kvd_hash_operation_t operation;
    uint8_t                  activity;
    sxd_rif_t                rif;
    uint32_t                 destination_ip[4];
    sxd_router_en_action_t   trap_action;
    uint16_t                 trap_id;
    sxd_counter_set_t        counter_set;
    struct sx_ether_addr     mac_addr;
};

/**
 * Filter fields for RAUHTD
 */
typedef enum sxd_rauhtd_filter_fields {
    SXD_RAUHTD_FILTER_ACTIVE = 1 << 0,
    SXD_RAUHTD_FILTER_RIF    = 1 << 3,
} sxd_rauhtd_filter_fields_t;

/**
 * operation for RAUHTD
 */
typedef enum sxd_rauhtd_operation {
    SXD_RAUHTD_OP_DUMP_ENTRIES   = 0,
    SXD_RAUHTD_OP_CLEAR_ACTIVITY = 1,
} sxd_rauhtd_operation_t;

/**
 * sxd_rauhtd_ipv6_entry_t structure is used to store a single IPv6 RAUHTD entry
 */
typedef struct sxd_rauhtd_ipv6_entry {
    sxd_router_route_type_t type;
    uint8_t                 a;
    sxd_rif_t               rif;
    uint32_t                dip[4];
} sxd_rauhtd_ipv6_entry_t;

/**
 * sxd_rauhtd_ipv4_single_entry_t structure is used to store a single IPv4 RAUHTD entry
 */
typedef struct sxd_rauhtd_ipv4_single_entry {
    uint8_t   a;
    sxd_rif_t rif;
    uint32_t  dip;
} sxd_rauhtd_ipv4_single_entry_t;

/**
 * sxd_rauhtd_ipv4_entry_t structure is used to store the IPv4 RAUHTD record
 */
typedef struct sxd_rauhtd_ipv4_entry {
    uint8_t                        num_entries;
    sxd_router_route_type_t        type;
    sxd_rauhtd_ipv4_single_entry_t entry[4];
} sxd_rauhtd_ipv4_entry_t;

/**
 * sxd_rauhtd_dump_record_t is used to store the RAUHTD dump entries.
 */
typedef union sxd_rauhtd_dump_record {
    sxd_rauhtd_ipv4_entry_t ipv4_entry;
    sxd_rauhtd_ipv6_entry_t ipv6_entry;
} sxd_rauhtd_dump_record_t;

/**
 * ku_rauhtd_reg structure is used to store the RAUHTD register parameters
 */
struct ku_rauhtd_reg {
    uint8_t                  filter_fields;
    sxd_rauhtd_operation_t   op;
    uint8_t                  num_of_rec;
    uint8_t                  entry_a;    /* Boolean - entry active == TRUE */
    sxd_router_route_type_t  entry_type;
    sxd_rif_t                entry_rif;
    sxd_rauhtd_dump_record_t dump_record[SXD_RAUHTD_MAX_REC_NUM];
};

/**
 * sxd_acl_ptar_action_type enumerated type is used to
 * note the PTAR action type.
 */
enum sxd_rmft_ttl_cmd {
    SXD_RMFT_TTL_CMD_DEC = 0,
    SXD_RMFT_TTL_CMD_SET = 1,
};

/**
 * sxd_rmft_rpf_action_t enumerated type is used to note the RPF action type
 * in RMFT.
 */
typedef enum sxd_rmft_rpf_action {
    SXD_RMFT_RPF_ACTION_NONE        = 0,
    SXD_RMFT_RPF_ACTION_DISCARD     = 1,
    SXD_RMFT_RPF_ACTION_TRAP        = 2,
    SXD_RMFT_RPF_ACTION_DIRECTIONAL = 4,
} sxd_rmft_rpf_action_t;

/**
 * ku_rmft_reg structure is used to store the RMFT register parameters
 */
struct ku_rmft_reg {
    uint8_t                           valid;
    sxd_router_route_type_t           route_type;
    sxd_router_tcam_write_operation_t operation;
    uint8_t                           activity;
    uint16_t                          offset;
    sxd_vrid_t                        router;
    uint32_t                          destination_ip[4];
    uint32_t                          destination_ip_mask[4];
    uint32_t                          source_ip[4];
    uint32_t                          source_ip_mask[4];
    uint32_t                          ecmp_hash;
    uint32_t                          ecmp_hash_mask;
    sxd_router_route_action_t         route_action;
    uint8_t                           trap_group;
    uint16_t                          trap_id;
    uint8_t                           qos;
    uint8_t                           ttl_cmd;
    uint8_t                           ttl_value;
    sxd_rmft_rpf_action_t             rpf;
    uint8_t                           assert_check;
    sxd_rif_t                         expected_ingress_rif;
};

/**
 * ku_rmft_v2_reg structure is used to store the RMFTv2 register parameters
 */
struct ku_rmft_v2_reg {
    sxd_boolean_t                     valid;
    sxd_router_mc_route_type_t        route_type;
    sxd_router_tcam_write_operation_t operation;
    sxd_boolean_t                     activity;
    uint16_t                          offset;
    sxd_vrid_t                        router;
    uint16_t                          irif;
    sxd_boolean_t                     irif_mask;
    uint32_t                          destination_ip[4];
    uint32_t                          destination_ip_mask[4];
    uint32_t                          source_ip[4];
    uint32_t                          source_ip_mask[4];
    sxd_flex_action_set_t             flexible_action_set;
};

/**
 * ku_rmftad_reg structure is used to store the RMFTAD register parameters
 */
struct ku_rmftad_reg {
    uint8_t                 operation;
    sxd_router_route_type_t route_type;
    uint16_t                offset;
    uint16_t                num_entries;
    uint32_t                activities[SXD_RMFTAD_ACTIVITIES_VECTOR_SIZE];
};

/**
 * ku_ptcead_reg structure is used to store the PTCEAD register
 * parameters
 */
struct ku_ptcead_reg {
    uint8_t  operation;
    uint16_t offset;
    uint16_t num_entries;
    uint8_t  tcam_region_info[SXD_TCAM_REGION_INFO_SIZE_BYTES];
    uint32_t activities[SXD_PTCEAD_ACTIVITIES_VECTOR_SIZE];
};

/**
 * sxd_router_ecmp_hash_type_t enumerated type is used to store router ECMP hash
 * type.
 */
typedef enum sxd_router_ecmp_hash_type {
    SXD_ROUTER_ECMP_HASH_TYPE_CRC    = 0,
    SXD_ROUTER_ECMP_HASH_TYPE_XOR    = 1,
    SXD_ROUTER_ECMP_HASH_TYPE_RANDOM = 2,
    SXD_ROUTER_ECMP_HASH_TYPE_CRC2   = 3,
} sxd_router_ecmp_hash_type_t;

/**
 * ku_recr_reg structure is used to store the RECR register parameters
 */
struct ku_recr_reg {
    uint8_t                     symmetric_hash;
    sxd_router_ecmp_hash_type_t hash_type;
    uint32_t                    hash_configuration;
    uint32_t                    seed;
};

/**
 * ku_recr_v2_reg structure is used to store the RECRv2 register parameters
 */
struct ku_recr_v2_reg {
    uint8_t                              per_port_configuration;
    uint8_t                              local_port;
    uint8_t                              lp_msb;    /**< local_port msb */
    uint8_t                              symmetric_hash;
    sxd_router_ecmp_hash_type_t          hash_type;
    uint32_t                             seed;
    uint32_t                             general_fields;
    uint16_t                             outer_header_enables;
    uint32_t                             outer_header_field_enables[5];
    uint16_t                             inner_header_enables;
    uint64_t __attribute__((aligned(8))) inner_header_field_enables;
};

/**
 * sxd_router_tcam_type_t enumerated type is used to note the TCAM type.
 */
typedef enum sxd_router_tcam_type {
    SXD_ROUTER_TCAM_TYPE_IPV4_UNICAST     = 0,
    SXD_ROUTER_TCAM_TYPE_IPV4_MULTICAST   = 1,
    SXD_ROUTER_TCAM_TYPE_IPV6_UNICAST     = 2,
    SXD_ROUTER_TCAM_TYPE_IPV6_MULTICAST   = 3,
    SXD_ROUTER_TCAM_TYPE_IPV4_HOST_TABLE  = 4,
    SXD_ROUTER_TCAM_TYPE_IPV6_HOST_TABLE  = 5,
    SXD_ROUTER_TCAM_TYPE_IPV4_MULTICAST_1 = 6,
    SXD_ROUTER_TCAM_TYPE_IPV6_MULTICAST_1 = 7,
    SXD_ROUTER_TCAM_TYPE_INVALID
} sxd_router_tcam_type_t;

/**
 * sxd_router_tcam_operation_t enumerated type is used to note the TCAM
 * operation.
 */
typedef enum sxd_router_tcam_operation {
    SXD_ROUTER_TCAM_OPERATION_ALLOCATE   = 0,
    SXD_ROUTER_TCAM_OPERATION_RESIZE     = 1,
    SXD_ROUTER_TCAM_OPERATION_DEALLOCATE = 2,
    SXD_ROUTER_TCAM_OPERATION_TEST       = 3,
} sxd_router_tcam_operation_t;

/**
 * sxd_router_optimization_type_t enumerated type is used to note the TCAM
 * optimization mode.
 */
typedef enum sxd_router_optimization_type_ {
    SXD_ROUTER_TCAM_NO_OPTIMIZATION   = 0,
    SXD_ROUTER_TCAM_SOFT_OPTIMIZATION = 1,
    SXD_ROUTER_TCAM_HARD_OPTIMIZATION = 2,
    SXD_ROUTER_TCAM_RESERVED          = 3,
} sxd_router_optimization_type_t;


/**
 * ku_rtar_reg structure is used to store the RTAR register parameters
 */
struct ku_rtar_reg {
    sxd_router_tcam_operation_t    operation;
    sxd_boolean_t                  external_bind;
    sxd_router_tcam_type_t         type;
    uint16_t                       tcam_size;
    sxd_router_optimization_type_t op_type;
};

/**
 * Router Interface List - Encoding of this field depends on the type field.
 */

typedef struct ku_eth_pkey_adjacency_list {
    uint16_t rif_table;
    uint16_t adjacency_index;
} ku_eth_pkey_adjacency_list_t;

typedef struct ku_eth_only_rif_list {
    uint32_t rif_list[128];
} ku_eth_only_rif_list_t;

typedef struct ku_eth_pkey_rif_list {
    uint8_t                      reserved1[3];
    uint8_t                      size;
    ku_eth_pkey_adjacency_list_t adj_list[127];
} ku_eth_pkey_rif_list_t;

typedef union ku_rif_list {
    ku_eth_only_rif_list_t eth_only_rif_list;
    ku_eth_pkey_rif_list_t eth_pkey_rif_list;
} ku_rif_list_t;

/**
 * sxd_rigr_op_t enumerated type is used to indicates the encoding of the router_interface_list field
 */
typedef enum sxd_rigr_op {
    RIGR_OP_ADD_RIF         = 1,
    RIGR_OP_REMOVE_RIF      = 2,
    RIGR_OP_REMOVE_ALL_RIFS = 3,
    RIGR_OP_UPDATE_RIF      = 4,
} sxd_rigr_op_t;

/**
 * sxd_rigr_encoding_t enumerated type is used to indicates the
 * encoding of the router_interface_list field
 */
typedef enum sxd_rigr_encoding {
    ETH_ONLY     = 0,
    ETH_AND_PKEY = 1,
} sxd_rigr_encoding_t;

/**
 * ku_rigr_reg structure is used to store the RIGR register parameters
 */
struct ku_rigr_reg {
    sxd_router_route_type_t types;
    uint8_t                 op;
    sxd_rigr_encoding_t     enc;
    uint16_t                offset;
    ku_rif_list_t           rif_list;
};

#define SXD_RMEIR_BIT_VECTOR_MAX 256

typedef struct sxd_rmeir_bit_vector {
    sxd_boolean_t bit_vector[SXD_RMEIR_BIT_VECTOR_MAX];
} sxd_rmeir_bit_vector_t;

#define SXD_RMEIR_ENTRIES_NUM_MAX 16

/**
 * ku_rmeir_reg structure is used to store the RMEIR register parameters
 */
struct ku_rmeir_reg {
    uint32_t               expected_irif_list_index;
    uint8_t                num_entries;
    sxd_rmeir_bit_vector_t expected_irif_bit_vector[SXD_RMEIR_ENTRIES_NUM_MAX];
};

#define SXD_RMID_EGRESS_PORT_MAX 256

/**
 * ku_rmid_reg structure is used to store the RMID register parameters
 */
struct ku_rmid_reg {
    uint32_t      rmid_index;
    uint16_t      rmpe_index;
    sxd_boolean_t egress_port[SXD_RMID_EGRESS_PORT_MAX];
};

#define SXD_RMPU_MAX 64

/**
 * ku_rmpu_reg structure is used to store the RMPU register parameters
 */
struct ku_rmpu_reg {
    uint8_t       local_port;
    uint8_t       lp_msb;    /**< local_port msb */
    sxd_boolean_t op;
    uint8_t       size;
    uint32_t      rmid_index[SXD_RMPU_MAX];
};

/**
 * ku_router_vlan_interface_properties_t struct is used to store the router interface properties when the router interface type is vlan.
 */

typedef struct ku_router_vlan_interface_properties {
    uint8_t  swid;
    uint16_t vlan_id;
    uint16_t efid;
    uint8_t  mac_profile_id;
    uint8_t  router_interface_mac[6];
    uint8_t  vrrp_id_ipv6;
    uint8_t  vrrp_id_ipv4;
} ku_router_vlan_interface_properties_t;


/**
 * ku_router_fid_interface_properties_t struct is used to store the router interface properties when the router interface type is fid.
 */

typedef struct ku_router_fid_interface_properties {
    uint8_t  swid;
    uint16_t fid;
    uint8_t  mac_profile_id;
    uint8_t  router_interface_mac[6];
    uint8_t  vrrp_id_ipv6;
    uint8_t  vrrp_id_ipv4;
} ku_router_fid_interface_properties_t;


/**
 * ku_router_sub_port_interface_properties_t struct is used to store the router interface properties when the router interface type is sub_port.
 */
typedef struct ku_router_sub_port_interface_properties {
    uint8_t  ar;
    uint8_t  lag;
    uint16_t system_port;
    uint16_t efid;
    uint8_t  mac_profile_id;
    uint8_t  router_interface_mac[6];
    uint16_t vlan_id;
    uint8_t  vrrp_id_ipv6;
    uint8_t  vrrp_id_ipv4;
} ku_router_sub_port_interface_properties_t;

/**
 * ku_router_l3_tunnel_interface_properties_t struct is used to store the router interface properties when the router interface type is L3 tunnel.
 */
typedef struct ku_router_l3_tunnel_interface_properties {
    uint8_t  type;
    uint8_t  options;
    uint16_t uvr;
    uint16_t underlay_router_interface;
    uint32_t usip[4];
    uint32_t gre_key;
} ku_router_l3_tunnel_interface_properties_t;

/**
 * ku_router_generic_tunnel_interface_properties_t struct is used to store the router interface properties when the router interface type is a generic tunnel.
 */
typedef struct ku_router_usip_tunnel_interface_properties {
    uint32_t usip[4];
} ku_router_usip_tunnel_interface_properties_t;

/**
 * ku_router_loopback_interface_properties_t struct is used to store
 * the router interface properties when the router interface
 * type is tunnel.
 */
typedef struct ku_router_loopback_interface_properties {
    uint8_t protocol;
    union {
        ku_router_l3_tunnel_interface_properties_t   l3_tunnel_interface;
        ku_router_usip_tunnel_interface_properties_t usip_tunnel_interface;
    } properties;
} ku_router_loopback_interface_properties_t;

/**
 * ku_router_pkey_interface_properties_t struct is used to store the router interface properties when the router interface type is pkey.
 */
typedef struct ku_router_pkey_interface_properties {
    uint8_t  swid;
    uint16_t pkey;
    uint8_t  scope;
    uint32_t qkey;
    uint32_t qpn;
} ku_router_pkey_interface_properties_t;

/**
 * ku_router_ib_swid_interface_properties_t struct is used to store the router interface properties when the router interface type is ib swid.
 */
typedef struct ku_router_ib_swid_interface_properties {
    uint8_t                              swid;
    uint16_t                             lid;
    uint8_t                              lmc;
    uint64_t __attribute__((aligned(8))) guid;
} ku_router_ib_swid_interface_properties_t;

/**
 * rif_properties is used to store the router interface properties depending on the router interface type.
 */
typedef union ku_rif_properties {
    ku_router_vlan_interface_properties_t     vlan_interface;
    ku_router_fid_interface_properties_t      fid_interface;
    ku_router_sub_port_interface_properties_t sub_port_interface;
    ku_router_loopback_interface_properties_t loopback_interface;
    ku_router_pkey_interface_properties_t     pkey_interface;
    ku_router_ib_swid_interface_properties_t  ib_swid_interface;
} ku_rif_properties_t;

/**
 * sxd_router_interface_type_t enumerated type is used to indicates the router interface type
 * Note: These values are used in the "type" field that was formerly in RITR bits 24-25, and
 *       was recently expanded to include bit 23.  In addition, a "type_ib" field was added
 *       in bit 22, which changes the meaning of the value in bits 23-25.  Taking all 4 bits
 *       together, the effect is that the original numerical values are shifted by 2, i.e.
 *       port becomes 4 instead of 1, pkey becomes 8 instead of 2, odd multiples of 2 are
 *       used for new values not associated with IB, and odd numbers are used for IB types.
 *       Thus, backward compatibility is achieved provided the parser is also updated.
 */
typedef enum sxd_router_interface_type {
    VLAN_INTERFACE         = 0,
    IB_SWID_INTERFACE      = 1,
    FID_INTERFACE          = 2,
    IB_SWID_PORT_INTERFACE = 3,
    SUB_PORT_INTERFACE     = 4,
    IB_PORT_INTERFACE      = 5,
    LOOPBACK_INTERFACE     = 6,
    PKEY_INTERFACE         = 8,
    INTERFACE_MIN          = VLAN_INTERFACE,
    INTERFACE_MAX          = PKEY_INTERFACE
} sxd_router_interface_type_t;

/**
 * sxd_router_interface_op_t enumerated type is used to indicates the router interface op
 */
typedef enum sxd_router_interface_op {
    INTERFACE_CREATE_OR_EDIT = 0,
    INTERFACE_DELETE         = 1
} sxd_router_interface_op_t;

/**
 * ku_ritr_reg structure is used to store the RITR register parameters
 */
struct ku_ritr_reg {
    uint8_t                     enable;
    uint8_t                     valid;
    uint8_t                     ipv4_enable;
    uint8_t                     ipv6_enable;
    uint8_t                     ipv4_mc;
    uint8_t                     ipv6_mc;
    sxd_router_interface_type_t type;
    uint8_t                     op;
    uint8_t                     mpls;
    sxd_rif_t                   router_interface;
    uint8_t                     ipv4_forward_enable;
    uint8_t                     ipv6_forward_enable;
    uint8_t                     ipv4_forward_mc;
    uint8_t                     ipv6_forward_mc;
    uint8_t                     lb_en;
    uint8_t                     urpf_en_ipv4;
    uint8_t                     urpf_en_ipv6;
    uint8_t                     urpf_strict;
    uint8_t                     urpf_ad;
    uint8_t                     mpls_forward;
    sxd_vrid_t                  router;
    ku_rif_properties_t         rif_properties;
    uint8_t                     ttl_threshold;
    uint16_t                    mtu;
    sxd_counter_set_t           ingress_counter_set;
    sxd_counter_set_t           egress_counter_set;
};

/**
 * sxd_ritr_loopback_protocol_t enumerated type is used to note the possible loopback protocols.
 */
typedef enum sxd_ritr_loopback_protocol {
    SXD_ROUTER_LOOPBACK_PROTOCOL_IPV4      = 0,
    SXD_ROUTER_LOOPBACK_PROTOCOL_IPV6      = 1,
    SXD_ROUTER_LOOPBACK_PROTOCOL_GENERIC   = 2,
    SXD_ROUTER_LOOPBACK_PROTOCOL_USIP_IPV4 = 3,
    SXD_ROUTER_LOOPBACK_PROTOCOL_USIP_IPV6 = 4,
} sxd_ritr_loopback_protocol_t;

/**
 * sxd_ritr_ipinip_tunnel_encap_type_t enumerated type is used to note the possible encapsulation types.
 */
typedef enum sxd_ritr_ipinip_tunnel_encap_type {
    SXD_TUNNEL_ENCAP_TYPE_IP_IN_IP            = 0, /**< Tunnel is IPinIP */
    SXD_TUNNEL_ENCAP_TYPE_IP_IN_GRE_IN_IP     = 1, /**< Tunnel is GRE, no key */
    SXD_TUNNEL_ENCAP_TYPE_IP_IN_GRE_KEY_IN_IP = 2, /**< Tunnel is GRE, with a key */
} sxd_ritr_ipinip_tunnel_encap_type_t;

/**
 * sxd_ritr_ipinip_tunnel_options_t enumerated type is used to note the possible value of options field.
 *
 * Note: should be used only when encapsulation type is TUNNEL_ENCAP_TYPE_IP_IN_GRE_KEY_IN_IP.
 */
typedef enum sxd_ritr_ipinip_tunnel_options {
    SXD_TUNNEL_KEY_GRE_KEY           = 0, /**< The key is defined by gre_key */
    SXD_TUNNEL_KEY_GRE_KEY_FROM_HASH = 1, /**< The 24msbs of the key are set by ipip_gre_key_for_hash */
} sxd_ritr_ipinip_tunnel_options_t;

/**
 * sxd_router_interface_type_t enumerated type is used to indicates the router interface type
 */
typedef enum sxd_rgcr_rpf_mode {
    SXD_RGCR_RPF_MODE_ENABLE  = 0,
    SXD_RGCR_RPF_MODE_DISABLE = 1,
} sxd_rgcr_rpf_mode_t;

typedef enum sxd_rgcr_pcp_rw_mode {
    SXD_RGCR_PCP_RW_MODE_PRESERVE = 0,
    SXD_RGCR_PCP_RW_MODE_DISABLE  = 2,
    SXD_RGCR_PCP_RW_MODE_ENABLE   = 3,
} sxd_rgcr_pcp_rw_mode_t;

typedef enum sxd_rgcr_usp_mode {
    SXD_RGCR_USP_MODE_PRESERVE    = 0,
    SXD_RGCR_USP_MODE_RECALCULATE = 1,
} sxd_rgcr_usp_mode_t;

typedef enum sxd_rgcr_op_type {
    SXD_RGCR_OP_TYPE_OPTIMIZATION_NONE = 0,
    SXD_RGCR_OP_TYPE_OPTIMIZATION_SOFT = 1,
    SXD_RGCR_OP_TYPE_OPTIMIZATION_HARD = 2,
    SXD_RGCR_OP_TYPE_RESERVED          = 3,
} sxd_rgcr_op_type_t;

/**
 * sxd_rgcr_packet_rate_t enumerated type is used to note the packet rate
 * for TCAM optimization mode. Granularity is 5%. Duplication number is used.
 */
typedef enum sxd_rgcr_packet_rate {
    SXD_RGCR_PACKET_RATE_0_PCT  = 0,
    SXD_RGCR_PACKET_RATE_10_PCT = 2,
    SXD_RGCR_PACKET_RATE_20_PCT = 4,
    SXD_RGCR_PACKET_RATE_40_PCT = 8,
    SXD_RGCR_PACKET_RATE_80_PCT = 16,
} sxd_rgcr_packet_rate_t;

typedef enum sxd_rgcr_activity_dis {
    SXD_RGCR_ACTIVITY_ENABLED  = 0,
    SXD_RGCR_ACTIVITY_DISABLED = 1,
} sxd_rgcr_activity_dis_t;

typedef enum sxd_rgcr_mpls_enable {
    SXD_RGCR_MPLS_DISABLE = 0,
    SXD_RGCR_MPLS_ENABLE  = 1,
} sxd_rgcr_mpls_enable_t;

typedef enum sxd_rgcr_relookup_rehash_type {
    SXD_RGCR_RELOOKUP_REHASH_TYPE_CRC    = 0,
    SXD_RGCR_RELOOKUP_REHASH_TYPE_XOR    = 1,
    SXD_RGCR_RELOOKUP_REHASH_TYPE_RANDOM = 2,
} sxd_rgcr_relookup_rehash_type_e;

/**
 * ku_rgcr_reg structure is used to store the RGCR register parameters
 */
struct ku_rgcr_reg {
    uint8_t                 ipv4_enable;
    uint8_t                 ipv6_enable;
    uint8_t                 mpls_enable;
    uint16_t                max_vlan_router_interfaces;
    uint16_t                max_port_router_interfaces;
    uint16_t                max_pkey_router_interfaces;
    uint16_t                max_router_interfaces;
    uint16_t                max_virtual_routers;
    uint8_t                 grht;
    sxd_rgcr_usp_mode_t     usp;
    sxd_rgcr_pcp_rw_mode_t  pcp_rw;
    uint8_t                 ipb;
    uint8_t                 allr;
    uint8_t                 mcsi;
    sxd_rgcr_rpf_mode_t     rpf;
    sxd_rgcr_op_type_t      ipv6_op_type;
    sxd_rgcr_packet_rate_t  ipv6_packet_rate;
    sxd_rgcr_op_type_t      ipv4_op_type;
    sxd_rgcr_packet_rate_t  ipv4_packet_rate;
    sxd_rgcr_activity_dis_t activity_dis_uc_route_entry;
    sxd_rgcr_activity_dis_t activity_dis_host_entry;
    sxd_rgcr_activity_dis_t activity_dis_adjacency_entry;
    uint8_t                 grh_hop_limit;
    uint32_t                expected_irif_list_index_base;
};

/**
 * ku_rdpm_reg structure is used to store the RDPM register parameters
 */
struct ku_rdpm_reg {
    uint8_t dscp_update[DSCP_CODES_NUMBER];    /**< dscp_update - whether to update this DSCP mapping in HW */
    uint8_t color[DSCP_CODES_NUMBER];          /**< color mapping per DSCP value */
    uint8_t priority[DSCP_CODES_NUMBER];       /**< priority mapping per DSCP value - Priority */
};

/**
 * ku_access_rdpm_reg structure is used to store the access register RDPM command parameters
 */
struct ku_access_rdpm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rdpm_reg      rdpm_reg; /**< rdpm_reg - rdpm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * rrcr operation
 */
typedef enum sxd_rrcr_opcode {
    SXD_RRCR_OPCODE_MOVE = 0,
    SXD_RRCR_OPCODE_COPY = 1,
} sxd_rrcr_opcode_t;

/**
 * ku_rrcr_reg structure is used to router rules move/copy
 * support
 */
struct ku_rrcr_reg {
    sxd_rrcr_opcode_t      op; /**< opcode - 0 - move, 1 -copy */
    uint16_t               offset; /**< offset - source offset */
    uint16_t               size; /**< size - num of entries to move/copy */
    sxd_router_tcam_type_t table_id;           /**< table_id - defines  the region (same coding as RTAR) */
    uint16_t               dest_offset; /**< dest_offset - dest_source offset */
};

/**
 * sxd_router_counter_operation_t enumerated type is used to note the Counter
 * Set operation.
 */
typedef enum sxd_router_counter_operation {
    SXD_ROUTER_COUNTER_OPERATION_NOP      = 0,
    SXD_ROUTER_COUNTER_OPERATION_ALLOCATE = 1,
    SXD_ROUTER_COUNTER_OPERATION_TEST     = 2,
    SXD_ROUTER_COUNTER_OPERATION_FREE     = 3,
} sxd_router_counter_operation_t;

/**
 * ku_rica_reg structure is used to store the RICA register parameters
 */
struct ku_rica_reg {
    sxd_router_counter_operation_t operation; /**< operation - Counter Operation */
    uint8_t                        index; /**< index - Counter Set ID */
    sxd_counter_set_t              ingress_counter_set; /**< ingress_counter_set - Opaque ID */
    sxd_counter_set_t              egress_counter_set; /**< egress_counter_set - Opaque ID */
};

/**
 * Router maximum counter set.
 */
#define SXD_ROUTER_COUNTER_SET_MAX (31)

/**
 * ku_ricnt_reg structure is used to store the RICNT register parameters
 */
struct ku_ricnt_reg {
    uint8_t                              clr;  /**< clr - Clear Counters */
    uint8_t                              flush; /**< Flush - Flush Counters */
    uint8_t                              add;  /**< Add - Add given counters to index */
    uint8_t                              gl;   /**< gl - Global */
    sxd_counter_set_t                    cntr_handle; /**< index - Counter set index */
    uint64_t __attribute__((aligned(8))) cntr[SXD_ROUTER_COUNTER_SET_MAX]; /**< cntr - Counter Set */
};


/*
 * RALTA operation
 */
typedef enum sxd_ralta_operation {
    SXD_RALTA_OPERATION_ALLOCATE   = 0,
    SXD_RALTA_OPERATION_DEALLOCATE = 1,
} sxd_ralta_operation_t;

#define SXD_SHSPM_TREE_DEFAULT_IPV4            0
#define SXD_SHSPM_TREE_DEFAULT_IPV6            1
#define SXD_SHSPM_TREE_ISSU_BANK1_DEFAULT_IPV4 0
#define SXD_SHSPM_TREE_ISSU_BANK1_DEFAULT_IPV6 2
#define SXD_SHSPM_TREE_ISSU_BANK2_DEFAULT_IPV4 1
#define SXD_SHSPM_TREE_ISSU_BANK2_DEFAULT_IPV6 3
#define SXD_SHSPM_TREE_USER_FIRST              2
#define SXD_SHSPM_TREE_BANK1_USER_FIRST        4
#define SXD_SHSPM_TREE_BANK2_USER_FIRST        5

#define SXD_RALST_NO_CHILD 0xFF

/**
 * sxd_ralue_format_t enumerated type is used to note the
 * format for RALUE register.
 */
typedef enum sxd_ralue_action_type {
    SXD_RALUE_ACTION_TYPE_REMOTE = 0,
    SXD_RALUE_ACTION_TYPE_LOCAL  = 1,
    SXD_RALUE_ACTION_TYPE_IP2ME  = 2,
    SXD_RALUE_ACTION_TYPE_AR     = 3,
} sxd_ralue_action_type_t;

/**
 * sxd_ralue_type_t enumerated type is used to note the
 * type of RALUE register.
 */
typedef enum sxd_ralue_type {
    SXD_RALUE_TYPE_MARKER       = 1,
    SXD_RALUE_TYPE_ROUTE        = 2,
    SXD_RALUE_TYPE_ROUTE_MARKER = 3,
} sxd_ralue_type_t;

/**
 * ku_ralue_action_remote structure is used to store the RALUE action remote field parameters
 */
struct ku_ralue_action_remote {
    sxd_router_en_action_t trap_action;
    uint16_t               trap_id;
    uint32_t               adjacency_index;
    uint16_t               ecmp_size;
};

/**
 * ku_ralue_action_local structure is used to store the RALUE action local field parameters
 */
struct ku_ralue_action_local {
    sxd_router_en_action_t trap_action;
    uint16_t               trap_id;
    sxd_rif_t              egress_rif;
};

/**
 * ku_ralue_action_ip2me structure is used to store the RALUE action ip2me field parameters
 */
struct ku_ralue_action_ip2me {
    uint8_t  valid;
    uint32_t tunnel_ptr;
};

/**
 * ku_ralue_action_ar structure is used to store the RALUE action AR field parameters
 */
struct ku_ralue_action_ar {
    sxd_router_en_action_t     trap_action;
    uint16_t                   trap_id;
    sxd_ar_lookup_profile_id_t ar_lookup_prof_id;
    uint32_t                   arft_ptr;
    uint16_t                   ecmp_size;
    uint16_t                   arlpgt_ptr;
};

/**
 * ku_ralue_action structure is used to store the RALUE action field parameters
 */
union ku_ralue_action {
    struct ku_ralue_action_remote remote;
    struct ku_ralue_action_local  local;
    struct ku_ralue_action_ip2me  ip2me;
    struct ku_ralue_action_ar     ar;
};

/**
 * ku_ralue_reg structure is used to store the RALUE register parameters
 */
struct ku_ralue_reg {
    sxd_router_route_type_t  protocol;
    sxd_kvd_hash_operation_t operation;
    uint8_t                  activity;
    sxd_vrid_t               router;
    uint8_t                  update_entry_type;
    uint8_t                  update_bmp_len;
    uint8_t                  update_action_fields;
    uint8_t                  prefix_len;
    uint32_t                 destination_ip[4];
    sxd_ralue_type_t         entry_type;
    uint8_t                  bmp_len;
    sxd_ralue_action_type_t  action_type;
    union ku_ralue_action    action;
    sxd_counter_set_t        counter_set;
};
/*
 * ku_xm_cmd_ipv4_route structure is used to store the XMDR ipv4 cmd as part of the transaction field parameters
 */
typedef struct ku_xm_cmd_ipv4_route {
    uint32_t flags : 12;
    uint32_t seq_number : 12;
    uint32_t command_id : 8;
    /*----------------------------------------------------------*/
    uint16_t vrid;
    uint8_t  trap_id_num : 4;
    uint8_t  trap_action : 4;
    uint8_t  op_code;
    /*----------------------------------------------------------*/
    uint8_t action_type : 4;
    uint8_t entry_type : 4;
    uint8_t reserved0;
    uint8_t bmp_len;
    uint8_t prefix_len;
    /*----------------------------------------------------------*/
    uint32_t counter_index : 24;
    uint32_t counter_set_type : 8;
    /*----------------------------------------------------------*/
    uint32_t entry0;
    /*----------------------------------------------------------*/
    uint32_t entry1;
    /*----------------------------------------------------------*/
    uint32_t reserved1;
    /*----------------------------------------------------------*/
    uint32_t dip;
    /*----------------------------------------------------------*/
} ku_xm_cmd_ipv4_route_t;

/**
 * ku_ralbu_reg structure is used to store the RALBU register parameters
 */
struct ku_ralbu_reg {
    sxd_router_route_type_t protocol;
    sxd_vrid_t              router;
    uint8_t                 old_bmp;
    uint8_t                 bin;
    uint8_t                 new_bmp;
    uint8_t                 prefix_len;
    uint32_t                destination_ip[4];
};

/**
 * ku_rtca_reg structure is used to store the RTCA register parameters
 */
struct ku_rtca_reg {
    uint8_t   swid;   /**< swid - Switch partition ID */
    uint8_t   lmc;    /**< lmc  - Lid Mask Count*/
    uint16_t  lid;    /**< lid  - Base LID for the port*/
    sxd_gid_t gid;     /**< gid  - Global ID*/
};

/**
 * sxd_tca_log_pstate_type_t enumerated type is used to indicates the TCA logical port state type
 */
typedef enum sxd_tca_log_pstate_type {
    SXD_TCA_LOG_PSTATE_DOWN   = 0,
    SXD_TCA_LOG_PSTATE_INIT   = 1,
    SXD_TCA_LOG_PSTATE_ARM    = 2,
    SXD_TCA_LOG_PSTATE_ACTIVE = 3,
} sxd_tca_log_pstate_type_t;

/**
 * sxd_tca_ phy_pstate_type_t enumerated type is used to indicates the TCA physical port state type
 */
typedef enum sxd_tca_phy_pstate_type {
    SXD_TCA_PHY_PSTATE_DOWN    = 0,
    SXD_TCA_PHY_PSTATE_POLLING = 1,
    SXD_TCA_PHY_PSTATE_UP      = 2,
} sxd_tca_phy_pstate_type_t;

/**
 * ku_rtps_reg structure is used to store the RTPS register parameters
 */
struct ku_rtps_reg {
    uint8_t                   swid;     /**< swid - Switch partition ID */
    sxd_tca_log_pstate_type_t tca_log_pstate;      /**< TCA logical port state*/
    sxd_tca_phy_pstate_type_t tca_phy_pstate;      /**< TCA physical port state*/
    sxd_tca_log_pstate_type_t switch_log_pstate;      /**< Switch logical port state*/
    sxd_tca_phy_pstate_type_t switch_phy_pstate;      /**< Switch physical port state*/
};


/**
 * ku_rcap_reg structure is used to store the RCAP register parameters
 */
struct ku_rcap_reg {
    uint8_t rif;          /**< rif - Router Interface */
    uint8_t vir_router;   /**< vir_router  - virtual router*/
};


/**
 * sxd_sub_port_type_e enumerated type is used to indicate if local_port represents a profile.
 */
typedef enum sxd_sub_port_type {
    SXD_SUP_PORT_TYPE_PHY_E     = 0,
    SXD_SUP_PORT_TYPE_PROFILE_E = 1
} sxd_sub_port_type_e;

/**
 * ku_pspa_reg structure is used to store the PSPA register parameters
 */
struct ku_pspa_reg {
    uint8_t swid; /**< swid - Switch partition ID */
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t sub_port; /**< sub_port - sub port number */
};

/**
 * ku_pmlp_reg structure is used to store the PMLP register parameters
 */
struct ku_pmlp_reg {
    uint8_t use_different_rx_tx; /** < use_different_rx_tx - use different rx and tx lanes */
    uint8_t autosplit;  /**< autosplit - Auto Split configuration */
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t width;  /**< width - width */
    uint8_t lane[NUMBER_OF_SERDESES]; /**< lane - Lane - up to 8 serdeses in a module can be mapped to a local port */
    uint8_t rx_lane[NUMBER_OF_SERDESES]; /**< lane - Lane - up to 8 serdeses in a module can be mapped to a local port */
    uint8_t module[NUMBER_OF_SERDESES]; /**< module - Module number */
    uint8_t slot[NUMBER_OF_SERDESES]; /**< module - slot number */
};

#define SXD_MGIR_HW_DEV_ID_SX          0xc738
#define SXD_MGIR_HW_DEV_ID_SWITCH_IB   0xcb20
#define SXD_MGIR_HW_DEV_ID_SPECTRUM    0xcb84
#define SXD_MGIR_HW_DEV_ID_SWITCH_IB2  0xcf08
#define SXD_MGIR_HW_DEV_ID_QUANTUM     0xd2f0
#define SXD_MGIR_HW_DEV_ID_QUANTUM2    0xd2f2
#define SXD_MGIR_HW_DEV_ID_QUANTUM3    0xd2f4
#define SXD_MGIR_HW_DEV_ID_SPECTRUM2   0xcf6c
#define SXD_MGIR_HW_DEV_ID_SPECTRUM3   0xcf70
#define SXD_MGIR_HW_DEV_ID_SPECTRUM4   0xcf80
#define SXD_MGIR_HW_REV_ID_A0          0xA0
#define SXD_MGIR_HW_REV_ID_A1          0xA1
#define SXD_MGIR_HW_REV_ID_A2          0xA2
#define SXD_MGIR_HW_REV_ID_SX_A0       SXD_MGIR_HW_REV_ID_A0
#define SXD_MGIR_HW_REV_ID_SX_A1       SXD_MGIR_HW_REV_ID_A1
#define SXD_MGIR_HW_REV_ID_SX_A2       SXD_MGIR_HW_REV_ID_A2
#define SXD_MGIR_HW_REV_ID_SWITCHIB_A0 SXD_MGIR_HW_REV_ID_A0
#define SXD_MGIR_HW_REV_ID_SLAVE_DEV   0xFF

/**
 * ku_plib_reg structure is used to store the PLIB register parameters
 */
struct ku_plib_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t ib_port; /**< ib_port -  IB Port remapping for local_port or Label port remapping for local_port */
    uint8_t split_num; /**< split_num - Label split mapping for local_port */
};

/**
 * ku_pcnr_reg structure is used to store the PCNR register parameters
 */
struct ku_pcnr_reg {
    uint8_t local_port;       /**< local_port - local port number */
    uint8_t lp_msb;           /**< local_port msb */
    uint8_t tuning_override; /**< tuning override - ENA/ DIS - enable PHY Fast boot mode */
};

/**
 * ku_pcmr_reg structure is used to store the PCMR register parameters
 */
struct ku_pcmr_reg {
    uint8_t local_port;        /**< local_port - local port number */
    uint8_t lp_msb;            /**< local_port msb */
    uint8_t rx_ts_over_crc_cap; /**< rx_ts_over_crc_cap - Ingress timestamp over CRC capability */
    uint8_t tx_fcs_recalc_cap; /**< tx_fcs_recalc_cap - Egress prevent CRC overwrite capability */
    uint8_t tx_ts_over_crc_cap; /**< tx_ts_over_crc_cap - Egress timestamp over CRC capability */
    uint8_t rx_fcs_drop_cap;   /**< rx_fcs_drop_cap - Ingress forward on bad CRC capability */
    uint8_t fcs_cap;           /**< fcs_cap - FCS check capability */
    uint8_t rx_ts_over_crc;    /**< rx_ts_over_crc - ENA/ DIS - enable Ingress timestamp over CRC */
    uint8_t tx_fcs_recalc;     /**< tx_fcs_recalc - ENA/ DIS - enable Egress prevent CRC overwrite */
    uint8_t tx_ts_over_crc;    /**< tx_ts_over_crc - ENA/ DIS - enable Egress timestamp over CRC */
    uint8_t rx_fcs_drop;       /**< rx_fcs_drop - ENA/ DIS - enable Ingress forward on bad CRC */
    uint8_t fcs_chk;           /**< FCS check - ENA/ DIS - enable FCS check  */
};

/**
 * ku_ppaos_reg structure is used to store the PPAOS register parameters
 */
struct ku_ppaos_reg {
    uint8_t swid;  /**< swid - Switch Partition ID to associate port with */
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t phy_test_mode_admin; /**< phy_test_mode_admin - Port extended administrative down status */
    uint8_t phy_test_mode_status; /**< phy_test_mode_status - Port extended down status */
};

/**
 * ku_plpc_reg structure is used to store the PLPC register parameters
 */
struct ku_plpc_reg {
    uint16_t profile_id; /**< profile_id - Profile ID (bitmask)  */
    uint8_t  proto_mask; /**< proto_mask - Protocol Mask. Indicates which of the protocol data is valid */
    uint16_t lane_speed; /**< lane_speed - Per lane speed (bitmask) */
    uint8_t  lpbf; /**< lpbf - Link Performance Based FEC */
    uint8_t  fec_mode_policy; /**< fec_mode_policy - FEC decision policy */
    uint8_t  retransmission_capability; /**< retransmission capability (bitmask) */
    uint32_t fec_mode_capability; /**< fec_mode_capability - FEC capability (bitmask) */
    uint8_t  retransmission_support_admin; /**< retransmission_support_admin - Retransmission support admin (bitmask) */
    uint32_t fec_mode_support_admin; /**< fec_mode_support_admin - FEC support admin (bitmask) */
    uint8_t  retransmission_request_admin; /**< retransmission_request_admin - Retransmission request admin (bitmask) */
    uint32_t fec_mode_request_admin; /**< fec_mode_request_admin - FEC request admin (bitmask) */
};

/**
 * ku_pplm_reg structure is used to store the PPLM register parameters
 */
struct ku_pplm_reg {
    uint8_t  local_port; /**< local_port - Local port number */
    uint8_t  lp_msb;     /**< local_port msb */
    uint8_t  port_profile_mode; /**< port_profile_mode - Port profile modes (bitmask) */
    uint8_t  static_port_profile; /**< static_port_profile - Valid when Media based port profile is cleared, used to set the static port's profile index. */
    uint8_t  active_port_profile; /**< active_port_profile - The port's active Profile ID */
    uint8_t  retransmission_active; /**< retransmission_active - Active Retransmission */
    uint32_t fec_mode_active; /**< fec_mode_active - Active FEC (bitmask) */
    uint8_t  rs_fec_correction_bypass_cap; /**< RS-FEC correction bypass override capability */
    uint16_t fec_override_cap_400g_8x;  /**< 400GE Ethernet FEC override capability bitmask */
    uint16_t fec_override_cap_200g_4x;  /**< 200GE Ethernet FEC override capability bitmask */
    uint16_t fec_override_cap_100g_2x;  /**< 100GE Ethernet FEC override capability bitmask */
    uint16_t fec_override_cap_50g_1x;  /**< 50GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_56g; /**< 56GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_100g; /**< 100GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_50g; /**< 50GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_25g; /**< 25GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_10g_40g; /**< 10/40GE Ethernet FEC override capability bitmask */
    uint16_t fec_override_cap_800g_8x;  /**< 800GE Ethernet FEC override capability bitmask */
    uint16_t fec_override_cap_400g_4x;  /**< 400GE Ethernet FEC override capability bitmask */
    uint16_t fec_override_cap_200g_2x;  /**< 200GE Ethernet FEC override capability bitmask */
    uint16_t fec_override_cap_100g_1x;  /**< 100GE Ethernet FEC override capability bitmask */
    uint8_t  rs_fec_correction_bypass_admin; /**< RS-FEC correction bypass override admin */
    uint16_t fec_override_admin_400g_8x;  /**< 400GE Ethernet FEC override admin */
    uint16_t fec_override_admin_200g_4x;  /**< 200GE Ethernet FEC override admin */
    uint16_t fec_override_admin_100g_2x;  /**< 100GE Ethernet FEC override admin */
    uint16_t fec_override_admin_50g_1x;  /**< 50GE Ethernet FEC override admin */
    uint8_t  fec_override_admin_56g; /**< 56GE Ethernet FEC override admin */
    uint8_t  fec_override_admin_100g; /**< 100GE Ethernet FEC override admin */
    uint8_t  fec_override_admin_50g; /**< 50GE Ethernet FEC override admin */
    uint8_t  fec_override_admin_25g; /**< 25GE Ethernet FEC override capability admin */
    uint8_t  fec_override_admin_10g_40g; /**< 10/40GE Ethernet FEC override capability admin */
    uint16_t fec_override_admin_800g_8x;  /**< 800GE Ethernet FEC override admin */
    uint16_t fec_override_admin_400g_4x;  /**< 400GE Ethernet FEC override admin */
    uint16_t fec_override_admin_200g_2x;  /**< 200GE Ethernet FEC override admin */
    uint16_t fec_override_admin_100g_1x;  /**< 100GE Ethernet FEC override admin */
    uint16_t ib_fec_override_admin_edr;  /**< EDR Infiniband FEC override admin */
    uint16_t ib_fec_override_admin_fdr;  /**< FDR Infiniband FEC override admin */
    uint16_t ib_fec_override_admin_hdr;  /**< HDR Infiniband FEC override admin */
    uint16_t ib_fec_override_admin_ndr;  /**< NDR Infiniband FEC override admin */
    uint16_t ib_fec_override_admin_xdr;  /**< XDR Infiniband FEC override admin */
};

/**
 * jtag_transaction_set structure is used to store the JTAG
 * Transaction Set Byte Layout
 */
struct jtag_transaction_set {
    uint8_t tms;
    uint8_t tdi;
    uint8_t tdo;
};

/**
 * ku_mjtag_reg structure is used to store the MJTAG register
 * parameters
 */
struct ku_mjtag_reg {
    uint8_t                     cmd; /**< Command  */
    uint8_t                     seq_num; /** < Command sequence Number */
    uint8_t                     size; /**< Size of operation */
    struct jtag_transaction_set jtag_transaction_sets[MAX_TRANSACTIONS_NUM];
};

/**
 * ku_pmpr_reg structure is used to store the PMPR register parameters
 */
struct ku_pmpr_reg {
    uint8_t module; /**< module number */
    uint8_t attenuation5g; /**< Attenuation5G */
    uint8_t attenuation7g; /**< Attenuation7G */
    uint8_t attenuation12g; /**< Attenuation12G */
};

/**
 * ku_pfsc_reg structure is used to store the PFSC register parameters
 */
struct ku_pfsc_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t fwd_admin; /**< fwd_admin - Administratively configured of Forward switching for Egress */
    uint8_t fwd_oper; /**< fwd_oper - Operational Egress Forward switching */
};

/**
 * ku_sbcm_reg structure is used to store the SBCM register parameters
 */
struct ku_sbcm_reg {
    uint8_t  desc; /**< desc - Descriptor buffer */
    uint8_t  snap; /**< snap - Read the snapshot */
    uint8_t  local_port; /**< local_port - Local port number */
    uint8_t  lp_msb;     /**< local_port msb */
    uint8_t  pg_buff; /**< pg_buff - Port PG */
    uint8_t  dir; /**< dir - Direction */
    uint8_t  infinite_size; /**< infinite_size - pool with infinite size. When set size is reserved */
    uint8_t  exc; /** Exclude - no accounting in the pool */
    uint32_t buff_occupancy; /**< buff_occupancy - Current buffer occupancy */
    uint32_t max_buff_occupancy; /**< max_buff_occupancy - Maximum value of buffer occupancy monitored */
    uint32_t clr; /**< clr - Clear max buffer occupancy - when set the max value is cleared */
    uint32_t min_buff; /**< min_buff - Minimum buffer size for the limiter */
    uint8_t  infi_max; /** Max buffer is infinite */
    uint32_t max_buff; /**< max_buff - Maximum buffer size for the limiter in cells or "alpha" */
    uint8_t  pool; /**< pool - Association of the port-priority to a pool*/
};

/**
 * ku_sbpm_reg structure is used to store the SBPM register parameters
 */
struct ku_sbpm_reg {
    uint8_t  desc; /**< desc - Descriptor buffer */
    uint8_t  local_port; /**< local_port - Local port number */
    uint8_t  lp_msb;     /**< local_port msb */
    uint8_t  pool; /**< pool - Association of the port-priority to a pool*/
    uint8_t  dir; /**< dir - Direction */
    uint8_t  infinite_size; /**< infinite_size - buff with infinite size. When set size is reserved */
    uint32_t buff_occupancy; /**< buff_occupancy - Current buffer occupancy */
    uint32_t max_buff_occupancy; /**< max_buff_occupancy - Maximum value of buffer occupancy monitored */
    uint32_t clr; /**< clr - Clear max buffer occupancy - when set the max value is cleared */
    uint32_t min_buff; /**< min_buff - Minimum buffer size for the limiter */
    uint32_t max_buff; /**< max_buff - Maximum buffer size for the limiter in cells or "alpha" */
};

/**
 * ku_sbmm_reg structure is used to store the SBMM register parameters
 */
struct ku_sbmm_reg {
    uint8_t  prio; /**< prio - Switch Priority*/
    uint8_t  infinite_size; /**< infinite_size - buff with infinite size. When set size is reserved */
    uint32_t buff_occupancy; /**< buff_occupancy - Current buffer occupancy */
    uint32_t max_buff_occupancy; /**< max_buff_occupancy - Maximum value of buffer occupancy monitored */
    uint32_t clr; /**< clr - Clear max buffer occupancy - when set the max value is cleared */
    uint32_t min_buff; /**< min_buff - Minimum buffer size for the limiter */
    uint32_t max_buff; /**< max_buff - Maximum buffer size for the limiter in cells or "alpha" */
    uint8_t  pool; /**< pool - Association of the switch priority to a pool*/
};

/**
 * ku_mfcr_reg structure is used to store the MFCR register parameters
 */
struct ku_mfcr_reg {
    uint8_t  pwm_frequency; /**< pwm_frequency - Controls the frequency of the PWM signal */
    uint8_t  pwm_active; /**< pwm_active - Indicates which of the PWM control is active (bit per PWM) */
    uint16_t tacho_active; /**< tacho_active - Indicates which of the tachometer is active (bit per tachometer)*/
};

/**
 * ku_mfsc_reg structure is used to store the MFSC register parameters
 */
struct ku_mfsc_reg {
    uint8_t pwm; /**< pwm - Pwm to control / monitor */
    uint8_t pwm_duty_cycle; /**< pwm_duty_cycle - Controls the duty cycle of the PWM */
};

/**
 * ku_mfsm_reg structure is used to store the MFSM register parameters
 */
struct ku_mfsm_reg {
    uint8_t  tacho; /**< tacho - Fan tachometer index */
    uint8_t  n; /**< n - Defines the number of tacho pulses duration in which the SwitchX counts TBD mSec periods */
    uint16_t rpm; /**< rpm - Fan speed */
};

/**
 * ku_mfsl_reg structure is used to store the MFSL register parameters
 */
struct ku_mfsl_reg {
    uint8_t  fan; /**< fan - Fan tachometer index */
    uint8_t  ee; /**< ee - Event Enable */
    uint8_t  ie; /**< ie - Interrupt Enable */
    uint16_t tach_min; /**< tach_min - Tachometer minimum value */
    uint16_t tach_max; /**< tach_max - Tachometer maximum value*/
};

/**
 * ku_fore_reg structure is used to store the FORE register parameters
 */
struct ku_fore_reg {
    uint16_t fan_under_limit; /**< fan_under_limit - Fan speed is below the low limit defined in MFSL register */
    uint16_t fan_over_limit; /**< fan_over_limit - Fan speed is above the high limit defined in MFSL register */
};


/**
 * mtbr_record_temperature structure is used to store one MTBR temperature record.
 */
struct mtbr_record_temperature {
    uint16_t max_temperature; /**< max_temperature - The highest measured temperature from the sensor */
    uint16_t temperature; /**< temperature - Temperature reading from the sensor */
};

/**
 * ku_mtbr_reg structure is used to store the MTBR register parameters
 */
struct ku_mtbr_reg {
    uint8_t                          slot_index; /**< slot_index - Slot index */
    uint16_t                         base_sensor_index; /**< base_sensor_index - Base sensors index to access */
    uint8_t                          num_rec; /**< num_rec - Number of records to read */
    struct   mtbr_record_temperature temperature_record[MTBR_MAX_TEMPERATURE_RECORDS]; /**< temperature_record - Temperature records */
};

#define SXD_MTBR_TEMPERATURE_MULT 1000 /* Multiplier for getting temperature fractional part (3 decimal places) */
#define SXD_MTBR_TEMPERATURE_UNIT 0.125
#define SXD_MTBR_NO_CABLE         0x8000
#define SXD_MTBR_NO_READ          0x8001
#define SXD_MTBR_INVALID_INDEX    0x8002
#define SXD_MTBR_READ_FAILED      0x8003
#define SXD_MTBR_NO_SENSOR        0x8004

/**
 * temperature_double structure is used to present the MTBR
 * register temperature record
 */
struct temperature_double {
    int16_t  integer_part;
    uint16_t fractional_part; /* 3 sign after the . */
};

/**
 * mtbr_record_temperature structure is used to store one MTBR temperature record.
 */
struct mtbr_record_temperature_ext {
    struct temperature_double max_temperature; /**< max_temperature - The highest measured temperature from the sensor */
    struct temperature_double temperature; /**< temperature - Temperature reading from the sensor */
};

/**
 * ku_mtbr_reg_ext structure is used to store the MTBR register
 * parameters with temperature in Celsius
 */
struct ku_mtbr_reg_ext {
    uint16_t                             base_sensor_index; /**< base_sensor_index - Base sensors index to access */
    uint8_t                              num_rec; /**< num_rec - Number of records to read */
    struct   mtbr_record_temperature_ext temperature_record[MTBR_MAX_TEMPERATURE_RECORDS]; /**< temperature_record - Temperature records */
};

/**
 * ku_mmdio_reg structure is used to store the MMDIO register parameters
 */
struct ku_mmdio_reg {
    uint8_t  mdio_index; /**< mdio_index - MDIO index */
    uint8_t  operation; /**< operation - operation */
    uint32_t address; /**< address - Address. If clause XX is used, only the lower 16 bits are valid */
    uint32_t data; /**< data - Data. If clause XX is used, only the lower 16 bits are valid */
};

/**
 * ku_mmia_reg structure is used to store the MMIA register parameters
 */
struct ku_mmia_reg {
    uint8_t  operation; /**< operation - operation */
    uint32_t data; /**< data - data */
};

/**
 * ku_mfpa_reg structure is used to store the MFPA register parameters
 */
struct ku_mfpa_reg {
    uint8_t  p; /**< p - Parallel */
    uint8_t  fs; /**< fs - Flash Select */
    uint32_t boot_address; /**< boot_address - Boot address points to the FW image in the flash */
    uint8_t  flash_num; /**< flash_num - Number of Flash Devices connected */
    uint32_t jedec_id; /**< jedec_id - Flash JEDEC ID */
    uint16_t block_allignment; /**< block_allignment - Required alignment for block access */
    uint16_t sector_size; /**< sector_size - Flash Sector Size */
    uint8_t  capability_mask; /**< capability_mask - Capability Mask
                               *  Bit 0: Parallel Flash Support
                               *  Else: Reserved */
};

/**
 * ku_mfbe_reg structure is used to store the MFBE register parameters
 */
struct ku_mfbe_reg {
    uint8_t  p; /**< p - Parallel */
    uint8_t  fs; /**< fs - Flash Select */
    uint32_t address; /**< address - address in bytes */
};

/**
 * ku_mfba_reg structure is used to store the MFBA register parameters
 */
struct ku_mfba_reg {
    uint8_t  p; /**< p - Parallel */
    uint8_t  fs; /**< fs - Flash Select */
    uint16_t size; /**< size - Transaction size */
    uint32_t address; /**< address - address in bytes */
    uint8_t  data[192]; /**< data - Data */
};

/**
 * ku_raw_reg structure is used to store the RAW register parameters
 */
struct ku_raw_reg {
    uint8_t *buff;     /**< buff - the register buffer */
    uint16_t size;    /**< size - the buffer size */
};

struct ku_raw_reg_ext {
    struct ku_raw_reg raw_reg;
    uint32_t          fw_emad_latency;
    uint32_t          fw_cache_read_time;
};

/**
 * ku_pelc_reg structure is used to store the PELC register parameters
 */
struct ku_pelc_reg {
    uint8_t                              op; /**< Operation - 0 - FEC control 1 - LLR control*/
    uint8_t                              local_port; /**< local_port - Local port number */
    uint8_t                              lp_msb;     /**< local_port msb */
    uint8_t                              op_admin; /**< op_admin - Operation specific administratively enabled properties */
    uint8_t                              op_capability; /**< op_capability - Operation specific properties capabilities */
    uint8_t                              op_request; /**< op_request - Operation specific properties request */
    uint8_t                              op_active; /**< op_active - Operation specific properties active */
    uint64_t __attribute__((aligned(8))) admin; /**< admin - Link administratively enabled */
    uint64_t __attribute__((aligned(8))) capability; /**< capability - Port Extended Property supported */
    uint64_t __attribute__((aligned(8))) request;
    uint64_t __attribute__((aligned(8))) active; /**< active - Link operational mode */
};

/**
 * ku_pvlc_reg structure is used to store the PVLC register parameters
 */
struct ku_pvlc_reg {
    uint8_t local_port; /**< local_port - Local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t vl_cap; /**< vl_cap - Virtual Lanes supported on this port */
    uint8_t vl_admin; /**< vl_admin - Virtual Lanes enabled by the local admin on this port */
    uint8_t vl_operational; /**< vl_operational - Virtual Lanes Operational as configured by the Subnet Manager on this port */
};

/**
 * ku_mcia_reg structure is used to store the MCIA register parameters
 */
struct ku_mcia_reg {
    uint8_t  l; /**< l - Lock bit. Setting this bit will lock the access to the specific cable */
    uint8_t  module; /**< module - module number */
    uint8_t  slot_index; /**< slot index - slot number */
    uint8_t  status; /**< status - module status */
    uint8_t  i2c_device_address; /**< i2c_device_address - I2C device address */
    uint8_t  page_number; /**< page_number - Page number */
    uint16_t device_address; /**< device_address - Device address */
    uint16_t size; /**< size - Number of bytes to read/write (up to 48 bytes) */
    uint32_t dword_0; /**< dword_0 - Bytes to read/write */
    uint32_t dword_1; /**< dword_1 - Bytes to read/write */
    uint32_t dword_2; /**< dword_2 - Bytes to read/write */
    uint32_t dword_3; /**< dword_3 - Bytes to read/write */
    uint32_t dword_4; /**< dword_4 - Bytes to read/write */
    uint32_t dword_5; /**< dword_5 - Bytes to read/write */
    uint32_t dword_6; /**< dword_6 - Bytes to read/write */
    uint32_t dword_7; /**< dword_7 - Bytes to read/write */
    uint32_t dword_8; /**< dword_8 - Bytes to read/write */
    uint32_t dword_9; /**< dword_9 - Bytes to read/write */
    uint32_t dword_10; /**< dword_10 - Bytes to read/write */
    uint32_t dword_11; /**< dword_11 - Bytes to read/write */
};

/**
 * ku_pptb_reg structure is used to store the PPTB register parameters
 */
struct ku_pptb_reg {
    uint8_t local_port; /**< local_port - Local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t cm; /**< cm - ctrl_buff mask, enables update the ctrl_buff field */
    uint8_t um; /**< um - untagged_buff mask, enables update the untagged_buff field */
    uint8_t pm; /**< pm - pioX_buff mask, enables update the pioX_buff field */
    uint8_t prio_0_buff; /**< prio_0_buff - Mapping of Prio 0 to one of the allocated receive port buffers. */
    uint8_t prio_1_buff; /**< prio_1_buff - Mapping of Prio 1 to one of the allocated receive port buffers. */
    uint8_t prio_2_buff; /**< prio_2_buff - Mapping of Prio 2 to one of the allocated receive port buffers. */
    uint8_t prio_3_buff; /**< prio_3_buff - Mapping of Prio 3 to one of the allocated receive port buffers. */
    uint8_t prio_4_buff; /**< prio_4_buff - Mapping of Prio 4 to one of the allocated receive port buffers. */
    uint8_t prio_5_buff; /**< prio_5_buff - Mapping of Prio 5 to one of the allocated receive port buffers. */
    uint8_t prio_6_buff; /**< prio_6_buff - Mapping of Prio 6 to one of the allocated receive port buffers. */
    uint8_t prio_7_buff; /**< prio_7_buff - Mapping of Prio 7 to one of the allocated receive port buffers. */
    uint8_t prio_8_buff; /**< prio_0_buff - Mapping of Prio 8 to one of the allocated receive port buffers. */
    uint8_t prio_9_buff; /**< prio_1_buff - Mapping of Prio 9 to one of the allocated receive port buffers. */
    uint8_t prio_10_buff; /**< prio_2_buff - Mapping of Prio 10 to one of the allocated receive port buffers. */
    uint8_t prio_11_buff; /**< prio_3_buff - Mapping of Prio 11 to one of the allocated receive port buffers. */
    uint8_t prio_12_buff; /**< prio_4_buff - Mapping of Prio 12 to one of the allocated receive port buffers. */
    uint8_t prio_13_buff; /**< prio_5_buff - Mapping of Prio 13 to one of the allocated receive port buffers. */
    uint8_t prio_14_buff; /**< prio_6_buff - Mapping of Prio 14 to one of the allocated receive port buffers. */
    uint8_t prio_15_buff; /**< prio_7_buff - Mapping of Prio 15 to one of the allocated receive port buffers. */
    uint8_t untagged_buff; /**< untagged_buff - Mapping of untagged frames to one of the allocated receive port buffers. */
    uint8_t ctrl_buff; /**< ctrl_buff - Mapping of control frames to one of the allocated receive port buffers. */
    uint8_t prio_buff_msb; /**< prio_buff_msb - Prio to buff mask. */
    uint8_t mapping_mode; /**< mm - mapping mode */
};

/**
 * ku_pfcc_reg structure is used to store the PFCC register parameters
 */
struct ku_pfcc_reg {
    uint8_t local_port; /**< local_port - Local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t prio_mask_tx; /**< prio_mask_tx - Bit per prio indicating if TX flow control policy should be updated based on the below */
    uint8_t prio_mask_rx; /**< prio_mask_rx - Bit per prio indicating if RX flow control policy should be updated based on the below */
    uint8_t pause_policy_tx; /**< pause_policy_tx - Pause policy on TX */
    uint8_t prio_policy_tx; /**< prio_policy_tx - Priority based Flow Control policy on TX */
    uint8_t cb_policy_tx; /**< cb_policy_tx - Credit Based Flow control policy in TX */
    uint8_t pause_policy_rx; /**< pause_policy_rx - Pause policy on RX */
    uint8_t prio_policy_rx; /**< prio_policy_rx - Priority based Flow Control policy on RX */
    uint8_t cb_policy_rx; /**< cb_policy_rx - Credit Based Flow control policy in RX */
    uint8_t patx; /**< patx - Peer advertisement pause policy on Tx */
    uint8_t parx; /**< parx - Peer advertisement pause policy on Rx */
};

/**
 * ku_pcap_reg structure is used to store the PCAP register parameters
 */
struct ku_pcap_reg {
    uint8_t  local_port; /**< local_port - Local port number */
    uint8_t  lp_msb;     /**< local_port msb */
    uint32_t port_capability_mask[4]; /**< port_capability_mask - Sets the PortInfoCapabilityMask */
};

/**
 * ku_pude_reg structure is used to store the PUDE register parameters
 */
struct ku_pude_reg {
    uint8_t swid; /**< swid - Switch ID */
    uint8_t local_port; /**< local_port - Local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t oper_status; /**< oper_status - Port operational state */
    uint8_t logical_state_status; /**< logical_state_status - Port logical link state */
};

/**
 * MFDE enum for command type
 */
#define SXD_FOREACH_OBJECT_COMMAND_TYPE(COMMAND_TYPE)      \
    COMMAND_TYPE(SXD_COMMAND_TYPE_MAD, = 0, "MAD")         \
    COMMAND_TYPE(SXD_COMMAND_TYPE_EMAD, = 1, "EMAD")       \
    COMMAND_TYPE(SXD_COMMAND_TYPE_CMD_IFC, = 2, "CMD-IFC") \
    COMMAND_TYPE(SXD_COMMAND_TYPE_CR_ACCESS, = 3, "CR")    \

typedef enum sxd_mfde_command_type {
    SXD_FOREACH_OBJECT_COMMAND_TYPE(SXD_GENERATE_ENUM)
} sxd_command_type_t;

/**
 * MFDE FW fatal cause ID
 */
#define SXD_FOREACH_MFDE_FW_FATAL_CAUSE_ID(CAUSE_ID)                                                     \
    CAUSE_ID(SXD_MFDE_FW_FATAL_CASUE_ID_CORE_PLL_LOCK_FAILURE_E, = 1, "Core PLL lock failure")           \
    CAUSE_ID(SXD_MFDE_FW_FATAL_CASUE_ID_MIN_E, = SXD_MFDE_FW_FATAL_CASUE_ID_CORE_PLL_LOCK_FAILURE_E, "") \
    CAUSE_ID(SXD_MFDE_FW_FATAL_CASUE_ID_MAX_E, = SXD_MFDE_FW_FATAL_CASUE_ID_CORE_PLL_LOCK_FAILURE_E, "")

typedef enum sxd_mfde_fw_fatal_cause_id {
    SXD_FOREACH_MFDE_FW_FATAL_CAUSE_ID(SXD_GENERATE_ENUM)
} sxd_mfde_fw_fatal_cause_id_e;

/**
 * ku_pmpc_reg structure is used to store the PMPC register parameters
 */
struct ku_pmpc_reg {
    uint32_t module_state_updated_bitmap[8]; /**< module_state_updated - A bit vector. each bit represent a module plugged/unplugged*/
};


/**
 * ku_mpsc_reg structure is used to store the MPSC register parameters
 */
struct ku_mpsc_reg {
    uint8_t                              local_port; /**< local_port - local port number */
    uint8_t                              lp_msb;     /**< local_port msb */
    uint8_t                              clear_count; /**< clear_count - clear counter */
    uint8_t                              enable; /**< enable - enable sampling on local_port */
    uint8_t                              cong; /**< cong - Congestion */
    uint32_t                             rate; /**< rate - sampling rate (total pkt/sampled pkt) */
    uint64_t __attribute__((aligned(8))) count_drops; /**< count_drops - count of frames after sampling */
};

/**
 * ku_mlcr_reg structure is used to store the MLCR register parameters
 */
struct ku_mlcr_reg {
    uint8_t  local_port;      /**< local_port - local port number */
    uint8_t  lp_msb;          /**< local_port msb */
    uint8_t  led_type;        /**< led_type - led type */
    uint8_t  cap_local_or_uid_only;        /**< cap_local_or_uid_only - cap local or uid only */
    uint16_t beacon_duration; /**< beacon_duration - duration of the beacon to be active */
    uint16_t beacon_remain;   /**< beacon_remain - remaining duration of the beacon */
};

/**
 * mpgcr_mpls_et
 */
typedef enum mpgcr_mpls_et {
    MPGCR_ET8847        = 1,
    MPGCR_ET8848        = 2,
    MPGCR_ET8847_ET8848 = 3,
} mpgcr_mpls_et_t;

/**
 * mpgcr_pcp_rw
 */
typedef enum mpgcr_pcp_rw {
    MPGCR_PCPRW_PRESERVE = 0,
    MPGCR_PCPRW_DISABLE  = 2,
    MPGCR_PCPRW_ENABLE   = 3
} mpgcr_pcp_rw_t;

/**
 * mpgcr_ler_exp_rw
 */
typedef enum mpgcr_ler_exp_rw {
    MPGCR_LER_EXP_DISABLE = 2,
    MPGCR_LER_EXP_ENABLE  = 3
} mpgcr_ler_exp_rw_t;

/**
 * mpgcr_lsr_egress_ttl
 */
typedef enum mpgcr_lsr_egress_ttl {
    MPGCR_LSR_EGRESS_TTL_POPPED = 1,
    MPGCR_LSR_EGRESS_TTL_MIN    = 2,
} mpgcr_lsr_egress_ttl_t;

/**
 * mpgcr_egress_ler_ttl
 */
typedef enum mpgcr_egress_ler_ttl {
    MPGCR_EGRESS_LER_TTL_PRESERVE = 0,
    MPGCR_EGRESS_LER_TTL_POPPED   = 1,
    MPGCR_EGRESS_LER_TTL_MIN      = 2,
} mpgcr_egress_ler_ttl_t;

/**
 * mpgcr_ingress_ler_ttl
 */
typedef enum mpgcr_ingress_ler_ttl {
    MPGCR_INGRESS_LER_TTL_IP     = 0,
    MPGCR_INGRESS_LER_TTL_CONFIG = 1,
} mpgcr_ingress_ler_ttl_t;

/**
 * mpgcr_activity_dis_mpnhlfe
 */
typedef enum mpgcr_activity_dis_mpnhlfe {
    MPGCR_ACTIVITY_MPNHLFE_ENABLE  = 0,
    MPGCR_ACTIVITY_MPNHLFE_DISABLE = 1,
} mpgcr_activity_dis_mpnhlfe_t;

/**
 * mpgcr_irif_vn_en
 */
typedef enum mpgcr_irif_vr_en {
    MPGCR_IRIF_VR_EN_DISABLE = 0,
    MPGCR_IRIF_VR_EN_ENABLE  = 1,
} mpgcr_irif_vr_en_t;

/**
 * ku_mpgcr_reg structure is used to store the MPGCR register parameters
 */
struct ku_mpgcr_reg {
    mpgcr_mpls_et_t              mpls_et; /**< mpls_et - enable MPLS Ethertypes */
    mpgcr_pcp_rw_t               mpls_pcp_rw; /**< mpls_pcp_rw - LSR and LER PCP Re-write enable */
    mpgcr_ler_exp_rw_t           ler_exp_rw; /**< ler_exp_rw - Ingress LER EXP Re-write Enable */
    mpgcr_ingress_ler_ttl_t      ingress_ler_ttl; /**< ingress_ler_ttl - Ingress LER TTL */
    mpgcr_egress_ler_ttl_t       egress_ler_ttl; /**< egress_ler_ttl - Egress LER TTL */
    mpgcr_lsr_egress_ttl_t       lsr_egress_ttl; /**< lsr_egress_ttl - LSR egress TTL */
    mpgcr_ingress_ler_ttl_t      ingress_ler_ttl_value; /**< ingress_ler_ttl_value - Ingress LER TTL value */
    uint8_t                      hrlsn; /**<hrlsn - High Reserved Label ID Space Number*/
    uint32_t                     label_id_min; /**< label_id_min - Label IDs from label_id_min*/
    uint32_t                     label_id_max; /**< label_id_max - Label IDs to label_id_max*/
    uint8_t                      entropy_msb; /**< entropy_msb - Entropy 8 msb*/
    mpgcr_irif_vr_en_t           irif_vr_en; /** irif virtual router enabled */
    mpgcr_activity_dis_mpnhlfe_t activity_dis_mpnhlfe; /**< activity_dis_mpnhlfe - Disable activity bit in MPNHLFE */
};

/**
 * ku_mpilm_reg structure is used to store the MPILM register parameters
 */
struct ku_mpilm_reg {
    uint8_t           op; /**< op - operation */
    uint8_t           label_space; /**< label_space - label space */
    uint32_t          label_id; /**< label_id - label ID */
    uint32_t          nhlfe_ptr; /**<nhlfe_ptr - NHLFE entry pointer */
    uint8_t           npop; /**< npop - number of labels to pop from the label stack */
    uint16_t          ecmp_size; /**< ecmp_size - the amount of sequential entries starting from the nhlfe_ptr */
    uint8_t           trap_action; /**< trap_action -trap action*/
    uint16_t          trap_id; /**< trap_id -trap id to be reported to CPU */
    sxd_counter_set_t counter_set; /**<counter_set - counter set */
};

/**
 * ku_mpibe_reg structure is used to store the MPIBE register parameters
 */
struct ku_mpibe_reg {
    uint8_t  label_space; /**< label_space - label space */
    uint32_t nhlfe_ptr; /**<nhlfe_ptr - NHLFE entry pointer */
    uint16_t ecmp_size; /**< ecmp_size - the amount of sequential entries starting from the nhlfe_ptr */
    uint32_t new_nhlfe_ptr; /**<nhlfe_ptr - new NHLFE entry pointer */
    uint16_t new_ecmp_size; /**< ecmp_size - new amount of sequential entries starting from the nhlfe_ptr */
};

/**
 * nhlfe_dscp_or_exp_rw_t structure enumerates types how to handle dscp or exp rewrite
 */
typedef enum    nhlfe_dscp_or_exp_rw {
    NHLFE_DSCP_RE_PRESERVE = 0,
    NHLFE_DSCP_RE_SET      = 1,
    NHLFE_DSCP_RE_CLEAR    = 2
} nhlfe_dscp_or_exp_rw_t;

/**
 * nhlfe_label_action_t structure enumerates types how to handle push action
 */
typedef enum nhlfe_label_action {
    NHLFE_LABEL_ACTION_NO_PHP                       = 0,
    NHLFE_LABEL_ACTION_PHP                          = 1,
    NHLFE_LABEL_ACTION_PUSH_LABEL                   = 2,
    NHLFE_LABEL_ACTION_PUSH_ENTROPY_LABEL           = 3,
    NHLFE_LABEL_ACTION_PUSH_ENTROPY_LABEL_AND_LABEL = 4
} nhlfe_label_action_t;

/**
 * ku_mdri_reg structure is used to store the MDRI register parameters
 */
struct ku_mdri_reg {
    uint8_t  clear;     /**< clear - clear per bit */
    uint8_t  read;     /**< read - read per bit */
    uint32_t global_reasons[8];     /**< global_reasons - global reasons */
    uint32_t port_reasons[8];     /**< port_reasons - port reasons */
    uint32_t buffer_reasons[8];     /**< buffer_reasons - buffer reasons */
    uint32_t ethernet_reasons[8];     /**< ethernet_reasons - ethernet reasons */
    uint32_t ip_reasons[8];     /**< ip_reasons - ip reasons */
    uint32_t mpls_reasons[8];     /**< mpls_reasons - mpls reasons */
    uint32_t tunnel_reasons[8];     /**< tunnel_reasons - tunnel reasons */
    uint32_t host_reasons[8];     /**< host_reasons - host reasons */
};

/**
 * ku_pfca_reg structure is used to store the PFCA register parameters
 */
struct ku_pfca_reg {
    uint8_t  op; /**< op - Operation */
    uint8_t  type; /**< type - Counter type */
    uint8_t  index; /**< index - Counter set index */
    uint32_t flow_counter_handle; /**< flow_counter_handle - Opaque object that represents the flow counter */
};

/**
 * ku_pfcnt_reg structure is used to store the PFCNT register parameters
 */
struct ku_pfcnt_reg {
    uint32_t                             flow_counter_handle; /**< flow_counter_handle - Handle to the flow counter to read */
    uint8_t                              clr; /**< clr - Counter - Setting the clr bit will reset the counter value for relevant flow counter. */
    uint64_t __attribute__((aligned(8))) flow_counter;  /**< flow_counter - flow counter value */
};


/**
 * ku_pbrl_reg structure is used to store the PBRL register parameters
 */
struct ku_pbrl_reg {
    uint8_t  lossy; /**< lossy - The field indicates if the buffer is lossy. 0 - Lossless 1 - Lossy */
    uint8_t  epsb; /**<  epsb - Eligible for Port Shared buffer */
    uint16_t size; /**< size - The part of the packet buffer array is allocated for the specific buffer */
    uint16_t xof_threshold; /**< xof_threshold - Once the amount of data in the buffer goes above this value, SwitchX
                             *  starts sending Pause frames for all Prios associated with the buffer.
                             *  Units represent 64 bytes chunks. */
    uint16_t xon_threshold; /**< xon_threshold - When the amount of data in the buffer goes below this value,
                             *  SwitchX stops sending Pause frames for the Prios associated with the
                             *  buffer. Units represent 64 bytes chunks. */
};

/**
 * ku_pbmc_reg structure is used to store the PBMC register parameters
 */
struct ku_pbmc_reg {
    uint8_t            local_port; /**< local_port - Local port number */
    uint8_t            lp_msb;     /**< local_port msb */
    uint16_t           xof_timer_value; /**< xof_timer_value - When SwitchX generates a Pause frame, it uses this value as the Pause timer. */
    uint16_t           xof_refresh; /**< xof_refresh - The time before a new Pause frame should be sent to refresh the Pause state. Using the same units as xof_timer_value above. */
    uint16_t           port_buffer_size; /**< port_buffer_size - Total packet buffer array available for the port. The sum of buffer array allocated to bufferX must not exceed port_buffer_size. */
    struct ku_pbrl_reg buffer[10]; /**< buffer - Configuring per-buffer parameters */
    struct ku_pbrl_reg shared_headroom_pool; /**< shared_headroom_pool - Port's shared headroom pool usage */
    struct ku_pbrl_reg port_shared_buffer; /**< port_shared_buffer - Configuring port shared buffer parameters. Using the same layout as in BufferX */
};

/**
 * sxd_sbpr_mode_e enumerated mode used in SBPR register event field
 */
typedef enum sxd_sbpr_mode {
    SXD_SBPR_MODE_STATIC_E  = 0,
    SXD_SBPR_MODE_DYNAMIC_E = 1,
} sxd_sbpr_mode_e;


/**
 * ku_sbpr_reg structure is used to store the SBPR register parameters
 */
struct ku_sbpr_reg {
    uint8_t  desc; /**< desc - Descriptor buffer */
    uint8_t  direction; /**< Direction - Ingress/ Egress */
    uint8_t  pool_id; /**< pool_id - pool number 1-16 */
    uint8_t  infinite_size; /**< infinite_size - pool with infinite size. When set size is reserved */
    uint32_t size; /**< size - pool size in buffers cells*/
    uint8_t  mode; /**< mode - Absolute/ Relative*/
    uint32_t current_occupancy; /**< current buff_occupancy*/
    uint32_t current_ext_occupancy; /**< current ext_buff_occupancy*/
    uint32_t clear; /**< clear - Clear on Read MAX buff occupancy*/
    uint32_t max_occupancy; /**< Max buff occupancy*/
};

/**
 * sxd_emad_shared_buffer_status structure is used to store shared buffer status for SBSR register
 */
struct shared_buffer_status {
    uint32_t buff_occupancy; /**< buff_occupancy - Current buffer occupancy */
    uint32_t max_buff_occupancy; /**< max_buff_occupancy - Maximum value of buffer occupancy monitored */
};

/**
 * ku_sbsr_reg structure is used to store the SBSR register parameters
 */
struct ku_sbsr_reg {
    uint8_t                     clr; /**< Direction - Ingress/ Egress */
    uint8_t                     desc;
    uint8_t                     port_page;
    uint32_t                    ingress_port_mask[SXD_EMAD_SBSR_PORT_MASK_SIZE]; /*< ingress port mask - 256 bits */
    uint32_t                    pg_buff_mask;
    uint32_t                    egress_port_mask[SXD_EMAD_SBSR_PORT_MASK_SIZE];
    uint32_t                    tclass_mask[SXD_EMAD_SBSR_TC_MASK_SIZE];
    struct shared_buffer_status sbstatus[SXD_EMAD_SBSR_MAX_RET_SIZE];
};

/**
 * ku_ppsc_reg structure is used to store the PPSC register
 * parameters
 */
struct ku_ppsc_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t lp_msb;     /**< local_port msb */
    uint8_t wrps_admin; /**< wrps_admin - Width Reduction Power Save Admin state */
    uint8_t wrps_status; /**< wrps_status - link actual width */
    uint8_t up_threshold; /**< up_threshold - Link Width Up Threshold - the amount of data queued on the link before the link goes back to full width */
    uint8_t down_threshold; /**< down_threshold - Link Width Down Threshold - the amount of quiet time on the link before the link width is moved to single lane */
    uint8_t srps_admin; /**< srps_admin - Speed Reduction Power Save Admin state */
    uint8_t srps_status; /**< srps_status - link actual speed */
};

/**
 * ku_spmcr_reg structure is used to store the SPMCR register parameters
 */
struct ku_spmcr_reg {
    uint8_t  swid; /**< swid - Switch partition ID */
    uint8_t  local_port; /**< local_port - Local port number */
    uint8_t  max_sub_port; /**< max_sub_port - Maximum number of VEPA channels for the port */
    uint16_t base_stag_vid; /**< base_stag_vid - Base S-Tag to be used on the S Component to represent the first VEPA channel
                             *  (subport). A subport is represented by S-Tag.VID = base_stag_vid+sub_port. */
};

/**
 * ku_hpkt_reg structure is used to store the HPKT register parameters
 */
struct ku_hpkt_reg {
    uint8_t  ack; /**< ack - Acknowledgment required. Only relevant for EVENT trap_id */
    uint8_t  action; /**< action - Action to perform on trap_id */
    uint8_t  trap_group; /**< trap_group - Trap Group configured for trap_id */
    uint16_t trap_id; /**< trap_id - Trap ID to configure */
    uint8_t  control; /**< control - control type of trap ID */
};

/**
 * ku_hcap_reg structure is used to store the HCAP register parameters
 */
struct ku_hcap_reg {
    uint8_t max_cpu_egress_tclass; /**< max_cpu_egress_tclass - Maximum number of CPU egress traffic classes supported */
    uint8_t max_cpu_ingress_tclass; /**< max_cpu_ingress_tclass - Maximum number of CPU ingress traffic classes supported */
    uint8_t max_num_trap_groups; /**< max_num_trap_groups - Maximum number of Trap Groups supported */
    uint8_t max_num_dr_paths; /**< max_num_dr_paths - Maximum number of Direct Route paths in the DR Path table */
};

/**
 * ku_hespr_reg structure is used to store the HESPR register parameters
 */
struct ku_hespr_reg {
    uint8_t stacking_tclass; /**< stacking_tclass - Stacking traffic class for Stacking_EN EMAD response */
    uint8_t cpu_tclass; /**< cpu_tclass - CPU traffic class for Stacking_EN EMAD response */
    uint8_t rdq; /**< rdq - CPU Receive Descriptor Queue for Stacking_EN EMAD response */
};

/**
 * ku_hdrt_reg structure is used to store the HDRT register parameters
 */
struct ku_hdrt_reg {
    uint8_t dr_index; /**< dr_index - Index into the Direct Route table */
    uint8_t hop_cnt; /**< hop_cnt - Hop Count is used to contain the number of valid elements in path and rpath */
    uint8_t path[64]; /**< path - Destination port number on forward path */
    uint8_t rpath[64]; /**< rpath - Destination port number on reverse path */
};

/**
 * ku_hctr_reg structure is used to store the HCTR register parameters
 */
struct ku_hctr_reg {
    uint8_t  custom_trap_index;    /**< custom_trap_index - Custom trap index [0 / 1] */
    uint8_t  tcp_dport;    /**< tcp_dport - tcp destination port */
    uint8_t  tcp_sport;    /**< tcp_dport - tcp source port */
    uint8_t  udp_dport;    /**< udp_dport - udp destination port */
    uint16_t range_min;    /**< Minimum range */
    uint16_t range_max;    /**< Maximum range */
};

/**
 * htgt_local_path structure is used to store the HTGT register local path parameters
 */
struct htgt_local_path {
    uint8_t cpu_tclass; /**< cpu_tclass - CPU traffic class for Trap Group grp */
    uint8_t rdq; /**< rdq - CPU Receive Descriptor Queue for Trap Group grp */
};

/**
 * htgt_stacking_path structure is used to store the HTGT register stacking path parameters
 */
struct htgt_stacking_path {
    uint8_t  stacking_tclass; /**< stacking_tclass - Stacking traffic class for Trap Group grp */
    uint8_t  cpu_tclass; /**< cpu_tclass - CPU traffic class for Trap Group grp */
    uint8_t  rdq; /**< rdq - CPU Receive Descriptor Queue for Trap Group grp */
    uint16_t cpu_sys_port; /**< cpu_sys_port - Designated CPU system port for Trap Group grp */
};

/**
 * htgt_dr_path structure is used to store the HTGT register dr path parameters
 */
struct htgt_dr_path {
    uint8_t dr_ptr; /**< dr_ptr - A pointer to the Direct Route Path Table */
};

/**
 * htgt_eth_path structure is used to store the HTGT register eth path parameters
 */
struct htgt_eth_path {
    uint64_t __attribute__((aligned(8))) mac;  /**< mac - MAC Address */
    uint16_t                             vid; /**< vid - VLAN Identifier */
};

/**
 * htgt_reg_path union is used to store the HTGT register possible paths
 */
union htgt_reg_path {
    struct htgt_local_path    local_path; /**< local_path - local path */
    struct htgt_stacking_path stacking_path; /**< stacking_path - stacking path */
    struct htgt_dr_path       dr_path; /**< dr_path - dr path */
    struct htgt_eth_path      eth_path; /**< eth_path - eth path */
};

/**
 * ku_htgt_reg structure is used to store the HTGT register parameters
 */
struct ku_htgt_reg {
    uint8_t             swid; /**< swid - Switch partition id */
    uint8_t             type; /**< type -  CPU Path Type */
    uint8_t             trap_group; /**< grp -  Trap Group */
    uint8_t             pide; /**< pide - Policer Enable */
    uint8_t             pid; /**< pid - Global Policer ID for Trap Group grp */
    union htgt_reg_path path; /**< path - Path to designated CPU */
    uint8_t             mirror_action; /**< mirror_action - trap mirror action */
    uint8_t             mirror_agent; /**< mirror_agent - mirroring agent */
    uint8_t             priority; /**< priority - trap group priority */
    uint32_t            mirror_probability_rate; /**< sampling rate = 1 out of rate packets */
};

/**
 * ku_mfm_reg structure is used to store the MFM register parameters
 */
struct ku_mfm_reg {
    uint8_t                              index; /**< index - Index to the Fabric Memory table */
    uint64_t __attribute__((aligned(8))) memory; /**< memory - Holds software-written data (Default value: 0x0) */
    uint64_t __attribute__((aligned(8))) memory_mask; /**< memory_mask - On write commands, indicates which of the bits from memory field are updated */
};

typedef struct sxd_slrip_slrip_16nm {
    uint8_t  ib_sel;
    uint8_t  ffe_tap0;
    uint8_t  ffe_tap1;
    uint8_t  ffe_tap2;
    uint8_t  ffe_tap3;
    uint8_t  ffe_tap4;
    uint8_t  ffe_tap5;
    uint8_t  ffe_tap6;
    uint8_t  ffe_tap7;
    uint8_t  ffe_tap8;
    uint8_t  sel_enc0;
    uint16_t ffe_tap_en;
    uint8_t  sel_enc1;
    uint8_t  sel_enc2;
    uint8_t  mixer_offset0;
    uint8_t  mixer_offset1;
    uint8_t  saved0_sel_enc0;
    uint8_t  saved0_mixer_offset0;
    uint8_t  saved1_sel_enc0;
    uint8_t  saved1_mixer_offset0;
} sxd_slrip_slrip_16nm_t;

typedef struct sxd_slrip_slrip_7nm {
    uint8_t  feq_train_mode;
    uint8_t  term_lpf_override_ctrl;
    uint8_t  vref_val_mode_ctrl;
    uint8_t  dffe_override_ctrl;
    uint8_t  vga_gain_override_ctrl;
    uint8_t  hf_gain_override_ctrl;
    uint8_t  mf_pole_override_ctrl;
    uint8_t  mf_gain_override_ctrl;
    uint8_t  lf_pole_override_ctrl;
    uint8_t  lf_gain_override_ctrl;
    uint8_t  dc_gain_override_ctrl;
    uint8_t  term_attn_override_ctrl;
    uint8_t  f1_override_ctrl;
    uint8_t  f2_override_ctrl;
    uint8_t  f3_override_ctrl;
    uint8_t  f4_override_ctrl;
    uint8_t  f5_override_ctrl;
    uint8_t  f6_override_ctrl;
    uint8_t  f7_override_ctrl;
    uint8_t  f8_override_ctrl;
    uint8_t  fm1_override_ctrl;
    uint8_t  fm2_override_ctrl;
    uint8_t  fm3_override_ctrl;
    uint8_t  eth_override_ctrl;
    uint8_t  mf_pole;
    uint8_t  mf_gain;
    uint8_t  lf_pole;
    uint8_t  lf_gain;
    uint8_t  term_attn_ctrl;
    uint8_t  hf_gain;
    uint8_t  dc_gain;
    uint8_t  adc_vref_val;
    uint8_t  vga_gain;
    uint8_t  ffe_fm1;
    uint8_t  ffe_fm2;
    uint8_t  ffe_fm3;
    uint8_t  ffe_f4;
    uint8_t  ffe_f3;
    uint8_t  ffe_f2;
    uint8_t  ffe_f1;
    uint8_t  ffe_f8;
    uint8_t  ffe_f7;
    uint8_t  ffe_f6;
    uint8_t  ffe_f5;
    uint8_t  dffe_dsel3;
    uint8_t  dffe_coef3;
    uint8_t  dffe_dsel2;
    uint8_t  dffe_coef2;
    uint8_t  dffe_dsel1;
    uint8_t  dffe_coef1;
    uint8_t  dffe_dsel0;
    uint8_t  dffe_coef0;
    uint8_t  dffe_dsel7;
    uint8_t  dffe_coef7;
    uint8_t  dffe_dsel6;
    uint8_t  dffe_coef6;
    uint8_t  dffe_dsel5;
    uint8_t  dffe_coef5;
    uint8_t  dffe_dsel4;
    uint8_t  dffe_coef4;
    uint8_t  dffe_dsel8;
    uint8_t  dffe_coef8;
    uint16_t th1;
    uint16_t th0;
    uint16_t th3;
    uint16_t th2;
    uint16_t th5;
    uint16_t th4;
    uint16_t th7;
    uint16_t th6;
    uint16_t th9;
    uint16_t th8;
    uint16_t th11;
    uint16_t th10;
    uint16_t th13;
    uint16_t th12;
    uint16_t th15;
    uint16_t th14;
    uint16_t th17;
    uint16_t th16;
    uint16_t th19;
    uint16_t th18;
    uint16_t th21;
    uint16_t th20;
} sxd_slrip_slrip_7nm_t;

union slrip_page_data {
    sxd_slrip_slrip_16nm_t slrip_16nm;
    sxd_slrip_slrip_7nm_t  slrip_7nm;
};

/**
 * ku_slrip_reg structure is used to store the SLRIP register parameters
 */
struct ku_slrip_reg {
    uint8_t               status;
    uint8_t               version;
    uint8_t               local_port;
    uint8_t               pnat;
    uint8_t               lp_msb;
    uint8_t               lane;
    uint8_t               port_type;
    union slrip_page_data page_data;
};

#define SXD_SLRP_ADC_VOS_NUM 64

#define SXD_SLRP_ADC_GOS_NUM 64


typedef enum sxd_slrp_ccal_state {
    SXD_SLRP_CCAL_STATE_IDLE_E  = 0x0,
    SXD_SLRP_CCAL_STATE_START_E = 0x1,
    SXD_SLRP_CCAL_STATE_ON_E    = 0x2,
    SXD_SLRP_CCAL_STATE_ABORT_E = 0x3,
    SXD_SLRP_CCAL_STATE_MIN     = SXD_SLRP_CCAL_STATE_IDLE_E,
    SXD_SLRP_CCAL_STATE_MAX     = SXD_SLRP_CCAL_STATE_ABORT_E
} sxd_slrp_ccal_state_t;


typedef enum sxd_slrp_ccal_op {
    SXD_SLRP_CCAL_OP_OFF_E   = 0x0,
    SXD_SLRP_CCAL_OP_NOP_E   = 0x1,
    SXD_SLRP_CCAL_OP_INIT_E  = 0x2,
    SXD_SLRP_CCAL_OP_START_E = 0x3,
    SXD_SLRP_CCAL_OP_MIN     = SXD_SLRP_CCAL_OP_OFF_E,
    SXD_SLRP_CCAL_OP_MAX     = SXD_SLRP_CCAL_OP_START_E
} sxd_slrp_ccal_op_t;

typedef struct sxd_slrp_slrp_40nm_28nm {
    uint8_t  ib_sel;
    uint8_t  dp_sel;
    uint8_t  dp90sel;
    uint8_t  mix90phase;
    uint8_t  ffe_tap0;
    uint8_t  ffe_tap1;
    uint8_t  ffe_tap2;
    uint8_t  ffe_tap3;
    uint8_t  ffe_tap4;
    uint8_t  ffe_tap5;
    uint8_t  ffe_tap6;
    uint8_t  ffe_tap7;
    uint8_t  ffe_tap8;
    uint8_t  mixerbias_tap_amp;
    uint16_t ffe_tap_en;
    uint8_t  ffe_tap_offset0;
    uint8_t  ffe_tap_offset1;
    uint16_t slicer_offset0;
    uint16_t mixer_offset0;
    uint16_t mixer_offset1;
    uint8_t  mixerbgn_inp;
    uint8_t  mixerbgn_inn;
    uint8_t  mixerbgn_refp;
    uint8_t  mixerbgn_refn;
    uint8_t  sel_slicer_lctrl_h;
    uint8_t  sel_slicer_lctrl_l;
    uint8_t  ref_mixer_vreg;
    uint8_t  slicer_gctrl;
    uint8_t  lctrl_input;
    uint8_t  mixer_offset_cm1;
    uint8_t  common_mode;
    uint16_t mixer_offset_cm0;
    uint16_t slicer_offset_cm;
} sxd_slrp_slrp_40nm_28nm_t;

typedef struct sxd_slrp_slrp_16nm {
    uint8_t mixer_offset_up;
    uint8_t mixer_offset_down;
    uint8_t sel_enc;
    uint8_t dp_sel;
    uint8_t sel_ref_in_mixer_biasgen_up;
    uint8_t sel_ref_in_mixer_biasgen_mid;
    uint8_t sel_ref_in_mixer_biasgen_down;
    uint8_t sel_ref_in_mixer_biasgen_eo;
    uint8_t sel_ref_out_mixer_biasgen_up;
    uint8_t sel_ref_out_mixer_biasgen_mid;
    uint8_t sel_ref_out_mixer_biasgen_down;
    uint8_t sel_ref_out_mixer_biasgen_eo;
    uint8_t sel_amp_mixer_biasgen_up;
    uint8_t sel_amp_mixer_biasgen_mid;
    uint8_t sel_amp_mixer_biasgen_down;
    uint8_t sel_amp_mixer_biasgen_eo;
    uint8_t mixer_offset_eye_scan;
    uint8_t gctrl_bin_bgn0_n;
    uint8_t gctrl_bin_bgn0_p;
    uint8_t gctrl_bin_bgn1_n;
    uint8_t gctrl_bin_bgn1_p;
    uint8_t sel_digital_gctrl;
    uint8_t sel_bias2ctle;
    uint8_t selgc_ref_op0_alev_ctle;
    uint8_t selgc_ref_op1_alev_ctle;
    uint8_t sel_bias_en_0;
    uint8_t sel_bias_en_1;
    uint8_t sel_bias_en_2;
    uint8_t sel_bias_en_3;
    uint8_t sel_bias_en_4;
    uint8_t sel_bias_en_5;
    uint8_t sel_bias_en_6;
    uint8_t sel_gctrln_en_0;
    uint8_t sel_gctrln_en_1;
    uint8_t sel_gctrln_en_2;
    uint8_t sel_gctrln_en_3;
    uint8_t sel_gctrln_en_4;
    uint8_t sel_gctrln_en_5;
    uint8_t sel_gctrln_en_6;
    uint8_t sel_gctrlp_en_0;
    uint8_t sel_gctrlp_en_1;
    uint8_t sel_gctrlp_en_2;
    uint8_t sel_gctrlp_en_3;
    uint8_t sel_gctrlp_en_4;
    uint8_t sel_gctrlp_en_5;
    uint8_t sel_gctrlp_en_6;
    uint8_t crnt_bgn_offset_p1;
    uint8_t crnt_bgn_offset_n1;
    uint8_t crnt_bgn_offset_p0;
    uint8_t crnt_bgn_offset_n0;
} sxd_slrp_slrp_16nm_t;

typedef struct sxd_slrp_slrp_gearbox {
    uint8_t  ffe_tap_index;
    uint8_t  ffe_sub_channel;
    uint8_t  snr_en;
    uint8_t  dsp_mode;
    uint8_t  afe_trim;
    uint8_t  ctle;
    uint16_t raw_snr_value;
    uint8_t  dsp_err_gen;
    uint8_t  snr_sym_cnt;
    uint32_t db_snr_value;
    uint8_t  ffe_tap_value;
} sxd_slrp_slrp_gearbox_t;

typedef struct sxd_slrp_slrp_usr {
    uint8_t mixer00;
    uint8_t mixer90;
    uint8_t termination;
    uint8_t neg_cap_up;
    uint8_t neg_cap_mid;
    uint8_t neg_cap_dn;
    uint8_t offset_coarse_polarity_up;
    uint8_t offset_coarse_polarity_mid;
    uint8_t offset_coarse_polarity_dn;
    uint8_t offset_fine_polarity_up;
    uint8_t offset_fine_polarity_mid;
    uint8_t offset_fine_polarity_dn;
    uint8_t amp_vga;
    uint8_t amp_vga_last_stage;
    uint8_t offset_coarse_up;
    uint8_t offset_coarse_mid;
    uint8_t offset_coarse_dn;
    uint8_t offset_fine_up;
    uint8_t offset_fine_mid;
    uint8_t offset_fine_dn;
} sxd_slrp_slrp_usr_t;

typedef struct sxd_slrp_slrp_7nm {
    uint8_t               adc_recording_admin;
    uint8_t               adc_recording_status;
    uint8_t               adc_rocording_lanes;
    uint8_t               edge_vos_ccal_en;
    uint8_t               adc_gain_shift_auto;
    uint8_t               ccal_mode;
    uint8_t               ctle_override_ctrl;
    uint8_t               vga_override_ctrl;
    uint8_t               adc_vos_override_ctrl;
    uint8_t               adc_gain_override_ctrl;
    uint8_t               phos_override_ctrl;
    uint8_t               cal_error_cnt;
    sxd_slrp_ccal_state_t ccal_state;
    sxd_slrp_ccal_op_t    ccal_op;
    uint8_t               phos;
    uint8_t               vga_vos1;
    uint8_t               vga_vos0;
    uint8_t               ctle_vos0;
    uint8_t               adc_vos[SXD_SLRP_ADC_VOS_NUM];
    uint8_t               adc_gos[SXD_SLRP_ADC_GOS_NUM];
    uint8_t               phos3;
    uint8_t               phos2;
    uint8_t               phos1;
    uint8_t               phos0;
    uint8_t               phos7;
    uint8_t               phos6;
    uint8_t               phos5;
    uint8_t               phos4;
} sxd_slrp_slrp_7nm_t;

union slrp_page_data {
    sxd_slrp_slrp_40nm_28nm_t slrp_40nm_28nm;
    sxd_slrp_slrp_16nm_t      slrp_16nm;
    sxd_slrp_slrp_gearbox_t   slrp_gearbox;
    sxd_slrp_slrp_usr_t       slrp_usr;
    sxd_slrp_slrp_7nm_t       slrp_7nm;
};

/**
 * ku_slrp_reg structure is used to store the SLRP register parameters
 */
struct ku_slrp_reg {
    uint8_t              status;
    uint8_t              version;
    uint8_t              local_port;
    uint8_t              pnat;
    uint8_t              lp_msb;
    uint8_t              lane;
    uint8_t              port_type;
    union slrp_page_data page_data;
};

#define SXD_PEUCG_PAGE_DATA_NUM 47

typedef struct sxd_peucg_page_data {
    uint16_t payload_data;
    uint8_t  rxtx;
    uint16_t address;
} sxd_peucg_page_data_t;

/**
 * ku_peucg_reg structure is used to store the PEUCG register parameters
 */
struct ku_peucg_reg {
    uint8_t               unit;
    uint8_t               local_port;
    uint8_t               pnat;
    uint8_t               lp_msb;
    uint8_t               lane;
    uint8_t               status;
    uint8_t               payload_size;
    uint8_t               db;
    uint8_t               clr;
    uint8_t               enum_init;
    uint16_t              num_of_entries;
    uint16_t              db_index;
    sxd_peucg_page_data_t page_data[SXD_PEUCG_PAGE_DATA_NUM];
};

#define SXD_PPLL_PLL_STATUS_28NM_NUM 4

#define SXD_PPLL_PLL_STATUS_16NM_NUM 4


typedef enum sxd_ppll_pll_ugl_state {
    SXD_PPLL_PLL_UGL_STATE_IDDQ_E            = 0x0,
    SXD_PPLL_PLL_UGL_STATE_SLEEP_E           = 0x1,
    SXD_PPLL_PLL_UGL_STATE_RCAL_DONE_WAIT1_E = 0x2,
    SXD_PPLL_PLL_UGL_STATE_RCAL_DONE_WAIT0_E = 0x3,
    SXD_PPLL_PLL_UGL_STATE_IDLE_E            = 0x4,
    SXD_PPLL_PLL_UGL_STATE_CAL_DONE_WAIT1_E  = 0x5,
    SXD_PPLL_PLL_UGL_STATE_CAL_DONE_WAIT0_E  = 0x6,
    SXD_PPLL_PLL_UGL_STATE_ACTIVE_E          = 0x7,
    SXD_PPLL_PLL_UGL_STATE_LOCK_E            = 0x8,
    SXD_PPLL_PLL_UGL_STATE_SPEED_CHANGE_E    = 0x9,
    SXD_PPLL_PLL_UGL_STATE_MIN               = SXD_PPLL_PLL_UGL_STATE_IDDQ_E,
    SXD_PPLL_PLL_UGL_STATE_MAX               = SXD_PPLL_PLL_UGL_STATE_SPEED_CHANGE_E
} sxd_ppll_pll_ugl_state_t;


typedef enum sxd_ppll_version {
    SXD_PPLL_VERSION_PRODUCTS_28NM_E = 0x0,
    SXD_PPLL_VERSION_PRODUCTS_16NM_E = 0x3,
    SXD_PPLL_VERSION_PRODUCTS_7NM_E  = 0x4,
    SXD_PPLL_VERSION_MIN             = SXD_PPLL_VERSION_PRODUCTS_28NM_E,
    SXD_PPLL_VERSION_MAX             = SXD_PPLL_VERSION_PRODUCTS_7NM_E
} sxd_ppll_version_t;

typedef struct sxd_ppll_pll_status_28nm {
    uint8_t  lock_cal;
    uint8_t  lock_status;
    uint16_t algo_f_ctrl;
    uint8_t  analog_algo_num_var;
    uint16_t f_ctrl_measure;
    uint8_t  analog_var;
    uint8_t  high_var;
    uint8_t  low_var;
    uint8_t  mid_var;
} sxd_ppll_pll_status_28nm_t;

typedef struct sxd_ppll_ppll_28nm {
    uint8_t                    ae;
    sxd_ppll_pll_status_28nm_t pll_status_28nm[SXD_PPLL_PLL_STATUS_28NM_NUM];
} sxd_ppll_ppll_28nm_t;

typedef struct sxd_ppll_pll_status_16nm {
    uint8_t  lock_status;
    uint8_t  pll_pwrup;
    uint8_t  lock_pulse;
    uint16_t lock_lost_counter;
    uint8_t  ae;
    uint8_t  clear_cause;
    uint8_t  lock_clk_val_cause;
    uint8_t  plllock_clk_val;
    uint8_t  clock_valid;
    uint8_t  pll_speed;
    uint8_t  lock;
    uint8_t  analog_var;
    uint8_t  high_var;
    uint8_t  low_var;
    uint8_t  mid_var;
    uint16_t fctrl_measure;
} sxd_ppll_pll_status_16nm_t;

typedef struct sxd_ppll_ppll_reg_16nm {
    sxd_ppll_pll_status_16nm_t pll_status_16nm[SXD_PPLL_PLL_STATUS_16NM_NUM];
} sxd_ppll_ppll_reg_16nm_t;

typedef struct sxd_ppll_ppll_reg_7nm {
    sxd_ppll_pll_ugl_state_t pll_ugl_state;
    uint16_t                 lokcdet_error_count;
    uint8_t                  lockdet_err_measure_done;
    uint8_t                  lockdet_err_state;
    uint8_t                  lockdet_cnt_based_lock;
    uint8_t                  lockdet_err_cnt_unlocked_sticky;
    uint8_t                  lockdet_err_cnt_locked_sticky;
    uint8_t                  lockdet_err_cnt_active_lock;
    uint8_t                  cal_internal_state;
    uint8_t                  cal_main_state;
    uint8_t                  pll_lockdet_state;
    uint8_t                  pwr_up_state;
    uint8_t                  cal_abort_sticky;
    uint8_t                  cal_abort;
    uint8_t                  cal_valid_sticky;
    uint8_t                  dco_coarse;
    uint8_t                  cal_done;
    uint8_t                  cal_en;
    uint8_t                  dco_coarse_bin;
    uint16_t                 cal_error_counter;
    uint8_t                  lma_rcal_code;
    uint8_t                  lma_rcal_tx_p_code;
    uint8_t                  lma_rcal_tx_n_code;
    uint8_t                  rcal_done_valid_sticky;
    uint8_t                  rcal_tx_p_valid_sticky;
    uint8_t                  rcal_tx_n_valid_sticky;
    uint8_t                  rcal_fsm_done;
    uint8_t                  speedo_valid;
    uint8_t                  cvb_trim_valid;
    uint8_t                  bg_trim_valid;
    uint16_t                 speedo;
    uint8_t                  cvb_trim;
    uint8_t                  bg_trim;
} sxd_ppll_ppll_reg_7nm_t;

union ppll_page_data {
    sxd_ppll_ppll_28nm_t     ppll_28nm;
    sxd_ppll_ppll_reg_16nm_t ppll_reg_16nm;
    sxd_ppll_ppll_reg_7nm_t  ppll_reg_7nm;
};

/**
 * ku_ppll_reg structure is used to store the PPLL register parameters
 */
struct ku_ppll_reg {
    uint8_t              num_pll_groups;
    uint8_t              pll_group;
    uint8_t              pci_oob_pll;
    uint8_t              num_plls;
    sxd_ppll_version_t   version;
    union ppll_page_data page_data;
};

typedef enum sxd_slrg_fom_mode {
    SXD_SLRG_FOM_MODE_FOM_MODE_EYEC_E    = 0x0,
    SXD_SLRG_FOM_MODE_FOM_MODE_EYEO_E    = 0x1,
    SXD_SLRG_FOM_MODE_FOM_MODE_EYEM_E    = 0x2,
    SXD_SLRG_FOM_MODE_FOM_MODE_BER_E     = 0x3,
    SXD_SLRG_FOM_MODE_FOM_MODE_EYEC_VN_E = 0x4,
    SXD_SLRG_FOM_MODE_FOM_MODE_EYEC_VP_E = 0x5,
    SXD_SLRG_FOM_MODE_FOM_MODE_EYEM_VN_E = 0x6,
    SXD_SLRG_FOM_MODE_FOM_MODE_EYEM_VP_E = 0x7,
    SXD_SLRG_FOM_MODE_MIN                = SXD_SLRG_FOM_MODE_FOM_MODE_EYEC_E,
    SXD_SLRG_FOM_MODE_MAX                = SXD_SLRG_FOM_MODE_FOM_MODE_EYEM_VP_E
} sxd_slrg_fom_mode_t;

typedef struct sxd_slrg_slrg_40nm_28nm {
    uint8_t  grade_lane_speed;
    uint8_t  grade_version;
    uint32_t grade;
    uint8_t  offset_units;
    uint8_t  phase_units;
    uint8_t  height_grade_type;
    uint32_t height_grade;
    uint16_t height_dz;
    uint16_t height_dv;
    uint16_t height_sigma;
    uint16_t height_eo_pos;
    uint16_t height_eo_neg;
    uint8_t  phase_grade_type;
    uint32_t phase_grade;
    uint8_t  phase_eo_pos;
    uint8_t  phase_eo_neg;
    uint16_t ffe_set_tested;
    uint16_t test_errors_per_lane;
} sxd_slrg_slrg_40nm_28nm_t;

typedef struct sxd_slrg_slrg_16nm {
    uint8_t  grade_lane_speed;
    uint8_t  grade_version;
    uint32_t grade;
    uint16_t height_eo_pos_up;
    uint16_t height_eo_neg_up;
    uint8_t  phase_eo_pos_up;
    uint8_t  phase_eo_neg_up;
    uint16_t height_eo_pos_mid;
    uint16_t height_eo_neg_mid;
    uint8_t  phase_eo_pos_mid;
    uint8_t  phase_eo_neg_mid;
    uint16_t height_eo_pos_low;
    uint16_t height_eo_neg_low;
    uint8_t  phase_eo_pos_low;
    uint8_t  phase_eo_neg_low;
    uint16_t mid_eye_grade;
    uint16_t up_eye_grade;
    uint16_t dn_eye_grade;
} sxd_slrg_slrg_16nm_t;

typedef struct sxd_slrg_slrg_7nm {
    uint8_t             fom_measurment;
    sxd_slrg_fom_mode_t fom_mode;
    uint8_t             initial_fom;
    uint8_t             last_fom;
    uint8_t             upper_eye;
    uint8_t             mid_eye;
    uint8_t             lower_eye;
} sxd_slrg_slrg_7nm_t;

typedef struct sxd_slrg_lane_meas_info {
    uint8_t  upper_max;
    uint8_t  mid_max;
    uint8_t  lower_max;
    uint8_t  comp_max;
    uint8_t  upper_min;
    uint8_t  mid_min;
    uint8_t  lower_min;
    uint8_t  comp_min;
    uint16_t upper_std;
    uint16_t mid_std;
    uint16_t lower_std;
    uint16_t comp_std;
    uint16_t upper_avg;
    uint16_t mid_avg;
    uint16_t lower_avg;
    uint16_t comp_avg;
} sxd_slrg_lane_meas_info_t;

typedef struct sxd_slrg_slrg_7nm_testing {
    uint8_t                   status;
    uint16_t                  iterations;
    sxd_slrg_lane_meas_info_t lane_meas_info;
} sxd_slrg_slrg_7nm_testing_t;

union slrg_page_data {
    sxd_slrg_slrg_40nm_28nm_t   slrg_40nm_28nm;
    sxd_slrg_slrg_16nm_t        slrg_16nm;
    sxd_slrg_slrg_7nm_t         slrg_7nm;
    sxd_slrg_slrg_7nm_testing_t slrg_7nm_testing;
};

/**
 * ku_slrg_reg structure is used to store the SLRG register parameters
 */
struct ku_slrg_reg {
    uint8_t              status;
    uint8_t              version;
    uint8_t              local_port;
    uint8_t              pnat;
    uint8_t              lp_msb;
    uint8_t              lane;
    uint8_t              port_type;
    uint8_t              test_mode;
    union slrg_page_data page_data;
};

/**
 * ku_access_slrg_reg structure is used to store the access register SLRG command parameters
 */
struct ku_access_slrg_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_slrg_reg      slrg_reg; /**< slrg_reg - slrg register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_slrp_reg structure is used to store the access register SLRP command parameters
 */
struct ku_access_slrp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_slrp_reg      slrp_reg; /**< slrp_reg - slrp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_peucg_reg structure is used to store the access register PEUCG command parameters
 */
struct ku_access_peucg_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_peucg_reg     peucg_reg; /**< peucg_reg - peucg register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_ppll_reg structure is used to store the access register PPLL command parameters
 */
struct ku_access_ppll_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppll_reg      ppll_reg; /**< ppll_reg - ppll register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_slcr_v2_reg structure is used to store the access register SLCR_V2 command parameters
 */
struct ku_access_slcr_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_slcr_v2_reg   slcr_v2_reg; /**< ku_slcr_v2_reg - slcr_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sfn_reg structure is used to store the access register SFN command parameters
 */
struct ku_access_sfn_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sfn_reg       sfn_reg; /**< ku_sfn_reg - sfn register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_spvtr_reg structure is used to store the access register SPVTR command parameters
 */
struct ku_access_spvtr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spvtr_reg     spvtr_reg; /**< ku_spvtr_reg - spvtr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pspa_reg structure is used to store the access register PSPA command parameters
 */
struct ku_access_pspa_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pspa_reg      pspa_reg; /**< pspa_reg - pspa register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pmlp_reg structure is used to store the access register PMLP command parameters
 */
struct ku_access_pmlp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmlp_reg      pmlp_reg; /**< pmlp_reg - pmlp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_plib_reg structure is used to store the access register PLIB command parameters
 */
struct ku_access_plib_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_plib_reg      plib_reg; /**< plib_reg - plib register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_ppaos_reg structure is used to store the access register PPAOS command parameters
 */
struct ku_access_ppaos_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppaos_reg     ppaos_reg; /**< ppaos_reg - ppaos register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pplm_reg structure is used to store the access register PPLM command parameters
 */
struct ku_access_pplm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pplm_reg      pplm_reg; /**< pplm_reg - pplm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_plpc_reg structure is used to store the access register PLPC command parameters
 */
struct ku_access_plpc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_plpc_reg      plpc_reg; /**< plpc_reg - plpc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pmpc_reg structure is used to store the access register PMPC command parameters
 */
struct ku_access_pmpc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmpc_reg      pmpc_reg; /**< pmpc_reg - pmpc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pmpr_reg structure is used to store the access register PMPR command parameters
 */
struct ku_access_pmpr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmpr_reg      pmpr_reg; /**< pmpr_reg - pmpr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pcnr_reg structure is used to store the access register PCNR command parameters
 */
struct ku_access_pcnr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pcnr_reg      pcnr_reg; /**< ku_pcnr_reg - pcnr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pcmr_reg structure is used to store the access register PCMR command parameters
 */
struct ku_access_pcmr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pcmr_reg      pcmr_reg; /**< ku_pcmr_reg - pcmr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pfsc_reg structure is used to store the access register PFSC command parameters
 */
struct ku_access_pfsc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pfsc_reg      pfsc_reg; /**< ku_pfsc_reg - pfsc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


/**
 * ku_access_mfsc_reg structure is used to store the access register MFSC command parameters
 */
struct ku_access_mfsc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfsc_reg      mfsc_reg; /**< mfsc_reg - mfsc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mfsm_reg structure is used to store the access register MFSM command parameters
 */
struct ku_access_mfsm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfsm_reg      mfsm_reg; /**< mfsm_reg - mfsm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mfsl_reg structure is used to store the access register MFSL command parameters
 */
struct ku_access_mfsl_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfsl_reg      mfsl_reg; /**< mfsl_reg - mfsl register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mjtag_reg structure is used to store the access register MJTAG command parameters
 */
struct ku_access_mjtag_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mjtag_reg     mjtag_reg; /**< mjtag_reg - mjtag register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_ppsc_reg structure is used to store the access
 * register PPSC command parameters
 */
struct ku_access_ppsc_reg {
    struct ku_operation_tlv op_tlv;     /**< op_tlv - operation tlv struct */
    struct ku_ppsc_reg      ppsc_reg;   /**< ppsc_reg- ppsc register tlv */
    uint8_t                 dev_id;     /**< dev_id - device id */
};

/**
 * ku_access_pelc_reg structure is used to store the access register PELC command parameters
 */
struct ku_access_pelc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pelc_reg      pelc_reg; /**< pelc_reg - pelc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pvlc_reg structure is used to store the access register PVLC command parameters
 */
struct ku_access_pvlc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pvlc_reg      pvlc_reg; /**< pvlc_reg - pvlc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mcia_reg structure is used to store the access register MCIA command parameters
 */
struct ku_access_mcia_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mcia_reg      mcia_reg; /**< mcia_reg - mcia register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_fore_reg structure is used to store the access register FORE command parameters
 */
struct ku_access_fore_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_fore_reg      fore_reg; /**< fore_reg - fore register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


/**
 * ku_access_mtbr_reg structure is used to store the access register MTBR command parameters
 */
struct ku_access_mtbr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtbr_reg      mtbr_reg; /**< mtbr_reg - mtbr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mmdio_reg structure is used to store the access register MMDIO command parameters
 */
struct ku_access_mmdio_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mmdio_reg     mmdio_reg; /**< mmdio_reg - mmdio register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mmia_reg structure is used to store the access register MMIA command parameters
 */
struct ku_access_mmia_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mmia_reg      mmia_reg; /**< mmia_reg - mmia register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mfpa_reg structure is used to store the access register MFPA command parameters
 */
struct ku_access_mfpa_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfpa_reg      mfpa_reg; /**< mfpa_reg - mfpa register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mfbe_reg structure is used to store the access register MFBE command parameters
 */
struct ku_access_mfbe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfbe_reg      mfbe_reg; /**< mfbe_reg - mfbe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mfba_reg structure is used to store the access register MFBA command parameters
 */
struct ku_access_mfba_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfba_reg      mfba_reg; /**< mfba_reg - mfba register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_raw_reg structure is used to store the access register command parameters for a RAW register
 */
struct ku_access_raw_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_raw_reg       raw_reg; /**< raw_reg - raw_reg register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_reg_raw_buff structure is used to store access register RAW parameters
 */
struct ku_access_reg_raw_buff {
    struct ku_raw_reg raw_buff;   /**< raw_buff - raw_reg register tlv */
    uint8_t           dev_id; /**< dev_id - device id */
};

/**
 * ku_access_hpkt_reg structure is used to store the access register HPKT command parameters
 */
struct ku_access_hpkt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hpkt_reg      hpkt_reg; /**< hpkt_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_hcap_reg structure is used to store the access register HCAP command parameters
 */
struct ku_access_hcap_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hcap_reg      hcap_reg; /**< hcap_reg - hcap register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_hdrt_reg structure is used to store the access register HDRT command parameters
 */
struct ku_access_hdrt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hdrt_reg      hdrt_reg; /**< hdrt_reg - hdrt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_hctr_reg structure is used to store the access register HCTR command parameters
 */
struct ku_access_hctr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_hctr_reg      hctr_reg; /**< hctr_reg - hctr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_htgt_reg structure is used to store the access register HTGT command parameters
 */
struct ku_access_htgt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_htgt_reg      htgt_reg; /**< htgt_reg - htgt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mfcr_reg structure is used to store the access register MFCR command parameters
 */
struct ku_access_mfcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfcr_reg      mfcr_reg; /**< mfcr_reg - mfcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mfm_reg structure is used to store the access register MFM command parameters
 */
struct ku_access_mfm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mfm_reg       mfm_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sspr_reg structure is used to store the access
 * register MFM command parameters
 */
struct ku_access_sspr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sspr_reg      sspr_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_spmcr_reg structure is used to store the access
 * register spmcr command parameters
 */
struct ku_access_spmcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spmcr_reg     spmcr_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sbmm_reg structure is used to store the access
 * register sbmm command parameters
 */
struct ku_access_sbmm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbmm_reg      sbmm_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_smid_reg structure is used to store the access
 * register smid command parameters
 */
struct ku_access_smid_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_smid_reg      smid_reg; /**< smid_reg - smid register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_spms_reg structure is used to store the access
 * register spms command parameters
 */
struct ku_access_spms_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spms_reg      spms_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sver_reg structure is used to store the access
 * register sver command parameters
 */
struct ku_access_sver_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sver_reg      sver_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_spvc_reg structure is used to store the access
 * register spvc command parameters
 */
struct ku_access_spvc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spvc_reg      spvc_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_qpbr_reg structure is used to store the access
 * register qpbr command parameters
 */
struct ku_access_qpbr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qpbr_reg      qpbr_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


/**
 * ku_access_qpem_reg structure is used to store the access
 * register qpem command parameters
 */
struct ku_access_qpem_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qpem_reg      qpem_reg; /**< qpem_reg - qpem register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_plbf_reg structure is used to store the access
 * register PLBF command parameters
 */
struct ku_access_plbf_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_plbf_reg      plbf_reg; /**< plbf_reg - plbf register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_msci_reg structure is used to store the access
 * register MSCI command parameters
 */
struct ku_access_msci_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_msci_reg      msci_reg; /**< msci_reg - msci register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mrsr_reg structure is used to store the access
 * register MRSR command parameters
 */
struct ku_access_mrsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mrsr_reg      mrsr_reg; /**< mrsr_reg - mrsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mpsc_reg structure is used to store the access
 * register MPSC command parameters
 */
struct ku_access_mpsc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mpsc_reg      mpsc_reg; /**< mpsc_reg - mpsc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mlcr_reg structure is used to store the access
 * register MLCR command parameters
 */
struct ku_access_mlcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mlcr_reg      mlcr_reg; /**< mlcr_reg - mlcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_ptce3_reg structure is used to store the access
 * register ptce3 command parameters
 */
struct ku_access_ptce3_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ptce3_reg     ptce3_reg; /**< ptce3_reg - ptce3 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef enum sxd_init_rr {
    SXD_INIT_RR_TYPE_0 = 0,
    SXD_INIT_RR_TYPE_1 = 1
} sxd_init_rr_t;

typedef enum sxd_rr_status {
    SXD_RR_STATUS_NONE    = 0,
    SXD_RR_STATUS_ONGOING = 1
} sxd_rr_status_t;

typedef enum sxd_iedr_resource_type {
    SXD_IEDR_RESOURCE_TYPE_ADJACENCY_E             = 0x21,
    SXD_IEDR_RESOURCE_TYPE_NVE_DECAP_E             = 0x21,
    SXD_IEDR_RESOURCE_TYPE_IPINIP_DECAP_E          = 0x21,
    SXD_IEDR_RESOURCE_TYPE_MPLS_NHLFE_E            = 0x22,
    SXD_IEDR_RESOURCE_TYPE_ACL_ACTION_SET_E        = 0x23,
    SXD_IEDR_RESOURCE_TYPE_PBS_E                   = 0x24,
    SXD_IEDR_RESOURCE_TYPE_CPU_SEND_MC_IDS_E       = 0x24,
    SXD_IEDR_RESOURCE_TYPE_MPLS_ILM_E              = 0x25,
    SXD_IEDR_RESOURCE_TYPE_RIGRV2_E                = 0x26,
    SXD_IEDR_RESOURCE_TYPE_MC_EXPECTED_IRIF_LIST_E = 0x27,
    SXD_IEDR_RESOURCE_TYPE_IPV6_E                  = 0x28,
    SXD_IEDR_RESOURCE_TYPE_TNUMT_E                 = 0x29
} sxd_iedr_resource_type_e;

typedef enum sxd_iedr_delete_mode {
    SXD_IEDR_DELETE_MODE_FOREGROUND_E = 0,
    SXD_IEDR_DELETE_MODE_BACKGROUND_E = 1
} sxd_iedr_delete_mode_e;

typedef enum sxd_ieds_bg_delete_status {
    SXD_IEDS_BG_DELETE_NONE_E    = 0,
    SXD_IEDS_BG_DELETE_ONGOING_E = 1
} sxd_ieds_bg_delete_status_e;

struct ku_mrrr_reg {
    sxd_init_rr_t   init_rr;
    sxd_rr_status_t rr_status;
};

/**
 * ku_access_mrrr_reg structure is used to store the access register MRRR command parameters
 */
struct ku_access_mrrr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mrrr_reg      mrrr_reg; /**< ku_mrrr_reg - mrrr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mdri_reg structure is used to store the access
 * register MDRI command parameters
 */
struct ku_access_mdri_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mdri_reg      mdri_reg; /**< mdri_reg - mdri register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mpgcr_reg structure is used to store the access
 * register MPGCR command parameters
 */
struct ku_access_mpgcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mpgcr_reg     mpgcr_reg; /**< mpgcr_reg - mpgcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mpilm_reg structure is used to store the access
 * register MPILM command parameters
 */
struct ku_access_mpilm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mpilm_reg     mpilm_reg; /**< mpilm_reg - mpilm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_slrip_reg structure is used to store the access register SLRIP command parameters
 */
struct ku_access_slrip_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_slrip_reg     slrip_reg; /**< slrip_reg - slrip register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_cwcp_profile structure is used with ku_access_cwcp_reg as a profile param
 * register cwcp command parameters
 */
struct ku_cw_profile {
    uint32_t profile_i_min;
    uint8_t  profile_i_percent;
    uint32_t profile_i_max;
};
/**
 * ku_access_cwcp_reg structure is used to store the access
 * register cwcp command parameters
 */
struct ku_cwtp_reg {
    uint8_t              local_port;
    uint8_t              lp_msb;    /**< local_port msb */
    uint8_t              traffic_class;
    uint8_t              mode;
    struct ku_cw_profile profiles[REDECN_NUM_HW_PROFILES];
};

/**
 * ku_access_cwtp_reg structure is used to store the access register CWTP command parameters
 */
struct ku_access_cwtp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_cwtp_reg      cwtp_reg; /**< ku_cwtp_reg - cwtp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pfcc_reg structure is used to store the access register PFCC command parameters
 */
struct ku_access_pfcc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pfcc_reg      pfcc_reg; /**< ku_pfcc_reg - pfcc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_qppm_reg structure is used to store the access register QPPM command parameters
 */
struct ku_access_qppm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qppm_reg      qppm_reg; /**< ku_qppm_reg - qppm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_slecr_reg structure is used to store the access register SLECR command parameters
 */
struct ku_access_slecr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_slecr_reg     slecr_reg; /**< ku_slecr_reg - slecr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_cwpp_reg structure is used to store the access
 * register cwpp command parameters
 */
struct ku_cwpp_reg {
    uint8_t              pool;
    struct ku_cw_profile profiles[REDECN_NUM_HW_PROFILES];
};

/**
 * ku_access_cwppm_reg structure is used to store the access
 * register cwppm command parameters
 */
struct ku_cwppm_reg {
    uint8_t pool;
    uint8_t tcp_g;
    uint8_t tcp_y;
    uint8_t tcp_r;
    uint8_t ntcp_g;
    uint8_t ntcp_y;
    uint8_t ntcp_r;
};

/**
 * ku_access_rgcr_reg structure is used to store the access
 * register RGCR command parameters
 */
struct ku_access_rgcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rgcr_reg      rgcr_reg; /**< rgcr_reg - rgcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_rtps_reg structure is used to store the access
 * register RGCR command parameters
 */
struct ku_access_rtps_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rtps_reg      rtps_reg; /**< rtps_reg - rtps register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_rtca_reg structure is used to store the access
 * register RTCA command parameters
 */
struct ku_access_rtca_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_rtca_reg      rtca_reg; /**< rtca_reg - rtca register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_ruft_reg structure is used to store the access
 * register RUFT command parameters
 */
struct ku_access_ruft_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ruft_reg      ruft_reg; /**< ruft_reg - ruft register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbhbr_reg structure is used to store the access
 * register sbhbr command parameters
 */
struct ku_sbhbr_reg {
    uint8_t  opcode;
    uint8_t  local_port;
    uint8_t  lp_msb;    /**< local_port msb */
    uint8_t  hist_id;
    uint16_t hist_type;
    uint32_t hist_parameters;
    uint32_t hist_max;
    uint32_t hist_min;
    uint8_t  sample_time;
};

/**
 * ku_access_sbhbr_reg structure is used to store the access
 * register SBHBR command parameters
 */
struct ku_access_sbhbr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbhbr_reg     sbhbr_reg;  /**< sbhbr_reg - sbhbr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbhrr_reg structure is used to store the access
 * register sbhrr command parameters
 */
struct ku_sbhrr_reg {
    uint8_t                              clr;
    uint8_t                              hist_id;
    uint64_t __attribute__((aligned(8))) bin[NUM_BINS_SBHRR];
};

/**
 * ku_access_sbhrr_reg structure is used to store the access
 * register SBHRR command parameters
 */
struct ku_access_sbhrr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbhrr_reg     sbhrr_reg;  /**< sbhrr_reg - sbhrr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbdcc_reg structure is used to store the access
 * register sbdcc command parameters
 */
struct ku_sbdcc_reg {
    uint8_t                              clr;
    uint64_t __attribute__((aligned(8))) ctr[NUM_COUNTERS_SBDCC];
};

/**
 * ku_access_sbdcc_reg structure is used to store the access
 * register SBDCC command parameters
 */
struct ku_access_sbdcc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbdcc_reg     sbdcc_reg;  /**< sbdcc_reg - sbdcc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbdcm_reg structure is used to store the access
 * register sbdcm command parameters
 */
struct ku_sbdcm_reg {
    uint8_t  ctr_set_type;
    uint32_t ctr_index;
};

/**
 * ku_access_sbdcm_reg structure is used to store the access
 * register SBDCM command parameters
 */
struct ku_access_sbdcm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbdcm_reg     sbdcm_reg;  /**< sbdcm_reg - sbdcm register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * sxd_sbctc_event_t enumerated type used in SBCTC register event field
 */
typedef enum sxd_sbctc_event {
    SXD_SBCTC_EVENT_NO_EVENT     = 0,
    SXD_SBCTC_EVENT_EVENTS       = 1,
    SXD_SBCTC_EVENT_SINGLE_EVENT = 2,
} sxd_sbctc_event_t;

/**
 * ku_sbctc_reg structure is used to store the access
 * register sbctc command parameters
 */
struct ku_sbctc_reg {
    uint8_t                              dir_ing;
    uint8_t                              local_port;
    uint8_t                              lp_msb;    /**< local_port msb */
    uint8_t                              res;
    uint8_t                              mode;
    uint8_t                              en_config;
    uint8_t                              event;
    uint64_t __attribute__((aligned(8))) tclass_en;
    uint32_t                             thr_max;
    uint32_t                             thr_min;
    uint8_t                              is_port_profile;
};

/**
 * ku_access_sbctc_reg structure is used to store the access
 * register SBCTC command parameters
 */
struct ku_access_sbctc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbctc_reg     sbctc_reg;  /**< sbctc_reg - sbctc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_ppbmi_reg structure is used to store the PPBMI register parameters
 */
struct ku_ppbmi_reg {
    uint32_t ilm_index;    /**< ilm_index - index of this entry in the KVD Linear */
    uint32_t nhlfe_index;  /**< nhlfe_index - NHLFE entry pointer */
    uint16_t ecmp_size;    /**< ecmp_size - the amount of sequential entries starting from the nhlfe_ptr */
    uint8_t  npop;         /**< npop - number of labels to pop from the label stack */
};

/**
 * ku_access_ppbmi_reg structure is used to store the access register PPBMI command parameters
 */
struct ku_access_ppbmi_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppbmi_reg     ppbmi_reg; /**< ku_ppbmi_reg - ppbmi register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_htac_reg_attr structure is used to store the access
 * register htac command parameters
 */
union  ku_htac_reg_attr {
    uint8_t  icmp_type; /**< used for ICMPV6_CONF_TYPE0/1 trap */
    uint16_t eth_type;  /**< used for NVE_DECAP_ET trap */
};

#define NUM_HTAC_TRAP_ATTR 2
/**
 * ku_htac_reg structure is used to store the access
 * register htac command parameters
 */
struct ku_htac_reg {
    uint16_t                trap_id;
    union  ku_htac_reg_attr attr[NUM_HTAC_TRAP_ATTR];
};

/**
 * ku_hopf_reg structure is used to store the access
 * register hopf command parameters
 */
struct ku_hopf_reg {
    uint8_t  sr; /**< send/receive */
    uint8_t  cqe_ver; /**< CQE version */
    uint32_t flow_number; /**< flow number */
    uint8_t  rcv_cpu_tclass; /**< receive CPU tclass */
    uint8_t  cpu_tclass; /**< CPU tclass */
    uint8_t  i_f; /**< OOB interface link */
    uint8_t  mac[6]; /**< MAC address */
    uint8_t  vlan_ex; /**< VLAN tag exists */
    uint8_t  dei; /**< DEI */
    uint8_t  pcp; /**< PCP */
    uint16_t vid; /**< VLAN ID */
};

/**
 * ku_access_htac_reg structure is used to store the access
 * register HTAC command parameters
 */
struct ku_access_htac_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_htac_reg      htac_reg; /**< htac_reg - htac register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_swid_config structure is used to store the swid attributes for the set profile command
 */
struct ku_swid_config {
    uint8_t           mask; /**< mask - Modify Switch Partition Configuration mask */
    enum ku_swid_type type; /**< type - Switch Partition type */
    uint8_t           properties; /**< properties - For IB switch partition bit 0 - IPoIB Router Port Enable */
};

#define SX_INDEPENDENT_MODULE_MASK ((uint64_t)(1ULL << 40)) /* Set bit 40 in profile mask - set module master */

/**
 * ku_profile structure is used to store the profile attributes for the set profile command
 */
struct ku_profile {
    uint8_t                              dev_id; /**< dev_id - device id */
    uint64_t __attribute__((aligned(8))) set_mask_0_63; /**< set_mask_0_63 - Capability bitmask for Set() command */
    uint64_t __attribute__((aligned(8))) set_mask_64_127; /**< set_mask_64_127 - Capability bitmask for Set() command */
    uint8_t                              max_vepa_channels; /**< max_vepa_channels - Maximum Number of VEPA Channels per port (0 through 16) */
    uint16_t                             max_lag; /**< max_lag - Maximum number of LAG IDs requested */
    uint16_t                             max_port_per_lag; /**< max_port_per_lag - Maximum number of ports per LAG requested */
    uint16_t                             max_mid; /**< max_mid - Maximum Multicast IDs Multicast IDs are allocated from 0 to max_mid-1 */
    uint16_t                             max_pgt; /**< max_pgt - Maximum records in the Port Group Table per Switch Partition */
    uint16_t                             max_system_port; /**< max_system_port - The maximum number of system ports that can be allocated */
    uint16_t                             max_active_vlans; /**< max_active_vlans - Maximum number of active VLANs */
    uint16_t                             max_regions; /**< max_regions - Maximum number of TCAM Regions */
    uint8_t                              max_flood_tables; /**< max_flood_tables - Maximum number of Flooding Tables. */
    uint8_t                              max_per_vid_flood_tables; /**< max_per_vid_flood_tables - Maximum number of Flooding Tables Per VID (A2 only in mixed mode ). */
    uint8_t                              flood_mode; /**< flood_mode - Flood Tables Mode: single, per vid, mixed (mixed supported in A2 only) */
    uint8_t                              max_fid_offset_flood_tables; /**< max_fid_offset_flood_tables - Maximum number of FID-Offset Flooding Tables */
    uint16_t                             fid_offset_table_size; /**< fid_offset_table_size - number of entries in each FID-Offset Flooding Table */
    uint8_t                              max_per_fid_flood_table; /**< max_per_fid_flood_table - Maximum number of FID Flooding Tables */
    uint16_t                             per_fid_table_size; /**< per_fid_table_size - Number of entries in each FID Flooding Table; */
    uint16_t                             max_fid; /**< max_fid - Maximum number of virtual FIDs */
    uint16_t                             max_ib_mc; /**< max_ib_mc - Maximum number of multicast FDB records for IB FDB (in 512 chunks) per IB Switch Partition */
    uint16_t                             max_pkey; /**< max_pkey - Maximum per port pkey table size (for pkey enforcement) */
    uint8_t                              hsba_status;  /**< Shared buffer hierarchical admission status */
    uint8_t                              ar_sec; /**< ar_sec - Primary / Secondary Capability */
    uint16_t                             adaptive_routing_group_cap; /**< adaptive_routing_group_cap - Adaptive Routing Group Capability */
    uint8_t                              arn; /**< arn - Adaptive Routing Notification Enable */
    uint8_t                              lag_mode; /**< Who manages PGT LAG Table. '0' - FW; '1' - SW (rm_lag_table_mngr_e)*/
    uint32_t                             kvd_linear_size; /**The size of KVD linear*/
    uint32_t                             kvd_hash_single_size; /**The size of KVD hash single*/
    uint32_t                             kvd_hash_double_size; /**The size of KVD hash single*/
    struct ku_swid_config                swid0_config_type; /**< swid0_config_type - Configuration for Switch Partition 0 */
    struct ku_swid_config                swid1_config_type; /**< swid1_config_type - Configuration for Switch Partition 1 */
    struct ku_swid_config                swid2_config_type; /**< swid2_config_type - Configuration for Switch Partition 2 */
    struct ku_swid_config                swid3_config_type; /**< swid3_config_type - Configuration for Switch Partition 3 */
    struct ku_swid_config                swid4_config_type; /**< swid4_config_type - Configuration for Switch Partition 4 */
    struct ku_swid_config                swid5_config_type; /**< swid5_config_type - Configuration for Switch Partition 5 */
    struct ku_swid_config                swid6_config_type; /**< swid6_config_type - Configuration for Switch Partition 6 */
    struct ku_swid_config                swid7_config_type; /**< swid7_config_type - Configuration for Switch Partition 7 */
    uint8_t                              ib_router_en; /**< IB router enable */
    uint8_t                              ib_router_ecmp; /**< IB Router ecmp */
    uint8_t                              ib_router_mcf; /**< IB Router multicast filter */
    uint16_t                             ib_router_ecmp_lid_range; /**< IB router ECMP LID range */
    uint32_t                             reserved1; /**< reserved1 */
    uint8_t                              ubridge_mode; /**< Use is deprecated. Always equal to 1. */
    uint8_t                              umlabel;   /**< user mirror label port */
    uint8_t                              port_profile_num;  /**< Number of port profiles */

    /* this array will contain supported revisions per type */
    uint64_t __attribute__((aligned(8))) sup_revs_by_type[SXD_CHIP_TYPES_MAX_ISSU];
    enum sxd_chip_types                  chip_type;
    uint8_t                              do_not_config_profile_to_device;
    uint8_t                              split_ready; /**< split_ready - Support split ports */
    uint8_t                              module_master_fw_default; /**< Module Master FW Default. 0 - FW control, 1 - SW control */
};

/**
 * ku_profile structure is used to store the kvh configuration parameters
 */
struct profile_kvh_params {
    uint8_t kvh_xlt_cache_mode;
};

/**
 * ku_swid_details is used to store the swid details for the enable/disable swid ioctls
 */
struct ku_swid_details {
    uint8_t                              dev_id; /**< dev_id - device id */
    uint8_t                              swid; /**< swid - swid (0-7, or 255=Don't care) */
    uint16_t                             iptrap_synd; /**< iptrap_synd - syndrome for the IPTRAPs */
    uint64_t __attribute__((aligned(8))) mac;     /**< mac - MAC address of the device */
};

/**
 * ku_trap_filter_data is used to store the data of the trap_filter change ioctl
 */
struct ku_trap_filter_data {
    uint16_t trap_id;    /**< trap_id - trap ID to filter on */
    uint8_t  is_lag;    /**< is_lag - is the port a lag port */
    uint16_t sysport;    /**< sysport - system port (valid if is_lag == 0) */
    uint16_t lag_id;    /**< lag_id - LAG ID (valid if is_lag == 1) */
};

/**
 * ku_default_vid_data is used to store the data of the default vid change ioctl
 */
struct ku_default_vid_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint8_t  is_lag;    /**< is_lag - is the vid belongs to a lag */
    uint16_t sysport;    /**< sysport - system port (valid if is_lag == 0) */
    uint16_t lag_id;    /**< lag_id - LAG ID (valid if is_lag == 1) */
    uint16_t default_vid;    /**< default_vid - the new default VLAN ID of the port/lag */
};

#ifdef SW_PUDE_EMULATION /* PUDE WA for NOS (PUDE events are handled by SDK). Needed for BU. */
/**
 * ku_admin_status_data is used to store the data of the port
 * admin status ioctl
 */
struct ku_admin_status_data {
    uint8_t  dev_id;       /**< dev_id - device id */
    uint16_t sysport;      /**< sysport - system port */
    uint8_t  admin_status; /**< admin_status - port admin status */
};
#endif /* SW_PUDE_EMULATION */

/**
 * ku_default_vid_data is used to store the data of the default vid change ioctl
 */
struct ku_vid_membership_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint8_t  is_lag;    /**< is_lag - is the vid belongs to a lag */
    uint16_t phy_port;    /**< phy_port - physical port (valid if is_lag == 0) */
    uint16_t lag_id;    /**< lag_id - LAG ID (valid if is_lag == 1) */
    uint16_t vid;    /**< vid - the new default VLAN ID of the port/lag */
    uint8_t  is_tagged;    /**< is_lag - is the vid belongs to a lag */
};

/**
 * ku_default_vid_data is used to store the data of the default vid change ioctl
 */
struct ku_prio_tagging_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint8_t  is_lag;    /**< is_lag - is the vid belongs to a lag */
    uint16_t phy_port;    /**< phy_port - physical port (valid if is_lag == 0) */
    uint16_t lag_id;    /**< lag_id - LAG ID (valid if is_lag == 1) */
    uint8_t  is_prio_tagged;    /**< is_lag - is the vid belongs to a lag */
};

/**
 * ku_default_vid_data is used to store the data of the default vid change ioctl
 */
struct ku_prio_to_tc_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint8_t  is_lag;    /**< is_lag - is the vid belongs to a lag */
    uint16_t phy_port;    /**< phy_port - physical port (valid if is_lag == 0) */
    uint16_t lag_id;    /**< lag_id - LAG ID (valid if is_lag == 1) */
    uint8_t  priority;
    uint8_t  traffic_class;
};

/**
 * ku_port_swid_data is used to store the data of the port swid change ioctl
 */
struct ku_local_port_swid_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint16_t local_port;    /**<  local port - system port (valid if is_lag == 0) */
    uint16_t swid;    /**< swid - the new SWID of the port/lag */
};

/**
 * ku_ib_local_port_data is used to store the data of the port swid change ioctl
 */
struct ku_ib_local_port_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint16_t local_port;    /**<  local port - system port (valid if is_lag == 0) */
    uint16_t ib_port;    /**< ib_port - IB port  */
};

/**
 * ku_system_local_port_data is used to store the data of the port swid change ioctl
 */
struct ku_system_local_port_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint16_t local_port;    /**<  local port - local port (valid if is_lag == 0) */
    uint16_t system_port;    /**< system_port - system port  */
};

/**
 * ku_default_vid_data is used to store the data of the default vid change ioctl
 */
struct ku_port_rp_mode_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint8_t  is_lag;    /**< is_lag - is the vid belongs to a lag */
    uint16_t sysport;    /**< sysport - system port (valid if is_lag == 0) */
    uint16_t vlan_id;    /**< lan id  */
    uint16_t lag_id;    /**< lag_id - LAG ID (valid if is_lag == 1) */
    uint8_t  is_rp;    /**< is_rp - is valid rif */
    uint8_t  is_valid; /**< is_valid - create=1 / delete=0 rif */
    uint16_t rif_id;    /**< rif_id - RIF ID */
    uint16_t hw_efid;   /**< hw_efid - egress FID */
};

/**
 * ku_port_vlan_to_fid_map_data is used to store the data of the port,vlan mapping ioctl
 */
struct ku_port_vlan_to_fid_map_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint16_t local_port;     /**< port - local port */
    uint16_t vid;     /**< vid - vlan id  */
    uint8_t  is_mapped_to_fid;    /**< is_mapped_to_fid  */
    uint16_t fid;     /**< fid - bridge id */
};

/**
 * ku_fid_to_hwfid_map_data is used to store the data of the fid to hw_fid mapping
 */
struct ku_fid_to_hwfid_map_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint16_t fid;       /**< fid - user fid (vlan/bridge id) */
    uint16_t hw_fid;    /**< hw_fid - relevant hw_fid  */
};
struct ku_sgmii_system_cfg {
    char              netdev_name[SX_IFNAMSIZ];
    uint8_t           netdev_mac[6];
    ku_chassis_type_t chassis_type;
    ku_mgmt_board_t   mgmt_board;
    uint8_t           cqe_ver;
};

/**
 * ku_sgmii_init_dev is used to init SGMII device
 */
struct ku_sgmii_init_dev {
    uint8_t dev_id;
    uint8_t init_hopf;
};

/**
 * ku_sgmii_default_dev is used to set SGMII default device
 */
struct ku_sgmii_default_dev {
    uint8_t       dev_id;
    sxd_boolean_t hopf_on_remote_mgmt;
};


/**
 * ku_get_counters is used to get the drivers counters (per trap_id)
 */
struct ku_get_counters {
    /* global counters */
    uint64_t __attribute__((aligned(8))) fromcpu_data_packet;              /**< number of data packets sent from CPU    */
    uint64_t __attribute__((aligned(8))) fromcpu_data_byte;                /**< number of data bytes sent from CPU      */
    uint64_t __attribute__((aligned(8))) fromcpu_control_packet;           /**< number of control packets sent from CPU */
    uint64_t __attribute__((aligned(8))) fromcpu_control_byte;             /**< number of control bytes sent from CPU   */

    /* per-trap_id counter */
    uint64_t __attribute__((aligned(8))) trap_id_packet[NUM_HW_SYNDROMES]; /**< number of packet received for a trap_id */
    uint64_t __attribute__((aligned(8))) trap_id_byte[NUM_HW_SYNDROMES];   /**< number of bytes received for a trap_id  */
    uint64_t __attribute__((aligned(8))) trap_id_events[NUM_HW_SYNDROMES]; /**< number of events received for a trap_id */
    uint64_t __attribute__((aligned(8))) trap_id_drops[NUM_HW_SYNDROMES]; /**< number of drops for a trap_id */


    /* per-rdq counter */
    uint64_t __attribute__((aligned(8))) trap_group_packet[NUMBER_OF_RDQS]; /**< number of packet received for a trap group */
    uint64_t __attribute__((aligned(8))) trap_group_byte[NUMBER_OF_RDQS];   /**< number of bytes received for a trap group  */
};


/**
 * ku_ptp_mode - events/polling
 */

typedef enum {
    KU_PTP_MODE_DISABLED,
    KU_PTP_MODE_EVENTS,
    KU_PTP_MODE_POLLING
} ptp_mode_t;

struct ku_ptp_mode {
    ptp_mode_t ptp_mode;
};


/**
 * ku_default_vid_data is used to store the data of the default vid change ioctl
 */
struct ku_local_port_to_lag_data {
    uint8_t  dev_id;    /**< dev_id - device id */
    uint8_t  is_lag;    /**< is_lag - is the vid belongs to a lag */
    uint16_t local_port;    /**< sysport - system port (valid if is_lag == 0) */
    uint16_t lag_id;    /**< lag_id - LAG ID (valid if is_lag == 1) */
    uint16_t lag_port_index;    /**< lag_id - LAG ID (valid if is_lag == 1) */
};


/**
 * ku_lag_oper_state_data is used to store the data of lag operating state update ioctl
 */
struct ku_lag_oper_state_data {
    uint16_t lag_id;     /**< lag_id - LAG ID */
    uint8_t  oper_state; /**< oper_state - up=1 / down=0 */
};

/**
 *  ku_ber_monitor_state_data is used to store the data of port ber monitor state update ioctl
 */
struct ku_ber_monitor_state_data {
    uint8_t  dev_id;
    uint16_t local_port;
    uint8_t  ber_monitor_state;
};

/**
 * ku_ber_monitor_bitmask_data is used to store the data of port ber monitor bitmask update ioctl
 */
struct ku_ber_monitor_bitmask_data {
    uint8_t  dev_id;
    uint16_t local_port;
    uint8_t  bitmask;
};

/**
 * ku_tele_threshold_data is used to store the data of telemetry threshold set ioctl
 */
struct ku_tele_threshold_data {
    uint16_t                             local_port;
    uint8_t                              dir_ing;
    uint64_t __attribute__((aligned(8))) tc_vec;
};

/**
 * ku_access_mhsr_reg structure is used to store the access register MHSR command parameters
 */
struct ku_access_mhsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mhsr_reg      mhsr_reg; /**< mhsr_reg - mhsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_vid2ip_data is used to store the data of the default vid change ioctl
 */
struct ku_vid2ip_data {
    uint16_t vid;       /**< vid - the new default VLAN ID of the port/lag */
    uint32_t ip_addr;
    uint8_t  valid;     /**< valid bit which define if valid */
};

/**
 * ku_sdk_health_event_control is sued to enable/disable sdk_health_event per device id
 */
struct ku_sdk_health_event_control {
    uint8_t       dev_id;         /**< Device ID */
    sxd_boolean_t enable;             /**< TRUE - enable sdk_health_event; FALSE - disable sdk_health_event */
    sxd_boolean_t get_and_disable;    /**< TRUE - disable sdk_health_event after getting status; FALSE- no change in status after get. Valid for GET */
};


/**
 * sxd_tunnel_flc_type_t enumerated flow label copy type.
 */
typedef enum sxd_tunnel_flc_type {
    SXD_TUNNEL_FLC_CALCULATE     = 0,
    SXD_TUNNEL_FLC_COPY_FROM_PKT = 1
} sxd_tunnel_flc_type_t;

/**
 * sxd_tunnel_flc_type_t enumerated tigcr flow label type.
 */
typedef enum sxd_tunnel_flh_type {
    SXD_TUNNEL_FLH_NO_LABEL  = 0,
    SXD_TUNNEL_FLH_CALCULATE = 1
} sxd_tunnel_flh_type_t;

/**
 * sxd_tunnel_sport_type_t enumerated udp sport type.
 */
typedef enum sxd_tunnel_sport_type {
    SXD_TUNNEL_SPORT_SET_FIX_BITS_E          = 0,
    SXD_TUNNEL_SPORT_USE_HASH_TO_CALCULATE_E = 1,
} sxd_tunnel_sport_type_t;

/**
 * sxd_tca_log_pstate_type_t enumerated type is used to indicates the TCA logical port state type
 */
typedef enum sxd_tunnel_nve_type {
    SXD_TUNNEL_NVE_VXLAN     = 0,
    SXD_TUNNEL_NVE_VXLAN_GPE = 1,
    SXD_TUNNEL_NVE_GENEVE    = 2,
    SXD_TUNNEL_NVE_NVGRE     = 3,
} sxd_tunnel_nve_type_t;


/**
 * sxd_tunnel_enc_set_dscp_t structure enumerates types how to set DSCP field for encapsulation
 */
typedef enum sxd_tunnel_enc_set_dscp {
    SXD_TUNNEL_ENC_DSCP_COPY = 0,
    SXD_TUNNEL_ENC_DSCP_SET  = 1
} sxd_tunnel_enc_set_dscp_t;

/**
 * sxd_tunnel_enc_set_sp_t structure enumerated types how to set Switch prio and color for encapsulation
 */
typedef enum sxd_tunnel_enc_set_sp {
    SXD_TUNNEL_ENC_SP_PRESERVE = 0,
    SXD_TUNNEL_ENC_SP_SET      = 1
} sxd_tunnel_enc_set_sp_t;

/**
 * sxd_tunnel_dec_set_dscp_t structure enumerates types how to set overlay DSCP field
 */
typedef enum sxd_tunnel_dec_set_dscp {
    SXD_TUNNEL_DEC_DSCP_PRESERVE = 0,
    SXD_TUNNEL_DEC_DSCP_COPY     = 1
} sxd_tunnel_dec_set_dscp_t;

/**
 * sxd_tunnel_dec_set_sp_t structure enumerated types how to set Switch prio and color for decapsulation
 */
typedef enum sxd_tunnel_dec_set_sp {
    SXD_TUNNEL_DEC_SP_PRESERVE = 0,
    SXD_TUNNEL_DEC_SP_SET      = 1
} sxd_tunnel_dec_set_sp_t;

/**
 * sxd_tunnel_dec_set_pcp_t structure enumerated types how to set the overlay PCP, DEI for decapsulation
 */
typedef enum sxd_tunnel_dec_set_pcp {
    SXD_TUNNEL_DEC_PCP_PRESERVE = 0,
    SXD_TUNNEL_DEC_PCP_COPY     = 1
} sxd_tunnel_dec_set_pcp_t;

/**
 * sxd_tunnel_enc_dscp_rw_t structure enumerates types how to handle DSCP rewrite
 */
typedef enum sxd_tunnel_dscp_rw {
    SXD_TUNNEL_DSCP_RW_PRESERVE = 0,
    SXD_TUNNEL_DSCP_RW_CLEAR    = 2,
    SXD_TUNNEL_DSCP_RW_SET      = 3
} sxd_tunnel_dscp_rw_t;

/**
 * sxd_tunnel_enc_pcp_rw_t structure enumerates types how to handle pcp rewrite
 */
typedef enum sxd_tunnel_pcp_rw {
    SXD_TUNNEL_PCP_RW_PRESERVE = 0,
    SXD_TUNNEL_PCP_RW_CLEAR    = 2,
    SXD_TUNNEL_PCP_RW_SET      = 3
} sxd_tunnel_pcp_rw_t;

/**
 * sxd_rm_duplication_table_type enumerated type is used to list
 * a supported logical table types for the entry duplications in
 * the KVD
 */
typedef enum sxd_rm_duplication_table_type {
    SXD_RM_DUPLICATION_TABLE_TYPE_INVALID_E = 0x00,
    /* HASH-BASED */
    SXD_RM_DUPLICATION_TABLE_TYPE_VID_TO_FID_E        = 0x01,
    SXD_RM_DUPLICATION_TABLE_TYPE_RQ_VID_TO_FID_E     = 0x02,
    SXD_RM_DUPLICATION_TABLE_TYPE_FID_E               = 0x03,
    SXD_RM_DUPLICATION_TABLE_TYPE_NVI_TO_FID_E        = 0x04,
    SXD_RM_DUPLICATION_TABLE_TYPE_MAC_L2_FORWARDING_E = 0x05,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV4_LPM_HIGH_E     = 0x06,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV4_LPM_LOW_E      = 0x07,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV4_LPM_LPM0_E     = 0x08,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_LPM_HIGH_E     = 0x09,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_LPM_LOW_E      = 0x0A,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_LPM_LPM0_E     = 0x0B,
    SXD_RM_DUPLICATION_TABLE_TYPE_MPLS_ILM_E          = 0x0C,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV4_HOST_TABLE_E   = 0x0D,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_HOST_TABLE_E   = 0x0E,
    SXD_RM_DUPLICATION_TABLE_TYPE_TUNNEL_IPV6_LEARN_E = 0x0F,
    SXD_RM_DUPLICATION_TABLE_TYPE_A_TCAM_1_KEY_E      = 0x10,
    SXD_RM_DUPLICATION_TABLE_TYPE_A_TCAM_2_KEY_E      = 0x11,
    SXD_RM_DUPLICATION_TABLE_TYPE_A_TCAM_4_KEY_E      = 0x12,
    SXD_RM_DUPLICATION_TABLE_TYPE_A_TCAM_6_KEY_E      = 0x13,

    /* linear */
    SXD_RM_DUPLICATION_TABLE_TYPE_ADJACENCY_E                = 0x21,
    SXD_RM_DUPLICATION_TABLE_TYPE_NVE_DECAP_E                = SXD_RM_DUPLICATION_TABLE_TYPE_ADJACENCY_E,
    SXD_RM_DUPLICATION_TABLE_TYPE_IP_IN_IP_DECAP_E           = SXD_RM_DUPLICATION_TABLE_TYPE_ADJACENCY_E,
    SXD_RM_DUPLICATION_TABLE_TYPE_MPLS_NHLFE_E               = 0x22,
    SXD_RM_DUPLICATION_TABLE_TYPE_ACL_ACTION_SET_EXTENSION_E = 0x23,
    SXD_RM_DUPLICATION_TABLE_TYPE_POLICY_BASED_SWITCHING_E   = 0x24,
    SXD_RM_DUPLICATION_TABLE_TYPE_POLICY_BASED_MPLS_ILM_E    = 0x25,
    SXD_RM_DUPLICATION_TABLE_TYPE_MC_ROUTER_INTF_GROUP_E     = 0x26,
    SXD_RM_DUPLICATION_TABLE_TYPE_MC_EXPECTED_IRIF_LIST_E    = 0x27,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_IP_ADDRESS_E          = 0x28,
    SXD_RM_DUPLICATION_TABLE_TYPE_TUNNEL_UNDERLAY_MC_E       = 0x29
} sxd_rm_duplication_table_type_e;

/**
 * sxd_tunnel_tigcr_ttlc enumerated tigcr ttlc type.
 */
typedef enum sxd_tunnel_tigcr_ttlc {
    SXD_TIGCR_TTLC_USE_CONFIG    = 0,
    SXD_TIGCR_TTLC_COPY_FROM_PKT = 1
} sxd_tunnel_tigcr_ttlc_t;

/**
 * sxd_tunnel_tngcr_ttlc enumerated TNGCR nve_ttlc type.
 */
typedef enum sxd_tunnel_tngcr_ttlc {
    SXD_TNGCR_TTLC_USE_CONFIG    = 0,
    SXD_TNGCR_TTLC_COPY_FROM_PKT = 1
} sxd_tunnel_tngcr_ttlc_t;

/**
 * sxd_tunnel_tngcr_ttlc enumerated TNGCR nve_decap_ttl type.
 */
typedef enum sxd_tunnel_tngcr_decap_ttl {
    SXD_TNGCR_NVE_DECAP_TTL_PRESERVE_E = 0,
    SXD_TNGCR_NVE_DECAP_TTL_COPY_E     = 1,
    SXD_TNGCR_NVE_DECAP_TTL_MINIMUM_E  = 2
} sxd_tunnel_tngcr_nve_decap_ttl_t;

/**
 * ku_vrpa_details is used to store the vrpa details for the vrpa create ioctls
 */
struct ku_vrpa_details {
    uint8_t  dev_id;    /**< dev_id - device id */
    int      num_of_ports;
    uint16_t max_pkey;
    uint8_t  swid[NUMBER_OF_SWIDS];
    uint16_t synd;    /**< iptrap_synd - syndrome for the VRPA */
};


typedef enum {
    PORT_ACCESS_TYPE_LOCAL_E = 0,
    PORT_ACCESS_TYPE_LABEL_E = 1,
    PORT_ACCESS_TYPE_PCI_E   = 2,
    PORT_ACCESS_TYPE_LAST_E
} port_access_type_t;

enum {
    SX_EVENT_LIST_SIZE = 2000,
    ISX_HDR_SIZE       = 16,

    /* SPC1 and SX support up to 10K packets    */
    SX_ETH_RDQ_MAX_MSG_SIZE_LEGACY = 10 * 1024,

    /* SPC2 and later support up to 12K packets */
    SX_ETH_RDQ_MAX_MSG_SIZE_SPC2 = 12 * 1024,

    /* Maximum of all ETH_RDQ_MSG_SIZE maximums (for static allocations) */
    SX_ETH_RDQ_MAX_MSG_SIZE = SX_ETH_RDQ_MAX_MSG_SIZE_SPC2
};

typedef enum {
    STATUS_OPCODE_NO_ISSUE                                       = 0,
    STATUS_OPCODE_PORT_IS_CLOSE_BY_COMMAND                       = 1,
    STATUS_OPCODE_AN_NO_PARTNER_DETECTED                         = 2,
    STATUS_OPCODE_AN_ACK_NOT_RECEIVED                            = 3,
    STATUS_OPCODE_AN_NEXT_PAGE_EXCHANGE_FAILED                   = 4,
    STATUS_OPCODE_KR_FRAME_LOCK_NOT_ACQUIREED                    = 5,
    STATUS_OPCODE_KR_LINK_INHIBIT_TIMEOUT                        = 6,
    STATUS_OPCODE_KR_LINK_PARTNER_DIDNT_SET_RECEIVER_READY       = 7,
    STATUS_OPCODE_KR_TUNING_DIDNT_COMPLETE                       = 8,
    STATUS_OPCODE_PCS_DIDNT_ACQUIRE_BLOCK_LOCK                   = 9,
    STATUS_OPCODE_PCS_DIDNT_ACQUIRE_AM_LOCK                      = 10,
    STATUS_OPCODE_PCS_DIDNT_GET_ALIGN_STATUS                     = 11,
    STATUS_OPCODE_FC_FEC_ISNT_LOCKED                             = 12,
    STATUS_OPCODE_RS_FEC_ISNT_LOCKED                             = 13,
    STATUS_OPCODE_REMOTE_FAULT_RECEIVED                          = 14,
    STATUS_OPCODE_BAD_SIGNAL_INTEGRITY                           = 15,
    STATUS_OPCODE_CABLE_COMPLIANCE_CODE_MISMATCH                 = 16,
    STATUS_OPCODE_LARGE_NUMBER_OF_PHYSICAL_ERRORS                = 17,
    STATUS_OPCODE_STAMPING_OF_NON_MELLANOX_CABLE_MODULE          = 20,
    STATUS_OPCODE_CALIBRATION_FAILURE                            = 23,
    STATUS_OPCODE_EDR_STAMPING                                   = 24,
    STATUS_OPCODE_FDR10_STAMPING                                 = 25,
    STATUS_OPCODE_ETHERNET_COMPLIANCE_CODE_ZERO                  = 26,
    STATUS_OPCODE_56GE_STAMPING                                  = 27,
    STATUS_OPCODE_NON_MELLANOX_QSFP28                            = 28,
    STATUS_OPCODE_NON_MELLANOX_SFP28                             = 29,
    STATUS_OPCODE_NO_BACKPLANE_ENABLED                           = 30,
    STATUS_OPCODE_NO_PASSIVE_PROTOCOL_ENABLED                    = 31,
    STATUS_OPCODE_NO_ACTIVE_PROTOCOL_ENABLED                     = 32,
    STATUS_OPCODE_NO_PARTNER_DETECTED_DURING_FORCE_MODE          = 36,
    STATUS_OPCODE_PARTIAL_LINK_INDICATION_DURING_FORCE_MODE      = 37,
    STATUS_OPCODE_AN_FEC_MISMATCH_DURING_OVERRIDE                = 38,
    STATUS_OPCODE_AN_NO_HCD                                      = 39,
    STATUS_OPCODE_BAD_SI_CABLE_IS_CONFIGURED_TO_NON_OPTIMAL_RATE = 42,
    STATUS_OPCODE_INFO_NOT_AVAILABLE                             = 1023,
    STATUS_OPCODE_CABLE_IS_UNPLUGGED                             = 1024,
    STATUS_OPCODE_LONG_RANGE_FOR_NON_MLNX_CABLE                  = 1025,
    STATUS_OPCODE_BUS_STUCK                                      = 1026,
    STATUS_OPCODE_BAD_EEPROM                                     = 1027,
    STATUS_OPCODE_PART_NUMBER_LIST                               = 1028,
    STATUS_OPCODE_UNSUPPORTED_CABLE                              = 1029,
    STATUS_OPCODE_MODULE_TEMP_SHUTDOWN                           = 1030,
    STATUS_OPCODE_SHORTED_CABLE                                  = 1031,
    STATUS_OPCODE_POWER_BUDGET_EXCEEDED                          = 1032,
    STATUS_OPCODE_MGMT_FORCED_DOWN_THE_PORT                      = 1033,
    STATUS_OPCODE_MODULE_DISABLED_BY_COMMAND                     = 1034,
    STATUS_OPCODE_MODULE_PMD_TYPE_IS_NOT_ENABLED                 = 1036
} status_opcode_t;


/**
 * ku_mtpppc_reg structure is used to store the access
 * register MTPPPC command parameters
 */
struct ku_mtpppc_reg {
    uint8_t  we;
    uint16_t ing_timestape_message_type;
    uint16_t egr_timestape_message_type;
    uint8_t  gm_local_port_0;
    uint8_t  gm_local_port_1;
};


/**
 * MTPPTR timestamp record for ku_mtpptr_reg structure
 */
struct mtpptr_record {
    uint16_t reserved1;
    uint8_t  message_type;
    uint8_t  domain_number;
    uint16_t reserved2;
    uint16_t sequence_id;
    uint64_t timestamp;
} __attribute__((packed));

/**
 * ku_mtpptr_reg structure is used to store the access
 * register MTPPTR command parameters
 */
struct ku_mtpptr_reg {
    uint8_t              local_port;
    uint8_t              lp_msb;    /**< local_port msb */
    uint8_t              dir;
    uint8_t              clr;
    uint8_t              read_one;
    uint8_t              ovf;
    uint8_t              num_record;
    struct mtpptr_record records[4];
};

/**
 * ku_mtptpt_reg structure is used to store the access
 * register MTPTPT command parameters
 */
struct ku_mtptpt_reg {
    uint8_t  trap_id;
    uint16_t message_type;
};


/**
 * ku_access_mtpppc_reg structure is used to store the access
 * register MTPPPC command parameters
 */
struct ku_access_mtpppc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtpppc_reg    mtpppc_reg; /**< mtpppc_reg - mtpppc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_mtptpt_reg structure is used to store the access
 * register MTPTPT command parameters
 */
struct ku_access_mtptpt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtptpt_reg    mtptpt_reg; /**< mtptpt_reg - mtptpt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


/**
 * ku_access_mtpptr_reg structure is used to store the access
 * register MTPPTR command parameters
 */
struct ku_access_mtpptr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtpptr_reg    mtpptr_reg; /**< mtpptr_reg - mtptpt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

struct ppbmp_monitor_params {
    uint8_t alarm_th_mantissa;
    uint8_t alarm_th_exp;
    uint8_t warning_th_mantissa;
    uint8_t warning_th_exp;
    uint8_t normal_th_mantissa;
    uint8_t normal_th_exp;
};

/**
 * ku_ppbmp_reg structure is used to store the access
 * register PPBMP command parameters
 */
struct ku_ppbmp_reg {
    uint8_t                     local_port;
    uint8_t                     lp_msb;    /**< local_port msb */
    uint8_t                     pnat;
    uint8_t                     monitor_group;
    struct ppbmp_monitor_params monitor_params;
};

/**
 * ku_access_ppbmp_reg structure is used to store the access
 * register PPBMP command parameters
 */
struct ku_access_ppbmp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppbmp_reg     ppbmp_reg; /**< ppbmp_reg - ppbmp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

typedef enum ku_ppbmp_monitor_type {
    KU_PPBMP_MONITOR_GROUP_RS_PRE_FEC_E     = 0, /**< Pre RS FEC */
    KU_PPBMP_MONITOR_GROUP_FC_PRE_FEC_E     = 1, /**< Pre FC FEC */
    KU_PPBMP_MONITOR_GROUP_NO_FEC_PRE_FEC_E = 2, /**< No FEC/Post FEC */
} ku_ppbmp_monitor_type_e;

/**
 * ku_ppbmc_reg structure is used to store the access
 * register PPBMC command parameters
 */
struct ku_ppbmc_reg {
    uint8_t local_port;
    uint8_t lp_msb;    /**< local_port msb */
    uint8_t pnat;
    uint8_t monitor_type;
    uint8_t event_ctrl;
    uint8_t e;
    uint8_t monitor_ctrl;
    uint8_t monitor_state;
};

/**
 * ku_access_ppbmc_reg structure is used to store the access
 * register PPBMC command parameters
 */
struct ku_access_ppbmc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppbmc_reg     ppbmc_reg; /**< ppbmc_reg - ppbmc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_ppbme_reg structure is used to store the access
 * register PPBME command parameters
 */
struct ku_ppbme_reg {
    uint8_t local_port;
    uint8_t lp_msb;    /**< local_port msb */
    uint8_t pnat;
    uint8_t monitor_type;
    uint8_t monitor_state;
};

/**
 * ku_access_ppbme_reg structure is used to store the access
 * register PPBME command parameters
 */
struct ku_access_ppbme_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppbme_reg     ppbme_reg; /**< ppbme_reg - ppbme register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_perpt_reg structure is used to store the access
 * register PERPT command parameters
 */
struct ku_perpt_reg {
    uint8_t  erpt_bank;
    uint8_t  erpt_index;
    uint8_t  key_size;
    uint8_t  bf_bypass;
    uint8_t  erp_id;
    uint8_t  erpt_base_bank;
    uint8_t  erpt_base_index;
    uint8_t  erp_index_in_vector;
    uint16_t erp_vector;
    uint8_t  mask[SXD_ACL_FLEX_KEY_BLOCK_SIZE_BYTES];
};

/**
 * ku_percr_reg structure is used to store the access
 * register PERCR command parameters
 */
struct ku_percr_reg {
    uint16_t region_id;
    uint8_t  atcam_ignore_prune;
    uint8_t  ctcam_ignore_prune;
    uint8_t  bf_bypass;
    uint8_t  master_mask[SXD_ACL_FLEX_KEY_BLOCK_SIZE_BYTES];
};

/**
 * ku_pererp_reg structure is used to store the access
 * register PERERP command parameters
 */
struct ku_pererp_reg {
    uint16_t region_id;
    uint8_t  ctcam_le;
    uint8_t  erpt_pointer_valid;
    uint8_t  ctcam_only;
    uint8_t  erpt_bank_pointer;
    uint8_t  erpt_pointer;
    uint16_t erpt_vector;
    uint8_t  master_rp_id;
};

/**
 * ku_access_perpt_reg structure is used to store the access
 * register perpt command parameters
 */
struct ku_access_perpt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_perpt_reg     perpt_reg; /**< perpt_reg - perpt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_percr_reg structure is used to store the access
 * register percr command parameters
 */
struct ku_access_percr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_percr_reg     percr_reg; /**< percr_reg - percr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pererp_reg structure is used to store the access
 * register pererp command parameters
 */
struct ku_access_pererp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_percr_reg     pererp_reg; /**< pererp_reg - pererp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_qpsc_reg structure is used to store the access
 * register QPSC command parameters
 */
struct ku_qpsc_reg {
    uint8_t  port_speed;
    uint8_t  time_exp;
    uint8_t  time_mantissa;
    uint8_t  shaper_inc;
    uint8_t  shaper_bs;
    uint8_t  ptsc_we;
    uint8_t  port_to_shaper_credits;
    uint32_t ing_timestamp_inc;
    uint32_t egr_timestamp_inc;
};

/**
 * ku_access_qpsc_reg structure is used to store the access
 * register QPSC command parameters
 */
struct ku_access_qpsc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qpsc_reg      qpsc_reg; /**< qpsc_reg - qpsc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * PEABFE Bloom Filter Entry Layout  for ku_peabfe_reg structure
 */
struct peabfe_bf_entry {
    uint8_t  state;
    uint8_t  bf_bank;
    uint32_t bf_index;
};

/**
 * ku_peabfe_reg structure is used to store the access
 * register PEABFE command parameters
 */
struct ku_peabfe_reg {
    uint16_t               size;
    struct peabfe_bf_entry bf_entry[SXD_ACL_BLOOM_FILTER_ENTRIES];
};

/**
 * ku_access_peabfe_reg structure is used to store the access
 * register peabfe command parameters
 */
struct ku_access_peabfe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_peabfe_reg    peabfe_reg; /**< peabfe_reg - peabfe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


/**
 * ku_moni_reg structure is used to store the access
 * register MONI command parameters
 */
struct ku_moni_reg {
    uint8_t local_port;     /**< local_port - local port number */
    uint8_t lp_msb;         /**< local_port msb */
    uint8_t en;             /**< en - enable monitoring on network interface */
};

struct ku_access_moni_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_moni_reg      moni_reg; /**< moni_reg - moni register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * sx_mtutc_op enumerated type is used to note the possible
 * mtutc OPs.
 */
typedef enum sx_mtutc_op {
    SX_MTUTC_OP_SET_TIME_NEXT_SEC_E  = SXD_MTUTC_OP_SET_TIME_NEXT_SEC,
    SX_MTUTC_OP_SET_TIME_IMMEDIATE_E = SXD_MTUTC_OP_SET_TIME_IMMEDIATE,
    SX_MTUTC_OP_ADJUST_TIME_E        = SXD_MTUTC_OP_ADJUST_TIME,
    SX_MTUTC_OP_ADJUST_FREQ_E        = SXD_MTUTC_OP_ADJUST_FREQ,
} sx_mtutc_op_e;

/**
 * ku_dpt_info is used to store the DPT info.
 */
struct ku_dpt_info {
    enum ku_dpt_path_type    cmd_path;
    enum ku_dpt_path_type    emad_path;
    enum ku_dpt_path_type    mad_path;
    enum ku_dpt_path_type    cr_access_path;
    uint8_t                  is_ifc_valid[DPT_PATH_MAX + 1];
    uint8_t                  is_local[DPT_PATH_MAX + 1];
    struct ku_dpt_i2c_info   sx_i2c_info;
    struct ku_dpt_pcie_info  sx_pcie_info;
    struct ku_dpt_sgmii_info sx_sgmii_info;
};
struct ku_psample_port_sample_rate {
    uint16_t local_port;
    uint32_t rate;
};

#define NUMBER_OF_BITS_IN_SX_BITMAP 256

/**
 * ku_sx_bitmap is used to store the bitmap.
 */
struct ku_sx_bitmap {
    uint32_t max;
    uint8_t  table[NUMBER_OF_BITS_IN_SX_BITMAP];
};

/**
 * ku_sx_core_db is used to store all the state which should be saved/restored
 * when sx_sdk is paused/resumed.
 */
struct ku_sx_core_db {
    /**
     * The struct ku_sx_core_db passed between user space and kernel space has big size, we
     * place magic numbers at the beginning and end of the struct to verify if the entire
     * struct is successfully copied between user space and kernel space.
     * If new fields have to be added to this struct, please add them after the magic_start field
     * and before the magic_end field.
     */
    uint32_t                             magic_start;
    struct ku_dpt_info                   dpt_info[MAX_NUM_OF_REMOTE_SWITCHES + 1];
    struct ku_get_pci_profile            profile;
    struct ku_swid_details               swid_data[NUMBER_OF_SWIDS];
    uint8_t                              swid_enabled[NUMBER_OF_SWIDS];
    struct ku_htgt_reg                   trap_group_info[NUM_OF_TRAP_GROUPS];
    struct ku_port_vlan_params           port_vlan_params[NUM_OF_NET_DEV_TYPE][MAX_NUM_TRAPS_TO_REGISTER];
    uint16_t                             trap_ids[NUM_OF_NET_DEV_TYPE][MAX_NUM_TRAPS_TO_REGISTER];
    uint16_t                             num_of_traps[NUM_OF_NET_DEV_TYPE];
    uint16_t                             sysport_filter_db[NUM_HW_SYNDROMES][MAX_SYSTEM_PORTS_IN_FILTER];
    uint16_t                             lag_filter_db[NUM_HW_SYNDROMES][MAX_LAG_PORTS_IN_FILTER];
    uint16_t                             pvid_sysport_db[MAX_SYSPORT_NUM];
    uint16_t                             pvid_lag_db[MAX_LAG_NUM];
    uint8_t                              port_vtag_mode[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    uint8_t                              lag_vtag_mode[MAX_LAG_NUM + 1][SXD_MAX_VLAN_NUM];
    uint8_t                              port_prio_tagging_mode[MAX_PHYPORT_NUM + 1];
    uint8_t                              lag_prio_tagging_mode[MAX_LAG_NUM + 1];
    uint8_t                              port_prio2tc[MAX_PHYPORT_NUM + 1][MAX_PRIO_NUM + 1];
    uint8_t                              lag_prio2tc[MAX_LAG_NUM + 1][MAX_PRIO_NUM + 1];
    uint8_t                              local_to_swid_db[MAX_PHYPORT_NUM + 1];
    uint16_t                             ib_to_local_db[MAX_IBPORT_NUM + 1];
    uint16_t                             system_to_local_db[MAX_SYSPORT_NUM];
    uint16_t                             local_to_system_db[MAX_PHYPORT_NUM + 1];
    uint8_t                              lag_is_rp[MAX_LAG_NUM];
    uint16_t                             lag_rp_vid[MAX_LAG_NUM];
    uint16_t                             lag_rp_rif[MAX_LAG_NUM][SXD_MAX_VLAN_NUM];
    uint8_t                              lag_rp_rif_valid[MAX_LAG_NUM][SXD_MAX_VLAN_NUM];
    uint8_t                              lag_member_to_local_db[MAX_LAG_NUM][MAX_LAG_MEMBERS_NUM];
    uint16_t                             local_rp_vid[MAX_PHYPORT_NUM + 1];
    uint16_t                             port_rp_rif[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    uint8_t                              port_rp_rif_valid[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    uint8_t                              lag_oper_state[MAX_LAG_NUM];
    uint8_t                              port_ber_monitor_state[MAX_NUM_OF_REMOTE_SWITCHES + 1][MAX_PHYPORT_NUM + 1];
    uint8_t                              port_ber_monitor_bitmask[MAX_NUM_OF_REMOTE_SWITCHES + 1][MAX_PHYPORT_NUM + 1];
    uint8_t                              tele_thrs_state[MAX_PHYPORT_NUM + 1];
    uint64_t __attribute__((aligned(8))) tele_thrs_tc_vec[MAX_PHYPORT_NUM + 1];
    uint16_t                             truncate_size_db[NUMBER_OF_RDQS];
    uint32_t                             icmp_vlan2ip_db[SXD_MAX_VLAN_NUM];
    uint16_t                             port_vid_to_fid[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    struct ku_sx_bitmap                  ts_bitmap;
    struct ku_sx_bitmap                  ts_hw_utc_bitmap;
    struct ku_sx_bitmap                  high_prio_cq_bitmap;
    uint16_t                             fid_to_hwfid[MAX_FIDS_NUM];
    uint16_t                             rif_id_to_hwfid[MAX_RIFS_NUM];
    /**
     * If new fields have to be added to this struct, please add them after the magic_start field
     * and before the magic_end field.
     */
    uint32_t magic_end;
};

typedef enum sxd_trap_id {
    /* GENERAL */
    SXD_TRAP_ID_GENERAL_FDB      = 0x01,
    SXD_TRAP_ID_GENERAL_DR_IPC   = 0x02,
    SXD_TRAP_ID_GENERAL_DR_RES   = 0x04,
    SXD_TRAP_ID_GENERAL_ETH_EMAD = 0x05,
    SXD_TRAP_ID_FDB              = 0x06,

    /* EVENTS */
    SXD_TRAP_ID_PUDE            = 0x08,
    SXD_TRAP_ID_PMPE            = 0x09,
    SXD_TRAP_ID_FLAE            = 0x0A,
    SXD_TRAP_ID_FORE            = 0x0B,
    SXD_TRAP_ID_TMPW            = 0x0C,
    SXD_TRAP_ID_CPUWD           = 0x0D,
    SXD_TRAP_ID_ACCU_FLOW_INC   = 0x27,
    SXD_TRAP_ID_PLLP            = 0x2A,
    SXD_TRAP_ID_PPMBE           = 0x101, /* Keep for legacy */
    SXD_TRAP_ID_PPBME           = 0x101,
    SXD_TRAP_ID_PACKET_RECEIVED = 0x103,
    SXD_TRAP_ID_MFDE            = 0x003,
    SXD_TRAP_ID_MOCS_DONE       = 0x106,
    SXD_TRAP_ID_PPCNT           = 0x107,
    SXD_TRAP_ID_MGPCB           = 0x108,
    SXD_TRAP_ID_PBSR            = 0x109,
    SXD_TRAP_ID_SBSRD           = 0x10A,
    SXD_TRAP_ID_CEER            = 0x10B,
    SXD_TRAP_ID_MAFBI           = 0x10C,
    SXD_TRAP_ID_IPAC_DONE       = 0x10F,
    SXD_TRAP_ID_MAFRI           = 0x10E,
    SXD_TRAP_ID_UTFD            = 0x228,
    SXD_TRAP_ID_MOFRB           = 0x235,
    SXD_TRAP_ID_MOPCE           = 0x1B2,
    SXD_TRAP_ID_MECCC           = 0x1B3,
    SXD_TRAP_ID_FSED            = 0x1B5,
    SXD_TRAP_ID_MFRI            = 0x1BA,
    SXD_TRAP_ID_SB_SNAPSHOT     = 0x230,
    SXD_TRAP_ID_USACN           = 0x231,
    SXD_TRAP_ID_UTCC            = 0x232,
    SXD_TRAP_ID_UPCNT           = 0x233,
    SXD_TRAP_ID_MTPPST          = 0x280,
    SXD_TRAP_ID_FSHE            = 0x281,
    SXD_TRAP_ID_FSPS            = 0x282,
    SXD_TRAP_ID_MCION           = 0x295,
    SXD_TRAP_ID_PTSE            = 0x297,

    /* ETHERNET L2 */
    SXD_TRAP_ID_ETH_L2_STP   = 0x10,
    SXD_TRAP_ID_ETH_L2_LACP  = 0x11,
    SXD_TRAP_ID_ETH_L2_EAPOL = 0x12,
    SXD_TRAP_ID_ETH_L2_LLDP  = 0x13,
    SXD_TRAP_ID_ETH_L2_MMRP  = 0x14,
    SXD_TRAP_ID_ETH_L2_MVRP  = 0x15,
    SXD_TRAP_ID_ETH_L2_RPVST = 0x16,

    /* PTP */
    SXD_TRAP_ID_PTP_PTP0      = 0x28,
    SXD_TRAP_ID_PTP_PTP1      = 0x29,
    SXD_TRAP_ID_PTP_ING_EVENT = 0x2D,
    SXD_TRAP_ID_PTP_EGR_EVENT = 0x2E,

    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_QUERY     = 0x30,
    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_V1_REPORT = 0x31,
    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_V2_REPORT = 0x32,
    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_V3_REPORT = 0x34,
    SXD_TRAP_ID_ETH_L2_IGMP_TYPE_V2_LEAVE  = 0x33,
    SXD_TRAP_ID_ETH_L2_UDLD                = 0x18,
    SXD_TRAP_ID_ETH_L2_DHCP                = 0x19,
    SXD_TRAP_ID_ETH_L2_DHCPV6              = 0x1A,
    SXD_TRAP_ID_ETH_CONF_TYPE0             = 0x35,
    SXD_TRAP_ID_ETH_CONF_TYPE1             = 0x36,
    SXD_TRAP_ID_ETH_L2_PKT_SAMPLE          = 0x38,
    SXD_TRAP_ID_ETH_L2_PACKET_SAMPLING     = 0x38, /* Keep for legacy */
    SXD_TRAP_ID_FDB_MISS                   = 0x3a,
    SXD_TRAP_ID_FDB_MISMATCH               = 0x3b,
    SXD_TRAP_ID_FID_MISS                   = 0x3d,
    SXD_TRAP_ID_ICMPV6_CONF_TYPE0          = 0x48,
    SXD_TRAP_ID_ICMPV6_CONF_TYPE1          = 0x49,
    SXD_TRAP_ID_OVERLAY_ICMPV6_CONF_TYPE   = 0x4a,
    SXD_TRAP_ID_RARP_OPCODES               = 0x4f,

    /* FCoE */
    SXD_TRAP_ID_FCOE_FIP = 0x20,

    /* Telemetry */
    SXD_TRAP_ID_SB_CONG_TX_PORT = 0x2F,   /* Telemetry threshold crossing */
    SXD_TRAP_ID_HTACG_DONE      = 0x296,  /* Telemetry TAC action done event */

    /* ECN */
    SXD_TRAP_ID_DECAP_ECN0 = 0x40,
    SXD_TRAP_ID_DECAP_ECN1 = 0x41,

    /* Router */
    SXD_TRAP_ID_ARP_REQUEST            = 0x50,
    SXD_TRAP_ID_ARP_RESPONSE           = 0x51,
    SXD_TRAP_ID_ETH_L3_MTUERROR        = 0x52,
    SXD_TRAP_ID_ETH_L3_TTLERROR        = 0x53,
    SXD_TRAP_ID_ETH_L3_LBERROR         = 0x54,
    SXD_TRAP_ID_OSPF                   = 0x55,
    SXD_TRAP_ID_RIP_V1                 = 0x56,
    SXD_TRAP_ID_RIP_V2                 = 0x57,
    SXD_TRAP_ID_PIM                    = 0x58,
    SXD_TRAP_ID_VRRP                   = 0x59,
    SXD_TRAP_ID_VRRP_IPV6              = 0x7a,
    SXD_TRAP_ID_RESERVED_MC            = 0x5A,
    SXD_TRAP_ID_IPBC                   = 0x5B,
    SXD_TRAP_ID_ETH_L3_RPF             = 0x5C,
    SXD_TRAP_ID_ETH_L3_URPF_PROTECTION = 0x7f,
    SXD_TRAP_ID_ETH_L3_ASSERT          = 0x5D,
    SXD_TRAP_ID_IP2ME                  = 0x5F,
    SXD_TRAP_ID_IPTRAP_MIN             = 0x1c0,
    SXD_TRAP_ID_IPTRAP_MAX             = 0x1ff,
    SXD_TRAP_ID_RTR_INGRESS0           = 0x70,
    SXD_TRAP_ID_RTR_INGRESS1           = 0x71,
    SXD_TRAP_ID_RTR_INGRESS2           = 0x72,
    SXD_TRAP_ID_RTR_INGRESS3           = 0x73,
    SXD_TRAP_ID_RTR_EGRESS0            = 0x80,
    SXD_TRAP_ID_RTR_EGRESS1            = 0x81,
    SXD_TRAP_ID_RTR_EGRESS2            = 0x82,
    SXD_TRAP_ID_RTR_EGRESS3            = 0x83,
    SXD_TRAP_ID_HOST_MISS_IPV4         = 0x90,
    SXD_TRAP_ID_HOST_MISS_IPV6         = 0x92,
    SXD_TRAP_ID_BFD_IPV4               = 0xd0,
    SXD_TRAP_ID_BFD_IPV6               = 0xd1,
    SXD_TRAP_ID_SSH_IPV4               = 0xd2,
    SXD_TRAP_ID_SSH_IPV6               = 0xd3,
    SXD_TRAP_ID_PING_IPV4              = 0xd4,
    SXD_TRAP_ID_PING_IPV6              = 0xd5,
    SXD_TRAP_ID_ROUTER_ALERT_IPV4      = 0xd6,
    SXD_TRAP_ID_ROUTER_ALERT_IPV6      = 0xd7,
    SXD_TRAP_ID_IPV4_DHCP              = 0x8f,
    SXD_TRAP_ID_IPV4_SNMP              = 0xda,
    SXD_TRAP_ID_IPV6_SNMP              = 0xdb,
    SXD_TRAP_ID_ROUTER_ARPBC           = 0xe0,
    SXD_TRAP_ID_ROUTER_ARPUC           = 0xe1,
    SXD_TRAP_ID_ROUTER_RARP_OPCODES    = 0xe2,

    /* IPv6 L3 */
    SXD_TRAP_ID_IPV6_UNSPECIFIED_SIP = 0x7b,
    SXD_TRAP_ID_IPV6_UNSPECIFIED_DIP = 0x7c,
    SXD_TRAP_ID_IPV6_LINK_LOCAL_DST  = 0x61,
    SXD_TRAP_ID_IPV6_LINK_LOCAL_SRC  = 0x62,
    SXD_TRAP_ID_IPV6_ALL_NODES_LINK  = 0x63,
    SXD_TRAP_ID_IPV6_OSPF            = 0x64,
    SXD_TRAP_ID_IPV6_DHCP            = 0x69,

    /* IPv6 (SwitchX) */
    SXD_TRAP_ID_IPV6_ROUTER_SOLICITATION    = 0x6a,
    SXD_TRAP_ID_IPV6_ROUTER_ADVERTISEMENT   = 0x6b,
    SXD_TRAP_ID_IPV6_NEIGHBOR_SOLICITATION  = 0x6c,
    SXD_TRAP_ID_IPV6_NEIGHBOR_ADVERTISEMENT = 0x6d,
    SXD_TRAP_ID_IPV6_REDIRECTION            = 0x6e,

    /* IPv6 (Spectrum) */
    SXD_TRAP_ID_IPV6_ALL_ROUTERS_LINK          = 0x6f,
    SXD_TRAP_ID_L3_IPV6_ROUTER_SOLICITATION    = 0x8a,
    SXD_TRAP_ID_L3_IPV6_ROUTER_ADVERTISEMENT   = 0x8b,
    SXD_TRAP_ID_L3_IPV6_NEIGHBOR_SOLICITATION  = 0x8c,
    SXD_TRAP_ID_L3_IPV6_NEIGHBOR_ADVERTISEMENT = 0x8d,
    SXD_TRAP_ID_L3_IPV6_REDIRECTION            = 0x8e,

    /* IPv6 L2 */
    SXD_TRAP_ID_IPV6_MLD_V1_V2     = 0x65,
    SXD_TRAP_ID_IPV6_MLD_V1_REPORT = 0x66,
    SXD_TRAP_ID_IPV6_MLD_V1_DONE   = 0x67,
    SXD_TRAP_ID_IPV6_MLD_V2_REPORT = 0x68,

    /* InfiniBand */
    SXD_TRAP_ID_INFINIBAND_QP0              = 0xf0,
    SXD_TRAP_ID_INFINIBAND_QP1              = 0xf1,
    SXD_TRAP_ID_INFINIBAND_OTHER_QPS        = 0xf2,
    SXD_TRAP_ID_INFINIBAND_EXTERNAL_SMA     = 0x5e,
    SXD_TRAP_ID_INFINIBAND_IN_NV_ACCESS_REG = 0xf7,
    SXD_TRAP_ID_INFINIBAND_IB_FMAD_RCV      = 0xf8,
    SXD_TRAP_ID_INFINIBAND_RESET_CMD        = 0x102,

    /* ACL */
    SXD_TRAP_ID_ACL_MIN = 0x1c0,
    SXD_TRAP_ID_ACL_MAX = 0x1ef,

    /* ACL Drop */
    SXD_TRAP_ID_ACL_DROP     = SXD_TRAP_ID_ACL_MAX - 4,
    SXD_TRAP_ID_SYS_ACL_DROP = SXD_TRAP_ID_ACL_MAX - 5,

    /* MPLS */
    SXD_TRAP_ID_MPLS_ILM_MISS    = 0x98,
    SXD_TRAP_ID_MPLS_LDP         = 0x99,
    SXD_TRAP_ID_MPLS_LB_LSP_PING = 0x9a,
    SXD_TRAP_ID_MPLS_ILM0        = 0xa0,
    SXD_TRAP_ID_MPLS_ILM1        = 0xa1,
    SXD_TRAP_ID_MPLS_ILM2        = 0xa2,
    SXD_TRAP_ID_MPLS_ILM3        = 0xa3,
    SXD_TRAP_ID_MPLS_NHLFE0      = 0xa8,
    SXD_TRAP_ID_MPLS_NHLFE1      = 0xa9,
    SXD_TRAP_ID_MPLS_NHLFE2      = 0xaa,
    SXD_TRAP_ID_MPLS_NHLFE3      = 0xab,

    /* BGP */
    SXD_TRAP_ID_IPV4_BGP = 0x88,
    SXD_TRAP_ID_IPV6_BGP = 0x89,


    /* SPAN */
    SXD_TRAP_ID_MIRROR        = 0x3f,
    SXD_TRAP_ID_MIRROR_AGENT0 = 0x220,
    SXD_TRAP_ID_MIRROR_AGENT1 = 0x221,
    SXD_TRAP_ID_MIRROR_AGENT2 = 0x222,
    SXD_TRAP_ID_MIRROR_AGENT3 = 0x223,
    SXD_TRAP_ID_MIRROR_AGENT4 = 0x224,
    SXD_TRAP_ID_MIRROR_AGENT5 = 0x225,
    SXD_TRAP_ID_MIRROR_AGENT6 = 0x226,
    SXD_TRAP_ID_MIRROR_AGENT7 = 0x227,

    /* Tunneling */
    SXD_TRAP_ID_DECAP_ENCAP          = 0xb0,
    SXD_TRAP_ID_IPIP_DECAP_ERROR     = 0xb1,
    SXD_TRAP_ID_IPIP_ERROR           = 0xb2,
    SXD_TRAP_ID_NVE_DECAP_IGMP       = 0xb6,
    SXD_TRAP_ID_NVE_DECAP_ARP        = 0xb8,
    SXD_TRAP_ID_NVE_DECAP_TAG_ERROR  = 0xb9,
    SXD_TRAP_ID_NVE_IPV4_DHCP        = 0xba,
    SXD_TRAP_ID_NVE_IPV6_DHCP        = 0xbb,
    SXD_TRAP_ID_NVE_DECAP_FRAG_ERROR = 0xbc,
    SXD_TRAP_ID_NVE_ENCAP_ARP        = 0xbd,
    SXD_TRAP_ID_NVE_DECAP_ETH        = 0xbe,
    SXD_TRAP_ID_NVE_DECAP_MLD        = 0xbf,

    /* Discards */
    SXD_TRAP_ID_DISCARD_ING_PACKET     = 0x110,
    SXD_TRAP_ID_DISCARD_ING_SWITCH     = 0x111,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH  = 0x112,
    SXD_TRAP_ID_DISCARD_ING_ROUTER     = 0x113,
    SXD_TRAP_ID_DISCARD_ING_LSR        = 0x114,
    SXD_TRAP_ID_DISCARD_ROUTER         = 0x115,
    SXD_TRAP_ID_DISCARD_LSR            = 0x116,
    SXD_TRAP_ID_DISCARD_DEC            = 0x117,
    SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH = 0x118,
    SXD_TRAP_ID_DISCARD_ISOLATION      = 0x119,
    SXD_TRAP_ID_DISCARD_NON_ROUTED     = 0x11a,
    SXD_TRAP_ID_DISCARD_EGR_LSR        = 0x11b,
    SXD_TRAP_ID_DISCARD_MC_SCOPE       = 0x11c,
    SXD_TRAP_ID_DISCARD_ROUTER2        = 0x130,
    SXD_TRAP_ID_DISCARD_ROUTER3        = 0x131,
    SXD_TRAP_ID_DISCARD_LSR2           = 0x132,
    SXD_TRAP_ID_DISCARD_LSR3           = 0x133,

    /* Extended Discards */
    SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC_MC     = 0x140,
    SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC_DMAC   = 0x141,
    SXD_TRAP_ID_DISCARD_ING_PACKET_RSV_MAC     = 0x142,
    SXD_TRAP_ID_DISCARD_ING_PACKET_SMAC0       = 0x143,
    SXD_TRAP_ID_DISCARD_ING_SWITCH_VTAG_ALLOW  = 0x148,
    SXD_TRAP_ID_DISCARD_ING_SWITCH_VLAN        = 0x149,
    SXD_TRAP_ID_DISCARD_ING_SWITCH_STP         = 0x14A,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_UC       = 0x150,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_MC_NULL  = 0x151,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_LB       = 0x152,
    SXD_TRAP_ID_DISCARD_LOOKUP_SWITCH_NO_PORTS = 0x153,

    SXD_TRAP_ID_DISCARD_ING_ROUTER_NO_HDR         = 0x160,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_UC_DIP_MC_DMAC = 0x161,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LB         = 0x162,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_MC         = 0x163,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_CLASS_E    = 0x164,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_LB         = 0x165,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_UNSP       = 0x166,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_IP_HDR         = 0x167,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_MC_DMAC        = 0x168,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_DIP        = 0x169,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_BC         = 0x16A,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LOCAL_NET  = 0x16B,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_DIP_LINK_LOCAL = 0x16C,
    SXD_TRAP_ID_DISCARD_ING_ROUTER_SIP_LINK_LOCAL = 0x16D,

    SXD_TRAP_ID_DISCARD_ING_LSR_NO_LABEL = 0x170,
    SXD_TRAP_ID_DISCARD_ING_LSR_UC_ET    = 0x171,
    SXD_TRAP_ID_DISCARD_ING_LSR_MC_DMAC  = 0x172,

    SXD_TRAP_ID_DISCARD_ROUTER_IRIF_EN  = 0x178,
    SXD_TRAP_ID_DISCARD_ROUTER_ERIF_EN  = 0x179,
    SXD_TRAP_ID_DISCARD_ROUTER_ERIF_FWD = 0x17A,
    SXD_TRAP_ID_DISCARD_ROUTER_LPM4     = 0x17B,
    SXD_TRAP_ID_DISCARD_ROUTER_LPM6     = 0x17C,

    SXD_TRAP_ID_DISCARD_LSR_MIN_LABEL = 0x180,
    SXD_TRAP_ID_DISCARD_LSR_MAX_LABEL = 0x181,
    SXD_TRAP_ID_DISCARD_LSR_LB        = 0x182,

    SXD_TRAP_ID_DISCARD_DEC_PKT                  = 0x188,
    SXD_TRAP_ID_DISCARD_DEC_DIS                  = 0x189,
    SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC_MC   = 0x190,
    SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC_DMAC = 0x191,
    SXD_TRAP_ID_DISCARD_ENC_ISOLATION            = 0x192,
    SXD_TRAP_ID_DISCARD_DEC_NVE_OPTIONS          = 0x193,
    SXD_TRAP_ID_DISCARD_OVERLAY_SWITCH_SMAC0     = 0x194,


    SXD_TRAP_ID_DISCARD_EGR_LSR_NO_LABEL  = 0x1A8,
    SXD_TRAP_ID_DISCARD_EGR_LSR_NO_IP     = 0x1A9,
    SXD_TRAP_ID_DISCARD_EGR_LSR_PHP_NO_IP = 0x1AA,

    SXD_TRAP_ID_DISCARD_MC_SCOPE_IPV6_0 = 0x1B0,
    SXD_TRAP_ID_DISCARD_MC_SCOPE_IPV6_1 = 0x1B1,

    /* User defined trap ID */
    SXD_TRAP_ID_IP2ME_CUSTOM0 = 0xc0,
    SXD_TRAP_ID_IP2ME_CUSTOM1 = 0xc1,
    /* Host Configurable Traps */
    SXD_TRAP_ID_CONFT_SWITCH0     = 0x240,
    SXD_TRAP_ID_CONFT_SWITCH1     = 0x241,
    SXD_TRAP_ID_CONFT_SWITCH2     = 0x242,
    SXD_TRAP_ID_CONFT_SWITCH3     = 0x243,
    SXD_TRAP_ID_CONFT_ROUTER0     = 0x250,
    SXD_TRAP_ID_CONFT_ROUTER1     = 0x251,
    SXD_TRAP_ID_CONFT_ROUTER2     = 0x252,
    SXD_TRAP_ID_CONFT_ROUTER3     = 0x253,
    SXD_TRAP_ID_CONFT_SWITCH_ENC0 = 0x260,
    SXD_TRAP_ID_CONFT_SWITCH_ENC1 = 0x261,
    SXD_TRAP_ID_CONFT_SWITCH_ENC2 = 0x262,
    SXD_TRAP_ID_CONFT_SWITCH_ENC3 = 0x263,
    SXD_TRAP_ID_CONFT_SWITCH_DEC0 = 0x270,
    SXD_TRAP_ID_CONFT_SWITCH_DEC1 = 0x271,
    SXD_TRAP_ID_CONFT_SWITCH_DEC2 = 0x272,
    SXD_TRAP_ID_CONFT_SWITCH_DEC3 = 0x273,

    /* Management and Peripherals control traps */
    SXD_TRAP_ID_TSDE  = 0x320,      /**< Temperature Shut-Down Event */
    SXD_TRAP_ID_DSDSC = 0x321,      /**< Downstream Device Status Change */
    SXD_TRAP_ID_BCTOE = 0x322,      /**< Binary code transfer operation executed. */
    SXD_TRAP_ID_PMLPE = 0x32e,      /**< Port mapping change trap */

    /* SDK Test Traps */
    SXD_TRAP_ID_SDK_TEST1 = 0x3fe,
    SXD_TRAP_ID_SDK_TEST2 = 0x3ff,

    /* SW Generated Events */
    SXD_TRAP_ID_SIGNAL                          = 0x400,
    SXD_TRAP_ID_NEW_DEVICE_ADD                  = 0x401, /**< device add event */
    SXD_TRAP_ID_NEED_TO_RESOLVE_ARP             = 0x404, /**< need to resolve ARP  */
    SXD_TRAP_ID_NO_NEED_TO_RESOLVE_ARP          = 0x405, /**< no need to resolve ARP  */
    SXD_TRAP_ID_FDB_EVENT                       = 0x406, /**< FDB event */
    SXD_TRAP_ID_RM_SDK_TABLE_THRESHOLD_EVENT    = 0x407,
    SXD_TRAP_ID_RM_HW_TABLE_THRESHOLD_EVENT     = 0x408,
    SXD_TRAP_ID_FDB_SRC_MISS                    = 0x409, /**< FDB SRC MISS trap */
    SXD_TRAP_ID_ROUTER_NEIGH_ACTIVITY           = 0x40a,
    SXD_TRAP_ID_ASYNC_API_COMPLETE_EVENT        = 0x40b,
    SXD_TRAP_ID_ROUTER_MC_ACTIVITY              = 0x40c, /**< router mc activity */
    SXD_TRAP_ID_FDB_IP_ADDR_ACTIVITY            = 0x40d,
    SXD_TRAP_ID_TRANSACTION_ERROR               = 0x40e,
    SXD_TRAP_ID_BFD_TIMEOUT_EVENT               = 0x40f,
    SXD_TRAP_ID_BFD_PACKET_EVENT                = 0x410,
    SXD_TRAP_ID_OBJECT_DELETED_EVENT            = 0x411,
    SXD_TRAP_ID_SDK_HEALTH_EVENT                = 0x412,
    SXD_TRAP_ID_API_LOGGER_EVENT                = 0x413,
    SXD_TRAP_ID_BULK_COUNTER_DONE_EVENT         = 0x414,
    SXD_TRAP_ID_PORT_PROFILE_APPLY_DONE         = 0x415,
    SXD_TRAP_ID_PORT_ADDED                      = 0x431,
    SXD_TRAP_ID_PORT_DELETED                    = 0x432,
    SXD_TRAP_ID_PORT_ADDED_TO_LAG               = 0x433,
    SXD_TRAP_ID_PORT_REMOVED_FROM_LAG           = 0x434,
    SXD_TRAP_ID_BULK_COUNTER_REFRESH_DONE_EVENT = 0x435,
    SXD_TRAP_ID_ACL_ACTIVITY                    = 0x436,

    SXD_TRAP_ID_MIN = SXD_TRAP_ID_GENERAL_FDB,
    SXD_TRAP_ID_MAX = SXD_TRAP_ID_ACL_ACTIVITY,
} sxd_trap_id_t;

/**
 * Health severity
 * SXD_HEALTH_SEVERITY_ERR and SXD_HEALTH_SEVERITY_CRIT obsolete, replaced
 * by health monitor functionality from 4.5.1200
 */
#define SXD_FOREACH_OBJECT_HEALTH_SEVERITY(SXD_HEALTH_SEVERITY) \
    SXD_HEALTH_SEVERITY(SXD_HEALTH_SEVERITY_CRIT, , "critical") \
    SXD_HEALTH_SEVERITY(SXD_HEALTH_SEVERITY_FATAL, , "fatal")   \
    SXD_HEALTH_SEVERITY(SXD_HEALTH_SEVERITY_ERR, , "error")     \
    SXD_HEALTH_SEVERITY(SXD_HEALTH_SEVERITY_WARN, , "warning")  \
    SXD_HEALTH_SEVERITY(SXD_HEALTH_SEVERITY_NOTICE, , "notice") \

/**
 * sx_health_severity_t is used to distinguish between different SDK health event severities
 */
typedef enum sxd_health_severity {
    SXD_FOREACH_OBJECT_HEALTH_SEVERITY(SXD_GENERATE_ENUM)
} sxd_health_severity_t;

#define SXD_FOREACH_OBJECT_HEALTH_CAUSE(SXD_HEALTH_TYPE)                                             \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_NONE, , "none")                                                 \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_FW, , "FW health issue")                                        \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_GO_BIT, , "go bit not cleared")                                 \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_NO_CMDIFC_COMPLETION, , "command interface completion timeout") \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_EMAD_TIMEOUT, , "EMAD completion timeout")                      \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_CATAS, , "HW catastrophic event")                               \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_DUMP_COMPLETED, , "extended dump completed")                    \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_DUMP_FAILED, , "extended dump failed")                          \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_RDQ, , "RDQ didn't respond to event from FW")                   \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_SDQ, , "SDQ didn't get ACK from HW")                            \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_SDK_THREADS, , "SDK threads error")                             \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_KERNEL_THREADS, , "KERNEL threads error")                       \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_SDK_WD, , "SDK watchdog issue")                                 \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_FW_HETT, , "FW is busy or timeout on HETT")                     \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_STATEFUL_DB_ORDERING_E, , "HW error in stateful DB ordering")   \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_ECC_E, , "ECC events received from FW")                         \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_GENERIC_E, , "Generic error")                                   \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_PLL_E, , "PLL lock failure")                                    \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_FW_LONG_COMMAND, , "FW Long Command")                           \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_FW_MFGD, , "Failed to send MFGD")                               \
    SXD_HEALTH_TYPE(SXD_HEALTH_CAUSE_MAX_E, = SXD_HEALTH_CAUSE_FW_MFGD, "")                          \


/**
 * sx_health_cause_t is used to distinguish between different SDK health event causes
 */
typedef enum sxd_health_event_cause {
    SXD_FOREACH_OBJECT_HEALTH_CAUSE(SXD_GENERATE_ENUM)
} sxd_health_cause_t;

typedef union sxd_event_health_ecc_stats {
    uint32_t ecc_corrected;
    uint32_t ecc_uncorrected;
} sxd_event_health_ecc_stats_t;

struct sxd_ecc_counters_info {
    uint32_t ecc_corrected;
    uint32_t ecc_uncorrected;
};

typedef struct sxd_event_health_ecc_data {
    uint16_t                     slot_index;
    uint16_t                     device_index;
    sxd_event_health_ecc_stats_t ecc_stats;
} sxd_event_health_ecc_data_t;

typedef union sxd_event_health_data {
    sxd_event_health_ecc_data_t ecc_data;
} sxd_event_health_data_t;

typedef struct sxd_health_external_report_data {
    struct sxd_ecc_counters_info ecc_stats;
    sxd_event_health_data_t      extra_data_event;
} sxd_health_external_report_data_t;

/**
 * This event is generated by the SDK to notify the user that an SDK monitored event has occurred
 * Supported devices: Pelican, Eagle, Spectrum, Spectrum2, Quantum
 *
 */
typedef struct sxd_event_health_notification {
    uint8_t                 device_id;
    sxd_health_severity_t   severity;
    sxd_health_cause_t      cause;
    int                     was_debug_started; /* according to policy, see: sx_api_dbg_policy */
    uint8_t                 irisc_id; /*< which IRISC triggered the event, in case the event is SDK and not FW should be DBG_ALL_IRICS  */
    sxd_event_health_data_t data;
} sxd_event_health_notification_t;

#define THREAD_STR_LEN 256

enum sxd_health_fatal_failure_detect_cmd_e {
    SXD_HEALTH_FATAL_FAILURE_ENABLE_E,
    SXD_HEALTH_FATAL_FAILURE_DISABLE_E,
    SXD_HEALTH_FATAL_FAILURE_ADD_TRAP_GROUP_E,
    SXD_HEALTH_FATAL_FAILURE_DELETE_TRAP_GROUP_E,
    SXD_HEALTH_FATAL_FAILURE_UPDATE_SAMPLE_PARAMS_E,
    SXD_HEALTH_FATAL_FAILURE_ADD_SDK_THREAD_FAILRE_E,
    SXD_HEALTH_FATAL_FAILURE_ADD_EMAD_TIMEOUT_FAILURE_E,
    SXD_HEALTH_FATAL_FAILURE_ISSU_ON_E,
    SXD_HEALTH_FATAL_FAILURE_ISSU_OFF_E
};

#define SXD_FOREACH_OBJECT_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_FAILURE_ID)                           \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_EMAD_TX_E, , "Emad tx thread error")                     \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_EMAD_RX_E, , "Emad rx thread error")                     \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_GC_POST_QUEUE_TIME_E, , "GcPostTime thread error")       \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_HLFC_RSM_TMR_E, , "HlfcRsmTmr thread error")             \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_HLFC_EVENTS_E, , "HlfcEvents thread error")              \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_TIMERS_E, , "Timers thread error")                       \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_FDB_UC_POLLING_E, , "FdbUcPoliing thread error")         \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_MAIN_CORE_HANDLER_E, , "Main core handler thread error") \
    SXD_HEALTH_THREAD_FAILURE_ID(SXD_HEALTH_THREAD_MAX_E, = SXD_HEALTH_THREAD_MAIN_CORE_HANDLER_E, "")

/**
 * sxd_thread_failure_t is used to distinguish between different SDK thread with errors
 */
typedef enum sxd_thread_failure {
    SXD_FOREACH_OBJECT_HEALTH_THREAD_FAILURE_ID(SXD_GENERATE_ENUM)
} sxd_thread_failure_e;

typedef struct tg_params {
    int hw_trap_group;
} tg_params_t;

typedef struct sampling_params {
    uint32_t              check_interval;
    uint32_t              alert_threshold;
    uint64_t              hw_groups_curr_status;
    sxd_health_severity_t min_severity;
    sxd_boolean_t         issu_on;
} sampling_params_t;

typedef struct sdk_threads_info {
    sxd_thread_failure_e  sdk_thread_id;
    sxd_health_severity_t severity;
    char                  error_msg[THREAD_STR_LEN];
} sdk_threads_info_t;

typedef struct ku_dbg_health_check_params {
    enum sxd_health_fatal_failure_detect_cmd_e sxd_health_fatal_failure_detect_cmd;
    uint8_t                                    dev_id;
    union {
        tg_params_t        tg_params;
        sampling_params_t  sampling_params;
        sdk_threads_info_t sdk_threads_info;
    } params;
    sxd_boolean_t fatal_error_mode_active;
} ku_dbg_health_check_params_t;


/*
 * Note:editing this enum requires edit FOREACH_SPICE_BULK_COUNTER_TYPEMASK
 * */
enum sxd_bulk_cntr_key_type_e {
    SXD_BULK_CNTR_KEY_TYPE_PORT_E,
    SXD_BULK_CNTR_KEY_TYPE_FLOW_E,
    SXD_BULK_CNTR_KEY_TYPE_SHARED_BUFFER_E,
    SXD_BULK_CNTR_KEY_TYPE_HEADROOM_E,
    SXD_BULK_CNTR_KEY_TYPE_ELEPHANT_E,
    SXD_BULK_CNTR_KEY_TYPE_STATEFUL_DB_E,
    SXD_BULK_CNTR_KEY_TYPE_ACCUFLOW_E, /*< for internal use only */
    SXD_BULK_CNTR_KEY_TYPE_ISSU_E, /*< for internal use only */
    SXD_BULK_CNTR_KEY_TYPE_PERFORMANCE_E,
    SXD_BULK_CNTR_KEY_TYPE_FLOW_ESTIMATOR_E,
    SXD_BULK_CNTR_KEY_TYPE_MACSEC_PORT_E,
    SXD_BULK_CNTR_KEY_TYPE_MACSEC_SA_E,
    SXD_BULK_CNTR_KEY_TYPE_MACSEC_ACL_FLOW_E,
    SXD_BULK_CNTR_KEY_TYPE_LAST_E
};
enum sxd_bulk_cntr_shared_buffer_attr_type_e {
    SXD_BULK_CNTR_SHARED_BUFFER_ATTR_TYPE_RX_PG_E         = 1,
    SXD_BULK_CNTR_SHARED_BUFFER_ATTR_TYPE_TX_TC_E         = 2,
    SXD_BULK_CNTR_SHARED_BUFFER_ATTR_TYPE_CPU_TX_TC_E     = 3,
    SXD_BULK_CNTR_SHARED_BUFFER_ATTR_TYPE_RX_POOL_E       = 4,
    SXD_BULK_CNTR_SHARED_BUFFER_ATTR_TYPE_TX_POOL_E       = 5,
    SXD_BULK_CNTR_SHARED_BUFFER_ATTR_TYPE_MC_SWITH_PRIO_E = 6,
    SXD_BULK_CNTR_SHARED_BUFFER_ATTR_TYPE_RX_PER_POOL_E   = 7,
    SXD_BULK_CNTR_SHARED_BUFFER_ATTR_TYPE_TX_PER_POOL_E   = 8,
};
enum sxd_bulk_cntr_headroom_buffer_type_e {
    SXD_BULK_CNTR_HEADROOM_BUFFER_TYPE_MASTER_E = 1,
    SXD_BULK_CNTR_HEADROOM_BUFFER_TYPE_SLAVE_E  = 2,
};

typedef struct sxd_flow_counter_set {
    /*
     *   ATTENTION:
     *   SWIG does not let sx_flow_counter_set_t to be a typedef of sxd_flow_counter_set_t.
     *   Therefore, any changes to this struct MUST be applied to sx_flow_counter_set_t as well!
     */

    uint64_t flow_counter_packets;
    uint64_t flow_counter_bytes;
} sxd_flow_counter_set_t;

typedef struct sxd_buffer_occupancy {
    uint32_t curr_occupancy;
    uint32_t watermark;
} sxd_buffer_occupancy_t;

typedef struct sxd_bulk_cntr_buffer_layout_common {
    uint32_t type; /**< SXD_BULK_CNTR_KEY_TYPE_PORT_E, SXD_BULK_CNTR_KEY_TYPE_FLOW_E */
    uint32_t buff_size; /**< total buffer size, including this header */
    uint32_t num_of_counters; /**< number of expected counters (registers TLVs) from the operation */
    uint32_t counters_received_so_far; /**< number of counters (register TLVs) received so far during the operation */
    uint32_t cookie; /**< User cookie */
    uint32_t reserved; /**< to keep alignment to 64bit */
} sxd_bulk_cntr_buffer_layout_common_t;

typedef struct sxd_bulk_cntr_buffer_layout_flow {
    sxd_bulk_cntr_buffer_layout_common_t common;
    uint32_t                             base_counter_id; /**< base counter ID of the range of flow counters */
    uint32_t                             reserved; /**< to keep alignment to 64bit */
    sxd_flow_counter_set_t               counters[0]; /**< set of counters */
} sxd_bulk_cntr_buffer_layout_flow_t;

#define FLOW_ESTIMATOR_BINS_PER_FLOW_COUNTER 4

typedef struct sxd_flow_counter_estimator_set {
    /*
     *   ATTENTION:
     *   SWIG does not let sx_flow_estimator_counter_set_t to be a typedef of sxd_flow_estimator_counter_set_t.
     *   Therefore, any changes to this struct MUST be applied to sx_flow_estimator_counter_set_t as well!
     */

    uint32_t flow_estimator_records[FLOW_ESTIMATOR_BINS_PER_FLOW_COUNTER];
} sxd_flow_estimator_counter_set_t;

typedef struct sxd_bulk_cntr_buffer_layout_flow_estimator {
    sxd_bulk_cntr_buffer_layout_common_t common;
    uint32_t                             base_counter_id; /**< base counter ID of the range of flow counters */
    sxd_flow_estimator_counter_set_t     counter_sets[0]; /**< set of flow bin counters */
} sxd_bulk_cntr_buffer_layout_flow_estimator_t;

typedef enum sxd_bulk_cntr_port_grp {
    SXD_BULK_CNTR_PORT_GRP_IEEE_802_DOT_3_E  = 1,
    SXD_BULK_CNTR_PORT_GRP_RFC_2863_E        = 2,
    SXD_BULK_CNTR_PORT_GRP_RFC_2819_E        = 4,
    SXD_BULK_CNTR_PORT_GRP_RFC_3635_E        = 8,
    SXD_BULK_CNTR_PORT_GRP_PRIO_E            = 16,
    SXD_BULK_CNTR_PORT_GRP_TC_E              = 32,
    SXD_BULK_CNTR_PORT_GRP_BUFF_E            = 64,
    SXD_BULK_CNTR_PORT_GRP_PERF_E            = 128,
    SXD_BULK_CNTR_PORT_GRP_DISCARD_E         = 256,
    SXD_BULK_CNTR_PORT_GRP_PHY_LAYER_E       = 512,
    SXD_BULK_CNTR_PORT_GRP_PHY_LAYER_STATS_E = 1024,
    SXD_BULK_CNTR_PORT_GRP_MAX_E             = SXD_BULK_CNTR_PORT_GRP_PHY_LAYER_STATS_E
} sxd_bulk_cntr_port_grp_t;

typedef uint64_t sxd_port_cntr_t;
typedef uint32_t sxd_port_cntr32_t;

/**
 *   ATTENTION:
 *   SWIG does not let sx_port_cntr_xxx_t to be a typedef of sxd_port_cntr_xxx_t.
 *   Therefore, any changes to sxd_port_cntr_xxx_t MUST be applied to sx_port_cntr_xxx_t as well!
 */
typedef struct sxd_port_cntr_ieee_802_dot_3 {
    sxd_port_cntr_t a_frames_transmitted_ok;
    sxd_port_cntr_t a_frames_received_ok;
    sxd_port_cntr_t a_frame_check_sequence_errors;
    sxd_port_cntr_t a_alignment_errors;
    sxd_port_cntr_t a_octets_transmitted_ok;
    sxd_port_cntr_t a_octets_received_ok;
    sxd_port_cntr_t a_multicast_frames_xmitted_ok;
    sxd_port_cntr_t a_broadcast_frames_xmitted_ok;
    sxd_port_cntr_t a_multicast_frames_received_ok;
    sxd_port_cntr_t a_broadcast_frames_recieved_ok;
    sxd_port_cntr_t a_in_range_length_errors;
    sxd_port_cntr_t a_out_of_range_length_field;
    sxd_port_cntr_t a_frame_too_long_errors;
    sxd_port_cntr_t a_symbol_error_during_carrier;
    sxd_port_cntr_t a_mac_control_frames_transmitted;
    sxd_port_cntr_t a_mac_control_frames_received;
    sxd_port_cntr_t a_unsupported_opcodes_received;
    sxd_port_cntr_t a_pause_mac_ctrl_frames_received;
    sxd_port_cntr_t a_pause_mac_ctrl_frames_transmitted;
} __attribute__((packed)) sxd_port_cntr_ieee_802_dot_3_t;

typedef struct sxd_port_cntr_rfc_2863 {
    sxd_port_cntr_t if_in_octets;
    sxd_port_cntr_t if_in_ucast_pkts;
    sxd_port_cntr_t if_in_discards;
    sxd_port_cntr_t if_in_errors;
    sxd_port_cntr_t if_in_unknown_protos;
    sxd_port_cntr_t if_out_octets;
    sxd_port_cntr_t if_out_ucast_pkts;
    sxd_port_cntr_t if_out_discards;
    sxd_port_cntr_t if_out_errors;
    sxd_port_cntr_t if_in_multicast_pkts;
    sxd_port_cntr_t if_in_broadcast_pkts;
    sxd_port_cntr_t if_out_multicast_pkts;
    sxd_port_cntr_t if_out_broadcast_pkts;
} __attribute__((packed)) sxd_port_cntr_rfc_2863_t;

typedef struct sxd_port_cntr_rfc_2819 {
    sxd_port_cntr_t ether_stats_drop_events;
    sxd_port_cntr_t ether_stats_octets;
    sxd_port_cntr_t ether_stats_pkts;
    sxd_port_cntr_t ether_stats_broadcast_pkts;
    sxd_port_cntr_t ether_stats_multicast_pkts;
    sxd_port_cntr_t ether_stats_crc_align_errors;
    sxd_port_cntr_t ether_stats_undersize_pkts;
    sxd_port_cntr_t ether_stats_oversize_pkts;
    sxd_port_cntr_t ether_stats_fragments;
    sxd_port_cntr_t ether_stats_jabbers;
    sxd_port_cntr_t ether_stats_collisions;
    sxd_port_cntr_t ether_stats_pkts64octets;
    sxd_port_cntr_t ether_stats_pkts65to127octets;
    sxd_port_cntr_t ether_stats_pkts128to255octets;
    sxd_port_cntr_t ether_stats_pkts256to511octets;
    sxd_port_cntr_t ether_stats_pkts512to1023octets;
    sxd_port_cntr_t ether_stats_pkts1024to1518octets;
    sxd_port_cntr_t ether_stats_pkts1519to2047octets;
    sxd_port_cntr_t ether_stats_pkts2048to4095octets;
    sxd_port_cntr_t ether_stats_pkts4096to8191octets;
    sxd_port_cntr_t ether_stats_pkts8192to10239octets;
} __attribute__((packed)) sxd_port_cntr_rfc_2819_t;

typedef struct sxd_port_cntr_phy_layer {
    sxd_port_cntr_t   time_since_last_clear;
    sxd_port_cntr_t   symbol_errors;
    sxd_port_cntr_t   sync_headers_errors;
    sxd_port_cntr_t   edpl_bip_errors_lane0;
    sxd_port_cntr_t   edpl_bip_errors_lane1;
    sxd_port_cntr_t   edpl_bip_errors_lane2;
    sxd_port_cntr_t   edpl_bip_errors_lane3;
    sxd_port_cntr_t   fc_fec_corrected_blocks_lane0;
    sxd_port_cntr_t   fc_fec_corrected_blocks_lane1;
    sxd_port_cntr_t   fc_fec_corrected_blocks_lane2;
    sxd_port_cntr_t   fc_fec_corrected_blocks_lane3;
    sxd_port_cntr_t   fc_fec_uncorrectable_blocks_lane0;
    sxd_port_cntr_t   fc_fec_uncorrectable_blocks_lane1;
    sxd_port_cntr_t   fc_fec_uncorrectable_blocks_lane2;
    sxd_port_cntr_t   fc_fec_uncorrectable_blocks_lane3;
    sxd_port_cntr_t   rs_fec_corrected_blocks;
    sxd_port_cntr_t   rs_fec_uncorrectable_blocks;
    sxd_port_cntr_t   rs_fec_no_errors_blocks;
    sxd_port_cntr_t   rs_fec_single_error_blocks;
    sxd_port_cntr_t   rs_fec_corrected_symbols_total;
    sxd_port_cntr_t   rs_fec_corrected_symbols_lane0;
    sxd_port_cntr_t   rs_fec_corrected_symbols_lane1;
    sxd_port_cntr_t   rs_fec_corrected_symbols_lane2;
    sxd_port_cntr_t   rs_fec_corrected_symbols_lane3;
    sxd_port_cntr32_t link_down_events;
    sxd_port_cntr32_t successful_recovery_events;
} __attribute__((packed)) sxd_port_cntr_phy_layer_t;

typedef struct sxd_port_cntr_phy_layer_statistics {
    sxd_port_cntr_t time_since_last_clear;   /**< The time passed since the last counters clear event in msec */
    sxd_port_cntr_t phy_received_bits;       /**< Total number of bits which were received for all lanes */
    sxd_port_cntr_t phy_symbol_errors;       /**< Total number of symbol errors for all lanes */
    sxd_port_cntr_t phy_corrected_bits;      /**< Total number of corrected bits for all lanes */
    sxd_port_cntr_t phy_raw_errors_lane0;    /**< Depending on FEC mode and link_side type may hold 'NO FEC', 'FC FEC', 'RS FEC', or 'ZL FEC corrected' counter value on Lane 0 */
    sxd_port_cntr_t phy_raw_errors_lane1;    /**< Depending on FEC mode and link_side type may hold 'NO FEC', 'FC FEC', 'RS FEC', or 'ZL FEC corrected' counter value on Lane 1 */
    sxd_port_cntr_t phy_raw_errors_lane2;    /**< Depending on FEC mode and link_side type may hold 'NO FEC', 'FC FEC', 'RS FEC', or 'ZL FEC corrected' counter value on Lane 2 */
    sxd_port_cntr_t phy_raw_errors_lane3;    /**< Depending on FEC mode and link_side type may hold 'NO FEC', 'FC FEC', 'RS FEC', or 'ZL FEC corrected' counter value on Lane 3 */
    sxd_port_cntr_t phy_raw_errors_lane4;    /**< Depending on FEC mode and link_side type may hold 'NO FEC', 'FC FEC', 'RS FEC', or 'ZL FEC corrected' counter value on Lane 4 */
    sxd_port_cntr_t phy_raw_errors_lane5;    /**< Depending on FEC mode and link_side type may hold 'NO FEC', 'FC FEC', 'RS FEC', or 'ZL FEC corrected' counter value on Lane 5 */
    sxd_port_cntr_t phy_raw_errors_lane6;    /**< Depending on FEC mode and link_side type may hold 'NO FEC', 'FC FEC', 'RS FEC', or 'ZL FEC corrected' counter value on Lane 6 */
    sxd_port_cntr_t phy_raw_errors_lane7;    /**< Depending on FEC mode and link_side type may hold 'NO FEC', 'FC FEC', 'RS FEC', or 'ZL FEC corrected' counter value on Lane 7 */
    sxd_port_cntr_t raw_ber_magnitude;       /**< BER magnitude value for total number of errors. Used for BER calculation - Raw_BER = raw_ber_coef * 10^(-raw_ber_magnitude) */
    sxd_port_cntr_t raw_ber_coef;            /**< BER coefficient value for total number of errors */
    sxd_port_cntr_t effective_ber_magnitude; /**< BER magnitude value for effective number of errors. Used for BER calculation - Effective_BER = effective_ber_coef * 10^(-effective_ber_magnitude) */
    sxd_port_cntr_t effective_ber_coef;      /**< BER coefficient value for effective number of errors */
} __attribute__((packed)) sxd_port_cntr_phy_layer_statistics_t;

typedef struct sxd_port_cntr_rfc_3635 {
    sxd_port_cntr_t dot3stats_alignment_errors;
    sxd_port_cntr_t dot3stats_fcs_errors;
    sxd_port_cntr_t dot3stats_single_collision_frames;
    sxd_port_cntr_t dot3stats_multiple_collision_frames;
    sxd_port_cntr_t dot3stats_sqe_test_errors;
    sxd_port_cntr_t dot3stats_deferred_transmissions;
    sxd_port_cntr_t dot3stats_late_collisions;
    sxd_port_cntr_t dot3stats_excessive_collisions;
    sxd_port_cntr_t dot3stats_internal_mac_transmit_errors;
    sxd_port_cntr_t dot3stats_carrier_sense_errors;
    sxd_port_cntr_t dot3stats_frame_too_longs;
    sxd_port_cntr_t dot3stats_internal_mac_receive_errors;
    sxd_port_cntr_t dot3stats_symbol_errors;
    sxd_port_cntr_t dot3control_in_unknown_opcodes;
    sxd_port_cntr_t dot3in_pause_frames;
    sxd_port_cntr_t dot3out_pause_frames;
} __attribute__((packed)) sxd_port_cntr_rfc_3635_t;

typedef struct sxd_port_cntr_discard {
    sxd_port_cntr_t ingress_general;
    sxd_port_cntr_t ingress_policy_engine;
    sxd_port_cntr_t ingress_vlan_membership;
    sxd_port_cntr_t ingress_tag_frame_type;
    sxd_port_cntr_t egress_vlan_membership;
    sxd_port_cntr_t loopback_filter;
    sxd_port_cntr_t egress_general;
    sxd_port_cntr_t egress_link_down;
    sxd_port_cntr_t egress_hoq;
    sxd_port_cntr_t port_isolation;
    sxd_port_cntr_t egress_policy_engine;
    sxd_port_cntr_t ingress_tx_link_down;
    sxd_port_cntr_t egress_stp_filter;
    sxd_port_cntr_t egress_hoq_stall;
    sxd_port_cntr_t egress_sll;
    sxd_port_cntr_t ingress_discard_all;
} __attribute__((packed)) sxd_port_cntr_discard_t;

typedef struct sxd_port_traffic_cntr {
    sxd_port_cntr_t tx_octet;
    sxd_port_cntr_t tx_uc_frames;
    sxd_port_cntr_t tx_mc_frames;
    sxd_port_cntr_t tx_bc_frames;
    sxd_port_cntr_t tx_frames;
    sxd_port_cntr_t tx_queue;
    sxd_port_cntr_t tx_no_buffer_discard_uc;
    sxd_port_cntr_t tx_wred_discard;
    sxd_port_cntr_t tx_ecn_marked_tc;
} sxd_port_traffic_cntr_t;

typedef struct sxd_port_cntr_prio {
    sxd_port_cntr_t rx_octets;
    sxd_port_cntr_t rx_uc_frames;
    sxd_port_cntr_t rx_mc_frames;
    sxd_port_cntr_t rx_bc_frames;
    sxd_port_cntr_t rx_frames;
    sxd_port_cntr_t tx_octets;
    sxd_port_cntr_t tx_uc_frames;
    sxd_port_cntr_t tx_mc_frames;
    sxd_port_cntr_t tx_bc_frames;
    sxd_port_cntr_t tx_frames;
    sxd_port_cntr_t rx_pause;
    sxd_port_cntr_t rx_pause_duration;
    sxd_port_cntr_t tx_pause;
    sxd_port_cntr_t tx_pause_duration;
    sxd_port_cntr_t rx_pause_transition;
    sxd_port_cntr_t rx_discard;
} __attribute__((packed)) sxd_port_cntr_prio_t;

typedef struct sxd_port_cntr_buff {
    sxd_port_cntr_t rx_octet;
    sxd_port_cntr_t rx_frames;
    sxd_port_cntr_t rx_buffer_discard;
    sxd_port_cntr_t rx_shared_buffer_discard;
} __attribute__((packed)) sxd_port_cntr_buff_t;

typedef struct sxd_port_cntr_perf {
    sxd_port_cntr_t tx_wait;
    sxd_port_cntr_t ecn_marked;
    sxd_port_cntr_t no_buffer_discard_mc;
    sxd_port_cntr_t rx_ebp;
    sxd_port_cntr_t tx_ebp;
    sxd_port_cntr_t rx_buffer_almost_full;
    sxd_port_cntr_t rx_buffer_full;
    sxd_port_cntr_t tx_stats_pkts64octets;
    sxd_port_cntr_t tx_stats_pkts65to127octets;
    sxd_port_cntr_t tx_stats_pkts128to255octets;
    sxd_port_cntr_t tx_stats_pkts256to511octets;
    sxd_port_cntr_t tx_stats_pkts512to1023octets;
    sxd_port_cntr_t tx_stats_pkts1024to1518octets;
    sxd_port_cntr_t tx_stats_pkts1519to2047octets;
    sxd_port_cntr_t tx_stats_pkts2048to4095octets;
    sxd_port_cntr_t tx_stats_pkts4096to8191octets;
    sxd_port_cntr_t tx_stats_pkts8192to10239octets;
    sxd_port_cntr_t ece_marked;
    sxd_port_cntr_t tx_int_cksm_err;
} __attribute__((packed)) sxd_port_cntr_perf_t;

typedef enum sxd_port_prio_id {
    SXD_PORT_PRIO_ID_0,
    SXD_PORT_PRIO_ID_1,
    SXD_PORT_PRIO_ID_2,
    SXD_PORT_PRIO_ID_3,
    SXD_PORT_PRIO_ID_4,
    SXD_PORT_PRIO_ID_5,
    SXD_PORT_PRIO_ID_6,
    SXD_PORT_PRIO_ID_7,
    SXD_PORT_PRIO_ID_MIN = SXD_PORT_PRIO_ID_0,
    SXD_PORT_PRIO_ID_MAX = SXD_PORT_PRIO_ID_7,
} sxd_port_prio_id_t;

typedef enum sxd_port_tc_id {
    SXD_PORT_TC_ID_0,
    SXD_PORT_TC_ID_1,
    SXD_PORT_TC_ID_2,
    SXD_PORT_TC_ID_3,
    SXD_PORT_TC_ID_4,
    SXD_PORT_TC_ID_5,
    SXD_PORT_TC_ID_6,
    SXD_PORT_TC_ID_7,
    SXD_PORT_TC_ID_8,
    SXD_PORT_TC_ID_9,
    SXD_PORT_TC_ID_10,
    SXD_PORT_TC_ID_11,
    SXD_PORT_TC_ID_12,
    SXD_PORT_TC_ID_13,
    SXD_PORT_TC_ID_14,
    SXD_PORT_TC_ID_15,
    SXD_PORT_TC_ID_16,
    SXD_PORT_TC_ID_MIN = SXD_PORT_TC_ID_0,
    SXD_PORT_TC_ID_MAX = SXD_PORT_TC_ID_16,
} sxd_port_tc_id_t;

#define SXD_PRIORITY_GROUP_NUM (8)

typedef struct sxd_port_cntr_composition {
    sxd_port_cntr_ieee_802_dot_3_t       ieee_802_dot_3;
    sxd_port_cntr_rfc_2863_t             rfc_2863;
    sxd_port_cntr_rfc_2819_t             rfc_2819;
    sxd_port_cntr_rfc_3635_t             rfc_3635;
    sxd_port_cntr_prio_t                 prio[SXD_PORT_PRIO_ID_MAX - SXD_PORT_PRIO_ID_MIN + 1];
    sxd_port_traffic_cntr_t              tc[SXD_PORT_TC_ID_MAX - SXD_PORT_TC_ID_MIN + 1];
    sxd_port_cntr_buff_t                 pg[SXD_PRIORITY_GROUP_NUM];
    sxd_port_cntr_perf_t                 perf;
    sxd_port_cntr_discard_t              discard;
    sxd_port_cntr_phy_layer_t            phy_layer;
    sxd_port_cntr_phy_layer_statistics_t phy_layer_stats;
} __attribute__((packed)) sxd_port_cntr_composition_t;

/**
 *  Since each array entry is uint16_t, to keep alignment to 64 bit, here we use '4' in the macros.
 *  Valid local port range: [1 - MAX_PHYPORT_NUM]
 *  Valid LAG ID range: [0 - MAX_LAG_NUM)
 */
#define SXD_BULK_CNTR_PORT_TO_LAG_MAP_SIZE ((MAX_PHYPORT_NUM + 1) + ((4 - ((MAX_PHYPORT_NUM + 1) % 4)) & 0x3))
#define SXD_BULK_CNTR_PORT_INDEX_MAP_SIZE  (SXD_BULK_CNTR_PORT_TO_LAG_MAP_SIZE)
#define SXD_BULK_CNTR_LAG_INDEX_MAP_SIZE   (MAX_LAG_NUM + ((4 - (MAX_LAG_NUM % 4)) & 0x3))

typedef struct sxd_bulk_cntr_buffer_layout_port_mappings {
    uint16_t port_to_lag_map[SXD_BULK_CNTR_PORT_TO_LAG_MAP_SIZE]; /**< local port to LAG ID mapping
                                                                   *  value MAX_LAG_NUM means the port is not member of any LAG,
                                                                   *  value [0 - MAX_LAG_NUM) means the port is the member of the specific LAG.
                                                                   */
    uint16_t port_index_map[SXD_BULK_CNTR_PORT_INDEX_MAP_SIZE]; /**< port counter index in the counters array, value (MAX_PHYPORT_NUM + MAX_LAG_NUM) means the port is not expected */
    uint16_t lag_index_map[SXD_BULK_CNTR_LAG_INDEX_MAP_SIZE];   /**< LAG counter index in the counters array, value (MAX_PHYPORT_NUM + MAX_LAG_NUM) means the LAG is not expected */
    uint64_t counter_set_bitmap; /**< [0-11] bits - counter group
                                  *  [12-19] bits - priority
                                  *  [20-27] bits - PG
                                  *  [28-54] bits - TC
                                  */
} sxd_bulk_cntr_buffer_layout_port_mappings_t;

#define SXD_BULK_CNTR_PORT_BITMAP_GET(bitmap, obj, offset) ((bitmap) & ((((uint64_t)0x1) << (obj)) << (offset)))
#define SXD_BULK_CNTR_PORT_BITMAP_SET(bitmap, obj, offset) ((bitmap) |= ((((uint64_t)0x1) << (obj)) << (offset)))
#define SXD_BULK_CNTR_PORT_BITMAP_GET_PRIO(bitmap, obj)    SXD_BULK_CNTR_PORT_BITMAP_GET(bitmap, obj, 12)
#define SXD_BULK_CNTR_PORT_BITMAP_SET_PRIO(bitmap, obj)    SXD_BULK_CNTR_PORT_BITMAP_SET(bitmap, obj, 12)
#define SXD_BULK_CNTR_PORT_BITMAP_GET_PG(bitmap, obj)      SXD_BULK_CNTR_PORT_BITMAP_GET(bitmap, obj, 20)
#define SXD_BULK_CNTR_PORT_BITMAP_SET_PG(bitmap, obj)      SXD_BULK_CNTR_PORT_BITMAP_SET(bitmap, obj, 20)
#define SXD_BULK_CNTR_PORT_BITMAP_GET_TC(bitmap, obj)      SXD_BULK_CNTR_PORT_BITMAP_GET(bitmap, obj, 28)
#define SXD_BULK_CNTR_PORT_BITMAP_SET_TC(bitmap, obj)      SXD_BULK_CNTR_PORT_BITMAP_SET(bitmap, obj, 28)


typedef struct sxd_bulk_cntr_buffer_layout_port {
    sxd_bulk_cntr_buffer_layout_common_t        common;
    sxd_bulk_cntr_buffer_layout_port_mappings_t mappings;
    uint32_t                                    counters_size; /**< The array size of counters */
    uint32_t                                    reserved; /**< To keep alignment to 64bit */
    sxd_port_cntr_composition_t                 counters[0];
} sxd_bulk_cntr_buffer_layout_port_t;

typedef struct sxd_bulk_cntr_shared_buffer_pool_occupancy {
    uint32_t               sw_pool_id;
    uint32_t               reserved;
    sxd_buffer_occupancy_t occupancy;
    uint32_t               ext_occupancy;
} sxd_bulk_cntr_shared_buffer_pool_occupancy_t;

typedef struct sxd_bulk_cntr_shared_buffer_mc_port {
    sxd_buffer_occupancy_t occupancy;
} sxd_bulk_cntr_shared_buffer_mc_port_t;

typedef struct sxd_bulk_cntr_shared_buffer_port {
    sxd_buffer_occupancy_t                       rx_pg[SXD_BULK_CNTR_PG_NUM];
    sxd_buffer_occupancy_t                       tx_tc[SXD_BULK_CNTR_TC_NUM];
    sxd_bulk_cntr_shared_buffer_pool_occupancy_t rx_per_pool[SXD_BULK_CNTR_POOL_NUM];
    sxd_bulk_cntr_shared_buffer_pool_occupancy_t tx_per_pool[SXD_BULK_CNTR_POOL_NUM];
    sxd_buffer_occupancy_t                       rx_pg_desc[SXD_BULK_CNTR_PG_NUM];
    sxd_buffer_occupancy_t                       tx_tc_desc[SXD_BULK_CNTR_TC_NUM];
    sxd_bulk_cntr_shared_buffer_pool_occupancy_t rx_per_pool_desc[SXD_BULK_CNTR_POOL_NUM];
    sxd_bulk_cntr_shared_buffer_pool_occupancy_t tx_per_pool_desc[SXD_BULK_CNTR_POOL_NUM];
} sxd_bulk_cntr_shared_buffer_port_t;

typedef struct sxd_bulk_cntr_shared_buffer_mc_sp {
    sxd_buffer_occupancy_t statistics[SXD_BULK_CNTR_SP_NUM];
} sxd_bulk_cntr_shared_buffer_mc_sp_t;

typedef struct sxd_bulk_cntr_shared_buffer_pool {
    sxd_bulk_cntr_shared_buffer_pool_occupancy_t statistics[SXD_BULK_CNTR_TOTAL_POOL_MAX_NUM];
} sxd_bulk_cntr_shared_buffer_pool_t;

typedef struct sxd_bulk_cntr_buffer_layout_shared_buffer {
    sxd_bulk_cntr_buffer_layout_common_t  common;
    uint32_t                              port_idx;
    uint8_t                               pg_tc_sp_idx;
    uint8_t                               port_pool_idx;
    uint8_t                               pool_idx;
    uint8_t                               last_type;
    uint32_t                              sw_pool_id[SXD_BULK_CNTR_TOTAL_POOL_MAX_NUM];
    uint32_t                              reserved;
    uint32_t                              port_mask[SXD_BULK_CNTR_PORT_MASK_NUM];
    uint32_t                              mc_pool_id;
    sxd_bulk_cntr_shared_buffer_port_t    port[SXD_BULK_CNTR_PORT_NUM];
    sxd_bulk_cntr_shared_buffer_mc_port_t mc_port[SXD_BULK_CNTR_PORT_NUM];
    sxd_bulk_cntr_shared_buffer_mc_sp_t   mc_switch_prio;
    sxd_bulk_cntr_shared_buffer_pool_t    pool;
} sxd_bulk_cntr_buffer_layout_shared_buffer_t;

typedef struct sxd_bulk_cntr_occupancy_statistics_list {
    uint64_t               cnt;
    sxd_buffer_occupancy_t statistics[2];       /* Master and slave */
} sxd_bulk_cntr_occupancy_statistics_list_t;

typedef struct sxd_bulk_cntr_headroom_statistic {
    sxd_buffer_occupancy_t                    statistics;
    sxd_bulk_cntr_occupancy_statistics_list_t occupancy_statistics_lst;
} sxd_bulk_cntr_headroom_statistic_t;

typedef struct sxd_bulk_cntr_headroom_port {
    sxd_bulk_cntr_headroom_statistic_t port_pg[SXD_BULK_CNTR_PG_NUM];
    sxd_bulk_cntr_headroom_statistic_t shared;
    sxd_buffer_occupancy_t             shared_headroom_usage;
} sxd_bulk_cntr_headroom_port_t;

typedef struct sxd_bulk_cntr_buffer_layout_headroom {
    sxd_bulk_cntr_buffer_layout_common_t common;
    uint32_t                             port_mask[SXD_BULK_CNTR_PORT_MASK_NUM];
    uint8_t                              port_width[SXD_BULK_CNTR_PORT_NUM];              /* port width */
    sxd_bulk_cntr_headroom_port_t        headroom[SXD_BULK_CNTR_PORT_NUM];
} sxd_bulk_cntr_buffer_layout_headroom_t;

typedef struct sxd_macsec_cntr_sa_stats {
    uint64_t in_pkts_unchecked; /**< InPktsUnchecked IEEE 802.1AE, MGT4-14 and InPktsInvalid IEEE 802.1AE, MGT4-18. */
    uint64_t in_pkts_late;      /**< InPktsLate IEEE 802.1AE, MGT4-16 and InPktsDelayed, See IEEE 802.1AE, MGT4-15. */
    uint64_t in_pkts_ok;        /**< InPktsOK, See IEEE 802.1AE, MGT4-17. */
    uint64_t in_pkts_not_valid; /**< InPktsNotValid, See IEEE 802.1AE, MGT4-19. */
} sxd_macsec_cntr_sa_stats_t;

typedef struct sxd_macsec_acl_counter_set {
    uint64_t packets_counter; /**< Packet counter */
} sxd_macsec_acl_counter_set_t;

/**
 * MACSec Port Counter Group-0 Stats.
 */
typedef struct sxd_macsec_cntr_port_group0_stats {
    uint64_t in_pkts_mtu;        /**< Packets greater than MTU */
    uint64_t in_pkts_general;    /**< Frame too short; smac==dmac; ET Invalid; Tag allow; Encrypt Err */
    uint64_t in_pn_overflow;     /**< PN Overflow Ingress */
    uint64_t in_pause_pfc;       /**< PFC Pause Packets Ingress */
    uint64_t in_eapol;           /**< EAPOL Packets Ingress(if EAPOL check passes) */
    uint64_t in_buffer_overflow; /**< Ingress Buffer Overflow. Orthogonal to switch shared buffer overflow */
    uint64_t out_pkts_general;   /**< Tag Allow; Encrypt Err */
    uint64_t out_pn_overflow;    /**< PN Overflow Egress */
    uint64_t out_pause_pfc;      /**< PFC Pause Packets Egress */
    uint64_t out_eapol;          /**< EAPOL Packets Egress */
} sxd_macsec_cntr_port_group0_stats_t;

/**
 * MACSec Port Counter Group-1 Stats.
 */
typedef struct sxd_macsec_cntr_port_group1_stats {
    uint64_t in_pkts_untagged;      /**< InPktsUntagged; Ref IEEE 802.1AE, MGT4-8; After decryption */
    uint64_t in_pkts_notag;         /**< InPktsNoTag; Ref IEEE 802.1AE, MGT4-9; After decryption */
    uint64_t in_pkts_bad_tag;       /**< InPktsBadTag; Ref IEEE 802.1AE, MGT4-10; After decryption */
    uint64_t in_pkts_no_sa_rcv;     /**< InPktsNoSARcv; Ref IEEE 802.1AE, MGT4-11; After decryption */
    uint64_t in_pkts_no_sa_discard; /**< InPktsNoSADiscard; Ref IEEE 802.1AE, MGT4-12; After decryption */
    uint64_t in_octets_validated;   /**< InOctetsValidated; Ref IEEE 802.1AE, MGT4-22; After decryption */
    uint64_t in_octets_decrypted;   /**< InOctestDecrypted; Ref IEEE 802.1AE, MGT4-23 */
    uint64_t in_pkts_too_long;      /**< MTU failure prior to decryption */
    uint64_t out_pkts_untagged;     /**< OutPktsUntagged; Ref IEEE 802.1AE, MGT4-24; Also counts bypassed packets */
    uint64_t out_pkts_too_long;     /**< OutPktsTooLong; Ref IEEE 802.1AE, MGT4-25 */
    uint64_t out_octets_protected;  /**< OutPktsProtected; Ref IEEE 802.1AE, MGT4-28 */
    uint64_t out_octets_encrypted;  /**< OutPktsEncrypted; Ref IEEE 802.1AE, MGT4-29 */
} sxd_macsec_cntr_port_group1_stats_t;

typedef enum sxd_macsec_dir {
    SXD_MACSEC_DIR_INGRESS_E = 0x1,
    SXD_MACSEC_DIR_EGRESS_E  = 0x2,
    SXD_MACSEC_DIR_MIN_E     = SXD_MACSEC_DIR_INGRESS_E,
    SXD_MACSEC_DIR_MAX_E     = SXD_MACSEC_DIR_EGRESS_E
} sxd_macsec_dir_e;

typedef struct sxd_bulk_cntr_buffer_layout_macsec_acl_flow {
    sxd_bulk_cntr_buffer_layout_common_t common;
    uint16_t                             port_index_map[SXD_BULK_CNTR_PORT_INDEX_MAP_SIZE]; /**< port counter index in the counters array,
                                                                                             * value (MAX_PHYPORT_NUM + MAX_LAG_NUM) means the
                                                                                             *  port is not expected. */
    uint64_t                     number_of_counters;         /**< number of expected counters from the operation */
    uint16_t                     base_entity_id;         /**< base counter ID of the range of ACL counters */
    uint16_t                     reserved1;
    sxd_macsec_dir_e             direction;
    sxd_macsec_acl_counter_set_t counter_sets[0];            /**< set of acl counters */
} sxd_bulk_cntr_buffer_layout_macsec_acl_flow_t;

typedef struct sxd_bulk_cntr_buffer_layout_macsec_sa {
    sxd_bulk_cntr_buffer_layout_common_t common;
    uint64_t                             number_of_counters; /**< number of expected counters from the operation */
    uint16_t                             base_entity_id; /**< base SA ID of the range of SA counters */
    uint16_t                             uengine_id;
    sxd_macsec_dir_e                     direction;
    uint16_t                             local_port;
    uint16_t                             reserved1;
    uint32_t                             reserved2;
    sxd_macsec_cntr_sa_stats_t           counter_sets[0];    /**< set of SA counters */
} sxd_bulk_cntr_buffer_layout_macsec_sa_t;

typedef enum sxd_bulk_cntr_macsec_port_grp {
    SXD_BULK_CNTR_MACSEC_PORT_GRP_0_E   = 0x1,
    SXD_BULK_CNTR_MACSEC_PORT_GRP_1_E   = 0x2,
    SXD_BULK_CNTR_MACSEC_PORT_GRP_MIN_E = SXD_BULK_CNTR_MACSEC_PORT_GRP_0_E,
    SXD_BULK_CNTR_MACSEC_PORT_GRP_MAX_E = SXD_BULK_CNTR_MACSEC_PORT_GRP_1_E
} sxd_bulk_cntr_port_macsec_grp_t;

typedef struct sxd_bulk_cntr_buffer_layout_macsec_port_mappings {
    uint16_t port_index_map[SXD_BULK_CNTR_PORT_INDEX_MAP_SIZE]; /**< port counter index in the counters array, value (MAX_PHYPORT_NUM + MAX_LAG_NUM) means the port is not expected */
    uint64_t counter_set_bitmap;                                /**< [0-1] bits - counter group */
} sxd_bulk_cntr_buffer_layout_macsec_port_mappings_t;

typedef struct sxd_macsec_port_cntr_composition {
    sxd_macsec_cntr_port_group0_stats_t port_group0_stats;
    sxd_macsec_cntr_port_group1_stats_t port_group1_stats;
} sxd_macsec_port_cntr_composition_t;

typedef struct sxd_bulk_cntr_buffer_layout_macsec_port {
    sxd_bulk_cntr_buffer_layout_common_t               common;
    sxd_bulk_cntr_buffer_layout_macsec_port_mappings_t mappings;
    uint32_t                                           counters_size;  /**< The array size of counters */
    uint32_t                                           reserved;  /**< To keep alignment to 64bit */
    sxd_macsec_port_cntr_composition_t                 counters[0];
} sxd_bulk_cntr_buffer_layout_macsec_port_t;

/*
 *   ATTENTION:
 *   SWIG does not let API types to be a typedef of kernel user types.
 *   Therefore, any changes to those struct MUST be applied to API as well!
 */

/**
 * sxd_layout_elephant_flow_list is redefine of sx_cos_elephant_flow_ids_list_t.
 */
typedef struct sxd_layout_elephant_flow_list {
    uint32_t flow_cnt;
    uint8_t  flow_id_list[SXD_COS_ELEPHANT_FLOW_ID_NUM_MAX];
} sxd_layout_elephant_flow_list_t;

/**
 * ku_elephant_flow_hash_data_t is redefine of sx_cos_elephant_flow_hash_data_t.
 */
typedef struct ku_elephant_flow_hash_data {
    uint32_t hash_valid;
    uint16_t lag_hash;
    uint16_t router_hash;
} ku_elephant_flow_hash_data_t;

/**
 * ku_pcp_dei_t is redefine of sx_cos_pcp_dei_t.
 */
typedef struct ku_pcp_dei {
    uint8_t pcp;
    uint8_t dei;
} ku_pcp_dei_t;

/**
 * ku_elephant_flow_l2_data_t is redefine of sx_cos_elephant_flow_l2_data_t.
 */
typedef struct ku_elephant_flow_l2_data {
    uint32_t             l2_type;
    uint32_t             vlan_type;
    struct sx_ether_addr smac;
    struct sx_ether_addr dmac;
    uint16_t             vid;
    ku_pcp_dei_t         pcp_dei;
    uint16_t             inner_vid;
    ku_pcp_dei_t         inner_pcp_dei;
} ku_elephant_flow_l2_data_t;


/**
 * struct sx_ip is redefine of sx_ip_addr_t.
 */
struct sx_ip {
    uint8_t family;
    union {
        uint32_t ipv4;
        uint32_t ipv6[4];
    };
};

/**
 * ku_elephant_flow_l3_data_t is redefine of sx_cos_elephant_flow_l3_data_t.
 */
typedef struct ku_elephant_flow_l3_data {
    uint32_t     l3_type;
    uint8_t      dscp;
    uint8_t      ecn;
    uint8_t      ttl;
    uint32_t     dont_frag;
    struct sx_ip dip;
    struct sx_ip sip;
} ku_elephant_flow_l3_data_t;

/**
 * ku_elephant_flow_l4_data_t is redefine of sx_cos_elephant_flow_l4_data_t.
 */
typedef struct ku_elephant_flow_l4_data {
    uint32_t l4_type;
    uint16_t l4_destination_port;
    uint16_t l4_source_port;
} ku_elephant_flow_l4_data_t;

/**
 * ku_elephant_flow_tunnel_extra_data_t is redefine of sx_cos_elephant_flow_tunnel_extra_data_t.
 */
typedef struct ku_elephant_flow_tunnel_extra_data {
    uint32_t                   vni;
    struct sx_ether_addr       smac;
    struct sx_ether_addr       dmac;
    ku_elephant_flow_l3_data_t inner_l3;
} ku_elephant_flow_tunnel_extra_data_t;

/**
 * ku_mpls_label is redefine of sx_cos_mpls_label_t.
 */
typedef struct ku_mpls_label {
    uint32_t label_valid;
    uint32_t label_id;
    uint8_t  ttl;
} ku_mpls_label;

/**
 * ku_elephant_flow_mpls_extra_data_t is redefine of sx_cos_elephant_flow_mpls_extra_data_t.
 */
typedef struct ku_elephant_flow_mpls_extra_data {
    ku_mpls_label mpls_labels[SXD_COS_ELEPHANT_MPLS_LABELS_MAX_CNT];
    uint8_t       exp;
    uint32_t      bos;
} ku_elephant_flow_mpls_extra_data_t;

/**
 * ku_elephant_flow_extra_data_t is redefine of sx_cos_elephant_flow_extra_data_t.
 */
typedef struct ku_elephant_flow_extra_data {
    uint32_t extra_data_key;
    union {
        ku_elephant_flow_tunnel_extra_data_t tunnel_extra_data;
        ku_elephant_flow_mpls_extra_data_t   mpls_extra_data;
    };
} ku_elephant_flow_extra_data_t;

/**
 * ku_elephant_flow_data_value_t is redefine of sx_cos_elephant_flow_data_value_t.
 */
typedef struct ku_elephant_flow_data_value {
    ku_elephant_flow_hash_data_t  hash;
    ku_elephant_flow_l2_data_t    l2;
    ku_elephant_flow_l3_data_t    l3;
    ku_elephant_flow_l4_data_t    l4;
    ku_elephant_flow_extra_data_t extra_data;
} ku_elephant_flow_data_value_t;

/**
 * ku_elephant_flow_data_key_t is redefine of sx_cos_elephant_flow_data_key_t.
 */
typedef struct ku_elephant_flow_data_key {
    uint8_t  flow_id;
    uint32_t valid;
} ku_elephant_flow_data_key_t;

/**
 * ku_elephant_flow_data_t is redefine of sx_cos_elephant_flow_data_t.
 */
typedef struct ku_elephant_flow_data {
    ku_elephant_flow_data_key_t   data_key;
    ku_elephant_flow_data_value_t data_value;
} ku_elephant_flow_data_t;

typedef struct sxd_bulk_cntr_buffer_layout_elephant {
    sxd_bulk_cntr_buffer_layout_common_t common;
    uint32_t                             port_mask[SXD_COS_ELEPHANT_PORT_MASK_NUM];
    sxd_layout_elephant_flow_list_t      port_flows[SXD_COS_ELEPHANT_PORT_NUM_MAX];
    ku_elephant_flow_data_t              data[0];
} sxd_bulk_cntr_buffer_layout_elephant_t;

/**
 *  ku_stateful_db_acl_key_data_t is a redefine of sx_stateful_db_acl_key_data_t
 */

typedef struct ku_stateful_db_acl_key_data {
    uint32_t key_id;
    uint8_t  key_value[48];       /**< Max key value  */
    uint32_t reserved;            /** for alignment */
} ku_stateful_db_acl_key_data_t;

/**
 *  ku_stateful_db_key_data_t is a redefine of sx_stateful_db_key_data_t
 */

typedef struct ku_stateful_db_key_data {
    ku_stateful_db_acl_key_data_t key_data_list_p[SXD_ACL_MAX_FIELDS_IN_KEY];
    uint32_t                      reserved;
    uint32_t                      key_data_list_cnt;
} ku_stateful_db_key_data_t;

/**
 *  ku_stateful_db_entry_meta_t is a redefine of sx_stateful_db_entry_meta_t
 */

typedef struct ku_stateful_db_entry_meta {
    uint32_t entry_activity;
    uint32_t entry_sem_status;
    uint16_t entry_sem_cnt;
} ku_stateful_db_entry_meta_t;


/**
 * ku_stateful_db_key_data_t is a redefine of sx_stateful_db_entry_data_t
 */
typedef struct ku_stateful_db_entry_data {
    uint64_t db_entry_value;
} ku_stateful_db_entry_data_t;

/**
 * ku_stateful_db_key_id_t is a redefine of sx_stateful_db_key_id_t
 */

typedef uint32_t ku_stateful_db_key_id_t;

typedef struct ku_stateful_db_entry {
    uint32_t                    partition_id;
    ku_stateful_db_entry_meta_t db_entry_meta;
    ku_stateful_db_key_data_t   key_data;
    ku_stateful_db_key_id_t     key_id;
    ku_stateful_db_entry_data_t db_entry_data;
} ku_stateful_db_entry_t;

typedef struct ku_stateful_db_meta_layout {
    uint32_t number_of_entries;            /* Number of entries received */
    uint32_t number_of_entries_translated; /* Number of entries after translation */
} ku_stateful_db_meta_layout_t;


/**
 *  ku_stateful_db_translated_entry_t is a redefine of sx_stateful_db_translated_entry_t
 */
typedef struct ku_stateful_db_translated_entry {
    uint32_t                  entry_num;
    ku_stateful_db_key_id_t   key_id;
    ku_stateful_db_key_data_t key_data;
} ku_stateful_db_translated_entry_t;


typedef struct sxd_bulk_cntr_buffer_layout_stateful_db {
    sxd_bulk_cntr_buffer_layout_common_t common;
    ku_stateful_db_meta_layout_t         meta_layout;
    ku_stateful_db_entry_t               data[0];
} sxd_bulk_cntr_buffer_layout_stateful_db_t;

struct sxd_bulk_cntr_params_port {
    uint32_t                                    number_of_counters; /**< number of expected counters from the operation */
    sxd_bulk_cntr_buffer_layout_port_mappings_t mappings;
};
struct sxd_bulk_cntr_params_flow {
    uint32_t base_counter_id; /**< base counter ID of the range of flow counters */
};
struct sxd_bulk_cntr_params_shared_buffer {
    uint32_t num_of_counters;
    uint32_t sw_pool_id[SXD_BULK_CNTR_TOTAL_POOL_MAX_NUM];
    uint32_t mc_pool_id;
    uint32_t port_mask[SXD_BULK_CNTR_PORT_MASK_NUM];
};
struct sxd_bulk_cntr_params_headroom {
    uint32_t num_of_counters;
    uint32_t port_mask[SXD_BULK_CNTR_PORT_MASK_NUM];
    uint8_t  port_width[SXD_BULK_CNTR_PORT_NUM];              /* port width */
};
struct sxd_bulk_cntr_params_elephant {
    uint32_t port_mask[SXD_COS_ELEPHANT_PORT_MASK_NUM];
};

struct sxd_bulk_cntr_params_stateful_db {
    uint32_t entries_num_max;
};
struct sxd_bulk_cntr_params_macsec_port {
    uint32_t                                           number_of_counters;  /**< number of expected counters from the operation */
    sxd_bulk_cntr_buffer_layout_macsec_port_mappings_t mappings;
};
struct sxd_bulk_cntr_params_macsec_acl_flow {
    uint64_t base_entity_id;                             /**< base counter ID of the range of ACL counters */
    uint16_t port_index_map[SXD_BULK_CNTR_PORT_INDEX_MAP_SIZE];                             /**< port counter index in the counters array,
                                                                                             * value (MAX_PHYPORT_NUM + MAX_LAG_NUM) means the
                                                                                             *  port is not expected */
    sxd_macsec_dir_e direction;
    uint32_t         number_of_counters;                     /**< number of expected counters from the operation */
};

struct sxd_bulk_cntr_params_macsec_sa {
    uint16_t         uengine_id;
    uint16_t         local_port;
    uint32_t         reserved;
    uint64_t         base_entity_id;                            /**< base SA ID of the range of SA counters */
    sxd_macsec_dir_e direction;
    uint32_t         number_of_counters;                        /**< number of expected counters from the operation */
};

union sxd_bulk_cntr_transaction_params {
    struct sxd_bulk_cntr_params_port            port_params;
    struct sxd_bulk_cntr_params_flow            flow_params;
    struct sxd_bulk_cntr_params_shared_buffer   shared_buffer_params;
    struct sxd_bulk_cntr_params_headroom        headroom_params;
    struct sxd_bulk_cntr_params_elephant        elephant_params;
    struct sxd_bulk_cntr_params_stateful_db     stateful_db_params;
    struct sxd_bulk_cntr_params_flow            flow_estimator_params;
    struct sxd_bulk_cntr_params_macsec_port     macsec_port_params;
    struct sxd_bulk_cntr_params_macsec_acl_flow macsec_acl_flow_params;
    struct sxd_bulk_cntr_params_macsec_sa       macsec_sa_params;
};

typedef union sxd_bulk_cntr_event_id {
    struct {
        uint64_t id : 24,        /* running counter                        */
                 type      : 8,  /* type of transaction: PPCNT, MGPCB, ... */
                 client_id : 32; /* client process-ID                      */
    } event_id_fields;
    uint64_t event_id_value;
} sxd_bulk_cntr_event_id_t;

enum sxd_bulk_cntr_done_status_e {
    SXD_BULK_CNTR_DONE_STATUS_OK,
    SXD_BULK_CNTR_DONE_STATUS_CANCELED,
    SXD_BULK_CNTR_DONE_STATUS_ERROR,
    SXD_BULK_CNTR_DONE_STATUS_PARTIALLY_COMPLETE,
};

/**
 * ku_bulk_cntr_transaction_add is used to store the data of the CTRL_CMD_BULK_CNTR_TR_ADD ioctl
 */
struct ku_bulk_cntr_transaction_add {
    unsigned long                          buffer_id; /**< buffer ID */
    sxd_bulk_cntr_event_id_t               event_id; /**< event-ID of the transaction */
    union sxd_bulk_cntr_transaction_params params; /**< per-type transaction parameters */
};

/**
 * ku_bulk_cntr_transaction_poll is used to store the data of the CTRL_CMD_BULK_CNTR_TR_POLL ioctl
 */
struct ku_bulk_cntr_transaction_ack {
    unsigned long            buffer_id;         /**< buffer ID */
    sxd_bulk_cntr_event_id_t event_id;          /**< event-ID of the transaction */
};

/**
 * ku_bulk_cntr_transaction is used to call DEL/CANCEL/IN_PROGRESS ioctl
 */
struct ku_bulk_cntr_transaction {
    pid_t         client_pid; /**< process ID that keeps the buffer */
    unsigned long buffer_id; /**< buffer ID */
    uint32_t      type; /**< In parameter, pass session type between user and kernel space, needed for IN_PROGRESS ioctl */
    uint8_t       in_progress; /**< Out parameter, needed for IN_PROGRESS ioctl */
};

/**
 * This event is generated by the SDK driver to notify the user that an asynchronous bulk-counter
 * transaction has finished/canceled.
 */
typedef struct sxd_bulk_counter_done_notification {
    /*
     *   ATTENTION:
     *   SWIG does not let sx_bulk_counter_done_notification_t to be a typedef of sxd_bulk_counter_done_notification_t.
     *   Therefore, any changes to this struct MUST be applied to sx_bulk_counter_done_notification_t as well!
     */

    enum sxd_bulk_cntr_done_status_e status; /**< canceled, done_ok, done_error */
    unsigned long                    buffer_id; /**< buffer ID */
    uint32_t                         cookie; /**< User cookie */
} sxd_bulk_counter_done_notification_t;

typedef struct sxd_port_per_prio_counter_cache {
    sxd_port_cntr_prio_t counters[MAX_PHYPORT_NUM + 1][SXD_PORT_PRIO_ID_MAX - SXD_PORT_PRIO_ID_MIN + 1];
} sxd_port_per_prio_counter_cache_t;

struct ku_bulk_cntr_per_prio_cache {
    pid_t         pid;
    unsigned long user_ptr;
    uint8_t       is_set;
};
struct ku_client_pid_get {
    pid_t pid;
};

typedef enum sxd_span_mirror_reason {
    SXD_SPAN_MIRROR_REASON_INVALID_E                = 0,
    SXD_SPAN_MIRROR_REASON_ING_PORT_E               = 1,
    SXD_SPAN_MIRROR_REASON_ACL_E                    = 2,
    SXD_SPAN_MIRROR_REASON_ING_SHARED_BUFFER_DROP_E = 8,
    SXD_SPAN_MIRROR_REASON_ING_WRED_E               = 9,
    SXD_SPAN_MIRROR_REASON_ING_PG_CONGESTION_E      = 10,
    SXD_SPAN_MIRROR_REASON_ING_TC_CONGESTION_E      = 11,
    SXD_SPAN_MIRROR_REASON_EGR_TC_LATENCY_E         = 12,
    SXD_SPAN_MIRROR_REASON_EGR_ECN_E                = 13,
    SXD_SPAN_MIRROR_REASON_EGR_PORT_E               = 14,
    SXD_SPAN_MIRROR_REASON_TRAP_GROUP_E             = 15,
    SXD_SPAN_MIRROR_REASON_MIN_E                    = SXD_SPAN_MIRROR_REASON_INVALID_E,
    SXD_SPAN_MIRROR_REASON_MAX_E                    = SXD_SPAN_MIRROR_REASON_TRAP_GROUP_E,
} sxd_span_mirror_reason_e;

/**
 * ku_buffer_drop_params is used to call CTRL_CMD_BUFFER_DROP_PARAMS ioctl
 */
struct ku_buffer_drop_params {
    uint8_t  is_set; /**< Set/unset the buffer drop parameters .*/
    uint16_t trap_id; /**< The trap ID configured by user for buffer drop, ignored when is_set is 0. */
};

typedef enum sxd_map_memory_type {
    SXD_MAP_MEMORY_TYPE_FW_LOAD_E          = 0,
    SXD_MAP_MEMORY_TYPE_PORT_PROFILE_MEM_E = 1,
    SXD_MAP_MEMORY_TYPE_MIN_E              = SXD_MAP_MEMORY_TYPE_FW_LOAD_E,
    SXD_MAP_MEMORY_TYPE_MAX_E              = SXD_MAP_MEMORY_TYPE_PORT_PROFILE_MEM_E
} sxd_map_memory_type_e;


/**
 * ku_map_mem is used to call CTRL_CMD_MAP_FW_MEMORY_TO_CPU ioctl
 */
struct ku_map_memory {
    uint8_t               dev_id; /**< dev_id - device id */
    uint16_t              mem_size; /**< Size of memory to map: total = (mem_size * 4K) */
    sxd_map_memory_type_e mem_type; /**< Type of memory */
};

typedef struct sxd_bulk_cntr_refresh_attr {
    uint32_t cookie; /**< User cookie */
} sxd_bulk_cntr_refresh_attr_t;

/**
 * This event is generated by the SDK driver to notify the user that an asynchronous bulk-counter
 * refresh has finished/canceled.
 */
typedef struct sxd_bulk_cntr_refresh_done_notification {
    /*
     *   ATTENTION:
     *   SWIG does not let sx_bulk_cntr_refresh_done_notification_t to be a typedef of sxd_bulk_counter_done_notification_t.
     *   Therefore, any changes to this struct MUST be applied to sx_bulk_cntr_refresh_done_notification_t as well!
     */
    sxd_bulk_cntr_refresh_attr_t counter_refresh_attr;
} sxd_bulk_cntr_refresh_done_notification_t;


typedef enum ku_accuflow_counters_params_op {
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_INVALID_E = 0,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_INIT_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_DEINIT_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_CLEAR_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_READ_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_TRASACTION_START_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_TRASACTION_RESERVATION_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_ALLOC_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_MOVE_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_MIN_E = KU_ACCUFLOW_COUNTERS_PARAMS_OP_INIT_E,
    KU_ACCUFLOW_COUNTERS_PARAMS_OP_MAX_E = KU_ACCUFLOW_COUNTERS_PARAMS_OP_MOVE_E,
} ku_accuflow_counters_params_op_e;

typedef struct ku_accuflow_counters_params_data_init {
    uint32_t prm_counters_num;
    uint16_t packets_inc_unit;
    uint16_t bytes_inc_unit;
    uint32_t prm_cntr_lines_per_bank;
    uint8_t  prm_cntr_banks;
    uint8_t  prm_cntr_lines_flow_both;
    uint8_t  prm_cntr_type_flow_both;
    uint32_t prm_cntr_start_idx_offset;
} ku_accuflow_counters_params_data_init_t;

typedef struct ku_accuflow_counters_params_data_deinit {
    uint32_t reserved;
} ku_accuflow_counters_params_data_deinit_t;

typedef struct ku_accuflow_counters_params_data_clear {
    uint32_t prm_counter_idx;
    uint32_t num_of_counters;
} ku_accuflow_counters_params_data_clear_t;

typedef struct ku_accuflow_counters_params_data_read {
    uint32_t               prm_counter_idx;
    uint32_t               num_of_counters;
    sxd_flow_counter_set_t counters_values[0];
} ku_accuflow_counters_params_data_read_t;

typedef struct ku_accuflow_counters_params_data_transaction {
    sxd_boolean_t            cancel; /**< Disable transaction that is currently in progress */
    uint32_t                 base_counter_id; /**< base counter ID of the range of flow counters */
    uint32_t                 prm_counter_id;
    uint32_t                 num_of_counters;
    sxd_bulk_cntr_event_id_t ev_id;
    unsigned long            buffer_id;
    sxd_boolean_t            clear;
    sxd_boolean_t            flush;
} ku_accuflow_counters_params_data_transaction_t;

enum ku_accuflow_counters_params_data_tr_reservation_action_e {
    KU_ACCUFLOW_COUNTERS_PARAMS_DATA_TR_RESERVATION_ACTION_ACQUIRE_E = 0,
    KU_ACCUFLOW_COUNTERS_PARAMS_DATA_TR_RESERVATION_ACTION_RELEASE_E
};

typedef struct ku_accuflow_counters_params_data_tr_reservation {
    enum ku_accuflow_counters_params_data_tr_reservation_action_e action;
    sxd_bulk_cntr_refresh_attr_t                                  refresh_attr;
} ku_accuflow_counters_params_data_tr_reservation_t;

typedef struct ku_accuflow_counters_params_data_alloc {
    uint32_t prm_counter_idx;
    uint32_t num_of_counters;
} ku_accuflow_counters_params_data_alloc_t;

typedef struct ku_accuflow_counters_params_data_move {
    uint32_t old_prm_counter_idx;
    uint32_t new_prm_counter_idx;
    uint32_t num_of_counters;
} ku_accuflow_counters_params_data_move_t;

typedef union ku_accuflow_counters_params_data {
    ku_accuflow_counters_params_data_init_t           init_data;
    ku_accuflow_counters_params_data_deinit_t         deinit_data;
    ku_accuflow_counters_params_data_clear_t          clear_data;
    ku_accuflow_counters_params_data_read_t           read_data;
    ku_accuflow_counters_params_data_transaction_t    transaction_data;
    ku_accuflow_counters_params_data_tr_reservation_t tr_reservation;
    ku_accuflow_counters_params_data_alloc_t          alloc_data;
    ku_accuflow_counters_params_data_move_t           move_data;
} ku_accuflow_counters_params_data_t;

/**
 * ku_accuflow_cmd_params is used to call CTRL_CMD_ACCUFLOW_COUNTERS ioctl
 */
typedef struct ku_accuflow_counters_params {
    ku_accuflow_counters_params_op_e   op;
    ku_accuflow_counters_params_data_t op_data;
} ku_accuflow_counters_params_t;

typedef struct ku_port_module_map_set_params {
    uint8_t       dev_id;
    sxd_boolean_t is_set;
    uint16_t      local_port;
    uint8_t       slot_id;
    uint8_t       module_id;
} ku_port_module_map_set_params_t;

typedef struct ku_port_module_update_params {
    uint16_t local_port;
    uint8_t  admin_status;
    uint8_t  slot_id;
    uint8_t  module_id;
} ku_port_module_update_params_t;

typedef enum sxd_macsec_ucheck_id {
    SXD_UCHECK_ID_INGRESS_MTU_EVENT_E = 0x30,
    SXD_UCHECK_ID_TAG_ALLOW_E         = 0x50,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_0_E  = 0x60,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_1_E  = 0x61,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_2_E  = 0x62,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_3_E  = 0x63,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_4_E  = 0x64,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_5_E  = 0x65,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_6_E  = 0x66,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_7_E  = 0x67,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_8_E  = 0x68,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_9_E  = 0x69,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_10_E = 0x6A,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_11_E = 0x6B,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_12_E = 0x6C,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_13_E = 0x6D,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_14_E = 0x6E,
    SXD_UCHECK_ID_UTCAM_EVENT_ID_15_E = 0x6F,
    SXD_UCHECK_ID_NO_SECTAG_E         = 0x80,
    SXD_UCHECK_ID_SECTAG_ERROR_E      = 0x81,
    SXD_UCHECK_ID_ENCRYPT_ERROR_E     = 0x84,
} sxd_macsec_ucheck_id_e;

#define SXD_IBSNI_IPV4_RECORD_NUM 4

#define SXD_IBSNI_IPV6_NUM 4

#define SXD_IBSNI_NETMASK_NUM 4

#define SXD_IBSNI_IPV6_RECORD_NUM 4

typedef struct sxd_ibsni_ipv4_record {
    uint32_t ipv4;
    uint32_t netmask;
} sxd_ibsni_ipv4_record_t;

typedef struct sxd_ibsni_ipv6_record {
    uint32_t ipv6[SXD_IBSNI_IPV6_NUM];
    uint32_t netmask[SXD_IBSNI_NETMASK_NUM];
} sxd_ibsni_ipv6_record_t;

/**
 * ku_ibsni_reg structure is used to store the IBSNI register parameters
 */
struct ku_ibsni_reg {
    sxd_ibsni_ipv4_record_t ipv4_record[SXD_IBSNI_IPV4_RECORD_NUM];
    sxd_ibsni_ipv6_record_t ipv6_record[SXD_IBSNI_IPV6_RECORD_NUM];
};

/**
 * ku_access_ibsni_reg structure is used to store the access register IBSNI command parameters
 */
struct ku_access_ibsni_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ibsni_reg     ibsni_reg; /**< ibsni_reg - ibsni register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_slcr_reg structure is used to store the access register SLCR command parameters
 */
struct ku_access_slcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_slcr_reg      slcr_reg; /**< slcr_reg - slcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

struct ku_mopir_v2_reg {
    uint16_t       dst_port; /* The local port the packet is forwarded to; Reserved when dr=0; */
    uint8_t        is_control; /* 0: data packet; 1: control packet */
    uint16_t       packet_length; /* packet length in bytes */
    const uint8_t *packet;   /* Packet data; Max packet size is 1712Bytes. */
};

/**
 * ku_access_mopir_v2_reg structure is used to store the access register MOPIR_V2 command parameters
 */
struct ku_access_mopir_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mopir_v2_reg  mopir_v2_reg; /**< mopir_v2_reg - mopir_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

struct ku_mopr_reg {
    uint8_t  op;            /* 0: read packet; 1: read packet and clear buffer */
    uint16_t packet_length; /* received packet length */
    uint8_t  cqe_v2[32];    /* Packet's CQE_v2 */
    uint8_t *packet;        /* Packet data; Max packet size is 1712Bytes. */
};

/**
 * ku_access_mopr_reg structure is used to store the access register MOPR command parameters
 */
struct ku_access_mopr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mopr_reg      mopr_reg; /**< mopr_reg - mopr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

# define SXD_MNVDA_TYPE_INDEX_NV_SWITCH_CONF 0x100
# define SXD_MNVDA_TYPE_CLASS_NV_SWITCH_CONF 0x8
# define SXD_MNVDA_LENGTH_NV_SWITCH_CONF     0x8

typedef struct ku_nv_switch_conf {
    sxd_boolean_t das;          /* Disable Auto-Split */
    sxd_boolean_t is_nvlink;    /* 0: IB; 1: NVlink */
    uint8_t       split_mode;   /* 0: NO_SPLIT_SUPPORT; 1: SPLIT_2X */
} ku_nv_switch_conf_t;

struct ku_mnvda_nv_switch_conf_reg {
    uint8_t             valid;             /* 0: invalid_data; 1: illegal; 2: valid_data; 3:free */
    uint8_t             length;            /* Length of configuration item data */
    uint32_t            type_class_index;
    uint16_t            crc16;
    ku_nv_switch_conf_t nv_switch_conf;
};

/**
 * ku_access_mnvda_nv_switch_conf_reg structure is used to store the access register MNVDA NV_SWITCH_CONF command parameters
 */
struct ku_access_mnvda_nv_switch_conf_reg {
    struct ku_operation_tlv            op_tlv;                      /**< op_tlv - operation tlv struct */
    struct ku_mnvda_nv_switch_conf_reg mnvda_nv_switch_conf_reg;    /**< mnvda_nv_switch_conf_reg - mnvda_nv_switch_conf register tlv */
    uint8_t                            dev_id;                      /**< dev_id - device id */
};

/* make sure that PAGE_SIZE is defined the same in user/kernel spaces */
#if !defined(__KERNEL__)
#define PAGE_SIZE 4096
#else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(5, 10, 0))
static_assert(PAGE_SIZE == 4096, "Page size is not 4096B");
#endif
#endif

#define EVENT_SIZE_IN_BYTES (sizeof(uint64_t))
/**
 * ku_host_mem_read_page structure is used to store the hot memory read parameters
 */
struct ku_host_mem_read_page {
    uint8_t      dev_id;                          /**< dev_id - Device ID */
    unsigned int page_index;                          /**< address - Address to read from */
    uint64_t     pg_data_arr[PAGE_SIZE / EVENT_SIZE_IN_BYTES];                          /**< data - Buffer to read into */
};

/* Please, do not move this include.
 *  It includes auto generated code which uses data defined in this file. */
#ifdef __KERNEL__
#include <linux/mlx_sx/auto_registers/kernel_user_auto.h>
#else
#include "auto_registers/kernel_user_auto.h"
#endif

struct sx_device_info_read_only {
    sxd_chip_types_t          chip_type;
    enum sxd_fw_boot_status_e fw_boot_status;
    struct ku_mgir_reg        mgir;
    struct ku_query_fw        q_fw;
};

struct sx_device_info_set {
    uint8_t sdk_folder_path[SXD_DIR_NAME_MAX_LEN + 1];
};

struct sx_device_info {
    struct sx_device_info_read_only dev_info_ro;
    struct sx_device_info_set       dev_info_set;
};


/**
 *  ku_dev_info structure is used to store the device id and the device info parameters
 */
struct ku_dev_info {
    uint8_t               dev_id;     /**< dev_id - device id */
    struct sx_device_info dev_info;     /**< dev_info - read-only information */
};

#endif /* KERNEL_USER_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
