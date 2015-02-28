/**
****************************************************************************************
*
* @file app_ptu_gtl_task.h
*
* @brief Header file for A4WP Wireless Power Transfer PTU application - GTL API handlers.
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

#ifndef APP_PTU_GTL_TASK_H_
#define APP_PTU_GTL_TASK_H_

#include "ke_task.h"         // kernel task
#include "ke_msg.h"          // kernel message
#include <stdint.h>          // standard integer
#include "app_ptu.h"

struct app_ext_ptu_generic_rsp
{
    ke_msg_id_t req_id;
    uint8_t status;
};

struct app_ext_ptu_local_fault_detected_ind
{
    uint8_t err_code; // Value for error code, eg. PTU_APP_LOCAL_ERROR_OVER_TEMP
                      // (more definitions can be found in app_ptu.h file)
};

struct app_ext_ptu_load_detected_ind
{
    uint16_t impedance_shift;
};

struct app_ext_ptu_time_set_default_ind
{
    uint8_t time_set_val;
};

struct app_ext_ptu_state_ntf
{
    ke_state_t state_new;
};

struct app_ext_ptu_pru_error_ntf
{
    uint8_t err_val;
    uint16_t connhdl;
};

struct app_ext_ptu_conn_devices_count_ntf
{
    uint8_t device_count;
};

struct app_ext_ptu_pru_dev_ntf
{
    uint8_t wpts_dev_count;
    struct wpts_pub_data wpts_devices[__ARRAY_EMPTY];
};

/**
 * Used for checking time set load right after writing PRU control
 */
struct app_ext_ptu_time_set_check_req
{
    uint16_t connhdl;
    uint8_t time_set_val;
};

/**
 * Stores result of time set load validation by target PRU device
 */
struct app_ext_ptu_time_set_validated_ind
{
    uint16_t connhdl;
    uint8_t status;
};

/**
 * Stores ptxin variation value that has been detected (probably after one of
 * PRU was suddenly taken from charging area)
 */
struct app_ext_ptxin_variation_detect_ind
{
    uint8_t ptxin_variation;
};

// Integrated host GTL for PTU APP
int app_ptu_latching_fault_cleared_ind_handler(ke_msg_id_t const msgid,
                                               void const *param,
                                               ke_task_id_t const dest_id,
                                               ke_task_id_t const src_id);

int app_ptu_load_detected_ind_handler(ke_msg_id_t const msgid,
                                      void const *param,
                                      ke_task_id_t const dest_id,
                                      ke_task_id_t const src_id);

int app_ptu_local_fault_detected_ind_handler(ke_msg_id_t const msgid,
                                            struct app_ext_ptu_local_fault_detected_ind const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id);

int app_ptu_local_fault_cleared_ind_handler(ke_msg_id_t const msgid,
                                            void const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id);

int app_ptu_get_current_state_ind_handler(ke_msg_id_t const msgid,
                                          void const *param,
                                          ke_task_id_t const dest_id,
                                          ke_task_id_t const src_id);

int app_ptu_get_current_dev_count_ind_handler(ke_msg_id_t const msgid,
                                              void const *param,
                                              ke_task_id_t const dest_id,
                                              ke_task_id_t const src_id);

int app_ptu_get_current_pru_dev_tab_ind_handler(ke_msg_id_t const msgid,
                                                void const *param,
                                                ke_task_id_t const dest_id,
                                                ke_task_id_t const src_id);

int app_ptu_set_ptu_static_ind_handler(ke_msg_id_t const msgid,
                                       struct ptu_static_value const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id);

int app_ptu_set_time_set_default_ind_handler(ke_msg_id_t const msgid,
                                       struct app_ext_ptu_time_set_default_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id);

int app_ptu_time_set_validated_result_ind_handler(ke_msg_id_t const msgid,
                                       struct app_ext_ptu_time_set_validated_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id);

int app_ptu_ptxin_var_rem_detect_ind_handler(ke_msg_id_t const msgid,
                                             struct app_ext_ptxin_variation_detect_ind const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id);

#endif //APP_PTU_GTL_TASK_H_
