#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "header.h"

int reflection = 1; //we start with player on the left

void reset_bullet(Bullet *b, Player *p)
{
  b->in_air = 0;
  b->target_hit = 0;
  b->x = (p->id == 1) ? 8 : 119;
  b->y = p->trajectory[8];
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

void get_rebound_trajectory(Player *p, int impactX, int impactY)
{
  int i;
  int distanceToMid;
  distanceToMid = ((p->y_top-16)>0)?p->y_top-16:16-p->y_top; //absolute value
  int ceiling = (impactY <16)? 1 : -1; //rebounding on ceiling or on the floor?
  int slope = ceiling*distanceToMid/8;

  if(p->id == 1)
  {
    for(i=0;i<128-impactX;i++)
      p->trajectory[impactX+i]=impactY+i*slope;
  }

  else
  {
    for(i=0;i<impactX;i++)
      p->trajectory[impactX-i]=impactY+i*slope;
  }

}

void player_turn(Bullet *b, Player *p)
{
  while(!(timesup)){
    int buttons = get_btns();
    clear_buffer(display_buffer);
    if(b->in_air ==0) {
      move_player(p);
      reset_bullet(b, p);
    }
    if(get_btns()&1)
    {
      b->in_air = 1;
    } 
    if(b->in_air==1)
    {
      move_bullet(b, p);
    }
    draw_grid();
    draw_bullet(b); 
    draw_player(p);
    display_image(0, display_buffer);
  }

  write_help();
}

void move_bullet(Bullet *b, Player *p)
{
  delay(2);
  reflection = (p->id == 1) ? 1 : -1;
  if (b->x < 0 || b->x >128) // wall collision
    reset_bullet(b, p); 

  if (b->y < 0 || b->y > 32) //floor or ceiling rebound
    get_rebound_trajectory(p, b->x, b->y);

  if (b->x+1==62){
    int p=b->y+1;
    if (col[(difficultyLevel-1)*4][p]==1){
      b->target_hit =1;
        int k = p;
        while((k-1)==1){
            k--;
        }
        while((k+1)==1){
            col[(difficultyLevel-1)*4][k]=0;
        }
    }
  }
  else if (b->x+1==68){
    int p=b->y+1;
    if (col[(difficultyLevel-1)*4+1][p]==1){
      b->target_hit =1;
        int k = p;
        while((k-1)==1){
            k--;
        }
        while((k+1)==1){
            col[(difficultyLevel-1)*4+1][k]=0;
        }
    }
  }
  else if (b->x+1==74){
    int p=b->y+1;
    if (col[(difficultyLevel-1)*4+2][p]==1){
      b->target_hit =1;
        int k = p;
        while((k-1)==1){
            k--;
        }
        while((k+1)==1){
            col[(difficultyLevel-1)*4+2][k]=0;
        }
    }
  }
  else if (b->x+1==80){
    int p=b->y+1;
    if (col[(difficultyLevel-1)*4+3][p]==1){
      b->target_hit =1;
        int k = p;
        while((k-1)==1){
            k--;
        }
        while((k+1)==1){
            col[(difficultyLevel-1)*4+3][k]=0;
        }
    }
  }
  if (b->target_hit)
  {
    p->score +=1; //quick score calculation : NEED TO MODIFY
    reset_bullet(b,p);
  }

  b->x = b->x + reflection;
  int i = b->x;
  b->y = p->trajectory[i];
}

/*add some delay to have easier aiming ?*/
void move_player(Player *p)
{
  delay(5);
  if ((get_btns()&4) && (p->y_top) > 0)
  {
    p->y_top = (p->y_top) - 1;
    get_trajectory(p);
  }
  else if ((get_btns()&2) && (p->y_top) < 32)
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
