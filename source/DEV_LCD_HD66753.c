/*
 * DEV_LCD_HD66753.c
 *
 *  Created on: 2013. 2. 21.
 *      Author: mcssol
 *   ref : MSP-EXP430f5438 example code
 */

#include "USER_LCD.h"

unsigned int LcdAddress = 0, LcdTableAddress = 0;
unsigned int LCD_MEM[110 * 17];

		//This array stores a copy of all data on the LCD
unsigned char Draw_Block_Value_Macro[] = {0x74, 0x00, 0x12, 0x76, 0xFF, 0xFF};
unsigned char Draw_Block_Address_Macro[] = {0x74, 0x00, 0x11, 0x76, 0x00, 0x00};
unsigned char LcdInitMacro[] = {
    0x74, 0x00, 0x00, 0x76, 0x00, 0x01,            // R00 start oscillation
    0x74, 0x00, 0x01, 0x76, 0x00, 0x0D,            // R01 driver output control
    0x74, 0x00, 0x02, 0x76, 0x00, 0x4C,            // R02 LCD - driving waveform control
    0x74, 0x00, 0x03, 0x76, 0x12, 0x14,            // R03 Power control
    0x74, 0x00, 0x04, 0x76, 0x04, 0x66,            // R04 Contrast control
    0x74, 0x00, 0x05, 0x76, 0x00, 0x10,            // R05 Entry mode
    0x74, 0x00, 0x06, 0x76, 0x00, 0x00,            // R06 RAM data write mask
    0x74, 0x00, 0x07, 0x76, 0x00, 0x15,            // R07 Display control
    0x74, 0x00, 0x08, 0x76, 0x00, 0x03,            // R08 Cursor Control
    0x74, 0x00, 0x09, 0x76, 0x00, 0x00,            // R09 RAM data write mask
    0x74, 0x00, 0x0A, 0x76, 0x00, 0x15,            // R0A
    0x74, 0x00, 0x0B, 0x76, 0x00, 0x03,            // R0B Horizontal Cursor Position
    0x74, 0x00, 0x0C, 0x76, 0x00, 0x03,            // R0C Vertical Cursor Position
    0x74, 0x00, 0x0D, 0x76, 0x00, 0x00,            // R0D
    0x74, 0x00, 0x0E, 0x76, 0x00, 0x15,            // R0E
    0x74, 0x00, 0x0F, 0x76, 0x00, 0x03,            // R0F
    0x74, 0x00, 0x10, 0x76, 0x00, 0x15,            // R0E
    0x74, 0x00, 0x11, 0x76, 0x00, 0x03,            // R0F
};
#define LCD_RST 0x80
#define LCD_CS 0x40
#define LCD_CLK 0x08
#define LCD_SIMO 0x02
#define LCD_SOMI 0x04

void Init_LCD(void)
{
	/* Port SEL*/
	P9DIR |= LCD_RST | LCD_CS;//RST, CS
	P9OUT |= LCD_RST | LCD_CS;

	P9OUT &= ~(LCD_RST);
	__delay_cycles(0xffff);
	P9OUT |= LCD_RST ;	//RST

	P9SEL |= LCD_CLK + LCD_SIMO;//P9.3, P9.1 => SPI
	P9DIR |= LCD_CLK;

	P9DIR &=~(LCD_SOMI);	//MISO
	P9DIR |= LCD_SIMO;

    UCB2CTL1 = UCSWRST;                            // Hold USCI in SW reset mode while configuring
                                                   // it
    UCB2CTL0 = UCMST + UCSYNC + UCCKPL + UCMSB;    // 3-pin, 8-bit SPI master
    UCB2CTL1 |= UCSSEL_2;                          // SMCLK
    UCB2BR0 = 2;                                   // Note: Do not exceed D/S spec for UCLK!
    UCB2BR1 = 0;
    UCB2CTL1 &= ~UCSWRST;                          // Release USCI state machine
    UCB2IFG &= ~UCRXIFG;

    LcdActive();

    LcdSendCommand(&LcdInitMacro[1 * 6]);
    LcdSendCommand(&LcdInitMacro[2 * 6]);
    LcdSendCommand(&LcdInitMacro[4 * 6]);
    LcdSendCommand(&LcdInitMacro[5 * 6]);
    LcdSendCommand(&LcdInitMacro[6 * 6]);
    LcdSendCommand(&LcdInitMacro[7 * 6]);

    Init_backlight();


}


