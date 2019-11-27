#pragma once

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>

enum {IGE_LOGGING_TASK, IGE_LOGGING_STEP, IGE_FINISHED_TASK, IGE_STEP_ERROR};
enum {BOLD, ERROR};
#define SPRITE_WIDTH 100

SDL_Window* window;
SDL_Surface* pawn_sprite;
SDL_Renderer* renderer; // Création d'un SDL_Renderer utilisant l'accélération matérielle


void print_pawn(int x, int y);
void IGE_init();
void IGE_render();
void IGE_quit();
void IGE_log(int importance, const char* message);
void print_label(const char * label, int display);
void IGE_displayBoard(int *, int, int);
