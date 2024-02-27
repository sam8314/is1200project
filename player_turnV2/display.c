#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "header.h"

uint8_t spi_send_recv(uint8_t data)
{
    while (!(SPI2STAT & 0x08));
    SPI2BUF = data;
    while (!(SPI2STAT & 0x01));
    return SPI2BUF;
}

void display_image(int x, const uint8_t *data)
{
    int i, j;

    for (i = 0; i < 4; i++)
    {
        DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
        spi_send_recv(0x22);
        spi_send_recv(i);

        spi_send_recv(x & 0xF);
        spi_send_recv(0x10 | ((x >> 4) & 0xF));

        DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;

        for (j = 0; j < 128; j++)
            spi_send_recv(data[i * 128 + j]);
    }
}

void display_string(int line, char *s) {
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)
		return;
	
	for(i = 0; i < 16; i++)
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}

void clear_buffer(uint8_t *data)
{
    int i;
    for (i = 0; i < 512; i++)
    {
        data[i] = 0;
    }
}

void draw_player(Player *p)
{
    draw_bit(p->x,16); //initial position
    int i;
    /*old drawing : is the projection on y axis*/
    if(p->y_top < 16)
    {
        for (i = p->y_top; i < 16; i++)
        {
            draw_bit((p->x), i);
        }       
    }
    else
    {
        for (i = 16; i < p->y_top; i++)
        {
            draw_bit((p->x), i);
        }             
    }

    /*this time as a line at an angle*/
    if(p->id =1)//player on the left
    {
        for(i=0; i<8;i++)
        {
            int increment = (p->y_top)*(p->x+i)/p->y_top;
            draw_bit((p->x+i), 16+increment);
        }
    }

    else
    {
        for(i=0; i<8;i++)
        {
            int increment = (p->y_top)*(p->x-i)/p->y_top;
            draw_bit((p->x-i), 16+increment);
        }
    }

}

void draw_bullet(Bullet * b) //HAVE TO MAKE IT BIGGER?
{
    draw_bit(b->x, b->y);
}

