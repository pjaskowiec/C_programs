#ifndef _PRIORQ
#define _PRIORQ

#include "Global.h"
#include <memory.h>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <iostream>


typedef struct tagPQElem
{
	PQGLOBAL* nElem;
	int nPrio;
}PQElem;

typedef struct tagPQueue
{
	PQElem** PQInter; //zaimplementujemy na tablicy,mozna tez(nawet latwiej na listach)
	int nSize;
	int cSize;
}PQueue;

PQueue* Creator(int Size);
void Enqueue( PQueue* TOADD, PQGLOBAL* nElem, int Prio ); 
void Update( PQueue* ToUp, int left, int right );
int PQisEmpty( PQueue* ToCheck );
PQElem* Dequeue( PQueue* TODEL );
void UpdateD( PQueue* ToDown, int left, int right );
void KeyDown( PQueue* KDown, int index, int nPrio );
void KeyUp( PQueue* KDown, int index, int nPrio );
void PQCleaner( PQueue* toClean );
void ByteEater( PQueue* toEat );
//void heapSort( PQueue* tab, int Size );
//void reverse( PQueue* arr, int n );
//void sifting( PQueue* tab, int l, int p );


#endif