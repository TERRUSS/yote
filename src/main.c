#include "main.h"

int main(void) {

	Game game;

	initGame( &game );
	initGraphics();


	// welcome menu - players setup
	firstMenu(&game);

	game.currentPlayer = pickPlayer();

	/*---------------- GAME LOOP ----------------*/

		Player * winner = gameLoop(&game);

	/*---------------- CONGRATULATION ----------------*/

	printf("The winner is : %s score : %d\n", winner->name,winner->score);
	saveScore(winner);
	//VictoryScreen( winner );

	quitGraphics();

	return 0;
}
