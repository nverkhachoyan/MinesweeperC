#include <stdlib.h>
#include <math.h>

#include "../include/Utilities.h"
#include "../include/Game_State.h"

#include <stdio.h>

void allocate_board_memory(Game_State *game_state, const int rows, const int cols) {
    // Allocate new board memory
    game_state->board = (Cell **)malloc(sizeof(Cell *) * rows);
    if (game_state->board == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for game board.\n");
        exit(EXIT_FAILURE); // Exit if memory allocation fails
    }

    // Allocate memory for board rows
    for (int i = 0; i < rows; i++)
    {
        game_state->board[i] = (Cell *)malloc(sizeof(Cell) * cols);
    }
}

void free_board_memory(Game_State *game_state) {
    if (game_state->board != NULL) {
        for (int i = 0; i < game_state->row_count; i++) {
            free(game_state->board[i]);
        }
        free(game_state->board);
        game_state->board = NULL;
    }
}

int get_random(const int range)
{
    return (int)floor((float)range * rand() / (float)RAND_MAX) % range;
}



