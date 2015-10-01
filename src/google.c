#include "globals.h"
#include "google.h"
#include "website.h"

/*-------------------------------------------------------
	FUNÇÕES DE MANIPULAÇÃO 
	DA LISTA DINÂMICA CIRCULAR COM CABEÇALHO
---------------------------------------------------------*/

/*-------------------------------------------------------

	createDatabase(DATABASE **database)

		DESCRIÇÃO:
		
			Aloca um DATABASE* na memória, setando
			o cabeçalho com ponteiros de próximo e
			anterior para ele mesmo.
		
		PARÂMETROS:
			
			@DATABASE **database: 
				Ponteiro para um DATABASE* na main.
			
---------------------------------------------------------*/

void createDatabase(DATABASE **database)
{
	(*database) = (DATABASE *) malloc(sizeof(DATABASE));

	if (database != NULL)
	{
		WEBSITE *sentinel = (WEBSITE *)malloc(sizeof(WEBSITE));
		sentinel->name = (char*)malloc(sizeof(char) * 100);
		sentinel->name = "header_sentinel";

		(*database)->header = sentinel;
		(*database)->header->next = sentinel;
		(*database)->header->previous = sentinel;
		(*database)->size = 0;

	}
}

/*-------------------------------------------------------

	insertWebsite(DATABASE *data, WEBSITE *node)

		DESCRIÇÃO:
		
			Insere um novo nó WEBSITE na lista circular
			DATABASE *data. Seta os ponteiros de anterior
			e próximo do header, do novo nó e do antigo nó
			final (anterior do header).
		
		PARÂMETROS:
			
			@DATABASE *data: 
				Lista dinâmica.
			@WEBSITE *node:
				Novo nó a ser inserido (previamente alocado)

---------------------------------------------------------*/

boolean insertWebsite(DATABASE *data, WEBSITE *node)
{
	if (node != NULL)
	{
		WEBSITE *aux = NULL;
		WEBSITE *end = (data)->header->previous;

		aux = end;
		aux->next = node;
		end = node;
		node->previous = aux;
		node->next = (data)->header;
		(data)->header->previous = node;
		(data)->size++;

		return true;
	}
	else
		return false;
}

/*-------------------------------------------------------

	insertKeyword

		DESCRIÇÃO:
			Insere uma nova keyword em um determinado website
		
		PARÂMETROS:
			@WEBSITE **site: 
				ponteiro para um WEBSITE* que será
				alterado
			@char *newKeyword: 
				nova keyword a ser inserida no website

---------------------------------------------------------*/

void insertKeyword(WEBSITE **site, char* newKeyword) 
{
	// Alocar mais uma string na lista de keywords
	(*site)->keywords->keywords = (char**)realloc(((*site)->keywords->keywords), sizeof(char*) * ((*site)->keywords->total + 1));
	(*site)->keywords->keywords[(*site)->keywords->total] = (char*)malloc(sizeof(char) * strlen(newKeyword));
	strcpy((*site)->keywords->keywords[(*site)->keywords->total], newKeyword);
	(*site)->keywords->total++;

}

/*-------------------------------------------------------

	removeWebsite

		DESCRIÇÃO:
			Remove um nó website do database
		
		PARÂMETROS:
			@ DATABASE **data: ponteiro para a lista dinâmica data
			@ WEBSITE *removal: nó a ser removido da lista
			
---------------------------------------------------------*/

boolean removeWebsite(DATABASE **data, WEBSITE *removal)
{

	if (removal != NULL) { 

		WEBSITE *aux = NULL;
		removal->previous->next = removal->next;
		removal->next->previous = removal->previous;	

		// ****** LIBERAR MEMÓRIA DO NÓ ********

		return true;
	} else {
		return false;
	}
}


/*-------------------------------------------------------

	updateRank

		DESCRIÇÃO:
			Atualiza o page rank de um website
		
		PARÂMETROS:
			WEBSITE *site: nó a ser modificado
			int newRank: novo page rank do website

---------------------------------------------------------*/

void updateRank(WEBSITE *site)
{
	int newRank = 0;
	printf("\tINSIRA O NOVO RANK DE %s:\n", site->name);
	scanf("%d", newRank);
	site->rank = newRank;
	printf("\tRANK ATUALIZADO COM SUCESSO\n");
	printf("\tPRESSIONE QUALQUER TECLA PARA CONTINUAR...\n");
	getchar();
}

/*-------------------------------------------------------
	
		newWebsite

			DESCRIÇÃO:
				O usuário insere os dados de um novo
				website que será colocado na lista pela
				insertWebsite (inserção ordenada)
	
			PARÂMETROS:
				@ DATABASE **data: 
					Endereço da lista em que o site será 
					inserido. 

---------------------------------------------------------*/

void newWebsite(DATABASE **data) {

	int i;
	int keytotal = 0;
	WEBSITE *new = NULL;
	new = (WEBSITE*)malloc(sizeof(WEBSITE));

	printf("\tINSIRA OS DADOS DO NOVO WEBSITE:\n");
	new->id = (*data)->header->previous->id + 1;

	printf("\tINSIRA O NOME: ");
	new->name = readString(stdin, 0);

	printf("\tINSIRA O RANK: ");
	scanf("%d", &new->rank);
	getchar();

	printf("\tINSIRA O ENDEREÇO: ");
	new->address = readString(stdin, 0);

	new->keywords = (KEYWORDS*)malloc(sizeof(KEYWORDS));
	printf("\tINSIRA O NÚMERO DE KEYWORDS: ");
	scanf("%d", &keytotal);

	new->keywords->total = keytotal;

	getchar();
	new->keywords->keywords = (char**)malloc(sizeof(char*) * new->keywords->total);

	printf("\tINSIRA AS KEYWORDS:\n");
	for (i = 0; i < new->keywords->total; i++) {
		printf("\tKEYWORD %d: ", i+1);
		new->keywords->keywords[i] = readString(stdin, 0);
	}

	new->related = false;
	new->next = NULL;
	new->previous = NULL;

	insertWebsite(*data, new);

}

/*-------------------------------------------------------

	emptyList	

		DESCRIÇÃO:
			Verifica se a lista possui nós.
		
		PARÂMETROS:
			DATABASE *database: lista a ser verificada
			
---------------------------------------------------------*/

boolean emptyList(DATABASE *database) {

	if(database->header->next == database->header) {
		return true;
	} else {
		return false;
	}
}/