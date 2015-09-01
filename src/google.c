#include <stdio.h>
#include <stdlib.h>
#include "google.h"

/*-------------------------------------------------------

	DEFINIÇÕES
	
---------------------------------------------------------*/

typedef struct database {

	WEBSITE *first;
	WEBSITE *last;
	int size;

} DATABASE


/*-------------------------------------------------------

	FUNÇÕES DE MANIPULAÇÃO DA LISTA
	
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