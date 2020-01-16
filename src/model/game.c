
#include "game.h"
#include <stdio.h>

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
    game->board[1][0].state = FILL;
    game->board[1][0].color = WHITE;

    // init player
    Player newplayer;
    newplayer.stock = 20;
    newplayer.deadPauns = 0;
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
}
