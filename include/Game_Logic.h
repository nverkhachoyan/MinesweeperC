#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "../include/Game_State.h"

void command_new(Game_State *game_state, int rows, int cols, int mines);
void command_show(const Game_State *game_state);
void command_flag(const Game_State *game_state, int r, int c);
void command_unflag(const Game_State *game_state, int r, int c);
void command_uncover(Game_State *game_state, int r, int c);
void uncover_recursive(const Game_State *game_state, int r, int c);
void display_cell(const Cell *c);
void init_cell(Cell *single_cell, int r, int c, int cols);
int check_win_condition(const Game_State *game_state);

#endif //GAME_LOGIC_H
