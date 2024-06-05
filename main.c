#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"

int main(int argc, char *argv[]) {
    FILE *file; /* File pointer */
    int *Row, *Column; /* Pointers to store the number of rows and columns */

    if (argc != 2) { /* Check if the number of arguments is not equal to 2 */
        printf("Usage: %s <filename>\n", argv[0]); /* Print the usage of the program */
        return 1;
    }

    char *filename = argv[1]; /* Get the filename from the command line arguments */
    
    Row = (int *)malloc(sizeof(int)); /* Allocate memory to store the number of rows */
    if (Row == NULL) { /* Check if memory allocation failed */
        printf("Memory allocation failed.\n");
        return 1;
    }

    Column = (int *)malloc(sizeof(int)); /* Allocate memory to store the number of columns */
    if (Column == NULL) { /* Check if memory allocation failed */
        printf("Memory allocation failed.\n");
        free(Row); /* Free the allocated memory for rows */
        return 1;
    }

    file = fopen(argv[1], "r"); /* Open the file for reading */
    if (file == NULL) { /* Check if file opening failed */
        printf("Error opening file.\n");
        free(Row); /* Free the allocated memory for rows */
        free(Column); /* Free the allocated memory for columns */
        return 1;
    }

    /* Read rows and columns from the file */
    if (fscanf(file, "%d %d", Row, Column) != 2) {
        printf("Invalid file format.\n");
        fclose(file);
        free(Row); /* Free the allocated memory for rows */
        free(Column); /* Free the allocated memory for columns */
        return 1;
    }

    fclose(file);

    initRandom(); /* Initialize the random number generator */
    createBox(*Row, *Column, filename); /* Create the box with the given number of rows and columns */

    free(Row); /* Free the allocated memory for rows */
    free(Column); /* Free the allocated memory for columns */

    return 0;
    
}

