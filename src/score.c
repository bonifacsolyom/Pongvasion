#include "score.h"

int globalScore = 0;
int previousScore = -1;
TTF_Font *scoreFont;
TTF_Font *highScoreFont;
SDL_Texture *scoreTexture;
SDL_Texture *highScoreTexture;
HighScore *highScoreArray;

SDL_Color scoreColor;

int scoreSurfaceWidth;
int scoreSurfaceHeight;

bool createdHighScoreTextures = false;

void initScore(int arraySize) {
	//TODO: NO HARDCODED VALUES
	//TODO: ERROR HANDLING
	scoreFont = TTF_OpenFont("data/04B_30__.ttf", 28);
	highScoreFont = TTF_OpenFont("data/04B_30__.ttf", 50);

	scoreColor.r = 255;
	scoreColor.g = 255;
	scoreColor.b = 255;
	scoreColor.a = 255;


	highScoreArray = (HighScore *)malloc(sizeof(HighScore) * arraySize);
}

//Returns the current date in string form
char *getCurrentTime() {
	time_t t = time(0);
	struct tm tm = *localtime(&t);
	char *returnString = (char *)malloc(sizeof(char) * 100);
	sprintf(returnString, "%d/%d/%d-%d:%d:%d", tm.tm_year % 100, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("returnString: %p\n", returnString);
	return returnString;
}

void readHighScoresFromFile(Score *scoreArray, int arraySize) {
	FILE *scoreFile;
	//TODO: ERROR HANDLING
	scoreFile = fopen("data/scores.txt", "r");
	char buffer[255];
	for (int i = 0; i < arraySize; i++) {
		fscanf(scoreFile, "%s", buffer);
		scoreArray[i].date = (char *)malloc(sizeof(char) * (strlen(buffer) + 1));
		printf("scoreArray[%d].date: %p\n", i, scoreArray[i].date);
		strcpy(scoreArray[i].date, buffer);
		fscanf(scoreFile, "%d", &(scoreArray[i].score));
	}

}

void writeHighScoreToFile(Score *scoreArray, int arraySize) {
	readHighScoresFromFile(scoreArray, arraySize);

	int pos = 0; //The index which will get replaced by the global score
	while (pos < arraySize) {
		if (globalScore >= scoreArray[pos].score) break;
		pos++;
	}

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
			printf("FREEING tempscore: %p\n", tempScore.date);
	free(tempScore.date);
		}
	}


	FILE *scoreFile;
	//TODO: ERROR HANDLING
	scoreFile = fopen("data/scores.txt", "w+");
	for (int i = 0; i < arraySize; i++) {
		fprintf(scoreFile, "%s\n%d\n", scoreArray[i].date, scoreArray[i].score);
	}
	fclose(scoreFile);

}


void updateScore() {
	if (previousScore != globalScore) {
		previousScore = globalScore;
		char scoreString[20];
		sprintf(scoreString, "Score: %d", globalScore); //Effectively creates a string out of an integer (globalScore)

		SDL_Surface* scoreSurface = TTF_RenderText_Solid(scoreFont, scoreString, scoreColor);
		//TODO: ERROR HANDLING
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

void renderHighScoreScreen(Score *scoreArray, int arraySize) {
	SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 255);
	SDL_RenderClear(globalRenderer);

	//TODO: DON'T RENDER IF 0
	//TODO: HIGHLIGHT CURRENT SCORE WITH YELLOW
	for (int i = 0; i < arraySize; i++) {
		char highScoreString[50];
		sprintf(highScoreString, "%s: %d", scoreArray[i].date, scoreArray[i].score);
		//TTF_RenderText_Solid is a very cpu intensive method, so we have to make sure only to call it when necessary
		if (!createdHighScoreTextures) {
			SDL_Surface* highScoreSurface = TTF_RenderText_Solid(highScoreFont, highScoreString, scoreColor);
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
	printf("FREEING:\n");
	for (int i = 0; i < arraySize; i++) {
		//memset(scoreArray[i].date, 0xFF, );
		free(scoreArray[i].date);
		printf("scoreArray[%d].date: %p\n", i, scoreArray[i].date);
	}

	SDL_DestroyTexture(scoreTexture);
	TTF_CloseFont(scoreFont);
	TTF_CloseFont(highScoreFont);
	scoreFont = 0;
	highScoreFont = 0;
}