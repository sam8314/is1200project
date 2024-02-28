void display_image(int x, uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

char * itoaconv( int num );

void quicksleep(int cyc);
void tick( unsigned int * timep );
void display_debug( volatile int * const addr );
extern const uint8_t const font[128*8];
extern uint8_t icon[128];
extern char textbuffer[4][16];
void delay(int);
void time2string( char *, int );


/*FONCTIONS*/

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

struct highscore{
    int score;
    char* initials;
};
extern struct highscore array[9];

void lead_init(struct highscore* array);
void add_element(struct highscore* array, int score, char* name);
void show_leaderboard(struct highscore* array, int buttons);
void write_help();
void lead_to_string(struct highscore high, char* string);
extern int firstRow;


// Game
void game_setup();
void build_targets_grid(int difficulty);
void player_turn(int playerId);


/* VARIABLES */
extern int currentPage;
extern int difficultyLevel;
extern int numberOfPlayers;
//extern int[?][?] targetsGrid;
extern int activePlayerId;

extern unsigned char display_buffer[];

typedef struct Player
{
    int id;
    float x;
    float y_top;
    int score;
    int timer;
    char active;
}Player;

extern Player p1,p2;

typedef struct Bullet{
  float x;
  float y;
  char in_air;
  char target_hit;
}Bullet;

extern Bullet b;