#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//#include <math.h>
#include <string.h>
#include "header.h"

/* Highscore* lead_init(){
    Highscore leaderboard[9];
    int i;
    for(i=0;i<9;i++){
        leaderboard[i].score=-1;
    }
    return leaderboard;
} */

//initializes given array to all score = -1 (invalid value, no such score possible later on)
void lead_init(Highscore* array){
    int i;
    for(i=0;i<9;i++){
        array[i].score=-1;
    }
}

/* Inserts a given high score into an ordered array (from highest to lowest score).
If the list would exceed 9 scores stored it deletes the last element. */
void add_element(Highscore* array, int score, char* name){
    int i, j;
    int count = 0;
    int length = 0;
    for (i=0;i<9;i++){
        if (array[i].score!=-1){length++;} //get the # of valid highscores
    }
    i = 0;
    while ((i<length)&&(array[i].score>score)) //iterating past greater scores
    {
        i++;
        count++;
    }
    if ((i==length)&&(count==9)){return;} //all highscores were greater
    else{
        Highscore new;
        new.score = score;
        new.initials = name;
        if (i==length){
            array[i] = new; //inserting after last but there aren't 9 highscores yet
        }
        else{  //we need to move all smaller highscore to make space for the new one
            for (j=length;j>i;j--){ //from length (<9) (last valid score+1) to i (first smaller score)
                array[j]=array[j-1];
            }
            array[i]=new; //insert new to the hole we made
        }
    }
}

/* Takes a highscore and a pointer to a string where it can write (assumed to be char array[10] with null byte) it can 
handle scores with 4 digits, writes the initials to the left and score from the right digit by digit (e.g EEEE   42'\0') */
void lead_to_string(Highscore high, char* string){
    int i;
    int score = high.score;
    for (i=0; i<4; i++){
        string[i] = high.initials[i];
    }
    string[8] = (char)(score%10)+0x30;
    i=2;
    while (score/10!=0){
        score = score/10;
        string[9-i] = (char)(score%10)+0x30;
        i++;
    }
    while (i<=5){
        string[9-i]=' ';
        i++;
    }
    string[9] = '\0';
}

/*Called from menu (previously named leaderboard()), it takes a pointer to a highscore array and the value on the buttons
as input and displays the current toplist in a scrollable format -> MIGHT need to change the firstRow variable to another
so that we can reset it!!!*/
void show_leaderboard(Highscore* array, int buttons){
    if((get_exit()))
    {
        currentPage=1;
        return;
    }
    int i;
    int length = 0;
    for (i=0;i<9;i++){
            if (array[i].score!=-1){length++;} //get the # of valid highscores
    }
    if ((buttons & 4) && (firstRow!=0))
    {
        firstRow--;
        delay(100);
    }
    else if ((buttons & 1) && (firstRow!=length-4))
    {
        firstRow++;
        delay(120);
    }
    else if (buttons & 2){firstRow=0;}
    i = 0;
    while (i<4){
        char string[10];
        lead_to_string(array[firstRow+i], string);
        display_string(i,string);
        i++;
    }
}

/*Called at the end of the game (if user decides to save score), it takes an arrar of chars initialized to AAAA and
keeps going through the alphabet until a name is secured with the switches -> we should probably write a warning to reset
the buttons before calling this*/
char* get_name(char* current){ 
    int switches; 
    while(!((get_sw()&0b1111)==0b1111)){ //until all switches are on, we increment the letters that belong to a switch that's off
        display_string(0, "");
        display_string(1, current);
        display_string(2, "");
        display_string(3, "");
        display_update();
        delay(1300); //wait a little -> could be with clock?
        switches = get_sw();
        if (!(switches&0x8)){ //left-most switch is off
            if (current[0]==0x5A){current[0]=0x41;} //if at Z, go back to A
            else{current[0]++;}
        }
        if (!(switches&0x4)){
            if (current[1]==0x5A){current[1]=0x41;} //if at Z, go back to A
            else{current[1]++;}
        }
        if (!(switches&0x2)){
            if (current[2]==0x5A){current[2]=0x41;} //if at Z, go back to A
            else{current[2]++;}
        }
        if (!(switches&0x1)){ //right-most switch
            if (current[3]==0x5A){current[3]=0x41;} //if at Z, go back to A
            else{current[3]++;}
        }
    }
    display_string(0,"to add_element");
    display_string(1, current);
    display_update();
    delay(2000);
    //add_element(array,score,current);
}


char* help[] = {"If you want to","save your score", "you can enter","your name on", 
    "the next page", "by switching", "the switches on", "when the right", 
    "letter appears", "Press BTN2 to", "continue or", "BTN1 to skip"};

/* Displayed at the end of a game, can call get_name and afterwards add_element -> needs the score to be passed down!!!*/
void write_help(){
    int firstRow = 0;
    while (1){
        int buttons = get_btns();
        int i = 0;
        if (get_exit()){
            currentPage=1; //back to menu
            return;
        }
        if ((buttons & 4) && (firstRow!=0)){firstRow--;delay(100);}
        else if ((buttons & 1) && (firstRow!=8)){firstRow++;delay(120);} //usual scrolling
        while(i<4)
        {
            display_string(i, help[firstRow+i]);
            i++;
        }
        display_update();
        if (buttons & 2){ //setup char array from AAAA, call get_name
            char current[4];
            int i;
            for (i=0;i<4;i++){
                current[i] = (char)0x41;
            }
            get_name(current);
            //call add_element
            break;
        }
    }
}

