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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Start();
    isr_UART_Rx_StartEx(Custom_ISR_RX);
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
