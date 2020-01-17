#include "inputs.h"
#include <stdio.h>


int handleInputs(Game * game){

	int quit = 0;
	int x, y;

	SDL_Event event;

	SDL_WaitEvent(&event);


	switch (event.type) {
		case SDL_WINDOWEVENT:
		if ( event.window.event == SDL_WINDOWEVENT_CLOSE ) {
			quit = 1;
		}
		break;
		case SDL_KEYUP:
		if ( event.key.keysym.sym == SDLK_ESCAPE ) {
			quit = 1;
		}
		break;
		case SDL_MOUSEBUTTONDOWN:
		if ( SDL_GetMouseState(&x, &y) && SDL_BUTTON(1) ) {
			Point click;
			click.x = x; click.y = y;

			Point point = handleClick(click);

			game->board[point.x][point.y].state = FILL;
			game->board[point.x][point.y].color = WHITE;
		}
	}

	return quit;
}


Point handleClick(Point click){

	Point coords = isoToCart(click);

	printf("case @[%d, %d]  ", coords.x, coords.y);
	printf("click @[%d, %d]\n", click.x, click.y);


	return coords;
}


void mouvPawn(Game * game, Point position){

	Point click;
	Point point;
	Point nextPoint;
	int takePawn = 0;

	//select the next mouv
	do{
		point=handleClick(click);
	}while((point.x==position.x+1)||(point.x==position.x-1)||(point.y==position.y+1)||(point.y==position.y-1));

	if(game->board[point.x][point.y].state==EMPTY){
		position.x=point.x;
		position.y=point.y;
	}else{
		takePawn = 1;
		if (position.x == point.x) {

			if ((position.y >= point.y)&&(game->board[point.x][point.y-2].state==FILL)) {
				position.y=position.y-2;
			}else if((position.y <= point.y)&&(game->board[point.x][point.y+2].state==FILL)) {
				position.y=position.y+2;
			}
		}else if(position.y == point.y){

			if ((position.x >= point.x)&&(game->board[point.x-2][point.y].state==FILL)) {
				position.x=position.x-2;

			}else if((position.x <= point.x)&&(game->board[point.x+2][point.y].state==FILL)) {
				position.x=position.x+2;
			}
		}
	}
	//Score ++ if the player take an opponant's pawn
	if (takePawn == 1) {

		if (game->board[position.x][position.y].color==WHITE) {

			do {
				nextPoint=handleClick(click);
			} while((game->board[nextPoint.x][nextPoint.y].color==BLACK) && (nextPoint.x != point.x) && (nextPoint.y != point.y) && (game->board[nextPoint.x][nextPoint.y].state==FILL));

			game->white.score = game->white.score + 2;
			game->black.stock = game->black.stock - 2;
			game->white.secondPosition.x = point.x;
			game->white.secondPosition.y = point.y;
		}else{
			do {
				nextPoint=handleClick(click);
			} while((game->board[nextPoint.x][nextPoint.y].color==WHITE) && (nextPoint.x != point.x) && (nextPoint.y != point.y) && (game->board[nextPoint.x][nextPoint.y].state==FILL));

			game->black.score = game->black.score + 2;
			game->white.stock = game->white.stock - 2;
			game->black.secondPosition.x = point.x;
			game->black.secondPosition.y = point.y;
		}
	}
}



void stockToBoard(Game * game){

	Point click;
	Point point;

	//select the position of the new pawn
	do {
		point = handleClick(click);
	} while(game->board[point.x][point.y].state==EMPTY);

	if (game->white.playing==1) {
		game->white.stock --;
	}else{
		game->black.stock --;
	}
}
