#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Input_Processing.h"
#include "../include/Constants.h"
#include "../include/Game_Logic.h"


void get_line(char line[])
{
    fgets(line, MAX_LINE_LEN, stdin);
    const int line_len = strlen(line);

    if (line[line_len - 1] == '\n')
        line[line_len - 1] = '\0';
}

void get_tokens(char line[], int max_line_len, char tokens[][20], int *token_count)
{
    char line_copy[max_line_len];
    strcpy(line_copy, line);

    const char *p = strtok(line_copy, " ");
    while (p != NULL)
    {
        strcpy(tokens[*token_count], p);

        p = strtok(NULL, " ");
        (*token_count)++;
    }
}

int is_command_legal(char tokens[][20], const int *token_count) {
    const char *legal_commands[] = { "new", "show", "quit", "uncover", "flag", "unflag" };
    const int legal_command_args[] = {3, 0, 0, 2, 2, 2};

    // Check if command is legal
    for (int i = 0; i < LEGAL_CMD_COUNT; i++) {
        if(strcmp(tokens[0], legal_commands[i]) == 0) {
                // Check if arguments given to command are legal
            if (legal_command_args[i] == *token_count - 1) {
                return 1; // Command is legal
            }
            break;
        }
    }

    return 0; // Command not legal
}

int process_command(Game_State *game_state, char tokens[][20], const int *token_count)
{
    const char *command = tokens[0];
    const int arg1 = atoi(tokens[1]);
    const int arg2 = atoi(tokens[2]);
    const int arg3 = atoi(tokens[3]);


    if(!is_command_legal(tokens, token_count))
    {
        printf("Invalid commands or arguments.\n");
        return 0;
    }

    if (strcmp(command, "new") == 0)
    {
        command_new(game_state, arg1, arg2, arg3);
        printf("New game created.\n");
        command_show(game_state);
    }
    else if (strcmp(command, "show") == 0)
    {
        command_show(game_state);
    }
    else if (strcmp(command, "uncover") == 0)
    {
        if (game_state->win == 0) {
            command_uncover(game_state, arg1 - 1, arg2 - 1);
        }
    }
    else if (strcmp(command, "flag") == 0)
    {
        command_flag(game_state, arg1 - 1, arg2 - 1);
    }
    else if (strcmp(command, "unflag") == 0)
    {
        command_unflag(game_state, arg1 - 1, arg2 - 1);
    }
    else if (strcmp(command, "quit") == 0)
    {
        printf("Quitting.\n");
        return -1;
    }
    else
    {
        printf("Incorrect command!\n");
    }

    return 1;
}