/* mipslabfunc.c
    This file written 2015 by F Lundevall
    Some parts are original code written by Axel Isaksson

    For copyright and licensing, see file COPYING */

#include <stdint.h>
#include <stdio.h>
#include <pic32mx.h>
#include "header.h" 


#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

static void num32asc( char * s, int );

void quicksleep(int cyc) 
{
    int i;
    for(i = cyc; i > 0; i--);
}

void tick( unsigned int * timep )
{
    /* Get current value, store locally */
    register unsigned int t = * timep;
    t += 1; /* Increment local copy */

    /* If result was not a valid BCD-coded time, adjust now */

    if( (t & 0x0000000f) >= 0x0000000a ) t += 0x00000006;
    if( (t & 0x000000f0) >= 0x00000060 ) t += 0x000000a0;
    /* Seconds are now OK */

    if( (t & 0x00000f00) >= 0x00000a00 ) t += 0x00000600;
    if( (t & 0x0000f000) >= 0x00006000 ) t += 0x0000a000;
    /* Minutes are now OK */

    if( (t & 0x000f0000) >= 0x000a0000 ) t += 0x00060000;
    if( (t & 0x00ff0000) >= 0x00240000 ) t += 0x00dc0000;
    /* Hours are now OK */

    if( (t & 0x0f000000) >= 0x0a000000 ) t += 0x06000000;
    if( (t & 0xf0000000) >= 0xa0000000 ) t = 0;
    /* Days are now OK */

    * timep = t; /* Store new value */
}

void display_debug( volatile int * const addr )
{
    display_string( 1, "Addr" );
    display_string( 2, "Data" );
    num32asc( &textbuffer[1][6], (int) addr );
    num32asc( &textbuffer[2][6], *addr );
    display_update();
}

uint8_t spi_send_recv(uint8_t data) {
  	while(!(SPI2STAT & 0x08));
	  SPI2BUF = data;
  	while(!(SPI2STAT & 1));
	  return SPI2BUF;
}

void display_init(void) {
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
    /* DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
    delay(10);
    DISPLAY_VDD_PORT &= ~DISPLAY_VDD_MASK;
    delay(1000000);

    spi_send_recv(0xAE);
    DISPLAY_RESET_PORT &= ~DISPLAY_RESET_MASK;
    delay(10);
    DISPLAY_RESET_PORT |= DISPLAY_RESET_MASK;
    delay(10);

    spi_send_recv(0x8D);
    spi_send_recv(0x14);

    spi_send_recv(0xD9);
    spi_send_recv(0xF1);

    DISPLAY_VBATT_PORT &= ~DISPLAY_VBATT_MASK;
    delay(10000000);

    spi_send_recv(0xA1);
    spi_send_recv(0xC8);

    spi_send_recv(0xDA);
    spi_send_recv(0x20);

    spi_send_recv(0xAF); */

    /*FROM LAB*/
    DISPLAY_CHANGE_TO_COMMAND_MODE;
	  quicksleep(10);
    DISPLAY_ACTIVATE_VDD;
    quicksleep(1000000);

    spi_send_recv(0xAE);
    DISPLAY_ACTIVATE_RESET;
    quicksleep(10);
    DISPLAY_DO_NOT_RESET;
    quicksleep(10);

    spi_send_recv(0x8D);
    spi_send_recv(0x14);

    spi_send_recv(0xD9);
    spi_send_recv(0xF1);

    DISPLAY_ACTIVATE_VBAT;
    quicksleep(10000000);

    spi_send_recv(0xA1);
    spi_send_recv(0xC8);

    spi_send_recv(0xDA);
    spi_send_recv(0x20);

	  spi_send_recv(0xAF);
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
        }else{
            textbuffer[line][i] = ' ';
      }
}

/*FROM THE LABS*/
void display_update(void) {
    int i, j, k;
    int c;
    for(i = 0; i < 4; i++) {
        DISPLAY_CHANGE_TO_COMMAND_MODE;
        spi_send_recv(0x22);
        spi_send_recv(i);

        spi_send_recv(0x0);
        spi_send_recv(0x10);

        DISPLAY_CHANGE_TO_DATA_MODE;

        for(j = 0; j < 16; j++) {
            c = textbuffer[i][j];
            if(c & 0x80)
                continue;

            for(k = 0; k < 8; k++)
                spi_send_recv(font[c*8 + k]);
        }
    }
}

void display_update2() {
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
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_COMMAND_DATA_PORT &= ~DISPLAY_COMMAND_DATA_MASK;
		spi_send_recv(0x22);
		spi_send_recv(i);
		
		spi_send_recv(0x0);
		spi_send_recv(0x10);
		
		DISPLAY_COMMAND_DATA_PORT |= DISPLAY_COMMAND_DATA_MASK;
		
		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;
			
			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}

static void num32asc( char * s, int n )
{
    int i;
    for( i = 28; i >= 0; i -= 4 )
        *s++ = "0123456789ABCDEF"[ (n >> i) & 15 ];
}

#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
    register int i, sign;
    static char itoa_buffer[ ITOA_BUFSIZ ];
    static const char maxneg[] = "-2147483648";

    itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
    sign = num;                           /* Save sign. */
    if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
    {
        for( i = 0; i < sizeof( maxneg ); i += 1 )
        itoa_buffer[ i + 1 ] = maxneg[ i ];
        i = 0;
    }
    else
    {
        if( num < 0 ) num = -num;           /* Make number positive. */
        i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
        do {
            itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
            num = num / 10;                   /* Remove digit from number. */
            i -= 1;                           /* Move index to next empty position. */
        } while( num > 0 );
        if( sign < 0 )
        {
            itoa_buffer[ i ] = '-';
            i -= 1;
        }
    }
    /* Since the loop always sets the index i to the next empty position,
    * we must add 1 in order to return a pointer to the first occupied position. */
    return( &itoa_buffer[ i + 1 ] );
}


/* void grid_to_cols(unsigned char* display_buffer){
    int i,j;
    //i+128 is same column in the next row
    for (i=0;i<128;i++) //go through columns
    {
        for (j=0;j<4;j++)
        {
            int nr = display_buffer[i]&
            //we need to extract 8 bits starting from j*8, convert them to an int and copy into icon[i+j*128]
        }
    }
} */
