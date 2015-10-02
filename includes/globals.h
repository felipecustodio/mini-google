#ifndef __GLOBALS_H__
#define __GLOBALS_H__

/*-------------------------------------------------------

	GLOBALS
		Contém bibliotecas, funções e definições globais,
		usadas em todos os headers e arquivos.
			
---------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "google.h"
#include "website.h"
#include "input.h"
#include "globals.h"
#include "menu.h"

/*-------------------------------------------------------
	TIPO BOOLEANO (Não existe como padrão na linguagem C)
		FALSE 	= 0
		TRUE 	= 1
---------------------------------------------------------*/

typedef enum {
	false, true
} boolean;

/*-------------------------------------------------------
	CARACTERES ESPECIAIS (ASCII)
		Auxiliar na leitura de arquivo e dados
---------------------------------------------------------*/

#define COMMA 42
#define ENTER 10
		
#endif