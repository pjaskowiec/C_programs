#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <stdio.h>

int CreateMatrix( double*** pTab, int nSize ); 
void DeleteMatrix( double*** pTab, int nSize ); 
void TransMatrix( double** pTab, int nDim ); 
void InverseMatrix( double** pInv, double** pTab, int nSize, double det ); 
double Det( double** pTab, int nSize ); 
void LayoutEquation( double** pInv, double* pB, double* pRes, int nSize ); 
#endif