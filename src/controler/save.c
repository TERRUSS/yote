#include <stdio.h>

void saveScore (Player * winner) {
	FILE * score;
	int i;
	tab[5];
	// open the file for writing
	score = fopen("../.scores","w");
	for (int i = 0; i < 5; i++) {
		readScore(i,tab[i]);
	}
	fprintf(score, "%s; %d", white->name, white->score);

	// close the file
	fclose(score);
	return 0;
}

#define MAXCHAR 1000

void readScore (int line; char * score) {
	FILE *score;
	char str[MAXCHAR];

	score = fopen("../.scores", "r");
	if (score == NULL){
		printf("Could not open file %s",filename);
		return 1;
	}
	// while (fgets(str, MAXCHAR, score) != NULL)
	// 	printf("%s", str);

	for (int i = 0; i < count && fgets(str, MAXCHAR, score) != NULL; i++) {}

	if (fgets(str, MAXCHAR, score)!= NULL){
		score = str;
	}

	fclose(score);
	return 0;
}
