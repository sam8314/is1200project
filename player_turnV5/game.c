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

void draw_pixel(float x, float y) 
{
    // calculate the pixel's row and column in the display buffer
    int pixelRow = (int)y / 8;
    int pixelColumn = (int)x + 128 * pixelRow;

    // determine the position of the pixel within its row
    int pixelPositionInRow = (int)y - 8 * pixelRow;

    // create a bitmask to set the corresponding pixel in the display buffer
    char pixelBitmask = 0x01 << pixelPositionInRow;

    // update the display buffer with the pixel information
    display_buffer[pixelColumn] |= pixelBitmask;
}

/*
todo:
Display the score only when turn is over
Timer is shown on the LEDs
*/
void draw_score_timer(Player * p)
{
	//
}

void update_screen(uint8_t *data)
{
	clear_buffer(data);
	if(p1.active && !p2.active)
	{
		player_turn(&b, &p1);
        draw_player(&p1);
	}
	else if(p2.active && !p1.active)
	{
		player_turn(&b, &p2);
		draw_player(&p2);
	}

	draw_bullet(&b);
}

int game(void)
{
	pins_init();
	display_init();
	timer_init();
	enable_interrupt();

    p1.id = 1;
    p1.x = 0;
    p1.y_top = 15;
    p1.score = 0;
    p1.timer = 10;
    p1.active = 0;
	int i;
	for(i=0;i<128;i++)
		p1.trajectory[i] = 16; //initial trajectory is a straight line

    p2.id = 2;
    p2.x = 127;
    p2.y_top = 15;
    p2.score = 0;
    p2.timer = 10;
    p2.active = 1;
	for(i=0;i<128;i++)
		p2.trajectory[i] = 16;

	//b.x = p1.x;
	b.x = 64;
    b.y = 16;
	b.in_air = 0;
	b.target_hit = 0;

    return 0;
}
