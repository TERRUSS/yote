#include "inputs.h"
#include <stdio.h>


void waitClick(Point * point){

	int x, y;

	SDL_Event event;

	SDL_WaitEvent(&event);

	SDL_GetMouseState(&x, &y);
	Point mouse_pos;
	mouse_pos.x = x; mouse_pos.y = y;

	if(isInBoard(mouse_pos)){
		printf("ok");
	}

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
		if ( SDL_BUTTON(1) ) {
			point->x = mouse_pos.x;
			point->y = mouse_pos.y;
		}
	}
}


void mouvPawn(Game * game, Point position){

	Point point;
	Point nextPoint;
	int takePawn = 0;
	int check = 0;

	//select the next mouv
	do{
		waitClick(&point);
		if ((game->currentPlayer == 0)&&(point.x==game->white.thirdPosition.x)&&(point.y==game->white.thirdPosition.y)) {
			check = 1;
		}else if ((game->currentPlayer == 1)&&(point.x==game->black.thirdPosition.x)&&(point.y==game->black.thirdPosition.y)) {
			check = 1;
		}
	}while(((point.x!=position.x+1)||(point.x!=position.x-1)||(point.y!=position.y+1)||(point.y!=position.y-1))&&(check!=0));

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
				waitClick(&nextPoint);
			} while((game->board[nextPoint.x][nextPoint.y].color!=BLACK) && (nextPoint.x == point.x) && (nextPoint.y == point.y) && (game->board[nextPoint.x][nextPoint.y].state!=FILL));

			game->white.score = game->white.score + 2;
			game->black.stock = game->black.stock - 2;
			game->white.secondPosition.x = point.x;
			game->white.secondPosition.y = point.y;
			game->white.thirdPosition.x = position.x;
			game->white.thirdPosition.y = position.y;
		}else{
			do {
				waitClick(&nextPoint);
			} while((game->board[nextPoint.x][nextPoint.y].color!=WHITE) && (nextPoint.x == point.x) && (nextPoint.y == point.y) && (game->board[nextPoint.x][nextPoint.y].state!=FILL));

			game->black.score = game->black.score + 2;
			game->white.stock = game->white.stock - 2;
			game->black.secondPosition.x = point.x;
			game->black.secondPosition.y = point.y;
			game->black.thirdPosition.x = position.x;
			game->black.thirdPosition.y = position.y;
		}
	}
}

void stockToBoard(Game * game){

	Point point;

	//select the position of the new pawn
	do {
		waitClick(&point);

	} while(game->board[point.x][point.y].state!=EMPTY);

	if (game->currentPlayer==0) {
		game->white.stock --;
	}else{
		game->black.stock --;
	}
}

int isInBoard(Point mouse_pos){
	Point point = isoToCart(mouse_pos);
	if (point.x >=0 && point.x < CELL_R && point.y >=0 && point.y < CELL_C){
		return 1;
	}
	return 0;
}
