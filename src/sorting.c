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

DATABASE mergeSort(DATABASE data) {

} 	

DATABASE insertionSort(DATABASE data) {

}

DATABASE binarySearch(DATABASE data) {

}

// MERGE SORT -> AULA DO MOACIR:

/*void mergesort(int *v, int ini, int fim) {

	if (fim-ini >= 1) {
		int cen = (int)( (fim+ini)/2.0 );
		// divisao
		mergesort(v, ini, cen);
		mergesort(v, cen+1, fim);

		// conquista
		intercala(v, ini, cen, fim);
	}

}

void intercala(int *v, int ini, int cen, int fim) {

	int i, j, k = 0;
	// i -> indice posicionado no menor elemento da lista 1 (ordenada)
	// j -> indice posicionado no menor elemento da lista 2 (ordenada)
	// k -> indice do proximo elemento a ser intercalado

	i = ini;
	j = cen+1;

	// aloca vetor auxiliar
	int *aux = (int *) malloc(sizeof(int) * (fim-ini+1));	

	// intercalacao
	while ( (i <= cen) && (j <= fim) ) {
		if (v[i] <= v[j]) {
			aux[k] = v[i];
			i++;
		} else {
			aux[k] = v[j];
			j++;
		}
		k++;
	}

	// verificar se ha elementos sobrando em alguma das listas
	// lista 1
	while (i <= cen) {
		aux[k] = v[i];
		i++; k++;
	}
	// lista 2
	while (j <= fim) {
		aux[k] = v[j];
		j++; k++;
	}

	for (i = ini; i <= fim; i++) {
		v[i] = aux[i-ini];
	}

	free(aux);
}*/