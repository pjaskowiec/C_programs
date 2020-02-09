#ifndef _FIFO_H
#define _FIFO_H
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct tagFifoItem 
{
	int nKey;
	tagFifoItem* next;
}FIFOstruct;


typedef struct queue
{
	FIFOstruct* Head;
	FIFOstruct* Tail;
}queue;

queue* Creator();
void Enqueue( queue* QADD, int elem );
int IsEmpty( queue* toCheck );
FIFOstruct* Dequeue( queue* QDEL );
//int Dequeue( queue* QDEL );
void Remover( queue* toRemove );
void Cleaner( queue* toClean );
void ByteEater( queue** toEat );

#endif