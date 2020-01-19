
#include "ia.h"


void play_ia(Game * game){
  Point pt;
  Point move[2];
  int r, c;
  int eatMove =0;

  int nbPawn = nbPawnOnBoardPlayer(game, BLACK);

  if (nbPawn > 0){
    for (r = 0; r < CELL_R && eatMove == 0; r++) {
        for (c = 0; c < CELL_C && eatMove == 0; c++) {
          if (game->board[r][c].state == FILL && game->board[r][c].color == BLACK){
            pt.x = r;pt.y=c;
            checkBestMove(game,pt,move);
            if (move[0].x != move[1].x || move[0].y != move[1].y)
              eatMove = 1;
          }
        }
    }
    //Si un mouvement gagnant existe
    if (move[0].x != move[1].x || move[0].y != move[1].y){
      movePawn(game,move[0],move[1]);
      game->black.score++;
      eatSecondPawn(game);
      //Sinon si le stock n'est pas vide
    }else if(game->black.stock > 0){
      placePawnIa(game);
    }else{
      movePawnUseless(game);
    }
  }else{
    placePawnIa(game);
  }
  nextPlayer(game);
}

void checkBestMove(Game * game,Point pt, Point move[2]){
  setBoardAccessibility(game,pt);
  Point pt2;
  move[0] = pt;
  move[1] = pt;

  for (int r = 0; r < CELL_R; r++) {
		for (int c = CELL_C-1; c >= 0; c--) {
      if (game->board[r][c].state == ACCESSIBLE){
        pt2.x = r;pt2.y = c;
        //Si un coups est gagnant !
        if (fabs(pt.x-pt2.x) == 2 || fabs(pt.y-pt2.y) == 2 ){
          move[1] = pt2;
        }
      }
    }
  }
  resetBoardAccessibility(game);
}

void placePawnIa(Game * game){
  Point pt;
  int place = 0;

  for (int r = 0; r < CELL_R; r++) {
    for (int c = CELL_C-1; c >= 0; c--) {
      if (game->board[r][c].color == WHITE && game->board[r][c].state == FILL){
        pt.x = r ; pt.y = c ;
        setBoardAccessibility(game,pt);
      }
    }
  }

  for (int r = 0; r < CELL_R && place == 0; r++) {
    for (int c = CELL_C-1; c >= 0 && place == 0; c--) {
      if (game->board[r][c].state == EMPTY){
        pt.x = r ; pt.y = c ;
        game->board[pt.x][pt.y].state = FILL;
        game->board[pt.x][pt.y].color = BLACK;
        place = 1;
      }
    }
  }

  //Si aucune case n'est sans danger suicide un pion
  if (place == 0){
    for (int r = 0; r < CELL_R && place == 0; r++) {
      for (int c = CELL_C-1; c >= 0 && place == 0; c--) {
        if (game->board[r][c].state == ACCESSIBLE){
          pt.x = r ; pt.y = c ;
          game->board[pt.x][pt.y].state = FILL;
          game->board[pt.x][pt.y].color = BLACK;
          place = 1;
        }
      }
    }
  }

  game->black.stock--;
  resetBoardAccessibility(game);
}
int isSafeMove(Game * game, Point src,Point dst){
  int tuple[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};
  Point p;
  int state,color;

  for (int i=0;i<4;i++){
    p.x = dst.x+tuple[i][0];
    p.y = dst.y+tuple[i][1];

    if(isInBoard(p)){
  		state = game->board[p.x][p.y].state;
  		color = game->board[p.x][p.y].color;

  		if(state == FILL && color != game->currentPlayer){
  			//Si la case est rempli par un pion d'un autre joueur alors move unsafe
        return 0;
  		}
    }
  }
  return 1;
}

void checkSafeMove(Game * game,Point pt, Point move[2]){
  setBoardAccessibility(game,pt);
  Point pt2;
  move[0] = pt;
  move[1] = pt;

  for (int r = 0; r < CELL_R; r++) {
    for (int c = CELL_C-1; c >= 0; c--) {
      if (game->board[r][c].state == ACCESSIBLE){
        pt2.x = r;pt2.y = c;
        //Si un coups est gagnant !
        if (isSafeMove(game,pt,pt2)){
          move[1] = pt2;
        }
      }
    }
  }
  resetBoardAccessibility(game);
}


void movePawnUseless(Game * game){
  Point pt;
  Point move[2];
  int c,r,safeMove=0;
  for (r = 0; r < CELL_R && safeMove == 0; r++) {
      for (c = 0; c < CELL_C && safeMove == 0; c++) {
        if (game->board[r][c].state == FILL && game->board[r][c].color == BLACK){
          pt.x = r;pt.y=c;
          checkSafeMove(game,pt,move);
          if (move[0].x != move[1].x || move[0].y != move[1].y)
            safeMove = 1;
        }
      }
  }

  movePawn(game,move[0],move[1]);
}


void eatSecondPawn(Game * game){
  int nbPawnAdverse = nbPawnOnBoardPlayer(game,WHITE);
  int eat = 0;

  if (nbPawnAdverse == 0){
    game->white.stock--;
  }else{
    for (int r = 0; r < CELL_R && eat == 0; r++) {
        for (int c = 0; c < CELL_C && eat == 0; c++) {
          if (game->board[r][c].state == FILL && game->board[r][c].color == WHITE){
            game->board[r][c].state = EMPTY;
            eat = 1;
          }
        }
    }
  }

}
