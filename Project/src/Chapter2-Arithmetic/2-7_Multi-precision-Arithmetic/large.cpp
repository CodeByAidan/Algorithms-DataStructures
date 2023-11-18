// large.cpp: Multi-precision integer arithmetic.
#ifdef __GNUG__
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

large::large(const char *str)
{   if (*str == '-'){neg = 1; str++; } else neg = 0;
	int n = strlen(str), i;
	large v=0;
	for (i=0; i<n; i++)
		v = v * 10 + (str[i] - '0');
	len = v.len; Len = RoundUp(len);
	p = new uint [Len];
	for (i=0; i<len; i++) p[i] = v.p[i];
	reduce();
}

large::large(int i)
{   neg = i < 0;
	if (neg) i = -i;
	MakeLarge(uint(i));
}

large::large(long L)
{   neg = L < 0;
	unsigned long UL = neg ? -L : L;
	MakeLarge(uint(UL));
#if LONG_MAX != INT_MAX
	len = 0;
	while (UL != 0)
	{   p[len++] = uint(UL & UINT_MAX);
		UL >>= wLen;
	}
#endif
}

large::large(uint i)
{   neg = 0; MakeLarge(i);
}

large::large(const large &v)
{   len = v.len; Len = v.Len; neg = v.neg;
	p = new uint[Len];
	for (int i=0; i<len; i++) p[i] = v.p[i];
}

large operator+(large x, const large &y){return x+=y;}
large operator-(large x, const large &y){return x-=y;}
large operator*(large x, const large &y){return x*=y;}
large operator/(large x, const large &y){return x/=y;}
large operator%(large x, const large &y){return x%=y;}
large operator<<(large u, uint k){return u <<= k;}
large operator>>(large u, uint k){return u >>= k;}

large large::operator-()const
{   large v = *this; v.neg = !v.neg; return v;
}

large &large::operator=(const large &y)
{   if (this != &y)
	{	SetLen(y.len); neg = y.neg;
		for (int i=0; i<len; i++) p[i] = y.p[i];
	}
	return *this;
}

large &large::operator+=(const large &y)
{   if (neg != y.neg) return *this -= -y;
	int i;
	uint d, carry = 0;
	IncrLen(max(y.len, len) + 1);
	for (i=0; i<len; i++)
	{	if (i >= y.len && carry == 0) break;
		d = p[i] + carry;
		carry = d < carry;
		if (i < y.len)
		{	p[i] = d + y.p[i];
			if (p[i] < d) carry = 1;
		}   else p[i] = d;
	}
	reduce();
	return *this;
}

large &large::operator-=(const large &y) {
	if (neg != y.neg) return *this += -y;
	if (!neg && y > *this || neg && y < *this)
		return *this = -(y - *this);
	int i, borrow = 0;
	uint d;
	for (i=0; i<len; i++ )
	{	if (i >= y.len && borrow == 0 ) break;
		d = p[i] - borrow;
		borrow = d > p[i];
		if (i < y.len)
		{   p[i] = d - y.p[i];
			if (p[i] > d) borrow = 1;
		}   else p[i] = d;
	}
	reduce();
	return *this;
}

large &large::operator*=(int y)
{	int len0 = len;
	uint Hi, Lo, dig = p[0], carry = 0, b = abs(y);
	IncrLen(len + 1);
	for (int i=0; i<len0; i++)
	{   DDproduct(dig, b, Hi, Lo);
		p[i] = Lo + carry;
		dig = p[i+1];
		carry = Hi + (p[i] < Lo);
	}
	p[len0] = carry;
	reduce();
	if (y < 0) neg = !neg;
	return *this;
}

