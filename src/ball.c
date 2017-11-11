#include "ball.h"

Ball ball;
const int maxVerticalSpeed = 5;

void initBall() {
	ball.x = globalWindowWidth / 2;
	ball.y = globalWindowHeight / 2;
	ball.radius = 15; //TODO: EXPERIMENT WITH THIS NUMBER
	ball.horizontalSpeed = randomBool() ? 10 : -10;
	ball.verticalSpeed = randomNumber(-maxVerticalSpeed, maxVerticalSpeed);
	ball.color.r = 255;
	ball.color.g = 255;
	ball.color.b = 255;
	ball.color.a = 255;
}

//Detects if the ball is colliding with anything, and changes its speed accordingly if so
void detectBallCollision() {

	int previousX = ball.x - ball.horizontalSpeed;
	int previousY = ball.y - ball.verticalSpeed;

	//Detect if touching any pads
	if (ball.horizontalSpeed > 0) { //If the ball is headed towards the left, we only need to check collision with the left pad
		if (ball.y >= rightPad.y && (ball.y <= (rightPad.y + rightPad.length))) { //The ball is in line with the pad
			if ((previousX + ball.radius) < rightPad.x && (ball.x + ball.radius) >= rightPad.x) {
				//(Distance of the ball from the middle of the pad) / (Length of the pad's half) -> This way we get a value between 0 and 1, which we then multiply with the maximum vertical speed.
				int rightPadMiddle = rightPad.y + (rightPad.length / 2);
				ball.verticalSpeed = ((double)(ball.y - rightPadMiddle) / (double)(rightPad.length / 2)) * maxVerticalSpeed;
				printf("%d\n", ball.verticalSpeed);
				ball.horizontalSpeed *= -1;
			}
		}
	} else { //The ball is headed towards the right pad
		if (ball.y >= leftPad.y && (ball.y <= (leftPad.y + leftPad.length))) { //The ball is in line with the pad
			if ((previousX - ball.radius) > (leftPad.x + leftPad.width) && (ball.x - ball.radius) <= (leftPad.x + leftPad.width)) {
				//(Distance of the ball from the middle of the pad) / (Length of the pad's half) -> This way we get a value between 0 and 1, which we then multiply with the maximum vertical speed.
				int leftPadMiddle = rightPad.y + (rightPad.length / 2);
				ball.verticalSpeed = ((double)(ball.y - leftPadMiddle) / (double)(leftPad.length / 2)) * maxVerticalSpeed;
				ball.horizontalSpeed *= -1;
			}
		}
	}

	//Detect if touching the top or bottom of the screen
	int ballTop = ball.y - ball.radius;
	int ballBottom = ball.y + ball.radius;
	bool isBallTouchingTheTop = (ballTop + ball.verticalSpeed) < 0;
	bool isBallTouchingTheBottom = (ballBottom + ball.verticalSpeed) > globalWindowHeight;
	if (isBallTouchingTheTop || isBallTouchingTheBottom) ball.verticalSpeed *= -1;
}

void detectBallMaxSpeed() {
	if (ball.verticalSpeed > maxVerticalSpeed) ball.verticalSpeed = maxVerticalSpeed;
	else if (ball.verticalSpeed < -maxVerticalSpeed) ball.verticalSpeed = -maxVerticalSpeed;
}

void updateBall() {
	detectBallCollision();
	detectBallMaxSpeed();
	ball.x += ball.horizontalSpeed;
	ball.y += ball.verticalSpeed;
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
}