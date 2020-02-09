#include "pch.h"
#include <iostream>
#include <stdio.h>
#include "Stack.h"
#include <math.h>
#include "DStack.h"

#define DOT '.'

void skipSpaces(); //pomijanie spacji przy wczytywaniu
double getNum(); //laczenie charow w liczbe
int isDigit(char c); //sprawdzanie czy znak jest liczba
char getOper(); //pobranie operatorow
int isOper(char cOper); //sprawdzanie czy znak jest operatorem
int prior(char cOper); //warunek priorytetu
double Calc(double arg1, double arg2, char cOperator);			//nasz kalkulator liczacy wartość											 
double ONP();
//void isMin(StackItem** pStack, DStackItem** dStack, double d, char c);


int main(int argc, char* argv[])
{
	printf("Podaj wyrazenie: ");
	printf("\n\n %0.2lf", ONP());

	return 0;
}

void skipSpaces()
{
	char c;
	while ((c = getchar()) == ' '); //przechodzimy przez wszystkie spacje
	ungetc(c, stdin); //trafilismy w koncu na znak inny od spacji-->zwracamy go na stdin,by go nie utracic
}

double getNum()
{
	unsigned char c;
	double num = 0;
	int sign = 0;
	skipSpaces();
	if ((c = getchar()) == '+' || c == '-')
	{
		if (c == '-') sign = -1; //liczba ujemna
	}
	else {
		ungetc(c, stdin);
	}

	while (isDigit(c = getchar()))	//petla trwa dopoki isdigit bedzie zczytywac cyfry																
		num = num * 10 + (c - '0');					//zczytujemy cyfry w ASCII i schematem hornera tworzymy z nich inty
	if (c == DOT)																		//warunek zmiennoprzecinkowy
	{
		double coef = 0.1;																	//mnoznik zmiennoprzecinkowo
		while (isDigit(c = getchar()))														//kontrola czy znak jest liczba
		{
			num += ((int)c - (int)'0') * coef;
			coef *= 0.1; //przesuwanie przecinka
		}
	}
	ungetc(c, stdin);
	return (sign) ? -num : num;								//zwracamy naszego double'a ze znakiem (-1 przekonwertuje na true)
}



int isDigit(char c)
{
	return (c >= '0') && (c <= '9');
}

char getOper()
{
	skipSpaces();
	return getchar();
}

int isOper(char cOper)
{
	switch (cOper)
	{
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '^': return 1;
	}
	return 0;
}

int prior(char cOper)
{
	switch (cOper)
	{
	case '+':
	case '-': return 1;
	case '*':
	case '/': return 2;
	case '^': return 3;
	}
	return 0;
}

