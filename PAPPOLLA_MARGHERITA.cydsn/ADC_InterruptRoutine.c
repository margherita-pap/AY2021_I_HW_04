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
#include "ADC_InterruptRoutine.h"
#include "UART_InterruptRoutine.h"

int32 value_digit_photoR;
int32 value_mV_photoR;
int32 value_digit_potentiometer;

int32 ReadDataConverted(int32 variable){
    variable=ADC_DelSig_Read32();
    if(variable<0)
        variable=0;
    if(variable>ADC_MAX_OUTPUT)
        variable= ADC_MAX_OUTPUT;
    return variable;
 }    

CY_ISR(Custom_ISR_ADC){
    int32 variable=0;
   if(SendByteFlag){
        TimerADC_ReadStatusRegister();
        AMux_Select(CH_PHOTORESISTOR);
        
        value_digit_photoR=ReadDataConverted(variable);
        DataBuffer[1]=value_digit_photoR>>8;
        DataBuffer[2]=value_digit_photoR&0xFF;
        value_mV_photoR= ADC_DelSig_CountsTo_mVolts(value_digit_photoR);
        if(value_mV_photoR>=2500){
            PWM_LED_WriteCompare(0);
            Flag_LED_off=1;
        }
        else{
            PWM_LED_WriteCompare(PERIOD_PWM);
            AMux_Select(CH_POTENTIOMETER);
            value_digit_potentiometer=ReadDataConverted(variable);
            DataBuffer[3]=value_digit_potentiometer>>8;
            DataBuffer[4]=value_digit_potentiometer&0xFF;
            uint8_t settaggio_PWM;
            settaggio_PWM= (value_digit_potentiometer*255)/65535;
            PWM_LED_WriteCompare(settaggio_PWM);
     
            Flag_LED_on=1;
            }
    
        PacketReadyFlag=1;
    }
}


    
    
    
    
        
        


/* [] END OF FILE */
