#pragma once

#define CELL_R 6
#define CELL_C 5

/*---------------- STRUCTURES ----------------*/

#define VIDE 0
#define MAX_NAME_LENGTH 50
enum {EMPTY, FILL};
enum {WHITE, BLACK};

typedef struct {
	int stock;	// pawns
	int deadPauns;

	int score;
	char name[MAX_NAME_LENGTH];
	int color;
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
} Game;

/*---------------- FUNCTIONS ----------------*/

void initGame( Game * game);
void game(Game * game);
