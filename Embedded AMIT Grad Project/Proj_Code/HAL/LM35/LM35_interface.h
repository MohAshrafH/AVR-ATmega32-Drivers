/*
 * File: LM35_interface.h
 *
 * Description:
 *     Interface header file for the LM35 temperature sensor module.
 *     This file provides the function prototypes for interfacing with the LM35 temperature sensor.
 *     The LM35 sensor is used to measure temperature, and its data is read through an ADC channel
 *     on the AVR ATmega32 microcontroller.
 *
 * Author: [Your Name]
 * Date: [Date of Creation or Modification]
 */

#ifndef HAL_LM35_LM35_INTERFACE_H_
#define HAL_LM35_LM35_INTERFACE_H_

/*
 * Function: LM35_voidInit
 * Description:
 *     Initializes the LM35 temperature sensor module.
 *     This function prepares the sensor for temperature reading by initializing the ADC channel
 *     connected to the LM35 sensor. It sets up the necessary configurations for accurate data acquisition.
 *
 * Parameters:
 *     void - No parameters.
 *
 * Returns:
 *     void - This function does not return a value.
 */
void LM35_voidInit(void);

/*
 * Function: LM35_f32GetTemperature
 * Description:
 *     Retrieves the current temperature reading from the LM35 sensor.
 *     This function reads the analog output of the LM35 sensor, converts it into a digital value,
 *     and then calculates the corresponding temperature in Celsius.
 *
 * Parameters:
 *     void - No parameters.
 *
 * Returns:
 *     float - The measured temperature in Celsius.
 */
float LM35_f32GetTemperature(void);

#endif /* HAL_LM35_LM35_INTERFACE_H_ */
