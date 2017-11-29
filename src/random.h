#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


/*
 * Initializes the random generator
 */
void initRandom();

/*
 * Generates a random boolean
 * @return Either true or false
 */
bool randomBool();

/*
 * Generates a random number between two integers
 * @param min The lowest number that can be generated
 * @param max The highest number that can be generated
 * @return The number that was generated
 */
int randomNumber(int min, int max);