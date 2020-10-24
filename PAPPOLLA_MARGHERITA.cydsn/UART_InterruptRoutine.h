/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef __UART_INTERRUPTROUTINE_H_
    #define __UART_INTERRUPTROUTINE_H_
    #include "cytypes.h"
    #include "stdio.h"
    #include "UART.h"
    #include "Pin_LED_onboard.h"
    #include "TimerADC.h"
    CY_ISR_PROTO (Custom_ISR_RX);
    
    volatile uint8_t SendByteFlag;
#endif    
    
/* [] END OF FILE */
