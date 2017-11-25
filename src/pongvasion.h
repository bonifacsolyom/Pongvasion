#pragma once

#include <stdbool.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "global.h"
#include "pad.h"
#include "ball.h"
#include "random.h"
#include "enemy.h"
#include "score.h"

#define SCORES_TO_SAVE 10
#define MILLISECONDS_IN_A_SECOND 1000
#define FPSLIMIT 60
#define TICKS_PER_SECOND 60

enum TimerEnum {
	TIMER_FPS,
	TIMER_TICK
};

bool initSDL(char*);
void closeGame(Score *, int);
Uint32 timerCallbackSDL(Uint32, void*);
void initTimers();
void logErrorSDL(char*);
void renderCurrentState();
bool updateGameState(const uint8_t*);
void start();