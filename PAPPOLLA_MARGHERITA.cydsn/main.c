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
    //Inizialization of variables and flags
    SendByteFlag=0;
    PacketReadyFlag=0;
    Flag_LED_on=0;
    value_digit_photoR=0;
    value_digit_potentiometer=0;
    //The packet to send has a header (A0) and a tail (C0)
    DataBuffer[0]=0xA0;
    DataBuffer[TRANSMIT_BUFFER_SIZE-1]=0xC0;
    
    for(;;)
    {  /*We do something in the for only if the ADC is sampling and we have some
        *data to send
       */
        if(PacketReadyFlag==1){
            if(Flag_LED_off==1){
                
            /*If LED is off i send like value of potentiometer 0
             *because the value of potentiometer is related to light
             *intensity of LED, so when LED is off the light brigthness is zero.
            */
                DataToSend(DataBuffer, value_digit_photoR, 0);
                UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE);
                Flag_LED_off=0;
            }
        
            if(Flag_LED_on==1){
            /*if LED is on i have also the value of the potentiometer 
             *sample by the ADC to send
            */    
            DataToSend(DataBuffer,value_digit_photoR,value_digit_potentiometer);
            UART_PutArray(DataBuffer,TRANSMIT_BUFFER_SIZE);
            Flag_LED_on=0;
            }  
        PacketReadyFlag=0;
    }
   }
 }

void DataToSend(uint8_t* DataBuffer, int32 value_digit_photoR, int32 value_digit_pot){
    /*My ADC is sampling at 16 bit, eventough my variable is at 32bit,
     *so i can send the value of he photoresistor using 2 bytes
    */
    DataBuffer[1]=value_digit_photoR>>8; //MSB_photoR
    DataBuffer[2]=value_digit_photoR&0xFF; //LSB_photoR
    //The value in digit is in 16 bits so i can send it through 2 bytes
    DataBuffer[3]=value_digit_pot>>8; //MSB_pot
    DataBuffer[4]=value_digit_pot&0xFF; //LSB_pot
}

void SystemStart(void){
    UART_Start(); //Start UART component
    PWM_LED_Start(); // Start LED driver
    AMux_Start();   // Start MUX component
    ADC_DelSig_Start(); //Start ADC DeltaSigma
    ADC_DelSig_StartConvert(); // Enable ADC to start converting
    
}
/* [] END OF FILE */
