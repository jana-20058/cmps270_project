#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_functions.h"
#include "bot.h"

#define GridSize 10
#define ShipNumber 4

<<<<<<< HEAD


char matchingCharacters(int index){

=======
int misses = 0;
int fires = 0;
char matchingCharacters(int index)

{
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
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

void ShipPlacment(char **grid)
{
    srand(time(NULL));
    int size[] = {5, 3, 4, 2};
    gridInitialization(grid);
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
    // for checking
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            printf("%c", grid[i][j]);
        }
    }
}
// Initialize the heatmap with zeros
void initializeHeatGrid(int **heatGrid)
{
    for (int i = 0; i < GridSize; i++)
    {
        heatGrid[i] = (int *)malloc(sizeof(int) * GridSize);
        for (int j = 0; j < GridSize; j++)
        {
            heatGrid[i][j] = 0;
<<<<<<< HEAD
        }
    }
}
void updateHeatMap(int row, int col, char result, char *move, int **heatGrid)
{
    int rowOffset[] = {-1, 1, 0, 0};
    int colOffset[] = {0, 0, -1, 1};

    if (strcmp(move, "fire") == 0)
    {
        if (result == '*')
        {
            heatGrid[row][col] = 0;

            for (int i = 0; i < 4; i++)
            {
                int adjRow = row + rowOffset[i];
                int adjCol = col + colOffset[i];
                if (checkIndex(adjRow, adjCol) && heatGrid[adjRow][adjCol] != 0)
                {
                    heatGrid[adjRow][adjCol] += 5;
                }
            }

            for (int i = 0; i < 4; i++)
            {
                int adjRow = row + rowOffset[i] * 2;
                int adjCol = col + colOffset[i] * 2;
                if (checkIndex(adjRow, adjCol) && heatGrid[adjRow][adjCol] != 0)
                {
                    heatGrid[adjRow][adjCol] += 2;
                }
            }
        }
        else if (result == 'o')
        {
            misses++;
            heatGrid[row][col] = 0;

            for (int i = 0; i < 4; i++)
            {
                int adjRow = row + rowOffset[i];
                int adjCol = col + colOffset[i];
                if (checkIndex(adjRow, adjCol) && heatGrid[adjRow][adjCol] != -1 && heatGrid[adjRow][adjCol] != 0)
                {
                    heatGrid[adjRow][adjCol] -=1;
                }
            }

            for (int i = 0; i < 4; i++)
            {
                int adjRow = row + rowOffset[i] * 2;
                int adjCol = col + colOffset[i] * 2;
                if (checkIndex(adjRow, adjCol) && heatGrid[adjRow][adjCol] != -1 && heatGrid[adjRow][adjCol] != 0)
                {
                    heatGrid[adjRow][adjCol] -= 1;
                }
            }
=======
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
        }
    }
}
void updateHeatMap(int row, int col, char result, char *move, int **heatGrid)
{
    int rowOffset[] = {-1, 1, 0, 0};
    int colOffset[] = {0, 0, -1, 1};

    if (strcmp(move, "fire") == 0)
    {
        if (result == '*')
        {
            heatGrid[row][col] = 0;

            for (int i = 0; i < 4; i++)
            {
                int adjRow = row + rowOffset[i];
                int adjCol = col + colOffset[i];
                if (checkIndex(adjRow, adjCol) && heatGrid[adjRow][adjCol] != -1 && heatGrid[adjRow][adjCol] != 0) {
                    heatGrid[adjRow][adjCol] += 5;
                }
            }

        for (int i = 0; i < 4; i++) {
    int adjRow = row + rowOffset[i] * 2;
    int adjCol = col + colOffset[i] * 2;
    if (checkIndex(adjRow, adjCol) && heatGrid[adjRow][adjCol] != -1 && heatGrid[adjRow][adjCol] != 0) {
        heatGrid[adjRow][adjCol] += 2;  
    }}
        }
        else if (result == 'o')
        {
            misses++;
            heatGrid[row][col] = -1;

            for (int i = 0; i < 4; i++)
            {
                int adjRow = row + rowOffset[i];
                int adjCol = col + colOffset[i];
                if (checkIndex(adjRow, adjCol) && heatGrid[adjRow][adjCol] != -1 && heatGrid[adjRow][adjCol] != 0) {
                    heatGrid[adjRow][adjCol] -= 5;
                }
            }

           for (int i = 0; i < 4; i++) {
    int adjRow = row + rowOffset[i] * 2;
    int adjCol = col + colOffset[i] * 2;
    if (checkIndex(adjRow, adjCol) && heatGrid[adjRow][adjCol] != -1 && heatGrid[adjRow][adjCol] != 0) {
        heatGrid[adjRow][adjCol] -= 2; 
        }
    }
}
    }}



