#include <stdint.h>
#include "mipslab.h"

int firstRow;
int buttons;
char* oneP[16] = {"In this game","your goal is to","destroy as many","blocks as you",
"can by shooting","them before","the clock runs", "out. The",
"remaining time","is added to","your score.","You can use",
"BTN4 and BTN2","for aiming and", "BTN3 for","shooting."};
char* twoP[24] = {"In 2player mode","the two of you","are competing","against each",
"other to see","who can destroy","more blocks.","You will be",
"taking turns","shooting. You","have 15 seconds","each time to",
"shoot as many","balls as you","can. The bigger","blocks earn you",
"less points.","There will be","some time at","the beginning",
"of your turn","to grab the","chip from the","other person."};

void rules(int buttons){
    if (get_exit()){
        currentPage=1; //back to menu
        return;
    }

    display_string(0, "RULES");
    display_string(1, "1player     BTN3");
    display_string(2, "2player     BTN4");
    display_string(3, "");
    if(buttons & 2) //BTN3
    {
        currentPage = 7; //1player
        firstRow=0;
    }
    else if(buttons & 4) //BTN4
    {
        currentPage = 8; //2player
        firstRow=0;
    }
}

void onePlayerRules(int buttons){
    if (get_exit()){
        currentPage=1; //back to menu
        return;
    }
    if ((buttons & 4) && (firstRow!=0)){firstRow--;delay(100);}
    else if ((buttons & 1) && (firstRow!=12)){firstRow++;delay(120);}
    else if (buttons & 2){firstRow=0;}
    int i = 0;
    while(i<4)
    {
        display_string(i, oneP[firstRow+i]); //printing 4 lines from oneP starting at firstRow
        i++;
    }
}

void twoPlayerRules(int buttons){
    if (get_exit()){
        currentPage=1; //back to menu
        return;
    }
    if ((buttons & 4) && (firstRow!=0)){firstRow--;delay(100);}
    else if ((buttons & 1) && (firstRow!=20)){firstRow++;delay(120);}
    else if (buttons & 2){firstRow=0;}
    int i = 0;
    while(i<4)
    {
        display_string(i, twoP[firstRow+i]); //printing 4 lines from twoP starting at firstRow
        i++;
    }
}
