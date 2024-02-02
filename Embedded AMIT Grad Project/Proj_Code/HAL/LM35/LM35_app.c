/*
 * LM35_test.c
 *
 *  Created on: Nov 10, 2023
 *      Author: elara
 */

#include <util/delay.h>
#include "../../UTIL_LIB/STD_TYPES.h"
#include "../../UTIL_LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_private.h"
#include "../../MCAL/ADC/ADC_config.h"
#include "../../MCAL/ADC/ADC_interface.h"
#include "../../MCAL/ADC/ADC_private.h"
#include "./LM35_config.h"
#include "./LM35_interface.h"
#include "./LM35_private.h"
#include "../../HAL/LCD/LCD_interface.h"
#include "../../HAL/LCD/LCD_private.h"
#include "../../HAL/LCD/LCD_config.h"
#include "../SEV_SEG/SEV_SEG_config.h"
#include "../SEV_SEG/SEV_SEG_interface.h"
#include "../SEV_SEG/SEV_SEG_private.h"

int main(void)
{
    /* Initialize modules */
    LM35_voidInit();          // Initialize LM35
    SEV_SEG_voidInitialize(); // Initialize 7-segment display
    /*	4 bit-mode initialization	*/
   // LCD_voidInit();

    f32 temp;
    u16 displayValue;

    while (1) {
        // Read temperature from LM35
        temp = LM35_f32GetTemperature();

        // Convert the temperature to a 4-digit number for display
        // For example, 26.4 becomes 0264, 27.1 becomes 0271
        displayValue = (u16)(temp * 10); // Multiply by 10 to shift decimal one place to the right

        // Display this value on the 7-segment display
        SEV_SEG_voidDisplayNumber(displayValue);


        // Refresh reading every 100ms
        _delay_ms(1000);
    }

    return 0;
}
