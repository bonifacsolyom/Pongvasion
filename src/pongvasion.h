#pragma once

#include <stdbool.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "global.h"

#define MILLISECONDS_IN_A_SECOND 1000

enum TimerEnum {
	TIMER_FPS,
	TIMER_TICK
};

bool initSDL(char*, SDL_Window*);
void close(SDL_Window*);
Uint32 timerCallbackSDL(Uint32, void*);
void initTimers(int);
void logErrorSDL(char*);
int start();