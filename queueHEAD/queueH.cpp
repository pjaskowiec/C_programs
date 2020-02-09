#include "pch.h"
#include "queueH.h"

queue* Creator()
{
	queue* tmpQUE = (queue*)calloc( 1, sizeof( queue ) );
	FIFOstruct* Sentinel = (FIFOstruct*)calloc( 1, sizeof( FIFOstruct ) );
	if( !tmpQUE || !Sentinel )
	{
		perror( "Memory allocation error-queue Creation!" );
		return NULL;
	}
	tmpQUE->Head = tmpQUE->Tail = Sentinel; //dzieki wartownikowi nie musimy sie martwic o NULL'owego head'a i tail'a
	return tmpQUE;
}

int IsEmpty( queue* toCheck )
{
	return !( toCheck->Head->next ) ;
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
	QADD->Tail->next = tmpADD; //juz nie musimy sie martwic o head'a,bo mamy wartownika 
	QADD->Tail = tmpADD; 
	//printf( "%d ", QADD->Tail->nKey );
}

void Remover( queue* toRemove )
{
	//teraz musiemy uwzglednic naszego wartownika na poczatku i na koncu,a wiêc:
	FIFOstruct* tmpRemove = toRemove->Head->next; //po prostu przechodzimy deko dalej
	toRemove->Head->next = tmpRemove->next;
	//free( tmpRemove ); //zwalniamy pamiec dla niepotrzebneogo elementu
	//przypadek,gdyby kolejka by³a jednoelementowa
	if( IsEmpty( toRemove ) ) toRemove->Tail = toRemove->Head; //w przypadku usuniecia ostatniego elementu zostana tylko zajmujace ten sam obszar pamiec wartowniki
}


FIFOstruct* Dequeue( queue* QDEL )
{
	if( IsEmpty( QDEL ) )
	{
		perror( "Nothing to remove!" );
		return 0;
	}
	//int RemovedElement=QDEL->Head->next->nKey;
	FIFOstruct* RemovedElement = QDEL->Head->next;
	/*if( !RemovedElement )
	{
		perror( "Memory allocation error-RemovedElement!" );
		return NULL;
	}
	memcpy( RemovedElement, QDEL->Head->next, sizeof( FIFOstruct ) );*/
	Remover( QDEL );
	return RemovedElement;
}

void Cleaner( queue* toClean )
{
	while( !IsEmpty( toClean ) ) free( Dequeue( toClean ) );
}

void ByteEater( queue** toEat )
{
	Cleaner( *toEat );
	free( ( *toEat )->Head );
	free( *toEat );
	*toEat = NULL;
}