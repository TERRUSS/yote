#pragma once

#define CELL_R 6
#define CELL_C 5

/*---------------- STRUCTURES ----------------*/

#define VIDE 0
#define MAX_NAME_LENGTH 50
enum {EMPTY, FILL, SELECTED, ACCESSIBLE};
enum {WHITE, BLACK};

#include "../controler/point.h"

typedef struct {
	int stock;	// pawns
	int score;
	char name[MAX_NAME_LENGTH];
	int color;
	int victory;
	Point firstPosition;
	Point secondPosition;
	Point thirdPosition;
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
	int currentPlayer;
} Game;


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../controler/inputs.h"



/*---------------- FUNCTIONS ----------------*/

void initGame( Game * game);
void game(Game * game);
int checkVictory(Game * game);
int pickPlayer ();
void roundPlayer (Game * game);

int isMovablePawn(Game * game, Point point);
int isInStock(Game * game,Point click);
void resetBoardAccessibility(Game * game);
