/*
 * File: DIO_program.c
 *
 * Description:
 *     Implementation file for the Digital Input/Output (DIO) module in the AVR ATmega32
 *     microcontroller. This file provides the functional implementations for the DIO driver,
 *     including setting pin directions, reading and writing to pins and ports, toggling
 *     pin values, and initializing pin configurations. The functions in this file interact
 *     directly with the AVR hardware registers to control the digital I/O functionalities.
 *
 * Author:
 * Date: [Specify Date Here]
 */


/* UTILES_LIB */
#include "../../UTIL_LIB/STD_TYPES.h"
#include "../../UTIL_LIB/BIT_MATH.h"

/* MCAL */
#include "../DIO/DIO_interface.h"
#include "../DIO/DIO_private.h"

/* DIO Pins Configuration Array */
/*
 * Description:
 *     This array defines the initial configuration for all microcontroller pins.
 *     The configuration determines whether each pin is set as an input or output.
 *     The 'const' keyword ensures that the configuration is fixed and cannot be
 *     changed during runtime. The DIO_initPinsConfig function uses this array to
 *     set the initial direction of each pin.
 */

/* Example configuration for LED and Keypad usage */
const u8 DIO_PinsConfigArray [DIO_TOTAL_PINS] =
{
		DIO_PIN_INPUT,     //PIN0	PORTA
		DIO_PIN_INPUT,     //PIN1	PORTA
		DIO_PIN_INPUT,     //PIN2	PORTA
		DIO_PIN_INPUT,     //PIN3	PORTA
		DIO_PIN_INPUT,    //PIN4	PORTA --> Green LED
		DIO_PIN_INPUT,    //PIN5	PORTA --> Blue LED
		DIO_PIN_INPUT,    //PIN6	PORTA --> Yellow LED
		DIO_PIN_INPUT,     //PIN7	PORTA

		DIO_PIN_INPUT,     //PIN0	PORTB
		DIO_PIN_INPUT,     //PIN1	PORTB
		DIO_PIN_INPUT,     //PIN2	PORTB
		DIO_PIN_INPUT,     //PIN3	PORTB
		DIO_PIN_INPUT,     //PIN4	PORTB
		DIO_PIN_INPUT,     //PIN5	PORTB
		DIO_PIN_INPUT,     //PIN6	PORTB
		DIO_PIN_INPUT,    //PIN7	PORTB --> Red LED

		DIO_PIN_INPUT,     //PIN0	PORTC
		DIO_PIN_INPUT,     //PIN1	PORTC
		DIO_PIN_OUTPUT,     //PIN2	PORTC --> Keypad Row 3
		DIO_PIN_OUTPUT,     //PIN3	PORTC --> Keypad Row 2
		DIO_PIN_OUTPUT,     //PIN4	PORTC --> Keypad Row 1
		DIO_PIN_OUTPUT,     //PIN5	PORTC --> Keypad Row 0
		DIO_PIN_INPUT,     //PIN6	PORTC
		DIO_PIN_INPUT,     //PIN7	PORTC

		DIO_PIN_INPUT,     //PIN0	PORTD
		DIO_PIN_INPUT,     //PIN1	PORTD
		DIO_PIN_INPUT,     //PIN2	PORTD
		DIO_PIN_INPUT,     //PIN3	PORTD --> Keypad Column 3
		DIO_PIN_INPUT,     //PIN4	PORTD
		DIO_PIN_INPUT,     //PIN5	PORTD --> Keypad Column 2
		DIO_PIN_INPUT,     //PIN6	PORTD --> Keypad Column 1
		DIO_PIN_INPUT      //PIN7	PORTD --> Keypad Column 0

};

/*
 * Function: DIO_setPinDirection
 * Description:
 *     Sets the direction of a specific pin within a port group.
 * Parameters:
 *     - PortId: The identifier of the port group (e.g., DIO_PORTA).
 *     - PinId: The pin number within the group (e.g., DIO_PIN0).
 *     - PinDirection: The desired direction of the pin (input or output).
 * Returns: void
 */
