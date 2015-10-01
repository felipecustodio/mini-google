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
	// valor inicial setado em um caractere especial
	// para não causar erros com o loop while
	char value = '@';
	char stop = '@';
	int counter = 0;

	if(flag) {
		stop = COMMA;
	} else {
		stop = ENTER;
	}

	do {

		fscanf(pointer, "%c", &value);
		string = (char*)realloc(string, sizeof(char) * counter + 1);
		string[counter] = value;		
		counter++;

	} while (value != stop);

	// transforma o vetor de caracteres em string com final \0
	string[counter-1] = '\0';

	return string;

}