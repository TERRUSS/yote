#pragma once
#include "../model/game.h"

void saveScore(Player * winner);
int readScore (int line, char * score);
void parseString (Player * player);
void sortLeaderBoard(Player* leaderBoard);
void instertScore(Player * leaderBoard,Player * winner);
