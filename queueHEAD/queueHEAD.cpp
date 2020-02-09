#include "pch.h"
#include "queueH.h"
#include <iostream>
#define _DEBUG_


int main( int argc, char* argv[] )
{
	if( argc != 2 ) 
    {
		perror( "Illegal arguments number!" );
		return 1;
	}
	int nSize = atoi( argv[ 1 ] );
	srand( (unsigned int)time( NULL ) );

	queue* mainQUE = Creator();
	for( int i = 0; i <= nSize; i++ )
	{
		int toADD = rand() % 10;
		printf( "%d ", toADD );
		Enqueue( mainQUE, toADD );
	}
	printf( "\n" );
	FIFOstruct* missedKey = Dequeue( mainQUE );
#ifdef _DEBUG_
	printf( "Head element after remove: %d\n", mainQUE->Head->next->nKey );
	printf( "Removed element: %d", missedKey->nKey );
#endif
	ByteEater( &mainQUE );
#ifdef _DEBUG_
	printf( "\n" );
	if( !mainQUE ) printf( "The queue is successfully remvoed!" );
#endif
	return 0;
}
