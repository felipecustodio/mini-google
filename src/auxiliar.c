#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "globals.h"
#include "auxiliar.h"

char* readString() {
	
	char* string = NULL;
	char value = '@';
	int counter = 0;

	while (value != ENTER) {

		scanf("%c", &value);
		string = (char*)realloc(string, sizeof(char) * counter + 1);
		
		string[counter] = value;		
		counter++;

	}

	string[counter-1] = '\0';

	return string;

}
