/*
 * MSP430_ADC.c
 *
 *  Created on: 2013. 2. 28.
 *      Author: mcssol
 */

#include "MSP430_ADC.h"

volatile unsigned int A1results[Num_of_Results];
volatile unsigned int A2results[Num_of_Results];
volatile unsigned int A3results[Num_of_Results];

unsigned int x;
unsigned int y;
unsigned int z;

void Init_ADC(void)
{

	/* DIO PORT SEL*/
	P6SEL |=0x0e;
	P6DIR |=0x01;
	P6OUT |=0x01;
	/* ADC12 */
	ADC12CTL0=0;

	ADC12CTL0 |=ADC12ON+ADC12MSC;					//ADC12A_ON(0X0010), ADC12_MSC(0X0080)

	// S/H TIME
	ADC12CTL1 |= ADC12SHP;							//	(0X0200)

	/* ADC CLK */
	ADC12CTL1 |= ADC12SSEL_3+ADC12DIV_7;			//SMCLK, DIVIDE 8
	//SMCLK 16777216/8=>2_097_152Hz
	//ADC12CTL0 |=ADC12SHT0_15+ADC12SHT1_15;
	ADC12CTL1 |= ADC12CONSEQ_3; 					//ADC12 conversion sequence mode => Repeat sequence of channels
	ADC12CTL2 |= ADC12RES1+ADC12TCOFF;				//12bit resolution	; TEMPERATURE SENSOR OFF

	ADC12MCTL1 |=ADC12INCH_1;
	ADC12MCTL2 |=ADC12INCH_2;
	ADC12MCTL3 |=ADC12INCH_3+ADC12EOS;

	ADC12CTL0 |= ADC12TOVIE + ADC12OVIE ;			//CONV Timer Overflow interrupt enable ; MEM Overflow interrupt enable

	ADC12IE	= 0x08;									// ADC Interrupt ENABLE
	ADC12CTL0 |= ADC12ENC;					  		// enable conversion

	ADC12CTL0 |= ADC12SC;                     		// Start conversion - software trigger

}


#pragma vector=ADC12_VECTOR
__interrupt void ADC12ISR (void)
{
  static unsigned int index = 0;

  switch(__even_in_range(ADC12IV,34))
  {
  case  0: break;                           // Vector  0:  No interrupt
  case  2: break;                           // Vector  2:  ADC overflow
  case  4: break;                           // Vector  4:  ADC timing overflow
  case  6:
  	  	  break;                            // Vector  6:  ADC12IFG0
  case  8:
	  	  break;    						// Vector  8:  ADC12IFG1
  case 10:
	  	  break;     	                    // Vector 10:  ADC12IFG2
  case 12:
		A1results[index] = ADC12MEM1;           // Move A1 results, IFG is cleared
		A2results[index] = ADC12MEM2;         	// Move A2 results, IFG is cleared
		A3results[index] = ADC12MEM3;           // Move A3 results, IFG is cleared
		index++;                                // Increment results index, modulo; Set Breakpoint1 here
		if(index >=Num_of_Results) {
			index = 0;							// Reset index, Set breakpoint 2 here
			x = A1results[0];
			y = A2results[0];
			z = A3results[0];
		}
		break;                           	// Vector 12:  ADC12IFG3
  case 14:
	  break;                           		// Vector 14:  ADC12IFG4
  case 16: break;                           // Vector 16:  ADC12IFG5
  case 18: break;                           // Vector 18:  ADC12IFG6
  case 20: break;                           // Vector 20:  ADC12IFG7
  case 22: break;                           // Vector 22:  ADC12IFG8
  case 24: break;                           // Vector 24:  ADC12IFG9
  case 26: break;                           // Vector 26:  ADC12IFG10
  case 28: break;                           // Vector 28:  ADC12IFG11
  case 30: break;                           // Vector 30:  ADC12IFG12
  case 32: break;                           // Vector 32:  ADC12IFG13
  case 34: break;                           // Vector 34:  ADC12IFG14
  default: break;
  }
}



