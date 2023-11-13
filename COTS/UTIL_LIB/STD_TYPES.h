/*
 * File: STD_TYPES.h
 * Author:
 *
 * Description:
 *     This header file provides standard data types used throughout the
 *     project. It defines types for various standard integer widths and
 *     boolean values, enhancing portability and readability of the code.
 */


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Standard Unsigned Integer Types */
typedef unsigned char            u8;   /* Unsigned 8-bit integer */
typedef unsigned short int       u16;  /* Unsigned 16-bit integer */
typedef unsigned long int        u32;  /* Unsigned 32-bit integer */

/* Standard Signed Integer Types */
typedef signed char              s8;   /* Signed 8-bit integer */
typedef signed short int         s16;  /* Signed 16-bit integer */
typedef signed long int          s32;  /* Signed 32-bit integer */

/* Floating-point Types */
typedef float                    f32;  /* Single precision floating-point */
typedef double                   f64;  /* Double precision floating-point */

/* NULL Definition */
#ifndef NULL
    #define NULL                 0    /* Null pointer */
#endif

/* Boolean Data Type */
typedef u8                       bool; /* Boolean data type */

/* Boolean Values */
#ifndef TRUE
    #define TRUE                 1    /* Boolean true value */
#endif

#ifndef FALSE
    #define FALSE                0    /* Boolean false value */
#endif

#endif /* STD_TYPES_H_ */
