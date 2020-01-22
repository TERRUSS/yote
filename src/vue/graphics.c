
#include "graphics.h"
#include <stdio.h>
#include <unistd.h>

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
	menubg = IMG_Load("./src/assets/menubg.png");

	btn_jvj = IMG_Load("./src/assets/buttons/jvj.png");
	btn_jvia = IMG_Load("./src/assets/buttons/jvia.png");
	btn_score = IMG_Load("./src/assets/buttons/score.png");
	btn_back = IMG_Load("./src/assets/buttons/back.png");

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
	char cwd[250],cwd_font[500];
  getcwd(cwd, sizeof(cwd));
	sprintf(cwd_font,"%s/src/assets/fonts/font.ttf",cwd);
	if (!(font = TTF_OpenFont(cwd_font, 24))){
		printLog(STEP_ERROR, TTF_GetError());
		quitGraphics();
	}

	printLog(FINISHED_TASK, "Initialisation Completed");
}

void quitGraphics(){
	SDL_DestroyWindow(window);
	SDL_Quit();
	exit(0);
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
	textColor.a = 255;

	int text_width, text_height;

	textSurface = TTF_RenderText_Solid(font, string, textColor);

	SDL_Texture * text = (SDL_Texture*)SDL_CreateTextureFromSurface(renderer, textSurface);

	text_width = textSurface->w;
	text_height = textSurface->h;

	SDL_FreeSurface(textSurface);
	SDL_Rect renderQuad = { pt.x, pt.y, text_width, text_height };
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

			if (game->board[r][c].state == ACCESSIBLE){
				SDL_Rect rectangle = {pt.x+HIT_BOX_HEIGHT/2.3,pt.y+HIT_BOX_HEIGHT/3.8,HIT_BOX_HEIGHT/2,HIT_BOX_WIDTH/2};

				SDL_SetRenderDrawColor(renderer,200,0,0,150);
				SDL_RenderDrawRect(renderer,&rectangle);
			}

			if (game->board[r][c].state == FILL || game->board[r][c].state == SELECTED ) {
				if (game->board[r][c].color == WHITE) {
					if (game->currentPlayer == WHITE)
						print_pawn(WHITE, pt,PAWN_SELECT_OPACITY);
					else
						print_pawn(WHITE, pt,PAWN_UNSELECT_OPACITY);

				}
				else if (game->board[r][c].color == BLACK) {
					if (game->currentPlayer == BLACK)
						print_pawn(BLACK, pt,PAWN_SELECT_OPACITY);
					else
						print_pawn(BLACK, pt,PAWN_UNSELECT_OPACITY);
				}
			}
		}
	}

	// printLog(FINISHED_TASK, "Ok");
}

