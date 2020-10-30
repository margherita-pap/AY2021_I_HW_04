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
            /*if we receive 1 of these 2 character we can start sampling the signals
             *and so we start the ADC, and turn on the LED on board to inform that we are sendind data
             */
            SendByteFlag=1;
            Pin_LED_onboard_Write(LED_ON);
            TimerADC_Start();
            break;
        case 'S':
        case 's':
            /*Stop the sending of data, turn off the LED on board
             *and restart the original configuration of LED driver
             */
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
