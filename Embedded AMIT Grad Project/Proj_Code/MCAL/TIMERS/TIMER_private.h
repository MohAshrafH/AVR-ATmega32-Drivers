/*
 * TIMER_private.h
 *
 *  Created on: Nov 8, 2023
 *      Author: elara
 */

#ifndef MCAL_TIMERS_TIMER_PRIVATE_H_
#define MCAL_TIMERS_TIMER_PRIVATE_H_


// Timer0 Registers
#define TCCR0   *((volatile u8*)0x53)
#define TCNT0   *((volatile u8*)0x52)
#define OCR0    *((volatile u8*)0x5C)
#define TIMSK   *((volatile u8*)0x59)

// Timer1 Registers
#define TCCR1A  *((volatile u16*)0x4F)
#define TCCR1B  *((volatile u16*)0x4E)
#define TCNT1   *((volatile u16*)0x4C)
#define OCR1A   *((volatile u16*)0x4A)

// Timer Interrupt Masks
#define OCIE0   1   // Timer0 Output Compare Match Interrupt Enable
#define OCIE1A  4   // Timer1 Output Compare A Match Interrupt Enable

// Timer Prescalers
#define TIMER_PRESCALER_1024 5

#endif /* MCAL_TIMERS_TIMER_PRIVATE_H_ */
