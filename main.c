#include "header.h"

int int main(void) {

  SDL_Window* fenetre(0);

  if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        SDL_Quit();
        return -1;
    }

  window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  return 0;
}
