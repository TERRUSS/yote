#pragma once

#include "../vue/graphics.h"
#include "../model/game.h"
#include "../vue/utils.h"


void waitClick(Point * point);
void mouvPawn_hugo(Game * game, Point position);

int isInBoard(Point mouse_pos);
int isInBoard_coord(Point mouse_pos);
