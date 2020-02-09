#ifndef _KNIGHT
#define _KNIGHT
#include <iostream>
#include <memory.h>
#include <Windows.h>
#include <cstdlib>
#define HORSEMOVES 8 //skoczek poruszy sie na 8 sposobow
#define BOARD_SIZE 6

typedef enum { FIRST, SECOND, THIRD, FOURTH, FIFTH, SIXTH, SEVENTH, EIGHT } moveNum; //tablica wyliczeniowa

typedef struct tagPoint
{
	int x0;
	int y0;
}Point;




int** Creator( int nDim );
int Movement( int** pChessBoard, int nDim, int target, int x, int y, int* px, int* py, Point* pHorseMoves );
int root( int** pChessBoard, int nDim, int moveNo, int x, int y, Point* pHorseMoves );
void Remover( int*** pChessBoard );

#endif 
