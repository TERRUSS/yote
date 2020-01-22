#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "../controler/point.h"
#include "utils.h"
#include "../utils/utils.h"
#include "../model/game.h"
#include "../controler/save.h"


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MARGE_TOP 0
#define MARGE_LEFT 300
#define SPRITE_WIDTH 70
#define SPRITE_HEIGHT 70

#define BTN_WIDTH 400
#define BTN_HEIGHT 130
enum {JVJ, JVIA, SCORE, BACK};

#define HIT_BOX_WIDTH 51
#define HIT_BOX_HEIGHT 53

#define PAWN_SELECT_OPACITY 255
#define PAWN_UNSELECT_OPACITY 200

// enum {WHITE, BLACK}

SDL_Window* window;
SDL_Surface* cell_sprite_blue;
SDL_Surface* cell_sprite_red;
SDL_Surface* white_pawn_sprite;
SDL_Surface* black_pawn_sprite;
SDL_Surface* btn_jvj;
SDL_Surface* btn_jvia;
SDL_Surface* btn_score;
SDL_Surface* btn_back;

SDL_Surface* menubg;
SDL_Surface* btn_back;

SDL_Renderer* renderer; // Création d'un SDL_Renderer (pour l'accélération matérielle)
TTF_Font *font;
SDL_Surface* textSurface;
SDL_Color textColor;

/*---------------- UTILS ----------------*/
void initGraphics();
void quitGraphics();
void render();
void print (Point pt, char* text, int color);

/*--------- PRINTING FUNCTIONS ----------*/
void print_board_cell(int color, Point pt);
void print_pawn(int color, Point pt,Uint8 alpha);
void print_stock(int color, int number,Uint8 alpha);
void displayBoard(Game * game);
void backgroundColor(int r, int g, int b);
void backgroundImage(int image);

void updateBoard(Game * game);
void displayPlayerName(Game * game);
void print_hover_cell(Point coord);
void print_score(Player * player);
void print_select_stock(int color,int number);
void print_button(Point pt, int type);

void VictoryScreen (Player * winner);
void printLeaderboard();
