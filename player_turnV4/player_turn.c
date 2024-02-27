#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "header.h"

int reflection = 1;

void reset_bullet(Bullet *b, Player *p)
{
  b->in_air = 0;
  b->target_hit = 0;
}

void get_trajectory(Player *p)
{
  int i;
  int distanceToMid;
  distanceToMid = p->y_top-16;
  int slope = distanceToMid/8;
  for(i=0;i<128;i++)
    p->trajectory[i]=16+i*slope;
}

void player_turn(Bullet *b, Player *p)
{
  reset_bullet(b, p);
  if(!(p->timer==0))//if there is still time
  {
    move_player(p);
    if (btn2() && (b->in_air==0))
    {
      b->in_air = 1;
      move_bullet(b, p);
    }
    else
    {
      prepare_bullet(b,p);
    }
  }
  
  else
  {
    b->in_air = 0;
    p->active = 0; //end of turn  
    delay(8000000); // wait a bit to give the chip to the other player
  }
}

/*before shooting*/
void prepare_bullet(Bullet *b, Player *p)
{
  b->x = (p->id == 1) ? 8 : 119;
  b->y = p->trajectory[8];
}

void move_bullet(Bullet *b, Player *p)
{
  reflection = (p->id == 1) ? 1 : -1;

  if (b->y <0 || b->y >128 || b->x >128) // edge collision
    reset_bullet(b, p);    

  if (b->target_hit)
  {
    p->score +=1; //quick score calculation : NEED TO MODIFY
    reset_bullet(b,p);
  }

  b->x = b->x + reflection;
  int i = b->x;
  b->y = p->trajectory[i];
}

void move_player(Player *p)
{
  if (btn4() && (p->y_top) > 0)
  {
    p->y_top = (p->y_top) - 1;
    get_trajectory(p);
  }
  else if (btn3() && (p->y_top) < 32)
  {
    p->y_top = (p->y_top) + 1;
    get_trajectory(p);
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
