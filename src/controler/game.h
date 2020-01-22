#pragma once

#include "../vue/graphics.h"
#include "../model/game.h"
#include "../model/ia.h"
#include "../vue/utils.h"

Player *  gameLoop (Game * game, int mode);
void placePawnFromStock(Game * game);
void moveLoop(Game * game,Point point);
void takePawn(Game * game);
