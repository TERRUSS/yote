
#include "game.h"

void initGame(Game * game){

    Cell newcell;
    newcell.state = EMPTY;
    newcell.color = VIDE;

    // init board
    int r, c;
    for (r = 0; r < CELL_R; r++) {
        for (c = 0; c < CELL_C; c++) {
            game->board[r][c] = newcell;
        }
    }

    // init player
    Player newplayer;
    newplayer.stock = 12;
    newplayer.score = 0;
    // newplayer.name = "";
    newplayer.color = BLACK;

    game->black = newplayer;

    newplayer.color = WHITE;
    game->white = newplayer;

    game->round = 0;

}

int checkVictory(Game * game){

    if((12 - game->black.stock == 10 )&&(12 - game->white.stock == 10)){
        game->draw++;
    }

    if ((game->white.score >= 12-game->black.stock)&&(game->black.stock != 12)) {
        game->white.victory=1;
    } else if ((game->black.score >= 12-game->white.stock)&&(game->white.stock != 12)) {
        game->black.victory=1;
    }else if((12 - game->black.stock == 10 )&&(12 - game->white.stock == 10)&&(game->draw==10)){
        game->victory=1;
    }

    return 0;
}

int pickPlayer (){
    srand(time(NULL));
    return rand()%2;
}

void roundPlayer (Game * game){

    Point click;
	Point point;

    do {
        waitClick(&click);
    } while(((game->board[point.x][point.y].color!=WHITE)&&(game->currentPlayer == 0)) || ((game->board[point.x][point.y].color!=BLACK)&&(game->currentPlayer == 0)));


    if ((point.x!=game->white.secondPosition.x)&&(point.y!=game->white.secondPosition.y)&&(game->currentPlayer == 0)) {
            game->white.firstPosition.x = point.x;
			game->white.firstPosition.y = point.y;
    }else if ((point.x!=game->black.secondPosition.x)&&(point.y!=game->black.secondPosition.y)&&(game->currentPlayer == 1)) {
            game->black.firstPosition.x = point.x;
			game->black.firstPosition.y = point.y;
    }else{
        game->black.firstPosition.x = point.x;
        game->black.firstPosition.y = point.y;
        game->black.secondPosition.x = -1;
        game->black.secondPosition.y = -1;
        game->black.thirdPosition.x = -1;
        game->black.thirdPosition.y = -1;
    }
    mouvPawn(game, point);

}



int isMovablePawn(Game * game, Point point) {
  if (game->board[point.x][point.y].state == FILL && game->board[point.x][point.y].color == game->currentPlayer)
    return 1;
  else
    return 0;
}

int isInStock(Game * game,Point click){
  if (game->currentPlayer == BLACK){
    if (click.x >=0 && click.x < SPRITE_WIDTH){
      return 1;
    }
    return 0;
  }else{
    if (click.x >=WINDOW_WIDTH-SPRITE_WIDTH && click.x < WINDOW_WIDTH){
      return 1;
    }
    return 0;
  }
}


void resetBoardAccessibility(Game * game){

  for (int r = 0; r < CELL_R; r++) {
		for (int c = CELL_C-1; c >= 0; c--) {
      if (game->board[r][c].state == ACCESSIBLE)
        game->board[r][c].state = EMPTY;
      else if (game->board[r][c].state == SELECTED)
        game->board[r][c].state = FILL;
    }
  }
}

/*
void setBoardAccessibility(){

}*/
