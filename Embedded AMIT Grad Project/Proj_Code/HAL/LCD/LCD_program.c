/*
 * LCD_program.c
 *
 *  Created on: Jul 23, 2023
 *      Author: Kareem Hussein
 */

/*
 *Whenever there is delay, define the clock speed to 16MHz (used in AVR ATMEGA32)
 */
//#define F_CPU 16000000UL
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

/*	Character patterns	*/


void LCD_voidInit(void)
{
	/*
	 *Startup initialization sequence of LCD panel to work using 4 bit mode, as per manufacturer
	 */
	//set all pins as outputs --> GND, VDD, VO, BLA and BLK are connected to external sources NOT AVR controller's pins
	//R/W is set to 0 (input) by hardware wirings (default)
	DIO_setPinDirection(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_E_PORT,LCD_E_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D4_PORT,LCD_D4_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D5_PORT,LCD_D5_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D6_PORT,LCD_D6_PIN,DIO_PIN_OUTPUT);
	DIO_setPinDirection(LCD_D7_PORT,LCD_D7_PIN,DIO_PIN_OUTPUT);
	
	
	//Wait for 35 ms so that VDD rises to 4.5 V
	_delay_ms(35);
	
	//set RS to 0 i.e. send command mode
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	/*
	 *1- Send command for function set (12 bits) --> send on 3 times (4 bitsx3)
	 *first 4 bits are same as second 4 bits
	 */
	/*
	 *Since this is 4 bit mode --> a single command or data is sent on two separate times (4 bits at a time)
	 */
	//0010
	private_voidWriteHalfPort(0b0010);
	/*
	 *Enable Pulse *//* H => L
	 *Enable works via rising/falling edges.
	 *To send commands --> High to low state switch (1 to 0).
	 *You send enable pulse each time 4 bits are sent (4 bit mode) --> inform LCD MC
	 */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);

	/*
	 *Send next 8 bits of function set instruction
	 *Sets interface data length (DL:8-bit/4-bit), numbers of display line (N: 2-line/l-line), and display font type F: (5x11dots/5x8dots)
	 *0010 and 10xx --> N = 1 and F = 1 and x's can be 0 or 1
	 */
	LCD_voidSendCmnd(0b00101000);	
	_delay_us(45);
	
	//2- Display on off Control (DisplayOn, Cursor on, Blink on)
	//D = 1 (display on), C = 1 (cursor on), B = 1 (blink on)
	LCD_voidSendCmnd(0b00001111);
	_delay_us(45);
	
	//3- Clear Display
	LCD_voidSendCmnd(0b00000001);
	_delay_ms(2);
	
	//4- Set Entry Mode
	/*
	 *Sets cursor move direction and enable the shift of entire display. These operations are performed during data write and read.
	 */
	LCD_voidSendCmnd(0b00000110);
}

/*
 *First function implemented in this .c file.
 *
 */
void LCD_voidSendCmnd(u8 copy_u8Cmnd)
{
	//set Rs pin = 0 (write command)
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_LOW);
	
	//Write The left-most (most sig.) 4 bits Of command on data pins
	private_voidWriteHalfPort(copy_u8Cmnd>>4);
	
	/* Enable Pulse *//* H => L */
	//enable pulse (high to low switch) informs LCD MC that 4 bits were sent
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
	//Write The right-most (least sig.) 4 bits Of command on data pins
	private_voidWriteHalfPort(copy_u8Cmnd);
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
}


void LCD_voidSendChar(u8 copy_u8Data)
{
	//set Rs pin = 1 (write data)
	DIO_setPinValue(LCD_RS_PORT,LCD_RS_PIN,DIO_PIN_HIGH);
	
	// Write The Most 4 bits Of data on Data Pins
	private_voidWriteHalfPort(copy_u8Data>>4);
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
	
	// Write The Least 4 bits Of data on Data Pins
	private_voidWriteHalfPort(copy_u8Data);
	
	/* Enable Pulse *//* H => L */
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_setPinValue(LCD_E_PORT,LCD_E_PIN,DIO_PIN_LOW);
}


