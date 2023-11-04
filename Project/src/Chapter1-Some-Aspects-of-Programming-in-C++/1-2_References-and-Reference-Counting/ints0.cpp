// ints0.cpp: Implementation of class ints0
//    (preliminary version: no reference counting).

#include "ints0.h"

ints0::ints0(int* a, int n)
{	p = new int[n];
	for (int i=0; i<n; i++)
		p[i] = a[i];
	length = n;
}

ints0::ints0(const ints0& r)
{	length = r.length;
	p = new int[length];
	for (int i=0; i<length; i++)
		p[i] = r.p[i];
}

ints0 &ints0::operator=(const ints0 &r)
{
	if (&r != this)
	{	delete[] p;
		length = r.length;
		p = new int[length];
		for (int i=0; i<length; i++)
			p[i] = r.p[i];
	}
	return *this;
}