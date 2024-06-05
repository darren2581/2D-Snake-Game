#include <stdio.h>
#include <stdlib.h>
#include "box.h"
#include "terminal.h"
#include "random.h"
#include "LinkedList.h"

void createBox(int Row, int Column, const char *filename) {
    LinkedList* playerMoves = createLinkedList(); /* Declaration and initialization of playerMoves*/
    LinkedList* snakeMoves = createLinkedList(); /* Declaration and initialization of snakeMoves*/
    char keys; /* Variable to store the key pressed by the user */
    int SRow, SColumn, PRow, PColumn, FRow, FColumn; /* Variables to store the row and column positions of snake, player, and food */
    Row = Row + 2; /* Set the number of rows for the inner space */
    Column = Column +2; /* Set the number of columns for the inner space */
    char PlayGround[Row][Column]; /* Declare a 2D array to store the playground */
    int i, j, UpdatedRow, UpdatedColumn, tildeRow, tildeColumn, randMove, dRow, dColumn; /* Declare variables */
    FILE* file = fopen(filename, "r"); /* Open the file for reading */
    if (file == NULL) /* Check if file opening failed */
    {
        printf("Error opening file.\n");
        return;
    }
    
    fscanf(file, "%d %d", &PRow, &PColumn); /* Read rows and columns from the file */
    int Player = 0; /* Initialize the player position */
    int Food = 0; /* Initialize the food position */
    int Snake = 0; /* Initialize the snake position */
    int playerCount = 0; /* Counter for '1' occurrences */
    int foodCount = 0; /* Counter for '2' occurrences */
    int snakeCount = 0; /* Counter for '3' occurrences */
    for (i = 1; i < Row - 1; i++)  /* Loop through each row of the txt file */
    {
        for (j = 1; j < Column - 1; j++)  
        {
            int cell; /* Variable to store the cell value */
            fscanf(file, "%d", &cell); /* Read the cell value from the file */
            if (cell == 1)  /* Check if the cell value is 1 */
            {
                playerCount++; /* Increment the player count */
                if (playerCount > 1) /* If '1' occurs more than once, exit the program */
                {
                    printf("Invalid file format. Please make sure there is exactly one '1', '2', and '3' in the file!\n");
                    fclose(file);
                    return;
                }
                PRow = i;
                PColumn = j;
                Player = 1;
            }
            if (cell == 2)  /* Check if the cell value is 2 */
            {
                foodCount++; /* Increment the food count */
                if (foodCount > 1) /* If '2' occurs more than once, exit the program */
                {
                    printf("Invalid file format. Please make sure there is exactly one '1', '2', and '3' in the file!\n");
                    fclose(file);
                    return;
                }
                FRow = i;
                FColumn = j;
                Food = 2;
            }
            if (cell == 3)  /* Check if the cell value is 3 */
            {
                snakeCount++; /* Increment the snake count */
                if (snakeCount > 1) /* If '3' occurs more than once, exit the program */
                {
                    printf("Invalid file format. Please make sure there is exactly one '1', '2', and '3' in the file!\n");
                    fclose(file);
                    return;
                }
                SRow = i;
                SColumn = j;
                Snake = 3;
            }
        }
    }
    fclose(file);

    if (Player != 1 || Food != 2 || Snake != 3)  /* Check if the player, food, and snake positions are valid */
    {
        printf("Invalid file format. Please make sure that '1', '2' and '3' is included!\n");
        return;
    }

    for (i = 0; i < Row; i++) /* Initialize the Playground with empty space */
    {
        for (j = 0; j < Column; j++) /* Loop through each cell of the playground */
        {
            if (i == 0 || i == Row - 1 || j == 0 || j == Column - 1) /* Check if the cell is on the border */
            {
                PlayGround[i][j] = '*'; /* Set the border cell to '*' */
            }
            else
            {
                PlayGround[i][j] = ' '; /* Set the inner cell to empty space */
            }
        }
    }
    insertPlayer(playerMoves, PRow, PColumn); /* Insert the player position into the linked list */
    insertSnake(snakeMoves, SRow, SColumn); /* Insert the snake position into the linked list */
    PlayGround[PRow][PColumn] = 'P'; /* Set the initial position of 'P' */
    PlayGround[SRow][SColumn] = '~'; /* Set the initial position of '~' */
    PlayGround[FRow][FColumn] = '@'; /* Set the position of '@' */
    UpdatedRow = PRow;    /* Initial row position of 'P' */
    UpdatedColumn = PColumn; /* Initial column position of 'P' */
    tildeRow = SRow;   /* Initial row position of '~' */
    tildeColumn = SColumn; /* Initial column position of '~' */
    while (1)
    {
        system("clear");
        for (i = 0; i < Row; i++) /* Print the playground*/
        {
            for (j = 0; j < Column; j++)
            {
                printf("%c", PlayGround[i][j]);
            }
            printf("\n");
        }
        printf("Press 'w' key to move up\n");
        printf("Press 's' key to move down\n");
        printf("Press 'a' key to move left\n");
        printf("Press 'd' key to move right\n");
        printf("Press 'u' key to undo the last move\n");
        disableBuffer(); /* Disable the buffer to read the key without pressing Enter*/
        keys = getchar(); /* Read the key pressed by the user*/
        enableBuffer(); /* Enable the buffer to read the key normally*/
        if (keys == 'w' || keys == 's' || keys == 'a' || keys == 'd')
        {
            PlayGround[UpdatedRow][UpdatedColumn] = ' '; /* Clear the old position of 'P'*/
            if (keys == 'w') 
            {
                UpdatedRow = (UpdatedRow - 1 + Row) % Row; 
                if (UpdatedRow == 0)  /* Wrap around to the bottom if reaching the top border*/
                {
                    UpdatedRow = Row - 2; 
                }
            } 
            if (keys == 's') 
            {
                UpdatedRow = (UpdatedRow + 1) % Row;
                if (UpdatedRow == Row - 1) /* Wrap around to the top if reaching the bottom border*/
                {
                    UpdatedRow = 1; 
                }
            }
            if (keys == 'a') 
            {
                UpdatedColumn = (UpdatedColumn - 1 + Column) % Column;
                if (UpdatedColumn == 0) /* Wrap around to the right if reaching the left border*/
                {
                    UpdatedColumn = Column - 2; 
                }
            }
            if (keys == 'd')
            {
                UpdatedColumn = (UpdatedColumn + 1) % Column;
                if (UpdatedColumn == Column - 1) /* Wrap around to the left if reaching the right border*/
                {
                    UpdatedColumn = 1; 
                }
            }

            insertPlayer(playerMoves, UpdatedRow, UpdatedColumn); /* Insert the move into the linked list*/
            insertSnake(snakeMoves, SRow, SColumn); /* Insert the move into the linked list*/
            PlayGround[UpdatedRow][UpdatedColumn] = 'P'; /* Set the new position of 'P'*/
        }
        if (keys == 'u') {
            Node *prevPlayerMove = removeLastPlayer(playerMoves); /* Remove the last player move from the linked list*/
            Node *prevSnakeMove = removeLastSnake(snakeMoves); /* Remove the last snake move from the linked list*/
            if (prevPlayerMove != NULL && prevSnakeMove != NULL) /* Check if the moves are valid*/
            { 
                PlayGround[UpdatedRow][UpdatedColumn] = ' '; /* Clear the old position of 'P'*/
                PlayGround[SRow][SColumn] = ' '; /* Clear the old position of '~'*/

                UpdatedRow = prevPlayerMove->row; /* Update the row position of 'P'*/
                UpdatedColumn = prevPlayerMove->column; /* Update the column position of 'P'*/
                SRow = prevSnakeMove->row; /* Update the row position of '~'*/
                SColumn = prevSnakeMove->column; /* Update the column position of '~'*/

                PlayGround[UpdatedRow][UpdatedColumn] = 'P'; /* Set the new position of 'P'*/
                PlayGround[SRow][SColumn] = '~'; /* Set the new position of '~'*/

                tildeRow = SRow; /* Update the row position of '~'*/
                tildeColumn = SColumn; /* Update the column position of '~'*/
            } 
            else 
            {
                printf("Cannot undo further.\n");
            }
        }

        if (keys == 'w' || keys == 's' || keys == 'a' || keys == 'd')
        {
            randMove = randomUCP(0, 7); /* Increase the range to include diagonal movements*/
            switch (randMove)
            {
            case 0: /* Move north*/
                if (tildeRow > 1)
                    tildeRow--;
                break;
            case 1: /* Move northeast*/
                if (tildeRow > 1 && tildeColumn < Column - 2)
                {
                    tildeRow--;
                    tildeColumn++;
                }
                break;
            case 2: /* Move east*/
                if (tildeColumn < Column - 2)
                    tildeColumn++;
                break;
            case 3: /* Move southeast*/
                if (tildeRow < Row - 2 && tildeColumn < Column - 2)
                {
                    tildeRow++;
                    tildeColumn++;
                }
                break;
            case 4: /* Move south*/
                if (tildeRow < Row - 2)
                    tildeRow++;
                break;
            case 5: /* Move southwest*/
                if (tildeRow < Row - 2 && tildeColumn > 1)
                {
                    tildeRow++;
                    tildeColumn--;
                }
                break;
            case 6: /* Move west*/
                if (tildeColumn > 1)
                    tildeColumn--;
                break;
            case 7: /* Move northwest*/
                if (tildeRow > 1 && tildeColumn > 1)
                {
                    tildeRow--;
                    tildeColumn--;
                }
                break;
            default:
                printf("Invalid move\n");
                break;
            }
        }
        
        PlayGround[SRow][SColumn] = ' '; /* Clear the old '~' position*/
        SRow = tildeRow; /* Update the row position of '~'*/
        SColumn = tildeColumn; /* Update the column position of '~'*/
        PlayGround[SRow][SColumn] = '~'; /* Set the new '~' position*/
        if (UpdatedRow == FRow && UpdatedColumn == FColumn) /* Check if the player found the food*/
        {
            system("clear");
            for (i = 0; i < Row; i++) /* Print the playground*/
            {
                for (j = 0; j < Column; j++) /* Loop through each cell of the playground*/
                {
                    printf("%c", PlayGround[i][j]);
                }
                printf("\n");
            }
            printf("Congratulations! You found the food. YOU WIN!\n");
            return 0;
        }
        dRow = abs(UpdatedRow - tildeRow); /* Calculate the absolute difference in row positions*/
        dColumn = abs(UpdatedColumn - tildeColumn); /* Calculate the absolute difference in column positions*/
        if ((dRow <= 1 && dColumn == 0) || (dRow == 0 && dColumn <= 1) || (dRow <= 1 && dColumn <= 1)) /* Check if the player and the snake are in the same row or column*/
        {
            system("clear");
            PlayGround[UpdatedRow][UpdatedColumn] = '~'; /* Set the position of '~'*/
            PlayGround[SRow][SColumn] = ' '; /* Clear the old position of '~'*/
            for (i = 0; i < Row; i++) /* Print the playground*/
            {
                for (j = 0; j < Column; j++)
                {
                    printf("%c", PlayGround[i][j]);
                }
                printf("\n");
            }
            printf("Game Over! You lost the game.\n");
            return 0;
        }
    }
}