void LCD_voidWriteString(u8* copy_pu8String)
{
	if(copy_pu8String != NULL)
	{
		u8 local_u8Counter = 0;
		while(copy_pu8String[local_u8Counter] != '\0')
		{
			LCD_voidSendChar(copy_pu8String[local_u8Counter]);
			++local_u8Counter; //Check
		}
	}
}


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
 *Send a number and print it out on LCD as number (not ASCII equivalent of number).
 *Input: signed long int.
 */
void LCD_voidWriteNumber(s32 copy_u8Data)
{
	//string size = to LCD screen columns
	u8 local_u8String[20];
	//remainder of modulus
	u8 local_u8Remainder;
	u8 local_u8Counter = 0;
	//counter is signed since it'll be decremented in a loop. Can cause errors.
	s8 local_s8Counter2;
	//Handle case: 0 is passed
	if(copy_u8Data == 0)
	{
		//Send ASCII of 0
		LCD_voidSendChar('0');
		return;
	}
	//Handle case: number is less than 0
	//turn number into positive and print '-'
	if(copy_u8Data < 0)
	{
		copy_u8Data *= (-1);
		LCD_voidSendChar('-');
	}
	//loop to get every single digit and sign as ASCII code
	while(copy_u8Data>0)
	{
		//gets right most digit
		local_u8Remainder = copy_u8Data%10;
		//adding by a char between ' ' treats local_u8Remainder as an ASCII code
		local_u8String[local_u8Counter] = local_u8Remainder + '0';
		//save number without rightmost digit
		copy_u8Data = copy_u8Data/10;
		local_u8Counter++;
	}
	//loop to send array of ASCII codes to be printed
	//j=i; number>0; j--
	//if number is -ve e.g. 132 --> arr={'2','3','1'}
	for(local_s8Counter2 = (local_u8Counter-1); local_s8Counter2 >= 0; local_s8Counter2--)
	{
		//It uses ASCII code to print
		LCD_voidSendChar(local_u8String[local_s8Counter2]);
	}

}

void LCD_voidWriteNumber4Digits(u16 copy_u8Data)
{
	/*
	 *given: 9632
	 *1- 9632%10000 = 9632
	 *2- 9632/1000 = 9 -> increment 9 on ASCII of 0 --> send ASCII (ASCII of9)
	 *Repeat
	 */
	LCD_voidSendChar(((copy_u8Data%10000)/1000) + '0');
	LCD_voidSendChar(((copy_u8Data%1000)/100) + '0');
	LCD_voidSendChar(((copy_u8Data%100)/10) + '0');
	LCD_voidSendChar(((copy_u8Data%10)/1) + '0');
}

