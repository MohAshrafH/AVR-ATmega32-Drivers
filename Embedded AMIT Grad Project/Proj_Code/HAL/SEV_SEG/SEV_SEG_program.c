/*
 * File: SEV_SEG_program.c
 *
 * Description:
 *     Implementation of the Seven Segment Display (SEV_SEG) module for the AVR ATmega32 microcontroller.
 *     This file provides functions to initialize the seven-segment display, display digits and numbers,
 *     and control the display segments. It utilizes the Digital Input/Output (DIO) module to interface
 *     with the hardware and manage the BCD (Binary Coded Decimal) pins and common anode/cathode pins.
 *
 * Author:
 * Created on:
 */

/* Standard Library for Delay Functions */
#include <util/delay.h>

/* UTIL_LIB */
#include "../../UTIL_LIB/STD_TYPES.h"  // Includes standard data types used across the application
#include "../../UTIL_LIB/BIT_MATH.h"   // Includes bit manipulation functions for direct hardware access

/* MCAL */
#include "../../MCAL/DIO/DIO_interface.h"  // DIO interface for controlling digital input/output
#include "../../MCAL/DIO/DIO_private.h"    // Private definitions and macros for DIO module (internal use)

/* SEV_SEG Module Configuration */
#include "../SEV_SEG/SEV_SEG_config.h"     // Configuration settings for the Seven Segment Display
#include "../SEV_SEG/SEV_SEG_interface.h"  // Interface definitions for the Seven Segment Display
#include "../SEV_SEG/SEV_SEG_private.h"    // Private definitions and macros for SEV_SEG module (internal use)

/*
 * Function: SEV_SEG_voidInitialize
 * Description:
 *     Initializes the seven-segment display by setting the BCD pins and common pins as outputs.
 *     This function should be called at the start of the program to prepare the display for use.
 */
void SEV_SEG_voidInitialize(void) {
    /* Set BCD pins as output */
    DIO_setPinDirection(DIO_PORTB, SEV_SEG_BCD_PIN_A, DIO_PIN_OUTPUT);
    DIO_setPinDirection(DIO_PORTB, SEV_SEG_BCD_PIN_B, DIO_PIN_OUTPUT);
    DIO_setPinDirection(DIO_PORTB, SEV_SEG_BCD_PIN_C, DIO_PIN_OUTPUT);
    DIO_setPinDirection(DIO_PORTB, SEV_SEG_BCD_PIN_D, DIO_PIN_OUTPUT);

    /* Set common pins as output */
    DIO_setPinDirection(DIO_PORTA, SEV_SEG_COM_PIN_1, DIO_PIN_OUTPUT);
    DIO_setPinDirection(DIO_PORTA, SEV_SEG_COM_PIN_2, DIO_PIN_OUTPUT);
    DIO_setPinDirection(DIO_PORTB, SEV_SEG_COM_PIN_3, DIO_PIN_OUTPUT);
    DIO_setPinDirection(DIO_PORTB, SEV_SEG_COM_PIN_4, DIO_PIN_OUTPUT);
}

/*
 * Function: SEV_SEG_voidDisplayDigit
 * Description:
 *     Displays a single digit on the specified display segment.
 *     This function controls which digit is displayed and on which segment.
 *
 * Parameters:
 *     - digit: The segment number (1-4) to display the digit on.
 *     - number: The digit (0-9) to display.
 */
void SEV_SEG_voidDisplayDigit(u8 digit, u8 number) {
    // Ensure the number is valid (between 0 and 9)
    if (number > 9) {
        return; // Invalid number, do nothing
    }

    // Set the BCD pins based on the number
    DIO_setPinValue(DIO_PORTB, SEV_SEG_BCD_PIN_A, GET_BIT(number, 0));
    DIO_setPinValue(DIO_PORTB, SEV_SEG_BCD_PIN_B, GET_BIT(number, 1));
    DIO_setPinValue(DIO_PORTB, SEV_SEG_BCD_PIN_C, GET_BIT(number, 2));
    DIO_setPinValue(DIO_PORTB, SEV_SEG_BCD_PIN_D, GET_BIT(number, 3));

    // Activate the specific digit
    switch (digit) {
        case 1: DIO_setPinValue(DIO_PORTA, SEV_SEG_COM_PIN_1, DIO_PIN_LOW); break;
        case 2: DIO_setPinValue(DIO_PORTA, SEV_SEG_COM_PIN_2, DIO_PIN_LOW); break;
        case 3: DIO_setPinValue(DIO_PORTB, SEV_SEG_COM_PIN_3, DIO_PIN_LOW); break;
        case 4: DIO_setPinValue(DIO_PORTB, SEV_SEG_COM_PIN_4, DIO_PIN_LOW); break;
        default: break; // Invalid digit
    }

    _delay_ms(1); // Short delay for display stability

    // Disable all digits
    SEV_SEG_voidDisableDisplay();
}

/*
 * Function: SEV_SEG_voidDisplayNumber
 * Description:
 *     Displays a multi-digit number across the seven-segment display.
 *     This function decomposes the number into individual digits and displays them sequentially.
 *
 * Parameters:
 *     - number: The number (up to 4 digits) to display.
 */
void SEV_SEG_voidDisplayNumber(u16 number) {
    if (number > 9999) {
        return; // Number is too large to display
    }

    // Decompose the number into individual digits
    u8 digit1 = number % 10;
    u8 digit2 = (number / 10) % 10;
    u8 digit3 = (number / 100) % 10;
    u8 digit4 = (number / 1000) % 10;

    // Multiplexing loop for display refresh
    for (int i = 0; i < 50; i++) {
        SEV_SEG_voidDisplayDigit(4, digit4);
        _delay_ms(2);
        SEV_SEG_voidDisplayDigit(3, digit3);
        _delay_ms(2);
        SEV_SEG_voidDisplayDigit(2, digit2);
        _delay_ms(2);
        SEV_SEG_voidDisplayDigit(1, digit1);
        _delay_ms(2);
    }
}

/*
 * Function: SEV_SEG_voidDisableDisplay
 * Description:
 *     Disables all display segments of the seven-segment display.
 *     This function turns off all segments to ensure no digits are displayed.
 */
void SEV_SEG_voidDisableDisplay(void) {
    /* Disable all displays */
    DIO_setPinValue(DIO_PORTA, SEV_SEG_COM_PIN_1, DIO_PIN_HIGH);
    DIO_setPinValue(DIO_PORTA, SEV_SEG_COM_PIN_2, DIO_PIN_HIGH);
    DIO_setPinValue(DIO_PORTB, SEV_SEG_COM_PIN_3, DIO_PIN_HIGH);
    DIO_setPinValue(DIO_PORTB, SEV_SEG_COM_PIN_4, DIO_PIN_HIGH);
}
