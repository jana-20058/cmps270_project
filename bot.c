#include <time.h>
#include <stdio.h>
#include <stdlib.h>

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
char matchingCharacters(int index)
{
    switch (index)
    {
    case 5:
        return 'C';
    case 3:
        return 'd';
    case 4:
        return 'B';
    case 2:
        return 's';

    default:
        return -1;
        break;
    }
}

void shuffle(int *array)
{
    for (int i = ShipNumber - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}
void ShipPlacment(char **grid)
{
    srand(time(NULL));
    int size[] = {5, 3, 4, 2};
    gridInitialization(grid);
    shuffle(size);
    for (int i = 0; i < ShipNumber; i++)
    {
        int shipLength = size[i];
        char ShipName = matchingCharacters(shipLength);
        int placed = 0;
        while (!placed)
        {
            int col_or_row = rand() % 2; // choosing 1 for H and 0 for V
            int noOverlapCounter = 0;

            // for the H
            if (col_or_row == 1)
            {
                int row = rand() % GridSize;
                int col = rand() % (GridSize - shipLength + 1);

                // checking for overlap

                for (int j = 0; j < shipLength; j++)
                {
                    if (grid[row][col + j] == '~')
                    {
                        noOverlapCounter++;
                    }
                }
                if (noOverlapCounter == shipLength)
                {
                    for (int j = 0; j < shipLength; j++)
                    {
                        grid[row][col + j] = ShipName;
                    }
                    placed = 1;
                }
            }
            // for the V
            else
            {
                int col = rand() % GridSize;
                int row = rand() % (GridSize - shipLength + 1);

                // checking for overlap

                for (int j = 0; j < shipLength; j++)
                {
                    if (grid[row + j][col] == '~')
                    {
                        noOverlapCounter++;
                    }
                }
                if (noOverlapCounter == shipLength)
                {
                    for (int j = 0; j < shipLength; j++)
                    {
                        grid[row + j][col] = ShipName;
                    }
                    placed = 1;
                }
            }
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

int main()
{
    char **bot = (char **)malloc(sizeof(char *) * 10);
    ShipPlacment(bot);
    printgrid(bot);
}
