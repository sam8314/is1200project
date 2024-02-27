#ifndef INIT_H
#define INIT_H
#include <stdint.h>
#include <stdio.h>
#include "structs.h"
#include "arrays.c"

//FROM LAB3:
/* header.h
   Header file for all labs.
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

/* Declare display-related functions from mipslabfunc.c */
void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

/* Declare lab-related functions from mipslabfunc.c */
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );

/* Declare display_debug - a function to help debugging.

   After calling display_debug,
   the two middle lines of the display show
   an address and its current contents.

   There's one parameter: the address to read and display.

   Note: When you use this function, you should comment out any
   repeated calls to display_image; display_image overwrites
   about half of the digits shown by display_debug.
*/
void display_debug( volatile int * const addr );

/* Declare bitmap array containing font */
extern const uint8_t const font[128*8];
/* Declare bitmap array containing icon */
extern const uint8_t const icon[128];
/* Declare text buffer for display output */
extern char textbuffer[4][16];

/* Declare functions written by students.
   Note: Since we declare these functions here,
   students must define their functions with the exact types
   specified in the laboratory instructions. */
/* Written as part of asm lab: delay, time2string */
void delay(int);
void time2string( char *, int );
/* Written as part of i/o lab: getbtns, getsw, enable_interrupt */
int getbtns(void);
int getsw(void);
void enable_interrupt(void);

//-------------------------

#define DISPLAY_VDD PORTFbits.RF6
#define DISPLAY_VBATT PORTFbits.RF5
#define DISPLAY_COMMAND_DATA PORTFbits.RF4
#define DISPLAY_RESET PORTGbits.RG9
#define DISPLAY_VDD_PORT PORTF
#define DISPLAY_VDD_MASK 0x40
#define DISPLAY_VBATT_PORT PORTF
#define DISPLAY_VBATT_MASK 0x20
#define DISPLAY_COMMAND_DATA_PORT PORTF
#define DISPLAY_COMMAND_DATA_MASK 0x10
#define DISPLAY_RESET_PORT PORTG
#define DISPLAY_RESET_MASK 0x200

extern void enable_interrupt();
extern void delay(int cyc);
extern void pins_init(void);
extern void display_init(void);
extern uint8_t spi_send_recv(uint8_t data);
extern void display_image(int x, const uint8_t *data);
extern void clear_buffer(uint8_t *data);
extern void move_bullet(Bullet *b, Player *p);
extern void prepare_bullet(Bullet *b, Player *p);
void get_trajectory(Player *p);
extern void reset_bullet(Bullet *b, Player *p);
extern void update_screen (uint8_t *data);
extern void draw_bit (float x, float y);
extern void draw_bullet (Bullet * b);
extern void draw_player (Player * p);
extern void draw_score_timer (Player * p);
extern void draw_grid(void);
extern void timer_init();
extern void move_player(Player *p);
extern int btn4 (void);
extern int btn3 (void);
extern int btn2 (void);
extern int btn1 (void);
#endif
