
#include "graphics.h"
#include <stdio.h>

/*---------------- UTILS ----------------*/

void initGraphics(){
	printLog(LOGGING_TASK, "Starting Initialisation");
	window = 0;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		printLog(LOGGING_STEP, "Window Creation ERROR : ");
		quitGraphics();
	} else {
		printLog(LOGGING_STEP, "Window Created");
	}


	window = SDL_CreateWindow("Yoté", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if ( renderer ) {
		printLog(LOGGING_STEP, "Renderer Created");
	} else {
		printLog(LOGGING_STEP, "Renderer Creation ERROR : ");
		printLog(STEP_ERROR, SDL_GetError());
		quitGraphics();
	}

	cell_sprite_blue = IMG_Load("./src/assets/board_blue.png");
	cell_sprite_red = IMG_Load("./src/assets/board_red.png");
	white_pawn_sprite = IMG_Load("./src/assets/pawn_white.png");
	black_pawn_sprite = IMG_Load("./src/assets/pawn_black.png");

	if ( cell_sprite_blue && cell_sprite_red && white_pawn_sprite && black_pawn_sprite ) {
		printLog(LOGGING_STEP, "Assets Loaded");
		SDL_Delay(50);
	} else {
		printLog(LOGGING_STEP, "Loading assets ERROR : ");
		printLog(STEP_ERROR, SDL_GetError());
		quitGraphics();
	}

	printLog(FINISHED_TASK, "Initialisation Completed");
}

void quitGraphics(){

	// Libération des ressources occupées par les sprites, le render et la fenêtre

	SDL_FreeSurface(cell_sprite_blue);
	SDL_FreeSurface(cell_sprite_red);
	SDL_FreeSurface(white_pawn_sprite);
	SDL_FreeSurface(black_pawn_sprite);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	SDL_Quit();
}

void render(){
	SDL_RenderPresent(renderer); // Affichage
}

/*--------- PRINTING FUNCTIONS ----------*/

void displayBoard(Game * game){

	// printLog(LOGGING_TASK, "Displaying Board");

	Point pt;
	for (int r = 0; r < CELL_R; r++) {
		for (int c = CELL_C-1; c >= 0; c--) {
			pt.x=c;
			pt.y=r;
			pt = cartToIso(pt);

			print_board_cell( ((r+c)%2) ? WHITE : BLACK, pt);

			if (game->board[r][c].state == FILL) {
				if (game->board[r][c].color == WHITE) {
					print_pawn(WHITE, pt);
				}
			}
		}
	}

	// printLog(FINISHED_TASK, "Ok");
}

void print_board_cell(int color, Point pt){
	SDL_Texture* pTexture;

	if (color == WHITE) { // Préparation du sprite de la case
		pTexture = SDL_CreateTextureFromSurface(renderer, cell_sprite_blue);
	} else {
		pTexture = SDL_CreateTextureFromSurface(renderer, cell_sprite_red);
	}

	if ( pTexture ) {
		SDL_Rect dest = { pt.x, pt.y, SPRITE_WIDTH, SPRITE_WIDTH};

		SDL_RenderCopy(renderer, pTexture, NULL, &dest); // Copie du pawn_sprite grâce au SDL_Renderer

		SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture

	} else {
		printLog(STEP_ERROR, SDL_GetError());
	}
}

void print_pawn(int color, Point pt){
		SDL_Texture* pTexture = 0;

	 if (color == WHITE) pTexture = SDL_CreateTextureFromSurface(renderer, white_pawn_sprite); // Préparation du pawn_sprite
	 else pTexture = SDL_CreateTextureFromSurface(renderer, black_pawn_sprite); // Préparation du pawn_sprite

	if ( pTexture ) {
		SDL_Rect dest = { pt.x+SPRITE_WIDTH/4, pt.y+SPRITE_WIDTH/10, SPRITE_WIDTH/2, SPRITE_WIDTH/2};

		SDL_RenderCopy(renderer, pTexture, NULL, &dest); // Copie du pawn_sprite grâce au SDL_Renderer

		SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture

	} else {
		printLog(STEP_ERROR, SDL_GetError());
	}
}

void updateBoard(Game * game) {
	// SDL_RenderClear(renderer);
	backgroundColor(222, 49, 99);
	displayBoard(game);
}

void backgroundColor(int r, int g, int b){
	SDL_SetRenderDrawColor(renderer, r, b, b, 255);
	SDL_Rect rectangle;

	rectangle.x = 0;
	rectangle.y = 0;
	rectangle.w = WINDOW_WIDTH;
	rectangle.h = WINDOW_HEIGHT;
	SDL_RenderFillRect(renderer, &rectangle);
}
