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
#ifndef __ADC_INTERRUPT_ROUTINE_H_
    #define __ADC_INTERRUPT_ROUTINE_H_
    #include "cytypes.h"
    #include "stdio.h"
    #include "project.h"
    #define BYTE_TO_SEND 4
    #define TRANSMIT_BUFFER_SIZE 1+BYTE_TO_SEND +1
    CY_ISR_PROTO(Custom_ISR_ADC);
    uint8_t DataBuffer[TRANSMIT_BUFFER_SIZE];
    int32 ReadDataConverted(int32 variable);
    //This varibale goes high if we read a value from ADC
    volatile uint8 PacketReadyFlag;
    // This value goes high if value of photoresistor is 
    //abouve the threshold
    volatile uint8_t Flag_LED_on;
    //This varibale goes high if value of photoresistor is 
    //below the threshold
    volatile uint8_t Flag_LED_off;
#endif

#define PERIOD_PWM 255
#define ADC_MAX_OUTPUT 65535
#define CH_PHOTORESISTOR 0
#define CH_POTENTIOMETER 1
/* [] END OF FILE */
