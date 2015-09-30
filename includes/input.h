#ifndef __INPUT_H__
#define __INPUT_H__

#include "globals.h"
#include "google.h"

char* readString(FILE *pointer);
void readData(char* filename, DATABASE **data);
KEYWORDS* readKeywords(FILE *googlebot);

#endif