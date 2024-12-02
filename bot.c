#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_functions.h"
#include "bot.h"

#define GridSize 10
#define ShipNumber 4

typedef struct
{
    int row;
    int col;
} coordinate;
coordinate targetList[MAX_TARGETS];
coordinate list[4];
  
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
    else if(strcmp(move, "torpedorow") == 0){
        for(int i=0;i<10;i++){
        heatGrid[row][i]=0;
        }}
        else if(strcmp(move, "torpedocolumn") == 0){
       for(int i=0;i<10;i++){
        heatGrid[i][col]=0;
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

        if (DisplayedGridBot[i][j] == '~' && BoundedByMisses(DisplayedGridBot, i, j))
        {
            arr[0] = i;
            arr[1] = j;
            flag = 1;
        }
    }
    return arr;
}
int BoundedByMisses(char **DisplayedGridBot, int col, int row)
{
    if (col != 0 && col != 9 && row != 0 && row != 9 && DisplayedGridBot[row + 1][col] == 'o' && DisplayedGridBot[row][col - 1] == 'o' && DisplayedGridBot[row][col + 1] == 'o' && DisplayedGridBot[row - 1][col] == 'o')
    {
        return -1;
    }

    else if (col == 0 && row == 0 && DisplayedGridBot[row + 1][col] == 'o' && DisplayedGridBot[row][col + 1] == 'o' || col == 9 && row == 9 && DisplayedGridBot[row][col - 1] == 'o' && DisplayedGridBot[row - 1][col] == 'o' ||
             col == 0 && row == 9 && DisplayedGridBot[row - 1][col] == 'o' && DisplayedGridBot[row][col + 1] == 'o' ||
             col == 9 && row == 0 && DisplayedGridBot[row + 1][col] == 'o' && DisplayedGridBot[row][col - 1] == 'o')
    {
        return -1;
    }

    else if (col == 0 && DisplayedGridBot[row][col + 1] == 'o' && DisplayedGridBot[row - 1][col] == 'o' && DisplayedGridBot[row + 1][col] == 'o' || col == 9 && DisplayedGridBot[row][col - 1] == 'o' && DisplayedGridBot[row - 1][col] == 'o' && DisplayedGridBot[row + 1][col] == 'o' ||
             row == 0 && DisplayedGridBot[row][col + 1] == 'o' && DisplayedGridBot[row][col - 1] == 'o' && DisplayedGridBot[row + 1][col] == 'o' ||
             row == 9 && DisplayedGridBot[row][col + 1] == 'o' && DisplayedGridBot[row][col - 1] == 'o' && DisplayedGridBot[row - 1][col] == 'o')
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

int botmove(char **oponentGrid, int **heatmap, char **DisplayedGridBot, int *ship, int **SmokeGridOpp)
{    int flag=0;
for(int i=0;i<ShipNumber;i++){
    if(ship[i]==1){
        flag=1;
    }
}
    if (flagShipSunkInCurrentTurn == 1 && totalNumberOfShipsSunkByBot >= 3)
    {
        torpedo(oponentGrid, DisplayedGridBot, ship, heatmap);

    }
    
    
    else if (flagShipSunkInCurrentTurn == 1)
    {
        ArtilleryBot(heatmap, ship, DisplayedGridBot, oponentGrid);
    }
    else if (radarSweepsUsedBot < 3 && targetCount == 0 && flag==0)
    {
    
        RadarSweepBot(oponentGrid, DisplayedGridBot, radarSweepsUsedBot, heatmap, ship, SmokeGridOpp);
        radarSweepsUsedBot++;
    }
    else if (flagShipSunkInCurrentTurn > 0 && smokeScreensUsedBot < totalNumberOfShipsSunkByBot)
    {
        // Smoke()
    }
    else
    {
        FireBot(oponentGrid, heatmap, DisplayedGridBot, ship);
        
    }
    flagShipSunkInCurrentTurn = ShipsSunkByBot(ship);
    ;
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
    else if (misses >= 3 && misses <= 8 && hits <= 4)
    {
        int *arr = checkedge(DisplayGridBot);

        nexti = arr[0];
        nextj = arr[1];
    }
    else
    {
        int *arr = heatmapvalue(heatmap, DisplayGridBot, opponentGrid);
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
int *heatmapvalue(int **heatmap, char **DisplayGridBot, char **opponentGrid)
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

        int choice = rand() % count;
        array[0] = candidates[choice][0];
        array[1] = candidates[choice][1];
    }
    if (BoundedByMisses(opponentGrid, array[0], array[1]) == -1)
    {
        do
        {
            array[0] = rand() % GridSize;
            array[1] = rand() % GridSize;
        } while (heatmap[array[0]][array[1]] == 0);
    }
    return array;
}

char updateDisplayedGridBot(char **opponentGrid, char **DisplayGridBot, int nexti, int nextj, int *ship, int **heatmap)
{
    char result;
    if (isalpha(opponentGrid[nexti][nextj]) && heatmap[nexti][nextj] != 0 && checkIndex(nexti, nextj))
    {
        result = DisplayGridBot[nexti][nextj] = '*';
        hits++; // Hit
        int num = matchingIndecies(opponentGrid[nexti][nextj]);
        if (num != -1 && ship[num] > 0)
        {
            ship[num]--;
        }
    }
    else
    {
        result = DisplayGridBot[nexti][nextj] = 'o';
        misses++; // Miss
    }
    if (isTargetPresent(nexti, nextj))
    {
        for (int i = 0; i < targetCount; i++)
        {
            if (list[i].row == nexti && list[i].col == nextj)
                removeTarget(i);
            break;
        }
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
bool **sunkships(int *ship, char **opponentGrid, char **DisplayedBotGrid)
{

    coordinate arr[12];
    for (int i = 0; i < 12; i++)
    {
        arr[i].row = -1;
        arr[i].col = -1;
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

    bool **isShip = malloc(GridSize * sizeof(bool *));
    for (int i = 0; i < GridSize; i++)
    {
        isShip[i] = malloc(GridSize * sizeof(bool));
        for (int j = 0; j < GridSize; j++)
        {
            isShip[i][j] = false;
        }
    }
    for (int i = 0; i < index; i++)
    {
        if (arr[i].row >= 0 && arr[i].row < GridSize &&
            arr[i].col >= 0 && arr[i].col < GridSize)
        {
            isShip[arr[i].row][arr[i].col] = true; // set the ships in the list as true
        }
    }
    return isShip;
}
// Function for torpedoing
void torpedo(char **opponentGrid, char **DisplayedBotGrid, int *ship, int **heatmap)
{
    coordinate arr[12];
    for (int i = 0; i < 12; i++)
    {
        arr[i].row = -1;
        arr[i].col = -1;
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

    int maxHitsCol = 0, columnToApplyTorpedo = 0;
    int maxHitsRow = 0, rowToApplyTorpedo = 0;
    bool **isShip = sunkships(ship, opponentGrid, DisplayedBotGrid);
    for (int K = 0; K < GridSize; K++)
    {
        int hitsInCol = 0, hitsInRow = 0;

        for (int j = 0; j < GridSize; j++)
        {
            if (DisplayedBotGrid[j][K] == '*' && !isShip[j][K])
            {
                hitsInCol++;
            }

            if (DisplayedBotGrid[K][j] == '*' && !isShip[K][j])
            {
                hitsInRow++;
            }
        }

        if (hitsInCol > maxHitsCol)
        {
            maxHitsCol = hitsInCol;
            columnToApplyTorpedo = K;
        }

        if (hitsInRow > maxHitsRow)
        {
            maxHitsRow = hitsInRow;
            rowToApplyTorpedo = K;
        }
    }


    if (maxHitsCol != 0 && maxHitsRow != 0)
    {
        if (maxHitsCol < maxHitsRow)
        {
            torpedoRow(DisplayedBotGrid, rowToApplyTorpedo, opponentGrid, ship, heatmap);
        }
        else if (maxHitsCol > maxHitsRow)
        {
            torpedoCol(DisplayedBotGrid, columnToApplyTorpedo, opponentGrid, ship, heatmap);
        }
        else
        {
            int choice = rand() % 2;
            if (choice == 0)
            {
                torpedoRow(DisplayedBotGrid, rowToApplyTorpedo, opponentGrid, ship, heatmap);
            }
            else
            {
                torpedoCol(DisplayedBotGrid, columnToApplyTorpedo, opponentGrid, ship, heatmap);
            }
        }
    }
    else
    {

        int maxRowSum = -1, maxColSum = -1;

        char targetType;
        int targetRow = 0;
        int targetcol = 0;
        for (int i = 0; i < GridSize; i++)
        {
            int rowSum = 0;
            for (int j = 0; j < GridSize; j++)
            {
                rowSum += heatmap[i][j];
            }
            if (rowSum > maxRowSum)
            {
                maxRowSum = rowSum;
                targetRow = i;
            }
        }

        for (int j = 0; j < GridSize; j++)
        {
            int colSum = 0;
            for (int i = 0; i < GridSize; i++)
            {
                colSum += heatmap[i][j];
            }
            if (colSum > maxColSum)
            {
                maxColSum = colSum;
                targetcol = j;
            }
        }
        if (maxColSum < maxRowSum)
        {
            torpedoRow(DisplayedBotGrid, rowToApplyTorpedo, opponentGrid, ship, heatmap);
        }
        else if (maxColSum > maxRowSum)
        {
            torpedoCol(DisplayedBotGrid, columnToApplyTorpedo, opponentGrid, ship, heatmap);
        }
        else
        {
          int rowsum=  sumheatmap(rowToApplyTorpedo,0,heatmap);
          int colsum=sumheatmap(columnToApplyTorpedo,1,heatmap);
            if (rowsum>colsum)
            {
                torpedoRow(DisplayedBotGrid, rowToApplyTorpedo, opponentGrid, ship, heatmap);
            }
            else
            {
                torpedoCol(DisplayedBotGrid, columnToApplyTorpedo, opponentGrid, ship, heatmap);
            }
        }
    }
}
void torpedoCol(char **DisplayedBotGrid, int columnToApplyTorpedo, char **opponentGrid, int *ship, int **heatmap)
{
    for (int i = 0; i < GridSize; i++)
    {
        if (DisplayedBotGrid[i][columnToApplyTorpedo] == '*' || DisplayedBotGrid[i][columnToApplyTorpedo] == 'o')
        {
            continue;
        }
        else
        {
            char c = updateDisplayedGridBot(opponentGrid, DisplayedBotGrid, i, columnToApplyTorpedo, ship, heatmap);
        }
    }
    updateHeatMap(0,columnToApplyTorpedo,'N',"torpedocolumn",heatmap);
}

void torpedoRow(char **DisplayedBotGrid, int rowToApplyTorpedo, char **opponentGrid, int *ship, int **heatmap)
{
    for (int i = 0; i < GridSize; i++)
    {
        if (DisplayedBotGrid[rowToApplyTorpedo][i] == '*' || DisplayedBotGrid[rowToApplyTorpedo][i] == 'o')
        {
            continue;
        }
        else
        {

            char c = updateDisplayedGridBot(opponentGrid, DisplayedBotGrid, rowToApplyTorpedo, i, ship, heatmap);
        }
    }
        updateHeatMap(rowToApplyTorpedo,0,'N',"torpedorow",heatmap);
}
int   sumheatmap(int num,int type,int** heatmap){
    int sum=0;
    if(type==0){
for(int i=0;i<10;i++){
sum+=heatmap[num][i];
}
    }
    else {
        for(int i=0;i<10;i++){
sum+=heatmap[i][num];
}
    }
}
bool visited[GridSize][GridSize] = {false};

// Comparator function for sorting cells based on heatmap values in descending order
int compareCells(const void *a, const void *b, void *heatmap_void)
{
    int **heatmap = (int **)heatmap_void;
    int rowA = ((int *)a)[0];
    int colA = ((int *)a)[1];
    int rowB = ((int *)b)[0];
    int colB = ((int *)b)[1];

    return heatmap[rowB][colB] - heatmap[rowA][colA];
}

// Helper function to check if a cell is adjacent to any sunk ship
bool isAdjacentToSunkShip(int row, int col, char **opponentGrid, int *ship)
{

    int dRow[] = {-1, 1, 0, 0, -1, -1, 1, 1};
    int dCol[] = {0, 0, 1, -1, 1, -1, 1, -1};

    for (int i = 0; i < 8; i++)
    {
        int adjRow = row + dRow[i];
        int adjCol = col + dCol[i];

        if (adjRow >= 0 && adjRow < GridSize && adjCol >= 0 && adjCol < GridSize)
        {
            char cell = opponentGrid[adjRow][adjCol];
            if (isalpha(cell))
            {

                int shipIndex = matchingIndecies(cell);
                if (shipIndex != -1 && ship[shipIndex] == -1)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

// Merged RadarSweepBot function with embedded RadarSweep logic (2x2 sweep area)
void RadarSweepBot(char **opponentGrid, char **displayedGrid, int radarSweepsUsedBot, int **heatmap, int *ship, int **SomkeGridOppd){
 

    bool **arr = sunkships(ship, opponentGrid, displayedGrid);
    int row = -1;
    int col = -1;
    for (int i = 0; i < GridSize; i++)
    {
        for (int j = 0; j < GridSize; j++)
        {
            if (!arr[i][j] && displayedGrid[i][j] == '*')
            {
                row = i;
                col = j;
               
            }
        }
    }

    if (row != -1 && col != -1)
    {
        char c = GetGreatestArea(heatmap, row, col);

        switch (c)
        {
        case 'A':
            row = row - 2;
            break;
        case 'B':
            row = row + 2;
            break;
        case 'L':
            col = col - 2;
            break;
        case 'R':
            col = col + 2;
            break;
        default:
            break;
        }
    }
    else
    {
     
        int **Grid = malloc(4 * sizeof(int *));
        for (int i = 0; i < 4; i++)
        {
            Grid[i] = malloc(2 * sizeof(int));
            for (int j = 0; j < 2; j++)
            {
                Grid[i][j] = 0; // Initialize each element to 0
            }
        }
        findHighest2x2Grid(heatmap, Grid); // Assuming this handles memory allocation
        row = Grid[0][0];
        col = Grid[0][1];
        for (int i = 0; i < 4; i++)
        {
            free(Grid[i]);
        }
        free(Grid);
    }

    printf("Bot chose radar sweep coordinates: %d   %d\n", row, col);

    int shipsFound = 0;
    for (int i = row; i < row + 2; i++)
    {
        if (shipsFound)
            break;
        for (int j = col; j < col + 2; j++)
        {
            if (checkIndex(i, j))
            {
                if (displayedGrid[i][j] == '~')
                {
                
                    if (isalpha(opponentGrid[i][j]))
                    {
                        shipsFound = 1;
                        break;
                    }
                }
            }
        }
    }


    int validGrid = 1;
    for (int i = row; i < row + 2; i++)
    {
        for (int j = col; j < col + 2; j++)
        {
            if (!checkIndex(i, j))
            {
                validGrid = 0;
                break;
            }
        }
    }

    if (validGrid)
    {
        if (shipsFound == 0)
        {
            for (int i = row; i < row + 2; i++)
            {
                for (int j = col; j < col + 2; j++)
                {
                   
                    heatmap[i][j] -= 3;
                }
            }
        }

        else
        {
            int index = 0;
            for (int i = row; i < row + 2; i++)
            {
                for (int j = col; j < col + 2; j++)
                {

                    heatmap[i][j] += 5;
                    list[index].row = i;
                    list[index].col = j;
                    targetCount++;
                    index++;
                }
            }
        }
    }
}
/*
int SmokeScreenBot (int **smokeGrid, char **displayedGrid, int shipsSunk, int smokeScreensUsedBot) {
    if (smokeScreensUsedBot >= shipsSunk) {
        printf("The bot cannot use any more smoke screens\n");
        return 0;
    }

    int row = -1, col = -1;
    bool foundNewArea = false;

    // Implementing Edge and Corner Bias for Smoke Screen
    for (int i = 0; i < GridSize && !foundNewArea; i++) {
        for (int j = 0; j < GridSize && !foundNewArea; j++) {
            if ((i == 0 || i == GridSize - 1 || j == 0 || j == GridSize - 1) && !visited[i][j]) {
                row = i;
                col = j;
                foundNewArea = true;
            }
        }
    }

    // If no edges or corners are found, choose an area near bot's ships (Proximity to Player's Ship Locations)
    if (!foundNewArea) {
        for (int i = 0; i < GridSize && !foundNewArea; i++) {
            for (int j = 0; j < GridSize && !foundNewArea; j++) {
                if (displayedGrid[i][j] == '*' && !visited[i][j]) {
                    row = i;
                    col = j;
                    foundNewArea = true;
                }
            }
        }
    }

    // If no new area is found (e.g., all edges and ship areas are covered), use a random area
    if (!foundNewArea) {
        srand(time(NULL));
        do {
            row = rand() % GridSize;
            col = rand() % GridSize;
        } while (visited[row][col]);
    }

    visited[row][col] = true;

    printf("Bot chose smoke screen coordinates: %c%d\n", 'A' + row, col + 1);

    // Deploy the smoke screen in a 2x2 area starting from the chosen coordinates
    for (int i = row; i < row + 2; i++) {
        for (int j = col; j < col + 2; j++) {
            if (i >= 0 && i < GridSize && j >= 0 && j < GridSize) {
                smokeGrid[i][j] = 1;
            }
        }
    }

    printf("Bot deployed smoke screen successfully\n");
   return 1;
}*/

// Helper functions
bool addTarget(int row, int col)
{
    // Check for duplicates
    for (int i = 0; i < targetCount; i++)
    {
        if (targetList[i].row == row && targetList[i].col == col)
        {
            return false; // Duplicate found, do not add
        }
    }

    if (targetCount < MAX_TARGETS)
    {
        targetList[targetCount].row = row;
        targetList[targetCount].col = col;
        targetCount++;
        return true;
    }
    else
    {
        printf("Target list is full. Cannot add more targets.\n");
        return false;
    }
}
void removeTarget(int index)
{
    if (index < 0 || index >= targetCount)
    {
        printf("Invalid target index: %d\n", index);
        return;
    }

    for (int i = index; i < targetCount - 1; i++)
    {
        list[i] = list[i + 1];
    }
    targetCount--;
}

bool isTargetPresent(int row, int col)
{
    for (int i = 0; i < targetCount; i++)
    {
        if (list[i].row == row && list[i].col == col)
        {
            return true;
        }
    }
    return false;
}

void findHighest2x2Grid(int **heatmap, int **Grid)
{

    int maxSum = -1;

    for (int i = 0; i < GridSize - 1; i++)
    {
        for (int j = 0; j < GridSize - 1; j++)
        {
            int sum = heatmap[i][j] + heatmap[i][j + 1] + heatmap[i + 1][j] + heatmap[i + 1][j + 1];

            if (sum > maxSum)
            {
                maxSum = sum;

                Grid[0][0] = i;
                Grid[0][1] = j;
                Grid[1][0] = i;
                Grid[1][1] = j + 1;
                Grid[2][0] = i + 1;
                Grid[2][1] = j;
                Grid[3][0] = i + 1;
                Grid[3][1] = j + 1;
            }
        }
    }

} // Updated GetGreatestArea function
char GetGreatestArea(int **heatmap, int row, int col)
{
    int RowCoordinate[] = {-2, 2, 0, 0};
    int ColumnCoordinate[] = {0, 0, -2, 2};
    char directions[] = {'A', 'B', 'L', 'R'};
    int maxHeat = -1;
    char bestDirection = 'N';

    for (int K = 0; K < 4; K++)
    {
        int startRow = row + RowCoordinate[K];
        int startCol = col + ColumnCoordinate[K];

        // Ensure the starting point and the 2x2 grid stay within bounds
        if (startRow >= 0 && startRow + 1 < GridSize && startCol >= 0 && startCol + 1 < GridSize)
        {
            int sumHeat = 0;

            // Loop over the 2x2 grid starting at (startRow, startCol)
            for (int r = startRow; r < startRow + 2; r++)
            {
                for (int c = startCol; c < startCol + 2; c++)
                {
                    sumHeat += heatmap[r][c];
                }
            }

            if (sumHeat > maxHeat)
            {
                maxHeat = sumHeat;
                bestDirection = directions[K];
            }
        }
    }
    return bestDirection;
}

// Updated choosenGrid function
void choosenGrid(char direction, int col, int row, int **heatmap, char **opponentGrid, char **DisplayedBotGrid, int *ship)
{
    int startRow = row, startCol = col;
    int i, j;

    switch (direction)
    {
    case 'A':
        startRow = row - 2;
        break;
    case 'B':
        startRow = row + 2;
        break;
    case 'L':
        startCol = col - 2;
        break;
    case 'R':
        startCol = col + 2;
        break;
    default:
        break;
    }

    for (i = startRow; i < startRow + 2; i++)
    {
        for (j = startCol; j < startCol + 2; j++)
        {

            if (i >= 0 && i < GridSize && j >= 0 && j < GridSize)
            {
                // Perform your actions on the heatmap, opponentGrid, and DisplayedBotGrid
                char result = updateDisplayedGridBot(opponentGrid, DisplayedBotGrid, i, j, ship, heatmap);
                updateHeatMap(i, j, result, "fire", heatmap);
            }
        }
    }
}

// Corrected ArtilleryBot function with proper memory handling
void ArtilleryBot(int **heatmap, int *ship, char **DisplayedBotGrid, char**opponentGrid)
{
   
   /* if (targetCount>0)
    {
       for(int i=list[0].row;i<list[0].row+2;i++){
        for(int j=list[0].col;j<list[0].col+2;j++){
char result= updateDisplayedGridBot(opponentGrid, DisplayedBotGrid, i,j, ship, heatmap);
               updateHeatMap(i, j, result, "fire", heatmap);
        // RadarGrid logic
    }}}
   else
   {*/
        bool **isShip = sunkships(ship, opponentGrid, DisplayedBotGrid);
        int col = -1, row = -1;
        for (int i = 0; i < GridSize; i++)
        {
            for (int j = 0; j < GridSize; j++)
            {
                if (DisplayedBotGrid[i][j] == '*' && !isShip[i][j])
                {
                    row = i;
                    col = j;
                    break;
                }
            }
        }

        if (col != -1 && row != -1)
        {
            char direction = GetGreatestArea(heatmap, row, col);
            choosenGrid(direction, col, row, heatmap, opponentGrid, DisplayedBotGrid, ship);
        }
        else
        {
            int **Grid = malloc(4 * sizeof(int *));
            for (int i = 0; i < 4; i++)
            {
                Grid[i] = malloc(2 * sizeof(int));
                for (int j = 0; j < 2; j++)
                {
                    Grid[i][j] = 0; // Initialize each element to 0
                }
            }
            findHighest2x2Grid(heatmap, Grid); // Assuming this handles memory allocation

            for (int i = 0; i < 4; i++)
            {
    
                char result = updateDisplayedGridBot(opponentGrid, DisplayedBotGrid, Grid[i][0], Grid[i][1], ship, heatmap);
                updateHeatMap(Grid[i][0], Grid[i][1], result, "fire", heatmap);
            }
            for (int i = 0; i < 4; i++)
            {
                free(Grid[i]);
            }
            free(Grid);

            // Free `isShip` array
            for (int i = 0; i < GridSize; i++)
            {
                free(isShip[i]);
            }
            free(isShip);
        }
    }

