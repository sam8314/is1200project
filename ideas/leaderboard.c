#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "mipslab.h"

//creates head of a double linked list and returns a pointer to it
struct node* lead_init(){
    struct node* headp = (struct node*)malloc(sizeof(struct node));
    headp->next = NULL;
    headp->prev = NULL;
    return headp;
}

/* Inserts a given high score into an ordered linked list (from highest to lowest score).
If the list would exceed 9 scores stored it deletes the last node. */
void add_element(struct node* head, int score, char* initials){
    int count = 0;
    struct node* current = head;
    while ((current->next!=NULL)&&(current->next->score>score)) //searching for first smaller score
    {
        current = current->next;
        count++;
    }
    if ((current->next == NULL) && (count==9)) //we are either at last node or we need to insert (or both)
    {
        return;
    }
    else
    {
        struct node* new = (struct node*)malloc(sizeof(struct node)); //allocate memory for new node
        new->initials = initials;
        new->score = score;
        if (current->next == 0) //we are inserting to end of list
        {
            new->next = NULL; //end of list points to NULL
            new->prev = current;
            current->next = new;
            head->prev = new; //previous from head is the last node (our new)
        }
        else
        {
            new->next = current->next; //basic insertion into double linked list
            new->prev = current;
            current->next = new;
            new->next->prev = new;
            while(current->next!=NULL) //continue counting elements
            {
                current = current->next;
                count++;
            }
        }
    }
    if (count==10) //we only store top 9, so we need to get rid of last node
    {
        head->prev->prev->next = NULL;
        head->prev = head->prev->prev;
    }
    return;
}

struct node* current = NULL;

void show_leaderboard(int buttons){
    if (get_exit()){
        //currentPage=1; //back to menu
        return;
    }
    if (loopOne==1)
    {
        struct node* current = head;
        loopOne=0;
        firstRow = 0;
    }
    if ((buttons & 4) && (firstRow!=0))
    {
        firstRow--;
        delay(100);
        current = current->prev;
    }
    else if ((buttons & 1) && (firstRow!=6) && (current->next!=NULL))
    {
        firstRow++;
        delay(120);
        current = current->next;
    }
    else if (buttons & 2){firstRow=0;}
    int i = 0;
    while((i<4)&&(current->next!=NULL))
    {
        display_string(i, current->next->initials); //printing 4 values from the leaderboard
        i++;
        current = current->next;
    }
}

