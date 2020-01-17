
#include "game.h"

void gameLoop (Game * game) {

	Point click;
	int winner = 0;

	updateBoard(game);
	render();

	do{

		click.x = -1; click.y = -1;
		waitClick(&click);
		Point point = isoToCart(click);

		printf("joueur courant %d, Point [%d,%d]\n",game->currentPlayer,point.x,point.y);

		//dans le plateau
		if ( isInBoard(point) ) {

			if ( isMovablePawn(game, point) ){
				printf("Click sur le pion du joueur !\n");
				winner = 1;
				// movePawn(game, point);
			}

			updateBoard(game);
			render();

		}else if(isInStock(game,click)){
			placePawnFromStock(game);
			updateBoard(game);
			render();

		}else{
			printf("Click pas dans le plateau !\n");
		}


		// winner = checkWinner(game);
	} while(!winner);

}

//attend que le joueur courant place sont pion sur une case vide du plateau
void placePawnFromStock(Game * game){
	Point click;
	int place = 0;

	//si la réserve est vide ne rentre pas dans la boucle
	if ((game->currentPlayer == BLACK && game->black.stock <=0) || (game->currentPlayer == WHITE && game->white.stock<=0))
		place = 1;

	//attend que le joueur place un pion
	while(!place){
		click.x = -1; click.y = -1;
		waitClick(&click);
		Point point = isoToCart(click);

		if ( isInBoard(point) && game->board[point.x][point.y].state == EMPTY) {
			game->board[point.x][point.y].state = FILL;
			game->board[point.x][point.y].color = game->currentPlayer;
			if (game->currentPlayer == BLACK)
				game->black.stock--;
			else
				game->white.stock--;
			place = 1;
		}
		//si on reclick dans le stock quitte le placement
		else if(isInStock(game,click)){
			place = 1;
		}

	}
}
