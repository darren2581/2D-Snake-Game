#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "random.h"

void initRandom() /* Function to initialize the random number generator*/
{
    srand(time(NULL));
}
int randomUCP(int low, int high) /* Function to generate a random number between low and high*/
{
    int number = -1; /* Variable to store the random number*/
    if (low <= high) /* Check if low is less than or equal to high*/
    {
        number = (rand() % (high - low + 1)) + low; /* Generate a random number between low and high*/
    }
    return number; /* Return the random number*/
}

