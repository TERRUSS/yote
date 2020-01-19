#include "main.h"

int main(void) {

	Game game;

	initGame( &game );
	initGraphics();


	// welcome menu - players setup
	int mode =firstMenu(&game);

	game.currentPlayer = pickPlayer();

	/*---------------- GAME LOOP ----------------*/

		Player * winner = gameLoop(&game,mode);
		printf("The winner is : %s score : %d\n",winner->name,winner->score);

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
