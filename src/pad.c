#include "pad.h"

Pad leftPad;
Pad rightPad;
int padSpeed;

void initPads() {
	
	padSpeed = 10;

	const int padDistanceFromScreenEdge = globalWindowWidth / 100; //TODO: EXPERIMENT WITH THIS NUMBER

	leftPad.width = globalWindowWidth / 100;
	rightPad.width = globalWindowWidth / 100;

	leftPad.length = globalWindowHeight / 6;
	rightPad.length = globalWindowHeight / 6;

	leftPad.x = padDistanceFromScreenEdge;
	leftPad.y = globalWindowHeight / 2;
	rightPad.x = globalWindowWidth - padDistanceFromScreenEdge - rightPad.width;
	rightPad.y = globalWindowHeight / 2;

	leftPad.color.r = 0;
	leftPad.color.g = 0;
	leftPad.color.b = 0;
	leftPad.color.a = 255;

	rightPad.color.r = 0;
	rightPad.color.g = 0;
	rightPad.color.b = 0;
	rightPad.color.a = 255;
}


void updatePads(const uint8_t *keyboardState) {
	if (keyboardState[SDL_SCANCODE_UP]) {
		leftPad.y -= padSpeed;
		rightPad.y -= padSpeed;
	}
	if (keyboardState[SDL_SCANCODE_DOWN]) {
		leftPad.y += padSpeed;
		rightPad.y += padSpeed;
	}
}

void renderPads() {
	boxRGBA(globalRenderer,
				  leftPad.x,
				  leftPad.y,
				  leftPad.x + leftPad.width,
				  leftPad.y + leftPad.length,
				  leftPad.color.r,
				  leftPad.color.g,
				  leftPad.color.b,
				  leftPad.color.a);
	boxRGBA(globalRenderer,
				  rightPad.x,
				  rightPad.y,
				  rightPad.x + rightPad.width,
				  rightPad.y + rightPad.length,
				  rightPad.color.r,
				  rightPad.color.g,
				  rightPad.color.b,
				  rightPad.color.a);
}






