#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "header.h"

int direction = 1;
float k = 0;

void reset_bullet(Bullet *b, Player *p)
{
  b->in_air = 0;
  b->target_hit = 0;
  b->x = (p->id == 1) ? 0 : 127;
  b->y = 16;
  k = p->y_top;
}

void player_turn(Bullet *b, Player *p)
{
  float deltaY = (p->y_top <16) ? p->y_top-16 : p->y_top;
  reset_bullet(b, p);
  if(!p->timer)//if there is still time
  {
    move_player(p);
      if (btn2() && !b->in_air)
      {
        b->in_air = 1;
        move_bullet(b, p, deltaY);
      }
  }
  else
  {
    b->in_air = 0;
    p->active = 0; //end of turn  
    delay(8000000); // wait a bit to give the chip to the other player
  }
}

void move_bullet(Bullet *b, Player *p, float deltaY)
{
  direction = (p->id == 1) ? 1 : -1; // go to the right if player 1 else go to the left
  k = deltaY/8;

  if (b->y <0 || b->y >128 || b->x >128) // edge collision
    reset_bullet(b, p);    

  if (b->target_hit)
  {
    p->score +=1; //quick score calculation : NEED TO MODIFY
    reset_bullet(b,p);
  }

  b->x = b->x + direction;
  b->y = b->y + k;
}

void move_player(Player *p)
{
  if (btn4() && (p->y_top) > 0)
  {
    p->y_top = (p->y_top) - 1;
  }
  else if (btn3() && (p->y_top) < 32)
  {
    p->y_top = (p->y_top) + 1;
  }
}

int btn4(void)
{
  return ((PORTD & 0x00000080) >> 7) & 0x1;
}

int btn3(void)
{
  return ((PORTD & 0x00000040) >> 6) & 0x1;
}

int btn2(void)
{
  return ((PORTD & 0x00000020) >> 5) & 0x1;
}

int btn1(void)
{
  return ((PORTF & 0x00000002) >> 1) & 0x1;
}
