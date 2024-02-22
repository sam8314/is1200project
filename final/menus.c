#include <stdint.h> 
#include "mipslab.h"

/*0 : welcome animation
1 : home menu
2 : leaderboard
3 : rules
4 : select player mode
5 : select difficulty
6 : game setup

fix: change home menu : BTN1 is untouchable
*/


void welcome_animation(){
    display_string(2,"welcome animation");
}

void home_menu(int buttons, int exit){
    if(currentPage==1)
    {
        display_string(0, "HOME MENU");
        display_string(1, "leaderboard BTN2");
        display_string(2, "how to play BTN3");
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

void leaderboard(int buttons, int exit){
    if(exit)
    {
        currentPage=1;
        return;
    }

    display_string(0,"");
    display_string(1,"");
    display_string(2, "leaderboard");
    display_string(3,"");


}

void select_player_mode(int buttons, int exit){
    if(exit)
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
    }
    else if(buttons & 2) //BTN3
    {
        numberOfPlayers = 2;
        currentPage= 5; //go select difficulty
    }


}

void select_difficulty(int buttons, int exit){
    if(exit)
    {
        currentPage=4;
        return;
    }
    display_string(0, "change mode BTN1");
    display_string(1, "easy        BTN2");
    display_string(2, "medium      BTN3");
    display_string(3, "hard        BTN4");

    if(buttons & 1) //BTN2
    {
        difficultyLevel = 1;
        currentPage= 6;// go to game setup
    }
    else if(buttons & 2) //BTN3
    {
        difficultyLevel = 2;
        currentPage= 6;//go game setup
    }
    else if(buttons & 4) //BTN4
    {
        difficultyLevel = 3;
        currentPage= 6;//go to game setup
    }
}

void rules(int buttons, int exit){
    if(exit)
    {
        currentPage=1;
        return;
    }

    display_string(0, "RULES");
    display_string(1, "");
    display_string(2, "");
    display_string(3, "");
}

void navigation(int page){
    int buttons = get_btns();
    int exit = get_exit();

    if(page==1){home_menu(buttons, exit);}
    else if(page==2){leaderboard(buttons, exit);}
    else if(page==3){rules(buttons, exit);}
    else if(page==4){select_player_mode(buttons, exit);}
    else if(page==5){select_difficulty(buttons, exit);}
}


