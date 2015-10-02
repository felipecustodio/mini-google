#ifndef _WEBSITE_H_
#define _WEBSITE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "google.h"
#include "website.h"
#include "globals.h"
#include "menu.h"

/*-------------------------------------------------------

	TAD WEBSITE
		Cada website é um nó do banco de dados,
		configurando uma lista dinâmica circular
		duplamente ligada com cabeçalho.
		
---------------------------------------------------------*/

/*-------------------------------------------------------
	DEFINIÇÕES
---------------------------------------------------------*/

typedef struct keywords {

	// com um vetor de strings, fica mais fácil acessar
	// cada keyword de um website separadamente
	char **keywords;
	int total;
	
} KEYWORDS;

typedef struct website {
	// Propriedades de um website
	int id;
	char *name;
	int rank;
	char *address;
	KEYWORDS *keywords;
	// boolean auxiliar para busca de
	// sites com keywords relacionadas
	boolean related;
	// Lista duplamente ligada
	struct website *next;
	struct website *previous;

} WEBSITE;

typedef struct search {

	// Armazena os resultados de uma busca,
	// criando um vetor temporário de nós
	// do tipo website. 
	WEBSITE **results;
	int total;

} SEARCH;

#endif