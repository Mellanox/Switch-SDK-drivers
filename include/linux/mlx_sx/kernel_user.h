/*
 * Copyright (c) 2010-2019,  Mellanox Technologies. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef KERNEL_USER_H_
#define KERNEL_USER_H_

#ifdef __KERNEL__
#include <linux/uio.h>
#else
#include <sys/uio.h>
#include <stdint.h>
#include <time.h>
#endif

/************************************************
 *  Define
 ***********************************************/

/**
 * MPCIR enum is used for opcode in the MPCIR register parameters
 */
typedef enum sxd_mpcir_op {
    SXD_MPCIR_OP_NOP_E = 0x0,
    SXD_MPCIR_OP_ENABLE_E = 0x1,
    SXD_MPCIR_OP_DISABLE_E = 0x2,
    SXD_MPCIR_OP_STATUS_E = 0x3,
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

enum {
    SX_SEND_DQ_DB_BASE = 0,
    SX_RECV_DQ_DB_BASE = 0x200,
    SX_MAX_LOG_DQ_SIZE = 10,
    SX_MAX_LOG_CQ_SIZE = 10,
    SX_CQE_VER_OFFSET = 4,
    SX_DBELL_CQ_CI_OFFSET = 0x400,
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
#define NUM_HW_SYNDROMES (512 + NUM_SW_SYNDROMES)

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

#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_0        0x10
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_1        0x11
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_2        0x12
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_3        0x13
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_4        0x14
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_5        0x15
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_6        0x16
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_7        0x17
#define SXD_ACL_KEY_BLOCK_FLEX2_MAC_8        0x18
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_0  0x20
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_1  0x21
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_2  0x22
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_3  0x23
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_MAC_4  0x24
#define SXD_ACL_KEY_BLOCK_IPV4_EX3           0x2D
#define SXD_ACL_KEY_BLOCK_FLEX2_IP_0         0x30
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_0       0x38
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_1       0x39
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_2       0x3A
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_3       0x3B
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_4       0x3C
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV4_5       0x3D
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_0       0x40
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_1       0x41
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_2       0x42
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_3       0x43
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_4       0x44
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_5       0x45
#define SXD_ACL_KEY_BLOCK_FLEX2_IPV6_6       0x46
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_0 0x50
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_1 0x51
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV4_2 0x52
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_0 0x58
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_1 0x59
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_2 0x5A
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_3 0x5B
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_4 0x5C
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_5 0x5D
#define SXD_ACL_KEY_BLOCK_FLEX2_INNER_IPV6_6 0x5E
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_0       0x60
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_1       0x61
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_2       0x62
#define SXD_ACL_KEY_BLOCK_FLEX2_MPLS_3       0x63
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
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_3       0xB3
#define SXD_ACL_KEY_BLOCK_FLEX2_MISC_4       0xB4
#define SXD_ACL_KEY_BLOCK_FLEX2_STATEFUL_0   0xB8
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_0  0xC0
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_1  0xC1
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_2  0xC2
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_3  0xC3
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_4  0xC4
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_5  0xC5
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_6  0xC6
#define SXD_ACL_KEY_BLOCK_FLEX2_PORT_LIST_7  0xC7
#define SXD_ACL_KEY_BLOCK_FLEX2_QOS_0        0xD0
#define SXD_ACL_KEY_BLOCK_FLEX2_QOS_1        0xD1
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_0     0xE0
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_1     0xE1
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_2     0xE2
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_3     0xE3
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_4     0xE4
#define SXD_ACL_KEY_BLOCK_FLEX2_CUSTOM_5     0xE5

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
#define SX_DBG_DUMP_PROC_DIR "dbg_dump"

#define SXD_RMFTAD_ACTIVITIES_VECTOR_SIZE 128
#define SXD_PTCEAD_ACTIVITIES_VECTOR_SIZE 128

#define NUMBER_OF_BITS_IN_BITMAP   256
#define MAX_NUM_OF_REMOTE_SWITCHES 256
#define MAX_SYSTEM_PORTS_IN_FILTER 256
#define MAX_LAG_PORTS_IN_FILTER    256
#define MAX_SYSPORT_NUM            65536
#define MAX_LAG_NUM                128
#define MAX_PHYPORT_NUM            128
#define SXD_MAX_VLAN_NUM           4096
#define MAX_PRIO_NUM               15
#define MAX_IBPORT_NUM             MAX_PHYPORT_NUM
#define MAX_LAG_MEMBERS_NUM        64
#define MAX_NUM_TRAPS_TO_REGISTER  256

#define INVALID_HW_FID_ID   0xFFFF
#define MAX_HW_FIDS_NUM     0x4000 /* 16k */
#define MAX_FIDS_NUM        MAX_HW_FIDS_NUM
#define MAX_RIFS_NUM        4000
#define MAX_MONITOR_RDQ_NUM 5

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
    SX_PKT_TYPE_MIN = SX_PKT_TYPE_ETH_CTL_UC, /**< Minimum enum value */
    SX_PKT_TYPE_MAX = SX_PKT_TYPE_LOOPBACK_CTL /**< Maximum enum value */
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
#if defined(PD_BU)
    /* Part of the PUDE WA for MLNX OS (PUDE events are handled manually):
     * - should be removed before Phoenix bring up;
     */
    CTRL_CMD_SET_PORT_ADMIN_STATUS, /**< Update port admin status */
#endif
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
    CTRL_CMD_MIN_VAL = CTRL_CMD_GET_CAPABILITIES, /**< Minimum enum value */
    CTRL_CMD_MAX_VAL = CTRL_CMD_SET_SW_IB_NODE_DESC /**< Maximum enum value */
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

    CTRL_CMD_ACCESS_REG_QSPTC, /**< Run access register QSPTC command */
    CTRL_CMD_ACCESS_REG_QSTCT, /**< Run access register QSTCT command */
    CTRL_CMD_ACCESS_REG_PTYS, /**< Run access register PTYS command */
    CTRL_CMD_ACCESS_REG_PMLP, /**< Run access register PMLP command */
    CTRL_CMD_ACCESS_REG_PLIB, /**< Run access register PLIB command */
    CTRL_CMD_ACCESS_REG_SPZR, /**< Run access register SPZR command */
    CTRL_CMD_ACCESS_REG_PPLM, /**< Run access register PPLM command */
    CTRL_CMD_ACCESS_REG_PLPC, /**< Run access register PLPC command */
    CTRL_CMD_ACCESS_REG_PMPC, /**< Run access register PMPC command */
    CTRL_CMD_ACCESS_REG_PMPR, /**< Run access register PMPR command */
    CTRL_CMD_ACCESS_REG_PMTU, /**< Run access register PMTU command */
    CTRL_CMD_ACCESS_REG_PPLR, /**< Run access register PPLR command */
    CTRL_CMD_ACCESS_REG_PELC, /**< Run access register PELC command */
    CTRL_CMD_ACCESS_REG_PFCA, /**< Run access register PFCA command */
    CTRL_CMD_ACCESS_REG_PFCNT, /**< Run access register PFCNT command */
    CTRL_CMD_ACCESS_REG_PMCR, /**< Run access register PMCR command */
    CTRL_CMD_ACCESS_REG_PFSC, /**< Run access register PFSC command */
    CTRL_CMD_ACCESS_REG_PMMP, /**< Run access register PMMP command */
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
    CTRL_CMD_ACCESS_REG_QPRT, /**< Run access register QPRT command */
    CTRL_CMD_ACCESS_REG_MFCR, /**< Run access register MFCR command */
    CTRL_CMD_ACCESS_REG_FORE, /**< Run access register FORE command */
    CTRL_CMD_ACCESS_REG_MTCAP, /**< Run access register MTCAP command */
    CTRL_CMD_ACCESS_REG_MTBR, /**< Run access register MTBR command */
    CTRL_CMD_ACCESS_REG_MTWE, /**< Run access register MTWE command */
    CTRL_CMD_ACCESS_REG_PMAOS, /**< Run access register PMAOS command */
    CTRL_CMD_ACCESS_REG_MMDIO, /**< Run access register MMDIO command */
    CTRL_CMD_ACCESS_REG_MMIA, /**< Run access register MMIA command */
    CTRL_CMD_ACCESS_REG_MFPA, /**< Run access register MFPA command */
    CTRL_CMD_ACCESS_REG_MFBE, /**< Run access register MFBE command */
    CTRL_CMD_ACCESS_REG_MFBA, /**< Run access register MFBA command */
    CTRL_CMD_ACCESS_REG_QCAP, /**< Run access register QCAP command */
    CTRL_CMD_ACCESS_REG_RAW, /**< Run access register command for a RAW register */
    CTRL_CMD_ACCESS_REG_RAW_BUFF, /**< Run access register command with a RAW buffer */
    CTRL_CMD_ACCESS_REG_MFM, /**< Run access register MFM command */
    CTRL_CMD_ACCESS_REG_SPAD, /**< Run access register SPAD command */
    CTRL_CMD_ACCESS_REG_SSPR, /**< Run access register SSPR command */
    CTRL_CMD_ACCESS_REG_SLCR_V2, /**< Run access register SLCR_V2 command */
    CTRL_CMD_ACCESS_REG_PPAD, /**< Run access register PPAD command */
    CTRL_CMD_ACCESS_REG_SPMCR, /**< Run access register SPMCR command */
    CTRL_CMD_ACCESS_REG_PBMC, /**< Run access register PBMC command */
    CTRL_CMD_ACCESS_REG_PPTB, /**< Run access register PPTB command */
    CTRL_CMD_ACCESS_REG_SMID, /**< Run access register SMID command */
    CTRL_CMD_ACCESS_REG_SPMS, /**< Run access register SPMS command */
    CTRL_CMD_ACCESS_REG_SPVID, /**< Run access register SPVID command */
    CTRL_CMD_ACCESS_REG_SPVC, /**< Run access register SPVC command */
    CTRL_CMD_ACCESS_REG_SVER, /**< Run access register SVER command */
    CTRL_CMD_ACCESS_REG_SFD, /**< Run access register SFD command */
    CTRL_CMD_ACCESS_REG_QPBR, /**< Run access register QPBR command */
    CTRL_CMD_ACCESS_REG_PLBF, /**< Run access register PLBF command */
    CTRL_CMD_ACCESS_REG_MGIR, /**< Run access register MGIR command */
    CTRL_CMD_ACCESS_REG_MHSR, /**< Run access register MHSR command */
    CTRL_CMD_ACCESS_REG_SGCR, /**< Run access register SGCR command */
    CTRL_CMD_ACCESS_REG_MSCI, /**< Run access register MSCI command */
    CTRL_CMD_ACCESS_REG_MRSR, /**< Run access register MRSR command */
    CTRL_CMD_ACCESS_REG_SBPR, /**< Run access register SBPR command */
    CTRL_CMD_ACCESS_REG_SBSR, /**< Run access register SBSR command */
    CTRL_CMD_ACCESS_REG_SBCM, /**< Run access register SBCM command */
    CTRL_CMD_ACCESS_REG_SBPM, /**< Run access register SBPM command */
    CTRL_CMD_ACCESS_REG_SBMM, /**< Run access register SBMM command */
    CTRL_CMD_ACCESS_REG_CWGCR, /**< Run access register CWGCR command */
    CTRL_CMD_ACCESS_REG_CWTP, /**< Run access register CWTP command */
    CTRL_CMD_ACCESS_REG_CWTPM, /**< Run access register CWTPM command */
    CTRL_CMD_ACCESS_REG_CWPP, /**< Run access register CWPP command */
    CTRL_CMD_ACCESS_REG_CWPPM, /**< Run access register CWPPM command */
    CTRL_CMD_ACCESS_REG_CPQE, /**< Run access register CPQE command */
    CTRL_CMD_ACCESS_REG_MPSC, /**< Run access register MPSC command */
    CTRL_CMD_ACCESS_REG_MPRS, /**< Run access register MPSC command */
    CTRL_CMD_ACCESS_REG_MLCR, /**< Run access register MLCR command */
    CTRL_CMD_ACCESS_REG_MPGCR, /**< Run access register MPGCR command */
    CTRL_CMD_ACCESS_REG_MPILM, /**< Run access register MPILM command */
    CTRL_CMD_ACCESS_REG_MPNHLFE, /**< Run access register MPNHLFE command */
    CTRL_CMD_ACCESS_REG_MRRR, /**< Run access register MRRR command */
    CTRL_CMD_ACCESS_REG_MDRI, /**< Run access register MDRI command */
    CTRL_CMD_ACCESS_REG_HTAC, /**< Run access register HTAC command */
    CTRL_CMD_ACCESS_REG_SBHBR, /**< Run access register SBHBR command */
    CTRL_CMD_ACCESS_REG_SBHRR, /**< Run access register SBHRR command */
    CTRL_CMD_ACCESS_REG_SBDCC, /**< Run access register SBDCC command */
    CTRL_CMD_ACCESS_REG_SBDCM, /**< Run access register SBDCM command */
    CTRL_CMD_ACCESS_REG_SBCTC, /**< Run access register SBCTC command */
    CTRL_CMD_ACCESS_REG_SBCTR, /**< Run access register SBCTR command */
    CTRL_CMD_ACCESS_REG_SBGCR, /**< Run access register SBGCR command */
    CTRL_CMD_ACCESS_REG_PPBMI, /**< Run access register PPBMI command */
    CTRL_CMD_ACCESS_REG_PDDR, /**< Run access register PDDR command */
    CTRL_CMD_ACCESS_REG_RGCR, /**< RGCR - tmp patch since FW needs it in Baz IB Router*/
    CTRL_CMD_ACCESS_REG_RTCA, /**< RTCA - for IB Router*/
    CTRL_CMD_ACCESS_REG_RTPS, /**< RTPS - for IB Router*/
    CTRL_CMD_ACCESS_REG_RITR, /**< RITR - for IB Router*/
    CTRL_CMD_ACCESS_REG_RUFT, /**< RUFT - for IB Router*/
    CTRL_CMD_ACCESS_REG_PPTT, /**< Run access register PPTT command */
    CTRL_CMD_ACCESS_REG_PPRT, /**< Run access register PPRT command */
    CTRL_CMD_ACCESS_REG_PPAOS, /**< Run access register PPAOS command */
    CTRL_CMD_ACCESS_REG_PCMR, /**< Run access register PCMR command */
    CTRL_CMD_ACCESS_REG_PCNR, /**< Run access register PCNR command */
    CTRL_CMD_ACCESS_REG_PPBMP, /**< Run access register PPBMP command */
    CTRL_CMD_ACCESS_REG_PPBMC, /**< Run access register PPBMC command */
    CTRL_CMD_ACCESS_REG_PPBME, /**< Run access register PPBME command */
    CTRL_CMD_ACCESS_REG_PBSR, /**< Run access register PBSR command */
    CTRL_CMD_ACCESS_REG_PTCE3, /**< Run access register PTCE_V3 command */
    CTRL_CMD_ACCESS_REG_PERPT, /**< Run access register PERPT command */
    CTRL_CMD_ACCESS_REG_PERAR, /**< Run access register PERAR command */
    CTRL_CMD_ACCESS_REG_PERCR, /**< Run access register PERCR command */
    CTRL_CMD_ACCESS_REG_PERERP, /**< Run access register PERCR command */
    CTRL_CMD_ACCESS_REG_PEABFE, /**< Run access register PEABFE command */
    CTRL_CMD_ACCESS_REG_QSLL, /**< Run access register QSLL command */
    CTRL_CMD_ACCESS_REG_QHLL, /**< Run access register QHLL command */
    CTRL_CMD_ACCESS_REG_MTPPTR, /**< Run access register MTPPTR command */
    CTRL_CMD_ACCESS_REG_QPSC, /**< Run access register QPSC command */
    CTRL_CMD_ACCESS_REG_MTPPPC, /**< Run access register MTPPPC command */
    CTRL_CMD_ACCESS_REG_MCION, /**< Run access register MCION command */
    CTRL_CMD_ACCESS_REG_MONI,  /**< Run access register MONI command */
    CTRL_CMD_ACCESS_REG_QPCR, /**< Run access register QPCR command */
    CTRL_CMD_ACCESS_REG_MIN = CTRL_CMD_ACCESS_REG_PSPA, /**< Minimum enum value */
    CTRL_CMD_ACCESS_REG_MAX = CTRL_CMD_ACCESS_REG_QPCR  /**< Maximum enum value */
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
    KU_SWID_TYPE_DISABLED = 0, /**< Disabled */
    KU_SWID_TYPE_INFINIBAND = 1, /**< IB */
    KU_SWID_TYPE_ETHERNET = 2, /**< Eth */
    KU_SWID_TYPE_ROUTER_PORT = 8, /**< RP */
    KU_SWID_TYPE_MIN = KU_SWID_TYPE_DISABLED, /**< Minimum enum value */
    KU_SWID_TYPE_MAX = KU_SWID_TYPE_ROUTER_PORT /**< Maximum enum value */
};

/**
 * ku_command_ifc_ret_status enumerated type is used to note the possible
 * return values from command IFC.
 */
enum ku_command_ifc_ret_status {
    COMMAND_IFC_RET_STATUS_OK = 0X00,             /**< OK */
    COMMAND_IFC_RET_STATUS_INTERNAL_ERROR = 0X01, /**< Internal error */
    COMMAND_IFC_RET_STATUS_BAD_OP = 0X02,         /**< Bad operation */
    COMMAND_IFC_RET_STATUS_BAD_PARAM = 0X03,      /**< Bad parameter */
    COMMAND_IFC_RET_STATUS_BAD_SYS_STATE = 0X04,  /**< Bad system state */
    COMMAND_IFC_RET_STATUS_BAD_RESOURCE = 0X05,   /**< Bad resource */
    COMMAND_IFC_RET_STATUS_RESOURCE_BUSY = 0X06,  /**< Resource busy */
    COMMAND_IFC_RET_STATUS_EXCEED_LIM = 0X08,     /**< Exceeds limitation */
    COMMAND_IFC_RET_STATUS_BAD_RES_STATE = 0X09,  /**< Bad res state */
    COMMAND_IFC_RET_STATUS_BAD_INDEX = 0X0A,      /**< Bad index */
    COMMAND_IFC_RET_STATUS_BAD_NVMEM = 0X0B,      /**< Bad NVMEM */
    COMMAND_IFC_RET_STATUS_BAD_PKT = 0X30,        /**< Bad packet */
    COMMAND_IFC_RET_STATUS_MIN = COMMAND_IFC_RET_STATUS_OK, /**< Minimum enum value */
    COMMAND_IFC_RET_STATUS_MAX = COMMAND_IFC_RET_STATUS_BAD_PKT /**< Maximum enum value */
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
    DPT_PATH_MIN = DPT_PATH_INVALID, /**< Minimum enum value */
    DPT_PATH_MAX = DPT_PATH_PCI_E /**< Maximum enum value */
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
    HTGT_LOCAL_PATH = 0, /**< Local path */
    HTGT_STACKING_PATH = 1, /**< Stacking path */
    HTGT_DR_PATH = 2, /**< Directed route path */
    HTGT_ETH_PATH = 3, /**< Ethernet path */
    HTGT_NULL_PATH = 0xF /**< NULL path */
};

typedef uint8_t sxd_boolean_t;

/**
 * sxd_port_ib_link_width_t enumerated type is used to store IB link width
 */
typedef enum sxd_port_ib_link_width {
    SXD_PORT_IB_LINK_WIDTH_1X = (1 << 0),
    SXD_PORT_IB_LINK_WIDTH_2X = (1 << 1),
    SXD_PORT_IB_LINK_WIDTH_4X = (1 << 2),
    SXD_PORT_IB_LINK_WIDTH_8X = (1 << 3),
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
    SXD_PORT_ETH_PROTOCOL_1000_BASE_KX = (1 << 1),
    SXD_PORT_ETH_PROTOCOL_10G_BASE_CX4_XAUI = (1 << 2),
    SXD_PORT_ETH_PROTOCOL_10G_BASE_KX4 = (1 << 3),
    SXD_PORT_ETH_PROTOCOL_10G_BASE_KR4 = (1 << 4),
    SXD_PORT_ETH_PROTOCOL_20G_BASE_KR2 = (1 << 5),
    SXD_PORT_ETH_PROTOCOL_40G_BASE_CR4 = (1 << 6),
    SXD_PORT_ETH_PROTOCOL_40G_BASE_KR4 = (1 << 7),
    SXD_PORT_ETH_PROTOCOL_56G_BASE_KR4 = (1 << 8),
    SXD_PORT_ETH_PROTOCOL_56G_BASE_KX4 = (1 << 9),
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
    SXD_PORT_IB_PROTOCOL_SDR = (1 << 0),
    SXD_PORT_IB_PROTOCOL_DDR = (1 << 1),
    SXD_PORT_IB_PROTOCOL_QDR = (1 << 2),
    SXD_PORT_IB_PROTOCOL_FDR10 = (1 << 3),
    SXD_PORT_IB_PROTOCOL_FDR = (1 << 4),
    SXD_PORT_IB_PROTOCOL_EDR = (1 << 5),
    SXD_PORT_IB_PROTOCOL_HDR = (1 << 6),
    SXD_PORT_IB_PROTOCOL_NDR = (1 << 7),
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
    SXD_COUNTER_SET_TYPE_NO_COUNT = 0x0,
    SXD_COUNTER_SET_TYPE_PACKET = 0x1,
    SXD_COUNTER_SET_TYPE_BYTE = 0x2,
    SXD_COUNTER_SET_TYPE_PACKET_AND_BYTE = 0x3,
    SXD_COUNTER_SET_TYPE_BYTE_STATISTICAL = 0x4,
    SXD_COUNTER_SET_TYPE_PACKET_AND_BYTE_STATISTICAL = 0x5,
    SXD_COUNTER_SET_TYPE_RIF = 0x8,
    SXD_COUNTER_SET_TYPE_RIF_BASIC = 0x9,
    SXD_COUNTER_SET_TYPE_RIF_ENHANCED = 0xA,
    SXD_COUNTER_SET_TYPE_RIF_MIXED_1 = 0xB,
    SXD_COUNTER_SET_TYPE_RIF_MIXED_2 = 0xC,
} sxd_counter_set_type_t;

/**
 * sxd_tunnel_type enumerated type is used to match tunnel type.
 */
typedef enum sxd_tunnel_type {
    SXD_TUNNEL_TYPE_NVGRE = 0,
    SXD_TUNNEL_TYPE_VXLAN = 1,
    SXD_TUNNEL_TYPE_MPLS = 2,
    SXD_TUNNEL_TYPE_IPINIP = 3,
    SXD_TUNNEL_TYPE_GRE = 4,
    SXD_TUNNEL_TYPE_NONE = 5,
} sxd_tunnel_type_t;

/**
 * sxd_nve_tubbel_type enumerated type is used to match tunnel type.
 */
typedef enum sxd_nve_tunnel_type {
    SXD_NVE_TUNNEL_TYPE_VXLAN = (1 << 0),
    SXD_NVE_TUNNEL_TYPE_GENEVE = (1 << 1),
    SXD_NVE_TUNNEL_TYPE_GRE = (1 << 2),
    SXD_NVE_TUNNEL_TYPE_NVGRE = (1 << 3),
} sxd_nve_tunnel_type_t;

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
    KU_PORT_VLAN_PARAMS_TYPE_PORT = 1,
    KU_PORT_VLAN_PARAMS_TYPE_LAG = 2,
    KU_PORT_VLAN_PARAMS_TYPE_VLAN = 3,
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
    KU_RES_ID_KVD_SIZE = 0x1001,
    KU_RES_ID_KVD_SINGLE_MIN_SIZE = 0x1002,
    KU_RES_ID_KVD_DOUBLE_MIN_SIZE = 0x1003,
    KU_RES_ID_CAP_MAX_SWIDS = 0x2001,
    KU_RES_ID_CAP_MAX_SWITCH_PORTS = 0x2002,
    KU_RES_ID_MAX_TRAP_GROUPS = 0x2201,
    KU_RES_ID_COUNTER_POOL_SIZE = 0x2410,
    KU_RES_ID_MAX_SPAN = 0x2420,
    KU_RES_ID_COUNTER_SIZE_PACKETS_BYTES = 0x2443,
    KU_RES_ID_COUNTER_SIZE_ROUTER_BASIC = 0x2449,
    KU_RES_ID_MAX_SYSTEM_PORT = 0x2502,
    KU_RES_ID_MAX_LAG = 0x2520,
    KU_RES_ID_MAX_LAG_MEMBERS = 0x2521,
    KU_RES_ID_MAX_BUFFER_SIZE = 0x2802,
    KU_RES_ID_CELL_SIZE = 0x2803,
    KU_RES_ID_ACL_MAX_TCAM_REGIONS = 0x2901,
    KU_RES_ID_ACL_MAX_TCAM_RULES = 0x2902,
    KU_RES_ID_ACL_MAX_REGIONS = 0x2903,
    KU_RES_ID_ACL_MAX_GROUPS = 0x2904,
    KU_RES_ID_ACL_MAX_GROUP_SIZE = 0x2905,
    KU_RES_ID_ACL_FLEX_KEYS = 0x2910,
    KU_RES_ID_ACL_MAX_ACTION_PER_RULE = 0x2911,
    KU_RES_ID_ACL_ACTIONS_PER_SET = 0x2912,
    KU_RES_ID_MAX_CPU_POLICERS = 0x2A13,
    KU_RES_ID_MAX_VRS = 0x2C01,
    KU_RES_ID_MAX_RIFS = 0x2C02,
    KU_RES_ID_MAX_LPM_TREES = 0x2C30,

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
    USER_CHANNEL_L3_NETDEV = 0,
    USER_CHANNEL_LOG_PORT_NETDEV = 1,
    USER_CHANNEL_PHY_PORT_NETDEV = 2,
    NUM_OF_NET_DEV_TYPE
};


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
    SXD_CHIP_TYPE_UNKNOWN = 0,
    SXD_CHIP_TYPE_SWITCHX_A2 = 1,
    SXD_CHIP_TYPE_SWITCHX_A1 = 3,
    SXD_CHIP_TYPE_SWITCHX_A0 = 4,
    SXD_CHIP_TYPE_SWITCH_IB = 5,
    SXD_CHIP_TYPE_SPECTRUM = 6,
    SXD_CHIP_TYPE_SWITCH_IB2 = 7,
    SXD_CHIP_TYPE_SPECTRUM_A1 = 8,
    SXD_CHIP_TYPE_SPECTRUM2 = 9,
    SXD_CHIP_TYPE_QUANTUM = 10,
    SXD_CHIP_TYPES_MAX
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
    unsigned int                      pci_id; /**< pci_id - PCI ID */
    void __attribute__((aligned(8))) *sx_dev; /**< sx_dev - SX device pointer */
};

/**
 * ku_dpt_path_info union is used to store the path
 * info in the DPT.
 */
