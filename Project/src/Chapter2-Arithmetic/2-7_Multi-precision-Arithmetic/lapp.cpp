// lapp: A simple application of class 'large' for
//   arithmetical operations on very large integers
//   (to be linked with large.cpp).
#include <iostream>
#include "large.h"

using namespace std;

int main()
{   large a = "987654321012345",
		  b =        "55544433", sum, dif, prod,
		  quot, rem;
	sum = a + b;
	dif = a - b;
	prod = a * b;
	quot = a / b;
	rem = a % b;
	cout << a << " + " << b << " = " << sum << endl;
	cout << a << " - " << b << " = " << dif << endl;
	cout << a << " * " << b << " = " << prod << endl;
	cout << a << " / " << b << " = " << quot << endl;
	cout << a << " % " << b << " = " << rem << endl;
	return 0;
}