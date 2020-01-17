#pragma once

#include "../vue/graphics.h"
#include "../model/game.h"
#include "../vue/utils.h"

void gameLoop (Game * game);
void placePawnFromStock(Game * game);
void movePawn2(Game * game,Point point);
