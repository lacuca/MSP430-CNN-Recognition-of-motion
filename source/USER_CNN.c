/*
 * USER_CNN.c
 *
 *  Created on: 2018. 5. 27.
 *      Author: mulik
 */

#include "USER_CNN.h"

matrix* IMG;

void RUN_CNN(unsigned char quantum[velocity_MAX])
{
	unsigned int i, j;
	double img[150][8];

	for(i=0; i<150; i++)
	{
		for(j=0; j<8; j++)
		{
			img[i][j] = 0;
		}
		if(quantum[i] != 0)
		{
			img[i][quantum[i]-1] = 1;
		}
	}

	IMG = matrix_new(150, 8);
	matrix_init(IMG, img);

	UART_A1_xmit('@');
	for(i=0; i<IMG->col; i++)
	{
		UART_int2msg(IMG->var[17][i]);
		UART_A1_xmit(' ');
	}

}
