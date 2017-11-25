#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include <SDL_ttf.h>

#include "global.h"

int globalScore;

typedef struct Score {
	char *date;
	int score;
} Score;

typedef struct HighScore {
	SDL_Texture *texture;
	int width;
	int height;
} HighScore;

void initScore(int);
void readHighScoresFromFile(Score *, int);
void writeHighScoreToFile(Score *, int);
void updateScore();
void renderScore();
void renderHighScoreScreen(Score *, int);
void cleanUpScores(Score *, int);

