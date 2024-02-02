/*
 * LCD_private.h
 *
 *  Created on: Jul 23, 2023
 *      Author: Kareem Hussein
 */

#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

/*
 *This is a helper function used in LCD functions.
 *Static ensures privacy (locality) to header file
 */
static void private_voidWriteHalfPort(u8 copy_u8Value);


#endif /* LCD_PRIVATE_H_ */
