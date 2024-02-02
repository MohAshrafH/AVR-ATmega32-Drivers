/*
 * File: ADC_config.h
 *
 * Description:
 *     Configuration header file for the Analog-to-Digital Converter (ADC) module
 *     in the AVR ATmega32 microcontroller. This file provides configurable
 *     settings for the ADC module, allowing for adjustments in reference voltage
 *     and result data alignment. The settings defined here can be modified to suit
 *     the needs of different applications and hardware setups.
 *
 *     The configuration options include setting the ADC's reference voltage
 *     (Vref) and adjusting the alignment of the conversion result (left or right).
 *
 * Usage:
 *     - ADC_VREF: Determines the reference voltage source for ADC conversions.
 *       Options include internal sources or AVCC with an external capacitor.
 *     - ADC_ADJUST: Configures the alignment of the ADC conversion result in
 *       the ADC Data Register. It can be set to either left or right adjusted.
 *
 * Notes:
 *     - Changes to this file may affect ADC behavior and should be made with
 *       an understanding of the ATmega32 ADC hardware.
 *     - Ensure that the selected reference voltage matches the application's
 *       requirements and the hardware design.
 *
 * Author: (Your Name)
 * Date: (Date of Creation or Modification)
 */

#ifndef MCAL_ADC_ADC_CONFIG_H_
#define MCAL_ADC_ADC_CONFIG_H_

/* Set the reference voltage (Vref) for the ADC */
/* Options: ADC_VREF_AVCC, ADC_VREF_INTERNAL, etc. */
#define ADC_VREF ADC_VREF_AVCC

/* Adjust the result left (1) or right (0) */
/* 0 for right adjusted, 1 for left adjusted result */
#define ADC_ADJUST ADC_ADJUST_RIGHT

#endif /* MCAL_ADC_ADC_CONFIG_H_ */
