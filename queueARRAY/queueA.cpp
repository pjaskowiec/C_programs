#include "pch.h"
#include "queueA.h"

Queue* Creator( int Size_2 )
{
	Queue* tmpQUE = (Queue*)calloc( 1, sizeof( Queue ) );
	if( !tmpQUE )
	{
		perror( "Memory allocation error-queue Creation!" );
		return NULL;
	}
	tmpQUE->tab = (GLOBALINT**)calloc( Size_2, sizeof( GLOBALINT* ) );
	if( !( tmpQUE->tab ) )
	{
		free( tmpQUE );
		perror( "Memory allocation error-queue Creation-Array!" );
		return NULL;
	}
	tmpQUE->nSize = Size_2;
	return tmpQUE;
}

void Enqueue( Queue* QADD, GLOBALINT* QKEY )
{
	if( QADD->quantity == QADD->nSize )
	{
		perror( "No place to add new element!" );
		return;
	}
	QADD->tab[ QADD->tail ] = QKEY;
	QADD->tail = ( QADD->tail + 1 ) % QADD->nSize; //dzieki temu zachowujemy cyklicznoœæ kolejki!!!
	QADD->quantity++;
}

int IsEmpty( Queue* toCheck )
{
	return ( toCheck->quantity ) ? 0 : 1;
}

GLOBALINT* Dequeue( Queue* QDEL )
{
	if( IsEmpty( QDEL ) )
	{
		perror( "No element to remove!" );
		return NULL;
	}
	GLOBALINT* toRemove = QDEL->tab[QDEL->head]; //trzymamy wartosc usuwana
	QDEL->tab[ QDEL->head ] = NULL; //zerujemy przod
	QDEL->head = ( QDEL->head + 1 ) % QDEL->nSize; //nastepny element bedzie teraz na czubie,a kolejka cykliczne przesuwa sie w prawo
	QDEL->quantity--; //ilosc elementow w kolejce zmniejsza sie o jeden
	return toRemove; //zwracamy usuniety klucz
}

void Cleaner( Queue* toClean )
{
	if( !IsEmpty( toClean ) )
	{
		for( int i = 0; i < toClean->nSize; i++ )
		{
			if( toClean->tab[ i ] ) free( toClean->tab[ i ] );
		}
	}
	toClean->quantity = 0;
	toClean->head = 0;
	toClean->tail = 0;
	memset( toClean->tab, 0, sizeof( Queue ) );
}

void ByteEater( Queue** toEat )
{
	Cleaner( *toEat );
	free( *toEat );
	*toEat = NULL;
}
