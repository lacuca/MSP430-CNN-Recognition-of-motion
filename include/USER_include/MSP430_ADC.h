/*
 * MSP430_ADC.h
 *
 *  Created on: 2013. 2. 28.
 *      Author: mcssol
 */

#ifndef MSP430_ADC_H_
#define MSP430_ADC_H_

#include "USER_TOP_HEADER.h"

#define Num_of_Results 10
extern volatile unsigned int A1results[Num_of_Results];
extern volatile unsigned int A2results[Num_of_Results];
extern volatile unsigned int A3results[Num_of_Results];

extern void Init_ADC(void);

#endif /* MSP430_ADC_H_ */
