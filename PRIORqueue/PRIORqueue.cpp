#include "pch.h"
#include "PRIORQ.h"
#define _DEBUG_

using namespace std;

void Printer( PQueue* ToPrint );

int main( int argc, char* argv[] )
{
	if( argc != 2 ) 
	{
		perror( "Illegal arguments number!" );
		return 1;
	}
	int MSize = atoi( argv[ 1 ] );
	PQueue* MainPQ = Creator( MSize );
	srand( (unsigned int)time( NULL ) );
	for( int i = 0; i < MSize; i++ ) 
	{
		PQGLOBAL* mainEl = (PQGLOBAL*)calloc( 1, sizeof( PQGLOBAL ) );
		mainEl->nKey = rand() % 10;
		Enqueue( MainPQ, mainEl, i );
	}

#ifdef _DEBUG_
	printf( "\nQueue after being filled\n" );
	Printer( MainPQ );

	Dequeue( MainPQ );
	printf( "Queue after removing element\n" );
	Printer( MainPQ );
	
	/*heapSort( MainPQ, MainPQ->cSize );
	Printer( MainPQ );*/

	printf( "\nQueue after decreasing first element priority \n" );
	KeyDown( MainPQ, 0, 6 );
	Printer( MainPQ );

	
	printf( "\nQueue after increasing third element priority \n" );
	KeyUp( MainPQ, 2, 16 );
	Printer( MainPQ );


	printf("\nCleaning queue...\nRemoved elements and theirs priors:\n"); 

	while( !( PQisEmpty( MainPQ ) ) )
	{
		PQElem* tmp = Dequeue( MainPQ );
		printf( "%d %d\n", tmp->nElem->nKey, tmp->nPrio );
	}	
#endif	

ByteEater( MainPQ );

#ifdef _DEBUG_
	if( !( MainPQ->PQInter ) ) printf( "\nCorrectly cleaned!" );
#endif

	return 0;
}

void Printer( PQueue* ToPrint )
{
	if( !PQisEmpty( ToPrint ) )
	{
		printf( "Priorities and keys:\n" );
		for( int i = 0; i < ToPrint->cSize; i++ )
		{
			printf( "%d ", ToPrint->PQInter[ i ]->nPrio );
			printf( "%d \n", ToPrint->PQInter[ i ]->nElem->nKey );
		}
	}
}
