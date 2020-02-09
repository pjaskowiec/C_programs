#include "pch.h"
#include "Index_Search.h"


#define Size 100
#define _DEBUG_

using namespace std;

ExArray* index_search( int* tab, int nSize, int Searcher );

	int main()
	{
		srand( (unsigned int)time( NULL ) );
		int toFind;
		int* tab = (int*)calloc( Size, sizeof( int ) );
		if( !tab )
		{
			perror( "Memory allocation error-tab_creation!" );
			return 1;
		}

		for( int j = 0; j <= Size - 1; j++ )
		{
			tab[ j ] = rand() % 100 + 1;
#ifdef _DEBUG_
			printf( "%d ", tab[ j ] );
#endif
		}

		printf( "\nEnter number :\n\n" );
		cin >> toFind;
		ExArray* toReturn = NULL;
		toReturn=index_search( tab, Size, toFind );
		if( !toReturn )
		{
			printf( "Such an element doesn't exist!" );
			return 2;
			free( tab ); 
			free( toReturn->ExTab );
			free( toReturn );
		}
		printf( "Index numbers:\n" );
		for( int z = 0; z <  toReturn->currSize;  z++ ) printf( "%d ", toReturn->ExTab[ z ] );

		free( tab );
		free( toReturn->ExTab );
		free( toReturn );
		return 0;
	}


	ExArray* index_search( int* tab, int nSize, int Searcher )
	{
		ExArray* CopyArray = (ExArray*)calloc( 1, sizeof( ExArray ) );
		if( !CopyArray )
		{
			perror( "Memory allocation error-Copytab_creation!" );
			return NULL;
		}
		CopyArray->ExTab = (int*)calloc( Size, sizeof( int ) );
		if( !( CopyArray->ExTab ) )
		{
			free( CopyArray );
			perror( "Memory allocation error-Copytab_creation!" );
			return NULL;
		}


		int j=0;
		for( int i = 0; i <= nSize - 1; i++ )
		{
			if( tab[ i ] == Searcher )
			{
				CopyArray->ExTab[ j ]=i;//niech zwraca wszystkie indeksy,ktore znajdzie
				j++;
				CopyArray->currSize = j;
			}
		}
		if( !j ) return NULL;
		return CopyArray;
	}
