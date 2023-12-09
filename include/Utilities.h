#ifndef UTILITIES_H
#define UTILITIES_H

#include "../include/Game_State.h"

// Get a random integer from 0 to range
int get_random(int range);

// Allocate memory for board given rows and columns
void allocate_board_memory(Game_State *game_state, int rows, int cols);

// Free board memory
void free_board_memory(Game_State *game_state);

#endif //UTILITIES_H