// Generate a heatmap based on ship sizes and placements
<<<<<<< HEAD
void generateHeatmap(int *shipSizes, int **heatmap, char **DisplayedBot)
=======
void generateHeatmap(int *shipSizes, int **heatmap)
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
{
    initializeHeatGrid(heatmap);

    for (int d = 0; d < ShipNumber; d++)
    {
        int shipSize = shipSizes[d];
<<<<<<< HEAD
        if (shipSize != -1)
        { // takes only the ships that weren't sunk
            for (int i = 0; i < GridSize; i++)
            {
                for (int j = 0; j < GridSize; j++)
                {
                    // Horizontal placement
                    if (j + shipSize - 1 < GridSize)
                    {
                        int valid = 1;
                        for (int k = 0; k < shipSize; k++)
                        {
                            if (DisplayedBot[i][j + k] != '~')
                               {valid = 0;
                            break;}
                        }
                        if (valid)
                        {
                            for (int k = 0; k < shipSize; k++)
                                heatmap[i][j + k] += 1;
                        }
                    }
                    // Vertical placement
                    if (i + shipSize - 1 < GridSize)
                    {
                        int valid = 1;
                        for (int k = 0; k < shipSize; k++)
                        {
                            if (DisplayedBot[i + k][j] != '~')
                               {valid = 0;
                            break;}
                        }
                        if (valid)
                        {
                            for (int k = 0; k < shipSize; k++)
                                heatmap[i + k][j] += 1;
                        }
=======
        for (int i = 0; i < GridSize; i++)
        {
            for (int j = 0; j < GridSize; j++)
            {
                // Horizontal placement
                if (j + shipSize - 1 < GridSize)
                {
                    for (int k = 0; k < shipSize; k++)
                    {
                        heatmap[i][j + k] += 1;
                    }
                }
                // Vertical placement
                if (i + shipSize - 1 < GridSize)
                {
                    for (int k = 0; k < shipSize; k++)
                    {
                        heatmap[i + k][j] += 1;
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
                    }
                }
            }
        }
    }
<<<<<<< HEAD
    // Stronger bias for edges and corners
    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (i == 0 || j == 0 || i == GridSize - 1 || j == GridSize - 1)
            {if(DisplayedBot[i][j]=='~')
                heatmap[i][j] += 3; // Increased edge bias
            }
            if ((i == 0 && j == 0) || (i == 0 && j == GridSize - 1) ||
                (i == GridSize - 1 && j == 0) || (i == GridSize - 1 && j == GridSize - 1))
            {if(DisplayedBot[i][j]=='~')
                heatmap[i][j] += 5; // Stronger corner bias
            }
        }
    }
}
int *checkedge(char **DisplayedGridBot)
{
    int *arr = (int *)malloc(sizeof(int) * 3);
    int flag = 0;
    int i = rand() % GridSize;
    int j = rand() % GridSize;

=======

    // Stronger bias for edges and corners
    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (i == 0 || j == 0 || i == GridSize - 1 || j == GridSize - 1)
            {
                heatmap[i][j] += 3; // Increased edge bias
            }
            if ((i == 0 && j == 0) || (i == 0 && j == GridSize - 1) ||
                (i == GridSize - 1 && j == 0) || (i == GridSize - 1 && j == GridSize - 1))
            {
                heatmap[i][j] += 5; // Stronger corner bias
            }
        }
    }
}
int *checkedge(char **DisplayedGridBot)
{
    int *arr = (int *)malloc(sizeof(int) * 3);
    int flag = 0;
    int i = rand() % GridSize;
    int j = rand() % GridSize;

>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
    while (!flag)
    {
        if (rand() % 2 == 0)
        {
            i = (rand() % 2 == 0) ? 0 : GridSize - 1; // Row 0 or GridSize-1
            j = rand() % GridSize;
        }
        else
        {
            j = (rand() % 2 == 0) ? 0 : GridSize - 1; // Column 0 or GridSize-1
            i = rand() % GridSize;
        }

        if (DisplayedGridBot[i][j] == '~')
        {
            arr[0] = i;
            arr[1] = j;
            flag = 1;
        }
    }
    return arr;
}

