/*
 * File: SEV_SEG_private.h
 *
 * Description:
 *     Private header file for the Seven Segment Display (SEV_SEG) module, tailored for the AVR ATmega32 microcontroller.
 *     This file defines the pin mappings and configurations specific to the hardware setup of the seven-segment display.
 *     It includes definitions for the Binary Coded Decimal (BCD) pins connected to a BCD decoder and the common pins
 *     for the individual seven-segment displays. These definitions are crucial for the internal workings of the SEV_SEG
 *     module and should not be accessed directly by other modules or applications.
 *
 * Author: [Your Name]
 * Date: [Specify Date Here]
 */

#ifndef SEV_SEG_PRIVATE_H_
#define SEV_SEG_PRIVATE_H_

/* Define the BCD pins connected to the BCD decoder. */
/* These pins are responsible for setting the individual segments of the display. */
#define SEV_SEG_BCD_PIN_A      DIO_PIN0  // BCD Pin A connected to PB0
#define SEV_SEG_BCD_PIN_B      DIO_PIN1  // BCD Pin B connected to PB1
#define SEV_SEG_BCD_PIN_C      DIO_PIN2  // BCD Pin C connected to PB2
#define SEV_SEG_BCD_PIN_D      DIO_PIN4  // BCD Pin D connected to PB4

/* Define the Common pins for the 7-segment displays. */
/* These pins are used to control which digit is active in a multi-digit display setup. */
#define SEV_SEG_COM_PIN_1      DIO_PIN3  // Common Pin 1 connected to PA3
#define SEV_SEG_COM_PIN_2      DIO_PIN2  // Common Pin 2 connected to PA2
#define SEV_SEG_COM_PIN_3      DIO_PIN5  // Common Pin 3 connected to PB5
#define SEV_SEG_COM_PIN_4      DIO_PIN6  // Common Pin 4 connected to PB6

#endif /* SEV_SEG_PRIVATE_H_ */
