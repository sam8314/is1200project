#include <stdint.h>
#include <stdlib.h>
#include <pic32mx.h>
#include "mipslab.h"

int currentPage = 1;
int numberOfPlayers = 0;
int difficultyLevel = 0;
int activePlayerId = 0;

 struct node* head = NULL;

void init(void){

    //IO ports
    TRISECLR = 0xFF; //sets bits 7..0 of port E as output (LEDs)
    TRISDSET = 0xFE0; //set bits 11..5 of port D as inputs (BTN2-4 & switches)
    PORTFSET = 0x1; //set BTN1 as input

    //timer2
    T2CON = 0x70; //stop timer and clear control register, set prescale to 256:1
    TMR2 = 0x0; // clear timer register
    PR2 = 0x7A12; //period register = 80000000/(256*10)=31250
    //T2CONSET = 0x8000; // start timer

    int currentPage = 1;
    struct node* head = lead_init();
    int firstRow = 0;
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

void user_isr( void ) {

}