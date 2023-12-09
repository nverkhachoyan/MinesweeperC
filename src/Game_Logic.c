#include <stdio.h>

#include "../include/Game_Logic.h"
#include "../include/Utilities.h"


void command_new(Game_State *game_state, const int rows, const int cols, const int mines)
{
    // Free board if exists, then allocate
    free_board_memory(game_state);
    allocate_board_memory(game_state, rows, cols);

    // Init global vars for later use
    game_state->row_count = rows;
    game_state->col_count = cols;
    game_state->win = 0; // Set to 0 for ongoing game

    // Initialize each cell with their pos
    init_cells(game_state, rows, cols);

    // Place mines sequantially starting pos 0
    place_mines(game_state, cols, mines);

    // Shuffle Cells
    shuffle_cells(game_state, rows, cols, mines);

    // Initalize adjacency counts
    init_adj_counts(game_state, rows, cols);
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
    if (!is_valid_cell(game_state, r, c))
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
    if (!is_valid_cell(game_state, r, c) || !game_state->board[r][c].covered || game_state->board[r][c].hasMine)
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

        if (is_valid_cell(game_state, rn, cn))
        {
            if (game_state->board[rn][cn].covered && !game_state->board[rn][cn].hasMine)
            {
                uncover_recursive(game_state, rn, cn);
            }
        }
    }
}

void init_cells(const Game_State *game_state, const int rows, const int cols) {
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            game_state->board[i][j].covered = 1;
            game_state->board[i][j].position = i * cols + j;
        }
    }
}

void init_adj_counts(const Game_State *game_state, const int rows, const int cols)
{
    const int rowneighbors[] = {-1, -1, +0, +1, +1, +1, +0, -1};
    const int colneighbors[] = {+0, +1, +1, +1, +0, -1, -1, -1};
    int mineCount = 0;

    for (int i = 0; i < rows; i++)
    {

        for (int j = 0; j < cols; j++)
        {
            const int neighborCount = 8;
            for (int k = 0; k < neighborCount; k++)
            {
                const int rn = i + rowneighbors[k];
                const int cn = j + colneighbors[k];
                if (0 <= rn && rn < rows && 0 <= cn && cn < cols)
                {
                    if (game_state->board[rn][cn].hasMine)
                    {
                        mineCount++;
                    }
                }
            }
            game_state->board[i][j].adjcount = mineCount;
            mineCount = 0;
        }
    }
}

void place_mines(const Game_State *game_state, const int cols, const int mines) {
    for (int i = 0; i < mines; i++)
    {
        const int r = i / cols;
        const int c = i % cols;
        game_state->board[r][c].hasMine = 1;
    }
}

void shuffle_cells(const Game_State *game_state, const int rows, const int cols, const int mines)
{
    for (int i = 0; i < mines * 20; i++)
    {
        const int r1 = get_random(rows);
        const int c1 = get_random(cols);
        const int r2 = get_random(rows);
        const int c2 = get_random(cols);

        const int x = game_state->board[r1][c1].hasMine;
        const int y = game_state->board[r2][c2].hasMine;

        game_state->board[r1][c1].hasMine = y;
        game_state->board[r2][c2].hasMine = x;
    }
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

int is_valid_cell(const Game_State *game_state, const int r, const int c)
{
    if (r < 0 || c < 0)
    {
        return 0;
    }

    if (r >= game_state->row_count || c >= game_state->col_count)
    {
        return 0;
    }

    return 1;
}

int check_win_condition(const Game_State *game_state) {

    for (int i = 0; i < game_state->row_count; i++) {
        for (int j = 0; j < game_state->col_count; j++) {
            if (!game_state->board[i][j].hasMine && game_state->board[i][j].covered)
                return 0;
        }
    }

    return 1;
}