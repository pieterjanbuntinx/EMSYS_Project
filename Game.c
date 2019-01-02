#include "Game.h"

bool player1[game_pixels];
bool player2[game_pixels];

uint8_t objects[game_pixels]; //types: 0: no object, 1: bullet, 2: wall, 3: ...

void reset_game(){
    player1[distance_from_border_start] = true; 
    player2[game_pixels-1-distance_from_border_start] = true;
}
