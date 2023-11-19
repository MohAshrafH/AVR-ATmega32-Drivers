/*
 * File: SEV_SEG_interface.h
 *
 * Description:
 *     This file is the interface for the Seven Segment Display (SEV_SEG) module designed for AVR ATmega32 microcontrollers.
 *     It provides function prototypes to initialize the display, display digits and numbers, and disable the display.
 *     The module is compatible with a 4-digit 7-segment display using Binary Coded Decimal (BCD) inputs and multiplexed common pin control.
 *
 * Author: [Your Name]
 * Date: [Creation Date]
 */

#ifndef SEV_SEG_INTERFACE_H_
#define SEV_SEG_INTERFACE_H_

/* Function: SEV_SEG_voidInitialize
 *
 * Brief:
 *   Initializes the 7-segment display control pins.
 *
 * Description:
 *   This function configures the BCD data pins and common pins as outputs. It prepares the 7-segment display
 *   for displaying digits by setting the necessary pins as outputs.
 *
 * Parameters:
 *   void - This function does not take any parameters.
 *
 * Returns:
 *   void - This function does not return a value.
 */
void SEV_SEG_voidInitialize(void);

/* Function: SEV_SEG_voidDisplayDigit
 *
 * Brief:
 *   Displays a single digit on a specific position of the 7-segment display.
 *
 * Description:
 *   This function displays a numeric digit on one of the four positions of the 7-segment display.
 *   The display position and the digit to display are specified as parameters.
 *
 * Parameters:
 *   digit - The display position to activate (ranging from 1 to 4).
 *   number - The numeric digit to display (ranging from 0 to 9).
 *
 * Returns:
 *   void - This function does not return a value.
 */
void SEV_SEG_voidDisplayDigit(u8 digit, u8 number);

/* Function: SEV_SEG_voidDisplayNumber
 *
 * Brief:
 *   Displays a multi-digit number on the 7-segment display.
 *
 * Description:
 *   This function displays a number across all four digits of the 7-segment display.
 *   It handles numbers up to four digits and ensures that each digit is displayed correctly.
 *
 * Parameters:
 *   number - The number to be displayed (ranging from 0 to 9999).
 *
 * Returns:
 *   void - This function does not return a value.
 */
void SEV_SEG_voidDisplayNumber(u16 number);

/* Function: SEV_SEG_voidDisableDisplay
 *
 * Brief:
 *   Disables all digits of the 7-segment display.
 *
 * Description:
 *   This function turns off all digits of the 7-segment display. It's useful for clearing the display or preparing for a new display cycle.
 *
 * Parameters:
 *   void - This function does not take any parameters.
 *
 * Returns:
 *   void - This function does not return a value.
 */
void SEV_SEG_voidDisableDisplay(void);

#endif /* SEV_SEG_INTERFACE_H_ */
