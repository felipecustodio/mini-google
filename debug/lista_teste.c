// Implementação de Lista Dinâmica Circular com Cabeçalho

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

char* readString(FILE *pointer) {
	
	char* string = NULL;
	char value = '@';
	int counter = 0;


	//printf("readString call\n");
	//printf("reading: ");

	do {
		//  && value != ENTER
		if (pointer == NULL) {
			scanf("%c", &value);
		} else {
		fscanf(pointer, "%c", &value);
		}
		//printf("%c", value);
		string = (char*)realloc(string, sizeof(char) * counter + 1);
		string[counter] = value;		
		counter++;


	} while (value != ENTER);
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

boolean insertWebsite(DATABASE *database, WEBSITE *newWebsite)
{
	if (newWebsite != NULL)
	{
		WEBSITE *aux = NULL;
		WEBSITE *end = database->header->previous;

		aux = end;
		aux->next = newWebsite;
		end = newWebsite;
		newWebsite->previous = aux;
		newWebsite->next = database->header;
		database->header->previous = newWebsite;
		database->size++;

		return true;
	}
	else
		return false;
}
                                       
void insertKeyword(WEBSITE **site, char* newKeyword) 
{
	// Alocar mais uma string na lista de keywords
	printf("alloc\n");
	(*site)->keywords->keywords = (char**)realloc(((*site)->keywords->keywords), sizeof(char*) * ((*site)->keywords->total + 1));
	printf("string alloc\n");
	(*site)->keywords->keywords[(*site)->keywords->total] = (char*)malloc(sizeof(char) * strlen(newKeyword));
	printf("copy\n");
	strcpy((*site)->keywords->keywords[(*site)->keywords->total], newKeyword);
	printf("increase total\n");
	(*site)->keywords->total++;

}

 //  _______ ______  _____ _______ ______ 
 // |__   __|  ____|/ ____|__   __|  ____|
 //    | |  | |__  | (___    | |  | |__   
 //    | |  |  __|  \___ \   | |  |  __|  
 //    | |  | |____ ____) |  | |  | |____ 
 //    |_|  |______|_____/   |_|  |______|


boolean removeWebsite(DATABASE **data, WEBSITE *removal)
{
	if (removal != NULL) { 

		WEBSITE *aux = NULL;
		removal->previous->next = removal->next;
		removal->next->previous = removal->previous;	

		// ****** LIBERAR MEMÓRIA DO NÓ ********

		return true;
	} else {
		return false;
	}
}

void updateRank(WEBSITE *site, int newRank)
{
	site->rank = newRank;

}

/*-------------------------------------------------------
	
		newWebsite
	
---------------------------------------------------------*/

void newWebsite(DATABASE **data) {

	int i;
	WEBSITE *new = NULL;
	new = (WEBSITE*)malloc(sizeof(WEBSITE));

	printf("\tINSIRA OS DADOS DO NOVO WEBSITE:\n");
	new->id = (*data)->header->previous->id + 1;

	printf("\tINSIRA O NOME: ");
	new->name = readString(stdin);

	printf("\tINSIRA O RANK: ");
	scanf("%d", &new->rank);
	printf("\n");

	printf("\tINSIRA O ENDEREÇO: ");
	new->address = readString(stdin);

	printf("\tINSIRA O NÚMERO DE KEYWORDS: ");
	scanf("%d", &new->keywords->total);
	new->keywords->keywords = (char**)malloc(sizeof(char*) * new->keywords->total);

	printf("\tINSIRA AS KEYWORDS: ");
	for (i = 0; i < new->keywords->total; i++) {

		new->keywords->keywords[i] = readString(stdin);
	}

	new->related = false;
	new->next = NULL;
	new->previous = NULL;

	insertWebsite(*data, new);

}


// ********** MAIN *********

int main(int argc, char const *argv[])
{
	printHeader();
	printf("\n\n");
	DATABASE *data = NULL;
	createDatabase(&data);

	WEBSITE *web1 = (WEBSITE*)malloc(sizeof(WEBSITE));
	web1->id = 1;
	web1->name = (char*)malloc(sizeof(char) * 100);
	web1->name = "website1";
	web1->rank = 100;
	web1->address = (char*)malloc(sizeof(char) * 100);
	web1->address = "address1";

	KEYWORDS *keylist = (KEYWORDS*)malloc(sizeof(KEYWORDS));
	keylist->keywords = NULL;
	keylist->total = 0;
	keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (2));
	keylist->keywords[0] = (char*)malloc(sizeof(char) * 100);
	keylist->keywords[1] = (char*)malloc(sizeof(char) * 100);
	keylist->keywords[0] = "key1";
	keylist->keywords[1] = "key2";
	keylist->total = 2;

	web1->keywords = keylist;


	WEBSITE *web2 = (WEBSITE*)malloc(sizeof(WEBSITE));
	web2->id = 2;
	web2->name = (char*)malloc(sizeof(char) * 100);
	web2->name = "website2";
	web2->rank = 200;
	web2->address = (char*)malloc(sizeof(char) * 100);
	web2->address = "address2";
	WEBSITE *web3 = (WEBSITE*)malloc(sizeof(WEBSITE));
	web3->id = 3;
	web3->name = (char*)malloc(sizeof(char) * 100);
	web3->name = "website3";
	web3->rank = 300;
	web2->address = (char*)malloc(sizeof(char) * 100);
	web2->address = "address3";

	insertWebsite(data, web1);
	insertWebsite(data, web2);
	insertWebsite(data, web3);

	printf("\tPRINT DATA:\n\t");

	WEBSITE *aux = NULL;
	aux = data->header->next;
	while (aux != data->header) {
		printf("%s %d -> ", aux->name, aux->rank);
		aux = aux->next;	
	}

	printf("%s %d -> ", aux->name, aux->rank);
	aux = aux->next;
	printf("%s %d -> ", aux->name, aux->rank);
	printf("\n\n");

	getchar();

	printf("\tNEW WEBSITE:\n");
	newWebsite(&data);

	printf("\tPRINT DATA:\n\t");

	aux = data->header->next;
	while (aux != data->header) {
		printf("%s %d -> ", aux->name, aux->rank);
		aux = aux->next;	
	}

	printf("%s %d -> ", aux->name, aux->rank);
	aux = aux->next;
	printf("%s %d-> ", aux->name, aux->rank);
	printf("\n\n");

	return 0;
}