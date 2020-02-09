#include "pch.h"
#include "Matrix.h"


void Complement( double** pTabO, double** pTabI, int nRow, int nCol, int nDim ); // wycianie macierzy
void ComplMatrix( double** pTabO, double** pTabI, int nDim ); // liczy macierz dopelnien
//void PrintMatrix( double** Tab, int Size );
int CreateMatrix( double*** pTab, int Size ) 
{
	*pTab = (double**)malloc( sizeof( double* ) * Size ); //rezerwujemy pamięć na tablice wskaznikow
	if( !*pTab ) return 0;
	memset( *pTab, NULL, sizeof( double* ) * Size ); //wypelniamy kolejne adresy pamieci nullami dla tablicy wskaznikow
	double** creator = *pTab; //wskaznik pomocniczy,by nie działać na ptab
	for( int i = 0; i < Size; i++ )
	{
		*creator = (double*)malloc( sizeof( double ) * Size );
		if( !*creator ) return 0;
		memset( *creator++, 0, sizeof( double ) * Size ); //z kolei teraz alokujemy pamiec w 'komorkach' i wypelniamy macierz domyslnie zerami
	}
	return 1; //warunek powodzenia
}


void DeleteMatrix( double*** pTab, int Size ) 
{
	double** creator = *pTab; 
	for( int i = 0; i < Size; i++ ) free( *creator++ ); // zerujemy pamiec w komorkach macierzy
	free( *pTab ); // gdy mamy czyste poszczegonlne adresy konkretne elementy tablic, zwalniamy pamiec dla całej tablicy wskaznikow 
	*pTab = NULL; // ustawiamy wskaznik ktory wskazywal na tablice wskaznikow na NULLA---->mamy juz czysto
}


void TransMatrix( double** pTab, int nDim ) //wiersze na kolumny,przekantnej nie tykamy
{
	double** row = pTab;
	for( int i = 0; i < nDim - 1; i++ )
	{
		double* col = *row++ + i + 1; //elementy przekatne zostaja na swoich miejscach
		for( int j = i + 1; j < nDim; j++ )
		{
			double temp = *col;
			*col++ = pTab[ j ][ i ]; 
			pTab[ j ][ i ] = temp;
			//*col++; //przechodzimy do kolejnej kolumny
		}
	}
}



void InverseMatrix( double** pInv, double** pTab, int Size, double det ) 
{
	// (AD)^T/DetA=macierz odwrócona
	ComplMatrix( pInv, pTab, Size ); // wyliczamy macierz dopelnien
	TransMatrix( pInv, Size ); // transponujemy ja
	double* s = NULL; //wskaznik pomocniczy do przechodzenia po kolumnach
	for( int i = 0; i < Size; i++ )
	{
		s = *pInv++;  //po wierszach
		for( int j = 0; j < Size; j++ )
		{
			*s++ /= det; //po kolumnach
		}
	}
}


double Det( double** pTab, int Size ) // rozwijamy laplacem i liczymy rekurencyjnie
{
	//mozna byloby dla macierzy jednoelementowej,ale po co?
	if( Size == 2 ) return ( pTab[ 0 ][ 0 ] * pTab[ 1 ][ 1 ] ) - ( pTab[ 0 ][ 1 ] * pTab[ 1 ][ 0 ] ); // liczmy wyznacznik dla macierzy 2-wymiarowej
	double** I = NULL; //  wskaznik pomocniczy
	CreateMatrix( &I, Size - 1 ); // macierz do wyciecia,dlatego mniejszy wymiarr
	double res = 0;
	double* f = *pTab; // wzgledem tego rozwijamy
	int sign = 1; // (-1)^i+j
	for( int i = 0; i < Size; i++ )
	{
		Complement( I, pTab, 0, i, Size ); // wycinamy z macierzy wiersz i kolumne
		//Σaij*detAij*(-1)^i+j
		res += *f++ * sign * Det( I, Size - 1 ); // rekurencyjnie obliczamy wyznacznik do size-1
		sign = -sign; //przy kazdym przejsciu zmiana znaku
	}
	DeleteMatrix( &I, Size - 1 ); // czyszczenie macierzy pomocniczej
	return res; // zwracamy wynik
}

void Complement( double **pTabOut, double **pTabIn, int nRow, int nCol, int nDim ) //wycinanie
{
	
	for( int i = 0; i < nDim; i++,pTabIn++ )
	{
	    double* copy = *pTabIn; // wskazniki na odpowiednie kolumny
		double* to = *pTabOut;
		if( i == nRow ) continue;
		for( int j = 0; j < nDim; j++, copy++ )
		{
			if( j == nCol )	 continue;
			*to++ = *copy; // przechodzimy po kolumnach i kopiujemy dane
		}
		pTabOut++;
	}
}

void LayoutEquation( double** pInv, double* pF, double* pRes, int Size )
{
	double* s = NULL; // wskaznik kolumna macierzy odwrotnej
	double* x = NULL; // wskaznik wektora wyrazow wolnych
	for( int i = 0; i < Size; i++ )
	{
		s = *pInv; // ustawiamy wskaznik na odpowiedniej kolumnie
		x = pF; // ustawiamy wskaznik na poczatku wektora wyrazow wolnych
		for( int j = 0; j < Size; j++ ) *pRes += *s++ * *x++;
		pInv++; // przechodzimy do kolejnego wiersza
		pRes++; // przechodzimy do kolejnej komorki wektora rozwiazan [x,y,z..]
	}
}






void ComplMatrix( double **pTabOut, double **pTabIn, int nDim ) // macierz dopelnien
{
	double* C = NULL; // wskaznik pomocniczy do dopisywania wartosci dopelnien
	double** I = NULL; // macierz pomocnicza do wyznacnzika
	double sign;
	CreateMatrix( &I, nDim - 1 ); //podobnie jak wczesniej przy wycieciu macierz bedzie rozmiar mniejsza
	for( int i = 0; i < nDim; i++ )
	{
		C = *pTabOut++; // ustawienie wskaznika we wlasciwej kolumnie
		if( i % 2 ) sign = -1;
		else sign = 1;
		for( int j = 0; j < nDim; j++ ) //wszystykie dopelnienia algebraiczne
		{
			Complement( I, pTabIn, i, j, nDim ); // wyciecie odpowiedniego wiersza i kolumny
			*C++ = sign * Det( I, nDim - 1 ); //podobnie jak w wyznanczniku,tylko liczymy bez sumowania i nie mnozymy przez konkretny element
			sign = -sign; //*=-1 dluzej sie wykonuje
		}
	}
	DeleteMatrix( &I, nDim - 1 ); // czyszczenie
}
//void PrintMatrix( double** Tab, int Size )
//{
	//double* p = NULL;
//	for( int i = 0; i < Size; i++ )
	//{
	//	p = *Tab++; 
		//for( int j = 0; j < Size; j++ )
			//printf( "%f ", *p++ ); 
		//printf( "\n" );
	//}
//
