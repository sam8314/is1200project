#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"


/*Assignement 1.f
function that returns the status of the toggle-switches on the board
no parameter
the 4 LSB of the return value contain data rest are 0
from SW5, SW3, SW2 and SW1
SW1 = LSB
assume Port D has been intialized
the switches are connected to bits 11 through 8 of portD*/
int getsw(void)
{
    return (PORTD&0xF00)>>8;
}

/*Assignement 1.g
function that returns the current status of the push-buttons BTN2 to BTN4
no parameter
the 3 LSB of the return value contain data the rest are 0
assume Port D has been initialized
the buttons are connected to bits 7 to 5 of port D
*/
int getbtns(void)
{
    return (PORTD&0xE0)>>5;
}