large &large::operator*=(large y)
{   // if(*this == 0 || y == 0) return *this = 0;
	if (len == 0 || y.len == 0) return *this = 0;
	int DifSigns = neg != y.neg;
	if (len + y.len == 2) {
		uint a = p[0], b = y.p[0];
		if (((a | b) & lMask) == 0)
		{   p[0] = a * b;
			len = 1;
		}   else
		{   DDproduct(a, b, p[1], p[0]);
			len = (p[1] != 0 ? 2 : (p[0] != 0));
		}
		neg = DifSigns;
		return *this;
	}
	if (len == 1)   //  && y.len > 1
	{	uint digit = p[0]; *this = y;
		*this *= digit;
	}   else
	if (y.len == 1 ) {
		*this *= y.p[0];
	}   else
	{   int lenProd = len + y.len, i, jA, jB;
		uint sumHi = 0, sumLo, Hi, Lo,
		sumLoOld, sumHiOld, carry=0;
		large x = *this;
		SetLen(lenProd); // Give *this length lenProd
		for (i=0; i<lenProd; i++)
		{   sumLo = sumHi; sumHi = carry; carry = 0;
			for (jA=0; jA<x.len; jA++)
			{   jB = i - jA;
				if (jB >=0 && jB < y.len)
				{   DDproduct(x.p[jA], y.p[jB], Hi, Lo);
					sumLoOld = sumLo; sumHiOld = sumHi;
					sumLo += Lo;
					if (sumLo < sumLoOld ) sumHi++;
					sumHi += Hi;
					carry += (sumHi < sumHiOld);
				}
			}
			p[i] = sumLo;
		}
	}
	reduce();
	neg = DifSigns;
	return *this;
}

large &large::operator/=(const large &divisor)
{   large r;
	divide(divisor, *this, r, 0);
	return *this;
}

large &large::operator%=(const large &divisor)
{	large q;
	divide(divisor, q, *this, 1);
	return *this;
}

large &large::operator<<=(uint k) {
	int q = k / wLen;
	if (q) // Increase len by q:
	{   int i;
		IncrLen(len + q);
		for (i=len-1; i>=0; i--)
			p[i] = (i < q ? 0 : p[i - q]);
		k %= wLen;
	}
	if (k) // 0 < k < wLen:
	{   int k1 = wLen - k;
		uint mask = (1 << k ) - 1;
		IncrLen(len + 1);
		for (int i=len-1; i>=0; i--)
		{   p[i] <<= k;
			if (i > 0)
				p[i] |= ( p[i-1] >> k1 ) & mask;
		}
	}
	reduce();
	return *this;
}

large &large::operator>>=(uint k) {
	int q = k / wLen;
	if (q >= len) {len = 0; return *this;}
	if (q)
	{   for (int i=q; i<len; i++) p[i-q] = p[i];
		len -= q;
		k %= wLen;
		if (k == 0) {reduce(); return *this;}
	}
	int n = len - 1, k1 = wLen - k;
	uint mask = (1 << k) - 1;
	for (int i=0; i<=n; i++)
	{   p[i] >>= k;
		if (i < n)
			p[i] |= ((p[i+1] & mask ) << k1);
	}
	reduce();
	return *this;
}

int large::compare(const large &y)const
{   if (neg != y.neg) return y.neg - neg;
	int code = 0;
	if (len == 0 || y.len == 0) code = len - y.len; else
	if (len < y.len) code = -1; else
	if (len > y.len) code = +1; else
	for (int i = len - 1; i >= 0; i--)
	{	if (p[i] > y.p[i]) {code = 1; break;} else
		if (p[i] < y.p[i]) {code = -1; break;}
	}
	return neg ? -code : code;
}

void large::DDproduct(uint A, uint B,
					  uint &Hi, uint &Lo)const
// Multiplying two digits: (Hi, Lo) = A * B
{   uint hiA = A >> hLen, loA = A & rMask,
		 hiB = B >> hLen, loB = B & rMask,
		 mid1, mid2, old;
	Lo = loA * loB; Hi = hiA * loB;
	mid1 = loA * hiB; mid2 = hiA * loB;
	old = Lo;
	Lo += mid1 << hLen; Hi += (Lo < old) + (mid1 >> hLen);
	old = Lo;
	Lo += mid2 << hLen; Hi += (Lo < old) + (mid2 >> hLen);
}

