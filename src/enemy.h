#pragma once
#include <math.h>

#include <SDL2_gfxPrimitives.h>

#include "global.h"
#include "ball.h"

typedef struct Enemy {
	//Double because they were moving too quickly otherwise 
	double x;
	double y;
	int radius;
	double speed;
	int points;
	Color color;
} Enemy;

typedef struct EnemyListUnit {
	Enemy enemy;
	struct EnemyListUnit *previous, *next;
} EnemyListUnit;

typedef struct EnemyList {
	EnemyListUnit *first;
	EnemyListUnit *last;
} EnemyList;

void initEnemies();
void generateEnemies();
void spawnEnemy(Enemy);
bool updateEnemies();
void renderEnemies();
void freeEnemies();