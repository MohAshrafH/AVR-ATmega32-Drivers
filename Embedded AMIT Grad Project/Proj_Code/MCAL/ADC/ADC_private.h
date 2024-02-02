/*
 * File: ADC_private.h
 *
 * Description:
 *     This file contains private definitions and macros for the Analog-to-Digital
 *     Converter (ADC) module of the AVR ATmega32 microcontroller. It defines
 *     the memory-mapped registers related to the ADC, as well as key constants
 *     used internally within the ADC module.
 *
 *     These definitions are intended for internal use within the ADC driver and
 *     should not be accessed directly by other modules or applications. They
 *     provide low-level access to ADC hardware registers and their configurations.
 *
 * Author: (Your Name)
 * Date: (Date of Creation or Modification)
 */

#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

/* ADC Control and Status Register A (ADCSRA) Address */
#define ADCSRA  (*(volatile u8*)0x26)

/* ADC Multiplexer Selection Register (ADMUX) Address */
#define ADMUX   (*(volatile u8*)0x27)

/* ADC Data Register High Byte (ADCH) Address */
#define ADCH    (*(volatile u8*)0x25)

/* ADC Data Register Low Byte (ADCL) Address */
#define ADCL    (*(volatile u8*)0x24)

/* ADC Right Adjust Result Configuration */
#define ADC_ADJUST_RIGHT 0

/* ADC Voltage Reference Selection for AVCC with external capacitor at AREF pin */
#define ADC_VREF_AVCC    0b01000000

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
