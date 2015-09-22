#ifndef _WEBSITE_H_
#define _WEBSITE_H_

/*-------------------------------------------------------

	TAD WEBSITE
	
---------------------------------------------------------*/

typedef struct keywords {

	char **keywords;
	int total;
	
} KEYWORDS;

typedef struct website {
	// Propriedades de um website
	int id;
	char name[50];
	int rank;
	char link[100];
	KEYWORDS list;
	// Lista duplamente ligada
	struct website *next;
	struct website *previous;

} WEBSITE;

#endif