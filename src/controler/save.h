#pragma once
#include "../model/game.h"

void saveScore(Player * winner);
int readScore (int line, char * score);
void parseString (Player * player);
void sortLeaderBoard(Player* leaderBoard, int length);
void instertScore(Player * leaderBoard, int length, Player * winner);

#define MAXCHAR 256
