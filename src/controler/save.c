#include <stdio.h>
#include "save.h"

void saveScore (Player * winner) {
	FILE * score;
	Player leaderBoard[10];
	char tmp;
	// open the file for writing
	score = fopen("../../.scores","w");

	fprintf(score, "%s;%d", winner->name, winner->score);

	int i = 0;
	while(readScore(i, leaderBoard[i].name) && i<10){
		parseString(&leaderBoard[i]);
		i++;
	}

	sortLeaderBoard(leaderBoard, i);

	instertScore(leaderBoard, i, winner);

		//rewrite the file
	for (int i = 0; i < 10; i++) {
		fprintf(score, "%s;%d", leaderBoard[i].name, leaderBoard[i].score);
	}

	// close the file
	fclose(score);
}


int readScore (int line, char * score) {
	FILE *scoreFile;
	int ok = 0;
	// char str[MAXCHAR] = {0};
	scoreFile = fopen("./.scores", "r");

	if (score == NULL){
		printf("Could not open the score file");
		return 0;
	}
	int i = 0;
	while ( fgets(score, MAXCHAR, scoreFile) != NULL ) {
		if (i == line) {
			ok = 1;
			break;
		}
		i++;
	}

	fclose(scoreFile);

	return ok;
}

void parseString (Player * player){
	char tmp_name[MAXCHAR];
	char tmp_score[MAXCHAR];
	int i,j;

	for (int i = 0; i < MAXCHAR ; i++) {

		if (player->name[i] == ';') {
			for (int j = 0; j < i; j++) {
				tmp_name[j]=player->name[j];
			}
			j=0;
			while (player->name[j] != 0) {
				tmp_score[j] = player->name[i+j];
				j++;
			}
		}
	}

	strcpy(player->name, tmp_name);
	sscanf(tmp_score, "%d", player->score); ;
}

void sortLeaderBoard (Player * leaderBoard, int length){

	Player tmp;

	for (int i = 0; i < length-1; i++) {
		for (int j = 0; j < length-1 - i; j++ ) {
			if (leaderBoard[j].score > leaderBoard[j+1].score) {
				tmp = leaderBoard[j+1];
				leaderBoard[j+1] = leaderBoard[j];
				leaderBoard[j] = tmp;
			}
		}
	}

}

void instertScore (Player * leaderBoard, int lenght, Player * winner){

	Player tmp;

	for (int i = 0; i < lenght; i++) {
		if (leaderBoard[i].score < winner->score) {
			tmp = leaderBoard[i];
			leaderBoard[i] = *winner;

			instertScore(leaderBoard, lenght, &tmp);
			break;
		}
	}
}
