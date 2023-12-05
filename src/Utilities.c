#include <stdlib.h>
#include <math.h>

#include "../include/Utilities.h"
#include "../include/Game_State.h"


extern Game_State game_state;

int get_random(const int range)
{
    return (int)floor((float)range * rand() / (float)RAND_MAX) % range;
}

int isValidCell(const int r, const int c)
{
    if (r < 0 || c < 0)
    {
        return 0;
    }

    if (r >= game_state.row_count || c >= game_state.col_count)
    {
        return 0;
    }

    return 1;
}

void initAdjCounts(const int rows, const int cols)
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
                    if (game_state.board[rn][cn].hasMine)
                    {
                        mineCount++;
                    }
                }
            }
            game_state.board[i][j].adjcount = mineCount;
            mineCount = 0;
        }
    }
}

void shuffleCells(const int rows, const int cols, const int mines)
{
    for (int i = 0; i < mines * 20; i++)
    {
        const int r1 = get_random(rows);
        const int c1 = get_random(cols);
        const int r2 = get_random(rows);
        const int c2 = get_random(cols);

        const int x = game_state.board[r1][c1].hasMine;
        const int y = game_state.board[r2][c2].hasMine;

        game_state.board[r1][c1].hasMine = y;
        game_state.board[r2][c2].hasMine = x;
    }
}

