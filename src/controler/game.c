
#include "game.h"

void gameLoop (Game * game) {

	Point point;
	int winner = 0;

	do{
		waitClick(&point);

		if ( isInBoard(point) ) {

			if ( isMovablePawn(game, point) ){
				// movePawn(game, point);
			}

		}
		else{}

		// winner = checkWinner(game);
	} while(!winner);

}
