/*
 * File: LCD_program.c
 *
 * Description:
 *     This file contains the implementation of functions for interfacing with an LCD display
 *     using the AVR ATmega32 microcontroller. It provides functionality for initializing the
 *     LCD in 4-bit mode, writing characters and strings to the display, and controlling the
 *     display properties such as cursor position and display shift. The implementation is
 *     based on the HD44780 LCD controller, commonly used in alphanumeric LCDs. This driver
 *     supports various LCD operations including displaying numbers, strings, custom characters,
 *     and handling the LCD in 4-bit communication mode.
 *
 *     The functions in this file are designed to abstract the lower-level details of interfacing
 *     with the LCD, providing a simple and intuitive API for displaying data. This includes
 *     functions for sending commands and data to the LCD, writing strings and numbers, and
 *     creating custom characters.
 *
 * Author: [Your Name]
 * Date: [Creation or Last Modification Date]
 *
 * Notes:
 *     - The LCD is assumed to be connected in a 4-bit mode.
 *     - This driver is designed to be modular and easily portable.
 *     - The file relies on the DIO driver for AVR ATmega32 for low-level pin control.
 */

#include <util/delay.h> 

/* UTILES_LIB */
#include "../../UTIL_LIB/STD_TYPES.h"
#include "../../UTIL_LIB/BIT_MATH.h"

/* MCAL */
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_private.h"

/* HAL */
#include "../LCD/LCD_interface.h"
#include "./LCD_private.h"
#include "../LCD/LCD_config.h"

/*
 * Function: LCD_voidInit
 * ----------------------
 * Initializes the LCD display for use in a 4-bit operation mode.
 *
 * This function performs the necessary startup sequence to prepare
 * the LCD for receiving commands and data. It sets up the LCD for
 * 4-bit mode operation, configures the display characteristics such
 * as display on/off, cursor visibility, and blinking. It also sets
 * the LCD entry mode for cursor movement and display shifting.
 *
 * Parameters:
 *   void - No parameters.
 *
 * Returns:
 *   void - This function does not return a value.
 */
void LCD_voidInit(void)
{
    // Configure LCD control and data pins as outputs
    DIO_setPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
    DIO_setPinDirection(LCD_E_PORT, LCD_E_PIN, DIO_PIN_OUTPUT);
    DIO_setPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
    DIO_setPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
    DIO_setPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
    DIO_setPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);

    // Wait for the power to stabilize (VDD to rise to 4.5V)
    _delay_ms(35);

    // Initialize LCD in 4-bit mode
    // Function Set: Interface is 4 bits, 2 line display, 5x8 font
    private_voidWriteHalfPort(0b0010);  // Send first part (only 4 MSB bits of command)
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
    LCD_voidSendCmnd(0b00101000);       // Send second part (full command)
    _delay_us(45);

    // Display On/Off Control: Display ON, Cursor ON, Blink ON
    LCD_voidSendCmnd(0b00001111);
    _delay_us(45);

    // Clear Display
    LCD_voidSendCmnd(0b00000001);
    _delay_ms(2);

    // Set Entry Mode: Increment cursor, No shift of display
    LCD_voidSendCmnd(0b00000110);
}

/*
 * Function: LCD_voidSendCmnd
 * --------------------------
 * Sends a command to the LCD display.
 *
 * This function is used to send various command instructions to the LCD.
 * The command is sent in two parts in 4-bit mode: the most significant 4 bits
 * are sent first, followed by the least significant 4 bits. Each part is
 * written to the LCD's data pins, and an enable pulse is sent to signal
 * the LCD controller to read these bits.
 *
 * Parameters:
 *   copy_u8Cmnd - The 8-bit command instruction to be sent to the LCD.
 *
 * Returns:
 *   void - This function does not return a value.
 *
 * Example Usage:
 *   LCD_voidSendCmnd(0x01); // Clears the LCD display
 */
