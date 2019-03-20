/*
 * USER_LCD.C
 *
 *  Created on: 2013. 2. 22.
 *      Author: mcssol
 */


#include "USER_LCD.h"
#include <math.h>

int CIRCLE_TEMPLATE[41*41];

void DrawLine( int r1, int c1, int r2, int c2, int Glayscale)
{
	int r,c,dr,dc, temp;

    if (r1 == r2 && c1 == c2)  // Line of zero length.
		return;

	// Is line more horizontal than vertical?
    if (abs(r2 - r1) < abs(c2 - c1)) {
		// Put points in increasing order by column.
		if (c1 > c2) {
			temp = r1; r1 = r2; r2 = temp;
			temp = c1; c1 = c2; c2 = temp;
		}
		dr = r2 - r1;
		dc = c2 - c1;
		for (c=c1; c<=c2; c++) {
			r = r1 + (c - c1) * dr / dc;
			LcdPixel(c, r, Glayscale);//0~137, 0~109, 0~3

		}
	} else {
		if (r1 > r2) {
			temp = r1; r1 = r2; r2 = temp;
			temp = c1; c1 = c2; c2 = temp;
		}
		dr = r2 - r1;
		dc = c2 - c1;
		for (r=r1; r<=r2; r++) {
			c = c1 + (r - r1) * dc / dr;
			LcdPixel(c, r, Glayscale);//0~137, 0~109, 0~3
		}
	}
}


/*
void DrawCircle(int c_m, int r_m, int radius, int Glayscale)
{

	int tmp_r_sq;
	int tmp_r_sqP1;
	int tmp;
	int c_p,r_p;

	tmp_r_sq=radius*radius;
	tmp_r_sqP1=(int)(radius+1)*(radius+1);
//	tmp_r_sqM1=(radius-1)*(radius+0.9f);
	for(c_p=(c_m-radius);c_p<=(c_m+radius);c_p++)
	{
		for(r_p=(r_m-radius);r_p<=(r_m+radius);r_p++)
		{
			tmp=(c_p-c_m)*(c_p-c_m)+(r_p-r_m)*(r_p-r_m);

			if((tmp>=tmp_r_sq)&&(tmp<tmp_r_sqP1))
				LcdPixel(c_p, r_p, Glayscale);//0~137, 0~109, 0~3
			else if(tmp<tmp_r_sq)
				LcdPixel(c_p, r_p, Glayscale-1);//0~137, 0~109, 0~3
		}
	}
}
*/


void Create_Circle_template(int radius)
{
	int c_m;//=20;
	int r_m;//=20;
//	int tmp_Glayscale=3;
	int tmp_r_sq;
	int tmp_r_sqP1;
	int tmp;
	int c_p,r_p;
	int tmp_2;

	c_m=radius;
	r_m=radius;
	tmp_2=radius*2+1;
	for(c_p=0;c_p<(tmp_2*tmp_2);c_p++)
		CIRCLE_TEMPLATE[c_p]=0;

	tmp_r_sq=radius*radius;
	tmp_r_sqP1=(int)(radius+1)*(radius+1);

	for(c_p=(c_m-radius);c_p<=(c_m+radius);c_p++)
	{
		for(r_p=(r_m-radius);r_p<=(r_m+radius);r_p++)
		{
			tmp=(c_p-c_m)*(c_p-c_m)+(r_p-r_m)*(r_p-r_m);

			if((tmp>=tmp_r_sq)&&(tmp<tmp_r_sqP1))
				CIRCLE_TEMPLATE[c_p+r_p*tmp_2]=3;//(c_p, r_p, Glayscale);//0~137, 0~109, 0~3
			else if(tmp<tmp_r_sq)
				CIRCLE_TEMPLATE[c_p+r_p*tmp_2]=1;
		}
	}

}
//#define LCD_ROW                 110
//#define LCD_COL                 138

void DRAW_TAMLATE(int* Tamplate,int start_pixel_c, int start_pixel_r,  int Row_length,int Col_length)
{
	int tmp_i=0,tmp_j=0;
	int tmp_c,tmp_r;

	tmp_c=start_pixel_c;
	tmp_r=start_pixel_r;
//if((tmp_c>=0)&&(tmp_c<=LCD_COL-Col_length)&&(tmp_r>=0)&&(tmp_r<=LCD_ROW-Row_length))
{
	for(tmp_i=0;tmp_i<Col_length;tmp_i++)
	{
		for(tmp_j=0;tmp_j<Row_length;tmp_j++)
		{

			if(Tamplate[tmp_i+tmp_j*Col_length]>0)
			LcdPixel(tmp_c, tmp_r, Tamplate[tmp_i+tmp_j*Col_length]);//0~137, 0~109, 0~3

			tmp_c++;
		}
		tmp_c=start_pixel_c;
		tmp_r++;
	}
}
}

void DEL_LAYER(int start_pixel_c, int start_pixel_r, int Col_length, int Row_length)
{
	int tmp_i=0,tmp_j=0;
	int tmp_c,tmp_r;

	tmp_c=start_pixel_c;
	tmp_r=start_pixel_r;

	for(tmp_i=0;tmp_i<Row_length;tmp_i++)
	{
		for(tmp_j=0;tmp_j<Col_length;tmp_j++)
		{

			LcdPixel(tmp_c, tmp_r, 0);//0~137, 0~109, 0~3

			tmp_c++;
		}
		tmp_c=start_pixel_c;
		tmp_r++;
	}
}

void Print_Char(unsigned char ascii_char, int col, int row)
{
	unsigned int LookUpChar,tmp_LookUpChar;
	unsigned int tmp_data,tmp_data2;
	int tmp_i,tmp_j;


    LookUpChar = fonts_lookup[ascii_char];
    tmp_LookUpChar= LookUpChar*(FONT_HEIGHT);
	for(tmp_j=0;tmp_j<FONT_HEIGHT;tmp_j++)
	{
		tmp_data=fonts[tmp_LookUpChar+tmp_j];
		for(tmp_i=0;tmp_i<8;tmp_i++)
		{
			tmp_data2=(tmp_data>>((tmp_i)*2))&(0x3);
			LcdPixel(col+tmp_i, row+tmp_j,tmp_data2);
		}

	}

}
void Print_Character(unsigned char ascii_char, int col, int row,int font_size,int reverse_state)
{
	unsigned int LookUpChar,tmp_LookUpChar;
	unsigned int tmp_data,tmp_data2;
	int tmp_i,tmp_j,tmp_k,tmp_l;
	int tmp_kk,tmp_ll;

    LookUpChar = fonts_lookup[ascii_char];
    tmp_LookUpChar= LookUpChar*(FONT_HEIGHT);
	for(tmp_j=0;tmp_j<FONT_HEIGHT;tmp_j++)
	{
		tmp_data=fonts[tmp_LookUpChar+tmp_j];
		for(tmp_i=0;tmp_i<8;tmp_i++)
		{
			tmp_data2=(tmp_data>>((tmp_i)*2))&(0x3);
			tmp_kk=(tmp_i+1)*font_size;
			tmp_ll=(tmp_j+1)*font_size;
			for(tmp_k=tmp_i*font_size;tmp_k<tmp_kk;tmp_k++)
				for(tmp_l=tmp_j*font_size;tmp_l<tmp_ll;tmp_l++)
					if(reverse_state==0)
						LcdPixel(col+tmp_k, row+tmp_l,tmp_data2);
					else
						LcdPixel(col+tmp_k, row+tmp_l,3-tmp_data2);
		}

	}
}

