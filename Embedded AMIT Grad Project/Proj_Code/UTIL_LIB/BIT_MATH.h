/*
 * File: BIT_MATH.h
 * Author:
 *
 * Description:
 *     This header file defines a set of macros for common bit manipulation
 *     operations. These macros simplify the process of setting, clearing,
 *     toggling, and reading individual bits within registers, enhancing
 *     code readability and maintainability.
 */
 
#ifndef BIT_MATH_H_
#define BIT_MATH_H_

/*
 * Macro: SET_BIT
 * Sets a specific bit in a register.
 *
 * Parameters:
 * REG - Register to modify.
 * BIT_NUM - Bit number to set (0-indexed).
 */
#define SET_BIT(REG,BIT_NUM)    (REG |= (1U << (BIT_NUM)))

/*
 * Macro: CLR_BIT
 * Clears a specific bit in a register.
 *
 * Parameters:
 * REG - Register to modify.
 * BIT_NUM - Bit number to clear (0-indexed).
 */
#define CLR_BIT(REG,BIT_NUM)    (REG &= (~(1U << (BIT_NUM))))

/*
 * Macro: TOG_BIT
 * Toggles a specific bit in a register.
 *
 * Parameters:
 * REG - Register to modify.
 * BIT_NUM - Bit number to toggle (0-indexed).
 */
#define TOG_BIT(REG,BIT_NUM)    (REG ^= (1U << (BIT_NUM)))

/*
 * Macro: GET_BIT
 * Reads a specific bit from a register.
 *
 * Parameters:
 * REG - Register to read from.
 * BIT_NUM - Bit number to read (0-indexed).
 *
 * Returns:
 * The value of the specified bit in the register.
 */
#define GET_BIT(REG,BIT_NUM)    (((REG) >> (BIT_NUM)) & 1U)

#endif /* BIT_MATH_H_ */