double ONP()
{
	char c;
	StackItem* pStack = NULL;
	makeEmptyStack(&pStack);
	DStackItem* pDStack = NULL;
	dmakeEmptyStack(&pDStack);
	if ( (c = getOper() ) == '-')																//rozwazamy przypadek,w ktorym minus jest pierwszym znakiem
	{
		push(&pStack, c);
		dpush(&pDStack, 0); //mozna byloby cos pokombinowac z getnumem,ale wywali jeden warunek:-num+num
		//pushujemy na stos operatorow minusa,nie mozemy operowac na pustym stosie			
	}
	else ungetc(c, stdin);	//jesli nie ma minusa musimy zwrocic na stdin
	
	while (( c = getOper() ) == '(')															//wyrazenie moze zaczac sie od dowolnej ilosci nawiasow otwierajacych: ((5+3)+2)
	{
		push(&pStack, c);																//wrzucamy na stos operatorow nawias
		if ( (c = getOper() ) == '-')															// trzeba sprawdzic,czy kolejny operator nie jest minusem(przypadek naprzemienny) (-(-(
		{
			push(&pStack, c);
			dpush(&pDStack, 0); 
		}
		else
		{
			ungetc(c, stdin);																//jesli znak nie jest minusem trzeba go zwrocic na stdin (moze byc kolejnym nawiasem)
		}
	}
	ungetc(c, stdin);																		 //po przejsciu przez petle w koncu trafilismy na znak inny od operatorw,wiec zwracamy go na stdin
	dpush(&pDStack, getNum());																//wrzucamy pierwsza liczbe na stos
	while (isOper(c = getOper()))															//sprawdzamy,czy nastepny znak jest operatorem
	{
		if (c == '(')																		//ponawiamy sytuacje z gory i sprawdzamy przypadki wielokrotynch nawiasow i naprzemiennych
		{
			push(&pStack, c);															
			c = getOper();
			if (c == '-')														//piatek rynek 20	 
			{
				push(&pStack, c);															
				dpush(&pDStack, getNum());
				c = getOper(); 
				ungetc(c, stdin);
				if (c != '(')																//musimy sprawdzic czy mamy rzeczywiscie naprzemienne nawiasy,ze wzgledu na:
				{                                                                             // np liczba*(-liczba)
					dpush(&pDStack, getNum());											//jesli jest taka sytuacja to musimy zgarnac liczbe ze znakiem  i wrzucic na stos 
				}																			
			}
			else if (c == '(')																//inny przypadek to kolejny otwierajcy nawias,a wiec warunek naprzemiennosci
			{
				ungetc(c, stdin);															//musimy go zwrocic,zeby kontynuowal nam petle
			}
			else
			{
				ungetc(c, stdin);															//gdy przeslismy juz przez wszystkie przypadki,wiemy ze znak nie jest operatorem
				dpush(&pDStack, getNum());													//skoro to nie operator jest to liczba,a wiec wrzucimy ja na stos liczb
			}
			continue;																		//skoro mamy liczbe to wracamy na czubek petli i ponownie sprawdzamy 
		}
		else if (c == ')') 											//udało się w końcu dojsc na zamykajacego nawiasu,wiec zaczynamy przymierzac sie do liczenia w nawiasach
		{
			
			while ((c = pop(&pStack)) != '(')												//zrzucamy wszystko ze stosu operatorow dopoki nie trafimy na nawias konczacy
			{
				double arg2 = dpop(&pDStack);												//sciagamy liczbe i przypisujemy do argumentu	
				dpush(&pDStack, Calc(dpop(&pDStack), arg2, c));							//wykonujemy calciem dzialania i wrzucamy wynik na stos
			}
			continue;             //wracamy na gore z powrotem
		}
		while (prior(c) <= prior(top(pStack)))												//petla,ktora sprawdza czy mozna wrzucic opeator na stos
		{
			double arg2 = dpop(&pDStack);													//zrzucamy liczbe z gory
			dpush(&pDStack, Calc(dpop(&pDStack), arg2, pop(&pStack)));						//wyliczamy wartosc dla dwoch liczb z gory,z operatorem,a nastepnie wynik wrzucamy na stos 
		}																					
		push(&pStack, c);														// wrzucamy na stos operatorow wczytanego operarota,gdybysmy usuneli oper. o wyzszym prior.
		if ((c = getOper()) != '(')															//sprawdzamy,czy kolejny znak nie nowym nawiasem
		{
			ungetc(c, stdin);																
			dpush(&pDStack, getNum());														//to musi byc liczba!
		}
		else
		{
			ungetc(c, stdin);																//jesli to nawias to wracamy na poczatek petli i kontynujemy operacje
		}
	}
	while (!isEmpty(pStack))																//mamy juz wszystko uporzadkowane,liczymy do oproznienia stosu
	{
		double arg2 = dpop(&pDStack);														//pobieramy argument z gory
		dpush(&pDStack, Calc(dpop(&pDStack), arg2, pop(&pStack)));							//wyliczamy wartosc dla dwoch liczb z gory,z operatorem,a nastepnie wynik wrzucamy na stos 
	}																						
	return dpop(&pDStack);																	//po oproznieniu stosu operatorow w koncu został nam naz ostatn stos liczbowego-wynik!
}

double Calc(double arg1, double arg2, char cOperator)
{
	switch (cOperator)
	{
	case '+': return arg1 + arg2;
	case '-': return arg1 - arg2;
	case '*': return arg1 * arg2;
	case '/': if (fabs(arg2) > 1e-14) return arg1 / arg2;
		cout << "Error: division by 0!!\n";
		break;
	case '^': return pow(arg1, arg2);
	}
	return 0;
}

/*void isMin(StackItem** pStack, DStackItem** dStack, double d, char c) {
	push(pStack, c);
	dpush(dStack, d);
} */