void LCD_voidClear(void)
{
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

//prints out the 8 bit binary representation of an unsigned short int
void LCD_voidWriteBinary(u8 copy_u8Data)
{
	s8 Local_s8Counter;
	//counter set to 7 and decremented to 0 --> 0 to 7 bits of binary
	for(Local_s8Counter = 7; Local_s8Counter >= 0; Local_s8Counter--)
	{
		//if the rightmost bit is AND by 1 --> 1 if it's 1 or 0 if it's 0
		if((copy_u8Data>>Local_s8Counter)&1)
		{
			//send ASCII of 1 to LCD MC (prints out 1 on LCD)
			LCD_voidSendChar('1');
		}
		else
		{
			//send ASCII of 0 to LCD MC (prints out 0 on LCD)
			LCD_voidSendChar('0');
		}
	}
}

//prints out the binary representation of an unsigned short in
//Any zeros on the left is not printed
void LCD_voidWriteBinaryShort(u8 copy_u8Data)
{
	s8 Local_s8Counter;
	//flag becomes 1 when the first '1' is encountered going from right to left
	s8 Local_Flag = 0;
	//counter set to 7 and decremented to 0 --> 0 to 7 bits of binary
	for(Local_s8Counter = 7; Local_s8Counter >= 0; Local_s8Counter--)
	{
		//if the leftmost bit is AND by 1 --> 1 if it's 1 or 0 if it's 0
		if((copy_u8Data>>Local_s8Counter)&1)
		{
			//send ASCII of 1 to LCD MC (prints out 1 on LCD)
			LCD_voidSendChar('1');
			Local_Flag = 1;
		}
		else
		{
			//ensures that 1st '1' was met in binary number
			//ensures printing out significant 0's only
			if(Local_Flag == 1)
			{
				//send ASCII of 0 to LCD MC (prints out 0 on LCD)
				LCD_voidSendChar('0');
			}
		}
	}
}

/*
 *Write data to CG or DD RAM
 *1 0 D7 D6 D5 D4 D3 D2 D1 D0 = 0x80 || mask (navigates to certain address on screen i.e. DDRAM)
 *Write data into internal RAM(DDRAM/CGRAM).
 *DDRAM is implemented as a buffer or an array of memory locations in the microcontroller's RAM (Random Access Memory).
 *Each memory location in the DDRAM corresponds to a specific pixel on the LCD screen.
 */
void LCD_voidGoTo(u8 copy_u8Line, u8 copy_u8Cell)
{
	//to write to first line in LCD (DDRAM)
	if(copy_u8Line == LCD_LINE_ONE)
	{
		//1 0 D7 D6 D5 D4 D3 D2 D1 D0 = 0x80 --> 1 at RS bit for write to DDR command
		//D7 to D0 makes you navigate to a certain cell in first line
		//or 0x80 || copy_u8Cell --> same operation
		LCD_voidSendCmnd(0x80+copy_u8Cell);
	}
	else if(copy_u8Line == LCD_LINE_TWO)
	{
		//0x40 makes you jump to start address of line 1
		LCD_voidSendCmnd(0x80+0x40+copy_u8Cell);
	}
	else if(copy_u8Line == LCD_LINE_THREE)
	{
		//0x40 makes you jump to start address of line 1
		LCD_voidSendCmnd(0x80+0x14+copy_u8Cell);
	}
	else if(copy_u8Line == LCD_LINE_FOUR)
	{
		//0x40 makes you jump to start address of line 1
		LCD_voidSendCmnd(0x80+0x54+copy_u8Cell);
	}
	else
	{}
}

void LCD_voidWriteHex(u8 copy_u8Data)
{
	//store higher nibble in 4 bits on right
	u8 Local_u8Hnibble = copy_u8Data>>4;
	//store lower nibble in 4 bits on right
	u8 Local_u8Lnibble = copy_u8Data&(0x0f);
	if(Local_u8Hnibble <= 9)
	{
		//e.g. 9 + '0' gives '9' which is also ASCII of 9
		LCD_voidSendChar(Local_u8Hnibble + '0');
	}
	else //if Lnibble A (10) to F (15)
	{
		//e.g B - 10 = 11 - 10 = 1 --> 1 + 'A' = 'B' or 66 in ASCII code
		LCD_voidSendChar(Local_u8Hnibble - 10 + 'A');
	}
	if(Local_u8Lnibble <= 9)
	{
		//e.g. 9 + '0' gives '9' which is also ASCII of 9
		LCD_voidSendChar(Local_u8Lnibble + '0');
	}
	else //if Lnibble A (10) to F (15)
	{
		//e.g B - 10 = 11 - 10 = 1 --> 1 + 'A' = 'B' or 66 in ASCII code
		LCD_voidSendChar(Local_u8Lnibble - 10 + 'A');
	}
}

void LCD_voidGoToClear(u8 copy_u8Line, u8 copy_u8Cell, u8 copy_u8NumOfCells)
{
	u8 Local_u8Counter;
	LCD_voidGoTo(copy_u8Line, copy_u8Cell);
	for(Local_u8Counter = 0; Local_u8Counter < copy_u8NumOfCells; Local_u8Counter++)
	{
		LCD_voidSendChar(' ');
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
