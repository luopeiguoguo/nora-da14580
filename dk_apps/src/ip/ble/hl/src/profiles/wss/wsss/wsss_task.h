/**
 ****************************************************************************************
 *
 * @file wsss_task.h
 *
 * @brief Header file - WSSSTASK.
 *
 * Copyright (C) 20124 Dialog Semiconductor Ltd, unpublished work. This computer 
 * program includes Confidential, Proprietary Information and is a Trade Secret of 
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited 
 * unless authorized in writing. All Rights Reserved.
 *
 * <bluetooth.support@diasemi.com> and contributors.
 *
 ****************************************************************************************
 */

#ifndef WSSS_TASK_H_
#define WSSS_TASK_H_

/**
 ****************************************************************************************
 * @addtogroup WSSSTASK Task
 * @ingroup WSSS
 * @brief Weight Scale Service Server Task
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#if (BLE_WSS_SERVER)
#include <stdint.h>
#include "compiler.h"
#include "ke_task.h"
#include "wsss.h"
#include "prf_types.h"

/*
 * DEFINES
 ****************************************************************************************
 */

#define WSSS_IDX_MAX        (1)

/// Possible states of the DISS task
enum
{
    ///Disabled state
    WSSS_DISABLED,
    ///Idle state
    WSSS_IDLE,
    ///Connected state
    WSSS_CONNECTED,

    ///Number of defined states.
    WSSS_STATE_MAX
};

/// Messages for Weight Scale Service Server
enum
{
    ///Add a WSS instance into the database
    WSSS_CREATE_DB_REQ = KE_FIRST_MSG(TASK_WSSS),
    
    ///Inform APP of database creation status
    WSSS_CREATE_DB_CFM,
    
    ///Set the value of "Measurement" attribute
    WSSS_MEAS_SEND_REQ,

    ///Send weight measurement value confirmation to APP if correctly sent.
    WSSS_MEAS_SEND_CFM,
    
    ///Inform APP of new configuration value
    WSSS_CFG_INDNTF_IND,
    
    ///Start the Weight Scale Service Task - at connection
    WSSS_ENABLE_REQ,

    /// Inform the application that the profile service role task has been disabled after a disconnection
    WSSS_DISABLE_IND,

    /// Error indication to Host
    WSSS_ERROR_IND,
};

/// Weight Measurement Flags field bit values
enum
{
    /// Measurement Units
    /// SI (weight & mass in kg and height in cm)
    WSSS_MEAS_FLAG_UNIT_SI            = 0x00,
    /// Imperial (weight & mass in lb and height in inches)
    WSSS_MEAS_FLAG_UNIT_IMPERIAL      = 0x01,
    /// Time Stamp
    /// Time Stamp not present
    WSSS_MEAS_FLAG_NO_TIME_STAMP      = 0x00,
    /// Time Stamp present
    WSSS_MEAS_FLAG_TIME_STAMP         = 0x02,
    /// User ID
    /// User id not present
    WSSS_MEAS_FLAG_USERID_NOT_PRESENT = 0x00,
    /// User id present
    WSSS_MEAS_FLAG_USERID_PRESENT     = 0x04,
    /// BMI & Height 
    /// BMI & Height not present
    WSSS_MEAS_FLAG_BMI_HT_NOT_PRESENT = 0x00,
    /// BMI & Height present
    WSSS_MEAS_FLAG_BMI_HT_PRESENT     = 0x08,
};

/// Weight Measurement User id field
enum
{
    /// Unknown user
    WSSS_MEAS_UNLNOWN_USER = 0xFF,
};

/// Weight Feature characteristic bit values
enum
{
    /// Time Stamp
    WSSS_FEAT_TIME_STAMP_NOT_SUPPORTED = 0x00,
    WSSS_FEAT_TIME_STAMP_SUPPORTED     = 0x01,
    /// Multiple Users
    WSSS_FEAT_MULTI_USER_NOT_SUPPORTED = 0x00,
    WSSS_FEAT_MULTI_USER_SUPPORTED     = 0x02,
    /// BMI
    WSSS_FEAT_BMI_NOT_SUPPORTED        = 0x00,
    /// User id present
    WSSS_FEAT_BMI_SUPPORTED            = 0x04,
    /// Weight Display Resolution 
    /// Not used or supported
    WSSS_FEAT_WT_DISPLAY_NOT_USED      = 0x00,
    /// Display resolution of 0.5 kg or 1 lb
    WSSS_FEAT_WT_DISPLAY_10TH_ACC      = 0x08,
    /// Display resolution of 0.05 kg or 0.1 lb
    WSSS_FEAT_WT_DISPLAY_100TH_ACC     = 0x10,
    /// Display resolution of 0.005 kg or 0.01 lb
    WSSS_FEAT_WT_DISPLAY_1000TH_ACC    = 0x18,
};



