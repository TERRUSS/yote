
#include "game.h"

void gameLoop (Game * game) {

	Point click;
	int winner = 0;

	displayPlayerName(game);
	updateBoard(game);
	render();

	do{

		click.x = -1; click.y = -1;
		waitClick(&click);

		if (click.x != -1 && click.y != -1){
			Point point = isoToCart(click);

			//dans le plateau
			if ( isInBoard(point) ) {

				if ( isMovablePawn(game, point) ){
					moveLoop(game, point);
				}

				updateBoard(game);
				render();

			}else if(isInStock(game,click)){
				placePawnFromStock(game);
				updateBoard(game);
				render();
			}
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
	else
		printf("Cliquer sur une case vide pour placer un pion - pour annuler cliquer de nouveau sur la reserve\n");

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

			//change de joueur;
			nextPlayer(game);
			displayPlayerName(game);
		}
		//si on reclick dans le stock quitte le placement
		else if(isInStock(game,click)){
			place = 1;
		}

	}
}

void moveLoop(Game * game,Point src){
	Point click;
	int played = 0;

	setBoardAccessibility(game,src);

	//attend que le joueur deplace sont pion
	while(!played){
		click.x = -1; click.y = -1;
		waitClick(&click);
		Point p = isoToCart(click);

		if ( isInBoard(p) ) {
			//si on fais un bon deplacement
			if (game->board[p.x][p.y].state == ACCESSIBLE){
				resetBoardAccessibility(game);
				movePawn(game,src,p);
				nextPlayer(game);
				displayPlayerName(game);
				played = 1;
			}
			//Si on click sur un autre de nos pions
			else if ( isMovablePawn(game, p) ){
				resetBoardAccessibility(game);
				src.x = p.x;src.y = p.y;
				setBoardAccessibility(game,p);
			}
			else{
				printf("Deplacement impossible\n");
			}
		}
		//si on click sur le stock on lance la fonction stock et on quite le move loop
		else if(isInStock(game,click)){
			resetBoardAccessibility(game);
			played=1;
			placePawnFromStock(game);
		}
	}
}
