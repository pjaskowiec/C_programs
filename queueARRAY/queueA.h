#ifndef _FIFO_H
#define _FIFO_H

#include "Global.h"
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct tagQueueItem
{
	GLOBALINT** tab;
	int head; 
	int tail; 
	int quantity;
	int nSize;
} Queue;
  
Queue* Creator( int Size_2 );
void Enqueue( Queue* QADD, GLOBALINT* QKEY );
int IsEmpty( Queue* toCheck );
GLOBALINT* Dequeue( Queue* QDEL );
void Cleaner( Queue* toClean );
void ByteEater( Queue** toEat );


#endif 
