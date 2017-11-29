#pragma once
#include <math.h>

#include <SDL2_gfxPrimitives.h>

#include "global.h"
#include "ball.h"
#include "score.h"

/**
 * @struct Enemy
 * Represents an enemy on the screen (The colorful circles that have to be hit by the ball)
 */
typedef struct Enemy {
	double x;
	double y;
	int radius;
	double speed;
	int points;
	SDL_Color color;
} Enemy;

/**
 * @struct EnemyListUnit
 * Represents a unit of a linked list made out of enemies
 */
typedef struct EnemyListUnit {
	Enemy enemy;
	struct EnemyListUnit *previous, *next;
} EnemyListUnit;

/**
 * @struct EnemyList
 * Stores the first and the last sentinel of the enemy linked list
 */
typedef struct EnemyList {
	EnemyListUnit *first;
	EnemyListUnit *last;
} EnemyList;

/**
 * Initializes all the different kinds of enemies
 */
void initEnemies();

/**
 * Generates enemies with a random chance, easier enemies have a bigger chance of spawning
 * The amount of enemies on screen is also taken into account
 */
void generateEnemies();

/**
 * Initializes and adds a new enemy to the linked list of enemies
 * @param enemy The enemy that is to be spawned
 */
void spawnEnemy(Enemy enemy);

/**
 * Should be called when the ball hits the enemy
 * Increases the player's score according to the enemy's type
 * And then deletes the enemy from the linked list
 * @param enemyToDelete The enemy that is to be deleted
 */
void deleteEnemy(EnemyListUnit *enemyToDelete);

/**
 * Checks whether the given enemy is colliding with the ball or not
 * @param the enemy that the collision is checked with
 */
bool isCollidingWithBall(Enemy enemy);

/**
 * Updates the states of the enemies
 * @return true when one of them has hit the bottom of the screen, thus ending the game
 */
bool updateEnemies();

/**
* Renders all the enemies on the globalRenderer
*/
void renderEnemies();

/**
 * Frees the memory that was allocated for the enemies
 * Called when the user closes the program
 */
void freeEnemies();