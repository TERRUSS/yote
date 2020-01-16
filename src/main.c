#include "main.h"

int main(void) {

	Game game;
	// int quit = 0, winner = 0;

	initGame( &game );
	initGraphics();


	updateBoard(&game);

  render();

  SDL_Delay(5000);

	/*---------------- GAME LOOP ----------------*/

	/*
	do {

		showTips();

		quit = handleEvents();

		updateBoard();

			//check victory
		winner = checkVictory(game);
		if (winner) {
			quit = 1;
		}
	} while( !quit );
	*/
	/*---------------- CONGRATULATION ----------------*/

	//VictoryScreen( winner );

	quitGraphics();

	return 0;
}
