/*-------------------------------------------------------

	TAD WEBSITE
	
---------------------------------------------------------*/


#ifndef __GOOGLE_H__
#define __GOOGLE_H__

/*-------------------------------------------------------

	DEFINIÇÕES
	
---------------------------------------------------------*/

// Relevância máxima
#define MAX_RANK 1000
// Limite de palavras-chave
#define MAX_KEYWORDS 10

#define TRUE 1
#define FALSE 0
#define boolean int

#define COMMA 42
#define ENTER 10

typedef struct website WEBSITE;
typedef struct database DATABASE;

/*-------------------------------------------------------

	FUNÇÕES DE MANIPULAÇÃO DE ARQUIVO
	
---------------------------------------------------------*/

void readCSV();


/*-------------------------------------------------------

	FUNÇÕES DO MENU
	
---------------------------------------------------------*/

void insertWebsite();
void insertKeyword();
void removeWebsite();
void updateRank();
void printList();
// Busca binária?
void searchKeyword();
void relatedWebsites();
void shutdown();

/*-------------------------------------------------------

	FUNÇÕES DE MANIPULAÇÃO DA LISTA
	
---------------------------------------------------------*/

// Moaça mito
void mergeSort();

/*WEBSITE *newWebsite(void);
boolean insert(int index, WEBSITE *database);
boolean remove_website(int index, WEBSITE *database);
boolean exists(int index, WEBSITE *database);
boolean compare(char *string1, char *string2);
int databaseSize(WEBSITE *database);
boolean fullList(WEBSITE *database);
boolean emptyList(WEBSITE *database);
void dump_data(WEBSITE *database);*/

#endif