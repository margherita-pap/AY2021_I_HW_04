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
#include "ADC_InterruptRoutine.h"
#include "UART_InterruptRoutine.h"

int32 value_digit_photoR;
int32 value_mV_photoR;

CY_ISR(Custom_ISR_ADC){
   if(SendByteFlag){
    TimerADC_ReadStatusRegister();
    value_digit_photoR = ADC_DelSig_Read32();
    if(value_digit_photoR<0)
        value_digit_photoR=0;
    if(value_digit_photoR>65535)
        value_digit_photoR=65535;
        value_mV_photoR= ADC_DelSig_CountsTo_mVolts(value_digit_photoR);
        sprintf(DataBuffer,"Sample: %ld mV \r\n", value_mV_photoR);
        PacketReadyFlag=1;
    }
}
        
        


/* [] END OF FILE */
