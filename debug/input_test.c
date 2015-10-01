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
		fscanf(pointer, "%c", &value);
		//printf("%c", value);
		string = (char*)realloc(string, sizeof(char) * counter + 1);
		string[counter] = value;		
		counter++;

	} while (value != COMMA);
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

		aux->name = readString(googlebot);

		fscanf(googlebot, "%d", &(aux->rank));
		buffer = fgetc(googlebot);

		aux->address = readString(googlebot);
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

SEARCH* searchKeyword(DATABASE *database, char *keyword)
{
    // começar a busca no header com nó sentinela
    SEARCH *search;
    search = (SEARCH*)malloc(sizeof(SEARCH));
    search->total = 0;
    search->results = NULL;
    
    WEBSITE *aux = database->header->next;
    int i, j, compare;
    
    while(aux != database->header)
    {
        // percorrer keywords do website atual
        for (j = 0; j < aux->keywords->total; j++) {
            
            compare = strcmp(aux->keywords->keywords[j], keyword);
            
            if (compare == 0) {
                // TAD search: contém endereços para os sites encontrados na busca
                search->results = (WEBSITE**)realloc(search->results, sizeof(WEBSITE*) * (search->total + 1));
                search->results[search->total] = aux;
                search->total++;
            }
            
        }
        
        aux = aux->next;
        
    }
    
    return search;
    
}

WEBSITE* searchID(DATABASE* database, const int id)
{
    WEBSITE* aux = database->header->next;
    
    while (aux != database->header)
    {
        if (aux->id == id)
        {
            return aux;
        }
        aux = aux->next;
    }
    
    aux = NULL;
    return aux;
}

void relatedWebsites(DATABASE* database, SEARCH* search, char *keyword)
{
    KEYWORDS* keylist = (KEYWORDS*) malloc(sizeof(KEYWORDS));
    keylist->keywords	= (char**) malloc(sizeof(char*) * search->total);
    
    int i;
    for(i = 0; i < search->total; i++)
    {
        //pegando uma palavra por site para buscar relacionados
        if (strcmp(keyword, search->results[i]->keywords->keywords[i]))
            keylist->keywords[i] = search->results[i]->keywords->keywords[i];
        else
        {
            if (i > 0)
            {
                keylist->keywords[i] = search->results[i]->keywords->keywords[i-1];
            }
            else
            {
                keylist->keywords[i] = search->results[i]->keywords->keywords[i+1];
            }
        }
        
    }
    
    WEBSITE* aux = database->header->next;
    
    int j;
    while(aux != database->header)
    {
        for(i = 0; i < keylist->total; i++)
        {
            for(j = 0; j < aux->keywords->total; j++)
            {
                if(strcmp(keylist->keywords[i], aux->keywords->keywords[j]))
                {
                    aux->related = true;
                }
            }
        }
        
        aux = aux->next;
    }
    
    for(i = 0; i < search->total; i++)
    {
        search->results[i]->related = false;
    }
    
    free(keylist->keywords);
    free(keylist);
}

int main(int argc, char const *argv[]) {
	DATABASE *data = NULL;
	createDatabase(&data);
	//printHeader();
	//printf("Iniciando leitura de 'googlebot.csv'\n");
	readData("googlebot.csv", &data);
	printCSV(data);
    
    printf("\n\n");
    SEARCH* test = searchKeyword(data, "reviews");
    int i;
    for(i = 0; i < test->total; i++)
    {
        printf("%s\n", test->results[i]->name);
    }
    relatedWebsites(data, test, "reviews");
    
	return 0;
}