/**
****************************************************************************************
*
* @file app_ptu_gtl_task.c
*
* @brief Implementation file for A4WP Wireless Power Transfer PTU application - GTL API handlers.
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

#include "app_ptu_gtl_task.h"
#include "app_api.h"
#include "app_ptu_hooks.h"
#include "app_ptu.h"
#if (BLE_APP_PTU)
// *****Integrated host GTL for PTU APP*****

static void send_rsp_cfm_to_gtl_app(ke_msg_id_t const req_id, uint8_t status)
{
    struct app_ext_ptu_generic_rsp * rsp = KE_MSG_ALLOC(APP_PTU_EXT_GENERIC_CFM, TASK_GTL, TASK_APP,
                                                        app_ext_ptu_generic_rsp);

    rsp->status = status;
    rsp->req_id = req_id;

    ke_msg_send((void *) rsp);
}

/**
 ****************************************************************************************
 * @brief Handles PTU latching fault cleared indication from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_latching_fault_cleared_ind_handler(ke_msg_id_t const msgid,
                                       void const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    send_rsp_cfm_to_gtl_app(APP_PTU_EXT_LATCHING_FAULT_CLEARED_IND, APP_PTU_NO_ERROR);

    // if there latching fault is cleared by user interaction, then resetting
    // self latchin fault counter
    app_ptu_env.self_clear_counter = 0;
    app_ptu_latching_fault_cleared_handle();

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles PTU load detecteded indication from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_load_detected_ind_handler(ke_msg_id_t const msgid,
                              void const *param,
                              ke_task_id_t const dest_id,
                              ke_task_id_t const src_id)
{
    app_ptu_load_detected_handle();

    send_rsp_cfm_to_gtl_app(APP_PTU_EXT_LOAD_DETECTED_IND, APP_PTU_NO_ERROR);
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles PTU local fault detected indication from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_local_fault_detected_ind_handler(ke_msg_id_t const msgid,
                                            struct app_ext_ptu_local_fault_detected_ind const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id)
{
    app_ptu_local_fault_detected_handle(param->err_code);

    send_rsp_cfm_to_gtl_app(APP_PTU_EXT_LOCAL_FAULT_DETECTED_IND, APP_PTU_NO_ERROR);
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles PTU local fault cleared indication from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_local_fault_cleared_ind_handler(ke_msg_id_t const msgid,
                                            void const *param,
                                            ke_task_id_t const dest_id,
                                            ke_task_id_t const src_id)
{
    app_ptu_local_fault_cleared_handle();

    send_rsp_cfm_to_gtl_app(APP_PTU_EXT_LOCAL_FAULT_CLEARED_IND, APP_PTU_NO_ERROR);
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles PTU local fault cleared indication from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_get_current_state_ind_handler(ke_msg_id_t const msgid,
                                          void const *param,
                                          ke_task_id_t const dest_id,
                                          ke_task_id_t const src_id)
{
    struct app_ext_ptu_state_ntf *msg = KE_MSG_ALLOC(APP_PTU_EXT_GET_CURRENT_STATE_RSP,
                                                     TASK_GTL, TASK_APP,
                                                     app_ext_ptu_state_ntf);
    msg->state_new = ke_state_get(TASK_APP_PTU);

    ke_msg_send(msg);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles PTU local fault cleared indication from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_get_current_dev_count_ind_handler(ke_msg_id_t const msgid,
                                              void const *param,
                                              ke_task_id_t const dest_id,
                                              ke_task_id_t const src_id)
{
    struct app_ext_ptu_conn_devices_count_ntf *msg = KE_MSG_ALLOC(APP_PTU_EXT_GET_CURRENT_DEV_COUNT_RSP,
                                                                 TASK_GTL, TASK_APP,
                                                                 app_ext_ptu_conn_devices_count_ntf);
     msg->device_count = app_ptu_env.conn_count;
     ke_msg_send(msg);

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles PTU get current pru dev tab indication from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_get_current_pru_dev_tab_ind_handler(ke_msg_id_t const msgid,
                                              void const *param,
                                              ke_task_id_t const dest_id,
                                              ke_task_id_t const src_id)
{

    app_ptu_gtl_send_update_of_wdev_tab();

    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles set PTU static from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_set_ptu_static_ind_handler(ke_msg_id_t const msgid,
                                       struct ptu_static_value const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    uint8_t validate_err;

    validate_err = app_ptu_validate_ptu_static(param);
    if (validate_err == APP_PTU_NO_ERROR)
        memcpy(&(app_ptu_env.ptu_stat_val), param, WPTS_PTU_STATIC_CHAR_LEN);

    // todo: check if power value is different
    if (app_ptu_env.conn_count > 0)
    {
        // Allowing for setting PTU Static when there is already some device connected
        // BUT:
        // have to try if power can be adjusted IF new Power val is different than previous

        send_rsp_cfm_to_gtl_app(APP_PTU_EXT_SET_PTU_STATIC_IND, APP_PTU_ERR_PTU_STATIC_NOT_ALLOWED_CONN_DEV);
        return (KE_MSG_CONSUMED);
    }

    send_rsp_cfm_to_gtl_app(APP_PTU_EXT_SET_PTU_STATIC_IND, validate_err);
    return (KE_MSG_CONSUMED);
}

/**
 ****************************************************************************************
 * @brief Handles set PRU control default value write from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Handles set PTU time set default value from External APP
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_set_time_set_default_ind_handler(ke_msg_id_t const msgid,
                                       struct app_ext_ptu_time_set_default_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    app_ptu_env.time_set_default_val = param->time_set_val;

    send_rsp_cfm_to_gtl_app(APP_PTU_EXT_SET_TIME_SET_DEFAULT_IND, APP_PTU_NO_ERROR);
    return (KE_MSG_CONSUMED);
}

//
/**
 ****************************************************************************************
 * @brief Handles validation result of Time Set validation
 *
 * @param[in] msgid     Id of the message received.
 * @param[in] param     Pointer to the parameters of the message.
 * @param[in] dest_id   ID of the receiving task instance
 * @param[in] src_id    ID of the sending task instance.
 *
 * @return If the message was consumed or not.
 ****************************************************************************************
 */
