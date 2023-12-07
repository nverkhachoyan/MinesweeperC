#ifndef UTILITIES_H
#define UTILITIES_H

#include "../include/Game_State.h"

int get_random(int range);
int isValidCell(const Game_State *game_state, int r, int c);
void initAdjCounts(const Game_State *game_state, int rows, int cols);
void shuffleCells(const Game_State *game_state, int rows, int cols, int mines);

#endif //UTILITIES_H