void LcdActive(void)
{
    LcdSendCommand(LcdInitMacro);         // R00 start oscillation

    // Wait a minimum of 10ms after issuing "start oscillation"
    // command (to accommodate for MCLK up to 8MHz)
    __delay_cycles(80000);

    LcdInitMacro[3 * 6 + 5] |= 0x04;
    LcdInitMacro[3 * 6 + 5] &= ~ (0x01) ;
    LcdSendCommand(&LcdInitMacro[3 * 6]); // R03 Power control
}
void LcdSendCommand(unsigned char Data[])
{
    unsigned char i;

    P9OUT &= ~LCD_CS;         //CS = 0 --> Start Transfer
    for (i = 0; i < 6; i++)
    {
        while (!(UCB2IFG & UCTXIFG)) ;             // Wait for TXIFG
        UCB2TXBUF = Data[i];                       // Load data

        if (i == 2)                                //Pull CS up after 3 bytes
        {
            while (UCB2STAT & UCBUSY) ;
            P9OUT |= LCD_CS;          //CS = 1 --> Stop Transfer
            P9OUT &=~LCD_CS;         //CS = 0 --> Start Transfer
        }
    }
    while (UCB2STAT & UCBUSY) ;
    P9OUT |= LCD_CS;                  //CS = 1 --> Stop Transfer
}
void LcdPixel(int x, int y, unsigned char GrayScale)//0~137, 0~109, 0~3
{
    unsigned int Address, Value;
    unsigned char offset;

    //Each line increments by 0x20
    if ((x >= 0) && (x < LCD_COL) && (y >= 0) && (y < LCD_ROW))//LCD_COL = 138, LCD_ROW = 110
    {
        Address = (y << 5) + (x >> 3);            // address = y*32+x/8 Narrow down to 8 possible pixels //

        Value = LCD_MEM[(y << 4) + y + (x >> 3)]; //y * 17 +x/8 --> row. x>>3 --> column

        offset = (x & 0x07) << 1;                 //3 LSBs = pos. within the 8 columns
        Value &= ~(3 << offset);                  //clear out the corresponding bits
        Value |= GrayScale << offset;             //set pixel to GrayScale level

        LcdDrawBlock(Address, Value);
    }
}


void LcdClear(void)
{
    int tmp_i, tmp_j, tmp_k, Current_Location = 0;

    LcdSetAddress(0);


    for (tmp_i = 0; tmp_i < 110; tmp_i++)
    {
        //prepare to send image
    	P9OUT &= ~LCD_CS;         //CS = 0 --> Start Transfer
        for (tmp_k = 0; tmp_k < 3; tmp_k++)
        {
            while (!(UCB2IFG & UCTXIFG)) ;         // Wait for TXIFG
            UCB2TXBUF = Draw_Block_Value_Macro[tmp_k]; // Load data
        }
        while (UCB2STAT & UCBUSY) ;
        P9OUT |= LCD_CS;          //CS = 1 --> Stop Transfer
        P9OUT &= ~LCD_CS;         //CS = 0 --> Start Transfer
        while (!(UCB2IFG & UCTXIFG)) ;             // Wait for TXIFG
        UCB2TXBUF = Draw_Block_Value_Macro[3];     // Load data

        //send blank line
        for (tmp_j = 0; tmp_j < 17; tmp_j++)
        {
            LCD_MEM[LcdTableAddress++] = 0x00;
            while (!(UCB2IFG & UCTXIFG)) ;         // Wait for TXIFG
            UCB2TXBUF = 0x00;                      // Load data
            while (!(UCB2IFG & UCTXIFG)) ;         // Wait for TXIFG
            UCB2TXBUF = 0x00;                      // Load data
        }
        //Clear the partially visible block at the edge of the screen
        while (!(UCB2IFG & UCTXIFG)) ;             // Wait for TXIFG
        UCB2TXBUF = 0x00;                          // Load data
        while (!(UCB2IFG & UCTXIFG)) ;             // Wait for TXIFG
        UCB2TXBUF = 0x00;                          // Load data
        while (UCB2STAT & UCBUSY) ;
        P9OUT |= LCD_CS;          //CS = 1 --> Stop Transfer

        Current_Location += 0x20;
        LcdSetAddress(Current_Location);
    }

    LcdSetAddress(0);
}

void LcdSetAddress(unsigned int Address)
{
	unsigned int temp;

    Draw_Block_Address_Macro[4] = Address >> 8;   //high byte
    Draw_Block_Address_Macro[5] = Address & 0xFF; //low byte
    LcdSendCommand(Draw_Block_Address_Macro);
    LcdAddress = Address;
    temp = Address >> 5;                     // Divided by 0x20
    temp = temp + (temp << 4);
    //Multiplied by (1+16) and added by the offset
    LcdTableAddress = temp + (Address & 0x1F);
}

void LcdDrawCurrentBlock(unsigned int Value)
{
   unsigned int temp;

    Draw_Block_Value_Macro[4] = Value >> 8;
    Draw_Block_Value_Macro[5] = Value & 0xFF;
    LCD_MEM[LcdTableAddress] = Value;

    LcdSendCommand(Draw_Block_Value_Macro);

    LcdAddress++;
    temp = LcdAddress >> 5;                 // Divided by 0x20
    temp = temp + (temp << 4);
    // Multiplied by (1+16) and added by the offset
    LcdTableAddress = temp + (LcdAddress & 0x1F);

    // If LcdAddress gets off the right edge, move to next line
    if ((LcdAddress & 0x1F) > 0x11)
        LcdSetAddress((LcdAddress & 0xFFE0) + 0x20);
    if (LcdAddress == LCD_Size)
        LcdSetAddress(0);
}



void LcdDrawBlock(unsigned int Address, unsigned int Value)
{
    LcdSetAddress(Address);
    LcdDrawCurrentBlock(Value);
}

void Init_backlight(void)
{
	Init_TimerA0_3_PWM(5);

}


