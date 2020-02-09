#include "pch.h"
#include "tab.h"
#include <iostream>
#define _DEBUG_


void fnc_QuickSort( int* tab, int Size );
void fnc_MergeSort( int* tab, int Size );
void dfnc_MergeSort( int* tab, int Size );


int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		perror( "Empty Size!!!" );
		return 1;
	}
	int nSize = atoi( argv[ 1 ] );
	sort_tab functions_tab[] = { fnc_MergeSort ,insertionSort ,selectionSort,halfInsertionSort,heapSort,MixedBubbleSort,fnc_QuickSort,BubbleSort,dfnc_MergeSort };
	const char* sort_names[] = { "Mergesort with two Arrays","insertionSort" ,"selectionSort","halfInsertionSort","heapSort","MixedBubbleSort","quickSort","BubbleSort","MergeSort with one Array" };
	int* tab = NULL;
	int* mycopy = NULL;
	tab = Creator( nSize );
	mycopy = Creator( nSize );

	if( !mycopy || !tab )
	{
		perror( "Memory allocation error:pre-initTab stage " );
		return 0;
	}
	initTab( tab, nSize );

#ifdef _DEBUG_
	printTab( tab, nSize );
#endif

	copyTab( mycopy, tab, nSize );

#ifdef _DEBUG_
	printTab( mycopy, nSize );
#endif

	clock_t start;
	clock_t stop;
	double time = 0;
	int size = sizeof( functions_tab ) / sizeof( sort_tab );
	for( int i = 0; i < size - 1; i++ )
	{
		start = clock();
		functions_tab[ i ]( tab, nSize );
		stop = clock();
#ifdef _DEBUG_
		printTab( tab, nSize );
#endif
		time = ( (double)stop - (double)start ) / CLOCKS_PER_SEC;
		printf( "The time of %s is %f seconds\n\n", sort_names[ i ], time );
		copyTab( tab, mycopy, nSize );
	}
	int* tab_s = Creator( 2 * nSize ); //double size array to merge on one array
	if( !tab_s )
	{
		perror( "Memory allocation error-second_Merge " );
		return 0;
	}
	copyTab( tab_s, tab, nSize );

#ifdef _DEBUG_
	printTab( tab_s, nSize * 2 );
#endif  

	start = clock();
	functions_tab[ 8 ]( tab_s, nSize );

#ifdef _DEBUG_
	printTab( tab, nSize );
#endif

	stop = clock();
	time = ( (double)stop - (double)start ) / CLOCKS_PER_SEC;

#ifdef _DEBUG_
	printTab( tab_s, nSize );
#endif

	printf( "The time of %s is %f seconds\n\n ", sort_names[ 8 ], time );
	free( tab );
	free( tab_s );
	free( mycopy );
	return 0;
}
void fnc_QuickSort( int* tab, int Size )
{
	quickSort( tab, 0, Size - 1 );
}
void fnc_MergeSort( int* tab, int Size )
{
	int* arr_f = Creator( Size );
	MergeSort( tab, 0, Size - 1, Size, arr_f );
	free( arr_f );
}
void dfnc_MergeSort( int* tab, int Size )
{
	d_MergeSort( tab, 0, Size - 1, Size );
}
