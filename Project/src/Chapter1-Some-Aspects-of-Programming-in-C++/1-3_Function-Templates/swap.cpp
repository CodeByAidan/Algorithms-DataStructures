/*
 * Demonstration:
 * i=8  j=5
 * January
 * April
 * P: (8, 2)
 * Q: (3, 4)
 */
// swap: Demonstration of a swap template.
#include <iostream>
using namespace std;

struct point{float x;
	float y;};

template <class T>
void mySwap(T& x, T& y)
{	T w = x; x = y; y = w;
}
int main()
{	int i = 5;
	int j = 8;
	const char *month1 = "April";
	const char *month4 = "January";
	point P = { 3, 4 };
	point Q = { 8, 2 };
	mySwap(i, j); // Two integers swapped
	mySwap(month1, month4); // Two pointers swapped
	mySwap(P, Q); // Two points swapped
	cout << "i=" << i << "  j=" << j << endl;
	cout << month1 << endl << month4 << endl;
	cout << "P: (" << P.x << ", " << P.y << ")\n";
	cout << "Q: (" << Q.x << ", " << Q.y << ")\n";
	return 0;
}