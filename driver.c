#include <ctype.h>
#include <stdio.h>

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "common_functions.c"
#include "player.c"
#include "bot.c"

#define ShipNumber 4
# define GridSize 10

int main()
{srand(time(NULL));
    char **Player = (char **)malloc(sizeof(char *) * 10);
char **Bot = (char **)malloc(sizeof(char *) * 10);
     gridInitialization(Player);

    printgrid(Player);
    char mode[10];
    printf("Whaat difficulty level do you want to play(easy,hard)? ");
    scanf("%9s", mode);
    to_lowercase(mode);
    while (strcmp(mode, "easy") != 0 && strcmp(mode, "hard") != 0)
    {
        printf("Invalid input!\n");
        printf("What difficulty level do you want to play(easy,hard)? ");
        scanf("%9s", mode);
    }
    printf("please enter your name: ");
    char name1[20];
    scanf("%19s", name1);
    int randplayer = rand() % 2;
  
    char **PlayerDisplayedGrid = (char **)malloc(sizeof(char *) * 10);
    char **BotDisplayedGrid = (char **)malloc(sizeof(char *) * 10);
    gridInitialization(PlayerDisplayedGrid);
    gridInitialization(BotDisplayedGrid);


    if (randplayer == 0)
    {
        printf("%s will start the game\n", name1);
    }
    else
    {
        printf("The bot will start the game\n");
    }
//in the initialization process between bot and player there is no difference who starts first
           fillGrid(Player, name1);
    printgrid(Player);

    printf("press enter if you have finished placing your ships ");
    getchar();
    getchar();
    clearConsole(); // or system("clear");
     ShipPlacment(Bot);


    // the players' ships
    int shipPlayer[ShipNumber] = {5, 3, 4, 2};
    int shipBot[ShipNumber] = {5, 3, 4, 2};
    int *other = shipPlayer;
    int *Curr = shipBot;

    int counterSunkByPlayer = 0;


    int radarSweepsPlayer = 0;


    int flagPlayer = 0;
    //2d array to keep tarck of smoked coordinates
int **playerSmoke = (int **)malloc(GridSize * sizeof(int *));
int **BotSmoke = (int **)malloc(GridSize * sizeof(int *));
int ** RadarGrid=(int **)malloc(GridSize * sizeof(int *));
for (int i = 0; i < GridSize; i++) {
    playerSmoke[i] = (int *)calloc(GridSize, sizeof(int));
    BotSmoke[i] = (int *)calloc(GridSize, sizeof(int));
    RadarGrid[i]=(int *)calloc(GridSize, sizeof(int));
}


int counterSunkByBot=0;

int smokeScreensUsedPlayer = 0;
int smokeScreensUsedBot = 0;


    printf("THE GAME WILL START!\n");
    int **heatmap = (int **)malloc(sizeof(int *) * 10);
    generateHeatmap(shipPlayer,heatmap,BotDisplayedGrid);

    if(randplayer==1){
        //will be changed shortly after
       botmove(Player,heatmap,BotDisplayedGrid,Curr,playerSmoke);
    }
   
    while (counterSunkByBot<4 && counterSunkByPlayer<4)
    {
        printf("\n%s this is  your opponent's current grid\n", name1);
        printgrid(PlayerDisplayedGrid);
        printf("The moves you can perform are:\n%4s\n%4s\n%4s\n%4s\n%4s", "1-Fire", "2-Radar", "3-Smoke", "4-Artillery", "5-Torpedo");
        printf("\nPlease %s , enter your command followed by the coordinate (e.g. Fire B3)\n", name1);

        char coordinate[4];
        char command[12];
        scanf("%s %s", command, coordinate);
        to_lowercase(command);

        int output;

        if (strcmp(command, "fire") == 0)
        {
            output = Fire(Bot, PlayerDisplayedGrid, coordinate, mode, other);
        }
        else if (strcmp(command, "radar") == 0)
        {       output = RadarSweep(Bot, PlayerDisplayedGrid, coordinate, radarSweepsPlayer, BotSmoke);
    if (output == 1) {
        radarSweepsPlayer++;
}}
        else if (strcmp(command, "smoke") == 0)
        {
               output = SmokeScreen(BotSmoke, coordinate, counterSunkByPlayer, smokeScreensUsedPlayer);
    if (output == 1) {
        smokeScreensUsedPlayer++;

        }}
        else if (strcmp(command, "artillery") == 0)
        {
             output = Artillery(Bot, PlayerDisplayedGrid, coordinate, mode,flagPlayer ,other);
        }
        else if (strcmp(command, "torpedo") == 0)
        {
             output=Torpedo(Bot,PlayerDisplayedGrid,coordinate,mode,other,flagPlayer,counterSunkByPlayer);
        }
        else
        {
            continue;
        }

        if (output == 1)
        {
            printf("\nThis is the updated grid\n");
            printgrid(PlayerDisplayedGrid);
            int increment = ShipsSunk(other);
            // flag to check if a ship was sunk within the current turn to unlock certain moves
            if (increment >= 1)
            {
                flagPlayer = 1;
            }
            else
            {
                flagPlayer = 0;
            }


            counterSunkByPlayer += increment;
        }
        else
        {
            printf("You have lost your turn\n");
        }

        printf("press enter to pass the turn ");
       getchar();
        getchar();
        clearConsole();

//call the bot function note will be chnaged shortly
counterSunkByBot=botmove(Player,heatmap,BotDisplayedGrid,Curr,playerSmoke);
 }
printf("The Game has ended\n");
if(counterSunkByPlayer>=4){
printf("Congratulations %s ! You have WON!!",name1);}
else{
printf("You LOST!");
}

    // Free the allocated memory 

    for (int i = 0; i < GridSize; i++)
    {
        free(Player[i]);
        free(Bot[i]);
    }
    free(Player);
    free(Bot);

    for (int i = 0; i < GridSize; i++) {
    free(playerSmoke[i]);
    free(BotSmoke[i]);
}

free(playerSmoke);
free(BotSmoke);


    return 0;

}

