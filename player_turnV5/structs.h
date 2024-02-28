#ifndef STRUCTS_H
#define STRUCTS_H

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

#endif
