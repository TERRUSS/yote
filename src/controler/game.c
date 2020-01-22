
#include "game.h"

Player * gameLoop (Game * game, int mode) {
	int version = 1;//version 0 = version simple plus de pions - version = 1 plus de pions sur le plateau
	Point click;
	int inGame = 1;
	Player * winner;


	updateBoard(game);
	render();


	do{
		if (!checkVictory(version,game)){

			if(mode == 2 && game->currentPlayer == BLACK ){
				play_ia(game);

				updateBoard(game);
				render();
			}else{
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
			}
		}else{
			inGame = 0;
			winner = getWinner(game);
		}
	} while(inGame);

	return winner;
}

//attend que le joueur courant place sont pion sur une case vide du plateau
void placePawnFromStock(Game * game){
	Point click;
	int place = 0;

	//si la réserve est vide ne rentre pas dans la boucle
	if ((game->currentPlayer == BLACK && game->black.stock <=0) || (game->currentPlayer == WHITE && game->white.stock<=0))
		place = 1;
	else{
		if (game->currentPlayer == BLACK)
			print_select_stock(game->currentPlayer,game->black.stock);
		else
			print_select_stock(game->currentPlayer,game->white.stock);
		render();
		printf("Cliquer sur une case vide pour placer un pion - pour annuler cliquer de nouveau sur la reserve\n");
	}

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
			game->round++;
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
	updateBoard(game);
	render();

	//attend que le joueur deplace sont pion
	while(!played){
		click.x = -1; click.y = -1;
		waitClick(&click);
		Point p = isoToCart(click);

		if ( isInBoard(p) ) {
			//si on fais un bon deplacement
			if (game->board[p.x][p.y].state == ACCESSIBLE){
				resetBoardAccessibility(game);
				if (movePawn(game,src,p)){//on deplace le pion si un pion est manger
					updateBoard(game);
					render();
					takePawn(game);
				}
				nextPlayer(game);
				game->round++;
				displayPlayerName(game);
				played = 1;
			}
			//Si on click sur un autre de nos pions
			else if ( isMovablePawn(game, p) ){
				resetBoardAccessibility(game);
				src.x = p.x;src.y = p.y;
				setBoardAccessibility(game,p);
				updateBoard(game);
				render();
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

//attend que le joueur courant prenne un pion adverse
void takePawn(Game * game){
	Point click;
	int took = 0;
	Player* adverse;
	if (game->currentPlayer == BLACK)
		adverse = &(game->white);
	else
		adverse = &(game->black);

	printf("Vous pouvez manger un autre pion adverse !\n");
	//Si l'adversaire n'a plus de pion sur sont plateau
	if (nbPawnOnBoardPlayer(game,adverse->color) == 0){
		if(adverse->stock > 1){
			adverse->stock--;
			printf("Pas de pions adverse sur le plateau ! Un pion de ca réserve a donc été supprimé\n");
		}else if(adverse->stock == 1){
			adverse->stock--;
			printf("Le dernier pion de l'adversaire a été manger ! il a perdu !\n");
		}else{
			printf("l'adversaire n'a plus de pions il a donc perdu !\n");
		}
		took = 1;
	}
	//attend que le joueur deplace sont pion
	while(!took){
		click.x = -1; click.y = -1;
		waitClick(&click);
		Point p = isoToCart(click);

		if ( isInBoard(p) ) {
			//si on fais un bon click
			if (game->board[p.x][p.y].state == FILL && game->board[p.x][p.y].color != game->currentPlayer){
				game->board[p.x][p.y].state = EMPTY;
				took = 1;
			}
			else{
				printf("Vous ne pouvez pas manger ce pion\n");
			}
		}
	}
}