void LCD_voidSendCmnd(u8 copy_u8Cmnd)
{
    // Set RS pin to 0 to indicate command mode
    DIO_setPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);

    // Send the most significant 4 bits of the command
    private_voidWriteHalfPort(copy_u8Cmnd >> 4);

    // Generate an enable pulse to latch the data
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);

    // Send the least significant 4 bits of the command
    private_voidWriteHalfPort(copy_u8Cmnd);

    // Generate another enable pulse to latch the data
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
}


/*
 * Function: LCD_voidSendChar
 * --------------------------
 * Sends a single character to the LCD display.
 *
 * This function sends an 8-bit data (character) to the LCD for display. The character
 * is sent in two parts when operating in 4-bit mode: first the most significant 4 bits
 * are sent, followed by the least significant 4 bits. Each part is written to the LCD's
 * data pins, and an enable pulse is sent to signal the LCD controller to read and process
 * these bits.
 *
 * Parameters:
 *   copy_u8Data - The character to be displayed on the LCD, passed as an 8-bit unsigned integer.
 *
 * Returns:
 *   void - This function does not return a value.
 *
 * Example Usage:
 *   LCD_voidSendChar('A'); // Displays the character 'A' on the LCD
 */
void LCD_voidSendChar(u8 copy_u8Data)
{
    // Set RS pin to 1 to indicate data mode (for displaying characters)
    DIO_setPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);

    // Send the most significant 4 bits of the character
    private_voidWriteHalfPort(copy_u8Data >> 4);

    // Generate an enable pulse to latch the data
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);

    // Send the least significant 4 bits of the character
    private_voidWriteHalfPort(copy_u8Data);

    // Generate another enable pulse to latch the data
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
    _delay_ms(1);
    DIO_setPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
}


/*
 * Function: LCD_voidWriteString
 * -----------------------------
 * Description:
 *     Displays a string of characters on the LCD screen.
 *     This function takes a pointer to a string (array of characters) and sends each character to
 *     the LCD to be displayed. The string must be null-terminated ('\0'), which is the standard
 *     format for strings in C. The function checks for the null terminator to know when the string ends.
 *
 * Parameters:
 *     - copy_pu8String: Pointer to the string to be displayed on the LCD.
 *                       This must be a null-terminated string.
 *
 * Returns:
 *     void: This function does not return a value.
 *
 * Example Usage:
 *     u8 myString[] = "Hello, World!";
 *     LCD_voidWriteString(myString); // Displays "Hello, World!" on the LCD.
 *
 * Note:
 *     - The LCD must be initialized with LCD_voidInit() before calling this function.
 *     - The string is displayed at the current cursor position on the LCD.
 *     - If the string is longer than the LCD's width, it will continue on the next line or wrap around.
 */
void LCD_voidWriteString(u8* copy_pu8String)
{
    // Check if the pointer is not NULL to avoid dereferencing a NULL pointer
    if(copy_pu8String != NULL)
    {
        u8 local_u8Counter = 0;
        // Iterate through each character in the string until the null terminator is reached
        while(copy_pu8String[local_u8Counter] != '\0')
        {
            // Send each character to the LCD to be displayed
            LCD_voidSendChar(copy_pu8String[local_u8Counter]);
            // Move to the next character in the string
            ++local_u8Counter;
        }
    }
}

/* Function Prototypes */

/*
 * Function: private_voidWriteHalfPort
 * -----------------------------------
 * Writes a 4-bit value to the LCD data lines.
 *
 * This static function is used internally within the LCD driver to send
 * half of a byte (4 bits) to the LCD in 4-bit mode operation. It directly
 * manipulates the data lines of the LCD connected to the microcontroller.
 * This function is marked static to limit its scope to this source file,
 * ensuring that it is not callable from outside the LCD module.
 *
 * Parameters:
 *   copy_u8Value - An 8-bit unsigned integer where only the lower 4 bits
 *                  are relevant and will be sent to the LCD data lines.
 *
 * Returns:
 *   void - This function does not return a value.
 */
