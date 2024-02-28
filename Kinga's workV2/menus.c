#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

/* Main changes: 
    - swapped rules and leaderboard so that in leaderboard we
    can use BTN2 and BTN4 for scrolling (same as everywhere else) 
    (idea was to avoid using the button in every function that got is 
    into the function)
    - added page 7 and 8 for 1 and 2player rules
    - BTN1 returns directly to menu so it's behaviour is 
    independent from double presses
    - in select difficulty I added a loopOne variable and a conditional 
    delay to get rid of double presses
    - changed navigation to switch cases
    - started implementing leaderboard with double linked lists */

/*0 : welcome animation
1 : home menu
2 : rules
3 : leaderboard
4 : select player mode
5 : select difficulty
6 : game setup
7 : 1player rules
8 : 2player rules

fix: change home menu : BTN1 is untouchable
*/

int loopOne; /* is 2 when we call select_difficulty, 
so 1. loop iteration we just print, 2. loop iteration we wait a little 
to discard double button presses, then continue naturally */

void welcome_animation(){
    display_string(2,"welcome animation");
}

void home_menu(int buttons){
    if(currentPage==1)
    {
        display_string(0, "HOME MENU");
        display_string(1, "how to play BTN2");
        display_string(2, "leaderboard BTN3");
        display_string(3, "game mode   BTN4");
    }

    if(buttons & 1) //BTN2
    {
        currentPage=2;
    }
    else if(buttons & 2) //BTN3
    {
        currentPage= 3;//go to page 1 of rules
    }
    else if(buttons & 4) //BTN4
    {
        currentPage= 4;//go select player mode
    }


}

void leaderboard(int buttons){
    if((get_exit()))
    {
        currentPage=1;
        return;
    }

    display_string(0,"");
    display_string(1,"");
    display_string(2, "leaderboard");
    display_string(3,"");


}

void select_player_mode(int buttons){
    if((get_exit()))
    {
        currentPage=1;
        return;
    }

    display_string(0, "return home BTN1");
    display_string(1,"");
    display_string(2, "one player  BTN2");
    display_string(3, "two players BTN3");
    
    if(buttons & 1) //BTN2
    {
        numberOfPlayers=1;
        currentPage = 5; // go select difficulty
        loopOne = 2;
    }
    else if(buttons & 2) //BTN3
    {
        numberOfPlayers = 2;
        currentPage= 5; //go select difficulty
        loopOne = 2;
    }
}

void select_difficulty(int buttons){
    if((get_exit()))
    {
        currentPage=1;
        return;
    }

    display_string(0, "change mode BTN1");
    display_string(1, "easy        BTN2");
    display_string(2, "medium      BTN3");
    display_string(3, "hard        BTN4");
    //delay(100);
    if (loopOne==2){loopOne--;}
    else if (loopOne==1){
        loopOne = 0;
        delay(150);
    }

    else if(buttons & 1) //BTN2
    {
        difficultyLevel = 1;
        display_string(1,"easy");
        currentPage= 6;// go to game setup
    }
    else if(buttons & 2) //BTN3
    {
        difficultyLevel = 2;
        display_string(2,"medium");
        currentPage= 6;//go game setup
    }
    else if(buttons & 4) //BTN4
    {
        difficultyLevel = 3;
        display_string(3,"hard");
        currentPage= 6;//go to game setup
    }
}


void navigation(int page){
    int buttons = get_btns();

    /* if(page==1){home_menu(buttons);}
    else if(page==2){rules(buttons);}
    else if(page==3){leaderboard(buttons);}
    else if((page==4)){select_player_mode(buttons);}
    else if((page==5)){select_difficulty(buttons);}
    else if((page==7)){onePlayerRules(buttons);}
    else if((page==8)){twoPlayerRules(buttons);} */

    switch(page){
        case 1: home_menu(buttons);
                break;
        case 2: rules(buttons);
                break;
        case 3: firstRow = 0;
                leaderboard(buttons);
                //show_leaderboard(array,buttons)
                break;
        case 4: select_player_mode(buttons);
                break;
        case 5: select_difficulty(buttons);
                break;
        case 7: onePlayerRules(buttons);
                break;
        case 8: twoPlayerRules(buttons);
                break;
    }
}


