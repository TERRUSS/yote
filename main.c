#include "header.h"
#include "vue/header.h"

int main(void) {

	SDL_Window* window = 0;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		{
				SDL_Quit();
				return -1;
		}

	window = SDL_CreateWindow("Test SDL 2.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	print_pawn();

	sleep(5000);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}
