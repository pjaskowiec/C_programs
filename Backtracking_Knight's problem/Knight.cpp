#include "pch.h"
#include "Knight.h"


int** Creator( int nDim ) 
{
	int** tmpBoard = (int**)calloc( nDim, sizeof( int* ) ); //dynamicznie tworzymy tablice dwuwymiarowa
	if( !tmpBoard )
	{
		perror( "Memory allocation error-chessBoard creation!" );
		return NULL;
	}
	*tmpBoard = (int*)calloc( nDim * nDim, sizeof( int ) ); //miejsce na pola szachownicy
	if( !(*tmpBoard) )
	{
		perror( "Memory allocation error-chessBoard creation-second dim!" );
		return NULL;
	}
	int** chessBoard = tmpBoard;
	for( int i = 0; i < nDim; i++ )  *chessBoard++ = *tmpBoard + ( nDim * i ); //uzupe³niamy kazde pole szachownicy
	return tmpBoard;
}

int Movement( int** pChessBoard, int nDim, int target, int x, int y, int* px, int* py, Point* pHorseMoves )
{
	*px = x + pHorseMoves[ target ].x0;
	*py = y + pHorseMoves[ target ].y0;
	return (   *px >= 0 && *px < nDim && *py >= 0 && *py < nDim && pChessBoard[ *px ][ *py ] == 0 ); //warunki mozliwosci wykonania ruchu
}


int root( int** pChessBoard, int nDim, int moveNum, int x, int y, Point* pHorseMoves ) 
{
	static int calls = 0;  //dzieki staticowi po kazdym wywolaniu wartosc sie nie zresetuje
	calls++;
	pChessBoard[ x ][ y ] = moveNum;

	if( moveNum == nDim * nDim ) //po przejsciu przez wszystkie pola szachownicy mozemy napisac ile potrzebowalismy wywolan do tego celu
	{
		printf( "Number of calls :%d \n", calls );
		return 1; //bedzie moglo wydrukowac 
	}
	int px;
	int py;

	for( int i = FIRST; i < EIGHT; i++ ) 
	{
		if( Movement( pChessBoard, nDim, i, x, y, &px, &py, pHorseMoves ) ) 
		{
			if( root( pChessBoard, nDim, moveNum + 1, px, py, pHorseMoves ) )   return 1; //przegladniemy wszystkie warianty ruchow skoczka z pola
		}
	}
	pChessBoard[ x ][ y ] = 0; //blad krokow,reset

	return 0;
}

//If all squares are visited
//print the solution
//Else
//a) Add one of the next moves to solution vector and recursively
//check if this move leads to a solution. ( A Knight can make maximum
//	eight moves.We choose one of the 8 moves in this step ).
//	b) If the move chosen in the above step doesn't lead to a solution
//	then remove this move from the solution vector and try other
//	alternative moves.
//	c) If none of the alternatives work then return false ( Returning false
//	will remove the previously added item in recursion and if false is
//		returned by the initial call of recursion then "no solution exists" )


void Remover( int*** pChessBoard )
{
	int** Holder = *pChessBoard;
	free( Holder[ 0 ] );
	free( *pChessBoard );
	pChessBoard = NULL;
}