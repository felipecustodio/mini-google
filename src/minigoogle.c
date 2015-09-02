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

#include "google.h"
#include "auxiliar.h"

int main(int argc, char const *argv[]) {
 	
 	int operation;

 
	do
	{
		printMainMenu();
		scanf("%d", &operation);
		getchar();

		system("clear");

		switch(operation) {
			case 1:
				// Inserir novo site
				printHeader();
				printf("\n\n\tOPCAO 1\n\n");
				break;
			
			case 2:
				// Inserir palavra-chave em um site
				printHeader();
				printf("\n\n\tOPCAO 2\n\n");
				break;
			
			case 3:
				// Remover um site da lista
				printHeader();
				printf("\n\n\tOPCAO 3\n\n");
				break;
			
			case 4:
				// Atualizar relevância de um site
				printHeader();
				printf("\n\n\tOPCAO 4\n\n");
				break;
			
			case 5:
				// Exibir lista
				printHeader();
				printf("\n\n\tOPCAO 5\n\n");
				break;

			case 6:
				// Busca por palavra-chave
				// Exibir sugestão de sites
				printHeader();
				printf("\n\n\tOPCAO 6\n\n");
				break;

			case 7:
				// Liberar memória
				// Finalizar o programa
				printHeader();
				printf("\n\n\tOPCAO 7\n\n");
				break;
		}

		printf("\tPRECIONE QUALQUER TECLA PARA CONTINUAR");
		getchar();

	} while(operation != 7);

	return 0;
}


/*-------------------------------------------------------

	COMENTÁRIO
	
---------------------------------------------------------*/