void private_voidWriteHalfPort(u8 copy_u8Value)
{
	if(GET_BIT(copy_u8Value,0) == 1)
	{
		DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_HIGH);
	}
	else if(GET_BIT(copy_u8Value,0) == 0)
	{
		DIO_setPinValue(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_LOW);
	}
	
	if(GET_BIT(copy_u8Value,1) == 1)
	{
		DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_HIGH);
	}
	else if(GET_BIT(copy_u8Value,1) == 0)
	{
		DIO_setPinValue(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_LOW);
	}
	
	if(GET_BIT(copy_u8Value,2) == 1)
	{
		DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_HIGH);
	}
	else if(GET_BIT(copy_u8Value,2) == 0)
	{
		DIO_setPinValue(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_LOW);
	}
	
	if(GET_BIT(copy_u8Value,3) == 1)
	{
		DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_HIGH);
	}
	else if(GET_BIT(copy_u8Value,3) == 0)
	{
		DIO_setPinValue(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_LOW);
	}
}

/*
 * Function: LCD_voidWriteNumber
 * -----------------------------
 * Description:
 *     Displays a signed long integer number on the LCD screen.
 *     This function converts a signed long integer to its string representation and displays it on the LCD.
 *     It handles both positive and negative numbers and correctly displays them, including the sign.
 *     This is particularly useful for displaying numeric data such as sensor readings or calculations.
 *
 * Parameters:
 *     - copy_u8Data: The signed long integer (s32) number to be displayed on the LCD.
 *
 * Returns:
 *     void: This function does not return a value.
 *
 * Example Usage:
 *     LCD_voidWriteNumber(1234); // Displays "1234" on the LCD.
 *     LCD_voidWriteNumber(-5678); // Displays "-5678" on the LCD.
 *
 * Note:
 *     - The number is displayed at the current cursor position on the LCD.
 *     - The function can handle numbers up to the maximum size of a signed long integer.
 *     - If the number is zero, it simply displays "0".
 */
void LCD_voidWriteNumber(s32 copy_u8Data)
{
    // Array to store the ASCII representation of the number
    u8 local_u8String[20];
    u8 local_u8Remainder;
    u8 local_u8Counter = 0;
    s8 local_s8Counter2;

    // Handle the special case when the number is zero
    if(copy_u8Data == 0)
    {
        LCD_voidSendChar('0'); // Display the character '0'
        return;
    }

    // Handle negative numbers
    if(copy_u8Data < 0)
    {
        copy_u8Data *= (-1); // Convert the number to positive
        LCD_voidSendChar('-'); // Display the minus sign
    }

    // Convert the number to its ASCII representation
    while(copy_u8Data > 0)
    {
        local_u8Remainder = copy_u8Data % 10; // Extract the least significant digit
        local_u8String[local_u8Counter] = local_u8Remainder + '0'; // Convert digit to ASCII
        copy_u8Data /= 10; // Remove the extracted digit
        local_u8Counter++;
    }

    // Display the number in reverse order (to correct the orientation)
    for(local_s8Counter2 = (local_u8Counter-1); local_s8Counter2 >= 0; local_s8Counter2--)
    {
        LCD_voidSendChar(local_u8String[local_s8Counter2]); // Display each digit
    }
}


/*
 * Function: LCD_voidWriteNumber4Digits
 * ------------------------------------
 * Description:
 *     Displays a 4-digit number on the LCD screen.
 *     This function takes a 16-bit unsigned integer (u16) and displays it as a 4-digit number.
 *     It ensures that all four digits are displayed, including leading zeros if necessary.
 *     This is particularly useful for displaying fixed-width numeric data such as time (e.g., "1234" or "0030").
 *
 * Parameters:
 *     - copy_u8Data: The 16-bit unsigned integer (u16) number to be displayed on the LCD.
 *                    The number should be in the range of 0 to 9999.
 *
 * Returns:
 *     void: This function does not return a value.
 *
 * Example Usage:
 *     LCD_voidWriteNumber4Digits(1234); // Displays "1234" on the LCD.
 *     LCD_voidWriteNumber4Digits(56);   // Displays "0056" on the LCD.
 *
 * Note:
 *     - The number is displayed at the current cursor position on the LCD.
 *     - If the number is larger than 9999, only the least significant 4 digits will be displayed.
 */
