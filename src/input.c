/*-------------------------------------------------------

	FUNÇÃO DE LEITURA AUXILIAR
	
---------------------------------------------------------*/

#include "input.h"

char* readString(FILE *pointer, int flag) {
	
	char* string = NULL;
	char value = '@';
	char stop = '@';
	int counter = 0;

	// FLAG:
	// 1 - lê até uma vírgula
	// 0 - lê até uma quebra de linha
	if(flag) {
		stop = ',';
	} else {
		stop = '\n';
	}


	do {

		fscanf(pointer, "%c", &value);

		string = (char*)realloc(string, sizeof(char) * counter + 1);
		string[counter] = value;		
		counter++;

	} while (value != stop);

	string[counter-1] = '\0';

	return string;

}