
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
    strcpy(newplayer.name,"Noir");
    newplayer.color = BLACK;

    game->black = newplayer;

    newplayer.color = WHITE;
    strcpy(newplayer.name,"Blanc");
    game->white = newplayer;

    game->round = 0;

}
int checkVictory(int version,Game * game){
  if (game->round > 2 && version == 0){
    if ((nbPawnOnBoardPlayer(game,BLACK) == 0 && game->black.stock == 0) || (nbPawnOnBoardPlayer(game,WHITE) == 0 && game->white.stock == 0)){
      return 1;
    }else{
      return 0;
    }
  }else if (game->round > 2 && version == 1){
    if (nbPawnOnBoardPlayer(game,BLACK) == 0 || nbPawnOnBoardPlayer(game,WHITE) == 0){
      return 1;
    }else{
      return 0;
    }
  }
  return 0;

}

int pickPlayer (){
    srand(time(NULL));
    return rand()%2;
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


void setBoardAccessibility(Game * game,Point point){
  int tuple[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
	int state,color;
  Point p;

  //Définie les cases accessible et selectionné
	game->board[point.x][point.y].state = SELECTED;
	for (int i=0;i<4;i++){
    p.x = point.x+tuple[i][0];
    p.y = point.y+tuple[i][1];

    if(isInBoard(p)){
  		state = game->board[p.x][p.y].state;
  		color = game->board[p.x][p.y].color;

  		//Si la case autour est vide elle est accessible
  		if (state == EMPTY){
  			game->board[p.x][p.y].state = ACCESSIBLE;
  		}else if(state == FILL && color != game->currentPlayer){
  			//Si la case est rempli par un pion d'un autre joueur
  			//il peut la manger si la case derrière est VIDE
  			if(game->board[p.x+tuple[i][0]][p.y+tuple[i][1]].state == EMPTY){
  				game->board[p.x+tuple[i][0]][p.y+tuple[i][1]].state = ACCESSIBLE;
  			}
  		}
    }
	}
}

int movePawn(Game * game, Point src ,Point dst){
  //renvoie un si un pion a été manger
  game->board[src.x][src.y].state = EMPTY;
  game->board[dst.x][dst.y].state = FILL;
  game->board[dst.x][dst.y].color = game->currentPlayer;

  int diff_x = src.x-dst.x;
  int diff_y = src.y-dst.y;
  Point eat;
  if (diff_x == -2 || diff_x == 2){
    if (diff_x == 2)
      eat.x = dst.x+1;
    else
      eat.x= dst.x-1;
    eat.y = dst.y;
    game->board[eat.x][eat.y].state = EMPTY;
    printf("pion manger sur l'axe x src:%d;%d,dst:%d;%d,milieu:%d;%d\n",src.x,src.y,dst.x,dst.y,eat.x,eat.y);
    return 1;
  }
  else if(diff_y == -2 || diff_y == 2){
    if (diff_y == 2)
      eat.y= dst.y+1;
    else
      eat.y= dst.y-1;
    eat.x = dst.x;
    game->board[eat.x][eat.y].state = EMPTY;
    printf("pion manger sur l'axe y src:%d;%d,dst:%d;%d,milieu:%d;%d\n",src.x,src.y,dst.x,dst.y,eat.x,eat.y);
    return 1;
  }
  return 0;
}

void nextPlayer(Game * game){
  game->currentPlayer = (game->currentPlayer+1)%2;
}


int nbPawnOnBoardPlayer(Game * game, int player){
  int nb = 0;
  for (int r = 0; r < CELL_R; r++) {
		for (int c = CELL_C-1; c >= 0; c--) {
      if (game->board[r][c].state == FILL && game->board[r][c].color == player )
        nb++;
    }
  }
  return nb;
}

Player * getWinner(Game * game){
  if (nbPawnOnBoardPlayer(game,BLACK) == 0){
    return &(game->white);
  }else{
    return &(game->black);
  }
}
