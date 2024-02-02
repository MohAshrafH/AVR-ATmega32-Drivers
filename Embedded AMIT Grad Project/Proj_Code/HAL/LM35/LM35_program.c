/*
 * File: LM35_program.c
 *
 * Description:
 *     Implementation of the LM35 temperature sensor module for AVR ATmega32.
 *     This file provides the functionality to initialize and read temperature
 *     data from the LM35 sensor through the ADC channel. It converts the ADC
 *     readings to a temperature value in degrees Celsius.
 *
 * Author: Elara
 * Date: November 10, 2023
 */

/* Standard Library Includes */
#include "../../UTIL_LIB/STD_TYPES.h"  // Standard types definitions
#include "../../UTIL_LIB/BIT_MATH.h"   // Bit manipulation operations

/* Microcontroller Abstraction Layer Includes */
#include "../../MCAL/DIO/DIO_interface.h"  // DIO interface functions
#include "../../MCAL/DIO/DIO_private.h"    // DIO private registers and macros
#include "../../MCAL/ADC/ADC_config.h"     // ADC configuration settings
#include "../../MCAL/ADC/ADC_interface.h"  // ADC interface functions
#include "../../MCAL/ADC/ADC_private.h"    // ADC private registers and macros

/* LM35 Module Specific Includes */
#include "./LM35_config.h"     // LM35 configuration settings
#include "./LM35_interface.h"  // LM35 interface functions
#include "./LM35_private.h"    // LM35 private macros and definitions

/* Define ADC Channel Connected to LM35 Sensor */
#define LM35_ADC_CHANNEL 1  // ADC channel 1 connected to LM35

/*
 * Function: LM35_voidInit
 * Description: Initializes the LM35 temperature sensor module. It configures
 *              the ADC channel connected to LM35 as an input and initializes
 *              the ADC module for temperature reading.
 * Parameters: None
 * Return: None
 */
void LM35_voidInit(void) {
    // Configure the ADC channel connected to LM35 as input
    DIO_setPinDirection(DIO_PORTA, LM35_ADC_CHANNEL, DIO_PIN_INPUT);

    // Initialize the ADC module
    ADC_voidInit();
}

/*
 * Function: LM35_f32GetTemperature
 * Description: Reads and calculates the temperature from the LM35 sensor.
 *              It first reads the analog value from the ADC channel connected
 *              to LM35, converts this value to a voltage level, and then converts
 *              this voltage level to a temperature in Celsius.
 * Parameters: None
 * Return: float - The calculated temperature in Celsius.
 */
float LM35_f32GetTemperature(void) {
    // Read ADC value from the channel connected to LM35
    u16 Local_u16ADCValue = ADC_u16Read(LM35_ADC_CHANNEL);

    // Convert ADC value to voltage (in millivolts)
    float Local_f32Voltage = (Local_u16ADCValue * 5000.0) / 1024.0;

    // Convert voltage to temperature (Celsius)
    // LM35 sensor output: 10mV per degree Celsius
    float Local_f32Temperature = Local_f32Voltage / 10.0;

    // Return the calculated temperature
    return Local_f32Temperature;
}
