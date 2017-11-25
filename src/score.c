#include "score.h"

int globalScore = 0;
int previousScore = -1;
TTF_Font *scoreFont;
TTF_Font *highScoreFont;
SDL_Texture *scoreTexture;
SDL_Texture *highScoreTexture;
HighScore *highScoreArray;

SDL_Color scoreColor;
SDL_Color currentScoreColor;

int scoreSurfaceWidth;
int scoreSurfaceHeight;

bool createdHighScoreTextures = false;

void initScore(int arraySize) {
	scoreFont = TTF_OpenFont("data/04B_30__.ttf", globalWindowHeight / 24);
	highScoreFont = TTF_OpenFont("data/04B_30__.ttf", globalWindowHeight / 15);
	if (scoreFont == 0 || highScoreFont == 0) {
		printf("Error while loading the fonts: %s\n", TTF_GetError());
	}

	scoreColor.r = 255;
	scoreColor.g = 255;
	scoreColor.b = 255;
	scoreColor.a = 255;
	currentScoreColor.r = 255;
	currentScoreColor.g = 255;
	currentScoreColor.b = 0;
	currentScoreColor.a = 255;


	highScoreArray = (HighScore *)malloc(sizeof(HighScore) * arraySize);
}

//Returns the current date in string form
char *getCurrentTime() {
	time_t t = time(0);
	struct tm tm = *localtime(&t);
	char *returnString = (char *)malloc(sizeof(char) * 100);
	sprintf(returnString, "%d/%d/%d-%d:%d:%d", tm.tm_year % 100, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
#ifdef _DEBUG
	printf("returnString: %p\n", returnString);
#endif
	return returnString;
}

void readHighScoresFromFile(Score *scoreArray, int arraySize) {
	FILE *scoreFile;
	scoreFile = fopen("data/scores.txt", "r");
	if (scoreFile == 0) {
		printf("Could not open scores.txt!\n");
	}
	char buffer[255];
	for (int i = 0; i < arraySize; i++) {
		fscanf(scoreFile, "%s", buffer);
		scoreArray[i].date = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
		printf("scoreArray[%d].date: %p\n", i, scoreArray[i].date);
		strcpy(scoreArray[i].date, buffer);
		fscanf(scoreFile, "%d", &(scoreArray[i].score));
	}

}

int writeHighScoreToFile(Score *scoreArray, int arraySize) {
	readHighScoresFromFile(scoreArray, arraySize);

	int pos = 0; //The index which will get replaced by the global score
	while (pos < arraySize) {
		if (globalScore >= scoreArray[pos].score) break;
		pos++;
	}
	int currentScorePosition = pos;
	//Inserting the new high score in the top 10
	Score replaceScore;
	replaceScore.score = globalScore;
	replaceScore.date = getCurrentTime();
	Score tempScore;
	for (; pos < arraySize; pos++) {
		tempScore = scoreArray[pos];
		scoreArray[pos] = replaceScore;
		replaceScore = tempScore;
		if (pos == arraySize - 1) {
#ifdef _DEBUG
			printf("FREEING tempscore: %p\n", tempScore.date);
#endif
			free(tempScore.date);
		}
	}


	FILE *scoreFile;
	scoreFile = fopen("data/scores.txt", "w+");
	if (scoreFile == 0) {
		printf("Could not open scores.txt!\n");
	}
	for (int i = 0; i < arraySize; i++) {
		fprintf(scoreFile, "%s\n%d\n", scoreArray[i].date, scoreArray[i].score);
	}
	fclose(scoreFile);
	return currentScorePosition;
}


void updateScore() {
	if (previousScore != globalScore) {
		previousScore = globalScore;
		char scoreString[20];
		sprintf(scoreString, "Score: %d", globalScore); //Effectively creates a string out of an integer (globalScore)

		SDL_Surface* scoreSurface = TTF_RenderText_Solid(scoreFont, scoreString, scoreColor);
		if (scoreSurface == 0) {
			printf("Error while creating a surface for the score: %s\n", TTF_GetError());
		}
		scoreSurfaceWidth = scoreSurface->w;
		scoreSurfaceHeight = scoreSurface->h;
		scoreTexture = SDL_CreateTextureFromSurface(globalRenderer, scoreSurface);
		SDL_FreeSurface(scoreSurface);
	}
}

void renderScore() {
	int padding = globalWindowHeight / 100;
	//Placing the score in the upper right corner
	SDL_Rect targetRect;
	targetRect.x = globalWindowWidth - scoreSurfaceWidth - padding;
	targetRect.y = padding;
	targetRect.w = scoreSurfaceWidth;
	targetRect.h = scoreSurfaceHeight;

	SDL_RenderCopy(globalRenderer, scoreTexture, 0, &targetRect);
}

void renderHighScoreScreen(Score *scoreArray, int arraySize, int currentScorePosition) {
	SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 255);
	SDL_RenderClear(globalRenderer);

	for (int i = 0; i < arraySize; i++) {
		char highScoreString[50];
		if (strcmp(scoreArray[i].date, "0") != 0) {
			sprintf(highScoreString, "%s %d", scoreArray[i].date, scoreArray[i].score);
		} else {
			strcpy(highScoreString, " ");
		}
		//TTF_RenderText_Solid is a very cpu intensive method, so we have to make sure only to call it when necessary
		if (!createdHighScoreTextures) {
			SDL_Surface* highScoreSurface = TTF_RenderText_Solid(highScoreFont, highScoreString, (i == currentScorePosition) ? currentScoreColor : scoreColor);
			if (highScoreSurface == 0) {
				printf("Error while creating the SDL_Surface for the high scores: %s\n", SDL_GetError());
			} else {
				highScoreArray[i].width = highScoreSurface->w;
				highScoreArray[i].height = highScoreSurface->h;
				highScoreArray[i].texture = SDL_CreateTextureFromSurface(globalRenderer, highScoreSurface);
				SDL_FreeSurface(highScoreSurface);
			}
		}
		SDL_Rect targetRect;
		targetRect.x = (globalWindowWidth / 2) - (highScoreArray[i].width / 2);
		targetRect.y = ((globalWindowHeight - (highScoreArray[i].height / 2)) / arraySize) * i + (highScoreArray[i].height / 2);
		targetRect.w = highScoreArray[i].width;
		targetRect.h = highScoreArray[i].height;

		SDL_RenderCopy(globalRenderer, highScoreArray[i].texture, 0, &targetRect);
	}
	createdHighScoreTextures = true;

	SDL_RenderPresent(globalRenderer);
}

void cleanUpScores(Score *scoreArray, int arraySize) {
#ifdef _DEBUG
	printf("FREEING:\n");
#endif
	for (int i = 0; i < arraySize; i++) {
		//memset(scoreArray[i].date, 0xFF, );
		free(scoreArray[i].date);
#ifdef _DEBUG
		printf("scoreArray[%d].date: %p\n", i, scoreArray[i].date);
#endif
	}

	SDL_DestroyTexture(scoreTexture);
	TTF_CloseFont(scoreFont);
	TTF_CloseFont(highScoreFont);
	scoreFont = 0;
	highScoreFont = 0;
}