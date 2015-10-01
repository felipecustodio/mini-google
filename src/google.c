#include "globals.h"
#include "google.h"
#include "website.h"
#include "input.h"

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

void updateRank(WEBSITE *site, int newRank)
{
	site->rank = newRank;

}


// *********************** FUNÇÕES ABAIXO PRECISAM SER TESTADAS ***************************
//***************************
//***************************
//***************************
//***************************
//***************************


/*-------------------------------------------------------

	nome_da_funcao

		DESCRIÇÃO:

		
		PARÂMETROS:
			
---------------------------------------------------------*/

void printList(DATABASE *data) 
{

	WEBSITE *aux = NULL;
	aux = data->header->next;
	while (aux != data->header) {
		// print website
	}

}

/*-------------------------------------------------------
	FUNÇÕES DE BUSCA POR PALAVRA-CHAVE E 
	EXIBIÇÃO DE SITES RELACIONADOS
---------------------------------------------------------*/

/*-------------------------------------------------------

	nome_da_funcao

		DESCRIÇÃO:

		
		PARÂMETROS:
			
---------------------------------------------------------*/

SEARCH* searchKeyword(DATABASE *database, char *keyword)
{
    // começar a busca no header com nó sentinela
    SEARCH *search;
    search = (SEARCH*)malloc(sizeof(SEARCH));
    search->total = 0;
    search->results = NULL;
    
    WEBSITE *aux = database->header->next;
    int i, j, compare;
    
    while(aux != database->header)
    {
        // percorrer keywords do website atual
        for (j = 0; j < aux->keywords->total; j++) {
            
            compare = strcmp(aux->keywords->keywords[j], keyword);
            
            if (compare == 0) {
                // TAD search: contém endereços para os sites encontrados na busca
                search->results = (WEBSITE**)realloc(search->results, sizeof(WEBSITE*) * (search->total + 1));
                search->results[search->total] = aux;
                search->total++;
            }
            
        }
        
        aux = aux->next;
        
    }
    
    return search;
    
}

/*-------------------------------------------------------

	nome_da_funcao

		DESCRIÇÃO:

		
		PARÂMETROS:
			
---------------------------------------------------------*/

void relatedWebsites(DATABASE* database, SEARCH* search, char *keyword)
{
    KEYWORDS* keylist = (KEYWORDS*) malloc(sizeof(KEYWORDS));
    keylist->keywords	= (char**) malloc(sizeof(char*) * search->total);
    
    int i;
    for(i = 0; i < search->total; i++)
    {
        //pegando uma palavra por site para buscar relacionados
        if (strcmp(keyword, search->results[i]->keywords->keywords[i]))
            keylist->keywords[i] = search->results[i]->keywords->keywords[i];
        else
        {
            if (i > 0)
            {
                keylist->keywords[i] = search->results[i]->keywords->keywords[i-1];
            }
            else
            {
                keylist->keywords[i] = search->results[i]->keywords->keywords[i+1];
            }
        }
        
    }
    
    WEBSITE* aux = database->header->next;
    
    int j;
    while(aux != database->header)
    {
        for(i = 0; i < keylist->total; i++)
        {
            for(j = 0; j < aux->keywords->total; j++)
            {
                if(strcmp(keylist->keywords[i], aux->keywords->keywords[j]))
                {
                    aux->related = true;
                }
            }
        }
        
        aux = aux->next;
    }
    
    for(i = 0; i < search->total; i++)
    {
        search->results[i]->related = false;
    }
    
    free(keylist->keywords);
    free(keylist);
}

/*-------------------------------------------------------

	nome_da_funcao

		DESCRIÇÃO:

		
		PARÂMETROS:
			
---------------------------------------------------------*/

boolean emptyList(DATABASE *database) {

	if(database->header->next == database->header) {
		return true;
	} else {
		return false;
	}
}



/*-------------------------------------------------------

	writeCSVFile

		DESCRIÇÃO:

		
		PARÂMETROS:
			
---------------------------------------------------------*/

void writeCSVFile(DATABASE* database, const char* filename)
{
    FILE* csv_file = fopen(filename, "w");
    if (csv_file == NULL)
    {
        printf("Could not open the file: %s\n", filename);
        exit(0);
    }
    
    WEBSITE* aux = database->header->next;
    int i;
    
    while(aux != database->header)
    {
        fprintf(csv_file, "%d,%s,%d,%s,", aux->id, aux->name, aux->rank, aux->address);
        for(i = 0; i < aux->keywords->total-1; i++)
        {
            fprintf(csv_file, "%s", aux->keywords->keywords[i]);
            fprintf(csv_file, ",");
        }
        
        fprintf(csv_file, "%s", aux->keywords->keywords[i]);
        fprintf(csv_file, "\n");
        
        aux = aux->next;
    }
    
    fclose(csv_file);
}

WEBSITE* searchID(DATABASE* database, const int id)
{
	WEBSITE* aux = database->header->next;

	while (aux != database->header)
	{
		if (aux->id == id)
		{
			return aux;
		}
		aux = aux->next;
	}

	aux = NULL;
	return aux;
}