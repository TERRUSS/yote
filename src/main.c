#include "main.h"

int main(void) {

	int mode = 0;
	Game game;

	initGraphics();

	do {
		initGame( &game );
		initMusic();
		// welcome menu - players setup
		int mode = firstMenu(&game);

		game.currentPlayer = pickPlayer();

		/*---------------- GAME LOOP ----------------*/

			Player * winner = gameLoop(&game,mode);
			printf("The winner is : %s score : %d\n",winner->name,winner->score);

		/*---------------- CONGRATULATION ----------------*/

		VictoryScreen( winner );
		saveScore(winner);
	} while (!mode);

	quitGraphics();

	return 0;
}
