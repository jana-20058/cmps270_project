#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "common_functions.h"
#include "bot.h"

#define GridSize 10
#define ShipNumber 4

typedef struct
{
    int row;
    int col;
} coordinate;

char matchingCharacters(int length)
{

    switch (length)
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
                    heatGrid[adjRow][adjCol] -= 1;
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
        }
    }
}

// Generate a heatmap based on ship sizes and placements
void generateHeatmap(int *shipSizes, int **heatmap, char **DisplayedBot)
{
    initializeHeatGrid(heatmap);

    for (int d = 0; d < ShipNumber; d++)
    {
        int shipSize = shipSizes[d];
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
                            {
                                valid = 0;
                                break;
                            }
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
                            {
                                valid = 0;
                                break;
                            }
                        }
                        if (valid)
                        {
                            for (int k = 0; k < shipSize; k++)
                                heatmap[i + k][j] += 1;
                        }
                    }
                }
            }
        }
    }
    // Stronger bias for edges and corners
    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (i == 0 || j == 0 || i == GridSize - 1 || j == GridSize - 1)
            {
                if (DisplayedBot[i][j] == '~')
                    heatmap[i][j] += 3; // Increased edge bias
            }
            if ((i == 0 && j == 0) || (i == 0 && j == GridSize - 1) ||
                (i == GridSize - 1 && j == 0) || (i == GridSize - 1 && j == GridSize - 1))
            {
                if (DisplayedBot[i][j] == '~')
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

int botmove(char **oponentGrid, int **heatmap, int smokeScreensUsedBot, int radarSweepsBot, char **DisplayedGridBot, int *ship)
{
    if (flagShipSunkInCurrentTurn == 1 && totalNumberOfShipsSunkByBot >= 3)
    {
        printf("check check !!");
        torpedo(oponentGrid, DisplayedGridBot, ship);
    }
    if (flagShipSunkInCurrentTurn == 1)
    {
        // Artillery()
    }
    if (radarSweepsBot != 3)
    {
        // Radarsweep()
    }
    if (flagShipSunkInCurrentTurn > 0 && smokeScreensUsedBot < totalNumberOfShipsSunkByBot)
    {
        // Smoke()
    }
    else
    {
        FireBot(oponentGrid, heatmap, DisplayedGridBot, ship);
        printf("Before fire");
        for (int i = 0; i < 4; i++)
        {

            printf("%d", ship[i]);
        }
    }
    flagShipSunkInCurrentTurn = ShipsSunkByBot(ship);
    printf("After fire");
    for (int i = 0; i < 4; i++)
    {
        printf("%d", ship[i]);
    }
    printf(" \nTHis is the flag %d\n", flagShipSunkInCurrentTurn);
    if (flagShipSunkInCurrentTurn)
    {
        generateHeatmap(ship, heatmap, DisplayedGridBot);
    }
    return totalNumberOfShipsSunkByBot;
}
// Fire based on the heatmap (targeting the highest value)
void FireBot(char **opponentGrid, int **heatmap, char **DisplayGridBot, int *ship)
{
    int nexti = -1, nextj = -1;
    // fires == 7 && ShipsSunk == 0 || fires == 14 && ShipsSunk == 1
    if (fires == 0)
    {
        nexti = rand() % GridSize;
        nextj = rand() % GridSize;

        char result = updateDisplayedGridBot(opponentGrid, DisplayGridBot, nexti, nextj, ship, heatmap);
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
        char result = updateDisplayedGridBot(opponentGrid, DisplayGridBot, nexti, nextj, ship, heatmap);
        printf("The Bot Fired at %d %d\n", nexti, nextj);
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

char updateDisplayedGridBot(char **opponentGrid, char **DisplayGridBot, int nexti, int nextj, int *ship, int **heatmap)
{
    char result;
    if (isalpha(opponentGrid[nexti][nextj]) && heatmap[nexti][nextj] != 0)
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
}

int ShipsSunkByBot(int *ship)
{
    flagShipSunkInCurrentTurn = 0;
    int counter = 0;
    for (int i = 0; i < ShipNumber; i++)
    {
        if (ship[i] == 0)
        {
            flagShipSunkInCurrentTurn = 1;
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
    printf("number of ships sunk:%d", totalNumberOfShipsSunkByBot);
    return flagShipSunkInCurrentTurn;
}
char matching(int index)
{

    switch (index)
    {
    case 0:
        return 'C';
    case 1:
        return 'd';
    case 2:
        return 'B';
    case 3:
        return 's';

    default:
        return '\0';
        break;
    }
}

void torpedo(char **opponentGrid, char **DisplayedBotGrid, int *ship)
{
    coordinate arr[12];
    for (int i = 0; i < 12; i++)
    {
        arr[i].row = -1;
        arr[i].col = -1;
    }
    // will be removed shortly
    for (int i = 0; i < 12; i++)
    {
        printf("\n The coordinates :%d  , %d )", arr[i].row, arr[i].col);
    }

    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        if (ship[i] == -1)
        {
            char c = matching(i);
            for (int j = 0; j < GridSize; j++)
            {
                for (int k = 0; k < GridSize; k++)
                {
                    if (opponentGrid[j][k] == c && DisplayedBotGrid[j][k] == '*')
                    { // idk if the second part is needed tbh
                        arr[index].row = j;
                        arr[index].col = k;
                        index++;
                    }
                }
            }
        }
    }

    // will be removed shortly
    for (int i = 0; i < 12; i++)
    {
        printf("\n The coordinates :%d  , %d )", arr[i].row, arr[i].col);
    }

    int maxHitsCol = 0, columnToApplyTorpedo = 0;
int maxHitsRow = 0, rowToApplyTorpedo = 0;


bool isShip[GridSize][GridSize] = {false}; //in defult all values are set to false
for (int i = 0; i < index; i++) {
    if (arr[i].row >= 0 && arr[i].row < GridSize &&
        arr[i].col >= 0 && arr[i].col < GridSize) {
        isShip[arr[i].row][arr[i].col] = true; //set the ships in the list as true
    }
}

for (int K = 0; K < GridSize; K++) {
    int hitsInCol = 0, hitsInRow = 0;

    for (int j = 0; j < GridSize; j++) {
        if (DisplayedBotGrid[j][K] == '*' && !isShip[j][K]) {
            hitsInCol++;
        }

        if (DisplayedBotGrid[K][j] == '*' && !isShip[K][j]) {
            hitsInRow++;
        }
    }

    if (hitsInCol > maxHitsCol) {
        maxHitsCol = hitsInCol;
        columnToApplyTorpedo = K;
    }

    if (hitsInRow > maxHitsRow) {
        maxHitsRow = hitsInRow;
        rowToApplyTorpedo = K;
    }
}

    // will be removed after
    printf("\nCol For torpedo %d", columnToApplyTorpedo);
    printf("\nRow For torpedo %d", rowToApplyTorpedo);

    if (maxHitsCol <= maxHitsRow)
    {
        // call torpedo on the Row
        for (int i = 0; i < GridSize; i++)
        {
            if (DisplayedBotGrid[rowToApplyTorpedo][i] == '*' || DisplayedBotGrid[rowToApplyTorpedo][i] == 'o')
            {
                continue;
            }
            else if (isalpha(opponentGrid[rowToApplyTorpedo][i]))
            {
                int n = matchingIndecies(opponentGrid[rowToApplyTorpedo][i]);
                if (n != -1)
                {
                    ship[n]--;
                }
                DisplayedBotGrid[rowToApplyTorpedo][i] = '*';
            }
            else
            {
                DisplayedBotGrid[rowToApplyTorpedo][i] = 'o';
            }
        }
    }
    else
    {
        // call torpedo on col
        for (int i = 0; i < GridSize; i++)
        {
            if (DisplayedBotGrid[i][columnToApplyTorpedo] == '*' || DisplayedBotGrid[i][columnToApplyTorpedo] == 'o')
            {
                continue;
            }
            else if (isalpha(opponentGrid[i][columnToApplyTorpedo]))
            {
                int n = matchingIndecies(opponentGrid[i][columnToApplyTorpedo]);
                if (n != -1)
                {
                    ship[n]--;
                }
                DisplayedBotGrid[i][columnToApplyTorpedo] = '*';
            }
            else
            {
                DisplayedBotGrid[i][columnToApplyTorpedo] = 'o';
            }
        }
    }
}
int RadarSweep(char **grid, char **displayedGrid, char *coordinate, int radarSweepsUsed, int **smokeGrid) {
    if (radarSweepsUsed >= 3) {
        printf("You have used all your radar sweeps\n");
        return 0; 
    }
    int row=Row(coordinate);
    int col=Col(coordinate);
    if (row==-1 || col==-1) {
        printf("Invalid coordinate\n");
        return 0; 
    }

    int shipsFound = 0;
    for (int i = row; i < row + 2; i++) {
        for (int j = col; j < col + 2; j++) {
            if (i >= 0 && i < GridSize && j >= 0 && j < GridSize) {
                if (smokeGrid[i][j] == 1) {
                    continue; 
                }
                if (grid[i][j] != '~' && grid[i][j] != '*' && grid[i][j] != 'o') {
                    shipsFound = 1;
                    break;
                }
            }
        }
        if (shipsFound) break;
    }

    if (shipsFound) {
        printf("Enemy ships found.\n");
    } else {
        printf("No enemy ships found.\n");
    }

    return 1; 
}