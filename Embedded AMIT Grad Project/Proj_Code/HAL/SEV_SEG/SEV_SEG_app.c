///*
// * File: SEV_SEG_app.c
// *
// * Description:
// *     Application file for testing the Seven Segment Display (SEV_SEG) module on the AVR ATmega32 microcontroller.
// *     This file includes several test scenarios to validate the functionality of the SEV_SEG module,
// *     ranging from displaying individual digits to showing multi-digit numbers.
// *
// * Author:
// * Date:
// */
//
///* AVR Library for Delay Functions */
//#include <util/delay.h>
//
///* Utility Libraries */
//#include "../../UTIL_LIB/STD_TYPES.h"  // Standard data types definitions
//#include "../../UTIL_LIB/BIT_MATH.h"   // Bit-level operations and manipulations
//
///* Microcontroller Abstraction Layer (MCAL) */
//#include "../../MCAL/DIO/DIO_interface.h"  // Interface for Digital Input/Output (DIO) operations
//#include "../../MCAL/DIO/DIO_private.h"    // Internal definitions and macros for DIO operations
//
///* Seven Segment Display Module Headers */
//#include "./SEV_SEG_interface.h"  // Interface for the Seven Segment Display functionalities
//#include "./SEV_SEG_private.h"    // Internal configurations and definitions for the Seven Segment Display
//#include "./SEV_SEG_config.h"     // Configuration settings for the Seven Segment Display module
//
//int main(void) {
//    // Initialize the 7-segment display
//    SEV_SEG_voidInitialize();
//
//    // Scenario 1: Test if all digit displays work
//    for (u8 digit = 1; digit <= 4; digit++) {
//        // Display '8' on each digit
//        SEV_SEG_voidDisplayDigit(digit, 8);
//        _delay_ms(1000); // 1-second delay
//    }
//
//    // Scenario 2: Test displaying all numbers (0-9)
//    for (u8 number = 0; number <= 9; number++) {
//        // Display each number on the first digit
//        SEV_SEG_voidDisplayDigit(1, number);
//        _delay_ms(700); // 0.5-second delay
//    }
//
//    // Scenario 3: Test displaying a whole multi-digit number
//    SEV_SEG_voidDisplayNumber(1234); // Display '1234'
//    _delay_ms(2000); // 2-second delay
//
//    // Scenario 4: Test changing numbers individually on each digit
//    for (u8 digit = 1; digit <= 4; digit++) {
//        for (u8 number = 0; number <= 9; number++) {
//            // Change number on specific digit
//            SEV_SEG_voidDisplayDigit(digit, number);
//            _delay_ms(700); // 0.3-second delay
//        }
//    }
//
//    // Scenario 5: Test with one digit off but others functioning
//    SEV_SEG_voidDisplayDigit(1, 1); // First digit '1'
//    SEV_SEG_voidDisplayDigit(2, 2); // Second digit '2'
//    SEV_SEG_voidDisplayDigit(4, 4); // Fourth digit '4'
//    // Third digit is intentionally left off
//    _delay_ms(2000);
//
//    // Additional scenario: Test rapid number change on a single digit
//    for (u8 number = 0; number <= 9; number++) {
//        // Rapid number change on the second digit
//        SEV_SEG_voidDisplayDigit(2, number);
//        _delay_ms(700); // 0.2-second delay
//    }
//
//    return 0;
//}
