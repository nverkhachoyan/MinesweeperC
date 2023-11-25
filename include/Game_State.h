#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "Cell.h"

// Structure to represent the state of the game
typedef struct
{
    int win;         // 1 for win, 0 for ongoing, -1 for lose
    int row_count;   // Number of rows in the board
    int col_count;   // Number of columns in the board
    Cell **board;    // Pointer to 2D array of Cells
} Game_State;

#endif //GAME_STATE_H
