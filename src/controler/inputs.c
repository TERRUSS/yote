#include "input.h"
#include <stdio.h>


void handleInputs(Game * game){

	int quit = 0;
	int x, y;

	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_WINDOWEVENT:
			if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) {
				quit = 1;
			}
			break;
		case SDL_KEYDOWN:
			if ( event.key.keysym.sym == SDLK_ESCAPE ) {
				quit = 1;
			}
			break;
		default:
			if ( SDL_GetMouseState(&x, &y) & SDL_BUTTON(1) ) {
				Point click;
				click.x = x; click.y = y;

				handleClick(Point click);
			}
	}

	return quit;
}


void handleClick(Point click){

	Point coords = getCellCoordinates( isoToCart(click) );
	printf("click @[%d, %d]", coords.x, coords.y);

}
