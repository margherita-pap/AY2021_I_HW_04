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
    
    AMux_Start();
    ADC_DelSig_Start();
    isr_UART_Rx_StartEx(Custom_ISR_RX);
    isr_ADC_StartEx(Custom_ISR_ADC);
    PacketReadyFlag=0;
    ADC_DelSig_StartConvert();
    for(;;)
    { 
        if(PacketReadyFlag==1){
        UART_PutString(DataBuffer);
        PacketReadyFlag=0;
    }
   }
 }

/* [] END OF FILE */
