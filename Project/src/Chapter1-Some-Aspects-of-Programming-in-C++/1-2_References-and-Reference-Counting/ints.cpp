// ints.cpp: Implementation of class ints.
#include "ints.h"

ints::ints(int *a, int n)
{	pRep = new intsrep;
	pRep->p = new int[n];
	for (int i=0; i<n; i++) pRep->p[i] = a[i];
	pRep->length = n;
	pRep->refcount = 1;
}