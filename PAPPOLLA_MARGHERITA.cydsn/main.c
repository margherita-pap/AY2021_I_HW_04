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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    PWM_LED_Start();
    AMux_Start();
    ADC_DelSig_Start();
    isr_UART_Rx_StartEx(Custom_ISR_RX);
    isr_ADC_StartEx(Custom_ISR_ADC);
    ADC_DelSig_StartConvert();
    TimerADC_Start();
    SendByteFlag=0;
    PacketReadyFlag=0;
    Flag_LED_on=0;
    DataBuffer[0]=0xA0;
    DataBuffer[TRANSMIT_BUFFER_SIZE-1]=0xC0;
    
    for(;;)
    { 
        if(PacketReadyFlag==1){
            if(Flag_LED_off==1){
                DataBuffer[3]=0x00;
                DataBuffer[4]=0x00;
                UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE);
                Flag_LED_off=0;
            }
        
            if(Flag_LED_on==1){
            UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE);
            Flag_LED_on=0;
            
            }  
           
        PacketReadyFlag=0;
    }
   }
 }

/* [] END OF FILE */
