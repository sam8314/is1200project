#ifndef INIT_H
#define INIT_H
#include <stdint.h>
#include <stdio.h>
#include "structs.h"
#include "arrays.c"

void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
char * itoaconv( int num );
void labwork(void);
int nextprime( int inval );
void quicksleep(int cyc);
void tick( unsigned int * timep );
void display_debug( volatile int * const addr );

extern const uint8_t const font[128*8];
extern const uint8_t const icon[128];
extern char textbuffer[4][16];
void delay(int);
void time2string( char *, int );
void enable_interrupt(void);

//-------------------------
/*
These defines were taken from the course's resources :
https://github.com/is1200-example-projects/hello-display/blob/master/main.c

Copyright (c) 2015, Axel Isaksson

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

1. Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
3. The name of the author may not be used to endorse or promote products
derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/
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

extern int game(void);
extern void enable_interrupt();
extern void delay(int cyc);
extern void pins_init(void);
extern void display_init(void);
extern uint8_t spi_send_recv(uint8_t data);
extern void display_image(int x, const uint8_t *data);
extern void clear_buffer(uint8_t *data);
extern void move_bullet(Bullet *b, Player *p);
void get_trajectory(Player *p);
void get_rebound_trajectory(Player *p, int impactX, int impactY);
extern void reset_bullet(Bullet *b, Player *p);
extern void update_screen(uint8_t *data);
extern void draw_pixel(float x, float y);
extern void draw_bullet(Bullet * b);
extern void draw_player(Player * p);
extern void draw_score_timer(Player * p);
extern void draw_grid(void);
extern void timer_init();
extern void move_player(Player *p);
extern int btn4 (void);
extern int btn3 (void);
extern int btn2 (void);
extern int btn1 (void);
#endif