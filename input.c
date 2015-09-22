#include <stdio.h>
#include <stdlib.h>

void readCSV() {

	FILE *bot = NULL;
	bot = fopen("googlebot.csv", "r");

	while (!feof(bot)) {

		scanf("%d", &id);
		getchar();
		name = readString(',');
		scanf("%d", &id);
		getchar();
		link = readString(',');
		while (value != 10) {
			// realloc links
			link[i] = readString(',');
		}

		id, nome, rank, link, palavra-chave

	}
}

char* readString(char stop) {
	
	char* string = NULL;
	char value = '@';
	int counter = 0;

	while (value != stop) {

		scanf("%c", &value);
		string = (char*)realloc(string, sizeof(char) * counter + 1);
		string[counter] = value;		
		counter++;

	}

	string[counter-1] = '\0';

	return string;

}