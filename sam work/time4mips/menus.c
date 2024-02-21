#include "mipslab.h"

/*0 : welcome animation
1 : home menu
2 : leaderboard
3 : rules page 1
4 : select difficulty
5 : game setup

fix: BTN1 input!
*/

void navigation(int page){
    if(page == 0){currentPage=welcome_animation();}
    else if(page==1){currentPage=home_menu();}
    else if(page==2){currentPage=leaderboard();}
    else if(page==3){currentPage=rules1();}
}

int welcome_animation(){
    display_string(2,"welcome animation");
    return 1; // go to home menu
}

int home_menu(){
    display_string(0, "leaderboard press BTN1");
    display_string(1, "how to play press BTN2");
    display_string(2, "single player press BTN3");
    display_string(3, "two players press BTN4");

    int buttons = getbtns();

    if(buttons != 0) // until a button is pressed
    {
        buttons = getbtns();
        if(buttons & 1) //BTN2
        {   
            return 3;// go to rules page 1
        } 
        else if(buttons & 2) //BTN3
        {   
            numberOfPlayers = 1;
            return 4;//go select difficulty
        } 
        else if(buttons & 4) //BTN4
        {   
            numberOfPlayers = 2;
            return 4;//go select difficulty
        } 
    }
}

int select_difficulty(){
    display_string(0, "easy BTN1");
    display_string(1, "medium BTN2");
    display_string(2, "hard BTN3");
    display_string(3, "go back BTN4");

    int buttons = gebtns();

    if(buttons != 0) // until a button is pressed
    {
        buttons = getbtns();
        //if BTN1
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
}

int rules1(){
    //...
}

int rules2(){
    //...
}