/*
 * API MESSAGES STRUCTURES
 ****************************************************************************************
 */

struct date_time
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
};

/// Parameters of the @ref WSSS_CREATE_DB_REQ message
struct wsss_create_db_req
{
   /// Unused and unchecked parameter - Avoid to have an empty structure
   uint8_t unused;
};

/// Parameters of the @ref WSSS_CREATE_DB_CFM message
struct wsss_create_db_cfm
{
    ///Status
    uint8_t status;
};

/// Feature structure
struct wss_feature
{
    /// flags 
    uint16_t flags;
};

/// Weight measurement structure - shall be dynamically allocated
struct wss_wt_meas
{
    /// flags 
    uint8_t flags;
    /// weight
    uint16_t weight;
    /// Time stamp 
    struct date_time datetime;
    /// User ID
    uint8_t userid;
    /// BMI
    uint8_t bmi;
    /// Height
    uint8_t height;
};

/// Parameters of the @ref WSSS_MEAS_VAL_SET_REQ message - shall be dynamically allocated
struct wsss_meas_send_req
{
    /// flags 
    uint16_t conhdl;
    /// weight measurement
    struct wss_wt_meas meas_val;
};

///Parameters of the @ref WSSS_MEAS_SEND_CFM message
struct wsss_meas_send_cfm
{
    ///Connection handle
    uint16_t conhdl;
    ///Status
    uint8_t status;
};

///Parameters of the @ref WSSS_CFG_INDNTF_IND message
struct wsss_cfg_indntf_ind
{
    ///Connection handle
    uint16_t conhdl;
    ///Stop/notify/indicate value to configure into the peer characteristic
    uint16_t cfg_val;
};

/// Parameters of the @ref WSSS_SET_CHAR_VAL_REQ message - shall be dynamically allocated
struct wsss_unsent_meas_val
{
    // pointer to next item
    struct wsss_unsent_meas_val* next;
    
    /// packed measurement value
    uint8_t wsss_packed_meas_val[1];
};

/// Parameters of the @ref WSSS_ENABLE_REQ message
struct wsss_enable_req
{
    ///Connection handle
    uint16_t conhdl;
    /// security level: b0= nothing, b1=unauthenticated, b2=authenticated, b3=authorized;
    /// b1 or b2 and b3 can go together
    /// it matches the permission bytes order of settings
    uint8_t sec_lvl;
    ///Type of connection - will someday depend on button press length; can be CFG or DISCOVERY
    uint8_t con_type;
    
    /// Weight Scale indication configuration
    uint16_t wt_meas_ind_en;
    /// Weight Scale features: 
    /// bit[0]: Time Stamp, bit[1]: Multiple Users Stamp, bit[2]: BMI, 
    /// bit[3-5]: Weight display resolution, 
    uint16_t ws_feature;
};

/// Parameters of the @ref WSSS_DISABLE_IND message
struct wsss_disable_ind
{
    ///Connection handle
    uint16_t conhdl;
};

///Parameters of the @ref DISC_RD_CHAR_REQ message
struct wsss_rd_feat_char_req
{
    ///Connection handle
    uint16_t conhdl;
    ///Characteristic value code
    uint8_t char_code;
};

/*
 * TASK DESCRIPTOR DECLARATIONS
 ****************************************************************************************
 */
extern const struct ke_state_handler wsss_state_handler[WSSS_STATE_MAX];
extern const struct ke_state_handler wsss_default_handler;
extern ke_state_t wsss_state[WSSS_IDX_MAX];

#endif //BLE_WSSS_SERVER

/// @} WSSSTASK
#endif // WSSS_TASK_H_
