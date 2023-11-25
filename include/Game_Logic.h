#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <stdio.h>
#include <stdlib.h>

#include "../include/Constants.h"
#include "../include/Utilities.h"
#include "../include/Game_State.h"

void command_new(int rows, int cols, int mines);
void command_show();
void command_flag(int r, int c);
void command_unflag(int r, int c);
void command_uncover(int r, int c);
void uncover_recursive(int r, int c);
void display_cell(const Cell *c);
void init_cell(Cell *single_cell, int r, int c, int cols);
int checkWinCondition();

#endif //GAME_LOGIC_H