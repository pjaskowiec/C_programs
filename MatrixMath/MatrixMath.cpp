#include "pch.h"
#include <stdio.h>
#include "Matrix.h"
#include <iostream>
#define _DEBUG_
using namespace std;

	void ReadData( FILE* fin, double** pMatrix, double* b, int nDim );

	int main( int argc, char* argv[] )
	{

		if( argc != 2 ) // muszą być dwa argumenty wywołania!!! mogłoby byc ew. <2,ale istnieja przypadki nadmiernej ilosci arg. 
		{
			perror( "No file to read!\n\n" );
			return 1;
		}
		FILE* p = fopen( argv[ 1 ], "r" ); // otwiera plik do czytania(r) i ustawiamy na niego wskaznik
		if( !p )
		{
			perror( "Read error!\n\n" );
			return 1;
		}

		int Size = 0;
		fscanf( p, "%d", &Size ); // zczytujemy z pliku rozmiar macierzy 
		double** ReadTab = NULL; // do czytania macierzy
		double* f_vec = NULL; // do wektora wyrazów wolnych 
#ifdef _DEBUG_ //wydruk kontrolny 
		printf( "ReadTab %d x %d\n", Size, Size );
#endif
		CreateMatrix( &ReadTab, Size );
		if( !CreateMatrix( &ReadTab, Size ) )
		{
			perror( "Memory allocation error matrix!\n\n" );
			return 2;
		}
		f_vec = (double*)malloc( sizeof( double ) * Size ); // dynamiczna alokacja
		if( !f_vec )
		{
			perror( "Memory allocation error free!\n\n" );
			return 0; // poprawnosc operacji alokowania
		}
		memset( f_vec, 0, sizeof( double ) * Size ); // wypelniamy zerami kolejne bajty pamięci
		ReadData( p, ReadTab, f_vec, Size ); // w koncu mozemy zczytac z pliku wartosci
		fclose( p ); //wyjscie z pliku

#ifdef _DEBUG_
//PrintMatrix(ReadTab, Size);
		printf( "\n" );
		for( int i = 0; i < Size; i++ )
		{
			printf( "\n" );
			for( int j = 0; j < Size; j++ )
			{
				printf( "%lf ", ReadTab[ i ][ j ] );
			}
		}
		printf( "\n\n" );
#endif



		double deter = Det( ReadTab, Size );
		if( fabs( deter ) <= 1e-14 )
		{
			perror( "Det=0, can't calc inverse matrix!\n\n" );
			return 0;
		}

		double* result = NULL; //deklaracja rozwiazania
		result = (double*)malloc( sizeof( double ) * Size );
		if( !result )
		{
			perror( "Memory allocation error result!\n\n" );
			return 0;
		}
		memset( result, 0, sizeof( double ) * Size );

		double** InvMat = NULL;
		CreateMatrix( &InvMat, Size ); // dodatkowa pamięć na macierz odwrotną 
		if( !CreateMatrix( &InvMat, Size ) )
		{
			perror( "Memory allocation error inverse!\n\n" );
			return 0;
		}

		InverseMatrix( InvMat, ReadTab, Size, deter ); // obliczamy macierz odwrotna
		DeleteMatrix( &ReadTab, Size );
		LayoutEquation( InvMat, f_vec, result, Size ); // wektor rozwiazan 
		free( f_vec );
		DeleteMatrix( &InvMat, Size );
		double* score = result;
		while( Size-- )
		{
#ifdef _DEBUG_
			printf( "Solution %d\n", Size + 1 );
#endif
			printf( "%f\n", *score++ );
		}// wyswietlamy rozwiazanie
		free( result );
		return 0;
	}


	void ReadData( FILE* fin, double** pMatrix, double* b, int Dim )
	{
		for( int i = 0; i < Dim; i++ )
		{
			double* column = *pMatrix++; // wskaznik na aktualną kolumnę
			for( int j = 0; j < Dim; j++ )
			{
				fscanf( fin, "%lf", column++ );
			}
			fscanf( fin, "%lf", b++ ); // zostaja nam ostatnia kolumn z wyrazami wolnymi
		}
	}
