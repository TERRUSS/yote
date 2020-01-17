#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../controler/point.h"


#define CELL_R 6
#define CELL_C 5

/*---------------- STRUCTURES ----------------*/

#define VIDE 0
#define MAX_NAME_LENGTH 50
enum {EMPTY, FILL, STOCK};
enum {WHITE, BLACK};

typedef struct {
	int stock;	// pawns
	int score;
	char name[MAX_NAME_LENGTH];
	int color;
	int victory;
	int playing;
	Point firstPosition;
	Point secondPosition;
} Player;

typedef struct {
	int state;
	int color;
} Cell;

typedef struct {
	Player black;
	Player white;
	int round;
	Cell board[CELL_R][CELL_C];
	int draw;
	int victory;
} Game;

/*---------------- FUNCTIONS ----------------*/

void initGame( Game * game);
void game(Game * game);
int checkVictory(Game * game);
int pickPlayer ();
void round (Game * game);
