#include <stdio.h>
#include <stdlib.h>

#include "../include/Game_Logic.h"
#include "../include/Utilities.h"


void command_new(Game_State *game_state, const int rows, const int cols, const int mines)
{
    // Free existing board memory
    if (game_state->board != NULL)
    {
        for (int i = 0; i < game_state->row_count; i++)
        {
            free(game_state->board[i]); // Free each row
        }
        free(game_state->board); // Free the board
        game_state->board = NULL; // Set board to NULL
    }

    // Allocate new board memory
    game_state->board = (Cell **)malloc(sizeof(Cell *) * rows);
    if (game_state->board == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for game board.\n");
        exit(EXIT_FAILURE); // Exit if memory allocation fails
    }

    // Init global vars for later use
    game_state->row_count = rows;
    game_state->col_count = cols;
    game_state->win = 0; // Set to 0 for ongoing game

    // Allocate memory for board rows
    for (int i = 0; i < rows; i++)
    {
        game_state->board[i] = (Cell *)malloc(sizeof(Cell) * cols);
    }

    // Initialize each Cell with their pos
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            init_cell(&game_state->board[i][j], i, j, cols);
        }
    }

    // Place mines sequantially starting pos 0
    for (int i = 0; i < mines; i++)
    {
        const int r = i / cols;
        const int c = i % cols;
        game_state->board[r][c].hasMine = 1;
    }

    // Shuffle Cells
    shuffleCells(game_state, rows, cols, mines);

    // Initalize adjacency counts
    initAdjCounts(game_state, rows, cols);
}

void command_flag(const Game_State *game_state,const int r, const int c)
{
    if (game_state->board[r][c].covered == 0)
    {
        printf("Cell uncovered\n");
        return;
    }

    if (game_state->board[r][c].flagged == 0)
    {
        game_state->board[r][c].flagged = 1;
    }
    else
    {
        printf("Cell already flagged\n");
    }
}

void command_unflag(const Game_State *game_state, const int r, const int c)
{
    if (game_state->board[r][c].flagged == 1)
    {
        game_state->board[r][c].flagged = 0;
    }
    else
    {
        printf("Cell already unflagged\n");
    }
}

void command_uncover(Game_State *game_state, const int r, const int c)
{
    // If invalid row and col, notify and continue
    if (!isValidCell(game_state, r, c))
    {
        printf("Invalid index. Please try again.\n");
        return;
    }

    // If hasMine Cell, game lost, return 0
    if (game_state->board[r][c].hasMine)
    {
        // Lose game
        game_state->board[r][c].covered = 0;
        game_state->win = -1;
        return;
    }

    // If adjacency count greater than 0, just uncover one Cell
    if (game_state->board[r][c].adjcount > 0)
    {
        game_state->board[r][c].covered = 0;
        return;
    }

    // Last case, if Cell not hasMine and adjcount == 0
    // then do a group uncover of surrounding Cells
    uncover_recursive(game_state, r, c);
}

void command_show(const Game_State *game_state)
{
    printf("%2d ", 0);
    for (int i = 0; i < game_state->col_count; i++) {
        printf("%2d ", i + 1);
    }

    printf("\n");

    for (int i = 0; i < game_state->row_count; i++)
    {
        printf("%2d ", i + 1);
        for (int j = 0; j < game_state->col_count; j++)
        {
            display_cell(&game_state->board[i][j]); // Display individual Cell
        }
        printf("\n"); // Newline at end of each row
    }
}

void uncover_recursive(const Game_State *game_state, const int r, const int c)
{
    const int rowneighbors[] = {-1, -1, +0, +1, +1, +1, +0, -1};
    const int colneighbors[] = {+0, +1, +1, +1, +0, -1, -1, -1};

    // Check if the current Cell is valid and needs to be uncovered
    if (!isValidCell(game_state, r, c) || !game_state->board[r][c].covered || game_state->board[r][c].hasMine)
    {
        return;
    }

    game_state->board[r][c].covered = 0;

    // If the adjacency count is greater than 0, do not uncover neighbors
    if (game_state->board[r][c].adjcount > 0)
    {
        return;
    }

    // Recursively uncover each valid neighbor
    for (int n = 0; n < 8; n++)
    {
        const int rn = r + rowneighbors[n];
        const int cn = c + colneighbors[n];

        if (isValidCell(game_state, rn, cn))
        {
            if (game_state->board[rn][cn].covered && !game_state->board[rn][cn].hasMine)
            {
                uncover_recursive(game_state, rn, cn);
            }
        }
    }
}

void init_cell(Cell *single_cell, const int r, const int c, const int cols)
{
    single_cell->covered = 1;
    single_cell->position = r * cols + c;
}

void display_cell(const Cell *c)
{
    if (c->flagged)
    {
        printf("%2s ", "P");
    }
    else if (c->covered)
    {
        printf("%2s ", "/");
    }
    else if (c->hasMine)
    {
        printf("%2s ", "*");
    }
    else if (c->adjcount > 0)
    {
        printf("%2d ", c->adjcount);
    }
    else
    {
        printf("%2s ", ".");
    }
}

int check_win_condition(const Game_State *game_state) {

    for (int i = 0; i < game_state->row_count; i++) {
        for (int j = 0; j < game_state->col_count; j++) {
            if (game_state->board[i][j].hasMine && !game_state->board[i][j].flagged)
                return 0;
            if (!game_state->board[i][j].hasMine && game_state->board[i][j].covered)
                return 0;
        }
    }

    return 1;
}