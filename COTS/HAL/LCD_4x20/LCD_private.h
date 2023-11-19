/*
 * File: LCD_private.h
 *
 * Description:
 *     Private header file for the LCD (Liquid Crystal Display) driver.
 *     This file contains private function prototypes and internal definitions
 *     used by the LCD driver. The functions and definitions declared here are
 *     intended for internal use within the LCD driver module and are not
 *     exposed to other modules or applications. The primary purpose of this
 *     file is to support and facilitate the functionalities of the public
 *     interface of the LCD driver.
 *
 * Author: [Your Name]
 * Date: [Date of Creation or Modification]
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

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
static void private_voidWriteHalfPort(u8 copy_u8Value);

#endif /* LCD_PRIVATE_H_ */
