#include "google.h"

/*-------------------------------------------------------

	DEFINIÇÕES
	
---------------------------------------------------------*/

typedef struct database {

	WEBSITE *first;
	WEBSITE *last;
	int size;

} DATABASE;


/*-------------------------------------------------------

	FUNÇÕES DE MANIPULAÇÃO DA LISTA
	
---------------------------------------------------------*/

DATABASE *createDatabase (void)
{
	DATABASE *database = (DATABASE *) malloc(sizeof(DATABASE));

	if (database != NULL)
	{
		database->first = NULL;
		database->last = NULL;
		database->size = 0;
	}

	return database;
}

boolean insertWebsite(DATABASE *database)
{
	WEBSITE *newW = (WEBSITE *) malloc(sizeof(WEBSITE));

	if (newW != NULL)
	{
		if (database->size == 0)
		{
			database->first = newW;
			database->last = newW;
		}
		else
		{
			database->last->next = newW;
		}

		database->size++;

		return true;
	}
	else
		return false;
}

void insertKeyword();
void removeWebsite();
void updateRank();
void printList();
void searchKeyword();
void relatedWebsites();
void shutdown();