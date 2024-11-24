#ifndef BOT_H
#define BOT_H
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
#endif