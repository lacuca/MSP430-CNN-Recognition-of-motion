/*
 * USER_DIO.C
 *
 *  Created on: 2013. 2. 12.
 *      Author: mcssol
 */
#include "USER_DIO.h"

#define SW_HH	3
#define SW_HL 	2
#define SW_LH 	1
#define SW_LL	0

unsigned char FlagSW1 = 1;
unsigned char FlagSW2 = 1;

void Init_DIO(void)
{
	P1DIR |= 0x03;					//0,1
	P2DIR &= 0x01;					//6,7
	P1OUT |= 0x03;
	/*DIO PORT PULL UP */
	P2REN |=0xfe;
	P2OUT |=0xfe;
	/*DIO INTERRUPT SETTING*/
	P2IE |=0xfe;
	P2IES |=0xfe;
}

#pragma vector=PORT2_VECTOR
__interrupt void PORT2_ISR(void)
{
  switch(__even_in_range(P2IV,0x10))
  {
  case 0x0:break;                             // Vector 0 - no interrupt
  case 0x2:break;
  case 0x4://LEFT

	  break;
  case 0x6://RIGHT

	  break;
  case 0x8://SELECT

	  break;
  case 0xa://UP

	  break;                             // Vector 4 - TXIFG
  case 0xc://DOWN

	  break;
  case 0xe://SW1
	  P1OUT^=0x01;
	  FlagSW1 = P1OUT & 0x01;
	  break;
  case 0x10://SW2
	  P1OUT^=0x02;
	  FlagSW2 = (P1OUT & 0x02)>>1;
	  break;
  default: break;
  }
}

void LCD_ctrl(void)
{
	static unsigned char LCD_STATE=SW_HH, pre_state=SW_HH;
	LCD_STATE=(P2IN>>6)&(0x03);
/*	static int tmp_a=10,init_flag=0;

	if(init_flag==0)
	{
		init_flag=1;
		Create_Circle_template(tmp_a);
	}
*/
	switch(LCD_STATE)
	{
		case SW_HH:
			pre_state=SW_HH;
			break;
		case SW_HL :
			if(pre_state==SW_HH)
			{
		//		if(TA0CCR3>(TA0CCR0/10))
			//		TA0CCR3=TA0CCR3-TA0CCR0/10;
			//	 DrawCircle(50,50,10 ,3);

			}
			pre_state=SW_HL;
			break;
		case SW_LH :
			if(pre_state==SW_HH)
			{
			//	if(TA0CCR3<=(TA0CCR0*0.9))
			//		TA0CCR3=TA0CCR3+TA0CCR0/10;
			//	LcdClear();

			}
			pre_state=SW_LH;
			break;
		case SW_LL :
			pre_state=SW_LL;
			break;
		default :
			break;
	}
}
void LED_toggle(void)
{
	P1OUT ^= 0x01;
}
void LED_ON(void)
{
	P1OUT |= 0x03;
}
void LED_OFF(void)
{
	P1OUT &= 0xfc;
}
void LED1_ON(void)
{
	P1OUT |= 0x01;
}
void LED1_OFF(void)
{
	P1OUT &= 0xfe;
}
void LED2_ON(void)
{
	P1OUT |= 0x02;
}
void LED2_OFF(void)
{
	P1OUT  &= 0xfd;
}

void DELAY_CNT(unsigned int cnt_i)
{
	volatile unsigned int tmp_i=0;
	while((cnt_i>tmp_i))
	{
		tmp_i++;
	}
}

