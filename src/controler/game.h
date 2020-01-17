#pragma once

#include "../vue/graphics.h"
#include "../model/game.h"
#include "../vue/utils.h"

void gameLoop (Game * game);
void placePawnFromStock(Game * game);
void moveLoop(Game * game,Point point);
