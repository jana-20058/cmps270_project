#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_functions.h"
#include "playerPrototypes.h"

#define GridSize 10
#define ShipNumber 4

int TorCol(char * coordinate,char** opponentGrid, char** DisplayedGrid,char *mode,int *ship){
    int hits=0;
    int num=Col(coordinate);
    for(int i=0;i<GridSize;i++){
        if(DisplayedGrid[i][num]=='*'||DisplayedGrid[i][num]=='o'){
            continue;
        }
else if(isalpha( opponentGrid[i][num])){
    int n=matchingIndecies(opponentGrid[i][num]);
    if(n!=-1){
        ship[n]--;
    }
    DisplayedGrid[i][num]='*';
    hits++;
}
else if(strcmp(mode, "easy") == 0){
    DisplayedGrid[i][num]='o';
}
    }
    printf("%s",(hits>0)?"HIT!":"MISS!");
    return 1;
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

int TorRow(char * coordinate,char** opponentGrid, char** DisplayedGrid,char *mode,int *ship){
    int hits=0;
    int num=RowForTorpedo(coordinate);
    for(int i=0;i<GridSize;i++){
        if(DisplayedGrid[num][i]=='*'||DisplayedGrid[num][i]=='o'){
            continue;
        }
else if(isalpha( opponentGrid[num][i])){
    int n=matchingIndecies(opponentGrid[num][i]);
    if(n!=-1){
        ship[n]--;
    }
    DisplayedGrid[num][i]='*';
    hits++;
}
else if(strcmp(mode, "easy") == 0){
    DisplayedGrid[num][i]='o';
}
    }
    printf("%s",(hits>0)?"HIT!":"MISS!");
    return 1;
}

// command functions
int Fire(char **opponenetGrid, char **DisplayedGrid, char *coordinates, char *mode, int *ship)
{
    int col = Col(coordinates);
    int row = Row(coordinates);
    if (col == -1 || row == -1)
    {
        printf("Invalid input!");
        return 0;
    }

    if (DisplayedGrid[row][col] == '*' || DisplayedGrid[row][col] == 'o')
    {
        printf("You have already fired at this coordinate\n");
        return 0;
    }

    if (isalpha(opponenetGrid[row][col]))
    {
        int num = matchingIndecies(opponenetGrid[row][col]);
        if (num != -1 && ship[num]>0)
        {
            ship[num]--;
        }
        DisplayedGrid[row][col] = '*';
        printf("HIT!\n");
    }
    else if (strcmp(mode, "easy") == 0)
    {
        DisplayedGrid[row][col] = 'o';
        printf("MISS!\n");
    }
    else
    {
        printf("MISS!\n");
    }
    return 1;
}

int Artillery(char **opponentGrid, char **DisplayedGrid, char *coordinate, char *mode, int flag, int *ship)
{

    if (flag == 0)
    {
        printf("You cannot use this move yet, sink one ship of your opponent in the current trun to unlock it for the next turn\n");
        return 0;
    }

    int col = Col(coordinate);
    int row = Row(coordinate);
    if (col == -1 || row == -1)
    {
        printf("Invalid input!");
        return 0;
    }

    int hits = 0;
    for (int i = row; i < row + 2; i++)
    {
        for (int j = col; j < col + 2; j++)
        {
            if (!checkIndex(i, j))
            {
                printf("invalid input/area is out of bounds\n");
                return 0;
            }
            else if(DisplayedGrid[i][j]=='*'|| DisplayedGrid[i][j]=='o'){
                continue;
            }
            else
            {
                if (isalpha(opponentGrid[i][j]))
                {
                    int num = matchingIndecies(opponentGrid[i][j]);
                    if (num != -1 && ship[num]>0)
                    {
                        ship[num]--;
                    }
                    DisplayedGrid[i][j] = '*';
                    hits++;
                }
                else if (strcmp(mode, "easy") == 0)
                {
                    DisplayedGrid[i][j] = 'o';
                }
            }
        }
    }
    printf("%s", (hits > 0) ? "HIT!" : "MISS");
    return 1;
}// Include this for isalpha and other character checks
int Torpedo(char **opponentGrid, char **DisplayedGrid, char *coordinates, char *mode, int *ship, int flag, int counter)
{
    if (counter < 3 || flag == 0)
    {
        printf("\nInvalid input/You can't use this move yet,make sure you have sunk 3 ships such that the last one sunk within the current turn to use the move on the next turn");
        return 0;
    }
    int length=strlen(coordinates);
    if (length == 1) {
        if (isalpha(coordinates[0])) {
            if (coordinates[0] < 'A' || coordinates[0] > 'J') {
                return 0;
            }
        } else if (isdigit(coordinates[0])) {
            if (coordinates[0] < '1' || coordinates[0] > '9') {
                return 0;
            }
        }

    }
    if (length == 2) {
        if (strcmp(coordinates, "10") != 0) {
            return 0;  
        }
    }
    if(strlen(coordinates)==1 && isalpha(coordinates[0])){
        TorCol(coordinates,opponentGrid,DisplayedGrid,mode,ship);
    }
    else{
        TorRow(coordinates,opponentGrid,DisplayedGrid,mode,ship);
    }
    return 1;
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

int SmokeScreen(int **smokeGrid, char *coordinate, int shipsSunk, int smokeScreensUsed) {
    if (smokeScreensUsed >= shipsSunk) {
        printf("You cant use  smoke screens\n");
        return 0; 
    }

    int row=Row(coordinate);
    int col=Col(coordinate);
    if (col==-1 ||row==-1) {
        printf("Invalid coordinate\n");
        return 0;
    }
    for (int i = row; i < row + 2; i++) {
        for (int j = col; j < col + 2; j++) {
            if (i >= 0 && i < GridSize && j >= 0 && j < GridSize) {
                smokeGrid[i][j] = 1;
            }
        }
    }

    printf("Smoke screen deployed successfully\n");
    printf("Press Enter to continue");
    getchar();
    getchar(); 
 
    clearConsole();

    return 1; 
}

void fillGrid(char **grid, char name[])
{
    char *ships[] = {"Carrier", "destroyer", "Battelship", "submarine"};
    int size[] = {5, 3, 4, 2};
    for (int i = 0; i < 4; i++)
    {
        char input[100];
        char *part1;
        char *part2;
        printf("%s please enter the coordinates(e.g. B3,vertical)  %s\n", name, ships[i]);
        scanf("%30s", input, sizeof(input));
        input[strcspn(input, "\n")] = '\0';

      

        part1 = strtok(input, ",");
        part2 = strtok(NULL, ",");

        if (part1 == NULL || part2 == NULL)
        {
            printf("Invalid input!\n");
            i--;
            continue; // Skip this iteration
        }

        int col = part1[0] - 'A';
        int row;
    
            // Determine column from part1
            col = part1[0] - 'A';

            // Handle special case for row '10'
            if (part1[1] == '1' && part1[2] == '0')
            {
                row = 9; // Row '10' corresponds to index 9
            }
            else
            {
                row = part1[1] - '1';
            }
        
        to_lowercase(part2);

        if (strcmp(part2, "horizontal") == 0)
        {
            if (canPlaceShip(grid, 'H', row, col, size[i]))
            {
                locateship(size[i], ships[i][0], col, row, grid, part2);
            }
            else
            {
                printf("Cannot place the ship! It is either out of bounds or overlaps with another ship.\n");
                i--;
            }
        }
        else if (strcmp(part2, "vertical") == 0)
        {
            if (canPlaceShip(grid, 'V', row, col, size[i]))
            {
                locateship(size[i], ships[i][0], col, row, grid, part2);
            }
            else
            {
                printf("Cannot place the ship! It is either out of bounds or overlaps with another ship.\n");
                i--;
            }
        }
        else
        {
            printf("Invalid direction\n");
            i--;
        }
    }
}

void locateship(int size, char letter, int col, int row, char **grid, char direction[])
{
    int i = 0;
    to_lowercase(direction);

    if (strcmp(direction, "horizontal") == 0)
    {
        
            for (int j = 0; j < size; j++)
            {
                grid[row][col + j] = letter;
            }
        
    }
    else
    {
        
            for (int j = 0; j < size; j++)
            {
                grid[row + j][col] = letter;
            }
        
    }
}


int canPlaceShip(char **grid, char direction, int row, int col, int size)
{
    if (direction == 'H')
    { // Horizontal placement
        if (col + size > GridSize||row>9)
            return 0; // Check out of bounds
        for (int i = 0; i < size; i++)
        {
            if (grid[row][col + i] != '~')
                return 0; // Check for overlap
        }
    }
    else if (direction == 'V')
    { // Vertical placement
        if (row + size > GridSize||col>9)
            return 0; // Check out of bounds
        for (int i = 0; i < size; i++)
        {
            if (grid[row + i][col] != '~')
                return 0; // Check for overlap
        }
    }
    return 1; // Valid placement
}
void to_lowercase(char *str)
{ // change the word to lowercase to compare
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

void clearConsole()
{
    printf("\033[H\033[J");
}
