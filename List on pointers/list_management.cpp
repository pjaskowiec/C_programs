#include "pch.h"
#include "list_struct.h"



List* ListCreator()
{
	List* pList = (List*)malloc( sizeof( List ) );
	if( !pList ) {
		perror( "Memory allocation error-List Create" );
		return NULL;
	}
	memset( pList, 0, sizeof( List ) ); //mozna rownie dobrze zrobic to wszystko calloc
	return pList;
}

void insert( List* instertion, GLOBALINT* element )
{
	List* extra_el = (List*)malloc( sizeof( List ) );
	if( !extra_el  )
	{
		perror( "Memory allocation error-Insertion" );
		return;
	}
	extra_el->p_cur = element; //element trafia na miejsce
	extra_el->p_next = instertion->p_next; //wskaznik na nastepny element
	instertion->p_next = extra_el; //podmianka
}


void frontal( List* toInsert, GLOBALINT* element )
{
	insert( toInsert, element ); //wywo³amy z sam¹ list¹,wiêc wejdzie na pierwsze miejsce
}

void Sorting( List* toSort, compar compar_function ) 
{
	List* holder = toSort;

	while( holder->p_next ) //przechodzimy przez cala liste
	{
		List*  Minimum = holder;
		List*  Loop = holder->p_next;
		while( Loop->p_next ) //sortowanie przez wybieranie-znajdujemy najmniejszy
		{
			//if( Compare(..))
			if( compar_function( (const void*)Loop->p_next->p_cur, (const void*)Minimum->p_next->p_cur ) )
			Minimum = Loop;
			Loop = Loop->p_next;
		}
		if( Minimum != holder ) //jesli choc raz element okaza³ siê mniejszy musimy przewiazac
		{
			Loop = Minimum->p_next; //element pod,którym siedzi minimum
			Minimum->p_next = Loop->p_next;//musimy `obejsc` minimum / minimum->p_next=minimum->p_next->p_next
			Loop->p_next = holder->p_next; //przewiazujemy
			holder->p_next = Loop; //teraz wskazuje na minimum
		}
		holder = holder->p_next; //element najmniejszy na pierwszym miejscu,juz go zostawiamy

	}
}





int CheckEmpty( List* check )
{
	return !check->p_next;
}
void deleter( List* todelete ) 
{
	while( !CheckEmpty( todelete ) ) RemoveFrontal( todelete );
}
void Restdeleter( List** wholeDel ) //z wartownikiem
{
	deleter( *wholeDel );
	free( *wholeDel );
	*wholeDel = NULL;
}



void Remover( List* ToRemove )
{
	
	if( !CheckEmpty(ToRemove) )
	{
		
		List* to_remove = ToRemove->p_next; //musi prztrzymac adres nastepnika
		ToRemove->p_next = to_remove->p_next; //zrywa polaczenie z elementem i wskazuje na nastepny po nim
		free( to_remove->p_cur );
		free( to_remove );
	}
	else perror( "No element to remove!" );
}
void RemoveFrontal( List* RemoveFirst )
{
	Remover( RemoveFirst );
}
List* finder( List* toFind, const void* value, List** previous, compar compare )
{
	List* find_tmp = toFind->p_next; 
	*previous = toFind; //poprzednik
	while( find_tmp )
	{
		if( compare( (const void*)find_tmp->p_cur, value ) ==2 ) return find_tmp; //porownujemy,jesli trafimy na element zwracamy struktrue 
		*previous = find_tmp; //jesli nie to poprzednik przyjmuje adres wczesniejszego przeszukiwanego elementu
		find_tmp = find_tmp->p_next; //i szukamy dalej
	}
	return *previous = NULL; //nie znalezlismy/trafilismy na element,ktory nie ma poprzednika
}