union ku_dpt_path_info {
    struct ku_dpt_i2c_info   sx_i2c_info; /**< sx_i2c_info - I2C info */
    struct ku_dpt_pcie_info  sx_pcie_info; /**< sx_pcie_info - PCI info */
    struct ku_dpt_sgmii_info sx_sgmii_info; /**< sx_sgmii_info - PCI info */
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

/**
 * ku_read structure is used to store the read
 * info.
 */
struct ku_read {
    uint16_t system_port; /**< system_port - system port on which the packet was received */
    uint16_t trap_id;  /**< trap_id - TrapID(=syndrome id) that captured the packet */
    uint8_t  is_lag; /**< is_lag - was the packet received from a port which is a LAG */
    uint8_t  lag_subport; /**< lag_subport - For LAGs this field describe the port index within the LAG */
    uint8_t  swid; /**< swid - swid */
    uint32_t original_packet_size; /**<the original size of packet,
                                    *        if packet wasn't truncated packet_size=original_packet_size*/
    uint8_t                                          has_timestamp; /**< does packet have timestamp */
    uint32_t                                         user_def_val; /**< for ACL trap id describe acl user ID */
    uint16_t                                         dest_sysport; /**< Destination sysport (for mirrored packets) */
    uint8_t                                          dest_is_lag; /**< Destination is LAG port */
    uint8_t                                          dest_lag_subport; /**< For LAG destination port: index within LAG */
    uint64_t __attribute__((aligned(8)))             length; /**< length - packet size (if 0 - no more packets) */
    struct   ku_timespec __attribute__((aligned(8))) timestamp; /**< timestamp of packet */
};

/**
 * loopback_data structure is used to store the data of a sent loopback packet.
 */
struct loopback_data {
    uint16_t trap_id;    /**< trap_id - the trap ID in case of a loopback packet */
    uint8_t  is_lag;    /**< is the system port member of a lag. */
    uint8_t  lag_subport;    /**< lag sub-port when applicable */
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
};

/**
 * ku_raise_trap structure is used to store the raise trap ioctl info
 */
struct ku_raise_trap {
    uint16_t                          trap_id; /**< trap_id - the trap ID */
    uint32_t                          buffer_size; /**< buffer_size - the buffer size */
    uint8_t                           swid; /**< swid - switch partition ID */
    uint16_t                          sysport; /**< sysport - system port or LAG ID */
    uint8_t                           is_lag; /**< is the source logical port member of a lag. */
    uint8_t                           lag_subport; /**< source lag port when applicable */
    void __attribute__((aligned(8))) *buffer_p;    /**< buffer_p - a pointer to the buffer */
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
 * ku_user_channel_type enumerated type is used to note the possible user channels types.
 */
enum ku_user_channel_type {
    SX_KU_USER_CHANNEL_TYPE_FD,
    SX_KU_USER_CHANNEL_TYPE_L3_NETDEV,
    SX_KU_USER_CHANNEL_TYPE_L2_NETDEV,
    SX_KU_USER_CHANNEL_TYPE_PHY_NETDEV,
    SX_KU_USER_CHANNEL_TYPE_L2_TUNNEL
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
    union ku_filter_critireas  critireas;  /**< critireas - additional filter critireas  */
    enum ku_user_channel_type  channel_type;  /**< channel_type - channel type */
    struct ku_l2_tunnel_params l2_tunnel_params;  /**< l2_tunnel_params - L2 tunnel parameters when channel type is L2 tunnel */
    struct ku_port_vlan_params port_vlan_params;  /**< port / vlan parameters for per port registration*/
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
    SXD_CHIP_REV_A0 = 1 << 1,
    SXD_CHIP_REV_A1 = 1 << 2,
    SXD_CHIP_REV_A2 = 1 << 3,
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
    int     rdq;    /**< rdq - RDQ */
    uint8_t enable; /**< enable - 0-disable, 1-enable */
};

/**
 * ku_rdq_cpu_priority structure is used to set priority to LOW/HIGH depends on HW policer existence
 */
struct ku_rdq_cpu_priority {
    int     rdq;    /**< rdq - RDQ */
    uint8_t high_prio; /**< 1=high priority, 0=low priority */
};

/**
 * ku_set_truncate_params structure is used to store the per RDQ truncate parameters
 */
struct ku_set_truncate_params {
    int      rdq;    /**< rdq - the RDQ */
    uint8_t  truncate_enable;    /**< truncate_enable - Should packets received on this RDQ be truncated */
    uint16_t truncate_size;    /**< truncate_size - The Maximum size of the truncated packets */
};

/**
 * ku_set_truncate_params structure is used to set RDQ is_monitor mode
 */
struct ku_set_monitor_rdq_params {
    int     rdq;            /**< rdq - the RDQ */
    uint8_t is_monitor;     /**< is_monitor: 1 - RDQ is Monitor RDQ , 0 - RDQ is generic RDQ */
    uint8_t cpu_tclass;
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
    uint8_t                              dev_id; /**< dev_id - Device ID */
    unsigned int                         address; /**< address - Address to read from */
    int                                  size; /**< size - size in bytes to read */
    uint8_t __attribute__((aligned(8))) *data;   /**< data - Buffer to read into */
};

/**
 * ku_cr_space_write structure is used to store the CR space write parameters
 */
struct ku_cr_space_write {
    uint8_t                              dev_id; /**< dev_id - Device ID */
    unsigned int                         address; /**< address - Address to write to */
    int                                  size; /**< size - size in bytes to write */
    uint8_t __attribute__((aligned(8))) *data;   /**< data - Data to write */
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
    uint8_t                              dev_id; /**< dev_id - device id */
    uint64_t __attribute__((aligned(8))) frc_offset;
    uint8_t                              frc_bar;
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
 * ku_query_board_info structure is used to store the query board info parameters
 */
struct ku_query_board_info {
    uint16_t vsd_vendor_id;    /**< vsd_vendor_id - PCISIG Vendor ID */
    char     board_id[SX_BOARD_ID_LEN];    /**< board_id - The board id string */
    uint8_t  dev_id;    /**< dev_id - device id */
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
 * ku_ptys_reg structure is used to store the PTYS register parameters
 */
struct ku_ptys_reg {
    sxd_port_an_disable_cap_t     an_disable_cap;       /** an_disable_cap - Auto Negotiation disable capability (device supports/does not support) */
    sxd_port_an_disable_admin_t   an_disable_admin;       /** an_disable_admin - Auto Negotiation disable */
    sxd_port_force_tx_aba_param_t force_tx_aba_param;       /** force_tx_aba_param - When set, use ABA parameters on TX when in force operation */
    uint8_t                       local_port;       /**< local_port - local port number */
    uint8_t                       proto_mask;       /**< proto_mask - protocol mask */
    sxd_port_an_status_t          an_status;       /** an_status - Auto Negotiation status */
    uint16_t                      data_rate_oper;       /** Port data rate in resolution of 100 Mb/s (0x0 = field unsupported) */
    sxd_port_eth_proto_t          eth_proto_capability;       /**< eth_proto_capability - Ethernet port speed/protocols supported (bitmask) */
    uint32_t                      ext_eth_proto_capability;       /**< ext_eth_proto_capability - Extended Ethernet port speed/protocols supported (bitmask) */
    sxd_port_ib_link_width_t      ib_link_width_capability;       /** ib_link width - IB port link width (bitmask) */
    sxd_port_ib_proto_t           ib_proto_capability;       /**< ib_proto_capability - IB port speed/protocols supported (bitmask) */
    uint32_t                      eth_proto_admin;       /**< eth_proto_admin - Ethernet port speed/protocols bitmask */
    uint32_t                      ext_eth_proto_admin;       /**< ext_eth_proto_admin - Extended Ethernet port speed/protocols bitmask */
    uint16_t                      ib_link_width_admin;       /** ib_link_width_admin - InfiniBand port link width bitmask */
    uint16_t                      ib_proto_admin;       /**< ib_proto_admin - IB port speed/protocols bitmask */
    uint32_t                      eth_proto_oper;       /**< eth_proto_oper - Ethernet port speed/protocols bitmask */
    uint32_t                      ext_eth_proto_oper;       /**< ext_eth_proto_oper - Extended Ethernet port speed/protocols bitmask */
    uint16_t                      ib_link_width_oper;       /** ib_link_width_oper - InfiniBand port link width bitmask */
    uint16_t                      ib_proto_oper;       /**< ib_proto_oper - IB port speed/protocols bitmask */
    sxd_port_connector_type_t     connector_type;       /** connector_type - connector type */
    uint32_t                      eth_proto_lp_advertise;       /** eth_proto_lp_advertise - Ethernet port's link partner advertised protocols */
};

/**
 * mhsr_health_mode enumerated type is used to note the MHSR health state.
 */
enum mhsr_health_mode {
    MHSR_HEALTH_MODE_FAILURE = 0,
    MHSR_HEALTH_MODE_RESERVED = 1,
    MHSR_HEALTH_MODE_NORMAL_OPERATION = 2,
    MHSR_HEALTH_MODE_DEFAULT_STATE = 3,      /*boot/init*/
    MHSR_HEALTH_MODE_MIN = MHSR_HEALTH_MODE_FAILURE,
    MHSR_HEALTH_MODE_MAX = MHSR_HEALTH_MODE_DEFAULT_STATE,
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
    PROFILE_FLOOD_MODE_TYPE_USE_FID = 1,
    PROFILE_FLOOD_MODE_TYPE_USE_VID = 2,
    PROFILE_FLOOD_MODE_TYPE_MIXED_MODE = 3,
    PROFILE_FLOOD_MODE_TYPE_CONTROL_MODE = 4,
    PROFILE_FLOOD_MODE_TYPE_MAX,
};

typedef enum sxd_sftr_table_type {
    SXD_SFTR_TABLE_TYPE_ANY_TYPE_E = 0x0,
    SXD_SFTR_TABLE_TYPE_FID_E = 0x4
} sxd_sftr_table_type_t;

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
    uint16_t                 ports_bitmap[0x000000FF + 1];
    uint16_t                 mask_bitmap[0x000000FF + 1];
};

/**
 * ku_svpe_reg structure is used to store the SVPE register parameters
 */
struct ku_svpe_reg {
    uint8_t local_port; /** local_port - Local port number */
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
 * sx_fdb_flush_type enumerated type is used to note FDB
 * flush type.
 */
enum fdb_flush_type {
    FDB_FLUSH_TYPE_SWID = 0,
    FDB_FLUSH_TYPE_FID = 1,
    FDB_FLUSH_TYPE_PORT = 2,
    FDB_FLUSH_TYPE_PORT_FID = 3,
    FDB_FLUSH_TYPE_LAG = 4,
    FDB_FLUSH_TYPE_LAG_FID = 5,
    FDB_FLUSH_TYPE_NVE = 6,
    FDB_FLUSH_TYPE_NVE_FID = 7
};

/**
 * ku_sfdf_reg structure is used to store the SFDF register parameters
 */
struct ku_sfdf_reg {
    uint8_t             swid; /** swid - Switch partition ID */
    enum fdb_flush_type flush_type; /** flush_type - Flush type */
    uint16_t            fid; /** fid - FDB ID */
    union {
        uint16_t system_port;
        uint16_t lag_id;
    } lag_port; /** lag_port - System port or lag id*/
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
    uint8_t sub_port; /** sub_port - Virtual port within the physical port */
    uint8_t learn_enable; /** learn_enable - Enable learning on this port */
};

/**
 * ku_spfsr_reg structure is used to store the SPFSR register parameters
 */
struct ku_spfsr_reg {
    uint8_t local_port; /** local_port - local port number */
    uint8_t security;   /** security   - Enable security checks on this port */
};

/**
 * ku_smid_reg structure is used to store the SMID register parameters
 */
struct ku_smid_reg {
    uint8_t  swid; /** swid - Switch partition ID */
    uint16_t mid; /** mid - Multicast Identifier */
    uint16_t ports_bitmap[0x000000FF + 1]; /** ports_bitmap - Local port <i> sub port <j> membership */
    uint16_t mask_bitmap[0x000000FF + 1]; /** mask_bitmap - Local port <i> sub port <j> mask */
    uint8_t  op; /** op - op == 0 legacy (SET), op == 1 CLEAR ALL*/
    uint8_t  smpe_valid; /** smpe_valid - SMPE validity bit */
    uint16_t smpe; /** smpe - Switch Multicast Port Egress */
};

/**
 * ku_smpu_reg structure is used to store the SMPU register parameters
 */
struct ku_smpu_reg {
    uint8_t  swid; /** swid - Switch partition ID */
    uint8_t  local_port; /** local_port - Local port to send the packet */
    uint8_t  op; /** Operation - 00 - Set bit, 01 - Clear bit */
    uint8_t  size; /** size - Number of valid MIDs to be updated. */
    uint16_t mid[255]; /** MID list to where the relevant
                        *   local_port bit indication is to be set / cleared. */
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
    uint8_t            num_rec; /** number of VLAN learm_mode records    */
    spvmlr_vlan_data_t vlan_data[SPVMLR_MAX_RECORDS];
};

/**
 * sxd_flow_counter_op enumerated type is used to note the
 * PFCA operation.
 */
enum sxd_flow_counter_op {
    SXD_PFCA_OP_NOP = 0,
    SXD_PFCA_OP_ALLOCATE = 1,
    SXD_PFCA_OP_TEST = 2,
    SXD_PFCA_OP_FREE = 3,
};


/**
 * spgt_operation enumerated type is used to note the SPGT operation.
 */
enum spgt_operation {
    SPGT_OPERATION_ADD = 0,
    SPGT_OPERATION_DELETE = 1,
    SPGT_OPERATION_EDIT = 2,
};

/**
 * ku_spgt_reg structure is used to store the SPGT register parameters
 */
struct ku_spgt_reg {
    enum spgt_operation operation;
    uint16_t            pgi;
    uint16_t            ports_bitmap[0x000000FF + 1];
    uint16_t            mask_bitmap[0x000000FF + 1];
};

/**
 * sfn_type enumerated type is used to note the SFN data type.
 */
enum sfn_type {
    SFN_TYPE_LEARNT_MAC = 5,
    SFN_TYPE_LEARNT_MAC_LAG = 6,
    SFN_TYPE_LEARNT_UNICAST_TUNNEL = 0xD,
    SFN_TYPE_AGED_MAC = 7,
    SFN_TYPE_AGED_MAC_LAG = 8,
    SFN_TYPE_AGED_UNICAST_TUNNEL = 0xE,
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
    SFD_TYPE_UNICAST = 0,
    SFD_TYPE_UNICAST_LAG = 1,
    SFD_TYPE_MULTICAST = 2,
    SFD_TYPE_LEARNT_MAC_E = 5,
    SFD_TYPE_LEARNT_MAC_LAG_E = 6,
    SFD_TYPE_AGED_MAC_E = 7,
    SFD_TYPE_AGED_MAC_LAG_E = 8,
    SFD_TYPE_UNICAST_TUNNEL = 0xC,
    SFD_TYPE_LEARNT_MAC_TUNNEL_E = 0xD,
    SFD_TYPE_AGED_MAC_TUNNEL_E = 0xE,
    SFD_TYPE_MULTICAST_TUNNEL = 0xF,
};

/**
 * sfd_operation enumerated type is used to note the SFD operation.
 */
enum sfd_operation {
    SFD_OPERATION_DUMP_FDB = 0,
    SFD_OPERATION_QUERY = 1,
    SXD_OPERATION_QUERY_AND_CLEAR_ACTIVITY = 2,
    SFD_OPERATION_TEST = 0,
    SFD_OPERATION_ADD = 1,
    SFD_OPERATION_DELETE = 2,
    SXD_OPERATION_REMOVE_NOTIFICATION = 3,
};

/**
 * sfd_policy enumerated type is used to note the SFD data replace policy.
 */
enum sfd_policy {
    SFD_POLICY_STATIC = 0,
    SFD_POLICY_DYNAMIC_REMOTE = 1,
    SFD_POLICY_DYNAMIC_AGEABLE = 3,
    SFD_POLICY_INVALID = -1,
};

/**
 * sfd_action enumerated type is used to note the SFD frame
 * action.
 */
enum sfd_action {
    SFD_ACTION_FORWARD_ONLY = 0,
    SFD_ACTION_FORWARD_AND_TRAP = 1,
    SFD_ACTION_TRAP_ONLY = 2,
    SFD_ACTION_FORWARD_TO_IP_ROUTER = 3,
    SFD_ACTION_FORWARD_TO_FCF = 4,
    SFD_ACTION_DISCARD = 15,
    SFD_ACTION_INVALID = -1,
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
    struct sx_ether_addr mac; /**< mac - Base MAC address */
    uint8_t              activity;
    uint16_t             mid;
    uint16_t             fid;
    uint8_t              action;
    uint32_t             underlay_mc_ptr;
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
    union {
        struct sfd_unicast_data     uc;
        struct sfd_unicast_lag_data uc_lag;
        struct sfd_multicast_data   mc;
        struct sfd_uc_tunnel_data   uc_tunnel;
        struct sfd_mc_tunnel_data   mc_tunnel;
    } sfd_data_type[SFD_MAX_RECORDS];
};

/**
 * ku_sfdat_reg structure is used to store the SFDAT register parameters
 */
struct ku_sfdat_reg {
    uint8_t  swid; /**< swid - Switch partition ID */
    uint32_t age_time; /**< age_time - Aging time in seconds */
};

/**
 * ku_spaft_reg structure is used to store the SPAFT register parameters
 */
struct ku_spaft_reg {
    uint8_t local_port; /**< local_port - Chip local port ID */
    uint8_t sub_port; /**< sub_port - VEPA channel on Local Port */
    uint8_t allow_untagged; /**< allow_untagged - When set, untagged frames on the ingress are admitted */
    uint8_t allow_priotagged; /**< allow_priotagged - When set, priority tagged frames on the ingress are admitted */
    uint8_t allow_tagged; /**< allow_tagged - When set, tagged frames on the ingress are admitted */
};

/**
 * spvm_vlan_data structure is used to store SPVM vlan data
 * vlan data.
 */
struct spvm_vlan_data {
    uint8_t  ingress_membership; /**< ingress_membership - Ingress membership in VLAN ID vid<i> */
    uint8_t  egress_membership; /**< egress_membership - Egress membership in VLAN ID vid<i> */
    uint8_t  untagged_membership; /**< untagged_membership - Untagged - port is an untagged member - egress transmission uses untagged frames on VID<i> */
    uint16_t vid; /** VLAN ID to be added/removed from port or for querying */
};

/**
 * ku_spvm_reg structure is used to store the SPVM register parameters
 */
struct ku_spvm_reg {
    uint8_t               prio_tagged; /** untagged packets are being transmitted untagged OR priority-tagged */
    uint8_t               local_port; /**< local_port - Chip local port ID */
    uint8_t               sub_port; /**< sub_port - VEPA channel on Local Port */
    uint8_t               num_vlans; /**< num_vlans - Number of records to update. Each record contains: i, e, u, vid */
    struct spvm_vlan_data vlan_data[256]; /**< vlan_data - VLAN data */
};

/**
 * ku_spvid_reg structure is used to store the SPVID register parameters
 */
struct ku_spvid_reg {
    uint8_t  tport;
    uint8_t  local_port; /**< local_port - Chip local port ID */
    uint8_t  egr_et_set;
    uint8_t  sub_port; /**< sub_port - VEPA channel on Local Port */
    uint8_t  et_vlan;  /**< EtherType used for when VLAN is pushed at ingress - 0 - Ethertype0 (default), 1 - Ethertype1 */
    uint16_t port_default_vid; /**< port_default_vid - Port default VID (default PVID is 001h) */
};

#define SXD_ETHERTYPE_MAX_COUNT (3)

/**
 * ku_spvc_reg structure is used to store the SPVC register parameters
 */
struct ku_spvc_reg {
    uint8_t local_port;      /**< local_port - Chip local port ID */
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


/**
 * ku_spvtr_reg structure is used to store the SPVTR register parameters
 */
struct ku_spvtr_reg {
    uint8_t tport;
    uint8_t sub_port; /**< sub_port - VEPA channel on Local Port. */
    uint8_t local_port; /**< local_port - Chip local port ID */
    uint8_t ipprio_enable; /**< ipprio_enable - set to 1 to configure ipprio_mode */
    uint8_t ipvid_enable;  /**< ipvid_enable - set to 1 to configure ipvid_mode */
    uint8_t epvid_enable;  /**< epvid_enable - set to 1 to configure epvid_mode */
    uint8_t ipprio_mode; /**< ipprio_mode - Ingress Port Priority Mode */
    uint8_t epvid_mode; /**< epvid_mode - Egress Port VLAN-ID Mode */
    uint8_t ipvid_mode; /**< ipvid_mode - Ingress Port VLAN-ID Mode */
};

/**
 * ku_pifr_reg structure is used to store the PIFR register parameters
 */
struct ku_pifr_reg {
    uint8_t local_port; /**< local_port - Chip local port ID */
    uint8_t ports_bitmap[0x000000FF + 1]; /**< 1 = filter packets coming from port[i], 0 = don't filter */
    uint8_t mask_bitmap[0x000000FF + 1];  /**< 1 = set port[i], 0 = don't set */
};

/**
 * ku_sspr_reg structure is used to store the SSPR register parameters
 */
struct ku_sspr_reg {
    uint8_t  is_master; /**< is_master - if set then this record describes the Master System Port */
    uint8_t  local_port; /**< local_port - Chip local port ID */
    uint8_t  sub_port; /**< sub_port - VEPA channel on Local Port */
    uint16_t system_port; /**< system_port - Multi SwitchX environment port ID */
};

/**
 * ku_scar_reg structure is used to store the SCAR register parameters
 */
struct ku_scar_reg {
    uint8_t log2_fdb_size; /**< log2_fdb_size - Capability: Log (base2) of the maximum FDB entries that are supported by the device */
};

/**
 * ku_sgcr_reg structure is used to store the SGCR register parameters
 */
struct ku_sgcr_reg {
    uint8_t llb; /**< llb - Link Local Broadcast  */
};
enum spms_mstp_state {
    SPMS_MSTP_STATE_DISCARDING = 1,
    SPMS_MSTP_STATE_LEARNING = 2,
    SPMS_MSTP_STATE_FORWARDING = 3,
};

/**
 * ku_spms_reg structure is used to store the SPMS register parameters
 */
struct ku_spms_reg {
    uint8_t              local_port; /**< local_port - local port number */
    enum spms_mstp_state state[4096]; /**< state - MSTP/RSTP State on VID<i> */
};
struct mpat_encap_local_eth {
    uint8_t tclass;
};
struct mpat_encap_remote_eth_vlan {
    uint8_t  tclass;
    uint16_t vid;
    uint8_t  pcp;
    uint8_t  dei;
    uint8_t  vlan_ethertype_id;
};
struct mpat_encap_remote_eth_l2 {
    uint8_t  swid;
    uint8_t  tclass;
    uint16_t vid;
    uint8_t  pcp;
    uint8_t  tp;
    uint8_t  mac[6];
    uint8_t  dei;
    uint8_t  vlan_ethertype_id;
    uint8_t  version;
    uint8_t  dpa;
};
struct mpat_encap_local_ib {
    uint8_t vl;
};
struct mpat_encap_remote_ib {
    uint8_t vl;
    uint8_t slid;
    uint8_t dlid;
    uint8_t sl;
};
struct mpat_encap_remote_eth_l3 {
    uint8_t  swid;
    uint8_t  tclass;
    uint16_t vid;
    uint8_t  pcp;
    uint8_t  tp;
    uint8_t  mac[6];
    uint8_t  dei;
    uint8_t  vlan_ethertype_id;
    uint8_t  version;
    uint8_t  dpa;
    uint8_t  protocol;
    uint8_t  smac[6];
    uint32_t dip[4];
    uint32_t sip[4];
    uint8_t  dscp;
    uint8_t  ecn;
    uint8_t  ttl;
};

/**
 * SPAN session type format
 */
union mpat_encapsulation {
    struct mpat_encap_local_eth       local_eth;
    struct mpat_encap_remote_eth_vlan remote_eth_vlan;
    struct mpat_encap_remote_eth_l2   remote_eth_l2;
    struct mpat_encap_local_ib        local_ib;
    struct mpat_encap_remote_ib       remote_ib;
    struct mpat_encap_remote_eth_l3   remote_eth_l3;
};

/**
 * ku_mpat_reg structure is used to store the MPAT register
 * parameters
 */
struct ku_mpat_reg {
    uint8_t                              pa_id; /**< pa_id - port analyzer id */
    uint8_t                              mngr_type; /**<  mngr_type - Manager Type*/
    uint16_t                             system_port; /**< system_port  */
    uint8_t                              e; /**<  e - indicating the Port Analyzer it enabled */
    uint8_t                              c; /**<  c - clear counters */
    uint8_t                              qos; /**< qos - quality of service mode */
    uint8_t                              be; /**< be- Best Effort traffic handling */
    uint8_t                              tr; /**<  tr - truncate the packet to truncate size */
    uint8_t                              stclass; /**< stclass - Stacking TClass */
    uint8_t                              span_type; /**<  SPAN Type */
    uint16_t                             truncation_size; /**< truncation_size - granularity 4 */
    union mpat_encapsulation             encap; /**<  Remote SPAN encapsulation */
    uint64_t __attribute__((aligned(8))) buffer_drop; /**< packet drops due to buffer size */
    uint64_t __attribute__((aligned(8))) be_drop; /**< packet drops due to best effort */
    uint64_t __attribute__((aligned(8))) wred_drop; /**< packet drops due to WRED */
};

typedef enum sxd_span_sbib_buff_status {
    SXD_SBIB_MIRROR_BUFF_STATUS_NOT_REACH_SIZE_E = 0,
    SXD_SBIB_MIRROR_BUFF_STATUS_REACH_SIZE_E = 1
} sxd_span_sbib_buff_status_t;

/**
 * ku_sbib_reg structure is used to store the SBIB register parameters
 */
struct ku_sbib_reg {
    uint8_t  type;      /**< type 0- Internal buffer allocated (Other values not supported) */
    uint8_t  local_port;    /**< local_port  */
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
    uint8_t  sub_port; /**< sub_port   */
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
    uint16_t lag_id; /**< lag_id - LAG Identifier. Index into the LAG Descriptor table */
    uint8_t  port_index; /**< port index - port index in the LAG list.*/
};

/**
 * ku_slcr_reg structure is used to store the SLCR register parameters
 */
struct ku_slcr_reg {
    uint8_t  sh; /**< sh - Symmetric Hash */
    uint8_t  hash_type; /**< hash_type - Hash Type */
    uint32_t hash_configuration; /**< hash_configuration - LAG Hashing Configuration */
    uint32_t seed; /**< seed - LAG seed value */
};

/**
 * ku_slcr_v2_reg structure is used to store the SLCR_V2 register parameters
 */

typedef enum slcr_v2_hash_type {
    SXD_SLCR_V2_HASH_TYPE_CRC = 0,
    SXD_SLCR_V2_HASH_TYPE_XOR = 1,
    SXD_SLCR_V2_HASH_TYPE_RANDOM = 2,
    SXD_SLCR_V2_HASH_TYPE_CRC2 = 3,   /* For Spectrum-2 and on */
} slcr_v2_hash_type_e;

typedef struct ku_slcr_v2_reg {
    uint8_t             pp; /**< pp - Per Port Configuration */
    uint8_t             local_port; /**< local_port - local port number */
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
    SLDR_OPERATION_CREATE_LAG = 0,
    SLDR_OPERATION_DESTROY_LAG = 1,
    SLDR_OPERATION_ADD_PORT_LIST = 2,
    SLDR_OPERATION_DEL_PORT_LIST = 3,
    SLDR_OPERATION_LAG_REDIRECT = 4,
    SLDR_OPERATION_FINE_GRAIN_LAG_ENABLE = 5,
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
    uint8_t sub_port; /**< sub_port - Virtual port within the physical port. */
    uint8_t color; /**< color - 0-green, 1-yellow, 2-red */
    uint8_t default_priority; /**< default_priority - Default Port priority (default 0) */
};

/**
 * ku_qsptc_reg structure is used to store the QSPTC register parameters
 */
struct ku_qsptc_reg {
    uint8_t local_iport; /**< local_iport - local ingress port number (must be stacking port) */
    uint8_t local_eport; /**< local_eport - local egress port number (must be stacking port) */
    uint8_t itclass; /**< itclass - Received tclass */
    uint8_t tclass; /**< tclass - Regenerated stacking traffic class for received packet on stacking port */
};

/**
 * ku_qtct_reg structure is used to store the QTCT register parameters
 */
struct ku_qtct_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t sub_port; /**< sub_port - Virtual port within the physical port. */
    uint8_t priority; /**< priority - Priority */
    uint8_t traffic_class; /**< traffic_class - Traffic class used for priority=<prio> */
};

/**
 * ku_cnct_reg structure is used to store the CNCT register parameters
 */
struct ku_cnct_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t prio; /**< priority - Priority */
    uint8_t enable_congestion_notif_valid; /**< enable write operation into enable_congestion_notif */
    uint8_t enable_congestion_notif; /**< disable/enable congestion notification for this egress port */
    uint8_t keep_cn_tags_valid; /**< enable write operation into keep_cn_tags */
    uint8_t keep_cn_tags; /**< keep/remove CNTags on frames egressing to this port */
};


/**
 * ku_cpid_reg structure is used to store the CPID register parameters
 */
struct ku_cpid_reg {
    uint8_t                              local_port; /**< local_port - local port number */
    uint8_t                              prio; /**< priority - Priority */
    uint64_t __attribute__((aligned(8))) cpid; /**< IEEE 802.1Qau Congestion Point Identifier */
};

/**
 * sxd_cpcs_operation enumerated type is used to note the
 * CPCS operation type.
 */
enum sxd_cpcs_operation {
    SXD_CPCS_OP_SET = 0,
    SXD_CPCS_OP_GET = 1,
};


/**
 * ku_cpcs_reg structure is used to store the CPCS register parameters
 */
struct ku_cpcs_reg {
    enum sxd_cpcs_operation operation;
    uint8_t                 traffic_class; /**< Traffic Class */
    uint32_t                set_point; /**< The set point for the queue, */
    int32_t                 cp_weight; /**< The weight (cpW) of the congestion point */
    uint32_t                cp_sample_base; /**< The minimum number of octets to enqueue in the CPs queue between CNM PDU transmissions */
    uint32_t                cp_min_header_octets; /**< The minimum number of octets that the CP is to return in the Encapsulated MSDU field ( */
};


/**
 * ku_cnmc_reg structure is used to store the CNMC register parameters
 */
struct ku_cnmc_reg {
    uint8_t prio; /**< priority - Priority */
};

/**
 * ets_tc_conf structure is used to store the QETCR register per tc parameters
 */
struct ets_tc_conf {
    uint8_t group_update; /**< group_update - Group Update */
    uint8_t bw_update; /**< bw_update - Bandwidth Allocation Update */
    uint8_t rate_update; /**< rate_update - Rate Limit Update */
    uint8_t group; /**< group - TCG assigned to traffic class tc */
    uint8_t bw_allocation; /**< bw_allocation - The percentage of bandwidth guaranteed to traffic class tc within its TCG */
    uint8_t max_bw_units; /**< max_bw_units - The maximal bandwidth allowed for the use Ttraffic class tc */
    uint8_t max_bw_value; /**< max_bw_value - The maximal bandwidth allowed for the use Ttraffic class tc */
};

/**
 * ets_global_shaper_conf structure is used to store the QETCR register global shaper parameters
 */
struct ets_global_shaper_conf {
    uint8_t rate_update; /**< rate_update - Rate Limit Update */
    uint8_t max_bw_units; /**< max_bw_units - The maximal bandwidth units for the use of Global Shaper */
    uint8_t max_bw_value; /**< max_bw_value - The maximal bandwidth value for the use of Global Shaper */
};

/**
 * ku_qegcs_reg structure is used to store the QEGCS register parameters
 */
struct ku_qegcs_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t group_0_7_arbiter;
    uint8_t group_15_arbiter;
    uint8_t global_arbiter;
};

/**
 * ku_qetcr_reg structure is used to store the QETCR register parameters
 */
struct ku_qetcr_reg {
    uint8_t                       local_port; /**< local_port - local port number */
    struct ets_tc_conf            tc_conf[8]; /**< tc_conf - Per-tclass configuration */
    struct ets_global_shaper_conf global_shaper; /**< global_shaper - Global Shaper configuration */
};

/**
 * ku_qpfcr_reg structure is used to store the QPFCR register parameters
 */
struct ku_qpfcr_reg {
    uint8_t local_port;
    uint8_t traffic_class;
    uint8_t traffic_class_group;
    uint8_t min_threshold;
    uint8_t max_threshold;
};

/**
 * ku_qdpm_reg structure is used to store the QDPM register parameters
 */
struct ku_qdpm_reg {
    uint8_t dscp_update[DSCP_CODES_NUMBER];    /**< dscp_update - whether to update this DSCP mapping in HW */
    uint8_t color[DSCP_CODES_NUMBER]; /**< color mapping per DSCP value */
    uint8_t priority[DSCP_CODES_NUMBER];       /**< priority mapping per DSCP value - Priority */
};

/**
 * ku_qpcr_reg structure is used to store the QPCR register parameters
 */
struct ku_qpcr_reg {
    uint8_t port; /**< port - Policer port number */
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
    uint8_t port; /**< port - Policer port number */
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
    uint8_t port; /**< local_port - local port number */
    uint8_t lbf_mode; /**< lbf_mode - Port loopback filtering state  */
};

/**
 * ku_qpts_reg structure is used to store the QPTS register parameters
 */
struct ku_qpts_reg {
    uint8_t port; /**< port - Port number */
    uint8_t trust_level; /**< trust_level -
                          *  0 - Trust Port
                          *  1 - Trust User Priority - this is the default value / trust L2
                          *  2 - Trust DSCP / trust L3
                          *  3 - Trust Both
                          *  Otherwise - reserved */
};

/**
 * ku_qstct_reg structure is used to store the QSTCT register parameters
 */
struct ku_qstct_reg {
    uint8_t swid; /**< swid - Switch partition ID */
    uint8_t prio; /**< prio - Ingress Priority */
    uint8_t utclass; /**< utclass - Stacking traffic class used for unicast packets with priority prio */
    uint8_t mtclass; /**< mtclass - Stacking traffic class used for multicast packets with priority prio */
};

/**
 * ku_qpdpm_reg structure is used to store the QPDPM register parameters
 */
struct ku_qpdpm_reg {
    uint8_t local_port; /**< port - Port number */
    uint8_t dscp_update[DSCP_CODES_NUMBER];    /**< dscp_update - whether to update this DSCP mapping in HW */
    uint8_t color[DSCP_CODES_NUMBER]; /**< color mapping per DSCP value */
    uint8_t priority[DSCP_CODES_NUMBER];       /**< priority mapping per DSCP value - Priority */
};

/**
 * ku_qepm_reg structure is used to store the QEPM register parameters
 */
struct ku_qepm_reg {
    uint8_t local_port; /**< port - Port number */
    uint8_t exp_update[EXP_CODES_NUMBER];    /**< exp_update - whether to update this EXP mapping in HW */
    uint8_t ecn[EXP_CODES_NUMBER]; /**< the new packet ecn value */
    uint8_t color[EXP_CODES_NUMBER]; /**< color mapping per EXP value */
    uint8_t priority[EXP_CODES_NUMBER];       /**< priority mapping per EXP value - Priority */
};

/**
 * ku_qeec_reg structure is used to store the QEEC register parameters
 */
struct ku_qeec_reg {
    uint8_t  local_port; /**< port - Port number */
    uint8_t  port_rate; /**< port_rate - Port rate */
    uint8_t  element_hierarchy; /**< 0-port, 1-group, 2-sub-group, 3-TC */
    uint8_t  element_index; /** index in the hierarchy */
    uint8_t  next_element_index; /** element index of the lower level element is connected to */
    uint8_t  min_shaper_enable; /**< min_shaper_enable - 0-disable, 1- enable */
    uint8_t  ptp_shaper; /**< shaper mode - 0-regular shaper, 1-PTP oriented shaper */
    uint8_t  packet_mode; /**<  0-bytes mode, 1-packet mode */
    uint32_t min_shaper; /** min shaper configuration */
    uint8_t  max_shaper_enable; /**< max_shaper_enable - 0-disable, 1-enable */
    uint32_t max_shaper; /** max shaper configuration */
    uint8_t  phantom_queue_enable; /**< phantom_queue_enable - 0-disable, 1-enable */
    uint32_t phantom_queue; /** phantom queue configuration */
    uint8_t  dwrr_enable; /**< dwrr_enable - 0-disable, 1-enable */
    uint8_t  dwrr; /** dwrr - 0-strict priority, 1-DWRR */
    uint8_t  dwrr_weight; /** dwrr weight on the link going down from the element */
};

/**
 * ku_qpdcp_reg structure is used to store the QPDCP register parameters
 */
struct ku_qpdpc_reg {
    uint8_t local_port; /**local port number */
    uint8_t sub_port; /** virtual port within the physical port */
    uint8_t dei; /** default port DEI */
    uint8_t pcp; /** default port PCP */
};

/**
 * ku_qtctm_reg structure is used to store the QTCTM register parameters
 */
struct ku_qtctm_reg {
    uint8_t local_port; /**local port number */
    uint8_t mc_aware; /** 0-non mc aware, 1-mc aware */
};

/**
 * ku_qspip_reg structure is used to store the QSPIP register parameters
 */
struct ku_qspip_reg {
    uint8_t switch_prio; /**switch priority */
    uint8_t ieee_prio; /** ieee priority */
};

/**
 * ku_qspcp_reg structure is used to store the QSPCP register parameters
 */
struct ku_qspcp_reg {
    uint8_t local_port; /**local port number */
    uint8_t switch_prio; /** switch priority */
    uint8_t rx_prio; /** RX counting priority */
    uint8_t tx_prio; /** TX counting priority */
};

/**
 * ku_qrwe_reg structure is used to store the QRWE register parameters
 */
struct ku_qrwe_reg {
    uint8_t local_port; /**local port number */
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
    struct qppm_switch_prio switch_prio[16]; /** switch priority to pcp mapping */
};

/**
 * ku_qsll_reg structure is used to store the QSLL register parameters
 */
struct ku_qsll_reg {
    uint8_t sll_time;
};

/**
 * ku_access_qsll_reg structure is used to store the access
 * register QSLL command parameters
 */
struct ku_access_qsll_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qsll_reg      qsll_reg; /**< qsll_reg - QSLL register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_qhll_reg structure is used to store the QHLL register parameters
 */
struct ku_qhll_reg {
    uint8_t local_port;
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
    SXD_PVGT_OP_ADD_VLAN_E = 0,
    SXD_PVGT_OP_REMOVE_VLAN_E = 1,
} sxd_pvgt_operation_t;

/**
 * ku_pvgt_reg structure is used to store the PVGT register parameters
 */
typedef struct ku_pvgt_reg {
    uint8_t              swid;
    sxd_pvgt_operation_t op;
    uint16_t             vid;
    uint16_t             vlan_group;
} ku_pvgt_reg_t;

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
    SXD_MRSR_CMD_DO_NOTHING = 0,
    SXD_MRSR_CMD_SW_RESET = 1,
    SXD_MRSR_CMD_ENCLOSURE_RESET = 3,
    SXD_MRSR_CMD_SHUTDOWN = 4
};

/**
 * ku_mrsr_reg structure is used to store the MRSR register parameters
 */
struct ku_mrsr_reg {
    enum sxd_mrsr_command command;
};

/**
 * ku_pprr_reg structure is used to store the PPRR register parameters
 */
typedef struct ku_pprr_reg {
    uint8_t  ipv4;
    uint8_t  ipv6;
    uint8_t  src;
    uint8_t  dst;
    uint8_t  tcp;
    uint8_t  udp;
    uint8_t  ignore_l3;
    uint8_t  ignore_l4;
    uint8_t  inner_outer;
    uint8_t  ip_length;
    uint8_t  reg_index;
    uint16_t port_range_min;
    uint16_t port_range_max;
    uint8_t  cbset;
} ku_pprr_reg_t;

/**
 * sxd_pagt_operation_t enumerated type is used to note the
 * PAGT operation type.
 */
typedef enum sxd_pagt_operation {
    SXD_PAGT_OP_CREATE_E = 0,
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
    SXD_PVBT_OP_BIND_E = 0,
    SXD_PVBT_OP_UNBIND_E = 1,
} sxd_pvbt_operation_t;

/**
 * ku_pvbt_reg structure is used to store the PVBT register parameters
 */
typedef struct ku_pvbt_reg {
    sxd_pvbt_operation_t operation;
    uint8_t              swid;
    uint16_t             vlan_group;
    uint8_t              group;
    uint16_t             acl_id_grp_id;
} ku_pvbt_reg_t;


/**
 * sxd_ppbt_operation enumerated type is used to note the
 * PPBT operation type.
 */
typedef enum sxd_ppbt_operation {
    SXD_PPBT_OP_BIND_E = 0,
    SXD_PPBT_OP_UNBIND_E = 1,
} sxd_ppbt_operation_t;

typedef enum sxd_flex_acl_action_type {
    SXD_ACTION_TYPE_NULL_E = 0,
    SXD_ACTION_TYPE_MAC_E = 1,
    SXD_ACTION_TYPE_VLAN_E = 2,
    SXD_ACTION_TYPE_TRAP_E = 3,
    SXD_ACTION_TYPE_TRAP_W_USER_DEF_VAL_E = 4,
    SXD_ACTION_TYPE_PORT_FILTER_E = 5,
    SXD_ACTION_TYPE_QOS_E = 6,
    SXD_ACTION_TYPE_FORWARD_E = 7,
    SXD_ACTION_TYPE_POLICING_COUNTING_E = 8,
    SXD_ACTION_TYPE_META_DATA_E = 9,
    SXD_ACTION_TYPE_UC_ROUTER_AND_MPLS_E = 10,
    SXD_ACTION_TYPE_VXLAN_E = 11,
    SXD_ACTION_TYPE_MPLS_E = 12,
    SXD_ACTION_TYPE_HASH_E = 13,
    SXD_ACTION_TYPE_VIRTUAL_FORWARDING_E = 14,
    SXD_ACTION_TYPE_IGNORE_E = 15,
    SXD_ACTION_TYPE_MC_E = 16,
    SXD_ACTION_TYPE_SIP_DIP_E = 17,
    SXD_ACTION_TYPE_L4_PORT_E = 18,
    SXD_ACTION_TYPE_MIRROR_SAMPLER_E = 19,
    SXD_ACTION_TYPE_UNDEFINDED_E = 20,
    SXD_ACTION_TYPE_PORT_FILTER_EXT_E = 21,
    SXD_ACTION_TYPE_LAST_E = 22
} sxd_flex_acl_action_type_t;

/**
 * sxd_ppbt_cong enumerated type is used to note the
 * PPBT congestion type.
 */
typedef enum sxd_ppbt_cong {
    SXD_PPBT_CONG_MAIN_BINDING = 0,
    SXD_PPBT_CONG_FALSE_BINDING = 1,
    SXD_PPBT_CONG_BINDING = 2
} sxd_ppbt_cong_t;

/**
 * ku_ppbt_reg structure is used to store the PPBT register parameters
 */
typedef struct ku_ppbt_reg {
    sxd_ppbt_operation_t operation;
    uint8_t              egress;
    uint8_t              port;
    sxd_ppbt_cong_t      cong;
    uint8_t              group;
    uint16_t             acl_id_grp_id;
} ku_ppbt_reg_t;

/**
 * sxd_acl_ptce_action_type enumerated type is used to
 * note the PTCE action type.
 */
typedef enum sxd_acl_ptce_action_type {
    SXD_PTCE_ACTION_TYPE_DEFAULT_E = 0,
    SXD_PTCE_ACTION_TYPE_EXTENDED_E = 1,
} sxd_acl_ptce_action_type_t;

/**
 * sxd_acl_ptce_key_type enumerated type is used to note
 * the PTCE key type.
 */
typedef enum sxd_acl_ptce_key_type {
    SXD_PTCE_KEY_TYPE_IPV4_FULL_E = 0,
    SXD_PTCE_KEY_TYPE_IPV6_FULL_E = 1,
    SXD_PTCE_KEY_TYPE_MAC_FULL_E = 2,
    SXD_PTCE_KEY_TYPE_MAC_IPV4_FULL_E = 3,
    SXD_PTCE_KEY_TYPE_MAC_SHORT_E = 5,
    SXD_PTCE_KEY_TYPE_FCOE_FULL_E = 32
} sxd_acl_ptce_key_type_t;

/**
 * sxd_ptce_trap_action enumerated type is used to note
 * the PTCE action trap action type.
 */
typedef enum sxd_ptce_trap_action {
    SXD_PTCE_TRAP_ACTION_PERMIT_E = 0,
    SXD_PTCE_TRAP_ACTION_SOFT_DROP_E = 1,
    SXD_PTCE_TRAP_ACTION_TRAP_E = 2,
    SXD_PTCE_TRAP_ACTION_SOFT_DROP_TRAP_E = 3,
    SXD_PTCE_TRAP_ACTION_DENY_E = 4,
} sxd_ptce_trap_action_t;

/**
 * sxd_ptce_vlan_action enumerated type is used to note
 * the PTCE action vlan action type.
 */
typedef enum sxd_ptce_vlan_action {
    SXD_PTCE_VLAN_ACTION_NOP_E = 0,
    SXD_PTCE_VLAN_ACTION_PUSH_VID_KEEP_PRIO_E = 0x8,
    SXD_PTCE_VLAN_ACTION_PUSH_VLAN_E = 0xC,
    SXD_PTCE_VLAN_ACTION_REPLACE_VID_KEEP_PRIO_E = 0x18,
    SXD_PTCE_VLAN_ACTION_REPLACE_VID_PRIO_E = 0x1c,
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
    SXD_PTCE_OP_WRITE = 0,
    SXD_PTCE_OP_READ = 0,
    SXD_PTCE_OP_CLEAR_ON_READ = 1,
    SXD_PTCE_OP_UPDATE = 1,
    SXD_PTCE_OP_CLEAR_ACTIVITY = 2,
    SXD_PTCE_OP_WRITE_CLEAR = 3
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
    SXD_FLEX_ACL_L2_DMAC_TYPE_UNICAST = 2,
} sxd_flex_acl_l2_dmac_type_t;

typedef enum sxd_flex_acl_l3_type_ {
    SXD_FLEX_ACL_L3_TYPE_IPV4 = 0,
    SXD_FLEX_ACL_L3_TYPE_IPV6 = 1,
    SXD_FLEX_ACL_L3_TYPE_ARP = 2,
    SXD_FLEX_ACL_L3_TYPE_OTHER = 3,
} sxd_flex_acl_l3_type_t;

typedef enum sxd_flex_acl_l4_type_ {
    SXD_FLEX_ACL_L4_TYPE_TCP = 1 << 0,
        SXD_FLEX_ACL_L4_TYPE_UDP = 1 << 1,
        SXD_FLEX_ACL_L4_TYPE_RESERVED = 1 << 2,
        SXD_FLEX_ACL_L4_TYPE_OTHER = 1 << 3,
} sxd_flex_acl_l4_type_t;

typedef enum sxd_flex_acl_discard_state_ {
    SXD_FLEX_ACL_DISCARD_STATE_FORWARD = 0,
    SXD_FLEX_ACL_DISCARD_STATE_SOFT_DISCARD_ERROR = 1,
    SXD_FLEX_ACL_DISCARD_STATE_DISCARD = 2,
    SXD_FLEX_ACL_DISCARD_STATE_DICARD_ERROR = 3,
    SXD_FLEX_ACL_DISCARD_STATE_LAST,
} sxd_flex_acl_discard_state_t;

typedef enum sxd_flex_acl_l4_type_extended_ {
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_NONE = 0,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_OTHERS = 1,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_TCP = 2,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_UDP = 3,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_BTH = 4,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_BTHOUDP = 5,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_ICMP = 6,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_IGMP = 7,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_AH = 8,
    SXD_FLEX_ACL_L4_TYPE_EXTENDED_ESP = 9,
} sxd_flex_acl_l4_type_extended_t;

typedef enum sxd_flex_acl_nd_sll_or_tll_valid_ {
    SXD_FLEX_ACL_NO_ND_SLL_OR_TTL = 0,
    SXD_FLEX_ACL_ND_SLL = 1,
    SXD_FLEX_ACL_ND_TLL = 2,
} sxd_flex_acl_nd_sll_or_tll_valid;

typedef enum sxd_flex_acl_mc_bc_or_flood_type_ {
    SXD_FLEX_ACL_MC_TYPE_FLOOD_FOR_UC = 1 << 0,
        SXD_FLEX_ACL_MC_TYPE_BC = 1 << 1,
        SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_NON_IP = 1 << 2,
        SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_IPV4 = 1 << 3,
        SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_IPV4_LINK_LOCAL = 1 << 4,
        SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_IPV6 = 1 << 5,
        SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_IPV6_NODES_LOCAL = 1 << 6,
        SXD_FLEX_ACL_MC_TYPE_FLOOD_MC_ROCE_V1 = 1 << 7,
} sxd_flex_acl_mc_bc_or_flood_type;

typedef enum sxd_flex_acl_ipv6_extension_headers_ {
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_ROUTING = 0,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_FRAGMENT = 1,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_DESTINATION_OPTIONS = 2,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_AUTHENTICATION = 3,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_ESP = 4,
    SXD_FLEX_ACL_IPV6_EXTENSION_HEADER_MOBILITY = 5,
} sxd_flex_acl_ipv6_extension_headers_t;

typedef enum sxd_flex_ttl_cmd_ {
    SXD_FLEX_TTL_CMD_DO_NOTHING_E = 0,
    SXD_FLEX_TTL_CMD_SET_TTL_VALUE_E = 1,
    SXD_FLEX_TTL_CMD_DECREMENT_E = 2,
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

typedef enum sxd_flex_dscp_cmd {
    SXD_FLEX_DSCP_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_DSCP_CMD_TYPE_SET_3_LSB_BITS_E = 1,
    SXD_FLEX_DSCP_CMD_TYPE_SET_3_MSB_BITS_E = 2,
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
    SXD_FLEX_SWITCH_PRIO_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_SWITCH_PRIO_CMD_TYPE_SET_SWITCH_PRIORITY_E = 1,
    SXD_FLEX_SWITCH_PRIO_CMD_TYPE_LAST,
} sxd_flex_switch_prio_cmd_t;

typedef enum sxd_flex_color_cmd {
    SXD_FLEX_COLOR_CMD_TYPE_DO_NOTHING_E = 0,
    SXD_FLEX_COLOR_CMD_TYPE_SET_COLOR_E = 1,
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
    SXD_FLEX_GOTO_RECORD_E = 1,
} sxd_ptce2_next_type_t;

typedef enum sxd_binding_cmd {
    SXD_FLEX_BINDING_NONE_E = 0,
    SXD_FLEX_BINDING_JUMP_E = 1,
    SXD_FLEX_BINDING_CALL_E = 2,
    SXD_FLEX_BINDING_BREAK_E = 3,
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

typedef struct sxd_metadata_flex_action {
    uint16_t meta_data;
    uint16_t mask;
} sxd_metadata_flex_action_t;

typedef enum sxd_uc_router_flex_action_type {
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_IP_REMOTE_E = 0,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_IP_LOCAL_E,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_TUNNL_TERMINIATION_E,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_MPLS_ILM_E,
    SXD_UC_ROUTER_FLEX_ACTION_TYPE_MPLS_NHLFE_E,
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

typedef struct sxd_uc_router_flex_action {
    sxd_uc_router_flex_action_type_t type;
    union {
        sxd_uc_router_flex_action_ip_remote_t          ip_remote;
        sxd_uc_router_flex_action_ip_local_t           ip_local;
        sxd_uc_router_flex_action_tunnul_termination_t tunnul_termination;
        sxd_uc_router_flex_action_mpls_ilm_t           mpls_ilm;
        sxd_uc_router_flex_action_mpls_nhlfe_t         mpls_nhlfe;
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
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SMAC_31_0_E = 0,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DMAC_31_0_E = 1,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DMAC_SMAC_47_32_E = 2,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SMAC_DMAC_47_32_E = 3,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SIP_31_0_E = 4,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SIP_63_32_E = 5,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SIP_95_64_E = 6,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SIP_127_96_E = 7,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DIP_31_0_E = 8,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DIP_63_32_E = 9,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DIP_95_64_E = 10,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_DIP_127_96_E = 11,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_SPI_E = 17,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_SIP_31_0_E = 18,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_SIP_63_32_E = 19,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_SIP_95_64_E = 20,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_SIP_127_96_E = 21,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_DIP_31_0_E = 22,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_DIP_63_32_E = 23,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_DIP_95_64_E = 24,
    SXD_HASH_FLEX_ACTION_HASH_FIELD_INNER_DIP_127_96_E = 25
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

typedef struct sxd_ignore_flex_action {
    sxd_ignore_flex_action_ignore_stp_type_t           ignore_stp;
    sxd_ignore_flex_action_ignore_vl_filter_type_t     ignore_vl_filter;
    sxd_ignore_flex_action_disable_learning_type_t     disable_learning;
    sxd_ignore_flex_action_disable_ovl_learning_type_t disable_ovl_learning;
} sxd_ignore_flex_action_t;

typedef enum sxd_group_or_acl_binding_type {
    SXD_GROUP_OR_ACL_BINDING_TYPE_ACL_E = 0,
    SXD_GROUP_OR_ACL_BINDING_TYPE_GROUP_E
} sxd_group_or_acl_binding_type_t;

typedef enum sxd_mc_flex_action_rpf_action_type {
    SXD_MC_FLEX_ACTION_RPF_ACTION_NOP_E = 0,
    SXD_MC_FLEX_ACTION_RPF_ACTION_RPF_TRAP_E = 1,
    SXD_MC_FLEX_ACTION_RPF_ACTION_RPF_DISCARD_ERR_E = 3,
    SXD_MC_FLEX_ACTION_RPF_ACTION_ASSERT_TRAP_E = 6,
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
    SXD_SIP_DIP_FLEX_ACTION_DIRECTION_SOURCE_E = 1,
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
    SXD_L4_PORT_FLEX_ACTION_DIRECTION_SOURCE_E = 0,
    SXD_L4_PORT_FLEX_ACTION_DIRECTION_DESTINATION_E = 1,
    SXD_L4_PORT_FLEX_ACTION_DIRECTION_TYPE_LAST_E,
} sxd_l4_port_flex_action_direction_t;

typedef enum sxd_l4_port_flex_action_hash {
    SXD_L4_PORT_FLEX_ACTION_HASH_NONE_E = 0,
    SXD_L4_PORT_FLEX_ACTION_HASH_ROUTER_E = 1,
    SXD_L4_PORT_FLEX_ACTION_HASH_LAG_E = 2,
    SXD_L4_PORT_FLEX_ACTION_HASH_TYPE_LAST_E,
} sxd_l4_port_flex_action_hash_t;

typedef struct sxd_l4_port_flex_action {
    sxd_flex_defer_t                    defer;
    sxd_l4_port_flex_action_direction_t direction;
    sxd_l4_port_flex_action_hash_t      hash;
    uint16_t                            l4_port;
} sxd_l4_port_flex_action_t;

typedef struct sxd_action_slot {
    sxd_flex_acl_action_type_t type;
    union {
        sxd_mac_flex_action_t                 action_mac;
        sxd_vlan_flex_action_t                action_vlan;
        sxd_trap_flex_action_t                action_trap;          /** Used for trap and trap_w_user_def_val */
        sxd_port_filter_flex_action_t         action_port_filter;
        sxd_qos_flex_action_t                 action_qos;
        sxd_forward_flex_action_t             action_forward;
        sxd_policing_monitoring_flex_action_t action_policing_monitoring;
        sxd_metadata_flex_action_t            action_metadata;
        sxd_uc_router_flex_action_t           action_uc_router;
        sxd_vni_flex_action_t                 action_vni;
        sxd_mpls_flex_action_t                action_mpls;
        sxd_hash_flex_action_t                action_hash;
        sxd_virtual_forward_flax_action_t     action_virtual_forward;
        sxd_ignore_flex_action_t              action_ignore;
        sxd_mc_flex_action_t                  action_mc;
        sxd_sip_dip_flex_action_t             action_sip_dip;
        sxd_l4_port_flex_action_t             action_l4_port;
        sxd_port_filter_ext_flex_action_t     action_port_filter_ext;
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
    SXD_PEFA_CA_OP_SET = 0,
    SXD_PEFA_CA_OP_CLEAR = 1,
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

#define SXD_ACL_CUSTOM_BYTE_SET0 0x0
#define SXD_ACL_CUSTOM_BYTE_SET1 0x1
#define SXD_ACL_CUSTOM_BYTE_SET2 0x2
#define SXD_ACL_CUSTOM_BYTE_SET3 0x3
#define SXD_ACL_CUSTOM_BYTE_SET4 0x4
#define SXD_ACL_CUSTOM_BYTE_SET5 0x5
#define SXD_ACL_CUSTOM_BYTE_SET6 0x6
#define SXD_ACL_CUSTOM_BYTE_SET7 0x7
#define SXD_ACL_CUSTOM_BYTE_SET8 0x8
#define SXD_ACL_CUSTOM_BYTE_SET9 0x9

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
#define SXD_ACL_EXTRACTION_POINT_GRE_PAYLOLAD       0x1A
#define SXD_ACL_EXTRACTION_POINT_UDP_PAYLOAD        0x25
#define SXD_ACL_EXTRACTION_POINT_INNER_MAC_HEADER   0x27
#define SXD_ACL_EXTRACTION_POINT_INNER_ETHER_TYPE   0x28
#define SXD_ACL_EXTRACTION_POINT_INNER_IPV4_HEADER  0x29
#define SXD_ACL_EXTRACTION_POINT_INNER_IPV4_PAYLOAD 0x2A
#define SXD_ACL_EXTRACTION_POINT_INNER_IPV6_HEADER  0x2D
#define SXD_ACL_EXTRACTION_POINT_INNER_IPV6_PAYLOAD 0x2E
#define SXD_ACL_EXTRACTION_POINT_INNER_UDP_PAYLOAD  0x3A

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
    KU_PEMB_ENTRY_TYPE_SPREADING_E = 0x1,
    KU_PEMB_ENTRY_TYPE_EGRESS_ACL_MULTICAST_E = 0x2,
    KU_PEMB_ENTRY_TYPE_RESERVED_E = 0x3
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
    SXD_PACL_ACL_TYPE_L3 = 1,
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
    SXD_PTAR_OP_ALLOCATE_E = 0,
    SXD_PTAR_OP_RESIZE_E = 1,
    SXD_PTAR_OP_DEALLOCATE_E = 2,
    SXD_PTAR_OP_TEST_ALLOCATE_E = 3,
} sxd_acl_ptar_op_t;


/**
 * sxd_acl_ptar_action_type enumerated type is used to
 * note the PTAR action type.
 */
typedef enum sxd_acl_ptar_action_type {
    SXD_PTAR_DEFAULT_ACTION_E = 0,
    SXD_PTAR_EXTENDED_ACTION_E = 1,
    SXD_PTAR_FLEX_ACTION_E = 2,
    SXD_PTAR_FLEX_2_ACTION_E = 2
} sxd_acl_ptar_action_type_t;


/**
 * sxd_acl_ptar_action_type enumerated type is used to
 * note the PTAR action type.
 */
typedef enum sxd_acl_ptar_key_type {
    SXD_PTAR_KEY_IPv4_FULL_E = 0,
    SXD_PTAR_KEY_IPv6_FULL_E = 1,
    SXD_PTAR_KEY_MAC_FULL_E = 2,
    SXD_PTAR_KEY_MAC_IPv4_FULL_E = 3,
    SXD_PTAR_KEY_MAC_SHORT_E = 4,
    SXD_PTAR_KEY_CONFIGURABLE_FULL_E = 16,
    SXD_PTAR_KEY_FCOE_FULL_E = 32,
    SXD_PTAR_KEY_FLEX_KEY_E = 0x50,
    SXD_PTAR_KEY_FLEX_2_KEY_E = 0x51
} sxd_acl_ptar_key_type_t;

/**
 * sxd_ptar_optimization_type_t enumerated type is used to note the TCAM
 * optimization mode.
 */
typedef enum sxd_ptar_optimization_type {
    SXD_PTAR_TCAM_NO_OPTIMIZATION_E = 0,
    SXD_PTAR_TCAM_SOFT_OPTIMIZATION_E = 1,
    SXD_PTAR_TCAM_HARD_OPTIMIZATION_E = 2,
    SXD_PTAR_TCAM_RESERVED_E = 3,
} sxd_ptar_optimization_type_t;

/**
 * sxd_ptar_packet_rate_t enumerated type is used to note the packet rate
 * for TCAM optimization mode. Granularity is 5%. Duplication number is used.
 */
typedef enum sxd_ptar_packet_rate {
    SXD_PTAR_PACKET_RATE_0_PCT = 0,
    SXD_PTAR_PACKET_RATE_10_PCT = 2,
    SXD_PTAR_PACKET_RATE_20_PCT = 4,
    SXD_PTAR_PACKET_RATE_40_PCT = 8,
    SXD_PTAR_PACKET_RATE_80_PCT = 16,
} sxd_ptar_packet_rate_t;

typedef enum sxd_acl_ptar_direction {
    SXD_PTAR_ACL_DIRECTION_INGRESS_E = 0,
    SXD_PTAR_ACL_DIRECTION_EGRESS_E = 1
} sxd_acl_ptar_direction_t;

/**
 * ku_ptar_reg structure is used to store the PTAR register parameters
 */
typedef struct ku_ptar_reg {
    sxd_acl_ptar_op_t            op;
    sxd_acl_ptar_action_type_t   action_type;
    sxd_acl_ptar_key_type_t      key_type;
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
 * sxd_acl_ffar_op enumerated type is used to note the
 * FFAR operation.
 */
enum sxd_acl_ffar_op {
    SXD_FFAR_OP_ALLOCATE = 0,
    SXD_FFAR_OP_RESIZE = 1,
    SXD_FFAR_OP_DEALLOCATE = 2,
    SXD_FFAR_OP_TEST_ALLOCATE = 3,
};


/**
 * sxd_fc_optimization_type_t enumerated type is used to note the TCAM
 * optimization mode.
 */
typedef enum sxd_fc_optimization_type {
    SXD_FC_TCAM_NO_OPTIMIZATION = 0,
    SXD_FC_TCAM_SOFT_OPTIMIZATION = 1,
    SXD_FC_TCAM_HARD_OPTIMIZATION = 2,
    SXD_FC_TCAM_RESERVED = 3,
} sxd_fc_optimization_type_t;

/**
 * ku_ffar_reg structure is used to store the FFAR register parameters
 */
struct ku_ffar_reg {
    enum sxd_acl_ffar_op       op;
    uint16_t                   region_size;
    sxd_fc_optimization_type_t op_type;
};

/**
 * ku_pgcr_reg structure is used to store the PGCR register
 * parameters
 */
typedef struct ku_pgcr_reg {
    uint8_t  update_prune;
    uint16_t pbs_table_size;
    uint16_t max_eacl;
    uint16_t max_iacl;
    uint16_t atcam_ignore_prune_vector;
    uint8_t  activity_dis;
    uint32_t default_action_base;
} ku_pgcr_reg_t;

/**
 * ku_puet_reg structure is used to store the PUET register
 * parameters
 */
typedef struct ku_puet_reg {
    uint8_t  index;
    uint16_t ethertype;
} ku_puet_reg_t;

/**
 * sxd_router_arp_operation_t enumerated type is used to note the ARP
 * operation.
 */
typedef enum sxd_router_arp_operation {
    SXD_ROUTER_ARP_OPERATION_ALLOCATE = 0,
    SXD_ROUTER_ARP_OPERATION_WRITE = 1,
    SXD_ROUTER_ARP_OPERATION_DEALLOCATE = 2,
    SXD_ROUTER_ARP_OPERATION_WRITE_A_CLEARED = 3,
    SXD_ROUTER_ARP_OPERATION_CLEAR_A = 2
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
    uint16_t ecmp_size;
    uint16_t underlay_router_interface;
} ku_mpls_adj_parameters_t;

/**
 * Underlay Destination IP Types
 */
typedef enum sxd_udip_type {
    SXD_UDIP_TYPE_IPV4 = 0,
    SXD_UDIP_TYPE_IPV6 = 1,
    SXD_UDIP_TYPE_AUTO_TUNNEL_IPV6_TO_IPV4 = 2,
    SXD_UDIP_TYPE_AUTO_TUNNEL_ISATAP = 3,
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
} ku_adj_parameters_t;

/**
 * sxd_router_adjacency_table_type enumerated type is used to note the Adjacency Entry Type
 * operation.
 */
typedef enum sxd_router_adjacency_table_type {
    ETHERNET = 0,
    PKEY_UNI_WITHOUT_GRH = 1,
    PKEY_UNI_WITH_GRH = 2,
    PKEY_MULTI = 3,
    MPLS = 4,
    L3_TUNNEL_ENCAP = 5,
} sxd_router_adjacency_table_type_t;

/**
 * sxd_router_adjacency_table enumerated is used to identify the table type
 */

typedef enum sxd_router_adjacency_table {
    ETHERNET_UNICAST_ADJACENCY = 0,
    IPoIB_UNICAST_AND_MULTICAST_ADJACENCY = 1,
    IPoIB_ALL_ROUTERS_ADJACENCY = 2,
    IPoIB_IP_BROADCAST_ADJACENCY = 3,
    IB_ALGO_ROUTING = 4,
} sxd_router_adjacency_table_t;

/**
 * sxd_router_adjacency_validate type is used to note if an
 * adjacency entry should be added or subtracted.
 */
typedef enum sxd_router_adjacency_validate {
    SXD_ROUTE_ADJECENCY_DELETE = 0,
    SXD_ROUTE_ADJECENCY_WRITE = 1,
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
    SXD_ROUTER_ROUTE_ACTION_PERMIT = 0,
    SXD_ROUTER_ROUTE_ACTION_SOFT_DROP = 1,
    SXD_ROUTER_ROUTE_ACTION_TRAP = 2,
    SXD_ROUTER_ROUTE_ACTION_SOFT_DROP_TRAP = 3,
    SXD_ROUTER_ROUTE_ACTION_DENY = 4,
} sxd_router_route_action_t;

/**
 * sxd_router_en_route_action_t enumerated type is used to note the route action in RouterEN.
 */
typedef enum sxd_router_en_action {
    SXD_ROUTER_EN_ACTION_NOP = 0,
    SXD_ROUTER_EN_ACTION_TRAP = 1,
    SXD_ROUTER_EN_ACTION_MIRROR_TO_CPU = 2,
    SXD_ROUTER_EN_ACTION_MIRROR = 3,
    SXD_ROUTER_EN_ACTION_DISCARD_ERROR = 4,
    SXD_ROUTER_EN_ACTION_MIN = SXD_ROUTER_EN_ACTION_NOP,
    SXD_ROUTER_EN_ACTION_MAX = SXD_ROUTER_EN_ACTION_DISCARD_ERROR,
} sxd_router_en_action_t;

/**
 * sxd_forward_action_t enumerated type is used to note the forward action in NHLFE.
 */
typedef enum sxd_forward_action {
    SXD_FORWARD_ACTION_ETH = 0,
    SXD_FORWARD_ACTION_IP_ROUTER = 1,
    SXD_FORWARD_ACTION_CONTINUE_LOOKUPS = 2,
    SXD_FORWARD_ACTION_NEXT_NHLFE = 3,
    SXD_FORWARD_ACTION_MIN = SXD_FORWARD_ACTION_ETH,
    SXD_FORWARD_ACTION_MAX = SXD_FORWARD_ACTION_NEXT_NHLFE,
} sxd_forward_action_t;

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
    SXD_RATRAD_OP_READ_ACTIVITY = 0,
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
    SXD_ROUTER_ROUTE_TYPE_IPV4 = 0,
    SXD_ROUTER_ROUTE_TYPE_IPV6 = 1,
    SXD_ROUTER_ROUTE_TYPE_IB_GID_SITE_LOCAL = 2,
} sxd_router_route_type_t;

typedef enum sxd_router_tcam_write_operation {
    /*On write register*/
    SXD_ROUTER_TCAM_WRITE = 0,
    SXD_ROUTER_TCAM_UPDATE = 1,
    SXD_ROUTER_TCAM_CLEAR_ACTIVITY = 2,
    SXD_ROUTER_TCAM_WRITE_CLEAR = 3,
    /*On read register*/
    SXD_ROUTER_TCAM_READ = 0,
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
    SXD_KVD_HASH_OPERATION_READ = 0,
    SXD_KVD_HASH_OPERATION_READ_CLEAR = 1,
} sxd_kvd_hash_operation_t;

typedef enum sxd_fcf_tcam_write_operation {
    SXD_FCF_TCAM_WRITE = 0,
    SXD_FCF_TCAM_UPDATE = 1,
    SXD_FCF_TCAM_CLEAR_ACTIVITY = 2,
} sxd_fcf_tcam_write_operation_t;

/**
 * sxd_router_qos_t enumerated type is used to note the route
 * quality of service .
 */
typedef enum {
    SXD_ROUTER_QOS_MAP_PRIO_FROM_DSCP = 0,
    SXD_ROUTER_QOS_PRESERVE_PRIO = 1,
} sxd_router_qos_t;

/*
 * Egress Port Type for Fibre Channel protocols
 */
typedef enum sxd_ept {
    SXD_FCF_FCOE_VF_PORT = 0,
    SXD_FCF_FCOE_VE_PORT = 1,
    SXD_FCF_FC_VF_PORT = 2,
    SXD_FCF_FC_VE_PORT = 3,
    SXD_FCF_FCOIB_VF_PORT = 4,
    SXD_FCF_FCOIB_VE_PORT = 5,
} sxd_ept_t;

typedef enum sxd_counter_opcode {
    SXD_COUNTER_OPCODE_NOP = 0,
    SXD_COUNTER_OPCODE_ADD_COUNTERS = 1,
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
 * ku_fftr_reg structure is used to store the FFTR register parameters
 */
struct ku_fftr_reg {
    uint8_t                        valid;
    sxd_fcf_tcam_write_operation_t operation;
    uint16_t                       offset;
    sxd_fcf_id_t                   fcf;
    sxd_fc_addr_t                  did;
    sxd_fc_addr_t                  did_mask;
    sxd_fc_addr_t                  sid;
    sxd_fc_addr_t                  sid_mask;
    sxd_ept_t                      ept;
    uint16_t                       ve_port_index;  /* Should be 0 for vf_ports */
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
        SXD_RAUHTD_FILTER_RIF = 1 << 3,
} sxd_rauhtd_filter_fields_t;

/**
 * operation for RAUHTD
 */
typedef enum sxd_rauhtd_operation {
    SXD_RAUHTD_OP_DUMP_ENTRIES = 0,
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
    SXD_RMFT_RPF_ACTION_NONE = 0,
    SXD_RMFT_RPF_ACTION_DISCARD = 1,
    SXD_RMFT_RPF_ACTION_TRAP = 2,
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
    sxd_router_route_type_t           route_type;
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
    SXD_ROUTER_ECMP_HASH_TYPE_CRC = 0,
    SXD_ROUTER_ECMP_HASH_TYPE_XOR = 1,
    SXD_ROUTER_ECMP_HASH_TYPE_RANDOM = 2,
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
    SXD_ROUTER_TCAM_TYPE_IPV4_UNICAST = 0,
    SXD_ROUTER_TCAM_TYPE_IPV4_MULTICAST = 1,
    SXD_ROUTER_TCAM_TYPE_IPV6_UNICAST = 2,
    SXD_ROUTER_TCAM_TYPE_IPV6_MULTICAST = 3,
    SXD_ROUTER_TCAM_TYPE_IPV4_HOST_TABLE = 4,
    SXD_ROUTER_TCAM_TYPE_IPV6_HOST_TABLE = 5,
    SXD_ROUTER_TCAM_TYPE_INVALID
} sxd_router_tcam_type_t;

/**
 * sxd_router_tcam_operation_t enumerated type is used to note the TCAM
 * operation.
 */
typedef enum sxd_router_tcam_operation {
    SXD_ROUTER_TCAM_OPERATION_ALLOCATE = 0,
    SXD_ROUTER_TCAM_OPERATION_RESIZE = 1,
    SXD_ROUTER_TCAM_OPERATION_DEALLOCATE = 2,
    SXD_ROUTER_TCAM_OPERATION_TEST = 3,
} sxd_router_tcam_operation_t;

/**
 * sxd_router_optimization_type_t enumerated type is used to note the TCAM
 * optimization mode.
 */
typedef enum sxd_router_optimization_type_ {
    SXD_ROUTER_TCAM_NO_OPTIMIZATION = 0,
    SXD_ROUTER_TCAM_SOFT_OPTIMIZATION = 1,
    SXD_ROUTER_TCAM_HARD_OPTIMIZATION = 2,
    SXD_ROUTER_TCAM_RESERVED = 3,
} sxd_router_optimization_type_t;


/**
 * ku_rtar_reg structure is used to store the RTAR register parameters
 */
struct ku_rtar_reg {
    sxd_router_tcam_operation_t    operation;
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
    RIGR_OP_ADD_RIF = 1,
    RIGR_OP_REMOVE_RIF = 2,
    RIGR_OP_REMOVE_ALL_RIFS = 3,
    RIGR_OP_UPDATE_RIF = 4,
} sxd_rigr_op_t;

/**
 * sxd_rigr_encoding_t enumerated type is used to indicates the
 * encoding of the router_interface_list field
 */
typedef enum sxd_rigr_encoding {
    ETH_ONLY = 0,
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

/**
 * sxd_rigr_v2_list_type_t enumerated type is used to indicate the
 * type of egress rif list encoded in the register
 */
typedef enum sxd_rigr_v2_list_type {
    RIGR_V2_ERIF_LIST = 0,
    RIGR_V2_BIT_VECTOR = 1,
    RIGR_V2_MPLS_ENCAP = 2,
    RIGR_V2_NVE_DECAP = 3,
    RIGR_V2_IPIP_ENCAP = 4,
} sxd_rigr_v2_list_type_t;

typedef struct sxd_rigr_v2_erif_list_entry {
    sxd_boolean_t valid;
    uint16_t      erif;
} sxd_rigr_v2_erif_list_entry_t;

#define SXD_RIGR_V2_ERIF_LIST_MAX  32
#define SXD_RIGR_V2_BIT_VECTOR_MAX 64

typedef struct sxd_rigr_v2_erif_list {
    sxd_boolean_t                 vrmid;
    uint32_t                      rmid_index;
    sxd_rigr_v2_erif_list_entry_t erifs[SXD_RIGR_V2_ERIF_LIST_MAX];
} sxd_rigr_v2_erif_list_t;

typedef struct sxd_rigr_v2_bit_vector {
    sxd_boolean_t vrmid;
    uint32_t      rmid_index;
    uint8_t       offset;
    sxd_boolean_t erif_bit_vector[SXD_RIGR_V2_BIT_VECTOR_MAX];
} sxd_rigr_v2_bit_vector_t;

typedef struct sxd_rigr_v2_mpls_encap {
    uint32_t nhlfe_ptr;
    uint16_t ecmp_size;
    uint16_t egress_rif;
} sxd_rigr_v2_mpls_encap_t;

typedef struct sxd_rigr_v2_nve_decap {
    uint16_t uerif;
} sxd_rigr_v2_nve_decap_t;

typedef struct sxd_rigr_v2_ip_in_ip_encap {
    sxd_router_route_type_t ipip_type;
    uint32_t                ipv4_udip;
    uint32_t                ipv6_ptr;
    uint16_t                egress_rif;
} sxd_rigr_v2_ip_in_ip_encap_t;

typedef union sxd_rigr_v2_erifs {
    sxd_rigr_v2_erif_list_t      erif_list;
    sxd_rigr_v2_bit_vector_t     bit_vector;
    sxd_rigr_v2_mpls_encap_t     mpls_encap;
    sxd_rigr_v2_nve_decap_t      nve_decap;
    sxd_rigr_v2_ip_in_ip_encap_t ipip_encap;
} sxd_rigr_v2_erifs_t;

/**
 * ku_rigr_v2_reg structure is used to store the RIGRv2 register parameters
 */
struct ku_rigr_v2_reg {
    sxd_rigr_v2_list_type_t list_type;
    uint32_t                rigr_index;
    sxd_boolean_t           vnext;
    uint32_t                next_rigr_index;
    sxd_rigr_v2_erifs_t     erifs;
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
    uint8_t  router_interface_mac[6];
    uint8_t  vrrp_id_ipv6;
    uint8_t  vrrp_id_ipv4;
} ku_router_fid_interface_properties_t;


/**
 * ku_router_sub_port_interface_properties_t struct is used to store the router interface properties when the router interface type is sub_port.
 */
typedef struct ku_router_sub_port_interface_properties {
    uint8_t  lag;
    uint16_t system_port;
    uint16_t efid;
    uint8_t  router_interface_mac[6];
    uint16_t vlan_id;
    uint8_t  vrrp_id_ipv6;
    uint8_t  vrrp_id_ipv4;
} ku_router_sub_port_interface_properties_t;

/**
 * ku_router_tunnel_interface_properties_t struct is used to store the router interface properties when the router interface type is tunnel.
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
 * ku_router_loopback_interface_properties_t struct is used to store
 * the router interface properties when the router interface
 * type is tunnel.
 */
typedef struct ku_router_loopback_interface_properties {
    uint8_t protocol;
    union {
        ku_router_l3_tunnel_interface_properties_t l3_tunnel_interface;
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
    VLAN_INTERFACE = 0,
    IB_SWID_INTERFACE = 1,
    FID_INTERFACE = 2,
    IB_SWID_PORT_INTERFACE = 3,
    SUB_PORT_INTERFACE = 4,
    IB_PORT_INTERFACE = 5,
    LOOPBACK_INTERFACE = 6,
    PKEY_INTERFACE = 8,
    INTERFACE_MIN = VLAN_INTERFACE,
    INTERFACE_MAX = PKEY_INTERFACE
} sxd_router_interface_type_t;

/**
 * sxd_router_interface_op_t enumerated type is used to indicates the router interface op
 */
typedef enum sxd_router_interface_op {
    INTERFACE_CREATE_OR_EDIT = 0,
    INTERFACE_DELETE = 1
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
 * ku_fitr_reg structure is used to store the FITR register parameters
 */
struct ku_fitr_reg {
    uint8_t      valid;
    sxd_fcf_id_t fcf;
    uint8_t      fc_map[3];
    uint8_t      prio; /**< prio - static VLAN prio for FCF egress traffic */
    uint16_t     vid; /**< vid - VLAN Identifier */
};

/**
 * sxd_ritr_loopback_protocol_t enumerated type is used to note the possible loopback protocols.
 */
typedef enum sxd_ritr_loopback_protocol {
    SXD_ROUTER_LOOPBACK_PROTOCOL_IPV4 = 0,
    SXD_ROUTER_LOOPBACK_PROTOCOL_IPV6 = 1,
    SXD_ROUTER_LOOPBACK_PROTOCOL_GENERIC = 2,
} sxd_ritr_loopback_protocol_t;

/**
 * sxd_ritr_ipinip_tunnel_encap_type_t enumerated type is used to note the possible encapsulation types.
 */
typedef enum sxd_ritr_ipinip_tunnel_encap_type {
    SXD_TUNNEL_ENCAP_TYPE_IP_IN_IP = 0,            /**< Tunnel is IPinIP */
    SXD_TUNNEL_ENCAP_TYPE_IP_IN_GRE_IN_IP = 1,     /**< Tunnel is GRE, no key */
    SXD_TUNNEL_ENCAP_TYPE_IP_IN_GRE_KEY_IN_IP = 2, /**< Tunnel is GRE, with a key */
} sxd_ritr_ipinip_tunnel_encap_type_t;

/**
 * sxd_ritr_ipinip_tunnel_options_t enumerated type is used to note the possible value of options field.
 *
 * Note: should be used only when encapsulation type is TUNNEL_ENCAP_TYPE_IP_IN_GRE_KEY_IN_IP.
 */
typedef enum sxd_ritr_ipinip_tunnel_options {
    SXD_TUNNEL_KEY_GRE_KEY = 0,           /**< The key is defined by gre_key */
    SXD_TUNNEL_KEY_GRE_KEY_FROM_HASH = 1, /**< The 24msbs of the key are set by ipip_gre_key_for_hash */
} sxd_ritr_ipinip_tunnel_options_t;

/**
 * sxd_router_interface_type_t enumerated type is used to indicates the router interface type
 */
typedef enum sxd_rgcr_rpf_mode {
    SXD_RGCR_RPF_MODE_ENABLE = 0,
    SXD_RGCR_RPF_MODE_DISABLE = 1,
} sxd_rgcr_rpf_mode_t;

typedef enum sxd_rgcr_pcp_rw_mode {
    SXD_RGCR_PCP_RW_MODE_PRESERVE = 0,
    SXD_RGCR_PCP_RW_MODE_DISABLE = 2,
    SXD_RGCR_PCP_RW_MODE_ENABLE = 3,
} sxd_rgcr_pcp_rw_mode_t;

typedef enum sxd_rgcr_usp_mode {
    SXD_RGCR_USP_MODE_PRESERVE = 0,
    SXD_RGCR_USP_MODE_RECALCULATE = 1,
} sxd_rgcr_usp_mode_t;

typedef enum sxd_rgcr_op_type {
    SXD_RGCR_OP_TYPE_OPTIMIZATION_NONE = 0,
    SXD_RGCR_OP_TYPE_OPTIMIZATION_SOFT = 1,
    SXD_RGCR_OP_TYPE_OPTIMIZATION_HARD = 2,
    SXD_RGCR_OP_TYPE_RESERVED = 3,
} sxd_rgcr_op_type_t;

/**
 * sxd_rgcr_packet_rate_t enumerated type is used to note the packet rate
 * for TCAM optimization mode. Granularity is 5%. Duplication number is used.
 */
typedef enum sxd_rgcr_packet_rate {
    SXD_RGCR_PACKET_RATE_0_PCT = 0,
    SXD_RGCR_PACKET_RATE_10_PCT = 2,
    SXD_RGCR_PACKET_RATE_20_PCT = 4,
    SXD_RGCR_PACKET_RATE_40_PCT = 8,
    SXD_RGCR_PACKET_RATE_80_PCT = 16,
} sxd_rgcr_packet_rate_t;

typedef enum sxd_rgcr_activity_dis {
    SXD_RGCR_ACTIVITY_ENABLED = 0,
    SXD_RGCR_ACTIVITY_DISABLED = 1,
} sxd_rgcr_activity_dis_t;

typedef enum sxd_rgcr_mpls_enable {
    SXD_RGCR_MPLS_DISABLE = 0,
    SXD_RGCR_MPLS_ENABLE = 1,
} sxd_rgcr_mpls_enable_t;

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
 * ku_fgcr_reg structure is used to store the FGCR register parameters
 */
struct ku_fgcr_reg {
    uint8_t  fcf_enable;
    uint16_t max_fcf_instances;
    uint16_t max_ve_ports;
    uint8_t  fcf_mac[6];
};

/**
 * ku_fvet_reg structure is used to store the FVET register parameters
 */
struct ku_fvet_reg {
    uint8_t  valid;
    uint16_t ve_port_id;
    uint8_t  dmac[6];
};

/**
 * ku_fipl_reg structure is used to store the FIPL register parameters
 */
struct ku_fipl_reg {
    uint8_t ipl[0x000000FF + 1];
    uint8_t ipl_mask[0x000000FF + 1];
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
    SXD_ROUTER_COUNTER_OPERATION_NOP = 0,
    SXD_ROUTER_COUNTER_OPERATION_ALLOCATE = 1,
    SXD_ROUTER_COUNTER_OPERATION_TEST = 2,
    SXD_ROUTER_COUNTER_OPERATION_FREE = 3,
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
    SXD_RALTA_OPERATION_ALLOCATE = 0,
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

/**
 * ku_ralta_reg structure is used to store the RALTA register parameters
 */
struct ku_ralta_reg {
    sxd_ralta_operation_t   operation;
    sxd_router_route_type_t protocol;
    uint8_t                 tree_id;
};

/*
 * Maximum LPM/SHSPM bins (= IPv6 maximum prefix length)
 */
#define SXD_RALST_MAX_BIN 128

/*
 * Tree terminator magic number. Denotes no-child
 */
#define SXD_RALST_NO_CHILD 0xFF

/**
 * Stores child bins of a bin in a SHSPM tree
 */
typedef struct sxd_ralst_children {
    uint8_t left_child;
    uint8_t right_child;
} sxd_ralst_children_t;

/**
 * ku_ralst_reg structure is used to store the RALST register parameters
 */
struct ku_ralst_reg {
    uint8_t              root_bin;
    uint8_t              tree_id;
    sxd_ralst_children_t structure[SXD_RALST_MAX_BIN];
};

/**
 * ku_raltb_reg structure is used to store the RALTB register parameters
 */
struct ku_raltb_reg {
    sxd_vrid_t              router;
    sxd_router_route_type_t protocol;
    uint8_t                 tree_id;
};

/**
 * sxd_ralue_format_t enumerated type is used to note the
 * format for RALUE register.
 */
typedef enum sxd_ralue_action_type {
    SXD_RALUE_ACTION_TYPE_REMOTE = 0,
    SXD_RALUE_ACTION_TYPE_LOCAL = 1,
    SXD_RALUE_ACTION_TYPE_IP2ME = 2,
} sxd_ralue_action_type_t;

/**
 * sxd_ralue_type_t enumerated type is used to note the
 * type of RALUE register.
 */
typedef enum sxd_ralue_type {
    SXD_RALUE_TYPE_MARKER = 1,
    SXD_RALUE_TYPE_ROUTE = 2,
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
 * ku_ralue_action structure is used to store the RALUE action field parameters
 */
union ku_ralue_action {
    struct ku_ralue_action_remote remote;
    struct ku_ralue_action_local  local;
    struct ku_ralue_action_ip2me  ip2me;
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

/**
 * ku_raleu_reg structure is used to store the RALEU register parameters
 */
struct ku_raleu_reg {
    sxd_router_route_type_t protocol;
    sxd_vrid_t              router;
    uint32_t                old_adjacency_index;
    uint16_t                old_ecmp_size;
    uint32_t                new_adjacency_index;
    uint16_t                new_ecmp_size;
};

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
    SXD_TCA_LOG_PSTATE_DOWN = 0,
    SXD_TCA_LOG_PSTATE_INIT = 1,
    SXD_TCA_LOG_PSTATE_ARM = 2,
    SXD_TCA_LOG_PSTATE_ACTIVE = 3,
} sxd_tca_log_pstate_type_t;

/**
 * sxd_tca_ phy_pstate_type_t enumerated type is used to indicates the TCA physical port state type
 */
typedef enum sxd_tca_phy_pstate_type {
    SXD_TCA_PHY_PSTATE_DOWN = 0,
    SXD_TCA_PHY_PSTATE_POLLING = 1,
    SXD_TCA_PHY_PSTATE_UP = 2,
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
 * ku_pspa_reg structure is used to store the PSPA register parameters
 */
struct ku_pspa_reg {
    uint8_t swid; /**< swid - Switch partition ID */
    uint8_t local_port; /**< local_port - local port number */
    uint8_t sub_port; /**< sub_port - sub port number */
};

/**
 * ku_pmlp_reg structure is used to store the PMLP register parameters
 */
struct ku_pmlp_reg {
    uint8_t use_different_rx_tx; /** < use_different_rx_tx - use different rx and tx lanes */
    uint8_t autosplit;  /**< autosplit - AutoSplit configuration */
    uint8_t local_port; /**< local_port - local port number */
    uint8_t width;  /**< width - width */
    uint8_t lane[NUMBER_OF_SERDESES]; /**< lane - Lane - up to 8 serdeses in a module can be mapped to a local port */
    uint8_t rx_lane[NUMBER_OF_SERDESES]; /**< lane - Lane - up to 8 serdeses in a module can be mapped to a local port */
    uint8_t module[NUMBER_OF_SERDESES]; /**< module - Module number */
};

#define SXD_MGIR_HW_DEV_ID_SX          0xc738
#define SXD_MGIR_HW_DEV_ID_SWITCH_IB   0xcb20
#define SXD_MGIR_HW_DEV_ID_SPECTRUM    0xcb84
#define SXD_MGIR_HW_DEV_ID_SWITCH_IB2  0xcf08
#define SXD_MGIR_HW_DEV_ID_QUANTUM     0xd2f0
#define SXD_MGIR_HW_DEV_ID_SPECTRUM2   0xcf6c
#define SXD_MGIR_HW_REV_ID_A0          0xA0
#define SXD_MGIR_HW_REV_ID_A1          0xA1
#define SXD_MGIR_HW_REV_ID_A2          0xA2
#define SXD_MGIR_HW_REV_ID_SX_A0       SXD_MGIR_HW_REV_ID_A0
#define SXD_MGIR_HW_REV_ID_SX_A1       SXD_MGIR_HW_REV_ID_A1
#define SXD_MGIR_HW_REV_ID_SX_A2       SXD_MGIR_HW_REV_ID_A2
#define SXD_MGIR_HW_REV_ID_SWITCHIB_A0 SXD_MGIR_HW_REV_ID_A0
#define SXD_MGIR_HW_REV_ID_SLAVE_DEV   0xFF

struct ku_mgir_hw_info {
    uint16_t device_hw_revision;
    uint16_t device_id;
    uint8_t  dvfs;
    uint32_t uptime;
};
struct ku_mgir_fw_info {
    uint8_t  major;
    uint8_t  minor;
    uint8_t  sub_minor;
    uint32_t build_id;
    uint8_t  month;
    uint8_t  day;
    uint16_t year;
    uint16_t hour;
    uint8_t  psid[16];
    uint32_t ini_file_version;
    uint32_t extended_major;
    uint32_t extended_minor;
    uint32_t extended_sub_minor;
    uint16_t isfu_major;
};
struct ku_mgir_sw_info {
    uint8_t major;
    uint8_t minor;
    uint8_t sub_minor;
};

/**
 * ku_mgir_reg structure is used to store the MGIR register parameters
 */
struct ku_mgir_reg {
    struct ku_mgir_hw_info hw_info; /**< hw_info - HW information */
    struct ku_mgir_fw_info fw_info; /**< fw_info - FW information */
    struct ku_mgir_sw_info sw_info; /**< sw_info - SW information */
};

/**
 * ku_plib_reg structure is used to store the PLIB register parameters
 */
struct ku_plib_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t ib_port; /**< ib_port -  IB Port remapping for local_port or Label port remapping for local_port */
    uint8_t split_num; /**< split_num - Label split mapping for local_port */
};

/**
 * ku_pcnr_reg structure is used to store the PCNR register parameters
 */
struct ku_pcnr_reg {
    uint8_t local_port;       /**< local_port - local port number */
    uint8_t tuning_override; /**< tuning override - ENA/ DIS - enable PHY Fast boot mode */
};

/**
 * ku_pcmr_reg structure is used to store the PCMR register parameters
 */
struct ku_pcmr_reg {
    uint8_t local_port;        /**< local_port - local port number */
    uint8_t tx_fcs_recalc_cap; /**< tx_fcs_recalc_cap - Egress prevent CRC overwrite capability */
    uint8_t rx_fcs_drop_cap;   /**< rx_fcs_drop_cap - Ingress forward on bad CRC capability */
    uint8_t fcs_cap;           /**< fcs_cap - FCS check capability */
    uint8_t tx_fcs_recalc;     /**< tx_fcs_recalc - ENA/ DIS - enable Egress prevent CRC overwrite */
    uint8_t rx_fcs_drop;       /**< rx_fcs_drop - ENA/ DIS - enable Ingress forward on bad CRC */
    uint8_t fcs_chk;           /**< FCS check - ENA/ DIS - enable FCS check  */
};

/**
 * ku_spzr_reg structure is used to store the SPZR register parameters
 */
struct ku_spzr_reg {
    uint8_t                              swid; /**< swid - SWitch partition ID */
    uint8_t                              ndm; /**< ndm - Node description mask. Set to 1 to write the NodeDescription field */
    uint8_t                              EnhSwP0_mask; /**< EnhSwP0_mask - Enhanced Switch Port 0 mask */
    uint8_t                              cm; /**< cm - Set PortInfo:CapabilityMask to PortInfo:CapabilityMask specified */
    uint8_t                              vk; /**< vk - Set the internal GSA V_Key */
    uint8_t                              mp; /**< mp - Change PKey table size to max_pkey */
    uint8_t                              sig; /**< sig - Set System Image GUID to system_image_guid specified */
    uint8_t                              ng; /**< ng - Set node GUID to node_guid specified */
    uint8_t                              g0; /**< g0 - Set port GUID0 to GUID0 specified */
    uint8_t                              EnhSwP0; /**< EnhSwP0 - When set, it enables Enhanced Switch Port 0. Reported in NodeInfo */
    uint32_t                             capability_mask; /**< capability_mask - Sets the PortInfoCapabilityMask: Specifies the supported capabilities of this node */
    uint64_t __attribute__((aligned(8))) system_image_guid_h_l; /**< system_image_guid_h_l - System Image GUID, takes effect only if the sig bit is set */
    uint64_t __attribute__((aligned(8))) guid0_h_l; /**< guid0_h_l - EUI-64 GUID assigned by the manufacturer */
    uint64_t __attribute__((aligned(8))) node_guid_h_l; /**< node_guid_h_l - Node GUID must be the same for both ports */
    uint32_t                             v_key_h; /**< v_key_h - The internal GSA V_Key (high) */
    uint32_t                             v_key_l; /**< v_key_l - The internal GSA V_Key (low) */
    uint16_t                             max_pkey; /**< max_pkey - max_pkey is derived from the profile - no set. Maximum pkeys for the port */
    uint8_t                              NodeDescription[SX_IB_NODE_DESCRIPTION_LEN]; /**< NodeDescription - Text string that describes the node */
};

/**
 * ku_ppaos_reg structure is used to store the PPAOS register parameters
 */
struct ku_ppaos_reg {
    uint8_t swid;  /**< swid - Switch Partition ID to associate port with */
    uint8_t local_port; /**< local_port - local port number */
    uint8_t phy_test_mode_admin; /**< phy_test_mode_admin - Port extended administrative down status */
    uint8_t phy_test_mode_status; /**< phy_test_mode_status - Port extended down status */
};

/**
 * ku_pptt_reg structure is used to store the PPTT register parameters
 */
struct ku_pptt_reg {
    uint8_t  e;    /**< e - Enable PRBS test mode bit */
    uint8_t  local_port;    /**< local_port - local port number */
    uint8_t  pnat;    /**< pnat - Port number access type. determines the way local_port is interpreted */
    uint32_t prbs_modes_cap;    /**< prbs_modes_cap - PRBS capability (bitmask)*/
    uint8_t  prbs_mode_admin;    /**< prbs_mode_admin - PRBS Administratively capability (bitmask) */
    uint16_t lane_rate_cap;    /**< lane_rate_cap - Per lane rate capability (bitmask) */
    uint16_t lane_rate_admin;    /**< lane_rate_admin - Lane rate be used in PRBS */
};

/**
 * ku_pprt_reg structure is used to store the PPRT register parameters
 */
struct ku_pprt_reg {
    uint8_t  e;    /**< e - Enable PRBS test mode bit */
    uint8_t  s;    /**< s - Start tuning */
    uint8_t  local_port;    /**< local_port - local port number */
    uint8_t  pnat;    /**< pnat - Port number access type. determines the way local_port is interpreted */
    uint32_t prbs_modes_cap;    /**< prbs_modes_cap - PRBS capability (bitmask)*/
    uint8_t  prbs_mode_admin;    /**< prbs_mode_admin - PRBS Administratively capability (bitmask) */
    uint16_t lane_rate_cap;    /**< lane_rate_cap - Per lane rate capability (bitmask) */
    uint16_t lane_rate_oper;    /**< lane_rate_admin - Lane rate be used in PRBS */
    uint8_t  rx_tuning_status;   /**< rx_tuning_status - Tuning status */
    uint8_t  lock_status;   /**< lock_status - lock on PRBS pattern status */
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
    uint8_t  port_profile_mode; /**< port_profile_mode - Port profile modes (bitmask) */
    uint8_t  static_port_profile; /**< static_port_profile - Valid when Media based port profile is cleared, used to set the static port's profile index. */
    uint8_t  active_port_profile; /**< active_port_profile - The port's active Profile ID */
    uint8_t  retransmission_active; /**< retransmission_active - Active Retransmission */
    uint32_t fec_mode_active; /**< fec_mode_active - Acive FEC (bitmask) */
    uint8_t  rs_fec_correction_bypass_cap; /**< RS-FEC correction bypass override capability */
    uint8_t  fec_override_cap_56g; /**< 56GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_100g; /**< 100GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_50g; /**< 50GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_25g; /**< 25GE Ethernet FEC override capability bitmask */
    uint8_t  fec_override_cap_10g_40g; /**< 10/40GE Ethernet FEC override capability bitmask */
    uint8_t  rs_fec_correction_bypass_admin; /**< RS-FEC correction bypass override admin */
    uint8_t  fec_override_admin_56g; /**< 56GE Ethernet FEC override admin */
    uint8_t  fec_override_admin_100g; /**< 100GE Ethernet FEC override admin */
    uint8_t  fec_override_admin_50g; /**< 50GE Ethernet FEC override admin */
    uint8_t  fec_override_admin_25g; /**< 25GE Ethernet FEC override capability admin */
    uint8_t  fec_override_admin_10g_40g; /**< 10/40GE Ethernet FEC override capability admin */
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
 * ku_pmaos_reg structure is used to store the PMAOS register parameters
 */
struct ku_pmaos_reg {
    uint8_t module; /**< module - Module number */
    uint8_t admin_status; /**< admin_status - Port administrative state (the desired state of the interface) */
    uint8_t oper_status; /**< oper_status - Port operational state */
    uint8_t ase; /**< ase - Admin State Update Enable */
    uint8_t ee; /**< ee - Event Update Enable */
    uint8_t error_type; /**< error_type - Module error details */
    uint8_t e; /**< e - Event Generation on operational state change */
    uint8_t rst; /**< rst - Module Reset Toggle */
};

/**
 * ku_pmtu_reg structure is used to store the PMTU register parameters
 */
struct ku_pmtu_reg {
    uint8_t  local_port; /**< local_port - local port number */
    uint16_t max_mtu; /**< max_mtu - Maximum MTU supported on the port (Read Only) */
    uint16_t admin_mtu; /**< admin_mtu - Administratively configured MTU on the port */
    uint16_t oper_mtu; /**< oper_mtu - Operational MTU */
};

/**
 * ku_pmcr_reg structure is used to store the PMCR register parameters
 */
struct ku_pmcr_reg {
    uint8_t local_port; /**< local_port - local port number (Index) */
    uint8_t tx_disable_override_value;
    uint8_t tx_disable_override_cntl;
    uint8_t cdr_override_cntl; /**< cdr_override_cntl - Module CDR override control (Read/Write) */
    uint8_t cdr_override_value; /**< cdr_override_value - Module CDR override value (Read/Write) */
    uint8_t rx_amp_override_cntl; /**< rx_amp_override_cntl - Module RX amplitude override control (Read/Write) */
    uint8_t rx_amp_override_value; /**< rx_amp_override_value - Module RX amplitude value (Read/Write) */
    uint8_t rx_emp_override_cntl; /**< rx_emp_override_cntl - Module RX emphasis override control (Read/Write) */
    uint8_t rx_emp_override_value; /**< rx_emp_override_value - Module RX emphasis value (Read/Write) */
    uint8_t tx_equ_override_cntl; /**< tx_equ_override_cntl - Module TX equalization override control (Read/Write) */
    uint8_t tx_equ_override_value; /**< tx_equ_override_value - Module TX equalization value (Read/Write) */
};

/**
 * ku_pfsc_reg structure is used to store the PFSC register parameters
 */
struct ku_pfsc_reg {
    uint8_t local_port; /**< local_port - local port number */
    uint8_t fwd_admin; /**< fwd_admin - Administratively configured of Forward switching for Egress */
    uint8_t fwd_oper; /**< fwd_oper - Operational Egress Forward switching */
};

/**
 * ku_pmmp_reg structure is used to store the PMMP register parameters
 */
struct ku_pmmp_reg {
    uint8_t  module; /**< module - Module number */
    uint16_t eeprom_override; /**< eeprom_override - override EEPROM bitmask */
    uint8_t  qsfp_cable_breakout;  /**< qsfp cable breakout. */
    uint8_t  qsfp_ethernet_compliance_code; /**< Ethernet compliance code bitmask (10/40/100G). */
    uint8_t  qsfp_ext_ethernet_compliance_code; /**< Extended specification compliance codes. */
    uint8_t  qsfp_giga_ethernet_compliance_code; /**< Giga Ethernet compliance codes. */
    uint8_t  sfp_bit_rate;               /**< sfp bitrate. */
    uint8_t  sfp_cable_technology;       /**< sfp+ cable technology. */
    uint8_t  sfp_tengig_ethernet_compliance_code; /**< 10G Ethernet compliance code */
    uint8_t  sfp_ext_ethernet_compliance_code; /**< Extended specification compliance codes. */
    uint8_t  sfp_ethernet_compliance_code; /**< Ethernet compliance codes. */
    uint8_t  cable_length;    /**< Length of cable assembly, units of 1m. */
    uint8_t  attenuation_12g; /**< total channel attenuation @ 12GHz in db. */
    uint8_t  attenuation_7g;  /**< total channel attenuation @ 7GHz in db. */
    uint8_t  attenuation_5g;  /**< total channel attenuation @ 5GHz in db. */
    uint8_t  module_identifier; /**< module identifier (SFP, QSFP, etc)  **/
};

/**
 * ku_sbcm_reg structure is used to store the SBCM register parameters
 */
struct ku_sbcm_reg {
    uint8_t  desc; /**< desc - Descriptor buffer */
    uint8_t  local_port; /**< local_port - Local port number */
    uint8_t  pg_buff; /**< pg_buff - Port PG */
    uint8_t  dir; /**< dir - Direction */
    uint8_t  infinite_size; /**< infinite_size - pool with inifinite size. When set size is reserved */
    uint32_t buff_occupancy; /**< buff_occupancy - Current buffer occupancy */
    uint32_t max_buff_occupancy; /**< max_buff_occupancy - Maximum value of buffer occupancy monitored */
    uint32_t clr; /**< clr - Clear max buffer occupancy - when set the max value is cleared */
    uint32_t min_buff; /**< min_buff - Minimum buffer size for the limiter */
    uint32_t max_buff; /**< max_buff - Maximum buffer size for the limiter in cells or "alpha" */
    uint8_t  pool; /**< pool - Association of the port-priority to a pool*/
};

/**
 * ku_sbpm_reg structure is used to store the SBPM register parameters
 */
struct ku_sbpm_reg {
    uint8_t  desc; /**< desc - Descriptor buffer */
    uint8_t  local_port; /**< local_port - Local port number */
    uint8_t  pool; /**< pool - Association of the port-priority to a pool*/
    uint8_t  dir; /**< dir - Direction */
    uint8_t  infinite_size; /**< infinite_size - buff with inifinite size. When set size is reserved */
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
    uint8_t  infinite_size; /**< infinite_size - buff with inifinite size. When set size is reserved */
    uint32_t buff_occupancy; /**< buff_occupancy - Current buffer occupancy */
    uint32_t max_buff_occupancy; /**< max_buff_occupancy - Maximum value of buffer occupancy monitored */
    uint32_t clr; /**< clr - Clear max buffer occupancy - when set the max value is cleared */
    uint32_t min_buff; /**< min_buff - Minimum buffer size for the limiter */
    uint32_t max_buff; /**< max_buff - Maximum buffer size for the limiter in cells or "alpha" */
    uint8_t  pool; /**< pool - Association of the switch priority to a pool*/
};

/**
 * ku_pplr_reg structure is used to store the PPLR register
 * parameters
 */
struct ku_pplr_reg {
    uint8_t local_port; /**< local_port - Local port number */
    uint8_t el; /**< el - Egress Loopback Enable */
    uint8_t il; /**< il - Ingress Loopback Enable */
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
 * ku_mtcap_reg structure is used to store the MTCAP register parameters
 */
struct ku_mtcap_reg {
    uint8_t sensor_count; /**< sensor_count - Number of sensors supported by the device */
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
    uint16_t block_allignment; /**< block_allignment - Required allignment for block access */
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
 * ku_qcap_reg structure is used to store the QCAP register parameters
 */
struct ku_qcap_reg {
    uint8_t max_policers_per_port; /**< max_policers_per_port - Maximum number of policers available per port */
    uint8_t max_policers_global; /**< max_policers_global - Maximum number of global policers */
};

/**
 * ku_raw_reg structure is used to store the RAW register parameters
 */
struct ku_raw_reg {
    uint8_t *buff;     /**< buff - the register buffer */
    uint16_t size;    /**< size - the buffer size */
};

/**
 * ku_mtwe_reg structure is used to store the MTWE register parameters
 */
struct ku_mtwe_reg {
    uint8_t sensor_warning; /**< sensor_warning - Bit vector indicating which of the sensor reading is above threshold */
};

/**
 * ku_pelc_reg structure is used to store the PELC register parameters
 */
struct ku_pelc_reg {
    uint8_t                              op; /**< Operation - 0 - FEC control 1 - LLR control*/
    uint8_t                              local_port; /**< local_port - Local port number */
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
 * ku_spad_reg structure is used to store the SPAD register parameters
 */
struct ku_spad_reg {
    uint64_t __attribute__((aligned(8))) base_mac; /**< base_mac - Base MAC address */
};

/**
 * ku_pvlc_reg structure is used to store the PVLC register parameters
 */
struct ku_pvlc_reg {
    uint8_t local_port; /**< local_port - Local port number */
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
    uint8_t prio_mask_tx; /**< prio_mask_tx - Bit per prio inticating if TX flow control policy should be updated based on the below */
    uint8_t prio_mask_rx; /**< prio_mask_rx - Bit per prio inticating if RX flow control policy should be updated based on the below */
    uint8_t pause_policy_tx; /**< pause_policy_tx - Pause policy on TX */
    uint8_t prio_policy_tx; /**< prio_policy_tx - Priority based Flow Control policy on TX */
    uint8_t cb_policy_tx; /**< cb_policy_tx - Credit Based Flow control policy in TX */
    uint8_t pause_policy_rx; /**< pause_policy_rx - Pause policy on RX */
    uint8_t prio_policy_rx; /**< prio_policy_rx - Priority based Flow Control policy on RX */
    uint8_t cb_policy_rx; /**< cb_policy_rx - Credit Based Flow control policy in RX */
};

/**
 * ku_pcap_reg structure is used to store the PCAP register parameters
 */
struct ku_pcap_reg {
    uint8_t  local_port; /**< local_port - Local port number */
    uint32_t port_capability_mask[4]; /**< port_capability_mask - Sets the PortInfoCapabilityMask */
};

/**
 * ku_pude_reg structure is used to store the PUDE register parameters
 */
struct ku_pude_reg {
    uint8_t swid; /**< swid - Switch ID */
    uint8_t local_port; /**< local_port - Local port number */
    uint8_t oper_status; /**< oper_status - Port operational state */
};

/**
 * ku_pmpe_reg structure is used to store the PMPE register parameters
 */
struct ku_pmpe_reg {
    uint8_t module_id; /**< module_id - Port module number */
    uint8_t oper_status; /**< oper_status - Port operational state */
    uint8_t error_type;
};

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
    uint8_t                              clear_count; /**< clear_count - clear counter */
    uint8_t                              enable; /**< enable - enable sampling on local_port */
    uint8_t                              cong; /**< cong - Congestion */
    uint32_t                             rate; /**< rate - sampling rate (total pkt/sampled pkt) */
    uint64_t __attribute__((aligned(8))) count_drops; /**< count_drops - count of frames after sampling */
};

/**
 * ku_mprs_reg structure is used to store the MPRS register parameters
 */
struct ku_mprs_reg {
    uint16_t parsing_depth;     /**< parsing_depth in bytes */
    uint16_t parsing_en;        /**< parsing enable */
    uint8_t  ctipl;             /**< cut through IP based */
    uint8_t  ctipl_l2_length;    /**< l2 header length to be added to ip length */
    uint16_t vxlan_udp_dport;    /**< VxLAN UDP dport */
};

/**
 * ku_mlcr_reg structure is used to store the MLCR register parameters
 */
struct ku_mlcr_reg {
    uint8_t  local_port;      /**< local_port - local port number */
    uint8_t  led_type;        /**< led_type - led type */
    uint8_t  cap_local_or_uid_only;        /**< cap_local_or_uid_only - cap local or uid only */
    uint16_t beacon_duration; /**< beacon_duration - duration of the beacon to be active */
    uint16_t beacon_remain;   /**< beacon_remain - remaining duration of the beacon */
};

/**
 * mpgcr_mpls_et
 */
typedef enum mpgcr_mpls_et {
    MPGCR_ET8847 = 1,
    MPGCR_ET8848 = 2,
    MPGCR_ET8847_ET8848 = 3,
} mpgcr_mpls_et_t;

/**
 * mpgcr_pcp_rw
 */
typedef enum mpgcr_pcp_rw {
    MPGCR_PCPRW_PRESERVE = 0,
    MPGCR_PCPRW_DISABLE = 2,
    MPGCR_PCPRW_ENABLE = 3
} mpgcr_pcp_rw_t;

/**
 * mpgcr_ler_exp_rw
 */
typedef enum mpgcr_ler_exp_rw {
    MPGCR_LER_EXP_DISABLE = 2,
    MPGCR_LER_EXP_ENABLE = 3
} mpgcr_ler_exp_rw_t;

/**
 * mpgcr_lsr_egress_ttl
 */
typedef enum mpgcr_lsr_egress_ttl {
    MPGCR_LSR_EGRESS_TTL_POPPED = 1,
    MPGCR_LSR_EGRESS_TTL_MIN = 2,
} mpgcr_lsr_egress_ttl_t;

/**
 * mpgcr_egress_ler_ttl
 */
typedef enum mpgcr_egress_ler_ttl {
    MPGCR_EGRESS_LER_TTL_PRESERVE = 0,
    MPGCR_EGRESS_LER_TTL_POPPED = 1,
    MPGCR_EGRESS_LER_TTL_MIN = 2,
} mpgcr_egress_ler_ttl_t;

/**
 * mpgcr_ingress_ler_ttl
 */
typedef enum mpgcr_ingress_ler_ttl {
    MPGCR_INGRESS_LER_TTL_IP = 0,
    MPGCR_INGRESS_LER_TTL_CONFIG = 1,
} mpgcr_ingress_ler_ttl_t;

/**
 * mpgcr_activity_dis_mpnhlfe
 */
typedef enum mpgcr_activity_dis_mpnhlfe {
    MPGCR_ACTIVITY_MPNHLFE_ENABLE = 0,
    MPGCR_ACTIVITY_MPNHLFE_DISABLE = 1,
} mpgcr_activity_dis_mpnhlfe_t;

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
    NHLFE_DSCP_RE_SET = 1,
    NHLFE_DSCP_RE_CLEAR = 2
} nhlfe_dscp_or_exp_rw_t;

/**
 * nhlfe_label_action_t structure enumerates types how to handle push action
 */
typedef enum nhlfe_label_action {
    NHLFE_LABEL_ACTION_NO_PHP = 0,
    NHLFE_LABEL_ACTION_PHP = 1,
    NHLFE_LABEL_ACTION_PUSH_LABEL = 2,
    NHLFE_LABEL_ACTION_PUSH_ENTROPY_LABEL = 3,
    NHLFE_LABEL_ACTION_PUSH_ENTROPY_LABEL_AND_LABEL = 4
} nhlfe_label_action_t;


/**
 * Forward to Ethernet Parameters
 */
typedef struct ku_struct_forward_to_eth_parameters {
    nhlfe_dscp_or_exp_rw_t dscp_rw;
    uint8_t                usp_dscp;
    uint8_t                usp_exp;
    nhlfe_dscp_or_exp_rw_t exp_rw;
    uint8_t                set_exp;
    uint8_t                exp;
    uint8_t                expected_ip_var;
    nhlfe_label_action_t   label_action;
    uint32_t               label_id;
    uint8_t                destination_mac[6];
    uint16_t               egress_router_interface;
    uint8_t                protection_en;
    uint8_t                protection_active;
    uint32_t               protection_nhlfe_ptr;
} ku_forward_to_eth_parameters_t;

/**
 * Forward to IP Router Parameters
 */
typedef struct ku_struct_forward_to_ip_parameters {
    nhlfe_dscp_or_exp_rw_t dscp_rw;
    uint8_t                usp_dscp;
    uint8_t                irifv;
    uint16_t               irif;
    uint8_t                erifv;
    uint16_t               egress_router_interface;
} ku_forward_to_ip_parameters_t;

/**
 * Forward to Continue Lookups Parameters
 */
typedef struct ku_continue_lookup_layout_parameters {
    nhlfe_dscp_or_exp_rw_t dscp_rw;
    uint8_t                usp_dscp;
    uint8_t                irifv;
    uint16_t               irif;
    uint8_t                erifv;
    uint16_t               egress_router_interface;
} ku_continue_lookup_layout_parameters_t;

/**
 * Forward to Next NHLFE Parameters
 */
typedef struct ku_next_nhlfe_layout_parameters {
    nhlfe_label_action_t label_action;
    uint32_t             label_id;
    uint32_t             next_nhlfe;
    uint16_t             ecmp_size;
} ku_next_nhlfe_layout_parameters_t;

/*
 * MPNHLFE - nhlfe_parameters
 */
typedef union ku_nhlfe_parameters {
    ku_forward_to_eth_parameters_t         forward_to_eth_parameters;
    ku_forward_to_ip_parameters_t          forward_to_ip_parameters;
    ku_continue_lookup_layout_parameters_t continue_lookup_layout_parameters;
    ku_next_nhlfe_layout_parameters_t      next_nhlfe_layout_parametrs;
} ku_nhlfe_parameters_t;

/**
 * ku_mpnhlfe_reg structure is used to store the MPNHLFE register parameters
 */
struct ku_mpnhlfe_reg {
    uint8_t                ca; /**< ca - clear activity */
    uint8_t                a; /**< a - activity  */
    uint8_t                v; /**< v - valid indication */
    uint32_t               nhlfe_ptr; /**<nhlfe_ptr - index in the NHLFE table  */
    sxd_forward_action_t   forward_action; /**<forward_action - NHLFE action */
    sxd_router_en_action_t trap_action; /**<trap_action - trap action */
    uint16_t               trap_id; /**<trap_id - trap ID */
    sxd_counter_set_t      counter_set; /**<counter_set - counter set */
    ku_nhlfe_parameters_t  nhlfe_parameters; /**<nhlfe_parameters - NHLFE parameters */
};

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
 * ku_ppcnt_ib_port_counters structure is used to store the PPCNT register Infiniband
 * port counters parameters
 */
struct ku_ppcnt_ib_port_counters {
    uint16_t symbol_error_counter;
    uint8_t  link_error_recovery_counter;
    uint8_t  link_downed_counter;
    uint16_t port_rcv_errors;
    uint16_t port_rcv_remote_physical_errors;
    uint16_t port_rcv_switch_relay_errors;
    uint16_t port_xmit_discards;
    uint8_t  port_xmit_constraint_errors;
    uint8_t  port_rcv_constraint_errors;
    uint8_t  local_link_integrity_errors;
    uint8_t  excessive_buffer_overrun_errors;
    uint16_t vl_15_dropped;
    uint32_t port_xmit_data;
    uint32_t port_rcv_data;
    uint32_t port_xmit_pkts;
    uint32_t port_rcv_pkts;
    uint32_t port_xmit_wait;
};


/**
 * ku_ppcnt_ib_port_counters_extended structure is used to store the PPCNT register Infiniband
 * port counters extended parameters
 */
struct ku_ppcnt_ib_port_counters_extended {
    uint64_t __attribute__((aligned(8))) port_xmit_data;
    uint64_t __attribute__((aligned(8))) port_rcv_data;
    uint64_t __attribute__((aligned(8))) port_xmit_pkts;
    uint64_t __attribute__((aligned(8))) port_rcv_pkts;
    uint64_t __attribute__((aligned(8))) port_unicast_xmit_pkts;
    uint64_t __attribute__((aligned(8))) port_unicast_rcv_pkts;
    uint64_t __attribute__((aligned(8))) port_multicast_xmit_pkts;
    uint64_t __attribute__((aligned(8))) port_multicast_rcv_pkts;
};

/**
 * ku_ppcnt_ib_port_rcv_err_details structure is used to store the PPCNT register Infiniband
 * port receive error details parameters
 */
struct ku_ppcnt_ib_port_rcv_err_details {
    uint16_t port_local_physical_errors;
    uint16_t port_malformed_packet_errors;
    uint16_t port_buffer_overrun_errors;
    uint16_t port_dlid_mapping_errors;
    uint16_t port_vl_mapping_errors;
    uint16_t port_looping_errors;
};

/**
 * ku_ppcnt_ib_port_xmit_discard_details structure is used to store the PPCNT register Infiniband
 * port xmit discard details parameters
 */
struct ku_ppcnt_ib_port_xmit_discard_details {
    uint16_t port_inactive_discards;
    uint16_t port_neighbor_mtu_discards;
    uint16_t port_sw_lifetime_limit_discards;
    uint16_t port_sw_hoq_lifetime_limit_discards;
};

/**
 * ku_ppcnt_ib_port_flow_ctl_counters structure is used to store the PPCNT register Infiniband
 * port flow control counters parameters
 */
struct ku_ppcnt_ib_port_flow_ctl_counters {
    uint32_t port_xmit_flow_pkts;
    uint32_t port_rcv_flow_pkts;
};

/**
 * ku_ppcnt_ib_port_vl_xmit_wait_counters structure is used to store the PPCNT register Infiniband
 * port VL xmit wait counters parameters
 */
struct ku_ppcnt_ib_port_vl_xmit_wait_counters {
    uint16_t port_vl_xmit_wait_0;
    uint16_t port_vl_xmit_wait_1;
    uint16_t port_vl_xmit_wait_2;
    uint16_t port_vl_xmit_wait_3;
    uint16_t port_vl_xmit_wait_4;
    uint16_t port_vl_xmit_wait_5;
    uint16_t port_vl_xmit_wait_6;
    uint16_t port_vl_xmit_wait_7;
    uint16_t port_vl_xmit_wait_8;
    uint16_t port_vl_xmit_wait_9;
    uint16_t port_vl_xmit_wait_10;
    uint16_t port_vl_xmit_wait_11;
    uint16_t port_vl_xmit_wait_12;
    uint16_t port_vl_xmit_wait_13;
    uint16_t port_vl_xmit_wait_14;
    uint16_t port_vl_xmit_wait_15;
};

/**
 * ku_ppcnt_ib_port_sw_port_vl_congestion structure is used to store the PPCNT register Infiniband
 * port SW port vl congestion parameters
 */
struct ku_ppcnt_ib_port_sw_port_vl_congestion {
    uint16_t sw_port_vl_congestion_0;
    uint16_t sw_port_vl_congestion_1;
    uint16_t sw_port_vl_congestion_2;
    uint16_t sw_port_vl_congestion_3;
    uint16_t sw_port_vl_congestion_4;
    uint16_t sw_port_vl_congestion_5;
    uint16_t sw_port_vl_congestion_6;
    uint16_t sw_port_vl_congestion_7;
    uint16_t sw_port_vl_congestion_8;
    uint16_t sw_port_vl_congestion_9;
    uint16_t sw_port_vl_congestion_10;
    uint16_t sw_port_vl_congestion_11;
    uint16_t sw_port_vl_congestion_12;
    uint16_t sw_port_vl_congestion_13;
    uint16_t sw_port_vl_congestion_14;
    uint16_t sw_port_vl_congestion_15;
};

/**
 * ku_ppcnt_reg structure is used to store the PPCNT register parameters
 */
struct ku_ppcnt_reg {
    uint8_t swid; /**< swid - Switch Partition ID to associate port with */
    uint8_t local_port; /**< local_port - Local port number */
    uint8_t cntr_grp; /**< cntr_grp - Performance counter group */
    uint8_t clr; /**< clr - Clear Counters */
    uint8_t cntr_prio; /**< cntr_prio - Priority for counter set that support per priority. */
    union {
        uint64_t __attribute__((aligned(8)))          cntr_list[31]; /**< cntr_list - Counter set */
        struct ku_ppcnt_ib_port_counters              ib_port_counters;
        struct ku_ppcnt_ib_port_counters_extended     ib_port_counters_extended;
        struct ku_ppcnt_ib_port_rcv_err_details       ib_port_receive_error_details;
        struct ku_ppcnt_ib_port_xmit_discard_details  ib_port_xmit_discard_details;
        struct ku_ppcnt_ib_port_flow_ctl_counters     ib_port_flow_ctl_counters;
        struct ku_ppcnt_ib_port_vl_xmit_wait_counters ib_port_vl_xmit_wait_counters;
        struct ku_ppcnt_ib_port_sw_port_vl_congestion ib_port_sw_port_vl_congestion;
    } cntrs;
    uint32_t cntr_num; /**< cntr_num - Counter num */
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
    uint16_t           xof_timer_value; /**< xof_timer_value - When SwitchX generates a Pause frame, it uses this value as the Pause timer. */
    uint16_t           xof_refresh; /**< xof_refresh - The time before a new Pause frame should be sent to refresh the Pause state. Using the same units as xof_timer_value above. */
    uint16_t           port_buffer_size; /**< port_buffer_size - Total packet buffer array available for the port. The sum of buffer array allocated to bufferX must not exceed port_buffer_size. */
    struct ku_pbrl_reg buffer[10]; /**< buffer - Configuring per-buffer parameters */
    struct ku_pbrl_reg port_shared_buffer; /**< port_shared_buffer - Configuring port shared buffer parameters. Using the same layout as in BufferX */
};

/**
 * ku_pbsr_stat structure is used to PBSR buffer status value
 */
struct ku_pbsr_stat {
    uint16_t watermark; /**< Max buffer usage since last clear */
    uint16_t used_buffer; /**< Number of used buffer lines */
};

/**
 * ku_pbsr_reg structure is used to store the PBSR register parameters
 */
struct ku_pbsr_reg {
    uint8_t             buffer_type; /**< Port buffer type */
    uint8_t             local_port; /**< Local port number */
    uint8_t             clear_wm; /**< Clear watermark for all PGs */
    uint16_t            used_shared_headroom_buffer; /**< Number of currently used shared headroom buffer lines */
    struct ku_pbsr_stat stat_buffer[SXD_EMAD_PBSR_BUFFER_NUM]; /**< Status per buffer */
};

/**
 * sxd_sbpr_mode_e enumerated mode used in SBPR register event field
 */
typedef enum sxd_sbpr_mode {
    SXD_SBPR_MODE_STATIC_E = 0,
    SXD_SBPR_MODE_DYNAMIC_E = 1,
} sxd_sbpr_mode_e;


/**
 * ku_sbpr_reg structure is used to store the SBPR register parameters
 */
struct ku_sbpr_reg {
    uint8_t  desc; /**< desc - Descriptor buffer */
    uint8_t  direction; /**< Direction - Ingress/ Egress */
    uint8_t  pool_id; /**< pool_id - pool number 1-16 */
    uint8_t  infinite_size; /**< infinite_size - pool with inifinite size. When set size is reserved */
    uint32_t size; /**< size - pool size in buffers cells*/
    uint8_t  mode; /**< mode - Absolute/ Relative*/
    uint32_t current_occupancy; /**< current_buff occupancy*/
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
    uint32_t                    ingress_port_mask[SXD_EMAD_SBSR_PORT_MASK_SIZE]; /*< ingress port mask - 256 bits */
    uint32_t                    pg_buff_mask;
    uint32_t                    egress_port_mask[SXD_EMAD_SBSR_PORT_MASK_SIZE];
    uint32_t                    tclass_mask[SXD_EMAD_SBSR_TC_MASK_SIZE];
    struct shared_buffer_status sbstatus[SXD_EMAD_SBSR_MAX_RET_SIZE];
};

/**
 * ku_ppad_reg structure is used to store the PPAD register parameters
 */
struct ku_ppad_reg {
    uint8_t single_base_mac;
    uint8_t local_port;
    uint8_t mac[6]; /**< mac - Base MAC address */
};

/**
 * ku_ppsc_reg structure is used to store the PPSC register
 * parameters
 */
struct ku_ppsc_reg {
    uint8_t local_port; /**< local_port - local port number */
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

/**
 * ku_access_slcr_v2_reg structure is used to store the access register SLCR_V2 command parameters
 */
struct ku_access_slcr_v2_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_slcr_v2_reg   slcr_v2_reg; /**< ku_slcr_v2_reg - slcr_v2 register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_ptys_reg structure is used to store the access register PTYS command parameters
 */
struct ku_access_ptys_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ptys_reg      ptys_reg; /**< ptys_reg - ptys register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_qsptc_reg structure is used to store the access register QSPTC command parameters
 */
struct ku_access_qsptc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qsptc_reg     qsptc_reg; /**< qsptc_reg - qsptc register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_qstct_reg structure is used to store the access register QSTCT command parameters
 */
struct ku_access_qstct_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qstct_reg     qstct_reg; /**< qstct_reg - qstct_reg register tlv */
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
 * ku_access_mgir_reg structure is used to store the access register MGIR command parameters
 */
struct ku_access_mgir_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mgir_reg      mgir_reg; /**< mgir_reg - mgir register tlv */
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
 * ku_access_spzr_reg structure is used to store the access register SPZR command parameters
 */
struct ku_access_spzr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spzr_reg      spzr_reg; /**< spzr_reg - spzr register tlv */
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
 * ku_access_pptt_reg structure is used to store the access register PPTT command parameters
 */
struct ku_access_pptt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pptt_reg      pptt_reg; /**< pptt_reg - pptt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pprt_reg structure is used to store the access register PPRT command parameters
 */
struct ku_access_pprt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pprt_reg      pprt_reg; /**< pprt_reg - pprt register tlv */
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
 * ku_access_pmaos_reg structure is used to store the access register PMAOS command parameters
 */
struct ku_access_pmaos_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmaos_reg     pmaos_reg; /**< pmaos_reg - pmaos register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pmtu_reg structure is used to store the access register PMTU command parameters
 */
struct ku_access_pmtu_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmtu_reg      pmtu_reg; /**< ku_pmtu_reg - pmtu register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pcnr_reg structure is used to store the access register PCNR command parameters
 */
struct ku_access_pcnr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pcnr_reg      pcnr_reg; /**< ku_pmtu_reg - pmtu register tlv */
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
 * ku_access_pmcr_reg structure is used to store the access register PMCR command parameters
 */
struct ku_access_pmcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmcr_reg      pmcr_reg; /**< pmcr_reg - pmcr register tlv */
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
 * ku_access_pmmp_reg structure is used to store the access register PMMP command parameters
 */
struct ku_access_pmmp_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pmmp_reg      pmmp_reg; /**< pmmp_reg - pmmp register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pplr_reg structure is used to store the access
 * register PPLR command parameters
 */
struct ku_access_pplr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pplr_reg      pplr_reg; /**< ku_pplr_reg - pplr register tlv */
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
 * ku_access_spad_reg structure is used to store the access register SPAD command parameters
 */
struct ku_access_spad_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spad_reg      spad_reg; /**< spad_reg - spad register tlv */
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
 * ku_access_mtcap_reg structure is used to store the access register MTCAP command parameters
 */
struct ku_access_mtcap_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtcap_reg     mtcap_reg; /**< mtcap_reg - mtcap register tlv */
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
 * ku_access_mtwe_reg structure is used to store the access register MTWE command parameters
 */
struct ku_access_mtwe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtwe_reg      mtwe_reg; /**< mtwe_reg - mtwe register tlv */
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
 * ku_access_qcap_reg structure is used to store the access register QCAP command parameters
 */
struct ku_access_qcap_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qcap_reg      qcap_reg; /**< qcap_reg - qcap register tlv */
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
 * ku_access_qprt_reg structure is used to store the access register QPRT command parameters
 */
struct ku_access_qprt_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_qprt_reg      qprt_reg; /**< qprt_reg - qprt register tlv */
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
 * ku_access_sfd_reg structure is used to store the access
 * register MFM command parameters
 */
struct ku_access_sfd_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sfd_reg       sfd_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_ppad_reg structure is used to store the access
 * register ppad command parameters
 */
struct ku_access_ppad_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ppad_reg      ppad_reg; /**< mfm_reg - hpkt register tlv */
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
 * ku_access_pbmc_reg structure is used to store the access
 * register pbmc command parameters
 */
struct ku_access_pbmc_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pbmc_reg      pbmc_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sbpr_reg structure is used to store the access
 * register sbpr command parameters
 */
struct ku_access_sbpr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbpr_reg      sbpr_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sbsr_reg structure is used to store the access
 * register sbsr command parameters
 */
struct ku_access_sbsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbsr_reg      sbsr_reg; /**< mfm_reg - sbsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_pbsr_reg structure is used to store the access
 * register pbsr command parameters
 */
struct ku_access_pbsr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pbsr_reg      pbsr_reg; /**< pbsr_reg - pbsr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sbcm_reg structure is used to store the access
 * register sbcm command parameters
 */
struct ku_access_sbcm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbcm_reg      sbcm_reg; /**< mfm_reg - hpkt register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sbpm_reg structure is used to store the access
 * register sbpm command parameters
 */
struct ku_access_sbpm_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbpm_reg      sbpm_reg; /**< mfm_reg - hpkt register tlv */
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
 * ku_access_pptb_reg structure is used to store the access
 * register pptb command parameters
 */
struct ku_access_pptb_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pptb_reg      pptb_reg; /**< mfm_reg - hpkt register tlv */
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
 * ku_access_spvid_reg structure is used to store the access
 * register spvid command parameters
 */
struct ku_access_spvid_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_spvid_reg     spvid_reg; /**< mfm_reg - hpkt register tlv */
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
 * ku_access_plbf_reg structure is used to store the access
 * register PLBF command parameters
 */
struct ku_access_plbf_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_plbf_reg      plbf_reg; /**< plbf_reg - plbf register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_sgcr_reg structure is used to store the access
 * register SGCR command parameters
 */
struct ku_access_sgcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sgcr_reg      sgcr_reg; /**< sgcr_reg - sgcr register tlv */
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
 * ku_access_mpsc_reg structure is used to store the access
 * register MPSC command parameters
 */
struct ku_access_mprs_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mprs_reg      mprs_reg; /**< mprs_reg - mprs register tlv */
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
    SXD_RR_STATUS_NONE = 0,
    SXD_RR_STATUS_ONGOING = 1
} sxd_rr_status_t;

typedef enum sxd_iedr_resource_type {
    SXD_IEDR_RESOURCE_TYPE_ADJACENCY_E = 0x21,
    SXD_IEDR_RESOURCE_TYPE_NVE_DECAP_E = 0x21,
    SXD_IEDR_RESOURCE_TYPE_IPINIP_DECAP_E = 0x21,
    SXD_IEDR_RESOURCE_TYPE_MPLS_NHLFE_E = 0x22,
    SXD_IEDR_RESOURCE_TYPE_ACL_ACTION_SET_E = 0x23,
    SXD_IEDR_RESOURCE_TYPE_PBS_E = 0x24,
    SXD_IEDR_RESOURCE_TYPE_CPU_SEND_MC_IDS_E = 0x24,
    SXD_IEDR_RESOURCE_TYPE_MPLS_ILM_E = 0x25,
    SXD_IEDR_RESOURCE_TYPE_RIGRV2_E = 0x26,
    SXD_IEDR_RESOURCE_TYPE_MC_EXPECTED_IRIF_LIST_E = 0x27,
    SXD_IEDR_RESOURCE_TYPE_IPV6_E = 0x28,
    SXD_IEDR_RESOURCE_TYPE_TNUMT_E = 0x29
} sxd_iedr_resource_type_e;

typedef enum sxd_iedr_delete_mode {
    SXD_IEDR_DELETE_MODE_FOREGROUND_E = 0,
    SXD_IEDR_DELETE_MODE_BACKGROUND_E = 1
} sxd_iedr_delete_mode_e;

typedef enum sxd_ieds_bg_delete_status {
    SXD_IEDS_BG_DELETE_NONE_E = 0,
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
 * ku_access_mpnhlfe_reg structure is used to store the access
 * register MPNHLFE command parameters
 */
struct ku_access_mpnhlfe_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mpnhlfe_reg   mpnhlfe_reg; /**< mpnhlfe_reg - mpnhlfe register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_access_cwgc_reg structure is used to store the access
 * register cwgc command parameters
 */
struct ku_cwgcr_reg {
    uint8_t en;
    uint8_t scd;
    uint8_t aqs_weight;
    uint8_t aqs_time;
    uint8_t cece;
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
    uint8_t              traffic_class;
    uint8_t              mode;
    struct ku_cw_profile profiles[REDECN_NUM_HW_PROFILES];
};

/**
 * ku_access_cwcpm_reg structure is used to store the access
 * register ku_access_cwcpm_reg command parameters
 */
struct ku_cwtpm_reg {
    uint8_t local_port;
    uint8_t traffic_class;
    uint8_t ew;
    uint8_t ee;
    uint8_t tcp_g;
    uint8_t tcp_y;
    uint8_t tcp_r;
    uint8_t ntcp_g;
    uint8_t ntcp_y;
    uint8_t ntcp_r;
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
 * ku_access_cwprp_reg structure is used to store the access
 * register cwprp command parameters
 */
struct ku_cpqe_reg {
    uint8_t egress_local_port;
    uint8_t element_hierarchy;
    uint8_t element_index;
    uint8_t profile_percent;
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
 * ku_access_ritr_reg structure is used to store the access
 * register RITR command parameters
 */
struct ku_access_ritr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_ritr_reg      ritr_reg; /**< ritr_reg - ritr register tlv */
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
    SXD_SBCTC_EVENT_NO_EVENT = 0,
    SXD_SBCTC_EVENT_EVENTS = 1,
    SXD_SBCTC_EVENT_SINGLE_EVENT = 2,
} sxd_sbctc_event_t;

/**
 * ku_sbctc_reg structure is used to store the access
 * register sbctc command parameters
 */
struct ku_sbctc_reg {
    uint8_t                              local_port;
    uint8_t                              en_config;
    uint8_t                              event;
    uint64_t __attribute__((aligned(8))) tclass_en;
    uint32_t                             thr_max;
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
 * ku_sbctr_reg structure is used to store the access
 * register sbctr command parameters
 */
struct ku_sbctr_reg {
    uint8_t                              ievent;
    uint8_t                              local_port;
    uint8_t                              fp;
    uint8_t                              entity;
    uint64_t __attribute__((aligned(8))) tclass_vec;
};

/**
 * ku_access_sbctr_reg structure is used to store the access
 * register SBCTR command parameters
 */
struct ku_access_sbctr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbctr_reg     sbctr_reg;  /**< sbctr_reg - sbctr register tlv */
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
    uint8_t                              ar_sec; /**< ar_sec - Primary / Secondary Capability */
    uint16_t                             adaptive_routing_group_cap; /**< adaptive_routing_group_cap - Adaptive Routing Group Capability */
    uint8_t                              arn; /**< arn - Adaptive Routing Notification Enable */
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
    uint8_t                              ubridge_mode;


    /* this array will contain supported revisions per type */
    uint64_t __attribute__((aligned(8))) sup_revs_by_type[SXD_CHIP_TYPES_MAX];
    enum sxd_chip_types                  chip_type;
    uint8_t                              do_not_config_profile_to_device;
    uint8_t                              split_ready; /**< split_ready - Support split ports */
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

#if defined(PD_BU)
/* Part of the PUDE WA for MLNX OS (PUDE events are handled manually):
 * - should be removed before Phoenix bring up;
 */
/**
 * ku_admin_status_data is used to store the data of the port
 * admin status ioctl
 */
struct ku_admin_status_data {
    uint8_t  dev_id;       /**< dev_id - device id */
    uint16_t sysport;      /**< sysport - system port */
    uint8_t  admin_status; /**< admin_status - port admin status */
};
#endif

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
    uint8_t dev_id;
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
};


/**
 * ku_ptp_mode - events/polling
 */

typedef enum {
    KU_PTP_MODE_EVENTS,
    KU_PTP_MODE_POLLING,
    KU_PTP_MODE_DISABLED
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
    uint8_t local_port;
    uint8_t ber_monitor_state;
};

/**
 * ku_ber_monitor_bitmask_data is used to store the data of port ber monitor bitmask update ioctl
 */
struct ku_ber_monitor_bitmask_data {
    uint8_t local_port;
    uint8_t bitmask;
};

/**
 * ku_tele_threshold_data is used to store the data of telemetry threshold set ioctl
 */
struct ku_tele_threshold_data {
    uint8_t                              local_port;
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
 * sxd_tunnel_flc_type_t enumerated flow label copy type.
 */
typedef enum sxd_tunnel_flc_type {
    SXD_TUNNEL_FLC_CALCULATE = 0,
    SXD_TUNNEL_FLC_COPY_FROM_PKT = 1
} sxd_tunnel_flc_type_t;

/**
 * sxd_tunnel_flc_type_t enumerated tigcr flow label type.
 */
typedef enum sxd_tunnel_flh_type {
    SXD_TUNNEL_FLH_NO_LABEL = 0,
    SXD_TUNNEL_FLH_CALCULATE = 1
} sxd_tunnel_flh_type_t;

/**
 * sxd_tunnel_sport_type_t enumerated udp sport type.
 */
typedef enum sxd_tunnel_sport_type {
    SXD_TUNNEL_SPORT_SET_ZERO = 0,
    SXD_TUNNEL_SPORT_CALCULATE = 1,
} sxd_tunnel_sport_type_t;

/**
 * sxd_tca_log_pstate_type_t enumerated type is used to indicates the TCA logical port state type
 */
typedef enum sxd_tunnel_nve_type {
    SXD_TUNNEL_NVE_VXLAN = 0,
    SXD_TUNNEL_NVE_VXLAN_GPE = 1,
    SXD_TUNNEL_NVE_GENEVE = 2,
    SXD_TUNNEL_NVE_NVGRE = 3,
} sxd_tunnel_nve_type_t;

/**
 * ku_tngcr_reg structure is used to store the TNGCR register parameters
 */
struct ku_tngcr_reg {
    sxd_tunnel_nve_type_t   type;
    uint8_t                 nve_valid;
    uint8_t                 nve_ttl_uc;
    uint8_t                 nve_ttl_mc;
    sxd_tunnel_flc_type_t   nve_flc;
    sxd_tunnel_flh_type_t   nve_flh;
    uint16_t                nve_fl_prefix;
    uint8_t                 nve_enc_orig;
    uint8_t                 nve_enc_orig_we;
    sxd_tunnel_sport_type_t nve_udp_sport_type;
    uint8_t                 et_vlan;
    uint8_t                 nve_udp_sport_prefix;
    uint16_t                nve_udp_dport;
    uint8_t                 nve_group_size_mc;
    uint8_t                 nve_group_size_flood;
    uint8_t                 learn_enable;
    uint16_t                underlay_virtual_router;
    uint16_t                underlay_rif;
    uint32_t                usipv4;
    uint32_t                usipv6[4];
};

/**
 * ku_tncr_reg structure is used to store the TNCR register parameters
 */
struct ku_tncr_reg {
    uint8_t  clear_counters;
    uint32_t count_encap_high;
    uint32_t count_encap_low;
    uint32_t count_decap_high;
    uint32_t count_decap_low;
    uint32_t count_decap_errors_high;
    uint32_t count_decap_errors_low;
    uint32_t count_decap_discards_high;
    uint32_t count_decap_discards_low;
};

/**
 * sxd_tunnel_tnumt_type enumerated tnumt record type.
 */
typedef enum sxd_tunnel_tnumt_type {
    SXD_TNUMT_TYPE_IPV4 = 0,
    SXD_TNUMT_TYPE_IPV6 = 1
} sxd_tunnel_tnumt_type_t;

/**
 * ku_nve_mc_ipv4 structure is used for Tunneling Underlay Multicast Record for IPV4 type
 */
struct ku_nve_mc_ipv4 {
    uint8_t  size;
    uint32_t udip[3];
};

/**
 * ku_nve_mc_ipv6 structure is used for Tunneling Underlay Multicast Record for IPV6 type
 */
struct ku_nve_mc_ipv6 {
    uint8_t  size;
    uint32_t udip_ptr[5];
};

/**
 * ku_tnumt_reg structure is used to store the TNUMT register parameters
 */
struct ku_tnumt_reg {
    sxd_tunnel_tnumt_type_t record_type;
    uint32_t                underlay_mc_ptr;
    uint8_t                 vnext;
    uint32_t                next_underlay_mc_ptr;
    union {
        struct ku_nve_mc_ipv4 mc_ipv4;
        struct ku_nve_mc_ipv6 mc_ipv6;
    } record;
};

/**
 * sxd_tunnel_enc_set_dscp_t structure enumerates types how to set DSCP field for encapsulation
 */
typedef enum sxd_tunnel_enc_set_dscp {
    SXD_TUNNEL_ENC_DSCP_COPY = 0,
    SXD_TUNNEL_ENC_DSCP_SET = 1
} sxd_tunnel_enc_set_dscp_t;

/**
 * sxd_tunnel_enc_set_sp_t structure enumerated types how to set Switch prio and color for encapsulation
 */
typedef enum sxd_tunnel_enc_set_sp {
    SXD_TUNNEL_ENC_SP_PRESERVE = 0,
    SXD_TUNNEL_ENC_SP_SET = 1
} sxd_tunnel_enc_set_sp_t;

/**
 * sxd_tunnel_dec_set_dscp_t structure enumerates types how to set overlay DSCP field
 */
typedef enum sxd_tunnel_dec_set_dscp {
    SXD_TUNNEL_DEC_DSCP_PRESERVE = 0,
    SXD_TUNNEL_DEC_DSCP_COPY = 1
} sxd_tunnel_dec_set_dscp_t;

/**
 * sxd_tunnel_dec_set_sp_t structure enumerated types how to set Switch prio and color for decapsulation
 */
typedef enum sxd_tunnel_dec_set_sp {
    SXD_TUNNEL_DEC_SP_PRESERVE = 0,
    SXD_TUNNEL_DEC_SP_SET = 1
} sxd_tunnel_dec_set_sp_t;

/**
 * sxd_tunnel_dec_set_pcp_t structure enumerated types how to set the overlay PCP, DEI for decapsulation
 */
typedef enum sxd_tunnel_dec_set_pcp {
    SXD_TUNNEL_DEC_PCP_PRESERVE = 0,
    SXD_TUNNEL_DEC_PCP_COPY = 1
} sxd_tunnel_dec_set_pcp_t;

/**
 * sxd_tunnel_enc_dscp_rw_t structure enumerates types how to handle DSCP rewrite
 */
typedef enum sxd_tunnel_dscp_rw {
    SXD_TUNNEL_DSCP_RW_PRESERVE = 0,
    SXD_TUNNEL_DSCP_RW_CLEAR = 2,
    SXD_TUNNEL_DSCP_RW_SET = 3
} sxd_tunnel_dscp_rw_t;

/**
 * sxd_tunnel_enc_pcp_rw_t structure enumerates types how to handle pcp rewrite
 */
typedef enum sxd_tunnel_pcp_rw {
    SXD_TUNNEL_PCP_RW_PRESERVE = 0,
    SXD_TUNNEL_PCP_RW_CLEAR = 2,
    SXD_TUNNEL_PCP_RW_SET = 3
} sxd_tunnel_pcp_rw_t;

/**
 * sxd_rm_duplication_table_type enumerated type is used to list
 * a supported logical table types for the entry duplications in
 * the KVD
 */
typedef enum sxd_rm_duplication_table_type {
    SXD_RM_DUPLICATION_TABLE_TYPE_INVALID_E = 0x00,
    /* HASH-BASED */
    SXD_RM_DUPLICATION_TABLE_TYPE_VID_TO_FID_E = 0x01,
    SXD_RM_DUPLICATION_TABLE_TYPE_RQ_VID_TO_FID_E = 0x02,
    SXD_RM_DUPLICATION_TABLE_TYPE_FID_E = 0x03,
    SXD_RM_DUPLICATION_TABLE_TYPE_NVI_TO_FID_E = 0x04,
    SXD_RM_DUPLICATION_TABLE_TYPE_MAC_L2_FORWARDING_E = 0x05,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV4_LPM_HIGH_E = 0x06,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV4_LPM_LOW_E = 0x07,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV4_LPM_LPM0_E = 0x08,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_LPM_HIGH_E = 0x09,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_LPM_LOW_E = 0x0A,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_LPM_LPM0_E = 0x0B,
    SXD_RM_DUPLICATION_TABLE_TYPE_MPLS_ILM_E = 0x0C,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV4_HOST_TABLE_E = 0x0D,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_HOST_TABLE_E = 0x0E,
    SXD_RM_DUPLICATION_TABLE_TYPE_TUNNEL_IPV6_LEARN_E = 0x0F,
    SXD_RM_DUPLICATION_TABLE_TYPE_A_TCAM_1_KEY_E = 0x10,
    SXD_RM_DUPLICATION_TABLE_TYPE_A_TCAM_2_KEY_E = 0x11,
    SXD_RM_DUPLICATION_TABLE_TYPE_A_TCAM_4_KEY_E = 0x12,
    SXD_RM_DUPLICATION_TABLE_TYPE_A_TCAM_6_KEY_E = 0x13,

    /* linear */
    SXD_RM_DUPLICATION_TABLE_TYPE_ADJACENCY_E = 0x21,
    SXD_RM_DUPLICATION_TABLE_TYPE_NVE_DECAP_E = SXD_RM_DUPLICATION_TABLE_TYPE_ADJACENCY_E,
    SXD_RM_DUPLICATION_TABLE_TYPE_IP_IN_IP_DECAP_E = SXD_RM_DUPLICATION_TABLE_TYPE_ADJACENCY_E,
    SXD_RM_DUPLICATION_TABLE_TYPE_MPLS_NHLFE_E = 0x22,
    SXD_RM_DUPLICATION_TABLE_TYPE_ACL_ACTION_SET_EXTENSION_E = 0x23,
    SXD_RM_DUPLICATION_TABLE_TYPE_POLICY_BASED_SWITCHING_E = 0x24,
    SXD_RM_DUPLICATION_TABLE_TYPE_POLICY_BASED_MPLS_ILM_E = 0x25,
    SXD_RM_DUPLICATION_TABLE_TYPE_MC_ROUTER_INTF_GROUP_E = 0x26,
    SXD_RM_DUPLICATION_TABLE_TYPE_MC_EXPECTED_IRIF_LIST_E = 0x27,
    SXD_RM_DUPLICATION_TABLE_TYPE_IPV6_IP_ADDRESS_E = 0x28,
    SXD_RM_DUPLICATION_TABLE_TYPE_TUNNEL_UNDERLAY_MC_E = 0x29
} sxd_rm_duplication_table_type_e;

/**
 * ku_tnqdr_reg structure is used to store the TNQDR register parameters
 */
struct ku_tnqdr_reg {
    uint8_t local_port;
    uint8_t color;
    uint8_t switch_prio;
    uint8_t dscp;
};


/**
 * sxd_tunnel_tigcr_ttlc enumerated tigcr ttlc type.
 */
typedef enum sxd_tunnel_tigcr_ttlc {
    SXD_TIGCR_TTLC_USE_CONFIG = 0,
    SXD_TIGCR_TTLC_COPY_FROM_PKT = 1
} sxd_tunnel_tigcr_ttlc_t;

/**
 * ku_tigcr_reg structure is used to store the TIGCR register parameters
 */
struct ku_tigcr_reg {
    sxd_tunnel_tigcr_ttlc_t ipip_ttlc;
    uint8_t                 ipip_ttl_uc;
    sxd_tunnel_flc_type_t   ipip_flc;
    sxd_tunnel_flh_type_t   ipip_flh;
    uint16_t                ipip_fl_prefix;
    uint32_t                ipip_gre_key_for_hash;
};

/**
 * ku_tiqdr_reg structure is used to store the access
 * register tiqdr command parameters
 */
struct ku_tiqdr_reg {
    uint8_t local_port;
    uint8_t color;
    uint8_t switch_prio;
    uint8_t dscp;
};

/**
 * ku_tiqcr_reg structure is used to store the access
 * register tiqcr command parameters
 */
struct ku_tiqcr_reg {
    sxd_tunnel_enc_set_dscp_t enc_set_dscp;
    sxd_tunnel_enc_set_sp_t   enc_set_sp;
    sxd_tunnel_dscp_rw_t      enc_dscp_rw;
    sxd_tunnel_pcp_rw_t       enc_pcp_rw;
    sxd_tunnel_dec_set_dscp_t dec_set_dscp;
    sxd_tunnel_dec_set_sp_t   dec_set_sp;
    sxd_tunnel_dscp_rw_t      dec_dscp_rw;
    sxd_tunnel_pcp_rw_t       dec_pcp_rw;
};

/**
 * ku_tieem_reg structure is used to store the access
 * register tieem command parameters
 */
struct ku_tieem_reg {
    uint8_t overlay_ecn;
    uint8_t underlay_ecn;
};

/**
 * ku_tidem_reg structure is used to store the access
 * register tidem command parameters
 */
struct ku_tidem_reg {
    uint8_t overlay_ecn;
    uint8_t underlay_ecn;
    uint8_t eip_ecn;
    uint8_t trap_en;
    uint8_t trap_id;
};

/**
 * ku_tneem_reg structure is used to store the access
 * register tneem command parameters
 */
struct ku_tneem_reg {
    uint8_t overlay_ecn;
    uint8_t underlay_ecn;
};

/**
 * ku_tndem_reg structure is used to store the access
 * register tndem command parameters
 */
struct ku_tndem_reg {
    uint8_t overlay_ecn;
    uint8_t underlay_ecn;
    uint8_t eip_ecn;
    uint8_t trap_en;
    uint8_t trap_id;
};

/**
 * ku_tnifr_reg structure is used to store the access
 * register tnifr command parameters
 */
struct ku_tnifr_reg {
    uint8_t port_filter[0x000000FF + 1]; /**< 1 = filter packets coming from port_filter[i], 0 = don't filter */
    uint8_t port_filter_update_en[0x000000FF + 1];  /**< 1 = modify relevant port_filter bit, 0 = don't modify */
};

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
    PORT_ACCESS_TYPE_PCI_E = 2,
    PORT_ACCESS_TYPE_LAST_E
} port_access_type_t;

typedef enum {
    PDDR_PAGE_OPT_OPR_INFO_E = 0,
    PDDR_PAGE_OPT_TROUBLESHOOT_E = 1,
    PDDR_PAGE_OPT_PHY_INFO_E = 2,
    PDDR_PAGE_OPT_MODULE_INFO_E = 3,
    PDDR_PAGE_OPT_MODULE_LAST_E
} pddr_page_options_t;


/**
 * pddr register use to request port diagnostic information
 */

typedef enum {
    PORT_PROTOCOL_IB_E = (1 << 0),
    PORT_PROTOCOL_ETH_E = (1 << 2)
} port_protocol_t;

typedef enum {
    NEG_MODE_NOT_NEG_E = 0,
    NEG_MODE_MLPN_REV_0_E = 1,
    NEG_MODE_CL73_ETH_E = 2,
    NEG_MODE_PARALLEL_DETECT_E = 3,
    NEG_MODE_STANDART_IB_E = 4
} neg_mode_t;

typedef enum {
    PHY_MGR_FSM_DISABLED_E,
    PHY_MGR_FSM_OPEN_PORT_E,
    PHY_MGR_FSM_POLLING_E,
    PHY_MGR_FSM_ACTIVE_E,
    PHY_MGR_FSM_CLOSE_PORT_E
} phy_mgr_fsm_state_t;

typedef enum {
    AUTONEG_FSM_ENABLE_E,
    AUTONEG_FSM_XMIT_DISABLE_E,
    AUTONEG_FSM_ABILITY_DETECT_E,
    AUTONEG_FSM_ACK_DETECT_E,
    AUTONEG_FSM_COMPLETE_ACK_E,
    AUTONEG_FSM_GOOD_CHECK_E,
    AUTONEG_FSM_GOOD_E,
    AUTONEG_FSM_NEXT_PAGE_WAIT_E,
    AUTONEG_FSM_LINK_STATE_CHECK_E,
    AUTONEG_FSM_EXTRA_TUNE_E,
    AUTONEG_FSM_FIX_REVERSALS_E,
    AUTONEG_FSM_IB_FAIL_E,
} autoneg_fsm_state_t;

typedef enum {
    RETRANSMIT_MODE_NONE_E = 0,
    RETRANSMIT_MODE_LLR_E = (1 << 0),
    RETRANSMIT_MODE_PLR_E = (1 << 1),
    RETRANSMIT_MODE_LLR_AND_PLR_E = (RETRANSMIT_MODE_LLR_E | RETRANSMIT_MODE_PLR_E)
} retransmit_mode_t;

typedef enum {
    LOOPBACK_MODE_PHY_REMOTE_E = 0,
    LOOPBACK_MODE_LOCAL_E = 2,
    LOOPBACK_MODE_EXTERNAL_LOCAL_E = 4
} loopback_mode_t;

typedef enum {
    FEC_MODE_NONE_E = 0,
    FEC_MODE_FIRE_CODE_E = 1,
    FEC_MODE_RS_FEC_E = 2,
    FEC_LL_RS_E = 3,
    FEC_MLX_STRONG_LL_RS_E = 4,
    FEC_MLX_LL_RS_E = 5,
    FEC_ZERO_LATENCY_E = 6
} fec_mode_t;

typedef enum {
    FEC_PROFILE_IB_SPEC_E = 0,
    FEC_PROFILE_INTERNAL_PORTS_E = (1 << 0),
    FEC_PROFILE_PASSIVE_COPPER_SHORT_E = (1 << 1),
    FEC_PROFILE_PASSIVE_COPPER_MEDIUM_E = (1 << 2),
    FEC_PROFILE_PASSIVE_COPPER_LONGE_E = (1 << 3),
    FEC_PROFILE_ACTIVE_OPTICS_E = (1 << 4),
    FEC_PROFILE_OPTIC_LONG_REACH_E = (1 << 5),
    FEC_PROFILE_NO_FEC_E = (1 << 6),
    FEC_PROFILE_FEC_ONE_E = (1 << 7)
} profile_fec_in_use_t;

typedef enum {
    REMOTE_DEVICE_UNKNOWN_E = 0,
    REMOTE_DEVICE_CX4_E = 1,
    REMOTE_DEVICE_CX4LX_E = 2,
    REMOTE_DEVICE_CX5_E = 3,
    REMOTE_DEVICE_CX5_LX_E = 4,
    REMOTE_DEVICE_CX6_E = 5,
    REMOTE_DEVICE_CX6_LX_E = 6,
    REMOTE_DEVICE_SWITCH_IB_E = 100,
    REMOTE_DEVICE_SPECTRUM_E = 101,
    REMOTE_DEVICE_SWITCH_IB_2_E = 102,
    REMOTE_DEVICE_SWITCH_IB_3_E = 103,
    REMOTE_DEVICE_SPECTRUME_2_E = 104,
} remote_device_type_t;

typedef enum {
    PORT_NOTIF_NONE_E = 0,
    PORT_NOTIF_LINK_PARTNER_ADV_CPBILITY_E = (1 << 0),
    PORT_NOTIF_SPEED_DECLR_E = (1 << 1)
} port_notifications_t;

typedef enum {
    PHY_MGR_DISABLE_MASK_NONE_E = 0,
    PHY_MGR_DISABLE_MASK_MODULE_NOT_PERESENT_E = (1 << 0),
    PHY_MGR_DISABLE_MASK_PAOS_COMMANDS_E = (1 << 1),
    PHY_MGR_DISABLE_MASK_MAD_IB_PORT_INFO_DOWN_CMD = (1 << 2),
    PHY_MGR_DISABLE_MASK_LONG_RANGE_CABLE_E = (1 << 3),
    PHY_MGR_DISABLE_MASK_VERIFICATION_COMMAND_E = (1 << 4),
    PHY_MGR_DISABLE_MASK_EKEY_COMMAND_E = (1 << 5),
    PHY_MGR_DISABLE_MASK_HIGH_POWER_E = (1 << 6),
    PHY_MGR_DISABLE_MASK_UNKNOWN_IDNTIFIER_E = (1 << 7),
    PHY_MGR_DISABLE_MASK_PAOS_UP_ONCE_E = (1 << 8),
    PHY_MGR_DISABLE_MASK_STAMPING_FAILURE_E = (1 << 9),
    PHY_MGR_DISABLE_MASK_CALIBRATION_NOT_DONE_E = (1 << 10)
} phy_mgr_disable_mask_t;

typedef enum {
    PCS_PHY_STATE_BLOCK_LOCK_E = (1 << 0),
    PCS_PHY_STATE_AM_LOCK_E = (1 << 1),
    PCS_PHY_STATE_FEC_LOCK_E = (1 << 2),
    PCS_PHY_STATE_ALIGN_STATUS_E = (1 << 3),
} pcs_phy_lock_t;

typedef enum {
    LINK_DOWN_LANE_NONE = 0,
    LINK_DOWN_LANE_BLOCK_LOCK_FAILED = (1 << 0),
    LINK_DOWN_LANE_SKIP_DETECTED = (1 << 1),
    LINK_DOWN_LANE_FEC_SYNC_FAILED = (1 << 2),
    LINK_DOWN_LANE_FEC_BLOCK_SYNC_E = (1 << 3),
    LINK_DOWN_LANE_FEC_BLOCK_SYNC_LOST_E = (1 << 4)
} link_down_lane_fec_t;

typedef enum {
    SPEED_DEG_DB_VALID = (1 << 0),
    SPEED_DEG_DB_SERDES_RX_DB_VALID = (1 << 1),
    SPEED_DEG_DB_RX_RESERVED = (1 << 2),
    SPEED_DEG_DB_RX_REVERSAL = (1 << 3),
    SPEED_DEG_DB_TX_REVERSAL = (1 << 4),
    SPEED_DEG_DB_FAILED_QDR = (1 << 5),
    SPEED_DEG_DB_FAILED_EDR = (1 << 6),
    SPEED_DEG_DB_PEER_TEST = (1 << 7),
    SPEED_DEG_DB_FIRST_TEST_SPEED = (1 << 8)
} speed_deg_db_t;

typedef enum {
    KR_FSM_INITIALIZED_E = 0,
    KR_FSM_SEND_TRAINING_E = 1,
    KR_FSM_TRAIN_LOCAL_TX_E = 2,
    KR_FSM_TRAIN_LOCAL_RX = 3,
    KR_FSM_TRAIN_REMOTE_E = 4,
    KR_FSM_LINK_READY_E = 5,
    KR_FSM_SEND_DATA_E = 6
} kr_fsm_t;

typedef enum {
    ETH_AN_DEBUG_FORCE_LINK_UP_E = (1 << 0),
    ETH_AN_DEBUG_NO_HCD_E = (1 << 1),
    ETH_AN_DEBUG_ENTERED_ACK_DETECTED_E = (1 << 2),
    ETH_AN_DEBUG_ENTERED_GOOD_E = (1 << 3),
    ETH_AN_DEBUG_ENTERED_GOOD_CHECK_E = (1 << 4),
    ETH_AN_DEBUG_ENTERED_EXTRA_TUNE_E = (1 << 5),
    ETH_AN_DEBUG_ENTERED_FIX_REVERSALS_E = (1 << 6),
    ETH_AN_DEBUG_ENTERED_NEXT_PAGE_E = (1 << 7),
    ETH_AN_DEBUG_ENTERED_SUB_FSM_FAIL_E = (1 << 8),
    ETH_AN_DEBUG_TUNING_TIMEOUT_E = (1 << 9),
    ETH_AN_DEBUG_NO_MARKED_DETECTED = (1 << 10),
    ETH_AN_DEBUG_DO_KR_STARTUP = (1 << 11),
} eth_an_debug_indication_t;

struct eth_an_debug_indication {
    eth_an_debug_indication_t debug_indication;
    sxd_boolean_t             kr_strtup_failure_mask[NUMBER_OF_SERDESES];
};

typedef enum {
    KR_DEBUG_INDIC_NONE_E = 0,
    KR_DEBUG_INDIC_PRBS_LOCK_FAILED_E = (1 << 0),
    KR_DEBUG_INDIC_SEND_TRAINING_E = (1 << 1),
    KR_DEBUG_INDIC_ENT_TRAIN_LOCAL_RX_E = (1 << 2),
    KR_DEBUG_INDIC_ENT_TRAIN_REMOTE_E = (1 << 3),
    KR_DEBUG_INDIC_ENT_LINK_READY_E = (1 << 4),
    KR_DEBUG_INDIC_SEND_DATA_E = (1 << 5),
    KR_DEBUG_INDIC_DIDNT_GET_RECV_READY_E = (1 << 6),
    KR_DEBUG_INDIC_TUNING_TIMEOUT_E = (1 << 7),
    KR_DEBUG_INDIC_NO_FRAME_LOCK_E = (1 << 8),
    KR_DEBUG_INDIC_NO_RESP_FROM_USER_E = (1 << 9),
    KR_DEBUG_INDIC_FRAME_LOCK_TUNING_NOT_DONE_E = (1 << 10)
} kr_debug_indication_t;

typedef enum {
    STAMPING_REASON_NONE_E = 0,
    STAMPING_REASON_COM_CODE_IS_ZERO_E = (1 << 0),
    STAMPING_REASON_RX_CDR_CHECK_FORCE_MODE_E = (1 << 1),
    STAMPING_REASON_COM_CODE_COMPLAINCE_E = (1 << 2),
    STAMPING_REASON_ETH_56G_STAMPED_E = (1 << 3),
    STAMPING_REASON_NON_MLX_QSFP_TRANC_E = (1 << 4),
    STAMPING_REASON_NON_MLX_SFP_TRANC_E = (1 << 5),
    STAMPING_REASON_IB_COMP_CODES_E = (1 << 6),
    STAMPING_REASON_EDR_COMP_E = (1 << 7),
    STAMPING_REASON_FDR_COMP_E = (1 << 8)
} stamping_reason_t;

typedef enum {
    HW_LINK_PHY_STATE_SLEEPING_DELAY = 0x10,
    HW_LINK_PHY_STATE_SLEEPING_QUIET = 0x11,
    HW_LINK_PHY_STATE_POLLING_ACTIVE = 0x20,
    HW_LINK_PHY_STATE_POLLING_QUIET = 0x21,
    HW_LINK_PHY_STATE_DISABLE = 0x30,
    HW_LINK_PHY_STATE_CONFIG_DEBOUNCE = 0x40,
    HW_LINK_PHY_STATE_CONFIG_RECEIVER = 0x41,
    HW_LINK_PHY_STATE_CONFIG_WAIT_REMOTE = 0x42,
    HW_LINK_PHY_STATE_CONFIG_TX_REVERSE_LANES = 0x43,
    HW_LINK_PHY_STATE_CONFIG_ENHANCED = 0x44,
    HW_LINK_PHY_STATE_HW_LINK_PHY_STATE_CONFIG_TEST = 0x45,
    HW_LINK_PHY_STATE_CONFIG_WAIT_REMOTE_TEST = 0x46,
    HW_LINK_PHY_STATE_WAIT_CONFIG_ENAHNCED = 0x47,
    HW_LINK_PHY_STATE_CONFIG_IDLE = 0x48,
    HW_LINK_PHY_STATE_LINKUP = 0x50,
    HW_LINK_PHY_STATE_RECOVER_RETRAIN = 0x60,
    HW_LINK_PHY_STATE_RECOVER_WAIT_REMOTE = 0x61,
    HW_LINK_PHY_STATE_RECOVER_IDLE = 0x62,
    HW_LINK_PHY_STATE_TEST = 0x70,
    HW_LINK_PHY_STATE_FORCE = 0x80,
    HW_LINK_PHY_STATE_FORCE_SEND_TS2 = 0x90,
    HW_LINK_PHY_STATE_FORCE_SENT_IDLE = 0xA2,
    HW_LINK_PHY_STATE_FORCE_SEND_TS_MLNX = 0xB0,
    HW_LINK_PHY_STATE_FORCE_SEND_TS3 = 0xC0,
    HW_LINK_PHY_STATE_FORCE_LINK_UP = 0xD0
} hw_link_phy_state_t;

typedef enum {
    IB_LAST_LINK_DOWN_HEARTBEAT_ACK_RECVED_E = (1 << 0),
    IB_LAST_LINK_DOWN_HEARTBEAT_SEND_RECVED_E = (1 << 1),
    IB_LAST_LINK_DOWN_HEARTBEAT_HEARTBEAT_ERR_E = (1 << 2),
    IB_LAST_LINK_DOWN_TX_WIDTH_REDUCT_DONE_1X_E = (1 << 3),
    IB_LAST_LINK_DOWN_RX_WIDTH_REDUCT_DONE_FULL_E = (1 << 4),
    IB_LAST_LINK_DOWN_RX_WIDTH_REDUC_DONE_1X_E = (1 << 5),
    IB_LAST_LINK_DOWN_RX_WIDTH_REDUC_DONE_FULL_E = (1 << 6),
    IB_LAST_LINK_DOWN_WIDTH_REDUC_TIMEOUT_E = (1 << 7),
    IB_LAST_LINK_DOWN_IBL_LINK_RETAIN_E = (1 << 8),
    IB_LAST_LINK_DOWN_RX_COMPSKP_TIMEOUT_E = (1 << 9),
    IB_LAST_LINK_DOWN_FIFO_FULL_ERR_E = (1 << 10),
    IB_LAST_LINK_DOWN_TS_AT_LINK_UP_E = (1 << 11),
    IB_LAST_LINK_DOWN_MINOR_THRESHOLD_REACHED_E = (1 << 12),
    IB_LAST_LINK_DOWN_LINK_FAIL_E = (1 << 13),
    IB_LAST_LINK_DOWN_RX_EB_FULL_R_E = (1 << 14),
    IB_LAST_LINK_DOWN_8_10_LANE_ERR_E = (1 << 15),
    IB_LAST_LINK_DOWN_LLR_LINK_RETRAIN_SET_E = (1 << 16),
    IB_LAST_LINK_DOWN_FC_TIMEOUT_E = (1 << 17),
    IB_LAST_LINK_DOWN_PHY_ERR_E = (1 << 18),
    IB_LAST_LINK_DOWN_LLI_ERR_E = (1 << 19),
    IB_LAST_LINK_DOWN_EXESSIVE_BUFFER_ERR_E = (1 << 20),
    IB_LAST_LINK_DOWN_REMOTE_INIT_E = (1 << 21),
} ib_last_link_down_reason_t;

typedef enum {
    IB_PHY_FSM_STATE_TRACE_AN_FSM_DISABLE = (1 << 0),
    IB_PHY_FSM_STATE_TRACE_AN_FSM_INITIALY = (1 << 1),
    IB_PHY_FSM_STATE_TRACE_AN_FSM_RCVR_CFG = (1 << 2),
    IB_PHY_FSM_STATE_TRACE_AN_FSM_CFG_TEST = (1 << 3),
    IB_PHY_FSM_STATE_TRACE_AN_FSM_WAIT_RMT_TEST = (1 << 4),
    IB_PHY_FSM_STATE_TRACE_AN_FSM_WAIT_CFG_ENHANCED = (1 << 5),
    IB_PHY_FSM_STATE_TRACE_AN_FSM_CFG_IDLE = (1 << 6),
    IB_PHY_FSM_STATE_TRACE_AN_FSM_LINK_UP = (1 << 7),
    IB_PHY_FSM_STATE_TRACE_FAILED_FROM_CFG_IDLE = (1 << 8),
} ib_phy_fsm_state_trace;

typedef enum {
    CABLE_TYPE_UNIDENTIFIED_E = 0,
    CABLE_TYPE_ACTIVE_CABLE_E = 1,
    CABLE_TYPE_OPTICAL_MODULE = 2,
    CABLE_TYPE_PASSIVE_COPPER_E = 3,
    CABLE_TYPE_UNPLAGGED_E = 4
} cable_type_t;

typedef enum {
    CABLE_VENDOR_OTHER_E = 0,
    CABLE_VENDOR_MELLANOX_E = 1,
    CABLE_VENDOR_KNOWN_OUI_E = 2
} cable_vendor_t;

typedef enum {
    CABLE_IDENT_OSFP28_E = 0,
    CABLE_IDENT_OSFP_PLUS_E = 1,
    CABLE_IDENT_SFP28_SFP_PLUS_E = 2,
    CABLE_IDENT_QSA_E = 3,
    CABLE_IDENT_BACKPLANE_E = 4
} cable_identifier_t;

typedef enum {
    CABLE_POWER_CLASS_0_E = 0,
    CABLE_POWER_CLASS_1_E = 1,
    CABLE_POWER_CLASS_2_E = 2,
    CABLE_POWER_CLASS_3_E = 3,
    CABLE_POWER_CLASS_4_E = 4,
    CABLE_POWER_CLASS_5_E = 5,
    CABLE_POWER_CLASS_6_E = 6,
    CABLE_POWER_CLASS_7_E = 7,
} cable_power_class_t;

typedef enum {
    CDR_CAP_NONE = 0,
    CDR_CAP_BUILD_IN_WITH_ON_OFF_E = 1,
    CDR_CAP_BUILD_IN_WITHOUT_ON_OFF_E = 2,
} cdr_cap_t;

typedef enum {
    CDR_STATE_ON_OFF_ON_CHANNEL_0_E = (1 << 0),
    CDR_STATE_ON_OFF_ON_CHANNEL_1_E = (1 << 1),
    CDR_STATE_ON_OFF_ON_CHANNEL_2_E = (1 << 2),
    CDR_STATE_ON_OFF_ON_CHANNEL_3_E = (1 << 3),
} cdr_state_t;

enum {
    SX_EVENT_LIST_SIZE = 2000,
    ISX_HDR_SIZE = 16,
    SX_MAX_MSG_SIZE = 10240
};

struct pddr_oper_info_resp {
    port_protocol_t     port_protocol;
    neg_mode_t          port_neg_mode;
    phy_mgr_fsm_state_t phy_mgr_fsm_state;
    autoneg_fsm_state_t autoneg_fsm_state;
    uint8_t             ib_phy_fsm_state;
    union {
        struct eth {
            uint32_t eth_phy_mgr_admin_state;
            uint32_t eth_core_admin_state;
            uint32_t eth_proto_active_state;
        } eth_admin;
        struct ib {
            uint16_t phy_mgr_link_width_enabled;
            uint16_t phy_manager_link_proto_enabled;
            uint16_t core_to_phy_link_width_enabled;
            uint16_t core_to_phy_link_proto_enabled;
            uint16_t link_width_active;
            uint16_t link_speed_active;
        } ib_admin;
    } admin_state;
    uint32_t          cable_proto_cap;
    retransmit_mode_t retransmit_mode_active;
    retransmit_mode_t retransmit_mode_requested;
    loopback_mode_t   loopback_mode;
    fec_mode_t        fec_mode_active;
    fec_mode_t        fec_mode_req;
    uint8_t           profile_fec_in_use; /** see profile_fec_in_use_t **/
    uint8_t           eth_25g_50g_fec_support;
    uint8_t           eth_100g_fec_support;
};

typedef enum {
    LANE_FAILURE_QDR_E = (1 << 0),
    LANE_FAILURE_FDR_E = (1 << 1),
    LANE_FAILURE_EDR_E = (1 << 2),
    LANE_FAILURE_PEER_TEST_E = (1 << 3)
} lane_failure_t;

struct pddr_speed_deg_db {
    sxd_boolean_t  speed_degr_db_valid;
    sxd_boolean_t  speed_degr_serdes_rx_db_valid;
    sxd_boolean_t  rx_reversal;
    sxd_boolean_t  tx_reversal;
    sxd_boolean_t  first_test_speed;
    lane_failure_t lane_failure[NUMBER_OF_SERDESES];
};
struct pcs_phy_state {
    pcs_phy_lock_t state_bitmap[NUMBER_OF_SERDESES];
    sxd_boolean_t  align_state;
    sxd_boolean_t  hi_ber;
};
struct pddr_phy_info_resp {
    remote_device_type_t   remote_device;
    port_notifications_t   port_notifications;
    uint16_t               neg_attempts;
    uint8_t                ib_revision;
    uint8_t                lp_ib_revision;
    hw_link_phy_state_t    hw_link_phy_state;
    phy_mgr_disable_mask_t phy_mgr_disable_mask_bitmap;
    struct pcs_phy_state   pcs_phy_state;
    union {
        sxd_port_eth_proto_t eth;
        sxd_port_ib_proto_t  ib;
    } lp_proto_enabled;
    fec_mode_t                     lp_fec_mode_supported;
    fec_mode_t                     lp_fec_mode_req;
    ib_last_link_down_reason_t     ib_last_link_down_reason;
    link_down_lane_fec_t           eth_lastlink_down_lane[NUMBER_OF_SERDESES];
    struct pddr_speed_deg_db       speed_deg;
    uint32_t                       degrade_grade_lane[NUMBER_OF_SERDESES];
    kr_fsm_t                       kr_startup_fsm_lane[NUMBER_OF_SERDESES];
    struct eth_an_debug_indication eth_an_debug_indication;
    ib_phy_fsm_state_trace         ib_phy_fsm_state_trace;
    kr_debug_indication_t          kr_startup_debug_indication[NUMBER_OF_SERDESES];
    uint8_t                        irisc_status;
    stamping_reason_t              stamping_reason;
};
struct pddr_module_info_resp {
    uint8_t             cable_technology;
    uint8_t             cable_breakout;
    uint8_t             ext_ethernet_compliance_code;
    uint8_t             ethernet_compliance_code;
    cable_type_t        cable_type;
    cable_vendor_t      cable_vendor;
    uint8_t             cable_length;
    cable_identifier_t  cable_identifier;
    cable_power_class_t cable_power_class;
    uint8_t             cable_rx_amp;
    uint8_t             cable_rx_emphasis;
    uint8_t             cable_tx_equalization;
    uint8_t             cable_attenuation_12g;
    uint8_t             cable_attenuation_7g;
    uint8_t             cable_attenuation_5g;
    cdr_cap_t           rx_cdr_cap;
    cdr_cap_t           tx_cdr_cap;
    cdr_state_t         rx_cdr_state;
    cdr_state_t         tx_cdr_state;
    uint32_t            vendor_name;
    uint32_t            vendor_pn;
    uint16_t            fw_version;
    uint16_t            vendor_rev;
    uint32_t            vendor_sn;
    uint16_t            temperature;
    uint16_t            voltage;
    uint16_t            rx_power_lane[NUMBER_OF_SERDESES];
    uint16_t            tx_power_lane[NUMBER_OF_SERDESES];
    uint16_t            temperature_high_th;
    uint16_t            temperature_low_th;
    uint16_t            voltage_high_th;
    uint16_t            voltage_low_th;
    uint16_t            rx_power_high_th;
    uint16_t            rx_power_low_th;
    uint16_t            tx_power_high_th;
    uint16_t            tx_power_low_th;
    uint16_t            tx_bias_high_th;
    uint16_t            tx_bias_low_th;
    uint16_t            wavelength;
};

typedef enum {
    GROUP_OPCODE_MONITOR = 0,
    GROUP_OPCODE_ADVANCE = 1
} group_opcode_t;

typedef enum {
    STATUS_OPCODE_NO_ISSUE = 0,
    STATUS_OPCODE_PORT_IS_CLOSE_BY_COMMAND = 1,
    STATUS_OPCODE_AN_NO_PARTNER_DETECTED = 2,
    STATUS_OPCODE_AN_ACK_NOT_RECEIVED = 3,
    STATUS_OPCODE_AN_NEXT_PAGE_EXCHANGE_FAILED = 4,
    STATUS_OPCODE_KR_FRAME_LOCK_NOT_ACQUIREED = 5,
    STATUS_OPCODE_KR_LINK_INHIBIT_TIMEOUT = 6,
    STATUS_OPCODE_KR_LINK_PARTNER_DIDNT_SET_RECEIVER_READY = 7,
    STATUS_OPCODE_KR_TUNING_DIDNT_COMPLETE = 8,
    STATUS_OPCODE_PCS_DIDNT_ACQUIRE_BLOCK_LOCK = 9,
    STATUS_OPCODE_PCS_DIDNT_ACQUIRE_AM_LOCK = 10,
    STATUS_OPCODE_PCS_DIDNT_GET_ALIGN_STATUS = 11,
    STATUS_OPCODE_FC_FEC_ISNT_LOCKED = 12,
    STATUS_OPCODE_RS_FEC_ISNT_LOCKED = 13,
    STATUS_OPCODE_REMOTE_FAULT_RECEIVED = 14,
    STATUS_OPCODE_BAD_SIGNAL_INTEGRITY = 15,
    STATUS_OPCODE_CABLE_COMPLIANCE_CODE_MISMATCH = 16,
    STATUS_OPCODE_STAMPING_OF_NON_MELLANOX_CABLE_MODULE = 20,
    STATUS_OPCODE_CALIBRATION_FAILURE = 23,
    STATUS_OPCODE_EDR_STAMPING = 24,
    STATUS_OPCODE_FDR10_STAMPING = 25,
    STATUS_OPCODE_ETHERNET_COMPLIANCE_CODE_ZERO = 26,
    STATUS_OPCODE_56GE_STAMPING = 27,
    STATUS_OPCODE_NON_MELLANOX_QSFP28 = 28,
    STATUS_OPCODE_NON_MELLANOX_SFP28 = 29,
    STATUS_OPCODE_NO_BACKPLANE_ENABLED = 30,
    STATUS_OPCODE_NO_PASSIVE_PROTOCOL_ENABLED = 31,
    STATUS_OPCODE_NO_ACTIVE_PROTOCOL_ENABLED = 32,
    STATUS_OPCODE_AN_FEC_MISMATCH_DURING_OVERRIDE = 38,
    STATUS_OPCODE_AN_NO_HCD = 39,
    STATUS_OPCODE_BAD_SI_CABLE_IS_CONFIGURED_TO_NON_OPTIMAL_RATE = 42,
    STATUS_OPCODE_INFO_NOT_AVAILABLE = 1023,
    STATUS_OPCODE_CABLE_IS_UNPLUGGED = 1024,
    STATUS_OPCODE_LONG_RANGE_FOR_NON_MLNX_CABLE = 1025,
    STATUS_OPCODE_BUS_STUCK = 1026,
    STATUS_OPCODE_BAD_EEPROM = 1027,
    STATUS_OPCODE_PART_NUMBER_LIST = 1028,
    STATUS_OPCODE_UNSUPPORTED_CABLE = 1029,
    STATUS_OPCODE_MODULE_TEMP_SHUTDOWN = 1030,
    STATUS_OPCODE_SHORTED_CABLE = 1031,
    STATUS_OPCODE_POWER_BUDGET_EXCEEDED = 1032,
    STATUS_OPCODE_MGMT_FORCED_DOWN_THE_PORT = 1033,
    STATUS_OPCODE_MODULE_DISABLED_BY_COMMAND = 1034
} status_opcode_t;

struct pddr_troubleshooting_info_resp {
    group_opcode_t group_opcode;
    uint32_t       status_opcode;
    uint8_t        status_message[256];
};
struct ku_pddr_reg {
    uint8_t             local_port;
    port_access_type_t  pnat;
    pddr_page_options_t page_select;
    union {
        struct pddr_oper_info_resp            oper_info;
        struct pddr_module_info_resp          module_info;
        struct pddr_phy_info_resp             phy_info;
        struct pddr_troubleshooting_info_resp troubleshooting_info;
    } response;
};

/**
 * ku_mogcr_reg structure is used to store the access
 * register MOGCR command parameters
 */
struct ku_mogcr_reg {
    uint8_t  ptp_iftc;
    uint8_t  ptp_eftc;
    uint16_t mirror_latency_scale;
};

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
    uint8_t              dir;
    uint8_t              clr;
    uint8_t              read_one;
    uint8_t              ovf;
    uint8_t              num_record;
    struct mtpptr_record records[4];
};


/**
 * ku_mtpps_reg structure is used to store the access
 * register MTPPS command parameters
 */
struct ku_mtpps_reg {
    uint8_t  cap_max_num_of_pps_out_pins;
    uint8_t  cap_max_num_of_pps_in_pins;
    uint8_t  cap_number_of_pps_pins;
    uint8_t  cap_pin_0_mode;
    uint8_t  cap_pin_1_mode;
    uint8_t  cap_pin_2_mode;
    uint8_t  cap_pin_3_mode;
    uint8_t  cap_pin_4_mode;
    uint8_t  cap_pin_5_mode;
    uint8_t  cap_pin_6_mode;
    uint8_t  cap_pin_7_mode;
    uint32_t field_select;
    uint8_t  pin;
    uint8_t  pin_mode;
    uint8_t  pattern;
    uint8_t  enable;
    uint64_t time_stamp;
    uint16_t out_periodic_adjustment;
    uint16_t out_pulse_duration;
    uint32_t enhanced_out_periodic_adjustment;
    uint8_t  npps;
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
 * ku_access_mogcr_reg structure is used to store the access
 * register MOGCR command parameters
 */
struct ku_access_mogcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mogcr_reg     mogcr_reg; /**< mogcr_reg - mogcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
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


/**
 * ku_access_mtpps_reg structure is used to store the access
 * register MTPPS command parameters
 */
struct ku_access_mtpps_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mtpps_reg     mtpps_reg; /**< mtpps_reg - mtpps register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_sbgcr_reg structure is used to store the SBGCR register parameters
 */
struct ku_sbgcr_reg {
    uint8_t tele_entity; /**< tele_entity - telemetry entity
                          *   0 - TCLASS, 1 - PORT */
    uint8_t cong_fp; /**< cong_fp - congestion false positive */
};

/**
 * ku_access_sbgcr_reg structure is used to store the access
 * register SBGCR command parameters
 */
struct ku_access_sbgcr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_sbgcr_reg     sbgcr_reg; /**< sbgcr_reg - sbgcr register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};


/**
 * ku_access_pddr_reg structure is used to store the access
 * register PDDR command parameters
 */
struct ku_access_pddr_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_pddr_reg      pddr_reg; /**< pddr_reg - pddr register tlv */
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
    KU_PPBMP_MONITOR_GROUP_RS_PRE_FEC_E = 0, /**< Pre RS FEC */
    KU_PPBMP_MONITOR_GROUP_FC_PRE_FEC_E = 1, /**< Pre FC FEC */
    KU_PPBMP_MONITOR_GROUP_NO_FEC_PRE_FEC_E = 2, /**< No FEC/Post FEC */
} ku_ppbmp_monitor_type_e;

/**
 * ku_ppbmc_reg structure is used to store the access
 * register PPBMC command parameters
 */
struct ku_ppbmc_reg {
    uint8_t local_port;
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
 * ku_perar_reg structure is used to store the access
 * register PERAR command parameters
 */
struct ku_perar_reg {
    uint16_t region_id;
    uint8_t  inkbr;
    uint16_t hw_region;
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
 * ku_access_perar_reg structure is used to store the access
 * register perar command parameters
 */
struct ku_access_perar_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_perar_reg     perar_reg; /**< perar_reg - perar register tlv */
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
 * ku_mcion_reg structure is used to store the access
 * register MCION command parameters
 */
struct ku_mcion_reg {
    uint8_t  module;
    uint16_t module_status_bits;
    uint8_t  module_inputs;
    uint8_t  module_inputs_mask;
};

/**
 * ku_access_mcion_reg structure is used to store the access
 * register MCION command parameters
 */
struct ku_access_mcion_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_mcion_reg     mcion_reg; /**< mcion_reg - mcion register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * ku_moni_reg structure is used to store the access
 * register MONI command parameters
 */
struct ku_moni_reg {
    uint8_t local_port;     /**< local_port - local port number */
    uint8_t en;             /**< en - enable monitoring on network interface */
};

/**
 * ku_access_moni_reg structure is used to store the access
 * register MONI command parameters
 */
struct ku_access_moni_reg {
    struct ku_operation_tlv op_tlv; /**< op_tlv - operation tlv struct */
    struct ku_moni_reg      moni_reg; /**< mcion_reg - mcion register tlv */
    uint8_t                 dev_id; /**< dev_id - device id */
};

/**
 * sx_mtutc_op enumerated type is used to note the possible
 * mtutc OPs.
 */
typedef enum sx_mtutc_op {
    SX_MTUTC_OP_SET_TIME_NEXT_SEC_E = SXD_MTUTC_OP_SET_TIME_NEXT_SEC,
    SX_MTUTC_OP_SET_TIME_IMMEDIATE_E = SXD_MTUTC_OP_SET_TIME_IMMEDIATE,
    SX_MTUTC_OP_ADJUST_TIME_E = SXD_MTUTC_OP_ADJUST_TIME,
    SX_MTUTC_OP_ADJUST_FREQ_E = SXD_MTUTC_OP_ADJUST_FREQ,
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
/**
 * ku_sx_bitmap is used to store the bitmap.
 */
struct ku_sx_bitmap {
    uint32_t max;
    uint8_t  table[NUMBER_OF_BITS_IN_BITMAP];
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
    uint8_t                              ib_to_local_db[MAX_IBPORT_NUM + 1];
    uint8_t                              system_to_local_db[MAX_SYSPORT_NUM];
    uint16_t                             local_to_system_db[MAX_PHYPORT_NUM + 1];
    uint8_t                              lag_is_rp[MAX_LAG_NUM];
    uint16_t                             lag_rp_vid[MAX_LAG_NUM];
    uint16_t                             lag_rp_rif[MAX_LAG_NUM][SXD_MAX_VLAN_NUM];
    uint8_t                              lag_rp_rif_valid[MAX_LAG_NUM][SXD_MAX_VLAN_NUM];
    uint8_t                              lag_member_to_local_db[MAX_LAG_NUM][MAX_LAG_MEMBERS_NUM];
    uint8_t                              local_is_rp[MAX_PHYPORT_NUM + 1];
    uint16_t                             local_rp_vid[MAX_PHYPORT_NUM + 1];
    uint16_t                             port_rp_rif[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    uint8_t                              port_rp_rif_valid[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    uint8_t                              lag_oper_state[MAX_LAG_NUM];
    uint8_t                              port_ber_monitor_state[MAX_PHYPORT_NUM + 1];
    uint8_t                              port_ber_monitor_bitmask[MAX_PHYPORT_NUM + 1];
    uint8_t                              tele_thrs_state[MAX_PHYPORT_NUM + 1];
    uint64_t __attribute__((aligned(8))) tele_thrs_tc_vec[MAX_PHYPORT_NUM + 1];
    uint16_t                             truncate_size_db[NUMBER_OF_RDQS];
    uint32_t                             icmp_vlan2ip_db[SXD_MAX_VLAN_NUM];
    uint16_t                             port_vid_to_fid[MAX_PHYPORT_NUM + 1][SXD_MAX_VLAN_NUM];
    struct ku_sx_bitmap                  ts_bitmap;
    struct ku_sx_bitmap                  high_prio_cq_bitmap;
    uint16_t                             fid_to_hwfid[MAX_FIDS_NUM];
    uint16_t                             rif_id_to_hwfid[MAX_RIFS_NUM];
    /**
     * If new fields have to be added to this struct, please add them after the magic_start field
     * and before the magic_end field.
     */
    uint32_t magic_end;
};

/* Please, do not move this include.
 *  It includes auto generated code which uses data defined in this file. */
#ifdef __KERNEL__
#include <linux/mlx_sx/auto_registers/kernel_user_auto.h>
#else
#include "auto_registers/kernel_user_auto.h"
#endif

#endif /* KERNEL_USER_H_ */

/************************************************
 *                  EOF                         *
 ***********************************************/
