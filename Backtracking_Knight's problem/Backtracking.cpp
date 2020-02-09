#include "pch.h"
#include "Knight.h"
#include "stdio.h"

void Printer( int** pChessBoard, int nDim );

using namespace std;


int main( int argc, char** argv )
{
	if( argc != 3 )
	{
		perror( "Illegal arguments number!" );
		return 1;
	}

	Point HorseMove[ HORSEMOVES ]
	{
		{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1},{-2,-1},{-1,-2} //mozliwe przesuniecia skoczka
	};
	int x = atoi( argv[ 1 ] ); //ustawiamy skad chcemy zaczac
	int y = atoi( argv[ 2 ] );

	int** pChess = Creator( BOARD_SIZE );
	if( !pChess ) return 2;

	if( root( pChess, BOARD_SIZE, 1, x, y, HorseMove ) )  Printer( pChess, BOARD_SIZE );
	else perror( "No solution exists" );

	Remover( &pChess );
}



void Printer( int** pChessBoard, int nDim ) 
{
	for( int i = 0; i < nDim; i++ )
	{
		int* tmp = *pChessBoard++;
		for( int j = 0; j < nDim; j++, tmp++ ) printf( "%d ", *tmp );
		printf( "\n" );
	}
}