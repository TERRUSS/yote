#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include "../controler/point.h"
#include "utils.h"
#include "../utils/utils.h"
#include "../model/game.h"

#define LEN_MAX 50

int firstMenu(Game * game);
void recordText(char * input, Point inputPosition);
int selectMode ();
void getPlayerName (Game * game, int mode);
