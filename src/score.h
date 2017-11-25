#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 

#include <stdio.h>
#include <time.h>
#include <string.h>

#include <SDL_ttf.h>

#include "global.h"

int globalScore;

typedef struct Score {
	char *date;
	int score;
} Score;

void initScore();
void readHighScoresFromFile(Score *, int);
void writeHighScoreToFile(Score *, int);
void updateScore();
void renderScore();
void renderHighScoreScreen();
void cleanUpScores(Score *, int);

