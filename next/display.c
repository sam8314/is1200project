#include <pic32mx.h>
#include <stdint.h>
#include <stdio.h>
#include "header.h"

void display_image(int x, uint8_t *data)
{
    /*
    This function was taken from the course's resources :
    https://github.com/is1200-example-projects/hello-display/blob/master/main.c

    Copyright (c) 2015, Axel Isaksson

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions
    are met:

    1. Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
    3. The name of the author may not be used to endorse or promote products
    derived from this software without specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
    IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
    OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
    IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
    INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
    NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
    THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/
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

/*
FROM THE LABS
void display_image(int x, uint8_t *data) {
    int i, j;

    for(i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;

        spi_send_recv(0x22);
        spi_send_recv(i);

        spi_send_recv(x & 0xF);
        spi_send_recv(0x10 | ((x >> 4) & 0xF));

        DISPLAY_CHANGE_TO_DATA_MODE;

        for(j = 0; j < 128; j++)
            spi_send_recv(~data[i*128 + j]);
    }
}
*/

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
    int i;
    /*old drawing : is the projection on y axis*/
    if(p->y_top < 16)
    {
        for (i = p->y_top; i < 16; i++)
        {
            draw_pixel((p->x), i);
        }       
    }
    else
    {
        for (i = 16; i < p->y_top; i++)
        {
            draw_pixel((p->x), i);
        }             
    }

    /*this time using an array for the trajectory*/
    for(i =0; i<8;i++)
    {
        int reflection = (p->id == 1) ? i : 128-i;
        draw_pixel(reflection,p->trajectory[i]);  
    }
}

void draw_bullet(Bullet * b)
{
    draw_pixel(b->x, b->y);
    draw_pixel((b->x), (b->y-1));
    draw_pixel((b->x), (b->y+1));
    
    draw_pixel((b->x+1), (b->y+1));
    draw_pixel((b->x+1), (b->y));
    draw_pixel((b->x+1), (b->y-1));

    draw_pixel((b->x-1), (b->y-1));
    draw_pixel((b->x-1), (b->y));
    draw_pixel((b->x-1), (b->y+1)); 
}