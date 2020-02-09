#ifndef _WORDCOUNT
#define _WORDCOUNT

#include <iostream>
#include <memory.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queueWH.h"


#define MAXC 256


typedef struct tagTree {
	int n;
	char* toRead;
	queue* lines;
	tagTree* left;
	tagTree* right;
} Tree;

void TreeOrder( Tree* toSort );
int ReadData( Tree** TreeIn, const char* fName );
void TreeCleaner( Tree** toCleanTree );
void Printer( FIFOstruct* toPrint );

#endif