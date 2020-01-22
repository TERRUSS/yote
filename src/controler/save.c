#include <stdio.h>
#include "save.h"

void saveScore (Player * winner) {
	FILE * scoreFile;
	Player leaderBoard[10];
	// open the file for writing

	char score[MAXCHAR] = {0};
	int i = 0;
	while(readScore(i, score) && i<10){
		parseString(&leaderBoard[i], score);
		i++;
	}

	// instertScore(leaderBoard, 0, i, winner);
	// for (int k = 0; k <= i && k <10; k++) {
	// 	fprintf("inserted : %s;%d\n", leaderBoard[i].name, leaderBoard[i].score);
	// }

	// printf("\n\n");

		//rewrite the file
	scoreFile = fopen("./.scores","w");

	int inserted = 0;



	for (int k = 0; k < i && k < 10; k++) {
		if (winner->score >= leaderBoard[k].score && !inserted){
			fprintf(scoreFile, "%s;%d\n", winner->name, winner->score);
			if (k < 10) {
				fprintf(scoreFile, "%s;%d\n", leaderBoard[k].name, leaderBoard[k].score);
			}
			inserted = 1;
		}
		else{
			fprintf(scoreFile, "%s;%d\n", leaderBoard[k].name, leaderBoard[k].score);
		}
	}
	if (i == 0) {
		fprintf(scoreFile, "%s;%d\n", winner->name, winner->score);
	}
	// close the file
	fclose(scoreFile);
}


int readScore (int line, char * score) {
	FILE *scoreFile;
	int ok = 0;
	// char str[MAXCHAR] = {0};
	scoreFile = fopen("./.scores", "r");

	if (scoreFile == NULL){
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

void parseString (Player * player, char * score){
	char tmp_name[MAXCHAR];
	char tmp_score[MAXCHAR];

	int i = 0, offset = 0;

	while (score[i] != ';') {
		tmp_name[i] = score[i];
		i++;
	}
	tmp_name[i] = '\0';
	i++;
	offset = i;
	while (score[i] != '\0') {
		tmp_score[i-offset] = score[i];
		i++;
	}


	strcpy(player->name, tmp_name);
	sscanf(tmp_score, "%d", &player->score);
	printf("parsing %s : %s %d ", score, player->name, player->score);

}
