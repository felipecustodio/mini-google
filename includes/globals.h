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

/*-------------------------------------------------------

	errorCheck

		DESCRIÇÃO:
			
			Checa se uma alocação de memória foi realizada
			com sucesso. Se não foi, não há memória suficiente,
			fechando o programa.
		
		PARÂMETROS:

			@void *pointer: ponteiro void (aceita qualquer ponteiro)
			@char *pointerName: nome do dado que foi alocado
			
---------------------------------------------------------*/

// void errorCheck(void *pointer, char *pointerName) {
// 	if (pointer == NULL) {
// 		printf("Não há memória suficiente para alocar %s. Saindo...\n", pointerName);
// 		exit(0);
// 	}
// }

/*-------------------------------------------------------

	shutdown

		DESCRIÇÃO:
		
			Encerra o minigoogle, liberando toda a 
			memória alocada.
	
---------------------------------------------------------*/

// void shutdown() 
// {
// 	// ******** LIMPAR TODA A MEMÓRIA DO PROGRAMA *********
// 	exit(0);
// }

#endif