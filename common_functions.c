#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

int Row(char *coordinate)
{
    int row = atoi(&coordinate[1]);
    if (row < 1 || row > GridSize)
    {
        return -1; //  out of bounds
    }
    row = row - 1;
    return row;
}
int Col(char *coordinate)
{
    int col = coordinate[0] - 'A';
    if (col < 0 || col >= GridSize)
    {
        return -1;
    }
    return col;
}
int RowForTorpedo(char *coordinate)
{
    int row = atoi(coordinate);
    if (row < 1 || row > GridSize)
    {
        return -1; //  out of bounds
    }
    row = row - 1;
    return row;
}

int checkIndex(int row, int col)
{
    if (col >= GridSize || col < 0 || row >= GridSize || row < 0)
    {
        return 0;
    }
    return 1;
}

int ShipsSunk(int *ship)
{
    int counter = 0;
    for (int i = 0; i < ShipNumber; i++)
    {
        if (ship[i] == 0)
        {
            ship[i] = -1;

            char *str;
            switch (i)
            {
            case 0:
                str = "Carrier";
                break;
            case 1:
                str = "destroyer";
                break;
            case 2:
                str = "BattleShip";
                break;
            case 3:
                str = "Submarine";
                break;

            default:
                printf("\n");
                break;
            }
            printf("\n%s ship has Sunk!\n", str);
            counter++;
        }
    }
    return counter;
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