void print_hover_cell(Point coord){
	coord = cartToIso(isoToCart(coord));
	SDL_Rect rectangle = {coord.x+HIT_BOX_HEIGHT/2.3,coord.y+HIT_BOX_HEIGHT/3.8,HIT_BOX_HEIGHT/2,HIT_BOX_WIDTH/2};

	SDL_SetRenderDrawColor(renderer,0,0,255,150);
	SDL_RenderDrawRect(renderer,&rectangle);

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

void print_pawn(int color, Point pt,Uint8 alpha){
		SDL_Texture* pTexture = 0;

	 if (color == WHITE){ SDL_SetSurfaceAlphaMod(white_pawn_sprite,alpha);pTexture = SDL_CreateTextureFromSurface(renderer,white_pawn_sprite);} // Préparation du pawn_sprite
	 else{SDL_SetSurfaceAlphaMod(black_pawn_sprite,alpha); pTexture = SDL_CreateTextureFromSurface(renderer, black_pawn_sprite);} // Préparation du pawn_sprite

	if ( pTexture ) {
		SDL_Rect dest = { pt.x+SPRITE_WIDTH/4, pt.y+SPRITE_WIDTH/10, SPRITE_WIDTH/2, SPRITE_WIDTH/2};
		SDL_RenderCopy(renderer, pTexture, NULL, &dest); // Copie du pawn_sprite grâce au SDL_Renderer
		SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture

	} else {
		printLog(STEP_ERROR, SDL_GetError());
	}
}
void print_score(Player * player) {
	Point pt;
	char text[50+MAX_NAME_LENGTH];

	pt.x = 15;
	pt.y= 50;

	sprintf(text,"Score : %d",player->score);
	print(pt,text,WHITE);
}

void print_select_stock(int color,int number){
	Point pt;

	if (color == BLACK){
		pt.x = 0;
	}else{
		pt.x = WINDOW_WIDTH-SPRITE_WIDTH;
	}
	pt.y=WINDOW_HEIGHT-30-50;

	SDL_Rect rectangle = {pt.x,pt.y-(10*number),(SPRITE_WIDTH),(10*number)+50};

	SDL_SetRenderDrawColor(renderer,200,0,0,150);
	SDL_RenderDrawRect(renderer,&rectangle);
}

void print_stock(int color, int number,Uint8 alpha){
	Point pt;
	char text[25];

	if (color == BLACK){
		pt.x = 0;
	}else{
		pt.x = WINDOW_WIDTH-SPRITE_WIDTH;
	}
	pt.y=WINDOW_HEIGHT-30-50;

	if(number < 10)
		sprintf(text,"    %d",number);
	else
		sprintf(text,"   %d",number);

	pt.y+=50;
	print(pt,text,WHITE);
	pt.y-=50;
	for(int i = 0;i<number;i++){
		print_pawn(color,pt,alpha);
		pt.y-=10;
	}

}

void updateBoard(Game * game) {
	// SDL_RenderClear(renderer);
	backgroundColor(222, 49, 99);
	displayBoard(game);


	if (game->currentPlayer == BLACK){
		print_stock(BLACK, game->black.stock,PAWN_SELECT_OPACITY);
		print_stock(WHITE, game->white.stock,PAWN_UNSELECT_OPACITY);
		print_score(&(game->black));
	}else{
		print_stock(WHITE, game->white.stock,PAWN_SELECT_OPACITY);
		print_stock(BLACK, game->black.stock,PAWN_UNSELECT_OPACITY);
		print_score(&(game->white));
	}

	displayPlayerName(game);
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

void backgroundImage(int image){
	SDL_Texture* pTexture = 0;

	pTexture = SDL_CreateTextureFromSurface(renderer, menubg); // Préparation du pawn_sprite

	if ( pTexture ) {
		SDL_Rect dest = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
		SDL_RenderCopy(renderer, pTexture, NULL, &dest); // Copie du pawn_sprite grâce au SDL_Renderer
		SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture

	} else {
		printLog(STEP_ERROR, SDL_GetError());
		printLog(STEP_ERROR, "Go background color instead");
		SDL_RenderClear(renderer);
		backgroundColor(222, 49, 99);
	}
}


void displayPlayerName(Game * game){
	Point pt = {15,15};
	char text[MAX_NAME_LENGTH+10];
	if (game->currentPlayer == BLACK){
		sprintf(text,"Joueur : %s",game->black.name);
	}else{
		sprintf(text,"Joueur : %s",game->white.name);
	}
	print(pt,text,WHITE);
}


void print_button(Point pt, int type){
		SDL_Texture* pTexture = 0;

	 switch (type) {
		case JVJ:
			pTexture = SDL_CreateTextureFromSurface(renderer, btn_jvj);
			break;
		case JVIA:
			pTexture = SDL_CreateTextureFromSurface(renderer, btn_jvia);
			break;
		case SCORE:
			pTexture = SDL_CreateTextureFromSurface(renderer, btn_score);
			break;
		case BACK:
			pTexture = SDL_CreateTextureFromSurface(renderer, btn_back);
			break;
	 }

	if ( pTexture ) {
		SDL_Rect dest = { pt.x, pt.y, BTN_WIDTH, BTN_HEIGHT};

		if (type == BACK){
			dest.w = BTN_WIDTH/2;
			dest.h = BTN_HEIGHT/2;
		}

		SDL_RenderCopy(renderer, pTexture, NULL, &dest); // Copie du pawn_sprite grâce au SDL_Renderer
		SDL_DestroyTexture(pTexture); // Libération de la mémoire associée à la texture
	}
}

/*******************************************/

void VictoryScreen (Player * winner) {
	Point pt = {WINDOW_WIDTH/3, WINDOW_HEIGHT/3};
	char text[1000] = {0};

	SDL_RenderClear(renderer);
	backgroundColor(222, 49, 99);

	sprintf(text,"VICTOIRE ROYALE");
	print(pt,text,WHITE);
	pt.y += 50;
	sprintf(text,"%s vainqueur",winner->name);
	print(pt,text,WHITE);

	render();

	pt.x = -1;
	pt.y = -1;

	do{
		waitClick(&pt);
	} while(pt.x < 0 && pt.y < 0);
}


void printLeaderboard(){

	Point pt = {WINDOW_WIDTH/3, 50};

	SDL_RenderClear(renderer);
	backgroundColor(222, 49, 99);

	char score[MAXCHAR] = {0};


	print(pt, "Leaderboard", WHITE);

	int i = 0;
	pt.x = 50;
	pt.y = 100;
	while(readScore(i, score) && i<10){
		pt.y += 50;
		print(pt, score, WHITE);
		i++;
	}

	pt.x = 10; pt.y = 10;
	print_button(pt, BACK);

	render();

	pt.x = -1;
	pt.y = -1;

	do{
		waitClick(&pt);
	} while(pt.x < 0 && pt.y < 0);

}
