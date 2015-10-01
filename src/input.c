/*-------------------------------------------------------

	FUNÇÕES DE LEITURA DE ARQUIVO .CSV
	
---------------------------------------------------------*/

#include "input.h"


/*-------------------------------------------------------

	readData(char* filename, DATABASE **data)

		DESCRIÇÃO:
			Realiza a leitura do arquivo (filename), escrevendo
			em um DATABASE já existente na main. 

		PARÂMETROS:
			
			@char *filename: nome do arquivo a ser lido
			@DATABASE **data: endereço do ponteiro de lista *data

---------------------------------------------------------*/

char* readString(FILE *pointer, int flag) {
	
	char* string = NULL;
	char value = '@';
	char stop = '@';
	int counter = 0;

	if(flag) {
		stop = ',';
	} else {
		stop = '\n';
	}


	//printf("readString call\n");
	//printf("reading: ");

	do {
		//  && value != ENTER
		fscanf(pointer, "%c", &value);
		//printf("%c", value);
		string = (char*)realloc(string, sizeof(char) * counter + 1);
		string[counter] = value;		
		counter++;

	} while (value != stop);
	//printf("\n");
	//printf(" ");

	string[counter-1] = '\0';

	return string;

}