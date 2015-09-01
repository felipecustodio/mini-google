/* 
* @Author: felipecustodio
* @Date:   2015-09-01 06:01:44
* @Last Modified by:   felipecustodio
* @Last Modified time: 2015-09-01 10:57:45
*/

#include <stdio.h>
#include <stdlib.h>
#include "google.h"


/*-------------------------------------------------------

	DEFINIÇÕES
	
---------------------------------------------------------*/

#define TAM_MAX 100
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

// PSEUDOCODE - LER ARQUIVO CSV
// EXEMPLO: LENDO 1 WEBSITE

void readCSV() {
	WEBSITE website; // SERÁ LISTA
	FILE *bot = NULL;
	char *value;
	bot = fopen("googlebot.csv", "r");
	while(!feof(bot)) {

	}
}

/*-------------------------------------------------------

	FUNÇÕES DE MANIPULAÇÃO DA LISTA
	
---------------------------------------------------------*/


