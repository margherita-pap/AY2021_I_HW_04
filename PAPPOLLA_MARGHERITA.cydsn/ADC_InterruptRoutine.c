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
uint8_t flag;

CY_ISR(Custom_ISR_ADC){
   if(SendByteFlag){
     TimerADC_ReadStatusRegister();
        AMux_Select(0);
        value_digit_photoR = ADC_DelSig_Read32();
    if(value_digit_photoR<0)
        value_digit_photoR=0;
    if(value_digit_photoR>65535)
        value_digit_photoR=65535;
        value_mV_photoR= ADC_DelSig_CountsTo_mVolts(value_digit_photoR);
        sprintf(DataBuffer_photoR,"Sample: %ld mV \r\n", value_mV_photoR);
        if(value_mV_photoR>=2500){
            PWM_LED_WriteCompare(0);
        }
        else{
            PWM_LED_WriteCompare(255);
            flag=1;
            AMux_Select(1);
            value_digit_potentiometer=ADC_DelSig_Read32();
        if(value_digit_potentiometer<0)
                value_digit_potentiometer=0;
        if(value_digit_potentiometer>65535)
                value_digit_potentiometer=65535;
        uint8_t settaggio_PWM;
        settaggio_PWM= (value_digit_potentiometer*255)/65535;
        PWM_LED_WriteCompare(settaggio_PWM);
        sprintf(DataBuffer_potentiometer,"Sample: %ld \r\n", value_digit_potentiometer);
        flag=1;
           
        }
    
        PacketReadyFlag=1;
    }
}
        
        


/* [] END OF FILE */
