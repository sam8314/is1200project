#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

void game_setup(int difficulty){
    build_targets_grid(difficulty);

    //initialize players whether single or multiplayer mode
    int scoresCounters[2] = {0,0};
    int activePlayerId = 0;
    float angleOfShoot = 3.141592/2; //by default shoot in front of you
    int bulletInAir = 0; //at start the bullet isn't shot
}

void build_targets_grid(int difficulty){
    //
}

void player_turn(int playerId){
    //
}