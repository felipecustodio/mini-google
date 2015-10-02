#ifndef __GOOGLE_H__
#define __GOOGLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "google.h"
#include "website.h"
#include "globals.h"
#include "menu.h"

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

void createDatabase(DATABASE **database);
boolean insertWebsite(DATABASE *data, WEBSITE* node);
void insertKeyword(WEBSITE **site, char* newKeyword);
boolean removeWebsite(DATABASE **data, WEBSITE *removal);
void updateRank(WEBSITE *site);
void newWebsite(DATABASE **data);
SEARCH* searchKeyword(DATABASE *database, char *keyword);
void relatedWebsite(DATABASE* database, SEARCH* search, char *keyword);
boolean emptyList(DATABASE *database);
void writeCSVFile(DATABASE* database, const char* filename);
WEBSITE* searchID(DATABASE* database, const int id);

KEYWORDS* readKeywords(FILE *googlebot);
void readData(char* filename, DATABASE **data);

void printWebsite(WEBSITE *print);
void printList(DATABASE *data);
void printSearch(SEARCH *search, DATABASE *data);

void destroyDataBase(DATABASE* data);
void destroySearch(SEARCH* search);

#endif