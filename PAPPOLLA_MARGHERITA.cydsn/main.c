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
#include "project.h"
#include "UART_InterruptRoutine.h"
#include "ADC_InterruptRoutine.h"
extern uint8_t flag_LED_on;
extern uint8_t flag_LED_off;
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    PWM_LED_Start();
    AMux_Start();
    ADC_DelSig_Start();
    isr_UART_Rx_StartEx(Custom_ISR_RX);
    isr_ADC_StartEx(Custom_ISR_ADC);
    PacketReadyFlag=0;
    ADC_DelSig_StartConvert();
    DataBuffer[0]=0xA0;
    DataBuffer[TRANSMIT_BUFFER_SIZE-1]=0xC0;
    flag_LED_on=0;
    flag_LED_off=0;
    for(;;)
    { 
        if(PacketReadyFlag==1){
            if(flag_LED_off){
                DataBuffer[3]=0x00;
                DataBuffer[4]=0x00;
                UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE);
                flag_LED_off=0;
            }
        
            if(flag_LED_on){
            UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE);
            flag_LED_off=0;
            }  
           
        PacketReadyFlag=0;
    }
   }
 }

/* [] END OF FILE */
