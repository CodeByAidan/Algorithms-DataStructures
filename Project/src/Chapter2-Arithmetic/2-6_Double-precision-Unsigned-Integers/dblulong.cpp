// dblulong: Double-precision unsigned long arithmetic.
#include <iostream>
#include <iomanip>
#include <limits.h>
typedef unsigned long ulong;
using namespace std;

class ULONG {
public:
	friend ULONG operator+(const ULONG &x, const ULONG &y);
	ULONG(ulong u = 0){d[1] = 0; d[0]=u;}
	ulong d[2];
	friend ostream &operator<<(ostream &os, ULONG &u);
};

ULONG operator+(const ULONG &x, const ULONG &y)
{   ULONG s;
	s.d[0] = x.d[0] + y.d[0];
	s.d[1] = x.d[1] + y.d[1] + (s.d[0] < x.d[0]);
	return s;
}

ostream &operator<<(ostream &os, ULONG &u)
{   for (int i=1; i>=0; i--)
		os << hex << setw(2*sizeof(ulong)) << setfill('0')
		   << u.d[i] << " ";
	return os;
}

int main()
{   ULONG u1 = ULONG_MAX, u2, u4, u8;
	cout << "1 * ULONG_MAX: " << u1 << endl;
	cout << "2 * ULONG_MAX: " << (u2 = u1 + u1) << endl;
	cout << "4 * ULONG_MAX: " << (u4 = u2 + u2) << endl;
	cout << "8 * ULONG_MAX: " << (u8 = u4 + u4) << endl;
	return 0;
}