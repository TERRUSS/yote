#pragma once

#include "../vue/graphics.h"
#include "../model/game.h"
#include "../vue/utils.h"

int handleInputs(Game * game);
Point handleClick(Point click);
void mouvPawn(Game * game, Point position);
void stockToBoard(Game * game);
