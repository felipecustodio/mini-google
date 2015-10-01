/*-------------------------------------------------------
ICMC - USP
BCC - 2015
SCC0202 - Algoritmos e Estruturas de Dados I

  __  __ _       _    _____                   _      
 |  \/  (_)     (_)  / ____|                 | |     
 | \  / |_ _ __  _  | |  __  ___   ___   __ _| | ___ 
 | |\/| | | '_ \| | | | |_ |/ _ \ / _ \ / _` | |/ _ \
 | |  | | | | | | | | |__| | (_) | (_) | (_| | |  __/
 |_|  |_|_|_| |_|_|  \_____|\___/ \___/ \__, |_|\___|
                                         __/ |       
                                        |___/        

Alunos	:	Felipe Scrochio Custodio
			Guilherme Rodrigues Vicentin

Nº USP	:	9442688
			9293369

Data:		01/09/2015
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

typedef enum operation
{
	insertWebSite = 1,
	removeWebSite,
	insertKeyWord,
	updatePagerank,
	showList,
	searchByKey,
	close

} Operation;

int main(int argc, char const *argv[]) {
 	
 	int aux;
 	Operation operation;

 	printHeader();
 	printf("\tINICIALIZANDO PROGRAMA...\n");
 	DATABASE *data = NULL;
 	createDatabase(&data);
 	printf("\tPRESSIONE QUALQUER TECLA PARA CONTINUAR...\n");
 	getchar();

	do
	{
		printMainMenu();
		scanf("%d", &aux);
		operation = aux;
		getchar();

		system("clear");

		switch(operation) {
			case insertWebSite:
				// Inserir novo site
				printHeader();
				newWebsite(&data);
				printf("\n\n\t*** NOVO WEBSITE ***\n\n");
				break;
			
			case removeWebSite:
				// Remover um site da lista
				printHeader();
				printf("\n\n\t*** REMOVER WEBSITE ***\n\n");
				break;
			
			case insertKeyWord:
				// Inserir palavra-chave em um site
				printHeader();
				printf("\n\n\t*** NOVA KEYWORD ***\n\n");
				break;
			
			case updatePagerank:
				// Atualizar relevância de um site
				printHeader();
				printf("\n\n\t*** ATUALIZAR RELEVÂNCIA ***\n\n");
				break;
			
			case showList:
				// Exibir lista
				printHeader();
				printf("\n\n\t*** EXIBIR LISTA ***\n\n");
				break;

			case searchByKey:
				// Busca por palavra-chave
				// Exibir sugestão de sites
				printHeader();
				printf("\n\n\t*** BUSCA ***\n\n");
				break;

			case close:
				// Liberar memória
				// Finalizar o programa
				printHeader();
				printf("\n\n\t*** FINALIZAR ***\n\n");
				break;
		}

		printf("\tPRESSIONE QUALQUER TECLA PARA CONTINUAR");
		getchar();

	} while(operation != close);

	return 0;
}


/*-------------------------------------------------------

	COMENTÁRIO
	
---------------------------------------------------------*/