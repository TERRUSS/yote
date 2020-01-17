#include "main.h"

int main(void) {

	// Point click;
	// Point point;
	Game game;
	int quit = 0;//, winner = 0;

	initGame( &game );
	initGraphics();

	updateBoard(&game);

  	render();

  //SDL_Delay(5000);

	game.white.playing = pickPlayer();
	game.black.playing = !pickPlayer();

	/*---------------- GAME LOOP ----------------*/

	

	do{
		updateBoard(&game);

		quit = handleInputs(&game);

		render();

	}while(!quit);
	/*
	do {

		showTips();

		do {
			point = handleClick(click);
		} while(((game->board[point.x][point.y].color==WHITE)&&(game.white.playing == 1)) || ((game->board[point.x][point.y].color==BLACK)&&(game.black.playing == 1)));

		if (game->board[point.x][point.y].state==STOCK) {
			stockToBoard(game);
		}else{
			mouvPawn(game, point);
		}

		updateBoard();

		//check victory
		checkVictory(game);

		if (game->black.victory || game->white.victory || game->victory) {
			quit = 1;
		}
	} while( !quit );
	*/
	/*---------------- CONGRATULATION ----------------*/

	//VictoryScreen( winner );

	quitGraphics();

	return 0;
}
