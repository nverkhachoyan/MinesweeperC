#include "../include/Input_Processing.h"

extern Game_State game_state;

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

int process_command(char tokens[][20])
{
    if (strcmp(tokens[0], "new") == 0)
    {
        printf("New game created.\n");
        command_new(atoi(tokens[1]), atoi(tokens[2]), atoi(tokens[3]));
    }
    else if (strcmp(tokens[0], "show") == 0)
    {
        command_show();
    }
    else if (strcmp(tokens[0], "uncover") == 0)
    {
        if (game_state.win == 0) {
            command_uncover(atoi(tokens[1]), atoi(tokens[2]));
        }
    }
    else if (strcmp(tokens[0], "flag") == 0)
    {
        command_flag(atoi(tokens[1]), atoi(tokens[2]));
    }
    else if (strcmp(tokens[0], "unflag") == 0)
    {
        command_unflag(atoi(tokens[1]), atoi(tokens[2]));
    }
    else if (strcmp(tokens[0], "quit") == 0)
    {
        printf("Quitting.\n");
        return 0;
    }
    else
    {
        printf("Incorrect command!\n");
    }

    return 1;
}