int app_ptu_time_set_validated_result_ind_handler(ke_msg_id_t const msgid,
                                       struct app_ext_ptu_time_set_validated_ind const *param,
                                       ke_task_id_t const dest_id,
                                       ke_task_id_t const src_id)
{
    send_rsp_cfm_to_gtl_app(APP_PTU_EXT_SET_TIME_SET_DEFAULT_IND, APP_PTU_NO_ERROR);

    if (param->status != APP_PTU_NO_ERROR)
    {
        app_ptu_send_ext_error_ntf(param->status, param->connhdl);

        // going to latching fault because time set validation failed, cross
        // connection check failed
        app_ptu_proceed_to_latching_fault();
    }

    return (KE_MSG_CONSUMED);
}

int app_ptu_ptxin_var_rem_detect_ind_handler(ke_msg_id_t const msgid,
                                             struct app_ext_ptxin_variation_detect_ind const *param,
                                             ke_task_id_t const dest_id,
                                             ke_task_id_t const src_id)
{
    if (param->ptxin_variation >= 2)
    {
        ke_timer_set(APP_PTU_TIMER_PTXIN_VARIATION_EXPIRE, TASK_APP, PTU_PTXIN_VARIATION_EXPIRE_TIMER_VAL);
        app_ptu_env.ptxin_variation_detect = true;
    }

    send_rsp_cfm_to_gtl_app(APP_PTU_EXT_PTXIN_VAR_DEV_REM_DETECT_IND, APP_PTU_NO_ERROR);

    return (KE_MSG_CONSUMED);
}
#endif //(BLE_APP_PTU)
// *** INTEGRATED API END *********
