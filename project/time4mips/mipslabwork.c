/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x0; //initialize at zero
int timeouts = 0;
int prime = 1234567;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void ) {
  timeouts++;//assignement 3.e
  IFS(0)=0; //clear interrupt status flag

  if(timeouts==10) //assignement 3.f
  {
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    timeouts=0;
  }

  display_image(96, icon);

}
void labinit( void )
{
  volatile int * trisE = (volatile int *) 0xbf886100;
  *trisE = 0xFFFFFF00 & *trisE; //1.c : bits 7 through 0 of port E are set as output

  /*assignement 2.b*/
  T2CON = 0x70; //stop timer and clear control register, set prescale to 256:1
  TMR2 = 0x0; // clear timer register
  PR2 = 80000000/(256*10);/*period register = Fclk/Ftimer = Fclk/(prescale*Ftimer) = 80 MHz/(prescale*timer)*/

  TRISDSET = 0xFE0; //1.e set bits 11 through 5 of port D as inputs

  /*assignement 3.h*/
  IECSET(0) = 0x100; //enable interrupts
  IPC(2) = 0xC; //interrupt priority
  enable_interrupt(); //see labwork.S

  T2CONSET = 0x8000; //start timer

  return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();
}
