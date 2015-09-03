/*-------------------------------------------------------

	HEADER AUXILIAR  (NOME A SER MUDADO)
		Contém funções para manipulação de:
			@ Strings
			@ Arquivos (googlebot.csv)
			@ Menu principal 
			@ Impressão de dados
	
---------------------------------------------------------*/

#include "auxiliar.h"

/*-------------------------------------------------------

	ARQUIVOS
	
---------------------------------------------------------*/

void readCSV();

/*-------------------------------------------------------

	IMPRESSÃO DE DADOS
	
---------------------------------------------------------*/

void printDatabase(WEBSITE *first) {

   WEBSITE *i;
   for (i = first->next; i != NULL; i = i->prox) {
      // printWebsite(i);
   	
   }
}

void printWebsite(WEBSITE *i);

/*-------------------------------------------------------

	STRINGS
	
---------------------------------------------------------*/

char* readString() 
{	
	char* string = NULL;
	char value = '@';
	int counter = 0;

	while (value != ENTER) 
	{
		scanf("%c", &value);
		string = (char*)realloc(string, sizeof(char) * counter + 1);
		
		string[counter] = value;		
		counter++;

	}

	string[counter-1] = '\0';

	return string;
}

/*-------------------------------------------------------

	MENU
	
---------------------------------------------------------*/

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