void DIO_setPinDirection(u8 PortId, u8 PinId, u8 PinDirection)
{
	if((PortId<=3)&&(PinId<=7)&&((DIO_PIN_OUTPUT==PinDirection)||(DIO_PIN_INPUT==PinDirection)))
	{
		switch(PortId)
		{
		case DIO_PORTA:
			if(DIO_PIN_OUTPUT == PinDirection)
			{
				SET_BIT(DDRA,PinId);
			}
			else
			{
				CLR_BIT(DDRA,PinId);
			}
			break;

		case DIO_PORTB:
			if(DIO_PIN_OUTPUT == PinDirection)
			{
				SET_BIT(DDRB,PinId);
			}
			else
			{
				CLR_BIT(DDRB,PinId);
			}
			break;

		case DIO_PORTC:
			if(DIO_PIN_OUTPUT == PinDirection)
			{
				SET_BIT(DDRC,PinId);
			}
			else
			{
				CLR_BIT(DDRC,PinId);
			}
			break;

		case DIO_PORTD:
			if(DIO_PIN_OUTPUT == PinDirection)
			{
				SET_BIT(DDRD,PinId);
			}
			else
			{
				CLR_BIT(DDRD,PinId);
			}
			break;
		}
	}

	else
	{
		// Do Nothing
	}
}

/*
 * Function: DIO_setPinValue
 * Description:
 *     Sets the value of a specific pin if configured as output.
 * Parameters:
 *     - PortId: The identifier of the port group (e.g., DIO_PORTA).
 *     - PinId: The pin number within the group (e.g., DIO_PIN0).
 *     - PinValue: The desired output value (high or low).
 * Returns: void
 */
void DIO_setPinValue(u8 PortId, u8 PinId, u8 PinValue)
{
	switch(PortId)
	{
	case DIO_PORTA:
		if(DIO_PIN_HIGH == PinValue)
		{
			SET_BIT(PORTA,PinId);
		}
		else
		{
			CLR_BIT(PORTA,PinId);
		}
		break;

	case DIO_PORTB:
		if(DIO_PIN_HIGH == PinValue)
		{
			SET_BIT(PORTB,PinId);
		}
		else
		{
			CLR_BIT(PORTB,PinId);
		}
		break;

	case DIO_PORTC:
		if(DIO_PIN_HIGH == PinValue)
		{
			SET_BIT(PORTC,PinId);
		}
		else
		{
			CLR_BIT(PORTC,PinId);
		}
		break;

	case DIO_PORTD:
		if(DIO_PIN_HIGH == PinValue)
		{
			SET_BIT(PORTD,PinId);
		}
		else
		{
			CLR_BIT(PORTD,PinId);
		}
		break;
	}
}

/*
 * Function: DIO_getPinValue
 * Description:
 *     Reads the value of a specific pin within a port group.
 * Parameters:
 *     - PortId: The identifier of the port group (e.g., DIO_PORTA).
 *     - PinId: The pin number within the group (e.g., DIO_PIN0).
 *     - PinValue: Pointer to store the read value (high or low).
 * Returns: void
 */
void DIO_getPinValue(u8 PortId, u8 PinId, u8* PinValue)
{
	switch(PortId)
	{
	case DIO_PORTA:
		*PinValue = GET_BIT(PINA,PinId);
		break;

	case DIO_PORTB:
		*PinValue = GET_BIT(PINB,PinId);
		break;

	case DIO_PORTC:
		*PinValue = GET_BIT(PINC,PinId);
		break;

	case DIO_PORTD:
		*PinValue = GET_BIT(PIND,PinId);
		break;
	}
}

/*
 * Function: DIO_togglePinValue
 * Description:
 *     Toggles the value of a specific pin if configured as output.
 * Parameters:
 *     - PortId: The identifier of the port group (e.g., DIO_PORTA).
 *     - PinId: The pin number within the group (e.g., DIO_PIN0).
 * Returns: void
 */
