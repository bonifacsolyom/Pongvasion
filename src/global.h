#pragma once
#include <SDL.h>

SDL_Renderer *globalRenderer;
SDL_Window *globalWindow;
int globalWindowWidth, globalWindowHeight;

typedef struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color;