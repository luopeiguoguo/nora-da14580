/**
****************************************************************************************
*
* @file app_ptu_hooks.h
*
* @brief A4WP WPT Power Transmit Unit (PTU) application header file.
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
#ifndef APP_PTU_HOOKS_H_
#define APP_PTU_HOOKS_H_

#include "wpt_common.h"

uint8_t app_ptu_validate_pru_static(struct pru_static_value *static_val);

uint8_t app_ptu_validate_ptu_static(struct ptu_static_value const *ptu_static_val);

#endif /* APP_PTU_HOOKS_H_ */
