/*
 * USER_TIMER.h
 *
 *  Created on: 2013. 2. 12.
 *      Author: mcssol
 */

#ifndef MSP430_TIMER_H_
#define MSP430_TIMER_H_

#include "USER_TOP_HEADER.h"

extern void Init_TimerA1(unsigned long Timer_period_us);
extern volatile unsigned int timer1_A0_global_cnt;
extern void TIMER1_A0_ISR(void);

extern void Init_TimerA0_3_PWM(unsigned int PWM_period_ms);

#define velocity_MAX 150
extern long velocity[2][velocity_MAX];

#endif /* USER_TIMER_H_ */
