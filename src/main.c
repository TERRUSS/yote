#include "main.h"

int main(void) {

	Game game;
	int quit = 0;//, winner = 0;

	initGame( &game );
	initGraphics();


	// welcome menu - players setup
	getPlayersInfos(game);


	game.white.playing = pickPlayer();
	game.black.playing = !pickPlayer();

	/*---------------- GAME LOOP ----------------*/



	do{

		updateBoard(&game);
		render();

		quit = handleInputs(&game);

		render();

	}while(!quit);
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
