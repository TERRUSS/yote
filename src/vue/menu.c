
#include "menu.h"

int firstMenu(Game * game) {
	int mode = 0;

	do{
		mode = selectMode();

		switch (mode) {
			case 3:
				printLeaderboard();
				break;
			default:
				printf("mode %d\n", mode);
				getPlayerName(game, mode);
				break;
		}
	} while(mode > 2 && mode != 0);

	return mode;
}


void recordText(char * input, Point inputPosition) {

	SDL_StartTextInput();

	char rep[LEN_MAX + 1] = {0};
	int len = 0;
	SDL_Event event;

	Point position;

	while(1) {
		// clear screen
		SDL_SetRenderDrawColor(renderer, 222, 49, 99, 255);
		SDL_Rect rectangle;
		rectangle.x = inputPosition.x;
		rectangle.y = inputPosition.y;
		rectangle.w = WINDOW_WIDTH;
		rectangle.h = 50;
		SDL_RenderFillRect(renderer, &rectangle);


		SDL_bool has_type = SDL_FALSE;
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT){
			quitGraphics();
		}

		else if( event.type == SDL_KEYDOWN) {

			if(event.key.keysym.sym == SDLK_BACKSPACE) {

				if (len > 0) {
					len--;
				}

				rep[len] = 0;

				has_type = SDL_TRUE;
			}

			else if(event.key.keysym.sym == SDLK_RETURN) {
				break;
			}

			if(event.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL) && SDL_HasClipboardText()) {
				char *tmp = SDL_GetClipboardText();
				size_t l = strlen(tmp);
				size_t l_copy = len + l < LEN_MAX ? l : LEN_MAX - len;
				strncpy(rep + len, tmp, l_copy);
				len += l_copy;
				SDL_free(tmp);
				has_type = SDL_TRUE;
			}

			if(event.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL))
			SDL_SetClipboardText(rep);

		} else if(event.type == SDL_TEXTINPUT) {
			size_t l = strlen(event.text.text);
			size_t l_copy = len + l < LEN_MAX ? l : LEN_MAX - len;
			strncpy(rep + len, event.text.text, l_copy);
			len += l_copy;
			has_type = SDL_TRUE;
		}
		if(has_type) {
			printf("%s : %d\n", rep, len);
			if (rep[0]){
				print(inputPosition, rep, WHITE);
			}

			render();
		}
	}

	SDL_StopTextInput();

	for (int i = 0; i<len; i++) {
		input[i] = rep[i];
	}
}
// /*
int selectMode (){

	Point click;
	Point JvJ,JvIA,score;
	int check = 0;

	SDL_RenderClear(renderer);
	backgroundColor(222, 49, 99);
	SDL_SetRenderDrawColor(renderer, 222, 49, 99, 255);
	SDL_Rect rectangle;
	rectangle.w = 200;
	rectangle.h = 50;


	JvJ.x = 20;
	JvJ.y = 50;
	rectangle.x = JvJ.x;
	rectangle.y = JvJ.y;
	SDL_RenderFillRect(renderer, &rectangle);

	JvIA.x = 20;
	JvIA.y = 150;
	rectangle.x = JvIA.x;
	rectangle.y = JvIA.y;
	SDL_RenderFillRect(renderer, &rectangle);

	score.x = 20;
	score.y = 250;
	rectangle.x = score.x;
	rectangle.y = score.y;
	SDL_RenderFillRect(renderer, &rectangle);

	print(JvJ, "Joueur VS Joueur", WHITE);
	print(JvIA, "Joueur VS IA", WHITE);
	print(score, "Score", WHITE);
	render();

	do {
		waitClick(&click);

		if (((click.x <= 20 + rectangle.w )&&(click.x >= 20 ))&&((click.y <= 50 + rectangle.h )&&(click.y >= 50 ))) {
			check = 1;
		}else if (((click.x <= 20 + rectangle.w )&&(click.x >= 20 ))&&((click.y <= 150 + rectangle.h )&&(click.y >= 150 ))) {
			check = 2;
		}else if (((click.x <= 20 + rectangle.w )&&(click.x >= 20 ))&&((click.y <= 250 + rectangle.h )&&(click.y >= 250 ))) {
			check = 3;
		}
	} while(check == 0);

	return check;
}
// */

void getPlayerName (Game * game, int mode){

	Point click;
	Point j1, j2;

	int select;

	SDL_RenderClear(renderer);
	backgroundColor(222, 49, 99);

	j1.x = 20; j1.y = 50;
	j2.x = 20; j2.y = 100;

	print(j1, "Joueur Blanc : ", WHITE);

	if (mode == 1) {
		print(j2, "Joueur Noir : ", WHITE);
	}

	render();

	j1.x = 300;
	j2.x = 300;

	recordText( game->white.name, j1);
	if (mode == 1) {
		recordText( game->black.name, j2);
	}else{
		strcpy(game->black.name,"IA");
	}
	printf("White player name : %s\n", game->white.name);
	if (mode == 1) {
		printf("Black player name : %s\n", game->black.name);
	}
}
