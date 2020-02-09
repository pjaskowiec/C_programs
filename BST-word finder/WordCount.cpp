#include "pch.h"
#include "WordCount.h"

#pragma warning(disable : 4996) 
#pragma warning(disable : 4477) 

int Compare( char* fstr, char* sstr );
void CleanerT( Tree* toClean );
void TreeElem( char* word, Tree** Node, int line );
void FindAndInsert( char* word, Tree** BST, int line );




//funkcja do znajdywania pasujacego slowa i wsadzajaca go do drzewka
int Compare( char* fstr, char* sstr )
{
	char* ftmp = (char*)calloc( strlen( fstr ) + 1, sizeof( char ) );
	if( !ftmp )
	{
		perror( "Memory Allocation error-compare first str" );
		return 0;
	}
	char* stmp = (char*)calloc( strlen( sstr ) + 1, sizeof( char ) );
	if( !stmp )
	{
		perror( "Memory Allocation error-compare second str" );
		return 0;
	}
	strcpy( ftmp, fstr );
	strcpy( stmp, sstr );

	_strlwr( ftmp );//konwersja na male litery
	_strlwr( stmp ); 

	int toReturn = strcmp( ftmp,stmp );    //w string.h,porowna dlugosc i zwraca w zaleznosci od wyniku
	free( ftmp ); //oprozniamy niepotrzebnie juz zajeta pamiec
	free( stmp );
	return toReturn;
}

void TreeElem ( char* word, Tree** Node, int line )
{
	char* saver = (char*)calloc( strlen( word ) + 1, sizeof( char ) );
	if( !saver )
	{
		perror( "Memory allocation error-TreeElem-saver!" );
		return;
	}
	memcpy( saver, word, strlen( word ) + 1 ); //!! inaczej poprawnie nie zapisze wyrazow->bufor jest statyczny 
	*Node = (Tree*)calloc( 1, sizeof( Tree ) );
	if( !*Node )
	{
		perror( "Memory allocation error-TreeElem-Tree!" );
		return;
	}
	( *Node )->n = 1;
	( *Node )->lines = Creator(); //zew.
	( *Node )->lines->Tail->nKey = line;
	( *Node )->toRead = saver;
}


void FindAndInsert( char* word, Tree** BST, int line )
{

	if( !( *BST ) ) TreeElem( word, BST, line );
	//trzy przypadki lewe poddrzewo jesli mniejsze,prawe jesli wieksze
	else if( ( Compare( word, ( *BST )->toRead ) ) < 0 )   FindAndInsert( word, &( *BST )->left, line );
	else if( ( Compare( word, ( *BST )->toRead ) ) > 0 )   FindAndInsert( word, &( *BST )->right, line );
	else // slowo o tej samej dlugosci
	{
		( *BST )->n++;
		if( ( *BST )->lines->Tail->nKey == line ) return; 
		Enqueue( (*BST)->lines, line ); //zew.
	}
}


void TreeOrder( Tree* toSort )
{
	//musimy dojsc maksymalnie do lewej,wywolujac rekurencyjnie funkcje,a wiec
	if( toSort->left ) TreeOrder( toSort->left );
	printf( "Word:%s n:%d\nlines:", toSort->toRead, toSort->n );
	Printer( toSort->lines->Head ); //zew.
	printf( "\n" );
	if( toSort->right ) TreeOrder( toSort->right );
}

int ReadData( Tree** TreeIn, const char* fName )
{
	FILE* toOpen = fopen( fName, "r" );
	if( !toOpen )
	{
		perror( "File cannot be opened!" );
		return 0;
	}

	char exp[ MAXC ] = { 0 };
	char line[ MAXC ] = { 0 };
	int lineNo = 1;

	while( fgets( line, MAXC, toOpen ) )  //zczyta po kolei linie
	{
		char* tmpLine = line;
		int length = 0;


		while( sscanf( tmpLine += length, "%[_A-Za-z0-9]%n", exp, &length ) ) //przejdziemy przez konkretna linie,zapisujac do stringa wyrazy(cos jak while read line do)
		{
			FindAndInsert( exp, TreeIn, lineNo );
			sscanf( tmpLine += length, "%*[^_A-Za-z\n]%n", &length ); //pominiemy tym sposboem wyraz nie bedace wyrazami
		}

		lineNo++;
	}

	fclose( toOpen );
	return 1;
}



void CleanerT( Tree* toClean )
{
	if( toClean->left ) CleanerT( toClean->left );
	if( toClean->right ) CleanerT( toClean->right );

    free( toClean->toRead );
	ByteEater( &(toClean )->lines ); //zew.
}

void TreeCleaner( Tree** toCleanTree )
{
	if( *toCleanTree ) CleanerT( *toCleanTree );
	free( *toCleanTree );
}
