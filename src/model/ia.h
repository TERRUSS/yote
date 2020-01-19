#pragma once

#include "../controler/point.h"
#include "../model/game.h"
#include <math.h>


void play_ia(Game * game);
void checkBestMove(Game * game,Point pt, Point move[2]);
void placePawnIa(Game * game);

int isSafeMove(Game * game, Point src,Point dst);
void checkSafeMove(Game * game,Point pt, Point move[2]);
void movePawnUseless(Game * game);

void eatSecondPawn(Game * game);
