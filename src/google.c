/*-------------------------------------------------------
	FUNÇÕES DE MANIPULAÇÃO 
	DA LISTA DINÂMICA CIRCULAR COM CABEÇALHO
---------------------------------------------------------*/

#include "google.h"

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

		WEBSITE *aux = removal;
		removal->previous->next = removal->next;
		removal->next->previous = removal->previous;	

		// ****** LIBERAR MEMÓRIA DO NÓ ********
		free(removal);
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
	printf("\tINSIRA O NOVO RANK DE %s: ", site->name);
	scanf("%d", &newRank);
	site->rank = newRank;
	printf("\tRANK ATUALIZADO COM SUCESSO\n");
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
    keylist->total = 0;
    
    int i;
    for(i = 0; i < search->total; i++)
    {
        //pegando uma palavra por site para buscar relacionados
        if (strcmp(keyword, search->results[i]->keywords->keywords[0]))
            keylist->keywords[i] = search->results[i]->keywords->keywords[i];
        else
        {

            keylist->keywords[i] = search->results[i]->keywords->keywords[1];
                     
        }
        keylist->total++;
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
}

/*-------------------------------------------------------

	writeCSVFile

		DESCRIÇÃO:
			Reescreve o arquivo CSV com a lista
			de sites atualizada.
		
		PARÂMETROS:
			@ DATABASE* database: lista a ser escrita no arquivo
			@ const char* filename: nome do arquivo
			
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

/*-------------------------------------------------------

	searchID

		DESCRIÇÃO:
			Busca um website por ID, retornando
			um ponteiro para seu nó na lista.
		
		PARÂMETROS:
			@ DATABASE *database: lista a ser buscada
			@ const int id: id procurado
			
---------------------------------------------------------*/

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

/*-------------------------------------------------------

	readKeywords(FILE *googlebot)

		DESCRIÇÃO:

		Lê as palavras chaves do website atual no arquivo.
		Como o programa é feito em C, existem vários casos
		para serem tratados durante a leitura, pois o número
		de keywords por website é variável e a leitura deve
		ser feita até uma vírgula ou quebra de linha. 

		PARÂMETROS:

			@ FILE *googlebot: 
			FILE STREAM do arquivo aberto, googlebot.csv

---------------------------------------------------------*/

KEYWORDS* readKeywords(FILE *googlebot) {

	// lista de keywords auxiliar para leitura
	KEYWORDS *keylist = (KEYWORDS*)malloc(sizeof(KEYWORDS));
	keylist->keywords = NULL;
	keylist->total = 0;

	// string auxiliar que irá armazenar as keywords e caracteres
	// de separação, para depois ser quebrada em keywords
	char *keywords = NULL; 

	// token de separação de strings (strtok)
	char *token = NULL;
	char value;

	// contadores auxiliares
	int counter = 0;
	int byteCounter = 0;
	int tokenCounter = 0;

	do
	{

		value = fgetc(googlebot);
		byteCounter++;

		keywords = (char*)realloc(keywords, sizeof(char) * counter + 1);
		// inserir todos os caracteres até a quebra de linha
		if(value != ENTER) {
			keywords[counter] = value;
			counter++;
		}

	} while (value != ENTER);

	// iniciar quebra de keywords em 'tokens'
	token = strtok(keywords, ",");

	// armazenar na lista de keywords auxiliar
	keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (tokenCounter + 1));
	keylist->keywords[tokenCounter] = (char*)malloc(sizeof(char) * (strlen(token)));
	strcpy(keylist->keywords[tokenCounter], token);

	tokenCounter++;

	// encontrar e armazenar os próximos tokens
	while (token != NULL) 
	{

		token = strtok(NULL, ",");

		if (token != NULL) {

			keylist->keywords = (char**)realloc(keylist->keywords, sizeof(char*) * (tokenCounter + 1));
			keylist->keywords[tokenCounter] = (char*)malloc(sizeof(char) * (strlen(token)));
			strcpy(keylist->keywords[tokenCounter], token);

			tokenCounter++;
		}

	}

	keylist->total = tokenCounter;
	return keylist;

}

/*-------------------------------------------------------

	readData(char* filename, DATABASE **data)

		DESCRIÇÃO:
			Realiza a leitura do arquivo (filename), escrevendo
			em um DATABASE já existente na main. 

		PARÂMETROS:
			
			@char *filename: nome do arquivo a ser lido
			@DATABASE **data: endereço do ponteiro de lista *data

---------------------------------------------------------*/

void readData(char* filename, DATABASE **data) {
	
	// printHeader();

	// WEBSITE *aux = NULL;

	int counter = 0;

	FILE *googlebot = fopen(filename, "r");

	long int contaBytes = 0;
	long int totalBytes = 0;
	char buffer;
	int i, j;
	fseek(googlebot, 0L, SEEK_END);
	totalBytes = ftell(googlebot);
	rewind(googlebot);

	if(googlebot == NULL) {
		printf("O arquivo CSV não pôde ser aberto. Saindo...\n");
		exit(0);
	}

	do {

		WEBSITE *aux = NULL;

		if (aux == NULL) {
			aux = (WEBSITE*)malloc(sizeof(WEBSITE));

		}	

		fscanf(googlebot, "%d", &(aux->id));
		buffer = fgetc(googlebot);

		aux->name = readString(googlebot, 1);

		fscanf(googlebot, "%d", &(aux->rank));
		buffer = fgetc(googlebot);

		aux->address = readString(googlebot, 1);
		(aux->keywords) = readKeywords(googlebot);

		insertWebsite((*data), aux);

		contaBytes = ftell(googlebot);

	} while((!feof(googlebot)) && (contaBytes < totalBytes - 1));

	fclose(googlebot);

}

void printWebsite(WEBSITE *print) {

	int i;
	printf("\t");
	printf("ID: %d ", print->id);
	printf("NOME: %s ", print->name);
	printf("RANK: %d ", print->rank);
	printf("URL: %s ", print->address);
	printf("PALAVRAS-CHAVE: ");
	for (i = 0; i < print->keywords->total; i++) {	
		printf("%s ", print->keywords->keywords[i]);
	}
	printf("\n");

}

void printList(DATABASE *data) {

	WEBSITE *aux = NULL;
	aux = data->header->next;
	while (aux != data->header) {
		printWebsite(aux);
		aux = aux->next;
	}
}

void printSearch(SEARCH *search, DATABASE *data) {

	int i;
	printf("\tRESULTADO DA BUSCA:\n");
	for (i = 0; i < search->total; i++) {
		printWebsite(search->results[i]);
		search->results[i]->related = false;
	}
	printf("\n\n");
	printf("\tSITES RELACIONADOS:\n");
	WEBSITE *aux = NULL;
	aux = data->header->next;
	while (aux != data->header) {
		if(aux->related) {
			printWebsite(aux);
		}
		aux = aux->next;
	}



}

void destroyDataBase(DATABASE* data)
{
	WEBSITE* aux = data->header->next;

	int i;
	while (aux != data->header)
	{
		for(i = 0; i < aux->keywords->total; i++)
		{
			free(aux->keywords->keywords[i]);
		}
		free(aux->name);
		free(aux->keywords);
		free(aux);
		aux = aux->next; 
	} 

	free(aux);
	free(data);
}

void destroySearch(SEARCH* search)
{
	int i;
	for (i = 0; i < search->total; i++)
	{
		free(search->results[i]);
	}
}