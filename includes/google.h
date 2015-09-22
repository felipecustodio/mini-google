#ifndef __GOOGLE_H__
#define __GOOGLE_H__

#include <stdio.h>
#include <stdlib.h>
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

DATABASE *createDatabase(void);
boolean insertWebsite(DATABASE *database);
WEBSITE insertKeyword(WEBSITE *site, char* newKeyword);
void removeWebsite();
void updateRank(WEBSITE *site, int newRank);
void printList();
void searchKeyword(DATABASE *database, char *keyword);
void relatedWebsites();
boolean emptyList(DATABASE *database);
void shutdown();

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