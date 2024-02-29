#include <stdint.h>
#include <stdlib.h>
#include <pic32mx.h>
#include "header.h"


int main(void) {
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

    //display_init();
    //init(); //from init.c file
    
	all_inits();

 	//int currentPage = 1;
    int firstRow = 0;
	display_update();
    //for testing leaderboard
    add_element(array, 4, "ABBA");
	add_element(array, 6, "SSSE");
	add_element(array, 7, "NEXT");
	add_element(array, 9, "BIZE");
	add_element(array, 1, "LAST");

	while(1)
	{		
        //display_string(0,"here");
        //PORTE=0b1111;
        if (currentPage==6){game();}
        navigation(currentPage);
        display_update();
	}

	return 0;
}
/*
if current page is not 6 we go to navigation
		if current page is 6:
			we call draw_grid to create grid and put it in the buffer //not called anymore
			we initialize timer (based on mode and difficulty)
			we set player1 active and enter game
			in game (in an infinite loop):
				we convert and draw current buffer
				if !timesup:
					if bullet !inAir:
						we poll buttons ->change angle / shoot (inAir=true)
					else:
						update bullet position, check edge, check target
						if target-hit: remove target from buffer & add score & reset inAir
						if edge: reset inAir
				else: reset active player, wait a little, set other player active

->for checking size: we do it in the buffer: without counting, move to the top of the target , 
then with counting move until end score = 4-count -> size 3 is 1 point, size 1 is 3


user_isr: called 10 times every second by timer interrupt
count++
if (count!=10) return; -> we initialize it before starting timer in the beginning of player_turn
reset flag
if one of the players are active:
	LEDS--
if LEDS = 0:
	we need to let the game know through a variable (timesup=1)
	stop timer (we need to restart it at beginning of others turn and set value on LEDS back to original)
*/
