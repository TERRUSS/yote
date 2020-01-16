#include "main.h"

int main(void) {

	Game game;
	int quit = 0;//, winner = 0;

	initGame( &game );
	initGraphics();

	updateBoard(&game);

  render();

  //SDL_Delay(5000);

	/*---------------- GAME LOOP ----------------*/

	do{
		// updateBoard(&game);

		quit = handleInputs(&game);

		// render();

	}while(!quit);
	/*
	do {

		showTips();


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
