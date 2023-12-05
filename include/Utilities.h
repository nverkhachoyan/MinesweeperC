#ifndef UTILITIES_H
#define UTILITIES_H

int get_random(int range);
int isValidCell(int r, int c);
void initAdjCounts(int rows, int cols);
void shuffleCells(int rows, int cols, int mines);

#endif //UTILITIES_H
