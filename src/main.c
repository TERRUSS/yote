#include "main.h"

int main(void) {

	Game game;

	initGame( &game );
	initGraphics();


	// welcome menu - players setup
	int mode = firstMenu(&game);

	game.currentPlayer = pickPlayer();

	/*---------------- GAME LOOP ----------------*/

		Player * winner = gameLoop(&game,mode);
		printf("The winner is : %s score : %d\n",winner->name,winner->score);

	/*---------------- CONGRATULATION ----------------*/

	VictoryScreen( winner );
	saveScore(winner);

	quitGraphics();

	return 0;
}
