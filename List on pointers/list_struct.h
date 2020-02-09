#ifndef LIST_STRUCT //na wypadek wielokrotnego u¿ycia bibliotek 
#define LIST_STRUCT

#include <memory.h>
#include <iostream>
#include "keyINT.h"
#include <time.h>

typedef int( *compar )( const void* ,const void* );


typedef struct tagList_structure  {
	GLOBALINT* p_cur;
	tagList_structure* p_next;
}List;


List* ListCreator( ); //Memory allocation list
int CheckEmpty( List* check ); //Is list empty?
void insert( List* instertion, GLOBALINT* element );
void frontal( List* toInsert, GLOBALINT* element ); 

void Sorting( List* toSort,compar compar_function ); 
void Remover( List* ToRemove );
void RemoveFrontal( List* RemoveFirst );
void deleter( List* todelete );
void Restdeleter( List** wholeDel ); //z wartownikiem
List* finder( List* toFind, const void* value, List** previous, compar compare );

#endif