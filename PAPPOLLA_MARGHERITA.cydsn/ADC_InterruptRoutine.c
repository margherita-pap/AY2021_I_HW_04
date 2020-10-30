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
/*The interrupt is executed every 100ms if the Timer component is
 *started. But because the ADC has a conversion rate much faster than 100ms
 *in the same ISR i can sample both signals without risking of loosing some data
 */

#include "project.h"
#include "ADC_InterruptRoutine.h"
#include "UART_InterruptRoutine.h"


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
        
        /*I select first the MUX channel of the photoresistor 
         *to see if we are or not above threshold
        */
        AMux_Select(CH_PHOTORESISTOR);
        // I read the value in digit converted by the ADC Delta sigma
        value_digit_photoR=ReadDataConverted(variable);
        /*I set the threshold at 2.5V so in order to see that more clearly
         *I convert the value from digit to mV
        */
        value_mV_photoR= ADC_DelSig_CountsTo_mVolts(value_digit_photoR);
        if(value_mV_photoR>=THRESHOLD){
            //In this way the LED is turned off
            PWM_LED_WriteCompare(DUTY_CYCLE_ZERO);
            //I send high the flag that LED if off
            Flag_LED_off=1;
        }
        else{
            /*We are below threshold and i turn on the LED
             *by setting the DC=100%
            */
            PWM_LED_WriteCompare(PERIOD_PWM);
            /*If i am underthreshold i sample also the value of potenziometer,
             *in order to control the brightness of the LED
             *so i switch the channel of the MUX
            */
            AMux_Select(CH_POTENTIOMETER);
            //Save the value in digit sampled by the ADC Delta
            value_digit_potentiometer=ReadDataConverted(variable);
            /*In order to drive the LED brightness i choose a PWM with 8 bit
             *so i rescale the values of potentiometer that go from 0 to 65535
             *to the range of the values of PWM that in this case go from 0 to 255
            */
            uint8_t value_DC;
            value_DC= (value_digit_potentiometer*PERIOD_PWM)/ADC_MAX_OUTPUT;
            //I set the value of the DC according to the value of the potentiometer in 
            //that instant
            PWM_LED_WriteCompare(value_DC);
            //Set the flag that the LED is turned on high
            Flag_LED_on=1;
            }
        //I have all the values to send 
        PacketReadyFlag=1;
    }
}


    
    
    
    
        
        


/* [] END OF FILE */
