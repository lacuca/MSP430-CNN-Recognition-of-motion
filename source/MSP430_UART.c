/*
 * MSP430_UART.c
 *
 *  Created on: 2013. 2. 23.
 *      Author: mcssol
 */


#include "MSP430_UART.h"

unsigned char UART_DATA[Queue_size];
unsigned char head_point=0;
unsigned char tail_point=0;

#define USB_PORT_OUT      P5OUT
#define USB_PORT_SEL      P5SEL
#define USB_PORT_DIR      P5DIR
#define USB_PORT_REN      P5REN
#define USB_PIN_TXD       0x40
#define USB_PIN_RXD       0x80

void Init_UCA1_UART(void)
{
	unsigned long UART_baudrate=9600;
	unsigned int tmp_UCA1BR;
	/* PORT SEL	*/
	// p5.7 p5.6 UART mode
	P5DIR |= USB_PIN_TXD;
	P5DIR &=~(USB_PIN_RXD);
	P5SEL |= USB_PIN_TXD + USB_PIN_RXD ;
	/*UART SETTING*/


	//	9600
	UCA1CTL1 |= UCSWRST;                      // **Put state machine in reset**
	UCA1CTL1 |= UCSSEL_1;                     // CLK = ACLK
//	UCA1CTL0 |= UCMSB;
	UCA1CTL0 &= ~UC7BIT;   					//8bit
	tmp_UCA1BR =(unsigned int)((float)ACLK_FREQ/(float)UART_baudrate);
	UCA1BR1=(unsigned char)((tmp_UCA1BR>>8)&(0xff));
	UCA1BR0=(unsigned char)((tmp_UCA1BR)&(0xff));
	UCA1MCTL |= UCBRS_3+UCBRF_0;              // Modulation UCBRSx=6, UCBRFx=0
	UCA1CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	UCA1IE |= UCRXIE;                         // Enable USCI_A1 RX interrupt

	UART_A1_msg("\r\nTest UART_int2msg\r\n");
	UART_int2msg(-3204);
	UART_A1_msg("\r\n");
	UART_int2msg(0);
	UART_A1_msg("\r\n");
	UART_int2msg(690020L);
	UART_A1_msg("\r\n");
}
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
	unsigned char tmp_data;
	P1OUT^=0x01;
  switch(__even_in_range(UCA1IV,4))
  {
  case 0:break;                             // Vector 0 - no interrupt
  case 2:                                   // Vector 2 - RXIFG
	tmp_data=UCA1RXBUF;
	UART_DATA[tail_point++]=tmp_data;
	if(tail_point>=Queue_size)
		tail_point=0;

	while (!(UCA1IFG&UCTXIFG));             // USCI_A1 TX buffer ready?
//	while (!((UCA1IFG&UCTXIFG) | !(UCA1STAT&UCBUSY) ));
	UCA1TXBUF = tmp_data;

	  break;
  case 4:break;                             // Vector 4 - TXIFG
  default: break;
  }
}



