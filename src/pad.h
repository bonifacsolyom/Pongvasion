#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "global.h"

typedef struct Pad {
	//the coordinates of the top left corner of the pad
	//Originally unsigned, but caused problems with integer arithmetic
	int32_t x;
	int32_t y;
	int32_t length;
	int32_t width;
	Color color;
} Pad;


Pad leftPad;
Pad rightPad;
int padSpeed;

void initPads();
bool checkBounds(Pad);
bool boundaryCheckUp();
bool boundaryCheckDown();
void updatePads(const uint8_t*);
void renderPads();
