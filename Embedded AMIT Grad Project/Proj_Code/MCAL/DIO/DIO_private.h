/*
 * File: DIO_private.h
 *
 * Description:
 *     Private header file for the Digital Input/Output (DIO) module.
 *     This file defines the memory addresses of the data direction, output,
 *     and input registers for AVR ATmega32 microcontroller ports. These
 *     definitions are intended for internal use within the DIO module and
 *     should not be accessed directly by other modules or applications.
 *
 * Author:
 * Date: (Date of Creation or Modification)
 */

#ifndef DIO_PRIVATE_K_
#define DIO_PRIVATE_K_

/* DIO Registers: Memory Mapped Registers for Port Configuration and Control */

/*
 * Data Direction Registers (DDRx):
 * These registers determine the direction (input/output) of each pin in the corresponding port.
 * 1: Output, 0: Input
 */

/* Data Direction Register for Port A */
#define DDRA           (*(volatile u8*)0x3A)

/* Data Direction Register for Port B */
#define DDRB           (*(volatile u8*)0x37)

/* Data Direction Register for Port C */
#define DDRC           (*(volatile u8*)0x34)

/* Data Direction Register for Port D */
#define DDRD           (*(volatile u8*)0x31)

/*
 * Output Data Registers (PORTx):
 * These registers hold the output value of each pin in the corresponding port.
 * Writing a 1 turns on the output driver (high level), and writing a 0 turns it off (low level).
 */

/* Output Data Register for Port A */
#define PORTA          (*(volatile u8*)0x3B)

/* Output Data Register for Port B */
#define PORTB          (*(volatile u8*)0x38)

/* Output Data Register for Port C */
#define PORTC          (*(volatile u8*)0x35)

/* Output Data Register for Port D */
#define PORTD          (*(volatile u8*)0x32)

/*
 * Input Data Registers (PINx):
 * These registers represent the current logic level on each pin of the corresponding port.
 * Reading these registers gives the current input value (high/low) of the port pins.
 */

/* Input Data Register for Port A */
#define PINA           (*(volatile u8*)0x39)

/* Input Data Register for Port B */
#define PINB           (*(volatile u8*)0x36)

/* Input Data Register for Port C */
#define PINC           (*(volatile u8*)0x33)

/* Input Data Register for Port D */
#define PIND           (*(volatile u8*)0x30)

#endif /* DIO_PRIVATE_K_ */
