#ifndef BOT_H
#define BOT_H
#define MAX_TARGETS 100
#define ShipNumber 4
#include <stdbool.h>
 int misses = 0;
 int fires = 0;
int hits=0;
int targetCount=0;
int totalNumberOfShipsSunkByBot = 0;
int flagShipSunkInCurrentTurn = 0;
int smokeScreensUsedBot=0;
int radarSweepsUsedBot=0;
coordinate targetList[MAX_TARGETS];
bool** sunkships(int** ship,char**opponentGrid,char** DisplayedBotGrid);
char matchingCharacters(int index);
void ShipPlacment(char **grid);
char  GetGreatestArea(int** heatmap,int row,int col);
void initializeHeatGrid(int** heatGrid);
void generateHeatmap(int *shipSizes, int **heatmap, char **DisplayedBot);
void updateHeatMap(int col,int row,char result,char *move,int ** heatGrid);
int *heatmapvalue(int **heatmap, char **DisplayGridBot,char**opponentGrid);
void FireBot(char** opponentGrid, int** heatmap, char** DisplayGridBot,int* ship);
int botmove(char **oponentGrid, int **heatmap, int smokeScreensUsedBot, int radarSweepsBot, char **DisplayedGridBot, int *ship);
int matchingIndecies(char cell);
int *checkedge(char **DisplayedGridBot);
char updateDisplayedGridBot(char **opponentGrid, char **DisplayGridBot, int nexti, int nextj, int *ship,int ** heatmap);
int  ShipsSunkByBot(int *ship);
void torpedo(char **opponentGrid, char **DisplayedBotGrid, int *ship,int ** heatmap);
char matching(int index);
int SmokeScreenBot(int **smokeGrid, int shipsSunk, int smokeScreensUsedBot);
void choosenGrid(char direction, int col, int row, int** heatmap, char** opponentGrid, char** DisplayedBotGrid, int* ship);
void ArtilleryBot(int**heatmap,int *ship, char**DisplayedBotGrid, int **RadarGrid, char **opponentGrid);
void torpedoCol(char** DisplayedBotGrid,int columnToApplyTorpedo,char** opponentGrid,int* ship);
void torpedoRow(char** DisplayedBotGrid,int rowToApplyTorpedo,char** opponentGrid,int* ship);
bool isAdjacentToSunkShip(int row, int col, char **opponentGrid, int *ship);
int compareCells(const void *a, const void *b, void *heatmap_void);
void findHighest2x2Grid(int** heatmap, int**Grid);
int RadarSweepBot(char **opponentGrid, char **displayedGrid, int radarSweepsUsedBot, int **heatmap, int *ship);
#endif
