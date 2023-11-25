#include "../include/Game_Logic.h"

extern Game_State game_state;

void command_new(const int rows, const int cols, const int mines)
{
    // free existing board memory
    if (game_state.board != NULL)
    {
        for (int i = 0; i < game_state.row_count; i++)
        {
            free(game_state.board[i]); // Free each row
        }
        free(game_state.board); // Free the board
        game_state.board = NULL; // Set board to NULL
    }

    // allocate new board memory
    game_state.board = (Cell **)malloc(sizeof(Cell *) * rows);
    if (game_state.board == NULL)
    {
        fprintf(stderr, "Error: Unable to allocate memory for game board.\n");
        exit(EXIT_FAILURE); // Exit if memory allocation fails
    }

    // init global vars for later use
    game_state.row_count = rows;
    game_state.col_count = cols;
    game_state.win = 0; // Set to 0 for ongoing game

    // Allocate memory for board rows
    for (int i = 0; i < rows; i++)
    {
        game_state.board[i] = (Cell *)malloc(sizeof(Cell) * cols);
    }

    // initialize each Cell with their pos
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            init_cell(&game_state.board[i][j], i, j, cols);
        }
    }

    // place mines sequantially starting pos 0
    for (int i = 0; i < mines; i++)
    {
        const int r = i / cols;
        const int c = i % cols;
        game_state.board[r][c].hasMine = 1;
    }

    // shuffle Cells
    shuffleCells(rows, cols, mines);

    // initalize adjacency counts
    initAdjCounts(rows, cols);
}

void command_flag(const int r, const int c)
{
    if (game_state.board[r][c].covered == 0)
    {
        printf("Cell uncovered\n");
        return;
    }

    if (game_state.board[r][c].flagged == 0)
    {
        game_state.board[r][c].flagged = 1;
    }
    else
    {
        printf("Cell already flagged\n");
    }
}

void command_unflag(const int r, const int c)
{
    if (game_state.board[r][c].flagged == 1)
    {
        game_state.board[r][c].flagged = 0;
    }
    else
    {
        printf("Cell already unflagged\n");
    }
}

void command_uncover(const int r, const int c)
{
    // if invalid row and col, notify and continue
    if (!isValidCell(r, c))
    {
        printf("Invalid index. Please try again.\n");
        return;
    }

    // if hasMine Cell, game lost, return 0
    if (game_state.board[r][c].hasMine)
    {
        // lose game
        game_state.board[r][c].covered = 0;
        game_state.win = -1;
        return;
    }

    // if adjacency count greater than 0, just uncover one Cell
    if (game_state.board[r][c].adjcount > 0)
    {
        game_state.board[r][c].covered = 0;
        return;
    }

    // last case, if Cell not hasMine and adjcount == 0
    // then do a group uncover of surrounding Cells
    uncover_recursive(r, c);
}

void command_show()
{
    for (int i = 0; i < game_state.row_count; i++)
    {
        for (int j = 0; j < game_state.col_count; j++)
        {
            display_cell(&game_state.board[i][j]); // display individual Cell
        }
        printf("\n"); // newline at end of each row
    }
}

void uncover_recursive(const int r, const int c)
{
    const int rowneighbors[] = {-1, -1, +0, +1, +1, +1, +0, -1};
    const int colneighbors[] = {+0, +1, +1, +1, +0, -1, -1, -1};

    // check if the current Cell is valid and needs to be uncovered
    if (!isValidCell(r, c) || !game_state.board[r][c].covered || game_state.board[r][c].hasMine)
    {
        return;
    }

    game_state.board[r][c].covered = 0;

    // if the adjacency count is greater than 0, do not uncover neighbors
    if (game_state.board[r][c].adjcount > 0)
    {
        return;
    }

    // recursively uncover each valid neighbor
    for (int n = 0; n < 8; n++)
    {
        const int rn = r + rowneighbors[n];
        const int cn = c + colneighbors[n];

        if (isValidCell(rn, cn))
        {
            if (game_state.board[rn][cn].covered && !game_state.board[rn][cn].hasMine)
            {
                uncover_recursive(rn, cn);
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

int checkWinCondition() {
    for (int i = 0; i < game_state.row_count; i++) {
        for (int j = 0; j < game_state.col_count; j++) {
            if (game_state.board[i][j].hasMine && !game_state.board[i][j].flagged)
                return 0;
            if (!game_state.board[i][j].hasMine && game_state.board[i][j].covered)
                return 0;
        }
    }

    return 1;
}