<<<<<<< HEAD
int botmove(char **oponentGrid, int **heatmap, int smokeScreensUsedBot, int radarSweepsBot, char **DisplayedGridBot, int *ship)
{
    if (flagShipSunkInCurrentTurn == 1 && totalNumberOfShipsSunkByBot >= 3)
    {
        // Torpedo()
    }
    if (flagShipSunkInCurrentTurn == 1)
=======
void botmove(char **oponentGrid, int **heatmap, int flag, int CountershipsSunk, int smokeScreensUsedBot, int radarSweepsBot, char **DisplayedGridBot, int *ship)
{
    if (flag == 1 && CountershipsSunk >= 3)
    {
        // Torpedo()
    }
    if (flag == 1)
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
    {
        // Artillery()
    }
    if (radarSweepsBot != 3)
    {
        // Radarsweep()
    }
<<<<<<< HEAD
    if (flagShipSunkInCurrentTurn > 0 && smokeScreensUsedBot < totalNumberOfShipsSunkByBot)
=======
    if (CountershipsSunk > 0 && smokeScreensUsedBot < CountershipsSunk)
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
    {
        // Smoke()
    }
    else
    {
        FireBot(oponentGrid, heatmap, DisplayedGridBot, ship);
<<<<<<< HEAD
        printf("Before fire");
        for(int i=0;i<4;i++){
            
        printf("%d",ship[i]);
    }
    }
    flagShipSunkInCurrentTurn = ShipsSunkByBot(ship);
    printf("After fire");
    for(int i=0;i<4;i++){
        printf("%d",ship[i]);
    }
    printf(" \nTHis is the flag %d\n",flagShipSunkInCurrentTurn);
    if (flagShipSunkInCurrentTurn)
    {
        generateHeatmap(ship, heatmap, DisplayedGridBot);
    }
    return totalNumberOfShipsSunkByBot;
=======
    }
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
}
// Fire based on the heatmap (targeting the highest value)
void FireBot(char **opponentGrid, int **heatmap, char **DisplayGridBot, int *ship)
{
    int nexti = -1, nextj = -1;
<<<<<<< HEAD
    // fires == 7 && ShipsSunk == 0 || fires == 14 && ShipsSunk == 1
    if (fires == 0)
=======
//fires == 7 && ShipsSunk == 0 || fires == 14 && ShipsSunk == 1
    if (fires == 0 )
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
    {
        nexti = rand() % GridSize;
        nextj = rand() % GridSize;

<<<<<<< HEAD
        char result = updateDisplayedGridBot(opponentGrid, DisplayGridBot, nexti, nextj, ship,heatmap);
=======
        char result = updateDisplayedGridBot(opponentGrid, DisplayGridBot, nexti, nextj, ship);
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
    }
    else if (misses >= 3 && misses <= 8)
    {
        int *arr = checkedge(DisplayGridBot);
        if (checkIndex(arr[0], arr[1]))
        {
            nexti = arr[0];
            nextj = arr[1];
        }
    }
    else
    {
        int *arr = heatmapvalue(heatmap, DisplayGridBot);
        nexti = arr[0];
        nextj = arr[1];
    }

    if (nexti != -1 && nextj != -1)
    {
<<<<<<< HEAD
        char result = updateDisplayedGridBot(opponentGrid, DisplayGridBot, nexti, nextj, ship,heatmap);
        printf("The Bot Fired at %d %d\n", nexti, nextj);
=======
        char result = updateDisplayedGridBot(opponentGrid, DisplayGridBot, nexti, nextj, ship);
        printf("The Bot Fired at %c %d\n", 'A' + nexti, nextj);
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
        updateHeatMap(nexti, nextj, result, "fire", heatmap);
        fires++;
    }
}
int *heatmapvalue(int **heatmap, char **DisplayGridBot)
{
    int count = 0, max = -1;
    int *array = (int *)malloc(sizeof(int) * 2);
    int candidates[GridSize * GridSize][2];
    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (heatmap[i][j] > max && DisplayGridBot[i][j] == '~')
            {
                max = heatmap[i][j];
                count = 0;
                candidates[count][0] = i;
                candidates[count][1] = j;
                count++;
            }
            else if (heatmap[i][j] == max && DisplayGridBot[i][j] == '~')
            {
                candidates[count][0] = i;
                candidates[count][1] = j;
                count++;
            }
        }
    }
    if (count > 0)
    {
        int maxEdgeBias = -1;
        int edgeCandidates[GridSize * GridSize][2];
        int edgeCount = 0;

        // Evaluate edge bias for candidates
        for (int i = 0; i < count; i++)
        {
            int r = candidates[i][0];
            int c = candidates[i][1];
            int edgeBias = 0;

            // Calculate edge bias
            if (r == 0 || c == 0 || r == GridSize - 1 || c == GridSize - 1)
            {
                edgeBias += 2; // Edge
            }
            if ((r == 0 && c == 0) || (r == 0 && c == GridSize - 1) ||
                (r == GridSize - 1 && c == 0) || (r == GridSize - 1 && c == GridSize - 1))
            {
                edgeBias += 3; // Corner
            }

            // Update edgeCandidates based on edgeBias
            if (edgeBias > maxEdgeBias)
            {
                maxEdgeBias = edgeBias;
                edgeCount = 0;
                edgeCandidates[edgeCount][0] = r;
                edgeCandidates[edgeCount][1] = c;
                edgeCount++;
            }
            else if (edgeBias == maxEdgeBias)
            {
                edgeCandidates[edgeCount][0] = r;
                edgeCandidates[edgeCount][1] = c;
                edgeCount++;
            }
        }

        if (edgeCount > 0)
        {
            int choice = rand() % edgeCount;
            array[0] = edgeCandidates[choice][0];
            array[1] = edgeCandidates[choice][1];
        }
        else
        {
            int choice = rand() % count;
            array[0] = candidates[choice][0];
            array[1] = candidates[choice][1];
        }
    }
    return array;
}

