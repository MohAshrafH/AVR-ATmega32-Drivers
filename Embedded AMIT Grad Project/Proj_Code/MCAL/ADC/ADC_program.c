/*
 * File: ADC_program.c
 *
 * Description:
 *     Implementation file for the Analog-to-Digital Converter (ADC) module in the AVR ATmega32
 *     microcontroller. This file provides the functional implementations for the ADC driver,
 *     including initializing the ADC, configuring ADC settings, and reading analog values from
 *     ADC channels. The functions in this file interact directly with the AVR hardware registers
 *     to control the ADC functionalities.
 *
 * Author: [Your Name]
 * Date: [Specify Date Here]
 */

/* Standard Utility Libraries */
#include "../../UTIL_LIB/STD_TYPES.h"  // Standard types definitions
#include "../../UTIL_LIB/BIT_MATH.h"   // Bit manipulation operations

/* Microcontroller Abstraction Layer */
#include "../ADC/ADC_interface.h"      // ADC interface functions
#include "../ADC/ADC_private.h"        // ADC private registers and macros
#include "../ADC/ADC_config.h"         // ADC configuration settings

/*
 * Function: ADC_voidInit
 * Description:
 *     Initializes the ADC module with predefined settings from ADC_config.h.
 *     Configures reference voltage, result adjustment, ADC enable, and prescaler.
 *
 * Parameters:
 *     void - No parameters.
 *
 * Returns:
 *     void - This function does not return a value.
 */
void ADC_voidInit(void) {
    /* Set the reference voltage and adjust result */
    ADMUX = ADC_VREF | ADC_ADJUST;

    /* Enable ADC, set prescaler, and start conversion */
    ADCSRA = 0b10000111; // ADC Enable, Prescaler = 128 (Assuming 8MHz Clock -> 64 KHz ADC clock)
}

/*
 * Function: ADC_u16Read
 * Description:
 *     Reads an analog value from a specified ADC channel.
 *     Selects the channel, starts the conversion, waits for completion, and returns the result.
 *
 * Parameters:
 *     - Copy_u8Channel: The ADC channel number to read from (0 to 7).
 *
 * Returns:
 *     u16 - The 10-bit ADC conversion result.
 */
u16 ADC_u16Read(u8 Copy_u8Channel) {
    /* Select ADC channel and ensure it's within the first 8 channels */
    ADMUX = (ADMUX & 0xF8) | (Copy_u8Channel & 0x07); // Select ADC channel

    /* Start the conversion */
    SET_BIT(ADCSRA, 6); // Start conversion

    /* Wait for the conversion to finish */
    while (GET_BIT(ADCSRA, 4) == 0); // Wait for conversion to complete

    /* Clear the ADC Interrupt Flag */
    SET_BIT(ADCSRA, 4); // Clear the ADC interrupt flag

    /* Read and return the ADC value */
    return ADCL | (ADCH << 8); // Read the ADC value (low then high)
}
