// large.cpp: Multi-precision integer arithmetic.
#ifdef _MSC_VER
#include <strstrea.h>
#else
#include <strstream>
#endif
#include <iomanip>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include "large.h"
#define max(x, y) ((x) > (y) ? (x) : (y))
const uint uintmax = UINT_MAX;
const int MemUnit=64; // Use multiples of MemUnit words
const int wLen = sizeof(uint) * 8; // Number of bits
const int hLen = wLen/2;
const uint rMask = (1 << hLen) - 1;
const uint lMask = uintmax - rMask;
const uint lBit = uintmax - (uintmax >> 1);

void large::IncrLen(int lenNew)
{   int lenOld = len, i;
	len = lenNew;   // len > lenOld
	if (len > Len)
	{   Len = RoundUp(len);
		uint *pOld = p;
		p = new uint[Len];
		for (i=0; i<lenOld; i++) p[i] = pOld[i];
		delete[]pOld;
	}
	for (i=lenOld; i<len; i++) p[i] = 0;
}

int large::RoundUp(int i)const // Find suitable new block size
{   return ((i + i/3) / MemUnit + 1) * MemUnit;
}

void large::SetLen(uint n)
{   len = n;
	if (len > Len)
	{   Len = RoundUp(len);
		delete[]p; p = new uint[Len];
	}
}

void large::reduce()
{   for (int i=len-1; i>=0; i--)
		if (p[i] == 0) len--; else break;
	if (len == 0) neg = 0;
}

void large::MakeLarge(uint i)
{   Len = MemUnit;
	p = new uint[Len]; *p = i;
	len = i != 0;
}