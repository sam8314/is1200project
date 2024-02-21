#include "mipslab.h"

/*0 : welcome animation
1 : home menu
2 : leaderboard
3 : rules page 1
4 : select player mode
5 : select difficulty
6 : game setup

fix: change home menu : BTN1 is untouchable
*/

void navigation(int page){
    int buttons = getbtns();

    if(page == 0){currentPage=welcome_animation(buttons);}
    else if(page==1){currentPage=home_menu(buttons);}
    else if(page==2){currentPage=leaderboard(buttons);}
    else if(page==3){currentPage=rules1(buttons);}
    else if(page==4){currentPage=select_player_mode(buttons);}
    else if(page==5){currentPage=select_difficulty(buttons);}
}

int welcome_animation(buttons){
    display_string(2,"welcome animation");
    return 1; // go to home menu
}

int leaderboard(buttons){
    display_string(2, "leaderboard");
    return 1;
}

int home_menu(buttons){
    display_string(0, "HOME MENU");
    display_string(1, "leaderboard press BTN2");
    display_string(2, "how to play press BTN3");
    display_string(3, "select game mode press BTN4");

    if(buttons & 1) //BTN2
    {
        return 2;// go to leaderboard
    }
    else if(buttons & 2) //BTN3
    {
        return 3;//go to page 1 of rules
    }
    else if(buttons & 4) //BTN4
    {
        return 4;//go select player mode
    }
}

int select_player_mode(buttons){
    display_string(0, "go back home BTN1");
    display_string(2, "single player BTN2");
    display_string(3, "two players BTN3");

    /*is there a cleaner way of coding this?*/
    if(buttons & 1) //BTN2
    {
        numberOfPlayers=1;
        return 5; // go select difficulty
    }
    else if(buttons & 2) //BTN3
    {
        numberOfPlayers = 2;
        return 5; //go select difficulty
    }
}

int select_difficulty(buttons){
    display_string(0, "go back home BTN1");
    display_string(1, "easy BTN2");
    display_string(2, "medium BTN3");
    display_string(3, "hard BTN4");

    if(buttons & 1) //BTN2
    {
        difficultyLevel = 1;
        return 3;// go to rules page 1
    }
    else if(buttons & 2) //BTN3
    {
        difficultyLevel = 2;
        return 4;//go select difficulty
    }
    else if(buttons & 4) //BTN4
    {
        return 1;//go to home menu
    }

}

int rules1(buttons){
    //...
}

int rules2(buttons){
    //...
}


