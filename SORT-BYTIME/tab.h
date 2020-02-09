#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>


typedef void( *sort_tab )( int*, int );


int* Creator( int Size );
void initTab( int* tab, int Size );
void printTab( int* tab, int Size );
void BubbleSort( int* tab, int Size );
void insertionSort( int* tab, int Size );
void selectionSort( int* tab, int Size );
void halfInsertionSort( int* tab, int Size );
void MergeSort( int* tab, int l, int r, int Size, int* temp );
void heapSort( int* tab, int Size );
void quickSort( int* tab, int l, int r );
void MixedBubbleSort( int* tab, int Size );
void copyTab( int* tabt, int* tabf, int Size );
void d_MergeSort( int* tab, int l, int r, int Size );
