void display_image(int x, const uint8_t *data);
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);

char * itoaconv( int num );

void quicksleep(int cyc);
void tick( unsigned int * timep );
void display_debug( volatile int * const addr );
extern const uint8_t const font[128*8];
extern const uint8_t const icon[128];
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
//struct node* leaderboard_init(void);
void set_score(int score);
void show_leaderboard(void);


struct node{
    int score;
    char* initials;
    struct node* next;
    struct node* prev;
};

// Game
void game_setup();
void build_targets_grid(int difficulty);
void player_turn(int playerId);


/* VARIABLES*/
extern int currentPage;
extern int difficultyLevel;
extern int numberOfPlayers;
//extern int[?][?] targetsGrid;
extern int activePlayerId;