void LCD_voidWriteNumber4Digits(u16 copy_u8Data)
{
    // Display each digit by extracting it using modulo and division operations
    // The modulo operation isolates the digits, and division aligns them for display

    // Extract and display the thousands place digit
    LCD_voidSendChar(((copy_u8Data % 10000) / 1000) + '0');

    // Extract and display the hundreds place digit
    LCD_voidSendChar(((copy_u8Data % 1000) / 100) + '0');

    // Extract and display the tens place digit
    LCD_voidSendChar(((copy_u8Data % 100) / 10) + '0');

    // Extract and display the ones place digit
    LCD_voidSendChar(((copy_u8Data % 10) / 1) + '0');
}



/*
 * Function: LCD_voidDisplayFloat
 * ------------------------------
 * Displays a floating-point number on the LCD with specified precision.
 *
 * Parameters:
 * - float copy_f32Number: The floating-point number to be displayed.
 *
 * Returns:
 * - void
 *
 * Description:
 * This function takes a floating-point number, formats it to a string with
 * up to 3 decimal places and 8 whole number digits, and then displays it on the LCD.
 * The function handles the conversion of the floating-point number to a string and
 * ensures the formatted string fits the LCD's display constraints.
 */
void LCD_voidDisplayFloat(f32 number) {
    // Display the integer part
    s32 intPart = (s32)number;
    LCD_voidWriteNumber(intPart);

    // Display the decimal point
    LCD_voidSendChar('.');

    // Calculate the fractional part
    f32 fractionPart = number - (f32)intPart;
    // Assuming you want to display up to 3 decimal places
    s32 fracInt = (s32)(fractionPart * 1000); // Adjust 1000 for the number of decimal places

    // Display the fractional part
    // Check for leading zeros in the fractional part
    if (fracInt < 100 && fracInt >= 10) {
        // Only two digits after the decimal, add one leading zero
        LCD_voidSendChar('0');
    } else if (fracInt < 10) {
        // Only one digit after the decimal, add two leading zeros
        LCD_voidSendChar('0');
        LCD_voidSendChar('0');
    }

    // Now display the fractional part
    LCD_voidWriteNumber(fracInt);
}


/*
 * Function: LCD_voidClear
 * -----------------------
 * Description:
 *     Clears the LCD display screen.
 *     This function sends a command to the LCD to clear its display, removing any characters or data previously shown.
 *     After clearing, the cursor is reset to the home position (the first cell in the top-left corner of the display).
 *     This function is useful for refreshing the display or preparing the screen for new data after certain operations.
 *
 * Parameters:
 *     void: This function does not take any parameters.
 *
 * Returns:
 *     void: This function does not return a value.
 *
 * Example Usage:
 *     LCD_voidClear(); // Clears the entire LCD display.
 *
 * Note:
 *     - The clearing process takes a certain amount of time (usually a few milliseconds).
 *     - It is advisable to introduce a small delay after calling this function to ensure that the LCD has completed the clearing operation before proceeding with further display actions.
 */
void LCD_voidClear(void)
{
    // Send the clear display command (0x01) to the LCD
    // This command clears the display and returns the cursor to the home position
    LCD_voidSendCmnd(0x01);
}


/*
 * Function: LCD_voidShift
 * -----------------------
 * Shifts the cursor or the entire display of the LCD in the specified direction for a given number of times.
 * The LCD display or cursor can be shifted left or right depending on the provided parameters. This is
 * particularly useful for marquee display effects or adjusting the cursor position dynamically.
 *
 * Parameters:
 * - copy_u8SC_Bit: Determines whether to shift the cursor (0) or the entire display (1).
 * - copy_u8RL_Bit: Direction of shift; left (0) or right (1).
 * - copy_u8Shift_Times: Number of times the shifting should occur.
 *
 * Returns:
 * - void: This function does not return a value.
 *
 * Note:
 * The function introduces a delay between each shift operation to make the shift visible and smooth.
 */
