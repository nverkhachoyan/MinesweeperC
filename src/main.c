// ---------------------------------
// Application: Minesweeper
// File: main.c
// Author: Nver Khachoyan
// Instructor: Rick Covington
// Date: 10/10/2023
//
// This program implements a basic version of the Minesweeper game.
// It includes functions for creating a new game, displaying the game board,
// and handling user commands like uncovering Cells and flagging mines.
//
// ---------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/Cell.h"
#include "../include/Constants.h"
#include "../include/Game_State.h"
#include "../include/Game_Logic.h"
#include "../include/Input_Processing.h"
#include "../include/Utilities.h"

// Global variable to hold the state of the game
Game_State game_state;
void run_game();

int main()
{
    run_game();
    return 0;
}

void run_game()
{
    game_state.board = NULL;
    srand(time(0));

    while (1)
    {
        char line[MAX_LINE_LEN];
        char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LEN];
        int token_count = 0;

        printf(">>");

        // Processing inputs, tokenizing each arg in tokens array
        get_line(line);
        get_tokens(line, MAX_LINE_LEN, tokens, &token_count);

        const int result = process_command(tokens);

        // Check if game has been won
        const int winCondition = checkWinCondition();
        if(winCondition) {
            game_state.win = winCondition;
        }
        if (game_state.win == -1) {
            printf("You have lost the game!\n");
            printf("Use the new command to start a new game.\n");
        } else if (game_state.win == 1) {
            printf("Congratulations! You have won!\n");
            printf("Use the new command to start a new game.\n");
        }

        // Checking if process_command returned 0, indicating to quit
        if (result == 0)
            break;
    }
}