<<<<<<< HEAD
char updateDisplayedGridBot(char **opponentGrid, char **DisplayGridBot, int nexti, int nextj, int *ship,int ** heatmap)
{
    char result;
    if (isalpha(opponentGrid[nexti][nextj]) && heatmap[nexti][nextj]!=0)
=======
char updateDisplayedGridBot(char **opponentGrid, char **DisplayGridBot, int nexti, int nextj, int *ship)
{
    char result;
    if (isalpha(opponentGrid[nexti][nextj]))
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
    {
        result = DisplayGridBot[nexti][nextj] = '*'; // Hit
        int num = matchingIndecies(opponentGrid[nexti][nextj]);
        if (num != -1 && ship[num] > 0)
        {
            ship[num]--;
        }
    }
    else
    {
        result = DisplayGridBot[nexti][nextj] = 'o'; // Miss
    }
    return result;
<<<<<<< HEAD
}

int ShipsSunkByBot(int *ship)
{flagShipSunkInCurrentTurn=0;
    int counter = 0;
    for (int i = 0; i < ShipNumber; i++)
    {
        if (ship[i] == 0)
        { flagShipSunkInCurrentTurn=1;
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
                break;
            }
            printf("\n%s ship was Sunk by the Bot!\n", str);
            counter++;
        }
       
    }
    totalNumberOfShipsSunkByBot += counter;
    printf("number of ships sunk:%d",totalNumberOfShipsSunkByBot);
    return flagShipSunkInCurrentTurn;
}
=======
}
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
