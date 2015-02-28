/**
****************************************************************************************
*
* @file app_ptu_hooks.c
*
* @brief A4WP WPT Power Trasmit Unit (PTU) application hooks file - it defines hooks
* that has to be implemented by 'power antenna' part of the application
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
#include "app_ptu_hooks.h"
#include "app_ptu.h"

uint8_t app_ptu_validate_pru_static(struct pru_static_value *static_val)
{
    // NOTE: add real validation here, eg:
    //    if (s_value.protocol_rev > 1)
    //        return APP_PTU_ERR_PRU_STATIC_REJECTED;

    return APP_PTU_NO_ERROR;
}

uint8_t app_ptu_validate_ptu_static(struct ptu_static_value const *ptu_static_val)
{
    uint8_t max_number_of_dev = (ptu_static_val->num_devices_supported + 1);

    switch (ptu_static_val->ptu_class)
{
        case WPTC_CLASS_1:
            // always valid because min number of dev always at least 1
            // at least 1 Category#1 device
            break;
        case WPTC_CLASS_2:
            // at least 2 Category#1 devices
            if (max_number_of_dev < 2)
                return APP_PTU_ERR_PTU_STATIC_WRONG_NUM_DEVICES_VAL;
            break;
        case WPTC_CLASS_3:
            // at least 2 Category#3 devices
            if (max_number_of_dev < 2)
                return APP_PTU_ERR_PTU_STATIC_WRONG_NUM_DEVICES_VAL;
            break;
        case WPTC_CLASS_4:
            // at least 3 Category#3 devices
            if (max_number_of_dev < 3)
                return APP_PTU_ERR_PTU_STATIC_WRONG_NUM_DEVICES_VAL;
            break;
        case WPTC_CLASS_5:
            // at least 4 Category#3 device
            if (max_number_of_dev < 4)
                return APP_PTU_ERR_PTU_STATIC_WRONG_NUM_DEVICES_VAL;
            break;
        case WPTC_CLASS_6:
            // at least 5 Category#3 device
            if (max_number_of_dev < 5)
                return APP_PTU_ERR_PTU_STATIC_WRONG_NUM_DEVICES_VAL;
            break;
        default:
            return APP_PTU_ERR_PTU_STATIC_WRONG_PTU_CLASS;
}

    // even if number of supported devices is ok with current PTU Class, we also
    // have to confirm it locally if current iml can support so many connections at once
    if (max_number_of_dev > PTU_IMPL_MAX_SUPPORTED_DEV)
        return APP_PTU_ERR_PTU_STATIC_NUM_DEV_EXCEED_CONN_NUM;

    return APP_PTU_NO_ERROR;
}
