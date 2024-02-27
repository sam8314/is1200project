#include <pic32mx.h>
#include <stdint.h>
#include "header.h"

extern void enable_interrupt();
Bullet b;
Player p1, p2;

void user_isr(void)
{
	delay(50000);
	display_image(0, display_buffer);
	update_screen(display_buffer);
}

void draw_bit(float x, float y)
{
	x = (int)x;
	y = (int)y;
	int p = y / 8, B = x + 128 * p, b = y - 8 * p;
	char c = 0x01 << b;
	display_buffer[B] = display_buffer[B] | c;
}

void draw_score_timer(Player p)
{
	int i;
	switch (p.id)
	{
	case 1:
		for (i = 0; i < 8; i++)
		{
			display_buffer[52 + i] = numbers[p.score * 8 + i]; //found this online : bypasses display_string to display pre-drawn numbers see file array.c
			display_buffer[436 + i] = numbers[p.timer + i];
		}
		break;

	case 2:
		for (i = 0; i < 8; i++)
		{
			display_buffer[68 + i] = numbers[p.score * 8 + i];
			display_buffer[452 + i] = numbers[p.timer + i];
		}
		break;
	default:
		break;
	}
}

void update_screen(uint8_t *data)
{
	//some other timer management ?
	clear_buffer(data);
	if(p1.active && !p2.active)
	{
		float deltaY = (p1.y_top <16) ? p1.y_top-16 : p1.y_top;
    	float k = k = deltaY/4;
		player_turn(b, p1); //i think this is messing up the display
		draw_player(p1, k);
	}
	else if(p2.active && !p1.active)
	{
		float deltaY = (p1.y_top <16) ? p1.y_top-16 : p1.y_top;
    	float k = k = deltaY/4;
		player_turn(b, p2);
		draw_player(p2, k);
	}

	draw_bullet(b);
	draw_grid();
	draw_score_timer(p1);
	draw_score_timer(p2);
}

int main(void)
{
	pins_init();
	display_init();
	timer_init();
	enable_interrupt();

    p1.id = 1;
    p1.x = 0;
    p1.y_top = 12;
    p1.score = 0;
    p1.timer = 10;
    p1.active = 1;

    p2.id = 2;
    p2.x = 127;
    p2.y_top = 15;
    p2.score = 0;
    p2.timer = 10;
    p2.active = 0;

	b.x = p1.x;
    b.y = 16;
	b.in_air = 0;
	b.target_hit = 0;

	while(1)
	{
		/*for some reason, this works : before I added player_turn, it managed to perfectly display the bullet and the players whenever they were activated*/
		return 0;
	}
}
