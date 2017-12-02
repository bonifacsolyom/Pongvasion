#include "pongvasion.h"

bool initSDL(char* title) {
	bool success = true;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		logErrorSDL("Unable to initialize SDL: %s");
		success = false;
	} else {
		SDL_DisplayMode displayDetails;
		SDL_GetCurrentDisplayMode(0, &displayDetails);
		globalWindowWidth = displayDetails.w;
		globalWindowHeight = displayDetails.h;

		globalWindow = SDL_CreateWindow(title,
										SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										globalWindowWidth,
										globalWindowHeight,
										SDL_WINDOW_FULLSCREEN);
		if (globalWindow == 0) {
			logErrorSDL("Error while creating the window: %s");
			success = false;
		} else {
			globalRenderer = SDL_CreateRenderer(globalWindow, -1, SDL_RENDERER_ACCELERATED);
			if (globalRenderer == 0) {
				logErrorSDL("Failed to create the global renderer: %s");
				success = false;
			}
		}
	}

	if (TTF_Init() < 0) {
		printf("Unable to initialize SDL: %s\n", TTF_GetError());
		success = false;
	}
	return success;
}

void closeGame(Score *scoreArray, int arraySize, EnemyList enemyList, HighScoreTexture *highScoreArray) {
	freeEnemies(enemyList);
	cleanUpScores(scoreArray, arraySize, highScoreArray);
	SDL_DestroyWindow(globalWindow);
	TTF_Quit();
	SDL_Quit();
}

Uint32 timerCallbackSDL(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = (int)param;
	SDL_PushEvent(&event);

	return interval;
}

void initTimers() {
	int delayBetweenFrames = MILLISECONDS_IN_A_SECOND / FPSLIMIT;
	int tickRate = MILLISECONDS_IN_A_SECOND / TICKS_PER_SECOND;
	if (SDL_AddTimer(delayBetweenFrames, timerCallbackSDL, (int *)TIMER_FPS) == 0) {
		logErrorSDL("Error while creating the FPS timer!");
	}
	if (SDL_AddTimer(tickRate, timerCallbackSDL, (int *)TIMER_TICK) == 0) {
		logErrorSDL("Error while creating the tick timer!");
	}
}

void logErrorSDL(char* errorMessage) {
	printf("%s\n%s", errorMessage, SDL_GetError());
}

void renderCurrentState(EnemyList enemyList) {
	SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 255);
	SDL_RenderClear(globalRenderer);
	renderPads();
	renderEnemies(enemyList);
	renderBall();
	renderScore();

	SDL_RenderPresent(globalRenderer);
}

//Returns true when game is over
bool updateGameState(const uint8_t *keyboardState, EnemyList enemyList) {
	updatePads(keyboardState);
	bool ballOut = updateBall();
	generateEnemies(enemyList);
	bool enemyReached = updateEnemies(enemyList);
	updateScore();
	return ballOut || enemyReached;
}

void start() {
	bool isGameRunning = true;
	bool isGameOver = false;
	bool areScoresWrittenToFile = false;
	bool playerIsReadyToQuit = false;
	char *windowTitle = "Pongvasion";
	Score scoreArray[SCORES_TO_SAVE] = {0};
	EnemyList enemyList;
	HighScoreTexture *highScoreArray;

	initSDL(windowTitle);
	initTimers();
	initRandom();
	initPads();
	initBall();
	enemyList = initEnemies();
	highScoreArray = initScore(SCORES_TO_SAVE);

	const uint8_t *keyboardState = SDL_GetKeyboardState(0); //Updates every time SDL_PollEvent() is called

	SDL_Event sdlEvent;
	while (isGameRunning) {
		SDL_PollEvent(&sdlEvent);
		switch (sdlEvent.type) {
		case SDL_USEREVENT:
			if (sdlEvent.user.code == TIMER_TICK) {
				if (!isGameOver) {
					isGameOver = updateGameState(keyboardState, enemyList);
				}
			} else if (sdlEvent.user.code == TIMER_FPS) {
				if (!isGameOver) {
					renderCurrentState(enemyList);
				} else {
					int currentScorePosition;
					if (!areScoresWrittenToFile) {
						currentScorePosition = writeHighScoreToFile(scoreArray, SCORES_TO_SAVE);
						areScoresWrittenToFile = true;
					}
					renderHighScoreScreen(scoreArray, SCORES_TO_SAVE, currentScorePosition, highScoreArray);
				}
			}
			break;
		case SDL_QUIT:
			isGameRunning = false;
			break;
		case SDL_KEYDOWN:
			if (areScoresWrittenToFile && sdlEvent.key.repeat == 0) {
				isGameRunning = false;
			}
			break;
		}

	}

	closeGame(scoreArray, SCORES_TO_SAVE, enemyList, highScoreArray);
}
