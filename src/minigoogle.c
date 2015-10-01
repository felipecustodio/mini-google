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

#include "globals.h"

typedef enum operation
{
	insertWebSite = 1,
	removeWebSite,
	insertKeyWord,
	updateRank,
	showList,
	searchByKey,
	shutdown

} Operation;

int main(int argc, char const *argv[]) {
 	
 	int aux;
 	Operation operation;

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
				printf("\n\n\tOPCAO 1\n\n");
				break;
			
			case removeWebSite:
				// Inserir palavra-chave em um site
				printHeader();
				printf("\n\n\tOPCAO 2\n\n");
				break;
			
			case insertKeyWord:
				// Remover um site da lista
				printHeader();
				printf("\n\n\tOPCAO 3\n\n");
				break;
			
			case updateRank:
				// Atualizar relevância de um site
				printHeader();
				printf("\n\n\tOPCAO 4\n\n");
				break;
			
			case showList:
				// Exibir lista
				printHeader();
				printf("\n\n\tOPCAO 5\n\n");
				break;

			case searchByKey:
				// Busca por palavra-chave
				// Exibir sugestão de sites
				printHeader();
				printf("\n\n\tOPCAO 6\n\n");
				break;

			case shutdown:
				// Liberar memória
				// Finalizar o programa
				printHeader();
				printf("\n\n\tOPCAO 7\n\n");
				break;
		}

		printf("\tPRESSIONE QUALQUER TECLA PARA CONTINUAR");
		getchar();

	} while(operation != shutdown);

	return 0;
}


/*-------------------------------------------------------

	COMENTÁRIO
	
---------------------------------------------------------*/