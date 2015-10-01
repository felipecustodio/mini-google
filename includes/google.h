#ifndef __GOOGLE_H__
#define __GOOGLE_H__

#include "website.h"
#include "globals.h"

/*-------------------------------------------------------

	DEFINIÇÕES
	
---------------------------------------------------------*/

// Relevância máxima
#define MAX_RANK 1000
// Limite de palavras-chave
#define MAX_KEYWORDS 10

typedef struct database {

	// Lista circular com cabeçalho
	WEBSITE *header;
	int size;

} DATABASE;

/*-------------------------------------------------------

	FUNÇÕES DO MENU
	
---------------------------------------------------------*/

// Funções funcionando:
void createDatabase(DATABASE **database);
boolean insertWebsite(DATABASE *data, WEBSITE *node);
WEBSITE insertKeyword(WEBSITE *site, char* newKeyword);
boolean removeWebsite(DATABASE **data, WEBSITE *removal);
void updateRank(WEBSITE *site);

// Funções para terminar/testar:


WEBSITE *newWebsite();

void printList();
void searchKeyword(DATABASE *database, char *keyword);
void relatedWebsites();
boolean emptyList(DATABASE *database);
void shutdown();

#endif