#include "pch.h"
#include "tab.h"

void first_merge( int* tab, int l, int m, int r, int Size, int* arr );
void sec_merge( int* tab, int l, int m, int p, int Size );
void sifting( int* tab, int l, int p );


	int* Creator( int Size )
	{
		int* tab = (int*)malloc( Size * sizeof( int ) );
		if( !tab ) {
			perror( "Memory allocation error!" );
			return 0;
		}
		memset( tab, 0, sizeof( int ) * Size );
		return tab;
	}

	void initTab( int* tab, int Size )
	{
		srand( (unsigned int)time( NULL ) );
		for( int i = 0; i < Size; i++ )
			tab[ i ] = rand() % Size;
	}

	void printTab( int* tab, int Size )
	{
		for( int i = 0; i < Size; i++ )
			printf( "%d ", tab[ i ] );
		printf( "\n\n" );
	}

	void copyTab( int* tabt, int* tabf, int Size )
	{
		memcpy( tabt, tabf, Size * sizeof( int ) );
	}

	void MergeSort( int* tab, int l, int r, int Size, int* temp )
	{
		if( l < r )
		{
			int middle = ( l + r ) / 2;
			MergeSort( tab, l, middle, Size, temp );
			MergeSort( tab, middle + 1, r, Size, temp ); //rekurencyjnie dzielimy tablice
			first_merge( tab, l, middle, r, Size, temp ); //rekurencyjne ³aczenie
		}
	}


	void first_merge( int* tab, int l, int m, int r, int Size, int* arr )
	{
		int i = l; //start of first sorted
		int j = m + 1; //start of second sorted
		int k = l; //do wczytwania dwoch podciagow
		memcpy( arr + l, tab + l, sizeof( int ) * ( r - l + 1 ) ); //kopiowanie danych
		while( i <= m && j <= r )
		{
			if( arr[ i ] <= arr[ j ] )
			{
				tab[ k++ ] = arr[ i++ ];
			}
			else if( arr[ j ] <= arr[ i ] )
			{
				tab[ k++ ] = arr[ j++ ];
			}
		}
		memcpy( tab + k, arr + i, ( m - i + 1 ) * sizeof( int ) ); //dokopiowanie na ostatni adres
	}


	void d_MergeSort( int* tab, int l, int r, int Size )
	{
		if( l < r )
		{
			int m = ( l + r ) / 2;
			d_MergeSort( tab, l, m, Size );
			d_MergeSort( tab, m + 1, r, Size );
			sec_merge( tab, l, m, r, Size );
		}
	}

	void sec_merge( int* tab, int l, int m, int p, int Size )
	{
		copyTab( tab + Size + l, tab + l, p - l + 1 ); //zamiast kopiowania do drugiej tablicy,tworzymy nowa o 2-krotnym rozmiarze
		int i = l;
		int j = m + 1;
		int k = l;

		while( i <= m && j <= p ) // laczenie dwoch posortowanych ciagow
		{
			if( tab[ Size + i ] <= tab[ Size + j ] )
			{
				tab[ k++ ] = tab[ Size + i++ ];
			}
			else
			{
				tab[ k++ ] = tab[ Size + j++ ];
			}
		}
		copyTab( tab + k, tab + Size + i, m - i + 1 );
	}

	void sifting( int* tab, int l, int p )
	{
		if( l == p ) return;
	
		int i = l;
		int j = 2 * i + 1;
		int x = tab[ i ];
		while( j <= p )
		{
			if( j < p )
				if( tab[ j ] < tab[ j + 1 ] ) j++;
			if( x > tab[ j ] ) break;
			tab[ i ] = tab[ j ];
			i = j;
			j = 2 * i + 1;
		}
		tab[ i ] = x;

	}

	void heapSort( int* tab, int Size )
	{
		for( int l = (Size / 2 - 1) ; l >= 0; l-- )
		{
			sifting( tab, l, Size - 1 );
		}
		for( int p = Size - 1; p > 0; p-- )
		{
			int x = tab[ 0 ];
			tab[ 0 ] = tab[ p ];
			tab[ p ] = x;
			sifting( tab, 0, p - 1 );
		}
	}

	void BubbleSort( int* tab, int Size )
	{
		for( int i = 0; i < Size - 1; i++ )
			for( int j = Size - 1; j > i; j-- )
			{
				if( tab[ j ] < tab[ j - 1 ] )
				{
					int temp = tab[ j ];
					tab[ j ] = tab[ j - 1 ];
					tab[ j - 1 ] = temp;
				}
			}
	}


	void insertionSort( int* tab, int Size )
	{
		for( int i = 1; i < Size; i++ )
		{
			int x = tab[ i ];
			int j = i - 1;
			while( j >= 0 && tab[ j ] > x )
				tab[ j + 1 ] = tab[ j-- ];
			tab[ j + 1 ] = x;


		}

	}



	void selectionSort( int* tab, int Size )
	{
		for( int i = 0; i < Size - 1; i++ )
		{
			int min = tab[ i ];
			int x = i;
			for( int j = 1; j < Size; j++ )
				if( tab[ j ] < min )
				{
					min = tab[ j ];
					x = j;
				}
			tab[ x ] = tab[ i ];
			tab[ i ] = min;

		}


	}


	void halfInsertionSort( int* tab, int Size )
	{
		int start;
		int end;
		int middle;
		int score;
		for( int i = 1; i < Size; ++i )
		{
			score = tab[ i ];
			start = 0;
			end = i - 1;
			while( start <= end )
			{
				middle = ( start + end ) / 2;
				if( score < tab[ middle ] )
				{
					end = middle - 1;
				}
				else
				{
					start = middle + 1;
				}
			}
			for( int j = i - 1; j >= start; --j )
			{
				tab[ j + 1 ] = tab[ j ];
			}
			tab[ start ] = score;
		}
	}

	void quickSort( int* tab, int l, int r )
	{
		int i = l;
		int j = r;
		int v = tab[ ( l + r ) / 2 ];
		do {
			while( tab[ i ] < v )
				i++;
			while( v < tab[ j ] )
				j--;
			if( i <= j ) {
				int temp = tab[ i ];
				tab[ i ] = tab[ j ];
				tab[ j ] = temp;
				i++;
				j--;
			}
		} while( i <= j );
		if( l < j )
			quickSort( tab, l, j );
		if( i < r )
			quickSort( tab, i, r );


	}


	void MixedBubbleSort( int* tab, int Size )
	{
		int l = 1;
		int p = Size - 1;
		int k = Size;
		int x;
		while( l <= p )
		{
			for( int i = p; i >= l; i-- )
			{
				if( tab[ i - 1 ] > tab[ i ] )
				{
					x = tab[ i ];
					tab[ i ] = tab[ i - 1 ];
					tab[ i - 1 ] = x;
					k = i;

				}
			}
			l = k + 1;
			for( int i = l; i <= p; i++ )
			{
				if( tab[ i ] < tab[ i - 1 ] )
				{
					x = tab[ i ];
					tab[ i ] = tab[ i - 1 ];
					tab[ i - 1 ] = x;
					k = i;
				}
			}
			p = k - 1;
		}

	}
