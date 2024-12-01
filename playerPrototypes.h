#ifndef PLAYERPROTOTYPES_H
#define PLAYERPROTOTYPES_H
void to_lowercase(char *str);
void fillGrid(char **grid, char name[]);
void locateship(int size, char letter, int col, int row, char **grid, char direction[]);
void clearConsole();
int ShipsSunk(int *ship);
int Row(char *coordinate);
int Col(char *coordinate);
int RowForTorpedo(char *coordinate);
int canPlaceShip(char **grid, char direction, int row, int col, int size);
int TorCol(char * coordinate,char** opponentGrid, char** DisplayedGrid,char *mode,int *ship);
int TorRow(char * coordinate,char** opponentGrid, char** DisplayedGrid,char *mode,int *ship);
int Fire(char **opponenetGrid, char **DisplayedGrid, char *coordinates, char *mode, int *ship);
int Artillery(char **opponentGrid, char **DisplayedGrid, char *coordinate, char *mode, int flag, int *ship);
int Torpedo(char **opponentGrid, char **DisplayedGrid, char *coordinates, char *mode, int *ship, int flag, int counter);
int RadarSweep(char **grid, char **displayedGrid, char *coordinate, int radarSweepsUsed, int **smokeGrid);
int SmokeScreen(int **smokeGrid, char *coordinate, int shipsSunk, int smokeScreensUsed);
#endif
