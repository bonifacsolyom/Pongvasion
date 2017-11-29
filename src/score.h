#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>

#include "global.h"

int globalScore;


/*
 * @struct Score
 * Represents a score that's displayed at the end of the game
 */
typedef struct Score {
	char *date;
	int score;
} Score;


/*
 * @struct HighScoreTexture
 * The graphics of the score that's displayed at the end of the game
 */
typedef struct HighScoreTexture {
	SDL_Texture *texture;
	int width;
	int height;
} HighScoreTexture;

/*
 * Loads the score font, sets its color
 * Allocates memory for the high score graphics
 * @param arraySize the size of the HighScoreTexture array
 */
void initScore(int arraySize);

/*
 * Gets the local time, and returns it in string form
 * Used to identify the scores
 * @return the current time string in yy/mm/dd-hh:mm:ss form
 */
char *getCurrentTime();

/*
 * Reads the high scores from scores.txt, and stores them in the given scoreArray
 * @param scoreArray for storing the scores
 * @param arraySize the size of scoreArray
 */
void readHighScoresFromFile(Score *scoreArray, int arraySize);

/*
 * Writes the new score to scores.txt if it's bigger than what's already in there.
 * @param scoreArray for storing the scores
 * @param arraySize the size of scoreArray
 * @return The position of the current score on the high score list, so it can be highlighted by yellow.
 * SCORES_TO_SAVE if the current score wasn't saved due to not being big enough.
 */
int writeHighScoreToFile(Score *scoreArray, int arraySize);

/*
 * Updates the score display in the top right corner shown during the game
 */
void updateScore();

/*
 * Renders the current score in the top right corner
 */
void renderScore();

/*
 * Renders the high score screen at the end of the game
 * @param scoreArray with the scores read in from the file + the current one added if necessary
 * @param arraySize the size of scoreArray
 * @param currentScorePosition the position of the currently achieved score so that it can be highlighted by yellow
 * Equals to arraySize in case the score was lower than all the previously achieved ones
 */
void renderHighScoreScreen(Score *scoreArray, int arraySize, int currentScorePosition);

/*
 * Frees the memory allocated for the score and highScore arrays
 * Calls the necessary SDL_TTF functions for exiting
 * @param scoreArray with the high scores
 * @param arraySize the size of scoreArray
 */
void cleanUpScores(Score *scoreArray, int arraySize);

