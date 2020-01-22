#include <stdio.h>

#define LEN 256

void saveScore (Game * game) {
	FILE * score;
	int i;
	/* open the file for writing*/
	score = fopen ("./score.txt","w");

	/* write 10 lines of text into the file stream*/
	fprintf(score, "%s; %d|%d\n", game->white.name, game->white.score, game->white.stock);

	/* close the file*/
	fclose (score);
	return 0;
}

#define MAXCHAR 1000

int readScore () {
	FILE *score;
	char str[MAXCHAR];
	char* filename = "./score.txt";

	score = fopen(filename, "r");
	if (score == NULL){
		printf("Could not open file %s",filename);
		return 1;
	}
	while (fgets(str, MAXCHAR, score) != NULL)
		printf("%s", str);
	fclose(score);
	return 0;
}
