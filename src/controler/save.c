#include <stdio.h>
#include "save.h"

#define MAXCHAR 256

void saveScore (Player * winner) {
	FILE * score;
	Player leaderBoard[10];
	char tmp;
	// open the file for writing
	score = fopen("../.scores","w");

	fprintf(score, "%s;%d", winner->name, winner->score);

	int i = 0;
	while(readScore(i, leaderBoard[i].name) && i<10){
		parseString(&leaderBoard[i]);
		i++;
	}

	sortLeaderBoard(leaderBoard);

	instertScore(leaderBoard, winner);

		//rewrite the file
	for (int i = 0; i < 10; i++) {
		fprintf(score, "%s;%d", leaderBoard[i].name, leaderBoard[i].score);
	}

	// close the file
	fclose(score);
}


int readScore (int line, char * score) {
	FILE *scoreFile;
	char str[MAXCHAR] = {0};

	scoreFile = fopen("../.scores", "r");
	if (score == NULL){
		printf("Could not open the score file");
		return 0;
	}
	int i = 0;
	while ( fgets(str, MAXCHAR, scoreFile) != NULL ) {
		i++;
		if (i == line) {
			score = str;
			break;
		}
	}

	fclose(scoreFile);

	if (str[0])
		return 1;
	else
		return 0;
}

void parseString (Player * player){
	// char tmp_name[MAXCHAR];
	// char tmp_score[MAXCHAR];
	// int i,j;
	//
	// for (int i = 0; i < MAXCHAR ; i++) {
	//
	// 	if (player->name[i] == ';') {
	// 		for (int j = 0; j < i; j++) {
	// 			tmp_name[j]=player->name[j];
	// 		}
	// 		j=0;
	// 		while (player->name[j] != 0) {
	// 			tmp_score[j] = player->name[i+j];
	// 			j++;
	// 		}
	// 	}
	// }
	//
	// strcpy(player->name, tmp_name);
	// player->score = tmp_score;
}

void sortLeaderBoard (Player * leaderBoard){
	// int i,j;
	// char tmp;
	//
	// for (int i = 0; i < 9; i++) {
	// 	for (int j = 0; j < 9; j++) {
	//
	// 		if (leaderBoard[i]->score < leaderBoard[j+1]->score) {
	// 			tmp = leaderBoard[i]->score;
	// 			leaderBoard[i]->score = leaderBoard[j+1]->score;
	// 			leaderBoard[i+1]->score = leaderBoard[j]->score;
	// 		}
	// 	}
	// }
}

void instertScore (Player * leaderBoard, Player * winner){
	// int i,j;
	// char tmp;
	//
	// for (int i = 0; i < 9; i++) {
	// 	for (int j = 0; j < 9; j++) {
	//
	// 		if (leaderBoard[i]->score < leaderBoard[j+1]->score) {
	// 			tmp = leaderBoard[i]->score;
	// 			leaderBoard[i]->score = leaderBoard[j+1]->score;
	// 			leaderBoard[i+1]->score = leaderBoard[j]->score;
	// 		}
	// 	}
	// }
}
