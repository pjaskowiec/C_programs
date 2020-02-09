#include "pch.h"
#include "queueWH.h"

queue* Creator()
{
	queue* tmpQUE = (queue*)calloc( 1, sizeof( queue ) );
	if( !tmpQUE )
	{
		perror( "Memory allocation error-queue Creation!" );
		return NULL;
	}
	//tmpQUE->Head = tmpQUE->Tail = NULL;   bo calloc
	return tmpQUE;
}

int IsEmpty( queue* toCheck )
{
	return !( toCheck->Head );
}

void Enqueue( queue* QADD, int elem )
{
	FIFOstruct* tmpADD = (FIFOstruct*)calloc( 1, sizeof( FIFOstruct ) );
	if( !tmpADD )
	{
		perror( "Memory allocation error-Enqueue!" );
		return;
	}
	tmpADD->nKey = elem;
	if( IsEmpty( QADD ) )  QADD->Head = tmpADD; //na poczatek musimy ruszyc heada,pozniej bedzie polaczony z tailem,ktory bedzie polaczony z kolejnym...
	else QADD->Tail->next = tmpADD; //QADD->Tail->next obszar pamiec,na ktory wskazuje head,potem tail,który wksazuje na nastepnego potencjalnego taila,itd.
	QADD->Tail = tmpADD; //aktualizacja ogona
	printf( "%d ", QADD->Tail->nKey );
}

void Remover( queue* toRemove )
{
	//head musi wskazywac na element nastepny,po tym na ktory wszesniej wskazywalo
	FIFOstruct* tmpRemove = toRemove->Head;
	toRemove->Head = tmpRemove->next;
	//free( tmpRemove ); //zwalniamy pamiec dla niepotrzebneogo elementu
	//przypadek,gdyby kolejka by³a jednoelementowa
	if( IsEmpty( toRemove ) ) toRemove->Tail = NULL; //teraz i head i tail wskazuja na nulla
}


FIFOstruct* Dequeue( queue* QDEL )
{
	if( IsEmpty( QDEL ) )
	{
		perror( "Nothing to remove!" );
		return 0;
	}
	//gdyby by³o na inty,to:
	//int RemovedElement=QDEL->Head->nKey;
	FIFOstruct* RemovedElement = QDEL->Head;
	//if( !RemovedElement )
	//{
	///	perror( "Memory allocation error-RemovedElement!" );
	////	return NULL;
	//}
	//memcpy(RemovedElement, QDEL->Head, sizeof(FIFOstruct));
	Remover( QDEL );
	return RemovedElement;
}

void Cleaner( queue* toClean )
{
	while( !IsEmpty( toClean ) )
		free( Dequeue( toClean ) );
	//Dequeue( toClean )
}

void ByteEater( queue** toEat ) 
{
	Cleaner( *toEat );
	free( *toEat );
	*toEat = NULL;
}

