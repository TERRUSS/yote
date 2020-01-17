
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
				movePawn2(game, point);
				//winner = 1;
			}

			updateBoard(game);
			render();

		}else if(isInStock(game,click)){
			placePawnFromStock(game);
			updateBoard(game);
			render();

		}else{
			//printf("Click pas dans le plateau !\n");
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

			//change de joueur;
			game->currentPlayer = (game->currentPlayer+1)%2;
		}
		//si on reclick dans le stock quitte le placement
		else if(isInStock(game,click)){
			place = 1;
		}

	}
}

void movePawn2(Game * game,Point point){
	Point click;
	int played = 0;
	int tuple[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
	int state,color;

	//Définie les cases accessible et selectionné
	game->board[point.x][point.y].state = SELECTED;
	for (int i=0;i<4;i++){

		state = game->board[point.x+tuple[i][0]][point.y+tuple[i][1]].state;
		color = game->board[point.x+tuple[i][0]][point.y+tuple[i][1]].color;

		//Si la case autour est vide elle est accessible
		if (state == EMPTY){
			game->board[point.x+tuple[i][0]][point.y+tuple[i][1]].state = ACCESSIBLE;
		}else if(state == FILL && color != game->currentPlayer){
			//Si la case est rempli par un pion d'un autre joueur
			//il peut la manger si la case derrière est VIDE
			if(game->board[point.x+tuple[i][0]*2][point.y+tuple[i][1]*2].state == EMPTY){
				game->board[point.x+tuple[i][0]*2][point.y+tuple[i][1]*2].state = ACCESSIBLE;
			}
		}
	}


	//attend que le joueur deplace sont pion
	while(!played){
		click.x = -1; click.y = -1;
		waitClick(&click);
		Point p = isoToCart(click);

		if ( isInBoard(p) ) {
			printf("J'attend que tu jou pd\n");
			//played = 1;
			if (game->board[p.x][p.y].state == ACCESSIBLE){
				printf("bien jouer\n");
				//played = 1;
			}
			//Si on click sur un autre de nos pions
			if ( isMovablePawn(game, p) ){
				resetBoardAccessibility(game);
				game->board[p.x][p.y].state = SELECTED;
			}
		}




	}
}
