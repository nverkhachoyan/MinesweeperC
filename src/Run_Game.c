#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Run_Game.h"

#include <string.h>

#include "../include/Constants.h"
#include "../include/Input_Processing.h"
#include "../include/Game_Logic.h"
#include "../include/Game_State.h"


// Enumerates possible states resulting from processing a command
typedef enum {
    CMD_QUIT = -1, // Quit game
    CMD_WRONG = 0 // Wrong command, skip loop
} Command_State;

void run_game(Game_State *game_state)
{
    game_state->board = NULL;
    srand(time(0));

    while (1)
    {
        char line[MAX_LINE_LEN];
        char tokens[MAX_TOKEN_COUNT][MAX_TOKEN_LEN];
        int token_count = 0;

        // Reset tokens and token_count
        memset(tokens, 0, sizeof(char) * token_count);
        token_count = 0;

        // Command indicator
        printf(">>");

        // Processing inputs, tokenizing each arg in tokens array
        get_line(line);
        get_tokens(line, MAX_LINE_LEN, tokens, &token_count);

        // Process command and return 1 on success, 0 for invalid cmd, -1 to quit
        const int command_result = process_command(game_state, tokens, &token_count);

        // Quit if process_command returned -1
        if (command_result == CMD_QUIT)
            break;

        // Continue if process_command returned 0
        if (command_result == CMD_WRONG)
            continue;

        // Check if game has been won
        const int winCondition = check_win_condition(game_state);
        if(winCondition) {
            game_state->win = winCondition;
        }

        // Show statement depending if won or lost
        if (game_state->win == -1) {
            printf("You have lost the game!\n");
            command_show(game_state);
            printf("Use the new command to start a new game.\n");
        } else if (game_state->win == 1) {
            printf("Congratulations! You have won!\n");
            command_show(game_state);
            printf("Use the new command to start a new game.\n");
        }
    }
}