#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // talvez não use
#include "google.h"
#include "website.h"

/*-------------------------------------------------------
	FUNÇÕES DE MANIPULAÇÃO DA LISTA	
---------------------------------------------------------*/

DATABASE *createDatabase (void)
{
	DATABASE *database = (DATABASE *) malloc(sizeof(DATABASE));

	if (database != NULL)
	{
		WEBSITE *sentinel = (WEBSITE *)malloc(sizeof(WEBSITE));
		database->header = sentinel;
		database->header->next = sentinel;
		database->header->previous = sentinel;
		database->size = 0;
	}

	return database;
}

boolean insertWebsite(DATABASE *database)
{
	WEBSITE *newWebsite = (WEBSITE *)malloc(sizeof(WEBSITE));

	if (newWebsite != NULL)
	{
		WEBSITE *aux = NULL;
		WEBSITE *end = database->header->previous;

		aux = end;
		aux->proximo = newWebsite;
		end = newWebsite;
		newWebsite->previous = aux;
		newWebsite->next = database->header;
		database->size++;

		return true;
	}
	else
		return false;
}

WEBSITE insertKeyword(WEBSITE *site, char* newKeyword) 
{

	site->list.keywords = (char**)realloc(site->list.keywords, sizeof(char*) * (site->list.total + 1));
	site->list.keywords[site->list.total] = newKeyword;
	site->list.total = site->list.total + 1;
	return site;

}

boolean removeWebsite(DATABASE *database, WEBSITE *removal)
{
	if (removal != NULL) { 
		removal->next->previous = removal->previous;
		removal->previous->next = removal->next;
		freeWebsite(removal);
		return true;
	} else {
		return false;
	}
}

void updateRank(WEBSITE *site, int newRank)
{
	site->rank = newRank;
	return site;
}

void printList() 
{

}

void searchKeyword(DATABASE *database, char *keyword)
{
	// começar a busca no header com nó sentinela
	WEBSITE *aux = database->header;
	int i, j, compare;
	boolean found;
	
	for (i = 0; i < database->size; i++)
	{
		// percorrer keywords do website atual
		for (j = 0; j < aux->list.size; j++) {
			compare = strcmp(aux->list.keywords[j], keyword);
			if (compare == 0) {
				return true;
			}
		}
	}
}

void relatedWebsites()
{

}

boolean emptyList(DATABASE *database) {

	if(database->header->next == NULL) {
		return true;
	} else {
		return false;
	}

}

void shutdown() 
{
	// limpar memoria
}