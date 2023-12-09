#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../include/Game_State.h"

// Initalizes a new game given number of rows, cols, and mines
void command_new(Game_State *game_state, int rows, int cols, int mines);

// Flags a cell given row and column
void command_flag(const Game_State *game_state, int r, int c);

// Unflags a cell given row and column
void command_unflag(const Game_State *game_state, int r, int c);

// Uncovers a cell given row and column
void command_uncover(Game_State *game_state, int r, int c);

// Displays the board
void command_show(const Game_State *game_state);

// Recursively uncovers cells from the specified location
// If and only If the cell has adj_count == 0
void uncover_recursive(const Game_State *game_state, int r, int c);

// Initalizes all cells with default values, except adj_count
void init_cells(const Game_State *game_state, int rows, int cols);

// Initalizes adj_count for each cell
void init_adj_counts(const Game_State *game_state, int rows, int cols);

// Places mines sequantially, starting from (0, 0) position
void place_mines(const Game_State *game_state, int cols, int mines);

// Shuffles the cells to randomize mine placement
void shuffle_cells(const Game_State *game_state, int rows, int cols, int mines);

// Displays a single cell
void display_cell(const Cell *c);

// Checks if the given row and column dimensions are valid
int is_valid_cell(const Game_State *game_state, int r, int c);

// Checks if win condition is met
// NOTE: Lose condition is checked in command_uncover()
int check_win_condition(const Game_State *game_state);

#endif //GAME_LOGIC_H
