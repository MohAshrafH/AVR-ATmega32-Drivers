/*
 * LCD_config.h
 *
 *  Created on: Jul 23, 2023
 *      Author: Kareem Hussein
 */

#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/* Macros For Rs configuration */
/*
 * RS --> Register Select(0:Command , 1:Data)
 * 0 to send command and 1 to read/write data
 */
#define LCD_RS_PORT           DIO_PORTA
#define LCD_RS_PIN            DIO_PIN3

/* Macros For En configuration */
/*
 *Enable signal:
 *		1 to read data
 *		0 to write data
 */
#define LCD_E_PORT           DIO_PORTA
#define LCD_E_PIN            DIO_PIN2 


/* 4 Bit Mode Pins Configurtion */
/*
 *4 bits used to send data or commands
 */
#define LCD_D4_PIN            DIO_PIN0
#define LCD_D4_PORT           DIO_PORTB
							  
#define LCD_D5_PIN            DIO_PIN1
#define LCD_D5_PORT           DIO_PORTB
							  
#define LCD_D6_PIN            DIO_PIN2
#define LCD_D6_PORT           DIO_PORTB
							  
#define LCD_D7_PIN            DIO_PIN4
#define LCD_D7_PORT           DIO_PORTB


#endif /* LCD_CONFIG_H_ */
