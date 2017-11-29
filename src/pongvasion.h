#pragma once

#include <stdbool.h>
#include <stdio.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>

#include "global.h"
#include "pad.h"
#include "ball.h"
#include "random.h"
#include "enemy.h"
#include "score.h"

#define SCORES_TO_SAVE 10
#define MILLISECONDS_IN_A_SECOND 1000
#define FPSLIMIT 60
#define TICKS_PER_SECOND 60

enum TimerEnum {
	TIMER_FPS,
	TIMER_TICK
};

/*
 * Calls the basic SDL initializer function, and creates a window for the game
 * Also initializes SDL_TTF
 * @param title The title of the window (= the game's name)
 * @return False if there was an error, otherwise true
 */
bool initSDL(char *title);

/*
 * Safely closes the program
 * Should be called when the user quits the game
 * @param scoreArray the array that stores the scores read in from scores.txt
 * @param arraySize the size of scoreArray
 */
void closeGame(Score *scoreArray, int arraySize);

/*
 * The event that's called by SDL's timers.
 * It sends an SDL_USEREVENT to the message queue with a parameter attached.
 * @param interval The time that passes between two calls of the function in milliseconds
 * @param param The parameter that will be passed to the event queue with the sent SDL_USEREVENT
 * @return Returns the interval
 */
Uint32 timerCallbackSDL(Uint32 interval, void *param);

/*
 * Initializes SDL timers
 * Used for ticks and frames
 */
void initTimers();

/*
 * A simple SDL logger that makes life easier - prints out the given string with the most recent SDL error that occured
 * @param errorMessage The string that's to be printed
 */
void logErrorSDL(char* errorMessage);

/*
 * Calls every method that's needed to render the current state of the game
 */
void renderCurrentState();

/*
 * Calls every method that's needed to update the current state of the game
 * @param keyboardState The state of the keyboard that was received by calling SDL_GetKeyboardState()
 */
bool updateGameState(const uint8_t *keyboardState);

/*
 * Calls every initializer method
 * Contains the main game loop.
 */
void start();