/*
 * File: LCD_config.h
 *
 * Description:
 *     Configuration header file for the LCD (Liquid Crystal Display) driver.
 *     This file contains the pin configuration macros for interfacing with
 *     the LCD in 4-bit mode. It defines the ports and pins used for the
 *     control lines (RS, E) and the data lines (D4, D5, D6, D7) of the LCD.
 *     The configuration is essential for the proper operation of the LCD
 *     with the AVR ATmega32 microcontroller.
 *
 * Author: [Your Name]
 * Date: [Date of Creation or Modification]
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* Macros For Register Select (RS) Configuration */
/*
 * RS (Register Select) Pin Configuration:
 *   RS is used to switch between command mode (0) and data mode (1).
 *   When RS is low (0), the LCD expects a command, and when RS is high (1),
 *   it expects data to display.
 */
#define LCD_RS_PORT           DIO_PORTA  // Port for RS
#define LCD_RS_PIN            DIO_PIN3   // Pin for RS

/* Macros For Enable (E) Signal Configuration */
/*
 * Enable (E) Signal Configuration:
 *   The Enable pin is used to latch information present at the data pins.
 *   A high-to-low pulse needs to be applied to this pin to process
 *   the data/command written to the data lines.
 */
#define LCD_E_PORT            DIO_PORTA  // Port for Enable
#define LCD_E_PIN             DIO_PIN2   // Pin for Enable

/* Macros For 4-Bit Mode Data Lines Configuration */
/*
 * Configuration for the data pins in 4-bit mode:
 *   In 4-bit mode, only four pins (D4, D5, D6, D7) are used for communication
 *   between the microcontroller and the LCD. These pins transfer data
 *   and commands to the LCD.
 */
#define LCD_D4_PIN            DIO_PIN0   // Pin for Data 4
#define LCD_D4_PORT           DIO_PORTB  // Port for Data 4

#define LCD_D5_PIN            DIO_PIN1   // Pin for Data 5
#define LCD_D5_PORT           DIO_PORTB  // Port for Data 5

#define LCD_D6_PIN            DIO_PIN2   // Pin for Data 6
#define LCD_D6_PORT           DIO_PORTB  // Port for Data 6

#define LCD_D7_PIN            DIO_PIN4   // Pin for Data 7
#define LCD_D7_PORT           DIO_PORTB  // Port for Data 7

#endif /* LCD_CONFIG_H_ */
