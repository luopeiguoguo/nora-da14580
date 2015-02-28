/**
****************************************************************************************
*
* @file app_ancc_proj.h
*
* @brief ANCC application header file.
*
* Copyright (C) 2014. Dialog Semiconductor Ltd, unpublished work. This computer 
 * program includes Confidential, Proprietary Information and is a Trade Secret of 
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited 
 * unless authorized in writing. All Rights Reserved.
*
* <bluetooth.support@diasemi.com> and contributors.
*
****************************************************************************************
*/

#ifndef APP_ANCC_PROJ_H_
#define APP_ANCC_PROJ_H_

/**
 ****************************************************************************************
 * @addtogroup APP
 *
 * @brief 
 *
 * @{
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "rwble_config.h"
#include "app_task.h"                  // application task
#include "gapc_task.h"                 // gap functions and messages
#include "gapm_task.h"                 // gap functions and messages
#include "app.h"                       // application definitions
#include "co_error.h"                  // error code definitions
#include "smpc_task.h"                 // error code definitions
 

#if (BLE_ANC_CLIENT)
#include "app_ancc.h"
#include "app_ancc_task.h"
#endif 

#if (BLE_DIS_SERVER)
#include "app_dis.h"
#include "app_dis_task.h"
#endif

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

/****************************************************************************
Define device name. Used in Advertise string
*****************************************************************************/

#define APP_DEVICE_NAME "DA14580 ANCS Client"
#define APP_ADV_DATA        "\x11\x15\xD0\x00\x2D\x12\x1E\x4B\x0F\xA4\x99\x4E\xCE\xB5\x31\xF4\x05\x79"
#define APP_ADV_DATA_LEN    (18)

#define APP_SCNRSP_DATA         "\x00"
#define APP_SCNRSP_DATA_LENGTH  (0)
/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/// @} APP

#endif //APP_ANCC_PROJ_H_
