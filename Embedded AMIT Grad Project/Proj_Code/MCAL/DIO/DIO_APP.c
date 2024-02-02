///*
// * File: DIO_Test_Main.c
// *
// * Description:
// *     Test file for the Digital Input/Output (DIO) module on an AVR ATmega32
// *     engineering kit. This file demonstrates various test scenarios for LED
// *     control using the DIO driver, including direct port manipulation, individual
// *     pin control, channel mode operation, and configuration array initialization.
// *
// * Author: [Your Name]
// * Date: [Specify Date Here]
// */
//
///* AVR LIB */
//#include <util/delay.h>
//
///* UTILS_LIB */
//#include "../../UTIL_LIB/STD_TYPES.h"
//#include "../../UTIL_LIB/BIT_MATH.h"
//
///* MCAL */
//#include "../DIO/DIO_interface.h"
//#include "../DIO/DIO_private.h"
//
//int main(void) {
//
//    /*
//     * Test Set 1: Direct Port Manipulation
//     * Description:
//     *     This test uses direct port manipulation to control LEDs.
//     *     LEDs connected to PORTB and PORTA are turned on and off sequentially.
//     */
//    DDRB = 0b10000000;  // Set PB7 as output (Red LED)
//    DDRA = 0b01110000;  // Set PA4, PA5, PA6 as outputs (Green, Blue, Yellow LEDs)
//
//    PORTB = 0b10000000;  // Turn on Red LED
//    _delay_ms(1000);
//    PORTB = 0x00;        // Turn off Red LED
//    PORTA = 0b00010000;  // Turn on Green LED
//    _delay_ms(1000);
//    PORTA = 0b00100000;  // Turn on Blue LED
//    _delay_ms(1000);
//    PORTA = 0b01000000;  // Turn on Yellow LED
//    _delay_ms(1000);
//    PORTA = 0x00;        // Turn off all LEDs on PORTA
//    _delay_ms(1000);
//
//    /*
//     * Test Set 2: Individual Pin Control Using DIO Module
//     * Description:
//     *     This test uses the DIO module to control individual LED pins.
//     */
//    DIO_setPinDirection(DIO_PORTB, DIO_PIN7, DIO_PIN_OUTPUT);  // Red LED
//    DIO_setPinDirection(DIO_PORTA, DIO_PIN4, DIO_PIN_OUTPUT);  // Green LED
//    DIO_setPinDirection(DIO_PORTA, DIO_PIN5, DIO_PIN_OUTPUT);  // Blue LED
//    DIO_setPinDirection(DIO_PORTA, DIO_PIN6, DIO_PIN_OUTPUT);  // Yellow LED
//
//    DIO_setPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_HIGH);  // Turn on Red LED
//    _delay_ms(1000);
//    DIO_setPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_LOW);   // Turn off Red LED
//    DIO_setPinValue(DIO_PORTA, DIO_PIN4, DIO_PIN_HIGH);  // Turn on Green LED
//    _delay_ms(1000);
//    DIO_setPinValue(DIO_PORTA, DIO_PIN4, DIO_PIN_LOW);   // Turn off Green LED
//    DIO_setPinValue(DIO_PORTA, DIO_PIN5, DIO_PIN_HIGH);  // Turn on Blue LED
//    _delay_ms(1000);
//    DIO_setPinValue(DIO_PORTA, DIO_PIN5, DIO_PIN_LOW);   // Turn off Blue LED
//    DIO_setPinValue(DIO_PORTA, DIO_PIN6, DIO_PIN_HIGH);  // Turn on Yellow LED
//    _delay_ms(1000);
//    DIO_setPinValue(DIO_PORTA, DIO_PIN6, DIO_PIN_LOW);   // Turn off Yellow LED
//
//    /*
//     * Test Set 3: Channel Mode Operation
//     * Description:
//     *     This test uses channel mode for controlling LEDs.
//     */
//    DIO_setChannelDirection(Dio_PINB_7, DIO_PIN_OUTPUT);  // Red LED
//    DIO_setChannelDirection(Dio_PINA_4, DIO_PIN_OUTPUT);  // Green LED
//    DIO_setChannelDirection(Dio_PINA_5, DIO_PIN_OUTPUT);  // Blue LED
//    DIO_setChannelDirection(Dio_PINA_6, DIO_PIN_OUTPUT);  // Yellow LED
//
//    DIO_setChannelValue(Dio_PINB_7, DIO_PIN_HIGH);  // Turn on Red LED
//    _delay_ms(1000);
//    DIO_setChannelValue(Dio_PINB_7, DIO_PIN_LOW);   // Turn off Red LED
//    DIO_setChannelValue(Dio_PINA_4, DIO_PIN_HIGH);  // Turn on Green LED
//    _delay_ms(1000);
//
//    DIO_setChannelValue(Dio_PINA_4, DIO_PIN_HIGH); // Turn on Green LED
//    _delay_ms(1000);
//    DIO_setChannelValue(Dio_PINA_4, DIO_PIN_LOW);  // Turn off Green LED
//    DIO_setChannelValue(Dio_PINA_5, DIO_PIN_HIGH); // Turn on Blue LED
//    _delay_ms(1000);
//    DIO_setChannelValue(Dio_PINA_5, DIO_PIN_LOW);  // Turn off Blue LED
//    DIO_setChannelValue(Dio_PINA_6, DIO_PIN_HIGH); // Turn on Yellow LED
//    _delay_ms(1000);
//    DIO_setChannelValue(Dio_PINA_6, DIO_PIN_LOW);  // Turn off Yellow LED
//
//    /*
//     * Test Set 4: Initialization Using Configuration Array
//     * Description:
//     *     This test uses a configuration array to initialize all DIO pins.
//     *     The LEDs are controlled in a sequence similar to previous tests.
//     */
//    DIO_initPinsConfig(); // Initialize all pins as per configuration array
//
//    DIO_setPinValue(DIO_PORTB, DIO_PIN7, DIO_PIN_HIGH); // Turn on Red LED
//    _delay_ms(1000);
//    DIO_togglePinValue(DIO_PORTB, DIO_PIN7);            // Turn off Red LED
//    DIO_setPinValue(DIO_PORTA, DIO_PIN4, DIO_PIN_HIGH); // Turn on Green LED
//    _delay_ms(1000);
//    DIO_togglePinValue(DIO_PORTA, DIO_PIN4);            // Turn off Green LED
//    DIO_setPinValue(DIO_PORTA, DIO_PIN5, DIO_PIN_HIGH); // Turn on Blue LED
//    _delay_ms(1000);
//    DIO_togglePinValue(DIO_PORTA, DIO_PIN5);            // Turn off Blue LED
//    DIO_setPinValue(DIO_PORTA, DIO_PIN6, DIO_PIN_HIGH); // Turn on Yellow LED
//    _delay_ms(1000);
//    DIO_togglePinValue(DIO_PORTA, DIO_PIN6);            // Turn off Yellow LED
//
//    return 0;
//}
