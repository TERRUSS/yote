#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "utils.h"
#include "../utils/utils.h"
#include "../model/game.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MARGE_TOP 0
#define MARGE_LEFT 300
#define SPRITE_WIDTH 70
#define SPRITE_HEIGHT 70

#define HIT_BOX_WIDTH 51
#define HIT_BOX_HEIGHT 53

SDL_Window* window;
SDL_Surface* cell_sprite_blue;
SDL_Surface* cell_sprite_red;
SDL_Surface* white_pawn_sprite;
SDL_Surface* black_pawn_sprite;
SDL_Renderer* renderer; // Création d'un SDL_Renderer (pour l'accélération matérielle)

/*---------------- UTILS ----------------*/
void initGraphics();
void quitGraphics();
void render();

/*--------- PRINTING FUNCTIONS ----------*/
void print_board_cell(int color, Point pt);
void print_pawn(int color, Point pt);
void displayBoard(Game * game);
void backgroundColor(int r, int g, int b);
void updateBoard(Game * game);
