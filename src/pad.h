#pragma once

#include <stdbool.h>
#include <stdint.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "global.h"

typedef struct Pad {
	//The coordinates of the top left corner of the pad
	int32_t x;
	int32_t y;
	int32_t length;
	int32_t width;
	SDL_Color color;
} Pad;

Pad leftPad;
Pad rightPad;
int padSpeed;

/*
 * Initializes the speed, size, starting point and color of the two pads.
 */
void initPads();

/*
 * Checks if the next move of the pads would be out of bounds in the upward direction
 * @return true when it's okay to move, otherwise false.
 */
bool boundaryCheckUp();

/*
 * Checks if the next move of the pads would be out of bounds in the downward direction
 * @return true when it's okay to move, otherwise false.
 */
bool boundaryCheckDown();

/*
 * Checks for the up or down arrow being pressed
 * And updates the position of the pads accordingly
 */
void updatePads(const uint8_t*);

/*
 * Renders the pads on the globalRenderer
 *
 */
void renderPads();
