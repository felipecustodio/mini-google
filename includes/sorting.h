#ifndef __SORTING_H__
#define __SORTING_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "google.h"
#include "website.h"
#include "sorting.h"

/*-------------------------------------------------------

	ORDENAÇÃO E BUSCA
	
---------------------------------------------------------*/
// ORDENAÇÃO
// Duas opções: Retornar o DATABASE ou passar ele como endereço e não retornar nada
DATABASE mergeSort(DATABASE data); 		// Merge Sort -> Ordenação com lista totalmente aleatória
DATABASE insertionSort(DATABASE data); 	// Insertion Sort -> Ordenação com lista 
										// quase ordenada (após inserir elemento ou remover)
// BUSCA
DATABASE binarySearch(DATABASE data); 

#endif