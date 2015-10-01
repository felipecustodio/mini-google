/*-------------------------------------------------------

	FUNÇÕES DE LEITURA DE ARQUIVO .CSV
	
---------------------------------------------------------*/

#include "input.h"

/*-------------------------------------------------------

	readKeywords(FILE *googlebot)

		DESCRIÇÃO:

		Lê as palavras chaves do website atual no arquivo.
		Como o programa é feito em C, existem vários casos
		para serem tratados durante a leitura, pois o número
		de keywords por website é variável e a leitura deve
		ser feita até uma vírgula ou quebra de linha. 

		PARÂMETROS:

			@ FILE *googlebot: 
			FILE STREAM do arquivo aberto, googlebot.csv

---------------------------------------------------------*/

KEYWORDS* readKeywords(FILE *googlebot) {

	// lista de keywords auxiliar para leitura
	KEYWORDS *keylist = (KEYWORDS*)malloc(sizeof(KEYWORDS));
	keylist->keywords = NULL;
	keylist->total = 0;

	// string auxiliar que irá armazenar as keywords e caracteres
	// de separação, para depois ser quebrada em keywords
	char *keywords = NULL; 

	// token de separação de strings (strtok)
	char *token = NULL;
	char value;

	// contadores auxiliares
	int counter = 0;
	int byteCounter = 0;
	int tokenCounter = 0;

	do
	{

		value = fgetc(googlebot);
		byteCounter++;

		keywords = (char*)realloc(keywords, sizeof(char) * counter + 1);
		// inserir todos os caracteres até a quebra de linha
		if(value != ENTER) {
			keywords[counter] = value;
			counter++;
		}

	} while (value != ENTER);

	// iniciar quebra de keywords em 'tokens'
	token = strtok(keywords, ",");

	// armazenar na lista de keywords auxiliar
	keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (tokenCounter + 1));
	keylist->keywords[tokenCounter] = (char*)malloc(sizeof(char) * (strlen(token)));
	strcpy(keylist->keywords[tokenCounter], token);

	tokenCounter++;

	// encontrar e armazenar os próximos tokens
	while (token != NULL) 
	{

		token = strtok(NULL, ",");

		if (token != NULL) {

			keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (tokenCounter + 1));
			keylist->keywords[tokenCounter] = (char*)malloc(sizeof(char) * (strlen(token)));
			strcpy(keylist->keywords[tokenCounter], token);

			tokenCounter++;
		}

	}

	keylist->total = tokenCounter;
	return keylist;

}

/*-------------------------------------------------------

	readData(char* filename, DATABASE **data)

		DESCRIÇÃO:
			Realiza a leitura do arquivo (filename), escrevendo
			em um DATABASE já existente na main. 

		PARÂMETROS:
			
			@char *filename: nome do arquivo a ser lido
			@DATABASE **data: endereço do ponteiro de lista *data

---------------------------------------------------------*/

void readData(char* filename, DATABASE **data) {

	long int contaBytes = 0; // controlador do laço de leitura
	long int totalBytes = 0; // condição de parada da leitura
	
	/*-------------------------------------------------------
		ABRIR ARQUIVO
	---------------------------------------------------------*/

	FILE *googlebot = fopen(filename, "r");

	if(googlebot == NULL) {
		printf("O arquivo CSV não pôde ser aberto. Saindo...\n");
		exit(0);
	}
	
	// contador de bytes do arquivo
	fseek(googlebot, 0L, SEEK_END);
	totalBytes = ftell(googlebot);
	rewind(googlebot);

	// loop de leitura
	do {

		WEBSITE *aux = NULL;

		if (aux == NULL) {
			aux = (WEBSITE*)malloc(sizeof(WEBSITE));
		}	

		fscanf(googlebot, "%d", &(aux->id));
		buffer = fgetc(googlebot);

		aux->name = readString(googlebot, 1);

		fscanf(googlebot, "%d", &(aux->rank));
		buffer = fgetc(googlebot);

		aux->address = readString(googlebot, 1);
		(aux->keywords) = readKeywords(googlebot);

		aux->related = false;

		// inserir nó auxiliar na lista definitiva
		insertWebsite((*data), aux);

		// seta o contador de bytes para a posição atual
		contaBytes = ftell(googlebot);

	} while((!feof(googlebot)) && (contaBytes < totalBytes - 1));

	// SOBRE O FUNCIONAMENTO DO LOOP DE LEITURA: 
	// loop de leitura vai até o penúltimo byte (antes do \n final)
	// como usamos uma função auxiliar para ler strings, utilizar apenas o 
	// feof causa um erro, pois ao chegar no caractere EOF, a função é chamada
	// e tenta ler uma região do arquivo inexistente.

	fclose(googlebot);

	// LIBERAR MEMÓRIA!!!

}

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