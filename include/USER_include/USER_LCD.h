/*
 * USER_LCD.h
 *
 *  Created on: 2013. 2. 21.
 *      Author: mcssol
 */

#ifndef USER_LCD_H_
#define USER_LCD_H_
#include "USER_TOP_HEADER.h"

extern const unsigned char fonts_lookup[];
extern const unsigned int fonts[];
extern unsigned char LcdInitMacro[] ;
extern void LcdSendCommand(unsigned char Data[]);
extern void Init_LCD(void);
extern void LcdActive(void);
extern void LcdSetAddress(unsigned int Address);
extern void LcdClear(void);
extern void LcdDrawBlock(unsigned int Address, unsigned int Value);
extern void LcdPixel(int col, int row, unsigned char GrayScale);
extern void Init_backlight(void);

#define FONT_HEIGHT             13                    // Each character has 13 lines

#define LCD_ROW                 110
#define LCD_COL                 138
#define LCD_Size 				3505 //109*32-1 + 18
#define LCD_MEM_Size            110 * 17
extern int* BASE_LAYER;//138*110



extern void Draw_polygon(int* col,int* row,int vertex_number);
extern void DrawLine( int r1, int c1, int r2, int c2, int color);
extern void Painting_triangle(int* col,int* row);
//extern void DrawCircle(int c_m, int r_m, int radius, int Glayscale);
extern int CIRCLE_TEMPLATE[41*41];
void DRAW_TAMLATE(int* Tamplate,int start_pixel_c, int start_pixel_r,  int Row_length,int Col_length);
void  DEL_LAYER(int start_pixel_c, int start_pixel_r, int Col_length, int Row_length);
void Create_Circle_template(int radius);

extern void Print_Char(unsigned char ascii_char, int x, int y);
extern void Print_Character(unsigned char ascii_char, int x, int y,int font_size,int reverse_state);

#endif /* USER_LCD_H_ */
