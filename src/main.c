#include "main.h"

int main(void) {

	Game game;

	initGame( &game );
	initGraphics();


	// welcome menu - players setup
	//getPlayersInfos(&game);

	game.currentPlayer = pickPlayer();

	/*---------------- GAME LOOP ----------------*/

		gameLoop(&game);

	/*
	do {

		showTips();

		round(&game);

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
