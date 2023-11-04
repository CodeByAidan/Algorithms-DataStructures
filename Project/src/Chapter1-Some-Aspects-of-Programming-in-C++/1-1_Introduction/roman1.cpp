/*
 * Demonstration:
 * Enter a decimal number: 1999
 * Roman: MCMXCIX
 */

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
using namespace std;

class Roman {
private:
	enum { L = 100 };
public:
	Roman(unsigned n);
	char a[L];
};

Roman::Roman(unsigned n)
{
	int v[] = { 1000, 900, 500, 400, 100, 90, 50,
	40, 10, 9, 5, 4, 1 }, len = sizeof(v) / sizeof(*v);
	const char* r[] = { "M", "CM", "D", "CD", "C", "XC", "L",
		"XL", "X", "IX", "V", "IV", "I" };
	unsigned number = n; strcpy(a, "");
	for (int i = 0; i < len; i++)
	{
		while (v[i] <= n)
		{
			if (strlen(a) + strlen(r[i]) >= L)
			{
				cout << "Number too large.\n"; exit(1);
			}
			strcat(a, r[i]);
			n -= v[i];
		}
	}
}

//int main()
//{
//	unsigned n;
//	cout << "Enter a decimal number: ";
//	cin >> n;
//	cout << "Roman: " << Roman(n).a << endl;
//	return 0;
//}