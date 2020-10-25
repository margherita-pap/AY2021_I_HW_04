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
    #include "ADC_DelSig.h"
    #include "AMux.h"
    #include "TimerADC.h"
    #define TRANSMIT_BUFFER_SIZE 16
    CY_ISR_PROTO(Custom_ISR_ADC);
    char DataBuffer[TRANSMIT_BUFFER_SIZE];
    volatile uint8 PacketReadyFlag;
#endif

/* [] END OF FILE */
