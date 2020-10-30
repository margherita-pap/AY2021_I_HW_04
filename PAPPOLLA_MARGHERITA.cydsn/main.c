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

void SystemStart(void);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    SystemStart(); // Start all the components of the system
    
    //Start the execution of interrupt associated to UART component
    isr_UART_Rx_StartEx(Custom_ISR_RX);
    //Start the execution of interrupt associated to Timer component 
    isr_ADC_StartEx(Custom_ISR_ADC);
    //Inizialization of variable
    SendByteFlag=0;
    PacketReadyFlag=0;
    Flag_LED_on=0;
    //The packet has a header (A0) and a tail (C0)
    DataBuffer[0]=0xA0;
    DataBuffer[TRANSMIT_BUFFER_SIZE-1]=0xC0;
    
    for(;;)
    { 
        if(PacketReadyFlag==1){
            if(Flag_LED_off==1){
                
            /* If LED is off i send like value of potentiometer 0
                because the value of potentiometer is related to light
                intensity of LED, so when LED is off the light brigthness is zero.*/
                
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

void SystemStart(void){
    UART_Start(); //Start UART component
    PWM_LED_Start(); // Start LED driver
    AMux_Start();   // Start MUX component
    ADC_DelSig_Start(); //Start ADC DeltaSigma
    ADC_DelSig_StartConvert(); // Enable ADC to start converting
    
}
/* [] END OF FILE */
