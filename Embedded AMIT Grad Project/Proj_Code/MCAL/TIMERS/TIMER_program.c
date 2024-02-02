/*
 * TIMER_program.c
 *
 *  Created on: Nov 8, 2023
 *      Author: elara
 */

#include "avr/io.h"
#include "avr/interrupt.h"
#include "../../UTIL_LIB/STD_TYPES.h"
#include "../../UTIL_LIB/BIT_MATH.h"
#include "./TIMER_config.h"
#include "./TIMER_interface.h"
#include "./TIMER_private.h"

static void (*TIMER0_CallBack)(void) = NULL;
static void (*TIMER1_CallBack)(void) = NULL;

void TIMER0_voidInitialize(void) {
    // Timer0 initialization code...
}

void TIMER1_voidInitialize(void) {
    // Configure Timer1 for CTC mode
    CLR_BIT(TCCR1B, 3);  // WGM12
    CLR_BIT(TCCR1A, 0);  // WGM10
    CLR_BIT(TCCR1A, 1);  // WGM11

    // Prescaler = F_CPU/1024
    SET_BIT(TCCR1B, 2);
    CLR_BIT(TCCR1B, 1);
    SET_BIT(TCCR1B, 0);

    // Set the OCR1A value for a 100ms interval at 8MHz Clock after prescaling
    // For 100ms: OCR1A = (Timer Clock Frequency / Prescaler * Desired Time) - 1
    // OCR1A = (8e6 / 1024 * 0.1) - 1 = 7811.25 ~ 7811
    OCR1A = 7811;

    // Enable Timer1 compare match interrupt
    SET_BIT(TIMSK, OCIE1A);
}

void TIMER0_voidSetInterval_100ms(void (*Copy_ptr)(void)) {
    // Set the callback function for Timer0
    TIMER0_CallBack = Copy_ptr;
}

void TIMER1_voidSetInterval_100ms(void (*Copy_ptr)(void)) {
    // Set the callback function for Timer1
    TIMER1_CallBack = Copy_ptr;
}

void TIMER0_voidStopTimer(void) {
    // Stop Timer0 by clearing the prescaler bits...
}

void TIMER1_voidStopTimer(void) {
    // Stop Timer1 by clearing the prescaler bits
    CLR_BIT(TCCR1B, 0);
    CLR_BIT(TCCR1B, 1);
    CLR_BIT(TCCR1B, 2);
}

// ISR for Timer0 Compare Match (if using GCC)
ISR(TIMER0_COMP_vect) {
    if(TIMER0_CallBack != NULL) {
        TIMER0_CallBack();
    }
}

// ISR for Timer1 Compare Match A (if using GCC)
ISR(TIMER1_COMPA_vect) {
    if(TIMER1_CallBack != NULL) {
        TIMER1_CallBack();
    }
}
