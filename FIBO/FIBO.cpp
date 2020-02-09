#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>


long long int Fibo( int number );

int main( int argc, char* argv[] )
{
	if( argc != 2 )
	{
		perror( "Illegal arguments number!" );
		return 1;
	}
	int nFibo = atoi( argv[ 1 ] );
	long long int score = Fibo( nFibo );
	printf( "%d ", score );
	return 0;
}

//n-ty wyraz fibo

long long int Fibo( int number )
{
	long long int next;
	long long int a = 0;
	long long int b = 1;
	if( number==1 ) return b;
	else if( !number ) return a;
	for( int i = 2; i <= number; i++ )
	{
		next = a + b;
		a = b;
		b = next;
	}
	return b;
}
