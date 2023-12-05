#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Run_Game.h"
#include "../include/Constants.h"
#include "../include/Input_Processing.h"
#include "../include/Game_Logic.h"
#include "../include/Game_State.h"

extern Game_State game_state;

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

        const int result = process_command(tokens, &token_count);

        // Check if game has been won
        const int winCondition = check_win_condition();
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