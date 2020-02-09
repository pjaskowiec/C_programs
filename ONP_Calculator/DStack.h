#ifndef DSTACK_H
#define DSTACK_H

#include <stdlib.h>
#include <iostream>

typedef struct tagDStackItem {

	double fKey;
	tagDStackItem* pNext;

} DStackItem;

void dmakeEmptyStack(DStackItem** pStack);
void dpush(DStackItem** pStack, double x);
double dpop(DStackItem** pStack);
double dtop(DStackItem* pStack);
void ddel(DStackItem** pStack);
int isDEmpty(DStackItem* pStack);

#endif