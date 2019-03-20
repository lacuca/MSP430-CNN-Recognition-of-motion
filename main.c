
#include "USER_TOP_HEADER.h"
void Init_system(void);

int xm=40;
int ym=50;
int xm_temp=0;
int ym_temp=0;
int tmp_circle[21][21],i,j;

void main(void)
{
	Init_system();

//	/*
//	Print_Character('a', 0, 0, 1, 0);
//	Print_Character('b', 20, 20, 2, 0);
//	Print_Character('c', 50, 50, 3, 0);
//	Print_Character('d', 90, 50, 4, 0);
//	*/
	while(1)
	{
		//MENU_UART();
	}
}
void Init_system(void)
{
	WDTCTL = WDTPW + WDTHOLD;		// Stop watchdog timer
	Init_DIO();
	Init_UCS();
	Init_ADC();

	Init_TimerA1(10);// 1ms * n

	Init_UCA1_UART();

	Init_LCD();
	LcdClear();

	Init_weights();

//	Create_Circle_template(10);
//	DRAW_TAMLATE(CIRCLE_TEMPLATE,50,50,10*2+1,10*2+1);

	__bis_SR_register(LPM0_bits + GIE);       // Enter LPM0, enable interrupts
//	__bis_SR_register(GIE);       // enable interrupts

}

