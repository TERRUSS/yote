
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
    game->board[1][2].state = FILL;
    game->board[1][2].color = WHITE;

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
