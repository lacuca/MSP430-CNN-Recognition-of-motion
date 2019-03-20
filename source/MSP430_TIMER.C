/*
 * USER_TIMER.C
 *
 *  Created on: 2013. 2. 12.
 *      Author: mcssol
 */
#include "MSP430_TIMER.h"
volatile unsigned int timer1_A0_global_cnt=0;

#define PI 3.141592f

extern unsigned int x;
extern unsigned int y;
extern unsigned int z;

long velocity[2][velocity_MAX];

void UART_out1(unsigned char a)
{
    while (!(UCA1IFG&UCTXIFG));             // USCI_A1 TX buffer ready?

    UCA1TXBUF = a;

}
void Init_TimerA1(unsigned long Timer_period_us)
{
	unsigned long tmp_cnt=0;

	tmp_cnt=(Timer_period_us*((float)ACLK_FREQ/(float)1000ul));
	if(tmp_cnt<=0)
		tmp_cnt=1;

//	TA1CTL =  TASSEL_2 + MC_1 + TACLR;    // SMCLK, upcount_mode, clear TAR
	TA1CTL =  TASSEL_1 + MC_1 + TACLR;		// ACLK

	TA1CCR0=tmp_cnt;
//	TA1CCR0=3276;
	TA1CCTL0 = CCIE ;                //CCR0 interrupt enabled

}

#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void)
{
	static unsigned flag=0;
	static int bias_x, bias_z, tail;
	static long v_x, v_z;
	int temp;
	int i, theta;
	float th_tmp;
	unsigned char quantum[velocity_MAX];

	timer1_A0_global_cnt++;

	if(!FlagSW1 && !flag)
	{
		v_x = 0;
		v_z = 0;
		bias_x = x;
		bias_z = z;
//		cnt = 0;
		tail = 0;
		flag = 1;
	}
	else if (!FlagSW1 && flag==1)
	{
		temp = (int)x - bias_x;
		if(temp<-60 || temp>60)
			v_x += temp;
		temp = (int)z - bias_z;
		if(temp<-60 || temp>60)
			v_z += temp;

		velocity[0][tail] = v_x;
		velocity[1][tail] = v_z;
		tail++;

		if(tail>=velocity_MAX)
		{
			flag = 2;
			P1OUT ^= 0x02;
		}
	}
	else if (FlagSW1 && flag)
	{
		flag = 0;

		for(i=0; i<tail; i++)
		{
			if(velocity[0][i] == 0 && velocity[1][i] == 0)
			{
				theta = 200;
			}
			else
			{
				th_tmp = atan2((float)velocity[1][i], (float)velocity[0][i]);
				th_tmp = th_tmp*57.3f;
				theta = (int)th_tmp;
			}
			if(theta == 200)
				quantum[i] = 0;
			else if(theta < -157 || theta > 157)
				quantum[i] = 1;
			else if(theta < -122)
				quantum[i] = 2;
			else if(theta < -67)
				quantum[i] = 3;
			else if(theta < -22)
				quantum[i] = 4;
			else if(theta < 23)
				quantum[i] = 5;
			else if(theta < 68)
				quantum[i] = 6;
			else if(theta < 113)
				quantum[i] = 7;
			else if(theta < 158)
				quantum[i] = 8;
		}
		for(i=tail; i<velocity_MAX; i++)
			quantum[i] = 0;

//		UART_velocity(tail);
		UART_quantum(quantum);
		RUN_CNN(quantum);
	}

	/*
	if(timer1_A0_global_cnt % 100 == 0)
	{
		P1OUT ^= 0x02;

		UART_out1('\r');
		UART_out1('X');//2090
		UART_out1(':');
		UART_out1((x/1000)+48);
		UART_out1(((x%1000)/100)+48);
		UART_out1(((x%100)/10)+48);
		UART_out1((x%10)+48);

		UART_out1('Y');//2054
		UART_out1(':');
		UART_out1((y/1000)+48);
		UART_out1(((y%1000)/100)+48);
		UART_out1(((y%100)/10)+48);
		UART_out1((y%10)+48);

		UART_out1('Z');//2454
		UART_out1(':');//2080
		UART_out1((z/1000)+48);
		UART_out1(((z%1000)/100)+48);
		UART_out1(((z%100)/10)+48);
		UART_out1((z%10)+48);
		UART_out1('\n');
	}
	*/

	/*
	int x_theta;
	int y_theta;
	float x_tmp;
	float y_tmp;
	float x1, y1;
	x_tmp = atan2((float)(x-2090.0f), (float)(z-2080.0f));
	y_tmp = atan2((float)(y-2054.0f), (float)(z-2080.0f));
	x1 = x_tmp*57.3f;
	y1 = y_tmp*57.3f;

	if (x1>0) x_theta = (int)x1;
	else x_theta = (int)(-x1);
	if (y1>0) y_theta = (int)y1;
	else y_theta = (int)(-y1);

	UART_out1('\r');
	UART_out1('X');//2091
	UART_out1(':');
	if (x1>0) UART_out1(' ');
	else UART_out1('-');
	UART_out1(((x_theta%100)/10)+48);
	UART_out1((x_theta%10)+48);
	UART_out1(' ');
	UART_out1(' ');
	UART_out1('Y');//2042
	UART_out1(':');
	if (y1>0) UART_out1(' ');
	else UART_out1('-');
	UART_out1(((y_theta%100)/10)+48);
	UART_out1((y_theta%10)+48);
	*/
}



void Init_TimerA0_3_PWM(unsigned int PWM_period_ms)
{
	unsigned int tmp_cnt=0;
	/* LCD PORT ENABLE************************/
	P8DIR|=0x08;
	P8SEL|=0x08;//SEL TIMER_A
	/****************************************/
	tmp_cnt=(PWM_period_ms*((float)ACLK_FREQ/(float)1000ul));

	TA0CTL=TASSEL_1+TACLR+MC_1;

	TA0CCR0=tmp_cnt;

	TA0CCR3=tmp_cnt>>1;
	TA0CCTL3=OUTMOD_3;
}

/*
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void)
{
		P1OUT ^= 0x02;                            // Toggle P1.0
}
*/
