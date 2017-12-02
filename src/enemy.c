#include "enemy.h"
#include "random.h"

Enemy easyEnemy;
Enemy normalEnemy;
Enemy hardEnemy;

EnemyList initEnemies() {
	easyEnemy.radius = globalWindowHeight / 14;
	easyEnemy.points = 10;
	easyEnemy.speed = (double)globalWindowHeight / 7200;
	easyEnemy.color.r = 0;
	easyEnemy.color.g = 255;
	easyEnemy.color.b = 0;
	easyEnemy.color.a = 255;
	easyEnemy.points = 10;

	normalEnemy.radius = globalWindowHeight / 20;
	normalEnemy.points = 25;
	normalEnemy.speed = (double)globalWindowHeight / 3600;
	normalEnemy.color.r = 0;
	normalEnemy.color.g = 0;
	normalEnemy.color.b = 255;
	normalEnemy.color.a = 255;
	normalEnemy.points = 50;

	hardEnemy.radius = globalWindowHeight / 28;
	hardEnemy.points = 50;
	hardEnemy.speed = (double)globalWindowHeight / 1440;
	hardEnemy.color.r = 255;
	hardEnemy.color.g = 0;
	hardEnemy.color.b = 0;
	hardEnemy.color.a = 255;
	hardEnemy.points = 100;

	EnemyList enemyList;
	enemyList.first = malloc(sizeof(EnemyListUnit));
	enemyList.last = malloc(sizeof(EnemyListUnit));
	enemyList.first->next = enemyList.last;
	enemyList.last->previous = enemyList.first;
	return enemyList;
}

void generateEnemies(EnemyList enemyList) {
	int enemyCount = 0;
	EnemyListUnit *movingPointer = enemyList.first;
	while (movingPointer->next != enemyList.last) {
		enemyCount++;
		movingPointer = movingPointer->next;
	}
	if (randomNumber(1, 10 * (enemyCount + 1) * (enemyCount + 1)) == 1) {
		spawnEnemy(easyEnemy, enemyList);
	} else if (randomNumber(1, 50 * (enemyCount + 1) * (enemyCount + 1)) == 1) {
		spawnEnemy(normalEnemy, enemyList);
	} else if (randomNumber(1, 100 * (enemyCount + 1) * (enemyCount + 1)) == 1) {
		spawnEnemy(hardEnemy, enemyList);
	}
}

void spawnEnemy(Enemy enemy, EnemyList enemyList) {
	EnemyListUnit *newListUnit = (EnemyListUnit *)malloc(sizeof(EnemyListUnit));
	enemyList.last->previous->next = newListUnit;
	newListUnit->previous = enemyList.last->previous;
	enemyList.last->previous = newListUnit;
	newListUnit->next = enemyList.last;

	enemyList.last->previous->enemy = enemy;
	enemyList.last->previous->enemy.y = -enemyList.last->previous->enemy.radius;
	enemyList.last->previous->enemy.x = randomNumber(leftPad.x + leftPad.width + enemyList.last->previous->enemy.radius, rightPad.x - enemyList.last->previous->enemy.radius);
}

void deleteEnemy(EnemyListUnit *enemyToDelete) {
	globalScore += enemyToDelete->enemy.points;
	//The following is done so the player can't exploit the ball bouncing between the two pads with a vertical speed of 0
	switch (randomNumber(1, 3)) {
	case 1: 
		ball.verticalSpeed += 1;
		break;
	case 2:
		ball.verticalSpeed -= 1;
		break;
	default:
		break;
	}
	EnemyListUnit *temp = enemyToDelete;
	enemyToDelete->previous->next = enemyToDelete->next;
	enemyToDelete->next->previous = enemyToDelete->previous;
	free(enemyToDelete);
}

//Checks whether the given enemy is colliding with the ball
bool isCollidingWithBall(Enemy enemy) {
	int deltaX = (int)enemy.x - ball.x;
	int deltaY = (int)enemy.y - ball.y;
	int distanceSquared = deltaX*deltaX + deltaY*deltaY;
	int maxDistanceSquared = (enemy.radius + ball.radius) * (enemy.radius + ball.radius);
	return distanceSquared <= maxDistanceSquared;
}

bool updateEnemies(EnemyList enemyList) {
	EnemyListUnit *movingPointer = enemyList.first->next;
	while (movingPointer != enemyList.last) {
		if ((movingPointer->enemy.y + movingPointer->enemy.radius) >= globalWindowHeight) return true;
		if (isCollidingWithBall(movingPointer->enemy)) {
			deleteEnemy(movingPointer);
			break; //Temporary hack that will probably stay here forever
		}
		movingPointer->enemy.y += movingPointer->enemy.speed;
		movingPointer = movingPointer->next;
	}
	return false;
}

void renderEnemies(EnemyList enemyList) {
	EnemyListUnit *movingPointer = enemyList.first->next;
	while (movingPointer != enemyList.last) {
		filledCircleRGBA(globalRenderer,
						 (int)movingPointer->enemy.x,
						 (int)movingPointer->enemy.y,
						 movingPointer->enemy.radius,
						 movingPointer->enemy.color.r,
						 movingPointer->enemy.color.g,
						 movingPointer->enemy.color.b,
						 movingPointer->enemy.color.a);
		movingPointer = movingPointer->next;
	}
}

//Frees the memory, should be called when exiting the program
void freeEnemies(EnemyList enemyList) {
	EnemyListUnit *movingPointer = enemyList.first;
	while (movingPointer != enemyList.last) {
		EnemyListUnit *next = movingPointer->next;
		free(movingPointer);
		movingPointer = next;
	}
	free(enemyList.last);
}