void DIO_togglePinValue(u8 PortId, u8 PinId)
{
	switch(PortId)
	{
	case DIO_PORTA:
		TOG_BIT(PORTA,PinId);
		break;

	case DIO_PORTB:
		TOG_BIT(PORTB,PinId);
		break;

	case DIO_PORTC:
		TOG_BIT(PORTC,PinId);
		break;

	case DIO_PORTD:
		TOG_BIT(PORTD,PinId);
		break;
	}
}

/*
 * Function: DIO_activePinInPullUpResistance
 * Description:
 *     Activates the internal pull-up resistor of a specific pin.
 * Parameters:
 *     - PortId: The identifier of the port group (e.g., DIO_PORTA).
 *     - PinId: The pin number within the group (e.g., DIO_PIN0).
 * Returns: void
 */
void DIO_activePinInPullUpResistance(u8 PortId, u8 PinId)
{
	switch(PortId)
	{
	case DIO_PORTA:
		SET_BIT(PORTA,PinId);
		break;

	case DIO_PORTB:
		SET_BIT(PORTB,PinId);
		break;

	case DIO_PORTC:
		SET_BIT(PORTC,PinId);
		break;

	case DIO_PORTD:
		SET_BIT(PORTD,PinId);
		break;
	}
}


/* Function: DIO_setPortDirection
 *
 * Brief:
 *   Sets the direction of all pins in a specified port.
 *
 * Description:
 *   This function configures the data direction (input or output) of all pins in a given port.
 *   It is applicable to AVR ATmega32 microcontrollers.
 *
 * Parameters:
 *   PortId - An unsigned 8-bit integer representing the port identifier.
 *            Valid values are 0 to 3, corresponding to PORTA to PORTD.
 *   PortDirection - An unsigned 8-bit integer representing the desired direction for all pins.
 *                   Use DIO_PORT_OUTPUT for setting all pins as output, and DIO_PORT_INPUT for input.
 *
 * Returns:
 *   void - This function returns nothing.
 */
void DIO_setPortDirection(u8 PortId, u8 PortDirection)
{
	if((PortId<=3) && ((DIO_PORT_OUTPUT == PortDirection) || (DIO_PORT_INPUT == PortDirection)))
	{
		switch(PortId)
		{
		case 0:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRA = 0xff;
			}
			else
			{
				DDRA = 0x00;
			}
			break;

		case 1:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRB = 0xff;
			}
			else
			{
				DDRB = 0x00;
			}
			break;

		case 2:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRC = 0xff;
			}
			else
			{
				DDRC = 0x00;
			}
			break;

		case 3:
			if(DIO_PORT_OUTPUT == PortDirection)
			{
				DDRD = 0xff;
			}
			else
			{
				DDRD = 0x00;
			}
			break;
		}
	}
}

/* Function: DIO_setPortValue
 *
 * Brief:
 *   Sets the output values of all pins in a specified port.
 *
 * Description:
 *   This function writes high or low values to all pins of a specified port on AVR ATmega32 microcontrollers.
 *
 * Parameters:
 *   PortId - An unsigned 8-bit integer representing the port identifier (0 to 3 for PORTA to PORTD).
 *   PortValue - An unsigned 8-bit integer representing the value to be set for all pins in the port.
 *
 * Returns:
 *   void - This function returns nothing.
 */
void DIO_setPortValue(u8 PortId, u8 PortValue)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
		case 0:
			PORTA = PortValue;
			break;

		case 1:
			PORTB = PortValue;
			break;

		case 2:
			PORTC = PortValue;
			break;

		case 3:
			PORTD = PortValue;
			break;
		}
	}
}

/* Function: DIO_getPortValue
 *
 * Brief:
 *   Reads the input values from all pins of a specified port.
 *
 * Description:
 *   This function reads the current state (high or low) of all pins in a specified port.
 *   It's useful for reading the status of connected devices or sensors in one operation.
 *
 * Parameters:
 *   PortId - An unsigned 8-bit integer representing the port identifier.
 *   PortValue - A pointer to an unsigned 8-bit integer where the read values from the port will be stored.
 *
 * Returns:
 *   void - This function returns nothing.
 */
