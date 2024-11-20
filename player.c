#include "common_functions.c"
#include "PlayerShipPlacement.c"

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
