#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define GridSize 10
#define ShipNumber 4

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
