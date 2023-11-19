/*
 * File: LCD_APP.c
 *
 * Description:
 *     Application file for testing the LCD driver functions on an AVR ATmega32 microcontroller.
 *     This file contains various test scenarios to verify the functionality of each operation
 *     provided by the LCD driver. It includes tests for displaying strings, numbers, custom characters,
 *     and manipulating the display properties such as cursor position and display shift.
 *
 * Author: elara
 * Date: Jul 31, 2023
 */

#include <util/delay.h>
#include "../../UTIL_LIB/STD_TYPES.h"
#include "../../UTIL_LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../LCD/LCD_interface.h"

// Define F_CPU for delay calculations (if not defined globally)
#define F_CPU 16000000UL

// Custom character patterns for testing
u8 LCD_Char_Pattern1[] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

int main(void) {
    // Initialize the LCD in 4-bit mode
    LCD_voidInit();

    // Test strings for display
    u8 strName[15] = "Mohammad";

    // Custom character: a standing man
    u8 Local_Au8StandingMan[8] = {
        0b01110,  // Top of the head
        0b01110,  // Bottom of the head
        0b11111,  // Arms and upper torso
        0b00100,  // Mid torso
        0b00100,  // Lower torso
        0b01010,  // Upper legs
        0b01010,  // Lower legs
        0b01010   // Feet
    };

    // Test Case 1: Display string "Mohammad" on LCD
    LCD_voidWriteString(strName);
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 2: Display and shift custom character (standing man)
    LCD_voidCreateCharacter(Local_Au8StandingMan, 0);
    LCD_voidSendChar(0); // Display the custom character
    _delay_ms(1000);
    LCD_voidShift(1, 1, 20); // Shift the display
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 3: Display numbers
    LCD_voidWriteNumber(12345);
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 4: Display a binary number
    LCD_voidWriteBinary(0b10101010);
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 5: Display hexadecimal numbers
    LCD_voidWriteHex(0xAB);
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);


    // Test Case 6: Display a 4-digit number
    LCD_voidWriteNumber4Digits(2023);
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 7: Display binary number in short format (significant bits only)
    LCD_voidWriteBinaryShort(0b1010);
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 8: GoTo Function - Position cursor and display text
    LCD_voidGoTo(LCD_LINE_ONE, 5);
    LCD_voidWriteString("Hello");
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 9: Display a floating-point number (requires custom function)
    f32 floatNumber = 123.456f;
    LCD_voidDisplayFloat(floatNumber);
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 10: Create and display a custom character
    LCD_voidCreateCharacter(Local_Au8StandingMan, 1); // Store in CGRAM location 1
    LCD_voidGoTo(LCD_LINE_TWO, 0);
    LCD_voidSendChar(1); // Display custom character from CGRAM location 1
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 11: Display Hexadecimal number
    LCD_voidWriteHex(0xDE);
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 12: Shift Display Left and Right
    LCD_voidWriteString("Shifting");
    LCD_voidShift(1, 0, 5); // Shift left
    _delay_ms(1000);
    LCD_voidShift(1, 1, 5); // Shift right
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    // Test Case 13: Clear a part of the display
    LCD_voidWriteString("Clearing a part");
    _delay_ms(1000);
    LCD_voidGoToClear(LCD_LINE_ONE, 0, 8); // Clear first 8 cells of line 1
    _delay_ms(1000);
    LCD_voidClear();
    _delay_ms(500);

    /* More test cases can be added here as needed */

//    while(1) {
//        // Continuous test loop or interactive testing
//    }
}
