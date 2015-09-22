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

// ORDENAÇÃO POR RANKING
boolean mergeSort(DATABASE *data);
boolean insertionSort(DATABASE *data);
// BUSCA
boolean binarySearch(DATABASE data); 

#endif