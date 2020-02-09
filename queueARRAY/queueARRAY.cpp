#include "pch.h"
#include "queueA.h"
#include <iostream>
#define _DEBUG

int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		perror( "Illegal arguments number!" );
		return 1;
	}
	int Size = atoi( argv[ 1 ] );
	srand( (unsigned int)time( NULL ) );
	Queue* mainQUE = Creator( Size );
#ifdef _DEBUG
	printf( "The queue is filled with following numbers:\n" );
#endif
	for(int i=0;i<Size;i++ )
	{
		GLOBALINT* keyQUE = (GLOBALINT*)calloc( 1, sizeof( GLOBALINT ) );
		if( !keyQUE )
		{
			perror( "Memory allocation error-queue Creation-KEY!" );
			return 2;
		}
		keyQUE->nKey = rand() % 15;
#ifdef _DEBUG
		printf( "%d ", keyQUE->nKey );
#endif
		Enqueue( mainQUE, keyQUE );
	}
	GLOBALINT* missedKey = Dequeue( mainQUE );
#ifdef _DEBUG
	printf( "\nRemoved element is: %d ", missedKey->nKey );
#endif

#ifdef _DEBUG 
	printf( "\nCleaning..." );
#endif
	ByteEater( &mainQUE );
#ifdef _DEBUG
	if( !mainQUE ) printf( "\n%s", "Correct cleaning!" );
	else printf( "\n%s", "Uncorrect cleaning!" );
#endif
	return 0;
}