void LCD_voidShift(u8 copy_u8SC_Bit, u8 copy_u8RL_Bit, u8 copy_u8Shift_Times)
{
//	u8 Local_u8SC_Bit = copy_u8SC_Bit;
//	u8 Local_u8RL_Bit = copy_u8RL_Bit;
	u8 Local_u8Counter;
	if(copy_u8SC_Bit == 0)
	{
		switch(copy_u8RL_Bit)
		{
			case 0:
				for(Local_u8Counter = 0; Local_u8Counter < copy_u8Shift_Times; Local_u8Counter++)
				{
					//shift cursor left
					LCD_voidSendCmnd(0b00010000);
					_delay_ms(200);
				}
				break;
			case 1:
				for(Local_u8Counter = 0; Local_u8Counter < copy_u8Shift_Times; Local_u8Counter++)
				{
				//shift cursor right
				LCD_voidSendCmnd(0b00010100);
				_delay_ms(200);
				}
				break;
		}
	}
	else if(copy_u8SC_Bit == 1)
	{
		switch(copy_u8RL_Bit)
		{
			case 0:
				for(Local_u8Counter = 0; Local_u8Counter < copy_u8Shift_Times; Local_u8Counter++)
				{
					//Shift entire display left
					LCD_voidSendCmnd(0b00011000);
					_delay_ms(200);
				}
					break;
			case 1:
				for(Local_u8Counter = 0; Local_u8Counter < copy_u8Shift_Times; Local_u8Counter++)
				{
					//Shift entire display right
					LCD_voidSendCmnd(0b00011100);
					_delay_ms(200);
				}
					break;
		}
	}
	else
	{
		//Invalid SC Bit provided; exit the function without any operation
		return;
	}
}

/*
 * Function: LCD_voidWriteBinary
 * -----------------------------
 * Description:
 *     Displays the binary representation of an 8-bit unsigned integer on the LCD.
 *     This function converts an 8-bit unsigned integer (u8) into its binary form and displays it on the LCD.
 *     Each bit of the integer is represented as '1' or '0' on the LCD. It's a useful function for debugging or visualizing binary data.
 *
 * Parameters:
 *     copy_u8Data - An 8-bit unsigned integer (u8) whose binary representation is to be displayed.
 *
 * Returns:
 *     void - This function does not return a value.
 *
 * Example Usage:
 *     u8 data = 0b10101010;
 *     LCD_voidWriteBinary(data); // Displays "10101010" on the LCD.
 *
 * Note:
 *     - The function handles an 8-bit data input and represents it in 8 character spaces on the LCD.
 *     - It is assumed that the LCD is already initialized and configured for proper display.
 *     - The binary representation is displayed at the current cursor position on the LCD.
 *     - To display the binary data at a specific location, set the cursor position before calling this function.
 */
void LCD_voidWriteBinary(u8 copy_u8Data)
{
    s8 Local_s8Counter;
    // Iterate over each bit in the 8-bit data
    for(Local_s8Counter = 7; Local_s8Counter >= 0; Local_s8Counter--)
    {
        // Check each bit starting from the most significant bit (MSB) to least significant bit (LSB)
        // AND the data with 1 after shifting to the right for each bit position
        if((copy_u8Data >> Local_s8Counter) & 1)
        {
            // If the bit is 1, send '1' to the LCD
            LCD_voidSendChar('1');
        }
        else
        {
            // If the bit is 0, send '0' to the LCD
            LCD_voidSendChar('0');
        }
    }
}


