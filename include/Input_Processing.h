#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

#include "../include/Game_State.h"

// Reads a line from stdin, replaces newline char (\n) with terminating char (\0)
void get_line(char line[]);

// Parses line array into tokens separated by whitespace
void get_tokens(char line[], int max_line_len, char tokens[][20], int *token_count);

// Processes commands given tokens which hold both cmd and arguments
int process_command(Game_State *game_state, char tokens[][20], const int *token_count);

// Checks if given command is valid, and if it has valid args
int is_command_legal(char tokens[][20], const int *token_count);

#endif //INPUT_PROCESSING_H
