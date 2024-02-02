/*
 * File: DIO_interface.h
 *
 * Description:
 *     Header file for the Digital Input/Output (DIO) module for AVR ATmega32.
 *     It defines macros for pin identification, direction, and state, along with
 *     function prototypes for controlling and manipulating the DIO pins and ports.
 *
 * Author: Mohammad Ashraf
 * Date: [Specify Date Here]
 */

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

/* Macros for Pin Identification */
#define DIO_PIN0           0
#define DIO_PIN1           1
#define DIO_PIN2           2
#define DIO_PIN3           3
#define DIO_PIN4           4
#define DIO_PIN5           5
#define DIO_PIN6           6
#define DIO_PIN7           7

/* Macros for Pin Direction */
#define DIO_PIN_INPUT      0
#define DIO_PIN_OUTPUT     1

/* Macros for Pin State */
#define DIO_PIN_LOW        0
#define DIO_PIN_HIGH       1

/* Macro for Total Number of DIO Pins */
#define DIO_TOTAL_PINS     32

/* Macros for Port Identification */
#define DIO_PORTA          0
#define DIO_PORTB          1
#define DIO_PORTC          2
#define DIO_PORTD          3

/* Macros for Port Direction */
#define DIO_PORT_INPUT     0x00
#define DIO_PORT_OUTPUT    0xff

/* Macros for Port State */
#define DIO_PORT_LOW       0x00
#define DIO_PORT_HIGH      0xff

/* Enumeration for Channel Numbers */
typedef enum
{
    Dio_PINA_0, Dio_PINA_1, Dio_PINA_2, Dio_PINA_3,
    Dio_PINA_4, Dio_PINA_5, Dio_PINA_6, Dio_PINA_7,
    Dio_PINB_0, Dio_PINB_1, Dio_PINB_2, Dio_PINB_3,
    Dio_PINB_4, Dio_PINB_5, Dio_PINB_6, Dio_PINB_7,
    Dio_PINC_0, Dio_PINC_1, Dio_PINC_2, Dio_PINC_3,
    Dio_PINC_4, Dio_PINC_5, Dio_PINC_6, Dio_PINC_7,
    Dio_PIND_0, Dio_PIND_1, Dio_PIND_2, Dio_PIND_3,
    Dio_PIND_4, Dio_PIND_5, Dio_PIND_6, Dio_PIND_7
} Dio_CHANNEL_NUM;

/* Function Prototypes for Pin APIs */
void DIO_setPinDirection(u8 PortId, u8 PinId, u8 PinDirection);
void DIO_setPinValue(u8 PortId, u8 PinId, u8 PinValue);
void DIO_getPinValue(u8 PortId, u8 PinId, u8* PinValue);
void DIO_togglePinValue(u8 PortId, u8 PinId);
void DIO_activePinInPullUpResistance(u8 PortId, u8 PinId);

/* Function Prototypes for Port APIs */
void DIO_setPortDirection(u8 PortId, u8 PortDirection);
void DIO_setPortValue(u8 PortId, u8 PortValue);
void DIO_getPortValue(u8 PortId, u8* PortValue);
void DIO_togglePortValue(u8 PortId);
void DIO_activePortInPullUpResistance(u8 PortId);

/* Function Prototypes for Channel APIs */
void DIO_setChannelDirection(Dio_CHANNEL_NUM ChannelId, u8 ChannelDirection);
void DIO_setChannelValue(Dio_CHANNEL_NUM ChannelId, u8 ChannelValue);
void DIO_getChannelValue(Dio_CHANNEL_NUM ChannelId, u8* ChannelValue);
void DIO_toggleChannelValue(Dio_CHANNEL_NUM ChannelId);
void DIO_activeChannelInPullUpResistance(Dio_CHANNEL_NUM ChannelId);

/* Function Prototype for Pins Configuration API */
void DIO_initPinsConfig(void);

#endif /* DIO_INTERFACE_H_ */
