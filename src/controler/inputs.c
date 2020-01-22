#include "inputs.h"
#include <stdio.h>


void waitClick(Point * point){

	//int x, y;
	SDL_Event event;

	SDL_WaitEvent(&event);

	switch (event.type) {
		case SDL_WINDOWEVENT:
			if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) {
				quitGraphics();
			}
			break;
		case SDL_KEYUP:
			if ( event.key.keysym.sym == SDLK_ESCAPE ) {
				quitGraphics();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (SDL_BUTTON(1) ) {
				point->x = event.motion.x;
				point->y = event.motion.y;
			}
	}
}

int isInBoard_coord(Point mouse_pos){
	Point point = isoToCart(mouse_pos);
	if (point.x >=0 && point.x < CELL_R && point.y >=0 && point.y < CELL_C){
		return 1;
	}
	return 0;
}

int isInBoard(Point mouse_pos){
	if (mouse_pos.x >=0 && mouse_pos.x < CELL_R && mouse_pos.y >=0 && mouse_pos.y < CELL_C){
		return 1;
	}
	return 0;
}
