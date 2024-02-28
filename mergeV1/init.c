#include <stdint.h>
#include <stdlib.h>
#include <pic32mx.h>
#include "header.h"

int currentPage = 1;
int numberOfPlayers = 0;
int difficultyLevel = 0;
int activePlayerId = 0;
Highscore array[9];

void all_inits(void)
{
    pins_init();
	display_init();
	timer_init();
	lead_init(array);
	enable_interrupt();
}

void pins_init(void)
{
    /*from sam's work*/
    /* Set up peripheral bus clock */
  OSCCON &= ~0x180000;
  OSCCON |= 0x080000;

  /* Set up output pins */
  AD1PCFG = 0xFFFF;
  ODCE = 0x0;
  TRISECLR = 0xFF;
  PORTE = 0x0;

  /* Output pins for display signals */
  PORTF = 0xFFFF;
  PORTG = (1 << 9);
  ODCF = 0x0;
  ODCG = 0x0;
  TRISFCLR = 0x70;
  TRISGCLR = 0x200;

  /* Set up input pins */
  TRISDSET = (1 << 8);
  TRISFSET = (1 << 1);

  /* Set up SPI as master */
  SPI2CON = 0;
  SPI2BRG = 4;

  /* Clear SPIROV*/
  SPI2STATCLR &= ~0x40;
  /* Set CKP = 1, MSTEN = 1; */
  SPI2CON |= 0x60;

  /* Turn on SPI */
  SPI2CONSET = 0x8000;

  // Set buttons as input
  TRISDSET = 0xE0;
  TRISFSET = 0x2;

  /*FROM LAB*/
  /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
	
	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
	
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 4;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
        SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
}

void timer_init(void){
    /*FROM SAM*/
    T2CON = 0;
    T2CONSET = (0x4 << 4);
    TMR2 = 0x0;
    PR2 = 0x7A12;
    IFSCLR(0) = 0x00000100;
    IECSET(0) = 0x00000100;
    IPC(2) = 0x5;
    T2CONSET = 0x8000;

    /*FROM LAB?*/
    //IO ports
    TRISECLR = 0xFF; //sets bits 7..0 of port E as output (LEDs)
    TRISDSET = 0xFE0; //set bits 11..5 of port D as inputs (BTN2-4 & switches)
    PORTFSET = 0x1; //set BTN1 as input

    //timer2
    T2CON = 0x70; //stop timer and clear control register, set prescale to 256:1
    TMR2 = 0x0; // clear timer register
    PR2 = 0x7A12; //period register = 80000000/(256*10)=31250
    //T2CONSET = 0x8000; // start timer
}

int get_btns(void)
{
    return (PORTD&0xE0)>>5;
}

int get_sw(void)
{
    return (PORTD&0xF00)>>8;
}

int get_exit(void)
{
	return (PORTF&0x2)>>1;
}