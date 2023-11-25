#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/Constants.h"
#include "../include/Game_Logic.h"

void get_line(char line[]);
void get_tokens(char line[], int max_line_len, char tokens[][20], int *token_count);
int process_command(char tokens[][20]);

#endif //INPUT_PROCESSING_H
