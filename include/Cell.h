#ifndef CELL_H
#define CELL_H

// Structure to represent each Cell on the board
typedef struct
{
    int position; // Position of the Cell
    int adjcount; // Count of adjacent mines
    int hasMine;  // 1 if the Cell has a mine, 0 otherwise
    int covered;  // 1 if the Cell is covered, 0 otherwise
    int flagged;  // 1 if the Cell is flagged, 0 otherwise
} Cell;

#endif //CELL_H
