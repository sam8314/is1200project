typedef struct Player
{
    int id;
    float x;
    float y_top;
    int score;
    int timer; //CHANGE IT TO JUST INTERRUPT (unlinked to player)
    char active;
    int trajectory [128];
}Player;

typedef struct Bullet{
  float x; //of the bullet center
  float y; //of the bullet center
  char in_air;
  char target_hit;
}Bullet;

typedef struct Highscore{
    int score;
    char* initials;
}Highscore;

/*---------------------------------------------------------------------------------------------*/
/*FROM LAB*/


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
extern int timesup;

/*---------------------------------------------------------------------------------------------*/
/*FROM SAM's WORK*/

/*
The directly following defines were taken from the course's resources :
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

// inits
void pins_init(void);
void display_init(void);
void timer_init();
void init();

// inputs
int btn4(void);
int btn3(void);
int btn2(void);
int btn1(void);

//display
unsigned char display_buffer [128*8];
void draw_pixel(float x, float y);
void draw_bullet(Bullet * b);
void draw_player(Player * p);
void draw_score_timer(Player * p);
void draw_grid(void);
void clear_buffer(uint8_t *data);
void update_screen (uint8_t *data);

//game and movement
int game(void);
void move_bullet(Bullet *b, Player *p);
void reset_bullet(Bullet *b, Player *p);
void move_player(Player *p);
void get_trajectory(Player *p);
void get_rebound_trajectory(Player *p, int impactX, int impactY);