uint large::DDquotient(uint A, uint B, uint d)const 
// Divide double word (A, B) by d. Quotient = (qHi, qLo)
{	uint left, middle, right, qHi, qLo, x, dLo1,
	   dHi = d >> hLen, dLo = d & rMask;
	qHi = A/(dHi + 1 );
	// This initial guess of qHi may be too small.
	middle = qHi * dLo;
	left = qHi * dHi;
	x = B - (middle << hLen);
	A -= (middle >> hLen) + left + (x > B); B = x;
	dLo1 = dLo << hLen;
	// Increase qHi if necessary:
	while (A > dHi || (A == dHi && B >= dLo1))
	{	x = B - dLo1; A -= dHi + (x > B); B = x; qHi++;
	}
	qLo = ((A << hLen) | (B >> hLen))/(dHi + 1);
	// This initial guess of qLo may be too small.
	right = qLo * dLo; middle = qLo * dHi;
	x = B - right; A -= (x > B); B = x;
	x = B - (middle << hLen); A -= (middle >> hLen) + (x > B);
	B = x;
	// Increase qLo if necessary:
	while (A || B >= d) 
	{	x = B - d; A -= (x > B); B = x; qLo++;
	}
	return (qHi << hLen) + qLo;
}

void large::subtractmul(uint *a, uint *b, int n,
	uint &q)const 
// a -= q * b: b in n positions; correct q if necessary
{	uint Hi, Lo, d, carry = 0;
	int i;
	for (i=0; i<n; i++)
	{	DDproduct(b[i], q, Hi, Lo);
		d = a[i];
		a[i] -= Lo;
		if (a[i] > d) carry++;
		d = a[i + 1];
		a[i + 1] -= Hi + carry;
		carry = a[i + 1] > d;
	}
	if (carry) // q was too large
	{	q--;  carry = 0;
		for (i=0; i<n; i++) 
		{	d = a[i] + carry;
			carry = d < carry;
			a[i] = d + b[i];
			if (a[i] < d) carry = 1;
		}
		a[n] = 0;
	}
}

int large::normalize(large &denom, large &num, int &x)const 
{	int r = denom.len - 1;
	uint y = denom.p[r]; x = 0;
	while ((y & lBit) == 0){y <<= 1; x++;}
	denom <<= x; num <<= x;
	if (r > 0 && denom.p[r] < denom.p[r-1]) 
	{	denom *= uintmax; num *= uintmax;
		r++; return 1;
	}
	return 0;
}

void large::unnormalize(large &rem, int x, int SecondDone)const
{	if (SecondDone) rem /= uintmax;
	if (x > 0) rem >>= x; else rem.reduce();
}

void large::divide(large denom,
	large &quot, large &rem, int RemDesired)const
{	if (denom.len == 0) {cout << "Zero divide.\n"; exit(1);}
	int QuotNeg = neg ^ denom.neg, RemNeg = neg,
		i, r = denom.len - 1, SecondDone = 0, x = 0, n;
	uint q, d;
	large num = *this;
	num.neg = denom.neg = 0;
	if (num < denom) 
	{	quot = 0; rem = num; rem.neg = RemNeg; return;
	}
	if (denom.len == 1 && num.len == 1) 
	{	quot = uint(num.p[0]/denom.p[0]);
		rem = uint(num.p[0]%denom.p[0]);
		quot.neg = QuotNeg; rem.neg = RemNeg;
		return;
	}	else
	if (denom.len == 1 && (denom.p[0] & lMask) == 0) 
	{	// Denominator fits into a half word
		uint divisor = denom.p[0], dHi = 0,
			q1, r, q2, dividend;
		quot.SetLen(len);
		for (int i=len-1; i>=0; i--) 
		{	dividend = (dHi << hLen ) | (p[i] >> hLen);
			q1 = dividend/divisor; r = dividend % divisor;
			dividend = (r << hLen) | (p[i] % rMask);
			q2 = dividend/divisor; dHi = dividend % divisor;
			quot.p[i] = (q1 << hLen) | q2;
		}
		quot.reduce(); rem = dHi;
		quot.neg = QuotNeg; rem.neg = RemNeg;
		return;
	}
	large num0 = num, denom0 = denom;
	SecondDone = normalize(denom, num, x);
	r = denom.len - 1; n = num.len - 1;
	quot.SetLen(n - r);
	for (i=quot.len-1; i>=0; i--) quot.p[i] = 0;
	rem = num;
	if (rem.p[n] >= denom.p[r])
	{	rem.IncrLen(rem.len + 1); n++;
		quot.IncrLen(quot.len + 1);
	}
	d = denom.p[r];
	for (int k=n; k>r; k--)
	{	q = DDquotient(rem.p[k], rem.p[k-1], d);
		subtractmul(rem.p + k - r - 1, denom.p, r + 1, q);
		quot.p[k - r - 1] = q;
	}
	quot.reduce(); quot.neg = QuotNeg;
	if (RemDesired) 
	{	unnormalize(rem, x, SecondDone);
		rem.neg = RemNeg;
	}
}

