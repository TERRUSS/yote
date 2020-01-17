
#include "menu.h"

void getPlayersInfos(Game * game) {

	SDL_StartTextInput();
	recordText();
	SDL_StopTextInput();

}



void recordText() {
	char rep[LEN_MAX + 1] = {0};
	size_t len = 0;
	SDL_Event event;

	Point position;

	SDL_RenderClear(renderer);
	backgroundColor(222, 49, 99);
	render();

	while(1) {

		SDL_RenderClear(renderer);
		backgroundColor(222, 49, 99);


		SDL_bool has_type = SDL_FALSE;
		SDL_WaitEvent(&event);
		if(event.type == SDL_QUIT){
			quitGraphics();
		}

		else if( event.type == SDL_KEYDOWN) {

			if(event.key.keysym.sym == SDLK_BACKSPACE && len) {
				rep[len - 1] = 0;
				len--;
				has_type = SDL_TRUE;
			}

			else if(event.key.keysym.sym == SDLK_RETURN) {
				SDL_FreeSurface(textSurface);
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

			position.x = 20;
			position.y = 50;
			print(position, rep, WHITE);

			render();
		}
	}
}