/*
 * Function: LCD_voidWriteBinaryShort
 * ----------------------------------
 * Description:
 *     Displays the binary representation of an 8-bit unsigned integer on the LCD,
 *     omitting leading zeros. This function is useful for representing binary data
 *     in a concise format, especially when dealing with values that do not utilize
 *     the full 8-bit range. The binary representation is displayed at the current
 *     cursor position on the LCD.
 *
 * Parameters:
 *     copy_u8Data - An 8-bit unsigned integer (u8) whose binary representation,
 *                   without leading zeros, is to be displayed.
 *
 * Returns:
 *     void - This function does not return a value.
 *
 * Example Usage:
 *     u8 data = 0b00101010;
 *     LCD_voidWriteBinaryShort(data); // Displays "101010" on the LCD.
 *
 * Note:
 *     - The function iterates over each bit of the 8-bit data, starting from the
 *       most significant bit (MSB) to the least significant bit (LSB).
 *     - Leading zeros are not displayed. Once the first '1' is encountered,
 *       all subsequent zeros and ones are displayed.
 *     - It is assumed that the LCD is already initialized and configured for proper display.
 *     - To display the binary data at a specific location, set the cursor position before calling this function.
 */
void LCD_voidWriteBinaryShort(u8 copy_u8Data)
{
    s8 Local_s8Counter;
    s8 Local_Flag = 0; // Flag to indicate the occurrence of the first '1'

    // Iterate over each bit in the 8-bit data
    for(Local_s8Counter = 7; Local_s8Counter >= 0; Local_s8Counter--)
    {
        // Check each bit starting from MSB to LSB
        if((copy_u8Data >> Local_s8Counter) & 1)
        {
            // If the bit is 1, send '1' to the LCD and set the flag
            LCD_voidSendChar('1');
            Local_Flag = 1;
        }
        else
        {
            // If the bit is 0 and the flag is set (i.e., after the first '1' has been encountered)
            if(Local_Flag == 1)
            {
                // Send '0' to the LCD
                LCD_voidSendChar('0');
            }
        }
    }
}


/*
 * Function: LCD_voidGoTo
 * ----------------------
 * Description:
 *     Sets the cursor position on the LCD to a specified line and cell (column).
 *     This function is essential for controlling where characters are displayed on the LCD.
 *     It utilizes the Set DDRAM Address command to move the cursor to the desired position.
 *     The LCD screen is divided into lines and cells, with each cell capable of displaying one character.
 *
 * Parameters:
 *     copy_u8Line - An 8-bit unsigned integer (u8) specifying the line number.
 *                   This is typically 1 for the first line, 2 for the second, and so on.
 *     copy_u8Cell - An 8-bit unsigned integer (u8) specifying the cell (column) number within the line.
 *                   The value usually ranges from 0 (first cell) to the maximum number of cells minus one
 *                   (e.g., 15 for a 16x2 LCD).
 *
 * Returns:
 *     void - This function does not return a value.
 *
 * Example Usage:
 *     LCD_voidGoTo(1, 5); // Moves the cursor to line 1, cell 5.
 *     LCD_voidWriteString("Hello"); // Writes "Hello" starting from line 1, cell 5.
 *
 * Note:
 *     - It is assumed that the LCD is already initialized and in a ready state to receive commands.
 *     - The LCD lines and cells are indexed starting from 1, consistent with common LCD documentation.
 *     - The function calculates the DDRAM address based on the provided line and cell values.
 *     - Unsupported line numbers are ignored, and the function does nothing in such cases.
 */
void LCD_voidGoTo(u8 copy_u8Line, u8 copy_u8Cell)
{
    // Check which line is selected and calculate the DDRAM address accordingly
    switch(copy_u8Line)
    {
        case LCD_LINE_ONE:
            // For line 1, add the cell number to the base address of line 1 (0x80)
            LCD_voidSendCmnd(0x80 + copy_u8Cell);
            break;
        case LCD_LINE_TWO:
            // For line 2, add the cell number to the base address of line 2 (0x80 + 0x40)
            LCD_voidSendCmnd(0x80 + 0x40 + copy_u8Cell);
            break;
        case LCD_LINE_THREE:
            // For line 3 (specific to some LCD modules), add the cell number to the base address of line 3
            LCD_voidSendCmnd(0x80 + 0x14 + copy_u8Cell);
            break;
        case LCD_LINE_FOUR:
            // For line 4 (specific to some LCD modules), add the cell number to the base address of line 4
            LCD_voidSendCmnd(0x80 + 0x54 + copy_u8Cell);
            break;
        default:
            // If an unsupported line number is provided, do nothing
            break;
    }
}

