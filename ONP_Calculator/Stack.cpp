#include "pch.h"
#include "Stack.h"
void makeEmptyStack(StackItem** pStack)														
{
	while (!isEmpty(*pStack)) del(pStack);												
	(*pStack) = NULL;																			
}

void push(StackItem** pStack, char c)
{
	StackItem* p = (StackItem*)malloc(sizeof(StackItem));									
	if (p)   																		
	{
		p->cKey = c;
		p->pNext = *pStack;																		
		*pStack = p;																			
	}
	//!!!
}

char pop(StackItem** pStack)
{
	char c = top(*pStack);																		
	if (c)
		del(pStack);																		
	else
		cout << "\n\n *!* Stack underflow!! (POP) \n\n";
	return c;
}

char top(StackItem* pStack)
{
	if (!isEmpty(pStack))																	
		return pStack->cKey;																	
	return 0;
}

void del(StackItem** pStack)
{
	if (!isEmpty(*pStack))
	{
		StackItem* p = *pStack;																	
		*pStack = p->pNext;																		
		free(p);																				
	}
	else
		cout << "\n *!* Stack underflow!! ( DEL )\n\n";											
}

int isEmpty(StackItem* pStack)
{
	return !pStack;																			
}



