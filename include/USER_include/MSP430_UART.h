/*
 * MSP430_UART.h
 *
 *  Created on: 2013. 2. 23.
 *      Author: mcssol
 */

#ifndef MSP430_UART_H_
#define MSP430_UART_H_

#include "USER_TOP_HEADER.h"
extern void Init_UCA1_UART(void);

extern void UART_A1_msg(unsigned char * msg);
extern void UART_A1_xmit(unsigned char a);
extern void UART_int2msg(long n);
extern void UART_velocity(unsigned int tail);
extern void UART_quantum(unsigned char * quantum);

#define Queue_size	100
extern unsigned char UART_DATA[Queue_size];
extern unsigned char head_point;
extern unsigned char tail_point;

//extern unsigned char conv_ASCii_to_dec(unsigned char* ASCii_data,int data_num);//This function convert ASCii to DECIMAL(max : 999);
//extern unsigned char queue_data_out(void);
//extern void MENU_UART(void);
extern void USCI_A1_ISR(void);

extern int x_value[3];
extern int y_value[3];
#endif /* MSP430_UART_H_ */
