#pragma once

#include "../vue/graphics.h"
#include "../model/game.h"
#include "../vue/utils.h"


void waitClick(Point * point);
void mouvPawn(Game * game, Point position);
void stockToBoard(Game * game);
int isInBoard(Point mouse_pos);
