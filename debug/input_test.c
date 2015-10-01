#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// DEFINIÇÕES

typedef enum {
	false, true
} boolean;

void errorCheck(void *pointer, char *pointerName) {
	if (pointer == NULL) {
		printf("Não há memória suficiente para alocar %s. Saindo...\n", pointerName);
		exit(0);
	}
}

#define COMMA 44
#define ENTER 10

char* readString(FILE *pointer, int flag) {
	
	char* string = NULL;
	char value = '@';
	char stop = '@';
	int counter = 0;

	if(flag) {
		stop = COMMA;
	} else {
		stop = ENTER;
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

void printHeader(void)
{
	printf("\t  __  __ _       _    _____                   _       \n");
	printf("\t |  \\/  (_)     (_)  / ____|                 | |      \n");
	printf("\t | \\  / |_ _ __  _  | |  __  ___   ___   __ _| | ___  \n");
	printf("\t | |\\/| | | '_ \\| | | | |_ |/ _ \\ / _ \\ / _` | |/ _ \\ \n");
	printf("\t | |  | | | | | | | | |__| | (_) | (_) | (_| | |  __/ \n");
	printf("\t |_|  |_|_|_| |_|_|  \\_____|\\___/ \\___/ \\__, |_|\\___| \n");
	printf("\t                                         __/ |        \n");
	printf("\t                                        |___/         \n");
}

// Relevância máxima
#define MAX_RANK 1000
// Limite de palavras-chave
#define MAX_KEYWORDS 10

typedef struct keywords {

	char **keywords;
	int total;
	
} KEYWORDS;

typedef struct website {
	// Propriedades de um website
	int id;
	char *name;
	int rank;
	char *address;
	KEYWORDS *keywords;
	boolean related;
	// Lista duplamente ligada
	struct website *next;
	struct website *previous;

} WEBSITE;

typedef struct database {

	// Lista circular com cabeçalho
	WEBSITE *header;
	int size;

} DATABASE;

typedef struct search {

	WEBSITE **results;
	int total;

} SEARCH;

void createDatabase(DATABASE **database)
{
	(*database) = (DATABASE *) malloc(sizeof(DATABASE));

	if (database != NULL)
	{
		WEBSITE *sentinel = (WEBSITE *)malloc(sizeof(WEBSITE));
		sentinel->name = (char*)malloc(sizeof(char) * 100);
		sentinel->name = "header_sentinel";

		(*database)->header = sentinel;
		(*database)->header->next = sentinel;
		(*database)->header->previous = sentinel;
		(*database)->size = 0;

	}
}

boolean insertWebsite(DATABASE *data, WEBSITE *newWebsite)
{
	if (newWebsite != NULL)
	{
		WEBSITE *aux = NULL;
		WEBSITE *end = (data)->header->previous;

		aux = end;
		aux->next = newWebsite;
		end = newWebsite;
		newWebsite->previous = aux;
		newWebsite->next = (data)->header;
		(data)->header->previous = newWebsite;
		(data)->size++;

		return true;
	}
	else
		return false;
}

KEYWORDS* readKeywords(FILE *googlebot) {

	//printf("Criando KEYWORDS auxiliar\n");
	KEYWORDS *keylist = (KEYWORDS*)malloc(sizeof(KEYWORDS));
	keylist->keywords = NULL;
	keylist->total = 0;

	char *keywords = NULL;
	char **keywordsList = NULL;
	char *token = NULL;
	char value;
	int i;
	int counter = 0;
	int byteCounter = 0;
	int tokenCounter = 0;


	//printf("Iniciando leitura\n");
	//printf("reading:\n");
	do
	{

		value = fgetc(googlebot);
		byteCounter++;
		//printf("%c", value);
		keywords = (char*)realloc(keywords, sizeof(char) * counter + 1);
		if(value != ENTER) {
			keywords[counter] = value;
			counter++;
		}

	} while (value != ENTER);

	token = strtok(keywords, ",");
	//printf("token = %s\n", token);
	keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (tokenCounter + 1));
	keylist->keywords[tokenCounter] = (char*)malloc(sizeof(char) * (strlen(token)));
	strcpy(keylist->keywords[tokenCounter], token);
	//printf("allocated %s\n", keylist->keywords[tokenCounter]);
	tokenCounter++;

	while (token != NULL) 
	{

		token = strtok(NULL, ",");
		//printf("token = %s\n", token);
		if (token != NULL) {
			keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (tokenCounter + 1));
			keylist->keywords[tokenCounter] = (char*)malloc(sizeof(char) * (strlen(token)));
			strcpy(keylist->keywords[tokenCounter], token);
			//printf("allocated %s\n", keylist->keywords[tokenCounter]);
			tokenCounter++;
		}

	}

	keylist->total = tokenCounter;
	return keylist;

}

void readData(char* filename, DATABASE **data) {
	
	printHeader();

	// WEBSITE *aux = NULL;

	int counter = 0;

	FILE *googlebot = fopen(filename, "r");

	long int contaBytes = 0;
	long int totalBytes = 0;
	char buffer;
	int i, j;
	fseek(googlebot, 0L, SEEK_END);
	totalBytes = ftell(googlebot);
	rewind(googlebot);


	if(googlebot == NULL) {
		printf("O arquivo CSV não pôde ser aberto. Saindo...\n");
		exit(0);
	}

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

		insertWebsite((*data), aux);

		contaBytes = ftell(googlebot);

	} while((!feof(googlebot)) && (contaBytes < totalBytes - 1));

	fclose(googlebot);

}

void printCSV(DATABASE* data) {

	printf("\tPRINT DATA:\n\t");

	WEBSITE *aux = NULL;
	aux = data->header->next;
	while (aux != data->header) {
		printf("%s -> ", aux->name);
		aux = aux->next;	
	}

	printf("%s -> ", aux->name);
	aux = aux->next;
	printf("%s -> ", aux->name);
	aux = aux->next;
	printf("%s -> ", aux->name);

}

int main(int argc, char const *argv[]) {
	DATABASE *data = NULL;
	createDatabase(&data);
	//printHeader();
	//printf("Iniciando leitura de 'googlebot.csv'\n");
	readData("googlebot.csv", &data);
	printCSV(data);
	return 0;
}