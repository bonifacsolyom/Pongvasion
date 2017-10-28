#pragma once

#include <stdbool.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "global.h"
#include "pad.h"

#define MILLISECONDS_IN_A_SECOND 1000
#define FPSLIMIT 60
#define TICKS_PER_SECOND 60;

enum TimerEnum {
	TIMER_FPS,
	TIMER_TICK
};

bool initSDL(char*, SDL_Window*);
void close(SDL_Window*);
Uint32 timerCallbackSDL(Uint32, void*);
void initTimers();
void logErrorSDL(char*);
void renderCurrentState();
void updateGameState(const uint8_t*);
int start();