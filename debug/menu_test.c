/* 
* @Author: felipecustodio
* @Date:   2015-09-30 10:49:26
* @Last Modified by:   felipecustodio
* @Last Modified time: 2015-09-30 10:50:47
*/

#include <stdio.h>
#include <stdlib.h>

void printHeader(void)
{
	printf("\t  __  __ _       _    _____                   _       \n");
	printf("\t |  \\/  (_)     (_)  / ____|                 | |      \n");
	printf("\t | \\  / |_ _ __  _  | |  __  ___   ___   __ _| | ___  \n");
	printf("\t | |\\/| | | '_ \\| | | | |_ |/ _ \\ / _ \\ / _` | |/ _ \\ \n");
	printf("\t | |  | | | | | | | | |__| | (_) | (_) | (_| | |  __/ \n");
	printf("\t |_|  |_|_|_| |_|_|  \\_____|\\___/ \\___/ \\__, |_|\\___| \n");
	printf("\t                                         __/ |        \n");
	printf("\t                                        |___/         \n");
}

void printMenu(void)
{
	printf("\t------------------------------------------------------\n");
	printf("\t1 - Inserir novo site\n");
	printf("\t2 - Inserir palavra chave em um site\n");
	printf("\t3 - Remover um site da lista\n");
	printf("\t4 - Atualizar relevancia de um site\n");
	printf("\t5 - Exibir lista\n");
	printf("\t6 - Buscar por palavra chave e exibir sugestao de sites\n");
	printf("\t7 - Liberar memoria e finalizar o programa\n");
	printf("\t------------------------------------------------------\n");
	printf("\n\t>> Digite uma opcao (1 - 7): ");
}

void printMainMenu(void)
{
	system("clear");
	printHeader();
	printMenu();
}

typedef enum operation
{
	insertWebSite = 1,
	removeWebSite,
	insertKeyWord,
	refresh,
	showList,
	searchByKey,
	close

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
			
			case refresh:
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

			case close:
				// Liberar memória
				// Finalizar o programa
				printHeader();
				printf("\n\n\tOPCAO 7\n\n");
				break;
		}

		printf("\tPRESSIONE QUALQUER TECLA PARA CONTINUAR");
		getchar();

	} while(operation != close);

	return 0;
}