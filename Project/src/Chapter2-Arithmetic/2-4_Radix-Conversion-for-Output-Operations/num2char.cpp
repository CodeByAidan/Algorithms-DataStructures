/*
 * Demonstration:
 * 12345 iNumOut(s, 12345, 5)
 *  -234 iNumOut(s, -234, 5)
 *  3.46 fNumOut(s, 3.45678, 5, 2)
 *  0.00 fNumOut(s, 0, 5, 2)
 *  1100 iNumOut(s, 12, 5, 2)
 *  -11. fNumOut(s, -3, 5, 0, 2)
 *  0.11 fNumOut(s, 0.75, 5, 2, 2)
 *  1.00 fNumOut(s, 0.99999, 5, 2, 2)
 */
// num2char: Converting numbers to character strings.
#include <iostream>
#include <math.h>
using namespace std;

int iNumOut(char *a, int x, int width, int radix=10)
{   // This function places the digits of x (possibly preceded
	// by blanks and/or a minus sign) in
	// a[0], a[1], ..., a[width - 1], and
	// '\0' in a[width] (so at least width + 1 positions
	// should be available in a).
	// Return value: 0 (= OK), or 1 (= width too small).
	int i=0, r, neg = x < 0;
	for (i=0; i<width; i++) a[i] = ' ';
	a[width] = '\0';
	if (neg) x = -x; else
	if (x == 0 && width > 0) {a[width-1] = '0'; return 0;}
	// i == width
	do
	{   r = x % radix;
		if (--i < 0) return 1;
		a[i] = '0' + r;
		x /= radix;
	}   while (x);
	if (neg)
	{   if (--i < 0) return 1; else a[i] = '-';
	}
	return 0;
}

int fNumOut(char *a, double x, int width, int precision,
	int radix=10)
{   int i, PeriodDone = 0, neg = x < 0;
	double radixpower = 1, q;
	if (neg) x = -x;
	for (i=0; i<precision; i++) radixpower *= radix;
	for (i=0; i<width; i++) a[i] = ' ';
	a[width] = '\0';
	x = x * radixpower + 0.5;
	i = width;
	do
	{   if (i == width - precision)
		{   if (i > 0) a[--i] = '.'; else return 1;
			PeriodDone = 1;
		}
		q = floor(x/radix);
		if (i > 0) a[--i] = '0' + int(x - radix * q);
			else return 0;
		x = q;
	}  while (x > 0 || !PeriodDone);
	if (neg)
	{   if (i > 0) a[--i] = '-'; else return 1;
	}
	return 0;
}

int main()
{   char s[20];
	if (iNumOut(s, 12345, 5) == 0)
		cout << s << " iNumOut(s, 12345, 5)\n";
	if (iNumOut(s, -234, 5) == 0)
		cout << s << " iNumOut(s, -234, 5)\n";
	if (iNumOut(s, -456, 3) == 0)   // Width insufficient:
		cout << s << " iNumOut(s, -456, 3)\n"; // no output.
	if (fNumOut(s, 3.45678, 5, 2) == 0)
		cout << s << " fNumOut(s, 3.45678, 5, 2)\n";
	if (fNumOut(s, 0, 5, 2) == 0)
		cout << s << " fNumOut(s, 0, 5, 2)\n";
	if (iNumOut(s, 12, 5, 2) == 0)
		cout << s << " iNumOut(s, 12, 5, 2)\n";
	if (fNumOut(s, -3, 5, 0, 2) == 0)
		cout << s << " fNumOut(s, -3, 5, 0, 2)\n";
	if (fNumOut(s, 0.75, 5, 2, 2) == 0)
		cout << s << " fNumOut(s, 0.75, 5, 2, 2)\n";
	if (fNumOut(s, 0.99999, 5, 2, 2) == 0)
		cout << s << " fNumOut(s, 0.99999, 5, 2, 2)\n";
	return 0;
}