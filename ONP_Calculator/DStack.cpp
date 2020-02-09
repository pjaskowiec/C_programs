#include "pch.h"
#include "DStack.h"
#include <stdlib.h>
using namespace std;

void dmakeEmptyStack(DStackItem** pStack)
{
	while (!isDEmpty(*pStack)) ddel(pStack);													//USUWA WSZYSTKIE ELEMENTY KTORE SA NA STOSIE
	*pStack = NULL;																				//ZMIENIA WSKAZNIK NA NULL

}

void dpush(DStackItem** pStack, double x)
{
	DStackItem* p = (DStackItem*)malloc(sizeof(DStackItem));									//MALLOC REZERWUJE NOWY OBSZAR W PAMIECI 
	if (p)   																					//DEFINICJA NOWEGO WSKAZNIKA P 
	{
		p->fKey = x;
		p->pNext = *pStack;																		//PRZYPISUJEMY WSKAZNIKOWI PNEXT WSKAZNIK PSTACK KTORY WSKAZUJE NA WCZESNIEJSZY ELEMENT
		*pStack = p;																			//PRZYPISUJEMY WSKAZNIKOWI PSTACK WSKAZNIK P KTORY WSKAZUJE NA NOWO UTWORZONY ELEMEN
	}
}

double dpop(DStackItem** pStack)																// PARAMETR WE/WY
{
	double x = dtop(*pStack);																	 // PRZEKAZUJEMY TO NA CO WSKAZUJE PSTACK
	if (!isDEmpty(*pStack))
		ddel(pStack);																			 //USUWAMY ORGINAL CZYLI PSTACK
	else
		cout << "\n\n *!* Stack underflow!! (dpop) \n\n";
	return x;
}

double dtop(DStackItem* pStack)
{
	if (!isDEmpty(pStack))																		//SPRAWDZAMY CZY STOS NIE JEST PUSTY															
		return pStack->fKey;																	//JESLI NIE JEST TO ZWRACAMY WARTOSC GORNEGO ELEMENTU
	cout << "\n\n *!* Stack underflow!! (dtop) \n\n";
	return 0;
}

void ddel(DStackItem** pStack)
{
	if (!isDEmpty(*pStack))
	{
		DStackItem* p = *pStack;														 //PODPINAMY CO CHCEMY USUNAC
		*pStack = p->pNext;																 //PRZYPISUJEMY WSKAZNIK PSTACK(NA GORE STOSU) NA WCZESNIEJSZY ELEMENT
		free(p);																		 //CZYSCIMY PAMIEC (CLEAR W C++)
	}
	else
		cout << "\n *!* Stack underflow!! ( ddel )\n\n";								 //WYPISANIE BLEDU JESLI STOS JEST PUSTY
}

int isDEmpty(DStackItem* pStack)
{
	return !pStack;																		//SPRAWDZMY CZY STOS JEST PUSTY
}