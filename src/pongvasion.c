#include "pongvasion.h"

//Initializes SDL and handles all errors
bool initSDL(char* title) {
	bool success = true;

	//TODO: AUTOMATIC SCREEN RESOLUTION DETECION
	globalWindowWidth = 1280;
	globalWindowHeight = 720;


	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		logErrorSDL("Unable to initialize SDL: %s");
		success = false;
	} else {

		globalWindow = SDL_CreateWindow(title,
								  SDL_WINDOWPOS_CENTERED,
								  SDL_WINDOWPOS_CENTERED,
								  globalWindowWidth,
								  globalWindowHeight,
								  0); //TODO: SDL_FULLSCREEN
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

	return success;
}

//Safely closes the program
void close() {
	SDL_DestroyWindow(globalWindow);
	SDL_Quit();
}

//The event that's called by SDL's timers. It sends an SDL_USEREVENT to the message queue with a parameter attached
Uint32 timerCallbackSDL(Uint32 interval, void *param) {
	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user.code = (int)param;
	SDL_PushEvent(&event);

	return interval;

}

//Initializes SDL timers
void initTimers() {
	int delayBetweenFrames = MILLISECONDS_IN_A_SECOND / FPSLIMIT;
	int tickRate = MILLISECONDS_IN_A_SECOND / TICKS_PER_SECOND;
	if (SDL_AddTimer(delayBetweenFrames, timerCallbackSDL, (int *)TIMER_FPS) == 0) {
		logErrorSDL("Error while creating the FPS timer!"); 
	}
	if (SDL_AddTimer(tickRate, timerCallbackSDL, (int *)TIMER_TICK) == 0) {
		logErrorSDL("Error while creating the TICK timer!");
	}
}

//A simple SDL logger that makes life easier
void logErrorSDL(char* errorMessage) {
	printf("%s\n%s", errorMessage, SDL_GetError());
}

void renderCurrentState() {
	SDL_SetRenderDrawColor(globalRenderer, 0, 0, 0, 255);
	SDL_RenderClear(globalRenderer);

	renderPads();
	renderBall();

	SDL_RenderPresent(globalRenderer);
}

void updateGameState(const uint8_t *keyboardState) {
	updatePads(keyboardState);
	updateBall();
}

void start() {
	bool isGameRunning = true;
	char *windowTitle = "Pongvasion";
	
	initSDL(windowTitle);
	initTimers();
	
	initRandom();

	initPads();
	initBall();

	const uint8_t *keyboardState = SDL_GetKeyboardState(0); //Updates every time SDL_PollEvent() is called
	
	while (isGameRunning) {
		SDL_Event sdlEvent;

		while (SDL_PollEvent(&sdlEvent)) {
			switch (sdlEvent.type) {
			case SDL_USEREVENT:
				if (sdlEvent.user.code == TIMER_TICK) {
					updateGameState(keyboardState);
				} else if (sdlEvent.user.code == TIMER_FPS ) {
					renderCurrentState();
				}
				break;
			case SDL_QUIT:
				isGameRunning = false;
				break;
			}
		}
	}

	close();
}
