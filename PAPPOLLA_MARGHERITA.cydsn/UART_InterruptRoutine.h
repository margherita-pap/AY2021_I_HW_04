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
    #include "project.h"
    CY_ISR_PROTO (Custom_ISR_RX);
    // This variable goes high if the UART receive the start command 'b' or 'B'
    volatile uint8_t SendByteFlag;
#endif    

#define HIGH 1
#define LOW 0
#define LED_ON HIGH
#define LED_OFF LOW
/* [] END OF FILE */