large power(large x, uint n)
{	large y=1;
	while (n) 
	{	if (n & 1) y *= x;
		x *= x;
		n >>= 1;
	}
	return y;
}

class numstring {
public:
	numstring(large v);
	~numstring(){delete[]pStr;}
	char *pStr;
};

numstring::numstring(large v) 
{	int len = int(long(v.len) * wLen / 3) + 1, n = len, i = 0;
									// 1/3 > ln(2)/ln(10)
	static uint p10 = 1, ip10 = 0;
	pStr = new char[len];
	if (v.len == 0) {*pStr = '0'; i = 1;} else
	{	uint r;
		if (p10 == 1) 
		{	while (p10 <= UINT_MAX/10) 
			{	p10 = 10 * p10;
				ip10++;
			}
		}					 // p10 is max uint power of 10
		large R, LP10 = p10; // LP10 = p10 = pow(10, ip10)
		if (v.neg) {*pStr = '-'; i = 1;}
		do 
		{	v.divide(LP10, v, R, 1);
			r = (R.len ? R.p[0] : 0);
			for (uint j=0; j<ip10; j++) 
			{	pStr[--n] = char(r % 10 + '0');
				r /= 10;
				if (r + v.len == 0) break;
			}
		}	while (v.len);
		while (n < len)
			pStr[i++] = pStr[n++];
	}
	pStr[i] = '\0';
}

ostream &operator<<(ostream &os, const large &v) 
{	numstring numstr(v);
	int i=0;
	char ch;
	while ((ch = numstr.pStr[i]) != '\0') 
	{	os << ch;
		i++;
	}
	return os;
}

istream &operator>>(istream &is, large &v) 
{	const uint blocksize = 1024;
	uint maxlen = blocksize;
	char* str = new char[maxlen], *str0, ch;
	v = 0;
	uint i = 0;
	is >> ch;
	if (ch == '-' || isdigit(ch))
	{	str[i++] = ch;
		while(is.get(ch), isdigit(ch))
		{	if (i == maxlen - 1)
			{	str0 = str; str[maxlen - 1] = '\0';
				maxlen += blocksize;
				str = new char[maxlen]; strcpy(str, str0);
				delete[]str0;
			}
			str[i++] = ch;
		}
		str[i] = '\0';
		v = large(str);
		delete[]str;
	}
	is.putback(ch);
	return is;
}

large sqrt(const large &a)
{	large x = a, b = a, q;
	b <<= 1;
	while (b >>= 2, b > 0)
		x >>= 1;
	while (x > (q = a/x) + 1 || x < q - 1) 
	{	x += q;
		x >>= 1;
	}
	return x < q ? x : q;
}

large abs(const large &a) 
{	if (a.neg) {large b = a; b.neg = 0; return b;}
	return a;
}