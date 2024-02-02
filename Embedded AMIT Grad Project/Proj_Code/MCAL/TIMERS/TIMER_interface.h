/*
 * TIMER_interface.h
 *
 *  Created on: Nov 8, 2023
 *      Author: elara
 */
#ifndef MCAL_TIMERS_TIMER_INTERFACE_H_
#define MCAL_TIMERS_TIMER_INTERFACE_H_

void TIMER0_voidInitialize(void);
void TIMER1_voidInitialize(void);

void TIMER0_voidSetInterval_100ms(void (*Copy_ptr)(void));
void TIMER1_voidSetInterval_100ms(void (*Copy_ptr)(void));

void TIMER0_voidStopTimer(void);
void TIMER1_voidStopTimer(void);

#endif /* MCAL_TIMERS_TIMER_INTERFACE_H_ */
