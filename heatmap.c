#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define GRID_SIZE 10
#define numShips 5

void gridInitialization(int** DisplayGridBot);
void initializeHeatGrid(int** heatGrid);
void generateHeatmap(int* shipSizes, int** DisplayGridBot, int** heatmap);
void Fire(int** opponentGrid, int** heatmap, int** DisplayGridBot);
void printHeatmap(int** heatmap);

int main() {
    // Allocate memory for the opponent grid and heatmap
    int** DisplayGridBot = (int**)malloc(sizeof(int) * GRID_SIZE);
    int** heatmap = (int**)malloc(sizeof(int) * GRID_SIZE);
    int shipSizes[numShips] = {2, 3, 2, 3, 4};

    // Initialize the grids
    gridInitialization(DisplayGridBot);

    // Generate heatmap based on ship sizes
    generateHeatmap(shipSizes, DisplayGridBot, heatmap);

    // Print the heatmap
    printHeatmap(heatmap);

    // Fire based on heatmap
    Fire(DisplayGridBot, heatmap, DisplayGridBot);

    // Free allocated memory
    for (int i = 0; i < GRID_SIZE; i++) {
        free(DisplayGridBot[i]);
        free(heatmap[i]);
    }
    free(DisplayGridBot);
    free(heatmap);

    return 0;
}


// Initialize the heatmap with zeros
void initializeHeatGrid(int** heatGrid) {
    for (int i = 0; i < GRID_SIZE; i++) {
        heatGrid[i] = (int*)malloc(sizeof(int) * GRID_SIZE);
        for (int j = 0; j < GRID_SIZE; j++) {
            heatGrid[i][j] = 0;  
        }
    }
}

// Generate a heatmap based on ship sizes and placements
void generateHeatmap(int* shipSizes, int** DisplayGridBot, int** heatmap) {
     initializeHeatGrid(heatmap);
    for (int d= 0; d < numShips; d++) {
        int shipSize = shipSizes[d];

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {

                // Horizontal placement
                if (j + shipSize - 1 < GRID_SIZE) {

                    for (int k = 0; k < shipSize; k++) {
                            heatmap[i][j + k] += 1;
                        }
                    }
                

                // Vertical placement
                if (i+ shipSize - 1 < GRID_SIZE) {
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

  
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
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

    printf("The Bot Fires at %c %d\n", 'A' + nexti, nextj);
}


void printHeatmap(int** heatmap) {
    printf("Placement Heatmap:\n");
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            printf("%2d ", heatmap[i][j]);
        }
        printf("\n");
    }
}
void gridInitialization(int **grid)
{
    for (int i = 0; i < 10; i++)
    {
        grid[i] = (int *)malloc(GRID_SIZE* sizeof(int));
    }
    for (int j = 0; j < 10; j++)
    {
        for (int k = 0; k < 10; k++)
        {

            grid[j][k] = '~';
        }
    }
}