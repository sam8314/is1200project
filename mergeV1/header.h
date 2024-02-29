#ifndef INIT_H
#define INIT_H
#include <stdint.h>
#include <stdio.h>
#include "structs.h"


/*---------------------------------------------------------------------------------------------*/
/*FROM LAB*/

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

void display_image(int x, uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);

void quicksleep(int cyc);
void tick( unsigned int * timep );
void display_debug( volatile int * const addr );
extern const uint8_t const font[128*8];
extern uint8_t icon[128];
extern char textbuffer[4][16];
void delay(int);
void time2string( char *, int );

extern uint8_t spi_send_recv(uint8_t data);
char * itoaconv( int num );

/*---------------------------------------------------------------------------------------------*/
/*FROM OLD VERSION OF GAME*/

// IO
int get_btns(void);
int get_sw(void);
int get_exit(void);
void enable_interrupt(void);

// Menu
void navigation(int input);
void welcome_animation();
void home_menu(int buttons);
void select_difficulty(int buttons);
void rules(int buttons);

//Rules
void onePlayerRules(int buttons);
void twoPlayerRules(int buttons);

//Leaderboard
extern Highscore array[9];
void lead_init(Highscore* array);
void add_element(Highscore* array, int score, char* name);
void show_leaderboard(Highscore* array, int buttons);
void write_help();
void lead_to_string(Highscore high, char* string);
extern int firstRow;

// Game
//void build_targets_grid(int difficulty); WHERE WAS IT
extern int currentPage;
extern int difficultyLevel;
extern int numberOfPlayers;

/*---------------------------------------------------------------------------------------------*/
/*FROM SAM's WORK*/

/*need to check if we can do without those (used in pinss_init)*/
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

// inits
extern void pins_init(void);
extern void display_init(void);
extern void timer_init();

// inputs
extern int btn4(void);
extern int btn3(void);
extern int btn2(void);
extern int btn1(void);

//display
extern void draw_pixel(float x, float y);
extern void draw_bullet(Bullet * b);
extern void draw_player(Player * p);
extern void draw_score_timer(Player * p);
extern void draw_grid(void);
extern void clear_buffer(uint8_t *data);
extern void update_screen (uint8_t *data);

//game and movement
extern int game(void);
extern void move_bullet(Bullet *b, Player *p);
extern void reset_bullet(Bullet *b, Player *p);
extern void move_player(Player *p);
void get_trajectory(Player *p);
void get_rebound_trajectory(Player *p, int impactX, int impactY);



#endif