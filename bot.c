#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "common_functions.c"
#define GridSize 10
#define ShipNumber 4

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
// Initialize the heatmap with zeros
void initializeHeatGrid(int** heatGrid) {
    for (int i = 0; i < GridSize; i++) {
        heatGrid[i] = (int*)malloc(sizeof(int) * GridSize);
        for (int j = 0; j < GridSize; j++) {
            heatGrid[i][j] = 0;  
        }
    }
}

// Generate a heatmap based on ship sizes and placements
void generateHeatmap(int* shipSizes, int** DisplayGridBot, int** heatmap) {
     initializeHeatGrid(heatmap);
    for (int d= 0; d < ShipNumber; d++) {
        int shipSize = shipSizes[d];

        for (int i = 0; i < GridSize; i++) {
            for (int j = 0; j < GridSize; j++) {

                // Horizontal placement
                if (j + shipSize - 1 < GridSize) {

                    for (int k = 0; k < shipSize; k++) {
                            heatmap[i][j + k] += 1;
                        }
                    }
                

                // Vertical placement
                if (i+ shipSize - 1 < GridSize) {
                        for (int k = 0; k < shipSize; k++) {
                            heatmap[i + k][j] += 1; 
                        }
                    }
                }
            }
        }
    }


// Fire based on the heatmap (targeting the highest value)
void Fire(int** opponentGrid, int** heatmap, int** DisplayGridBot) {
    int nexti = -1, nextj = -1, max = -1;

  
    for (int i = 0; i < GridSize; i++) {
        for (int j = 0; j < GridSize; j++) {
            if (heatmap[i][j] > max && DisplayGridBot[i][j] == '~') {
                max = heatmap[i][j];
                nexti = i;
                nextj = j;
            }
        }
    }

    // Fire at the target
    if (isalpha(opponentGrid[nexti][nextj])) {
        DisplayGridBot[nexti][nextj] = '*';  
    } else {
        DisplayGridBot[nexti][nextj] = 'o';  
    }

    printf("The Bot Fired at %c %d\n", 'A' + nexti, nextj);
}

