all:
	gcc src/main.c src/pongvasion.c src/ball.c src/pad.c src/random.c src/enemy.c src/score.c -g -Wall `sdl2-config --cflags` -o Pongvasion -lm -lSDL2 -lSDL2_gfx -lSDL2_ttf
