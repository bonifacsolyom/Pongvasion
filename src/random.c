#include "random.h"

void initRandom() {
	srand((unsigned int)time(0));
}

bool randomBool() {
	return (bool)rand() % 2;
}

//Returns a random number between two integers
int randomNumber(int min, int max) {
	return rand() % (max - min) + min;
}