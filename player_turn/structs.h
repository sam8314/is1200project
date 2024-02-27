#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Player
{
    int id;
    float x;
    float y_top;
    int score;
    int timer;
    char active;
}Player;

typedef struct Bullet{
  float x;
  float y;
  char in_air;
  char target_hit;
}Bullet;

#endif
