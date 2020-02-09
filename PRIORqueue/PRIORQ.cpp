#include "pch.h"
#include "PRIORQ.h"


PQueue* Creator( int Size )
{
	PQueue* ToCreate = (PQueue*)calloc( 1, sizeof( PQueue ) );
	if(!ToCreate )
	{
		perror( "Memory allocation error-Priority Queue Creation!" );
		return NULL;
	}
	ToCreate->PQInter = (PQElem**)calloc( Size, sizeof( PQElem* ) );
	if( !(ToCreate->PQInter) )
	{
		free( ToCreate );
		perror( "Memory allocation error-Priority Queue Creation-Interior part!" );
		return NULL;
	}
	ToCreate->nSize = Size;
	return ToCreate;
}



void Enqueue( PQueue* TOADD, PQGLOBAL* nElement, int Prio )
{
	if( TOADD->cSize >= TOADD->nSize ) //nie mozemy wykroczyc poza wielkosc kolejki
	{
		perror( "No place to add new element!" );
		return;
	}
	TOADD->PQInter[ TOADD->cSize ] = (PQElem*)calloc( 1, sizeof( PQElem ) ); //alokacja pamieci na konkretny element w tablicy
	if( !( TOADD->PQInter[ TOADD->cSize ] ) )
	{
		perror( "Memory allocation error-Enqueue!" );
		return;
	}
	//uzupelniamy kolejke o informacje na temat elementu
	TOADD->PQInter[ TOADD->cSize ]->nElem = nElement;
	TOADD->PQInter[ TOADD->cSize ]->nPrio = Prio;
	//teraz nalezy uaktualnic stan kolejki
	Update( TOADD, 0, TOADD->cSize++ ); //jest to zasadniczo ukladanie stogu!!!
}
//update przy keyup do poprawy
void Update( PQueue* ToUp, int left, int right ) //od do³u
{
	if( left == right ) return; 
	int i = right; //wyznaczamy dziecko i rodzica
	int j = ( ( i - 1 ) / 2 ) ; 
	int k = ToUp->PQInter[ i ]->nPrio; 
	PQElem* tmp = ToUp->PQInter[ i ]; //bedziemy potrzebowali do podmianki po znalezieniu elementu
	while( j >= left ) //dopoki nie dojdziemy do lewego przedzialu(poczatku)
	{
		if( k <= ToUp->PQInter[ j ]->nPrio ) break; //jesli trafimy na jakikolwiek wiekszy prior,element juz wyzej nie przeskoczy-konczymy petle
		ToUp->PQInter[ i ] = ToUp->PQInter[ j ];
		i = j;
		j = ( ( i + 1 ) / 2 ) - 1;
	}
	ToUp->PQInter[ i ] = tmp;
}


int PQisEmpty( PQueue* ToCheck )
{
	//return ( ToCheck->cSize ) ? 0 : 1;
	return !( ToCheck->cSize );
}

PQElem* Dequeue( PQueue* TODEL )
{
	if( PQisEmpty( TODEL ) )
	{
		perror( "No element to remove!" );
		return NULL;
	}
	PQElem* Holder = TODEL->PQInter[ 0 ];
	TODEL->PQInter[ 0 ] = TODEL->PQInter[ --TODEL->cSize  ];
	TODEL->PQInter[ TODEL->cSize ]=NULL;
	//if( !PQisEmpty( TODEL ) )
	   UpdateD( TODEL, 0, TODEL->cSize-1 );
   	return Holder;
}

void UpdateD( PQueue* ToDown, int left, int right ) //od góry
{
	if( left >= right ) return;
	int i = left;
	int j = 2 * i + 1; // i jest lewym dzieckiem,a j prawym
	PQElem* toHold = ToDown->PQInter[ left ];  //przytrzymamy ojca,w stosunku do którego mo¿emy podmieniæ
	int k = ToDown->PQInter[i]->nPrio;
	while( j <= right ) //do ostatniego dziecka
	{
		if( j < right && ToDown->PQInter[ j ]->nPrio < ToDown->PQInter[ j + 1 ]->nPrio )  j++; //przeskok pomiedzy dziecmi
		if( k >= ToDown->PQInter[ j ]->nPrio ) break; 
		ToDown->PQInter[ i ] = ToDown->PQInter[ j ];
		i = j;
		j = 2 * i + 1;
	}
	ToDown->PQInter[ i ] = toHold; //znalenziony najwyzszy prior trafia na sama gore 
}

void KeyUp( PQueue* Kup,int index ,int nPrior )
{
	if( Kup->PQInter[ index ]->nPrio < nPrior )
	{
		Kup->PQInter[ index ]->nPrio = nPrior;
		Update( Kup, 0, index );
	}
}


void KeyDown( PQueue* KDown, int index, int nPrior )
{
	if( KDown->PQInter[ index ]->nPrio > nPrior )
	{
		KDown->PQInter[ index ]->nPrio = nPrior;
		UpdateD( KDown, index, KDown->cSize-1 );
	}
}

void PQCleaner( PQueue* toClean )
{

	while( !( PQisEmpty( toClean ) ) )	Dequeue( toClean );
		
}

void ByteEater( PQueue* toEat )
{
	PQCleaner( toEat );
	free( toEat->PQInter );
	free( toEat );
	toEat->PQInter = NULL;
	toEat = NULL;
}



//
//void sifting( PQueue* tab, int l, int p )
//{
//	if( l == p ) return;
//
//	int i = l;
//	int j = 2 * i + 1;
//	int x = tab->PQInter[ i ]->nPrio;
//	PQElem* tmp = tab->PQInter[ i ];
//	while( j <= p )
//	{
//		if( j < p )
//			if( tab->PQInter[ j ]->nPrio < tab->PQInter[ j + 1 ]->nPrio ) j++;
//		if( x > tab->PQInter[ j ]->nPrio ) break;
//		tab->PQInter[ i ] = tab->PQInter[ j ];
//		i = j;
//		j = 2 * i + 1;
//	}
//	tab->PQInter[ i ] = tmp;
//
//}
//
//void heapSort( PQueue* tab, int Size )
//{
//	for( int l = ( Size / 2 - 1 ); l >= 0; l-- )
//	{
//		sifting( tab, l, Size - 1 );
//	}
//	for( int p = Size - 1; p > 0; p-- )
//	{
//		PQElem* tmp2 = tab->PQInter[ 0 ];
//		tab->PQInter[ 0 ] = tab->PQInter[ p ];
//		tab->PQInter[ p ] = tmp2;
//		sifting( tab, 0, p - 1 );
//	}
//	reverse( tab, Size );
//}
//
//
//void reverse( PQueue* arr, int n )
//{
//	for( int low = 0, high = n-1 ; low >= high; low++, high-- )
//	{
//		int tmp3 = arr->PQInter[ low ]->nElem->nKey;
//		int tmp4 = arr->PQInter[ low ]->nPrio;
//		arr->PQInter[ low ]->nPrio = arr->PQInter[ high ]->nPrio;
//		arr->PQInter[ low ]->nElem->nKey = arr->PQInter[ high ]->nElem->nKey;
//		arr->PQInter[ high ]->nElem->nKey = tmp3;
//		arr->PQInter[ high ]->nPrio = tmp4;
//	}
//}