/*
 * Function: LCD_voidGoToClear
 *
 * Description:
 *    Clears a specific section of the LCD display by writing spaces to a designated area.
 *    This function is useful for erasing or updating a part of the display without affecting
 *    the rest of the content. It first moves the cursor to the specified start position and
 *    then writes blank spaces for the specified number of cells.
 *
 * Parameters:
 *    copy_u8Line       - The line number where the clearing should start.
 *    copy_u8Cell       - The cell (character position) in the line to start clearing.
 *    copy_u8NumOfCells - The number of cells to clear from the starting position.
 *
 * Returns:
 *    void
 *
 * Example:
 *    LCD_voidGoToClear(LCD_LINE_TWO, 0, 5); // Clears first 5 cells of the second line.
 *
 * Note:
 *    This function does not alter other parts of the display and is efficient for
 *    updating specific sections of the screen.
 */
void LCD_voidGoToClear(u8 copy_u8Line, u8 copy_u8Cell, u8 copy_u8NumOfCells) {
    // Move cursor to the specified line and cell
    LCD_voidGoTo(copy_u8Line, copy_u8Cell);

    // Clear the specified number of cells by writing spaces
    for (u8 i = 0; i < copy_u8NumOfCells; i++) {
        LCD_voidSendChar(' '); // Overwrite with space character
    }
}

/*
 * Function: LCD_voidWriteHex
 * -------------------------
 * Description:
 *     Displays a hexadecimal number on the LCD.
 *     This function takes an 8-bit unsigned integer (u8) and displays its hexadecimal representation on the LCD.
 *     It separates the input byte into two 4-bit nibbles (high and low), converts them to their ASCII equivalents,
 *     and sends them to the LCD to be displayed. This function is useful for debugging and displaying data in
 *     hexadecimal format, which is often more readable for certain types of data.
 *
 * Parameters:
 *     copy_u8Data - An 8-bit unsigned integer (u8) whose hexadecimal value is to be displayed on the LCD.
 *
 * Returns:
 *     void - This function does not return a value.
 *
 * Example Usage:
 *     LCD_voidWriteHex(0xAF); // Displays 'AF' on the LCD.
 *
 * Note:
 *     - The function handles both digits of the hexadecimal number separately.
 *     - It converts numbers from 0 to 9 and letters from A to F into their ASCII codes before sending them to the LCD.
 *     - The function assumes that the LCD is already initialized and ready to receive data.
 *     - Only 8-bit numbers (byte-sized) can be displayed in hexadecimal format using this function.
 */

/*
 * Function: LCD_voidWriteHex
 * -------------------------
 * Description:
 *     Displays a hexadecimal number on the LCD.
 *     This function takes an 8-bit unsigned integer (u8) and displays its hexadecimal representation on the LCD.
 *     It separates the input byte into two 4-bit nibbles (high and low), converts them to their ASCII equivalents,
 *     and sends them to the LCD to be displayed. This function is useful for debugging and displaying data in
 *     hexadecimal format, which is often more readable for certain types of data.
 *
 * Parameters:
 *     copy_u8Data - An 8-bit unsigned integer (u8) whose hexadecimal value is to be displayed on the LCD.
 *
 * Returns:
 *     void - This function does not return a value.
 *
 * Example Usage:
 *     LCD_voidWriteHex(0xAF); // Displays 'AF' on the LCD.
 *
 * Note:
 *     - The function handles both digits of the hexadecimal number separately.
 *     - It converts numbers from 0 to 9 and letters from A to F into their ASCII codes before sending them to the LCD.
 *     - The function assumes that the LCD is already initialized and ready to receive data.
 *     - Only 8-bit numbers (byte-sized) can be displayed in hexadecimal format using this function.
 */
