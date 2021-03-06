/**
 ****************************************************************************************
 *
 * @file periph_setup.c
 *
 * @brief Peripherals setup and initialization. 
 *
 * Copyright (C) 2012. Dialog Semiconductor Ltd, unpublished work. This computer 
 * program includes Confidential, Proprietary Information and is a Trade Secret of 
 * Dialog Semiconductor Ltd.  All use, disclosure, and/or reproduction is prohibited 
 * unless authorized in writing. All Rights Reserved.
 *
 * <bluetooth.support@diasemi.com> and contributors.
 *
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "rwip_config.h"             // SW configuration
#include "periph_setup.h"            // peripheral configuration
#include "global_io.h"
#include "gpio.h"
#include "uart.h"                    // UART initialization


/**
 ****************************************************************************************
 * @brief Each application reserves its own GPIOs here.
 *
 * @return void
 ****************************************************************************************
 */

#if DEVELOPMENT_DEBUG

void GPIO_reservations(void)
{
/*
* Globally reserved GPIOs reservation
*/

/*
* Application specific GPIOs reservation
*/    
#if (BLE_APP_PRESENT)
#if BLE_ANC_CLIENT
    #if USE_PUSH_BUTTON
    RESERVE_GPIO( PUSH_BUTTON, GPIO_BUTTON_PORT, GPIO_BUTTON_PIN, PID_GPIO);   
    #endif // USE_PUSH_BUTTON
    RESERVE_GPIO( GREEN_LED, GPIO_ALERT_LED_PORT, GPIO_ALERT_LED_PIN, PID_GPIO);
#endif
#endif
#ifdef CFG_PRINTF_UART2
	RESERVE_GPIO( UART2_TX, GPIO_PORT_0,  GPIO_PIN_4, PID_UART2_TX);
	RESERVE_GPIO( UART2_RX, GPIO_PORT_0,  GPIO_PIN_5, PID_UART2_RX);
#endif
    
}
#endif //DEVELOPMENT_DEBUG

/**
 ****************************************************************************************
 * @brief Map port pins
 *
 * The Uart and SPI port pins and GPIO ports are mapped
 ****************************************************************************************
 */
void set_pad_functions(void)        // set gpio port function mode
{

#ifdef CFG_PRINTF_UART2
	GPIO_ConfigurePin( GPIO_PORT_0, GPIO_PIN_4, OUTPUT, PID_UART2_TX, false );
	GPIO_ConfigurePin( GPIO_PORT_0, GPIO_PIN_5, INPUT, PID_UART2_RX, false );
#endif

#if BLE_ANC_CLIENT
    #if USE_PUSH_BUTTON
    GPIO_ConfigurePin( GPIO_BUTTON_PORT, GPIO_BUTTON_PIN, INPUT_PULLUP, PID_GPIO, false ); // Push Button 
    #endif // USE_PUSH_BUTTON
    GPIO_ConfigurePin( GPIO_ALERT_LED_PORT, GPIO_ALERT_LED_PIN, OUTPUT, PID_GPIO, false ); //Alert LED
#endif
}


/**
 ****************************************************************************************
 * @brief Enable pad's and peripheral clocks assuming that peripherals' power domain is down. The Uart and SPi clocks are set.
 *
 * @return void
 ****************************************************************************************
 */
void periph_init(void) 
{
	// Power up peripherals' power domain
    SetBits16(PMU_CTRL_REG, PERIPH_SLEEP, 0);
    while (!(GetWord16(SYS_STAT_REG) & PER_IS_UP)) ; 
    
#if ES4_CODE
    SetBits16(CLK_16M_REG,XTAL16_BIAS_SH_DISABLE, 1);
#endif    
	
	//rom patch
	patch_func();
	
	//Init pads
	set_pad_functions();

#if (BLE_APP_PRESENT)
/*
* (Re)Initialize peripherals
i.e.    
    uart_init(UART_BAUDRATE_115K2, 3);
*/        
#endif

#ifdef CFG_PRINTF_UART2
		SetBits16(CLK_PER_REG, UART2_ENABLE, 1);
		uart2_init(UART_BAUDRATE_115K2, 3);
#endif
    
   // Enable the pads
	SetBits16(SYS_CTRL_REG, PAD_LATCH_EN, 1);
}
