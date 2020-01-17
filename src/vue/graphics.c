
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

	printLog(LOGGING_STEP, "Loading fonts");
	TTF_Init();
	font = TTF_OpenFont("/home/tmo/Code/yote/src/assets/fonts/font.ttf", 24);

	printLog(FINISHED_TASK, "Initialisation Completed");
}

void quitGraphics(){

	// Libération des ressources occupées par les sprites, le render et la fenêtre

	SDL_FreeSurface(cell_sprite_blue);
	SDL_FreeSurface(cell_sprite_red);
	SDL_FreeSurface(white_pawn_sprite);
	SDL_FreeSurface(black_pawn_sprite);
	SDL_DestroyRenderer(renderer);

	TTF_Quit();
	SDL_FreeSurface(textSurface);

	SDL_DestroyWindow(window);
	SDL_Quit();
}

void render(){
	SDL_RenderPresent(renderer); // Affichage
}


void print (Point pt, char* string, int color) {
	switch (color) {
		case WHITE:
			textColor.r = 255;
			textColor.g = 255;
			textColor.b = 255;
			break;
		case BLACK:
			textColor.r = 0;
			textColor.g = 0;
			textColor.b = 0;
			break;
	}
	textColor.a = 0;


	int text_width, text_height;

	textSurface = TTF_RenderText_Solid(font, string, textColor);
	SDL_Texture * text = (SDL_Texture*)SDL_CreateTextureFromSurface(renderer, textSurface);
	text_width = textSurface->w;
	text_height = textSurface->h;

	SDL_FreeSurface(textSurface);
	SDL_Rect renderQuad = { 20, 50, text_width, text_height };
	SDL_RenderCopy(renderer, text, NULL, &renderQuad);

	SDL_DestroyTexture(text);
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
				else if (game->board[r][c].color == BLACK) {
					print_pawn(BLACK, pt);
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

void print_stock(int color, int number){
	Point pt;
	if (color == BLACK){
		pt.x = 0;
	}else{
		pt.x = WINDOW_WIDTH-SPRITE_WIDTH;;
	}

	pt.y=WINDOW_HEIGHT-SPRITE_WIDTH;

	for(int i = 0;i<number;i++){
		print_pawn(color,pt);
		pt.y-=10;
	}

}

void updateBoard(Game * game) {
	// SDL_RenderClear(renderer);
	backgroundColor(222, 49, 99);
	displayBoard(game);

	print_stock(BLACK, game->black.stock);
	print_stock(WHITE, game->white.stock);
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
