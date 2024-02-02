///*
// * LCD_APP.c
// *
// *  Created on: Jul 31, 2023
// *      Author: elara
// */
////#define F_CPU 16000000UL
//#include <util/delay.h>
//
///* UTILES_LIB */
//#include "../../UTIL_LIB/STD_TYPES.h"
//#include "../../UTIL_LIB/BIT_MATH.h"
//
///* MCAL */
//#include "../../MCAL/DIO/DIO_interface.h"
//#include "../../MCAL/DIO/DIO_private.h"
//
///* HAL */
//#include "../LCD/LCD_interface.h"
//#include "./LCD_private.h"
//#include "../LCD/LCD_config.h"
//
//
///*
// *SUGGEST ADJUSTMENT --> delay added within the clear command OR other commands that require delay
// *REPLY: delay from <util/delay.h> should not be used in embedded systems --> other ways to do it
// */
//
//u8 LCD_Char_Pattern1[] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff};
//
//int main(void)
//{
///*	4 bit-mode initialization	*/
//	LCD_voidInit();
//
///* Variables to test with	*/
//	u8 strName[15] = "Mohammad";
//
//	// Custom character - a standing man:
//	u8 Local_Au8StandingMan[8] = {
//		    0b01110,  // Top of the head
//		    0b01110,  // Bottom of the head
//		    0b11111,  // Arms fully extended and upper torso
//		    0b00100,  // Mid torso
//		    0b00100,  // Lower torso
//		    0b01010,  // Upper legs
//		    0b01010,  // Lower legs
//		    0b01010   // Feet
//	};
//
///*	Test Set 5	*/
//	/*
//	 *Test LCD_voidWriteString before main
//	 *Test goto line using LCD_voidGoTo
//	 */
////	LCD_voidWriteString(strName);
////	_delay_ms(50);
////	LCD_voidGoTo(LCD_LINE_ONE,0);
////	_delay_ms(50);
////	LCD_voidWriteString("Moh");
////	_delay_ms(50);
////	LCD_voidGoTo(LCD_LINE_TWO,0);
////	_delay_ms(50);
////	LCD_voidWriteString("Ashraf");
////	_delay_ms(50);
////	LCD_voidGoTo(LCD_LINE_THREE, 0);
////	_delay_ms(50);
////	LCD_voidWriteNumber(1997);
////	_delay_ms(50);
////	LCD_voidGoTo(LCD_LINE_FOUR, 0);
////	_delay_ms(50);
////	LCD_voidWriteBinaryShort(25);
////	_delay_ms(50);
//
///*	Test Set 6	*/
//	/*
//	 *Function: char counter with its binary representation
//	 *Result: works well
//	 */
////	LCD_voidWriteString("char :");
////	_delay_ms(50);
////	LCD_voidGoTo(LCD_LINE_THREE, 0);
////	_delay_ms(50);
////	LCD_voidWriteString("Bin :");
////	_delay_ms(50);
//
//
//	LCD_voidCreateCharacter(LCD_Char_Pattern1, 0);
//	_delay_ms(50);
//
//	while(1)
//	{
//	/*
//	 *Test Set 1
//	 *Function: fill the LCD panel with characters whilst incrementing
//	 *Result: works well
//	 */
////		LCD_voidSendChar('A');
////		_delay_ms(10);
//
//	/*
//	 *Test Set 2
//	 *Function: alphabet loop over first 10 letters and clear display
//	 *Result: works well
//	 */
////		u8 counter;
////		for(counter = 65; counter < 73; counter++)
////		{
////			//ASCII of A is 65
////			LCD_voidSendChar(counter);
////			_delay_ms(200);
////		}
////		LCD_voidClear();
////		_delay_ms(200);
//	/*
//	 *Test Set 3
//	 *Function: write string
//	 *Result: works well
//	 */
////		LCD_voidWriteString(strName);
////		_delay_ms(1000);
////		LCD_voidClear();
////		/*
////		 *every command (instruction) should be followed by delay --> clear instruction takes 1.53 ms to execute as per datasheet
////		 */
////		_delay_ms(500);
//
//	/*
//	 *Test Set 4
//	 *Function: write numbers
//	 *Result: works well
//	 */
////		//zero --> print 0 as 1 digit
////		LCD_voidWriteNumber(0);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////		//write 0 as 4 digits
////		LCD_voidWriteNumber4Digits(0);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////		//write 0 as 8 bit binary
////		LCD_voidWriteBinaryShort(0);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////		//0 in hexadecimal
////		LCD_voidWriteHex(0);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////
////		//-125
////		LCD_voidWriteNumber(-125);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////		LCD_voidWriteBinaryShort(-125);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////
////		//12345
////		LCD_voidWriteNumber(12345);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////		LCD_voidWriteNumber4Digits(12345);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////		LCD_voidWriteBinaryShort(12345);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////		LCD_voidWriteHex(12345);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
////
////		//255 or 0xff
////		LCD_voidWriteHex(255);
////		_delay_ms(1000);
////		LCD_voidClear();
////		_delay_ms(100);
//
//	/*
//	 *Test Set 6
//	 *Function: char counter with its binary representation
//	 *Result: works well
//	 */
////		u8 counter;
////		for(counter = 65; counter <= 90; counter++)
////		{
////			LCD_voidGoTo(LCD_LINE_ONE, 7);
////			_delay_ms(50);
////			LCD_voidWriteNumber(counter);
////			_delay_ms(50);
////			LCD_voidGoTo(LCD_LINE_ONE, 11);
////			_delay_ms(50);
////			LCD_voidSendChar(counter);
////			_delay_ms(50);
////			LCD_voidGoTo(LCD_LINE_THREE, 6);
////			_delay_ms(50);
////			LCD_voidWriteBinary(counter);
////			_delay_ms(50);
////			_delay_ms(1000);
////		}
//
//	/*
//	 *Test Set 7
//	 *Function: pattern test
//	 *Result: works well
//	 */
////		u8 counter;
////		for(counter = 65; counter <= 89; counter++)
////		{
////			LCD_voidGoTo(LCD_LINE_ONE, 0);
////			_delay_ms(50);
////			LCD_voidSendChar(counter);
////			_delay_ms(50);
////
////			u8 rowCells;
////			LCD_voidGoTo(LCD_LINE_ONE, 1);
////			_delay_ms(50);
////			for(rowCells = 1; rowCells <= 18; rowCells++)
////			{
////				LCD_voidSendChar('>');
////				_delay_ms(100);
////			}
////
////			LCD_voidGoTo(LCD_LINE_ONE, 19);
////			_delay_ms(50);
////			LCD_voidSendChar(counter+1);
////			_delay_ms(500);
////			LCD_voidClear();
////			_delay_ms(50);
////		}
//
//	/*
//	 *Test Set 8
//	 *Function: test
//	 *Result: works well
//	 */
////		LCD_voidGoTo(LCD_LINE_ONE, 0);
////		_delay_ms(50);
////		LCD_voidWriteString("Moh");
////		_delay_ms(50);
////		LCD_voidGoTo(LCD_LINE_TWO, 0);
////		_delay_ms(50);
////		LCD_voidWriteString("Ashraf");
////		_delay_ms(1000);
////		LCD_voidGoToClear(LCD_LINE_TWO, 0, 19);
////		_delay_ms(50);
////		LCD_voidGoTo(LCD_LINE_TWO, 0);
////		_delay_ms(50);
////		LCD_voidWriteString("Salah");
////		_delay_ms(1000);
//
//	/*
//	 *Test Set 9
//	 *Create patterns in CGRAM for each char using a char array representing the pixels of a character
//	 */
////		//0 here corresponds to base address of CGRAM
////		LCD_voidSendChar(0);
////		_delay_ms(500);
//		/*
//		 *Test Set 9
////		 *Create patterns in CGRAM for each char using a char array representing the pixels of a character
////		 */
////		// Create the standing man character and store it in location 0 of the CGRAM
////		LCD_voidCreateCharacter(Local_Au8StandingMan, 0);
////		_delay_ms(1);
////	    // Clear the LCD display
////	    //LCD_voidClear();
////	    // Move the LCD cursor to a specific location. Here, I choose the first line and the first cell.
////	    LCD_voidGoTo(LCD_LINE_ONE, 0);
////	    _delay_ms(1);
////		LCD_voidSendChar(0);
////		 _delay_ms(1);
////		_delay_ms(2000);
////
////	/*
////	 *Test Set 10
////	 *Shifting the special character
////	 */
////		LCD_voidShift(1, 1, 20);
////		 _delay_ms(1);
//
//
//	}
//}