void DIO_getPortValue(u8 PortId, u8* PortValue)
{
	if((PortId<=3) && (PortValue != 0))
	{
		switch(PortId)
		{
		case 0:
			*PortValue = PINA;
			break;

		case 1:
			*PortValue = PINB;
			break;

		case 2:
			*PortValue = PINC;
			break;

		case 3:
			*PortValue = PIND;
			break;
		}
	}
}

/* Function: DIO_togglePortValue
 *
 * Brief:
 *   Toggles the output values of all pins in a specified port.
 *
 * Description:
 *   This function inverts the current state of all pins in a given port. If a pin is high, it becomes low, and vice versa.
 *   It can be used for blinking LEDs or toggling the state of output devices.
 *
 * Parameters:
 *   PortId - An unsigned 8-bit integer representing the port identifier.
 *
 * Returns:
 *   void - This function returns nothing.
 */
void DIO_togglePortValue(u8 PortId)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
		case 0:
			PORTA = ~PORTA;
			break;

		case 1:
			PORTB = ~PORTB;
			break;

		case 2:
			PORTC = ~PORTC;
			break;

		case 3:
			PORTD = ~PORTD;
			break;
		}
	}
}

/* Function: DIO_activePortInPullUpResistance
 *
 * Brief:
 *   Activates the internal pull-up resistors for all pins in a specified port.
 *
 * Description:
 *   This function enables the internal pull-up resistors for all pins of the specified port.
 *   It's commonly used when the pins are configured as input to avoid floating states.
 *
 * Parameters:
 *   PortId - An unsigned 8-bit integer representing the port identifier.
 *
 * Returns:
 *   void - This function returns nothing.
 */
void DIO_activePortInPullUpResistance(u8 PortId)
{
	if(PortId<=3)
	{
		switch(PortId)
		{
		case 0:
			PORTA = 0xff;
			break;

		case 1:
			PORTB = 0xff;
			break;

		case 2:
			PORTC = 0xff;
			break;

		case 3:
			PORTD = 0xff;
			break;
		}
	}
}

/* Function: DIO_setChannelDirection
 *
 * Brief:
 *   Sets the direction of a specific channel (pin).
 *
 * Description:
 *   This function configures the direction (input or output) of a specific channel, which is a pin number irrespective of its port group.
 *   It abstracts the concept of ports and pins, making it easier to work with individual pins.
 *
 * Parameters:
 *   ChannelId - A numeric identifier for the channel (ranging from 0 to 31, covering all pins of PORTA to PORTD).
 *   ChannelDirection - An unsigned 8-bit integer representing the desired direction for the channel.
 *
 * Returns:
 *   void - This function returns nothing.
 */
void DIO_setChannelDirection(Dio_CHANNEL_NUM ChannelId, u8 ChannelDirection)
{
	//channel 10 --> 10/8 = 1 --> group 1 or PORTB
	u8 Local_u8PortId = ChannelId/8;
	//10%8 = 2 --> pin 2 (group 1 or PORTB)
	u8 Local_u8PinId = ChannelId%8;
	DIO_setPinDirection(Local_u8PortId, Local_u8PinId, ChannelDirection);
}

/* Function: DIO_setChannelValue
 *
 * Brief:
 *   Sets the value of a specific channel (pin).
 *
 * Description:
 *   This function writes a high or low value to a specific channel. It is used for controlling devices connected to individual pins.
 *
 * Parameters:
 *   ChannelId - A numeric identifier for the channel.
 *   ChannelValue - An unsigned 8-bit integer representing the value to be set (high or low).
 *
 * Returns:
 *   void - This function returns nothing.
 */
