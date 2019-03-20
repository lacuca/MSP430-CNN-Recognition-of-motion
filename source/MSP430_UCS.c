/*
 * USER_UCS.c
 *
 *  Created on: 2013. 2. 13.
 *      Author: mcssol
 */




#include "MSP430_UCS.h"



void Init_UCS(void)
{
	  int FLLN =256*2;//SMCLK = 8388608*2

	  P11DIR |= 0x07;                           // ACLK, MCLK, SMCLK set out to pins
	  P11SEL |= 0x07;                           // P11.0,1,2 for debugging purposes.

	  UCSCTL3 |= SELREF_2;                      // Set DCO FLL reference = REFO
	  UCSCTL4 |= SELA_2;

	  __bis_SR_register(SCG0);                  // Disable the FLL control loop
	  UCSCTL0 = 0x0000;                         // Set lowest possible DCOx, MODx
	  UCSCTL1 = DCORSEL_5;                      // Select DCO range 16MHz operation
	  UCSCTL2 = FLLD_1 + FLLN-1;                // Set DCO Multiplier for 8MHz
	                                            // (N + 1) * FLLRef = Fdco
	                                            // (249 + 1) * 32768 = 8MHz
	                                            // Set FLL Div = fDCOCLK/2
	  __bic_SR_register(SCG0);                  // Enable the FLL control loop
	  __delay_cycles(250000);
	  do
	  {
	    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG);
	                                            // Clear XT2,XT1,DCO fault flags
	    SFRIFG1 &= ~OFIFG;                      // Clear fault flags
	  }while (SFRIFG1&OFIFG);                   // Test oscillator fault flag


}
