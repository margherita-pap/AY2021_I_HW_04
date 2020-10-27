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
#include "UART_InterruptRoutine.h"

uint8_t ch_received;

CY_ISR_PROTO(Custom_ISR_RX){
    ch_received= UART_GetChar();
    switch(ch_received){
        case 'B' :
        case 'b':
            SendByteFlag=1;
            Pin_LED_onboard_Write(LED_ON);
            TimerADC_Start();
            break;
        case 'S':
        case 's':
            SendByteFlag=0;
            Pin_LED_onboard_Write(LED_OFF);
            TimerADC_Stop();
            PWM_LED_Init();
            break;
        default:
            break;
    }
}

        
        
    
/* [] END OF FILE */
