#ifndef BOT_H
#define BOT_H
<<<<<<< HEAD
 int misses = 0;
 int fires = 0;
int totalNumberOfShipsSunkByBot = 0;
int flagShipSunkInCurrentTurn = 0;

char matchingCharacters(int index);
void ShipPlacment(char **grid);
void initializeHeatGrid(int** heatGrid);
void generateHeatmap(int *shipSizes, int **heatmap, char **DisplayedBot);
void updateHeatMap(int col,int row,char result,char *move,int ** heatGrid);
int *heatmapvalue(int **heatmap, char **DisplayGridBot);
void FireBot(char** opponentGrid, int** heatmap, char** DisplayGridBot,int* ship);
int botmove(char **oponentGrid, int **heatmap, int smokeScreensUsedBot, int radarSweepsBot, char **DisplayedGridBot, int *ship);
int matchingIndecies(char cell);
int *checkedge(char **DisplayedGridBot);
char updateDisplayedGridBot(char **opponentGrid, char **DisplayGridBot, int nexti, int nextj, int *ship,int ** heatmap);
int  ShipsSunkByBot(int *ship);
=======
char matchingCharacters(int index);
void shuffle(int *array);
void ShipPlacment(char **grid);
void initializeHeatGrid(int** heatGrid);
void generateHeatmap(int* shipSizes,  int** heatmap);
void updateHeatMap(int col,int row,char result,char *move,int ** heatGrid);
int *heatmapvalue(int **heatmap, char **DisplayGridBot);
void FireBot(char** opponentGrid, int** heatmap, char** DisplayGridBot,int* ship);
void botmove(char**oponentGrid,int **heatmap,int flag,int CountershipsSunk, int smokeScreensUsedBot,int radarSweepsBot,char**DisplayedGridBot,int* ship);
int matchingIndecies(char cell);
int *checkedge(char **DisplayedGridBot);
char updateDisplayedGridBot(char **opponentGrid,char**DisplayGridBot,int nexti,int nextj,int*ship );
>>>>>>> 7735f5f40b3bc6abb6acab58a7c531978e2a2998
#endif