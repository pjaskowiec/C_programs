#include "pch.h"
#include "WordCount.h"


int main( int argc, char** argv )
{
	if( argc != 2 )
	{
		perror( "Illegal arguments!" );
		return 2;
	}
	Tree* BST = NULL;
	int toCheck=ReadData( &BST, argv[ 1 ] );
	if( toCheck )  TreeOrder( BST );
	TreeCleaner( &BST );
	return 0;
}