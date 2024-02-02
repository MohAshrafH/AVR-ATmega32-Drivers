/*
 * LCD_interface.h
 *
 *  Created on: Jul 23, 2023
 *      Author: Kareem Hussein
 */

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

/* Macros For LCD Shifting Direction */
#define LCD_SHIFT_LEFT          0
#define LCD_SHIFT_RIGHT         1

/* Macros For LCD Line Id */
/*
 *LCD is 4 rows by 20 columns*
 */
#define LCD_LINE_ONE            0
#define LCD_LINE_TWO            1
#define LCD_LINE_THREE          2
#define LCD_LINE_FOUR           3

/*	LCD Apis	*/

void LCD_voidInit(void);
void LCD_voidSendCmnd(u8 copy_u8Cmnd);
void LCD_voidSendChar(u8 copy_u8Data);
void LCD_voidWriteString(u8* copy_pu8String);
void LCD_voidWriteNumber(s32 copy_u8Data);
void LCD_voidWriteNumber4Digits(u16 copy_u8Data);
void LCD_voidClear(void);
void LCD_voidShift(u8 copy_u8SC_Bit, u8 copy_u8RL_Bit, u8 copy_u8Shift_Times);
void LCD_voidWriteBinary(u8 copy_u8Data);
void LCD_voidWriteHex(u8 copy_u8Data);
void LCD_voidGoTo(u8 copy_u8Line, u8 copy_u8Cell);
void LCD_voidGoToClear(u8 copy_u8Line, u8 copy_u8Cell, u8 copy_u8NumOfCells);

/*	CGRAM API	*/
void LCD_voidCreateCharacter(u8 *copy_Pu8CharArr, u8 copy_u8Location);

#endif /* LCD_INTERFACE_H_ */
