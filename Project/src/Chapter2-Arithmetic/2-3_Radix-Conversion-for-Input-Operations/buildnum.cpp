/*
 * Demonstration:
 * 5482     5482
 * 7		15
 * 123.457  0.875
 * 123      123
 */
// buildnum: Building numbers out of characters
#include <iostream>

using namespace std;

int iNumIn(const char *a, int radix=10)
{   int s=0, i=0, d;
	while ((d = a[i++] - '0') >= 0 && d < radix)
		s = radix * s + d;
	return s;
}

double fNumIn(const char *a, int radix=10)
{   int i=0, d;
	double s=0, PowerOfRadix=1;
	while ((d = a[i++] - '0') >= 0 && d < radix)
		s = radix * s + d;
	if (a[i-1] == '.')
	while ((d = a[i++] - '0') >= 0 && d < radix)
	{   PowerOfRadix *= radix;
		s += d/PowerOfRadix;
	}
	return s;
}

int main() {
	cout << iNumIn("5482") << "     " << iNumIn("5482", 10)
	     << endl;
	cout << iNumIn("111", 2) << "     " << iNumIn("17", 8)
	     << endl;
	cout << fNumIn("123.4567") << "     " << fNumIn(".111", 2)
	     << endl;
	cout << fNumIn("123.") << "     " << fNumIn("123")
	     << endl;
	return 0;
}