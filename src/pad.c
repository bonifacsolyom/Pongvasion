#include "pad.h"

void initPads() {

	padSpeed = 10;

	const int padDistanceFromScreenEdge = globalWindowWidth / 100; //TODO: EXPERIMENT WITH THIS NUMBER

	leftPad.width = globalWindowWidth / 100;
	rightPad.width = globalWindowWidth / 100;

	leftPad.length = globalWindowHeight / 6;
	rightPad.length = globalWindowHeight / 6;

	leftPad.x = padDistanceFromScreenEdge;
	leftPad.y = globalWindowHeight / 2 - (leftPad.length / 2);
	rightPad.x = globalWindowWidth - padDistanceFromScreenEdge - rightPad.width;
	rightPad.y = (globalWindowHeight / 2) - (rightPad.length / 2);

	leftPad.color.r = 255;
	leftPad.color.g = 255;
	leftPad.color.b = 255;
	leftPad.color.a = 255;

	rightPad.color.r = 255;
	rightPad.color.g = 255;
	rightPad.color.b = 255;
	rightPad.color.a = 255;
}

//Checks if the next move of the pads would be out of bounds in the upward direction
//returns true when it's okay to move, otherwise false.
bool boundaryCheckUp() {
	//The position of the two pads should always be the same, we're checking for both just in case
	if (((leftPad.y - padSpeed) < 0) || ((rightPad.y - padSpeed) < 0)) return false;
	return true;
}

//Checks if the next move of the pad would be out of bounds in the downwards direction
//returns true when it's okay to move, otherwise false.
bool boundaryCheckDown() {
	//The position of the two pads should always be the same, we're checking for both just in case
	if ((((leftPad.y + leftPad.length) + padSpeed) > globalWindowHeight) || (((rightPad.y + rightPad.length) + padSpeed) > globalWindowHeight)) return false;
	return true;
}

void updatePads(const uint8_t *keyboardState) {
	if (keyboardState[SDL_SCANCODE_UP]) {
		if (boundaryCheckUp()) {
			leftPad.y -= padSpeed;
			rightPad.y -= padSpeed;
		} else {
			leftPad.y = 0;
			rightPad.y = 0;
		}
	}
	if (keyboardState[SDL_SCANCODE_DOWN]) {
		if (boundaryCheckDown()) {
			leftPad.y += padSpeed;
			rightPad.y += padSpeed;
		} else {
			leftPad.y = globalWindowHeight - leftPad.length;
			rightPad.y = globalWindowHeight - leftPad.length;
		}
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






