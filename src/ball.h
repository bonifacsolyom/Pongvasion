#pragma once
#include <stdbool.h>
#include <stdint.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "global.h"
#include "random.h"
#include "pad.h"

int maxVerticalSpeed;

enum {
	LEFT_PAD,
	RIGHT_PAD
};

/**
 * @struct Ball
 * Stores the data of the Ball that's bouncing between the pads
 */
typedef struct Ball {
	//the coordinates of the top left corner of the ball
	int32_t x;
	int32_t y;
	int32_t radius;
	SDL_Color color;
	int32_t horizontalSpeed;
	int32_t verticalSpeed;
} Ball;

Ball ball;
/**
 * @struct Point
 * A coordinate, has a x and a y member.
 */
typedef struct Point {
	int x;
	int y;
} Point;

/**
 * Sets the ball's starting point, radius, speed, and color
 */
void initBall();

/**
 * Given a specific point, it returns the closest point on the Ball's edge to it
 * @param pointToCompareTo The point for which the closest point on the ball is needed
 */
Point getClosestPointOfBall(Point pointToCompareTo);

/**
 * Returns the point on the pad's innermost edge to which the ball's center the closest is
 * @param whichPad The pad that the ball is checked with, LEFT_PAD or RIGHT_PAD
 */
Point getClosestPointOfPad(int whichPad);

/**
 * Detects if the ball is colliding with anything, and changes its speed accordingly if so
 */
void detectBallCollision();

/**
 * Detects if the ball left the screen on the left or the right
 * @return true if the ball is out of bounds, otherwise false
 */
bool detectIfOutOfBounds();

/**
 * Moves the ball according to its speed
 * @return true if the ball is out of bounds on the left or the right, otherwise false
 */
bool updateBall();

/**
 * Renders the ball on the globalRenderer
 * Includes a few debug calls which draw the collision points of the ball and the pads
 */
void renderBall();