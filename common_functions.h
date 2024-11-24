#ifndef COMMON_FUNCTIONS_H
#define COMMON_FUNCTIONS_H
void gridInitialization(char **grid);
void printgrid(char **grid);
int Row(char *coordinate);
int Col(char *coordinate);
int RowForTorpedo(char *coordinate);
int checkIndex(int row, int col);
int ShipsSunk(int *ship);
int matchingIndecies(char element);
 #endif