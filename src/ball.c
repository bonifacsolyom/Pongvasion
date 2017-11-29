#include "ball.h"


void initBall() {
	maxVerticalSpeed = globalWindowHeight / 90;

	ball.x = globalWindowWidth / 2;
	ball.y = globalWindowHeight / 2;
	ball.radius = globalWindowHeight / 24;
	ball.horizontalSpeed = randomBool() ? globalWindowHeight / 72 : -(globalWindowHeight / 72);
	ball.verticalSpeed = randomNumber(-maxVerticalSpeed, maxVerticalSpeed);
	ball.color.r = 255;
	ball.color.g = 255;
	ball.color.b = 255;
	ball.color.a = 255;
}

Point getClosestPointOfBall(Point pointToCompareTo) {
	Point returnPoint;
	//the degree of the line between the circle's midpoint and the given point
	double alpha = atan2(ball.y - pointToCompareTo.y, pointToCompareTo.x - ball.x);

	returnPoint.x = (int)round((double)ball.x + cos(alpha) * (double)ball.radius);
	returnPoint.y = (int)round((double)ball.y - sin(alpha) * (double)ball.radius);
	return returnPoint;
}

Point getClosestPointOfPad(int whichPad) {
	Point returnPoint;
	if (whichPad == LEFT_PAD) {
		if (ball.y <= leftPad.y) { //If the center of the ball is above the left pad
			returnPoint.y = leftPad.y;
			returnPoint.x = leftPad.x + leftPad.width;
		} else if (ball.y >= leftPad.y && (ball.y <= (leftPad.y + leftPad.length))) { //If the center of the ball is in line with the left pad
			returnPoint.y = ball.y;
			returnPoint.x = leftPad.x + leftPad.width;
		} else { //If the center of the ball is below the left pad
			returnPoint.y = leftPad.y + leftPad.length;
			returnPoint.x = leftPad.x + leftPad.width;
		}
	} else { //The right pad
		if (ball.y <= rightPad.y) { //If the center of the ball is above the right pad
			returnPoint.y = rightPad.y;
			returnPoint.x = rightPad.x;
		} else if (ball.y >= rightPad.y && (ball.y <= (rightPad.y + rightPad.length))) { //If the center of the ball is in line with the right pad
			returnPoint.y = ball.y;
			returnPoint.x = rightPad.x;
		} else { //If the center of the ball is below the right pad
			returnPoint.y = rightPad.y + rightPad.length;
			returnPoint.x = rightPad.x;
		}
	}

	return returnPoint;
}

void detectBallCollision() {
	//The radius in which collision is checked between the ball and the pad
	int collisionRadius = ball.horizontalSpeed;

	int ballTop = ball.y - ball.radius;
	int ballBottom = ball.y + ball.radius;

	//Detect if the ball is touching any of the two pads
	if (ball.horizontalSpeed > 0) { //If the ball is headed towards the right, we only need to check collision with the right pad
		if ((ballBottom >= rightPad.y) && (ballTop <= (rightPad.y + rightPad.length))) { //If the ball is in line with the pad
			Point closestPointOfPad = getClosestPointOfPad(RIGHT_PAD);
			Point closestPointOfBall = getClosestPointOfBall(closestPointOfPad);
			//The first check is to see whether the center of the ball has already surpassed the pad or not
			if ((ball.x <= rightPad.x) && (closestPointOfBall.x >= closestPointOfPad.x) && ((closestPointOfBall.x - collisionRadius) < closestPointOfPad.x)) {
				int rightPadMiddle = rightPad.y + (rightPad.length / 2);
				//(Distance of the ball from the middle of the pad) / (Length of the pad's half) -> This way we get a value between -1 and 1, which we then multiply with the maximum vertical speed.
				ball.verticalSpeed = (int)(((double)(closestPointOfBall.y - rightPadMiddle) / (double)(rightPad.length / 2)) * maxVerticalSpeed);
				ball.horizontalSpeed *= -1;
			}
		}
	} else { //The ball is headed towards the left pad
		if ((ballBottom >= leftPad.y) && (ballTop <= (leftPad.y + leftPad.length))) { //If the ball is in line with the pad
			Point closestPointOfPad = getClosestPointOfPad(LEFT_PAD);
			Point closestPointOfBall = getClosestPointOfBall(closestPointOfPad);
			//The first check is to see whether the center of the ball has already surpassed the pad or not
			if ((ball.x >= leftPad.x) && (closestPointOfBall.x <= closestPointOfPad.x) && ((closestPointOfBall.x - collisionRadius) > closestPointOfPad.x)) {
				int leftPadMiddle = leftPad.y + (leftPad.length / 2);
				//(Distance of the ball from the middle of the pad) / (Length of the pad's half) -> This way we get a value between -1 and 1, which we then multiply with the maximum vertical speed.
				ball.verticalSpeed = (int)(((double)(closestPointOfBall.y - leftPadMiddle) / (double)(leftPad.length / 2)) * maxVerticalSpeed);
				ball.horizontalSpeed *= -1;
			}
		}
	}

	//Detect if the ball is touching the top or bottom of the screen
	bool isBallTouchingTheTop = (ballTop + ball.verticalSpeed) < 0;
	bool isBallTouchingTheBottom = (ballBottom + ball.verticalSpeed) > globalWindowHeight;
	if (isBallTouchingTheTop || isBallTouchingTheBottom) ball.verticalSpeed *= -1;
}

void detectBallMaxSpeed() {
	if (ball.verticalSpeed > maxVerticalSpeed) ball.verticalSpeed = maxVerticalSpeed;
	else if (ball.verticalSpeed < -maxVerticalSpeed) ball.verticalSpeed = -maxVerticalSpeed;
}

bool detectIfOutOfBounds() {
	bool onTheRight = (ball.x - ball.radius) > globalWindowWidth;
	bool onTheLeft = (ball.x + ball.radius) < 0;
	return onTheRight || onTheLeft;
}

bool updateBall() {
	detectBallCollision();
	detectBallMaxSpeed();
	ball.x += ball.horizontalSpeed;
	ball.y += ball.verticalSpeed;
	return detectIfOutOfBounds();
}

void renderBall() {
	filledCircleRGBA(globalRenderer,
					 ball.x,
					 ball.y,
					 ball.radius,
					 ball.color.r,
					 ball.color.g,
					 ball.color.b,
					 ball.color.a);

#ifdef _DEBUG
	Point pointRight = getClosestPointOfPad(RIGHT_PAD);
	filledCircleRGBA(globalRenderer,
					 pointRight.x,
					 pointRight.y,
					 5,
					 255,
					 0,
					 0,
					 255);
	Point pointLeft = getClosestPointOfPad(LEFT_PAD);
	filledCircleRGBA(globalRenderer,
					 pointLeft.x,
					 pointLeft.y,
					 5,
					 255,
					 0,
					 0,
					 255);
	Point pointBallLeft = getClosestPointOfBall(pointLeft);
	filledCircleRGBA(globalRenderer,
					 pointBallLeft.x,
					 pointBallLeft.y,
					 5,
					 255,
					 0,
					 0,
					 255);
	Point pointBallRight = getClosestPointOfBall(pointRight);
	filledCircleRGBA(globalRenderer,
					 pointBallRight.x,
					 pointBallRight.y,
					 5,
					 255,
					 0,
					 0,
					 255);
#endif
}