void LCD_voidWriteHex(u8 copy_u8Data)
{
    // Extract the higher (most significant) 4 bits (nibble) of the data
    u8 Local_u8Hnibble = copy_u8Data >> 4;

    // Extract the lower (least significant) 4 bits (nibble) of the data
    u8 Local_u8Lnibble = copy_u8Data & 0x0F;

    // Convert and display the higher nibble
    if(Local_u8Hnibble <= 9)
    {
        // For numeric values (0-9), convert to ASCII by adding '0'
        LCD_voidSendChar(Local_u8Hnibble + '0');
    }
    else
    {
        // For alphabetic values (A-F), convert to ASCII by subtracting 10 and adding 'A'
        LCD_voidSendChar(Local_u8Hnibble - 10 + 'A');
    }

    // Convert and display the lower nibble
    if(Local_u8Lnibble <= 9)
    {
        // For numeric values (0-9), convert to ASCII by adding '0'
        LCD_voidSendChar(Local_u8Lnibble + '0');
    }
    else
    {
        // For alphabetic values (A-F), convert to ASCII by subtracting 10 and adding 'A'
        LCD_voidSendChar(Local_u8Lnibble - 10 + 'A');
    }
}


/*
 *Create a pattern and store in an address in CGRAM
 *The whole CGRAM is 8 bytes (1 special character) * 8 character slots = 64 bytes --> 0x00 to 0x07 addresses
 */
/*
 * Function: LCD_voidCreateCharacter
 * ------------------------------
 * Create and store a custom character pattern in the LCD's Character Generator RAM (CGRAM).
 *
 * This function allows users to define custom characters by passing an array of bytes
 * representing the character and then storing it in a specific location in the LCD's CGRAM.
 * After creating the custom character, you can display it on the LCD by sending its location
 * value (0-7) as if it was a regular character.
 *
 * Parameters:
 * - copy_Pu8CharArr: Pointer to an array of 8 bytes representing the custom character.
 *                    Each byte corresponds to a row in the 5x8 dot matrix of the character.
 * - copy_u8Location: The CGRAM location where the custom character will be stored.
 *                    Valid values are 0 to 7 for standard LCDs with 8 custom character slots.
 *
 * Returns:
 * - void
 */
void LCD_voidCreateCharacter(u8 *copy_Pu8CharArr, u8 copy_u8Location)
{
	u8 Local_u8Counter;

	//the command to set (go to) CGRAM address is 0b01xxxxxx --> with 0s it's 0x40 for the base address
	//0x40 + Location*8 e.g. location = 2 i.e. second location 0x40+(16 decimal)=(0x40)+(0x10)=64+16=80= 0x50 --> address of second char slot in CGRAM

    // The base CGRAM address for LCDs is typically 0x40.
    // Multiplying the desired location by 8 calculates the offset from the base address.
    // For example, location 2 would be: 0x40 + (2 * 8) = 0x50.
	LCD_voidSendCmnd(0x40 + (copy_u8Location*8));
	_delay_us(50);
	//pass u8 array[8], representing the special character, to CGRAM using a for loop

    // Loop through each byte of the custom character array and send it to the current CGRAM address.
    // The LCD's CGRAM address will auto-increment after each byte, so the next byte will go to the next row of the character.
	for(Local_u8Counter = 0; Local_u8Counter < 8; Local_u8Counter++)
	{
		LCD_voidSendChar(copy_Pu8CharArr[Local_u8Counter]);
		_delay_us(100);
	}

	//on exit go back to DDRAM by setting DDRAM instruction

    // After storing the custom character, switch back to the Display Data RAM (DDRAM) address mode.
    // This is typically done using the 0x80 command for LCDs.
	LCD_voidSendCmnd(0x80);
	_delay_us(100);
}
