/*
 * USER_DIO.h
 *
 *  Created on: 2013. 2. 11.
 *      Author: mcssol
 */

#ifndef USER_DIO_H_
#define USER_DIO_H_
#include "USER_TOP_HEADER.h"

void DELAY_CNT(unsigned int cnt_i);
void LED_toggle(void);
void LED_ON(void);
void LED_OFF(void);
void LED1_ON(void);
void LED1_OFF(void);
void LED2_ON(void);
void LED2_OFF(void);

extern void Init_DIO(void);
extern void LCD_ctrl(void);

extern unsigned char FlagSW1;
extern unsigned char FlagSW2;

//void LED_ctrl(void);

#endif /* USER_DIO_H_ */
