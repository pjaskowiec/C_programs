#include "pch.h"
#include "list_struct.h"
#define _DEBUG_

void printer( List* p );
int Compare( const void* f, const void* s );

using namespace std;


int main( int argc, char* argv[] )
{
	if( argc != 2 ) {
		perror( "Illegal arguments number!" );
		return 1;
	}
	int Size = atoi( argv[ 1 ] );
	srand( (unsigned int)time( NULL ) );
	List* main_List = ListCreator( ); //deklarujemy pamiec na tablice
#ifdef _DEBUG_
	printf( "Unordered list:\n" );
	for( int i = 0; i < Size; i++ )
	{
		GLOBALINT* tmpint = (GLOBALINT*)malloc( sizeof( GLOBALINT ) ); 
		tmpint->nKey = rand() % 15; //wypelniamy klucze liczbami pseduolosowymi 
		frontal( main_List, tmpint );
	}
	printer( main_List ); //swietnie,mamy zapelniona tablice,teraz czas posortowac elementy
	Sorting( main_List, Compare );
	//Sorting( main_List )
	printf( "List in order:\n" ); //sort
	printer( main_List );

	printf( "After Removing second element:\n" ); //remove second
	Remover( main_List->p_next );
	printer( main_List );
	printf( "After Removing first element:\n" ); //remove front
	RemoveFrontal( main_List );
	printer( main_List );
	printf( "After Instering first element:\n" ); //insert fron
	GLOBALINT* tmpint2 = (GLOBALINT*)malloc( sizeof( GLOBALINT ) );
	tmpint2->nKey = 100; 
	frontal( main_List, tmpint2 );
	printer( main_List );
	printf( "After Instering third element:\n" ); //insert third
	tmpint2 = (GLOBALINT*)malloc( sizeof( GLOBALINT ) );
	tmpint2->nKey = 200;
	insert( main_List->p_next->p_next,tmpint2 );
	printer( main_List );
	GLOBALINT w = { 12 }; //inicjator
	List* c = NULL; //lista dla poprzednika
	List* p=finder( main_List, &w, &c, Compare );
	if( !c ) printf( "Not found!" );
	else if( c->p_cur) printf( "Found %d, Previous %d", p->p_cur->nKey, c->p_cur->nKey);
	else printf( "Found %d,No Previous!", p->p_cur->nKey );
	printf( "\nCleaning list..." );
	deleter( main_List );
	if( CheckEmpty( main_List ) )
	{
		printf( "\nList is empty!" );
	}
	else 
	{
		printf ("\nList still has elements!");
	}
#endif
}



void printer( List* p )
{
	List* tmp = p;
	tmp = tmp->p_next;

	while( tmp )
	{
		printf( " %d ", tmp->p_cur->nKey );
		tmp = tmp->p_next; //schodzimy sobie do poczatku listy
	}
	printf( "\n" );
}
int Compare( const void* f, const void* s )
{
	if( ( (GLOBALINT*)f )->nKey > ( (GLOBALINT*)s )->nKey )
		return 0;
	else if( ( (GLOBALINT*)f )->nKey < ( (GLOBALINT*)s )->nKey )
		return 1;
	return 2;
}
