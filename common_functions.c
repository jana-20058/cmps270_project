
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "common_functions.h"

#define GridSize 10
#define ShipNumber 4


void gridInitialization(char **grid)
{
    for (int i = 0; i < 10; i++)
    {
        grid[i] = (char *)malloc(GridSize * sizeof(char));
    }
    for (int j = 0; j < 10; j++)
    {
        for (int k = 0; k < 10; k++)
        {

            grid[j][k] = '~';
        }
    }
}

void printgrid(char **grid)
{
    char letters[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};
    printf("    ");
    for (int o = 0; o < 10; o++)
    {
        printf("%c ", letters[o]);
    }
    printf("\n");

    for (int i = 0; i < 10; i++)
    {
        printf("%2d  ", i + 1);
        for (int j = 0; j < 10; j++)
        {
            printf("%c ", grid[i][j]);
        }
        printf("\n");
    }
}

int checkIndex(int row, int col)
{
    if (col >= GridSize || col < 0 || row >= GridSize || row < 0)
    {
        return 0;
    }
    return 1;
}

int matchingIndecies(char element)
{
    switch (element)
    {
    case 'C':
        return 0;
    case 'd':
        return 1;
    case 'B':
        return 2;
    case 's':
        return 3;

    default:
        return -1;
        break;
    }
}
