/*-------------------------------------------------------

	TAD WEBSITE
	
---------------------------------------------------------*/

typedef struct keywords {

	char **keywords;
	int total;
	
} KEYWORDS;

typedef struct website {

	int id;
	char name[50];
	int rank;
	char link[100];
	KEYWORDS list;
	struct website *next;

} WEBSITE;