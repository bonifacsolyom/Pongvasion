#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "global.h"

typedef struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
} Color;

typedef struct Pad {
	//the coordinates of the top left corner of the pad
	uint32_t x;
	uint32_t y;
	uint32_t length;
	uint32_t width;
	Color color;
} Pad;


void initPads();
bool checkBounds(Pad);
void updatePads(const uint8_t*);
void renderPads();
