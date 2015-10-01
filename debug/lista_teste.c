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

void printWebsite(WEBSITE *print) {

	int i;
	printf("\t");
	printf("ID: %d ", print->id);
	printf("NOME: %s ", print->name);
	printf("RANK: %d ", print->rank);
	printf("URL: %s ", print->address);
	printf("PALAVRAS-CHAVE: ");
	for (i = 0; i < print->keywords->total; i++) {	
		printf("%s ", print->keywords->keywords[i]);
	}
	printf("\n");

}


void printList(DATABASE *data) {

	WEBSITE *aux = NULL;
	aux = data->header->next;
	while (aux != data->header) {
		printWebsite(aux);
		aux = aux->next;
	}
}


/*-------------------------------------------------------
	
		newWebsite
	
---------------------------------------------------------*/

void newWebsite(DATABASE **data) {

	int i;
	int keytotal = 0;
	WEBSITE *new = NULL;
	new = (WEBSITE*)malloc(sizeof(WEBSITE));

	printf("\tINSIRA OS DADOS DO NOVO WEBSITE:\n");
	new->id = (*data)->header->previous->id + 1;

	printf("\tINSIRA O NOME: ");
	new->name = readString(stdin, 0);

	printf("\tINSIRA O RANK: ");
	scanf("%d", &new->rank);
	getchar();

	printf("\tINSIRA O ENDEREÇO: ");
	new->address = readString(stdin, 0);

	new->keywords = (KEYWORDS*)malloc(sizeof(KEYWORDS));
	printf("\tINSIRA O NÚMERO DE KEYWORDS: ");
	scanf("%d", &keytotal);

	new->keywords->total = keytotal;

	getchar();
	new->keywords->keywords = (char**)malloc(sizeof(char*) * new->keywords->total);

	printf("\tINSIRA AS KEYWORDS:\n");
	for (i = 0; i < new->keywords->total; i++) {
		printf("\tKEYWORD %d: ", i+1);
		new->keywords->keywords[i] = readString(stdin, 0);
	}

	new->related = false;
	new->next = NULL;
	new->previous = NULL;

	insertWebsite(*data, new);

}

void writeCSVFile(DATABASE* database, const char* filename)
{
    FILE* csv_file = fopen(filename, "w");
    if (csv_file == NULL)
    {
        printf("Could not open the file: %s\n", filename);
        exit(0);
    }
    
    WEBSITE* aux = database->header->next;
    int i;
    
    while(aux != database->header)
    {
        fprintf(csv_file, "%d,%s,%d,%s,", aux->id, aux->name, aux->rank, aux->address);
        for(i = 0; i < aux->keywords->total-1; i++)
        {
            fprintf(csv_file, "%s", aux->keywords->keywords[i]);
            fprintf(csv_file, ",");
        }
        
        fprintf(csv_file, "%s", aux->keywords->keywords[i]);
        fprintf(csv_file, "\n");
        
        aux = aux->next;
    }
    
    fclose(csv_file);
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
	keylist->keywords = NULL;
	keylist->total = 0;
	keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (2));
	keylist->keywords[0] = (char*)malloc(sizeof(char) * 100);
	keylist->keywords[1] = (char*)malloc(sizeof(char) * 100);
	keylist->keywords[0] = "key1";
	keylist->keywords[1] = "key2";
	keylist->total = 2;
	web2->keywords = keylist;

	WEBSITE *web3 = (WEBSITE*)malloc(sizeof(WEBSITE));
	web3->id = 3;
	web3->name = (char*)malloc(sizeof(char) * 100);
	web3->name = "website3";
	web3->rank = 300;
	web3->address = (char*)malloc(sizeof(char) * 100);
	web3->address = "address3";
	keylist->keywords = NULL;
	keylist->total = 0;
	keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (2));
	keylist->keywords[0] = (char*)malloc(sizeof(char) * 100);
	keylist->keywords[1] = (char*)malloc(sizeof(char) * 100);
	keylist->keywords[0] = "key1";
	keylist->keywords[1] = "key2";
	keylist->total = 2;
	web3->keywords = keylist;
	web3->address = (char*)malloc(sizeof(char) * 100);
	web3->address = "address3";


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

    removeWebsite(&data, web2);
    removeWebsite(&data, web3);
    
	aux = data->header->next;
	while (aux != data->header) {
	 	printf("%s %d -> ", aux->name, aux->rank);
	 	aux = aux->next;	
	}

	printf("%s %d -> ", aux->name, aux->rank);
	aux = aux->next;
	printf("%s %d-> ", aux->name, aux->rank);
	printf("\n\n");



	printList(data);

    removeWebsite(&data, web2);
    removeWebsite(&data, web3);
    writeCSVFile(data, "teste.csv");

	return 0;
}