void DIO_setChannelValue(Dio_CHANNEL_NUM ChannelId, u8 ChannelValue)
{
	//channel 10 --> 10/8 = 1 --> group 1 or PORTB
	u8 Local_u8PortId = ChannelId/8;
	//10%8 = 2 --> pin 2 (group 1 or PORTB)
	u8 Local_u8PinId = ChannelId%8;
	DIO_setPinValue(Local_u8PortId, Local_u8PinId, ChannelValue);
}

/* Function: DIO_getChannelValue
 *
 * Brief:
 *   Reads the value of a specified DIO channel.
 *
 * Description:
 *   This function retrieves the current value (HIGH or LOW) of a specified digital input/output channel.
 *   It is typically used to read the state of a digital input pin.
 *
 * Parameters:
 *   ChannelId - An identifier for the DIO channel (pin) to read from.
 *   ChannelValue - A pointer to a variable where the read value will be stored.
 *
 * Returns:
 *   void - This function does not return a value. The result is stored in the variable pointed to by ChannelValue.
 */
void DIO_getChannelValue(Dio_CHANNEL_NUM ChannelId, u8* ChannelValue)
{
	//channel 10 --> 10/8 = 1 --> group 1 or PORTB
	u8 Local_u8PortId = ChannelId/8;
	//10%8 = 2 --> pin 2 (group 1 or PORTB)
	u8 Local_u8PinId = ChannelId%8;
	DIO_getPinValue(Local_u8PortId, Local_u8PinId, ChannelValue);
}

/* Function: DIO_toggleChannelValue
 *
 * Brief:
 *   Toggles the value of a specified DIO channel.
 *
 * Description:
 *   This function inverts the current value of a specified DIO channel.
 *   If the pin is HIGH, it becomes LOW and vice versa. It is typically used with output pins.
 *
 * Parameters:
 *   ChannelId - An identifier for the DIO channel (pin) to toggle.
 *
 * Returns:
 *   void - This function does not return a value.
 */
void DIO_toggleChannelValue(Dio_CHANNEL_NUM ChannelId)
{
	//channel 10 --> 10/8 = 1 --> group 1 or PORTB
	u8 Local_u8PortId = ChannelId/8;
	//10%8 = 2 --> pin 2 (group 1 or PORTB)
	u8 Local_u8PinId = ChannelId%8;
	DIO_togglePinValue(Local_u8PortId, Local_u8PinId);
}

/* Function: DIO_activeChannelInPullUpResistance
 *
 * Brief:
 *   Activates the pull-up resistor for a specified DIO channel.
 *
 * Description:
 *   Enables the internal pull-up resistor for the specified DIO channel.
 *   This is useful when the channel is configured as an input to ensure a default HIGH state.
 *
 * Parameters:
 *   ChannelId - An identifier for the DIO channel (pin) where the pull-up resistor will be activated.
 *
 * Returns:
 *   void - This function does not return a value.
 */
void DIO_activeChannelInPullUpResistance(Dio_CHANNEL_NUM ChannelId)
{
	//channel 10 --> 10/8 = 1 --> group 1 or PORTB
	u8 Local_u8PortId = ChannelId/8;
	//10%8 = 2 --> pin 2 (group 1 or PORTB)
	u8 Local_u8PinId = ChannelId%8;
	DIO_activePinInPullUpResistance(Local_u8PortId, Local_u8PinId);
}

/* Function: DIO_initPinsConfig
 *
 * Brief:
 *   Initializes all DIO pins according to a predefined configuration.
 *
 * Description:
 *   Configures the direction of all DIO pins based on a predefined array.
 *   This function should be called at the beginning of the program to set up the pin directions.
 *
 * Parameters:
 *   void - This function does not take any parameters.
 *
 * Returns:
 *   void - This function does not return a value.
 */
void DIO_initPinsConfig(void)
{
	u8 Local_PinCounter;
	for(Local_PinCounter = 0; Local_PinCounter < DIO_TOTAL_PINS; Local_PinCounter++)
	{
		DIO_setChannelDirection(Local_PinCounter, DIO_PinsConfigArray[Local_PinCounter]);
	}
}
