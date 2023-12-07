#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

#include "../include/Game_State.h"

void get_line(char line[]);
void get_tokens(char line[], int max_line_len, char tokens[][20], int *token_count);
int process_command(Game_State *game_state, char tokens[][20], const int *token_count);
int is_command_legal(char tokens[][20], const int *token_count);

#endif //INPUT_PROCESSING_H
