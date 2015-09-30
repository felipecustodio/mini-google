#ifndef _WEBSITE_H_
#define _WEBSITE_H_

#include "globals.h"

/*-------------------------------------------------------

	TAD WEBSITE
	
---------------------------------------------------------*/

/*-------------------------------------------------------

	TAD WEBSITE
	
---------------------------------------------------------*/

typedef struct keywords {

	char **keywords;
	int total;
	
} KEYWORDS;

/*-------------------------------------------------------

	TAD WEBSITE
	
---------------------------------------------------------*/

typedef struct website {
	// Propriedades de um website
	int id;
	char name[50];
	int rank;
	char address[100];
	KEYWORDS *keywords;
	boolean related;
	// Lista duplamente ligada
	struct website *next;
	struct website *previous;

} WEBSITE;

/*-------------------------------------------------------

	TAD WEBSITE
	
---------------------------------------------------------*/

typedef struct search {

	WEBSITE **results;
	int total;

} SEARCH;

#endif