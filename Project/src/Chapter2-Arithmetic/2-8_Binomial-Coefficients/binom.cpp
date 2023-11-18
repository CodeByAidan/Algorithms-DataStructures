/*
 * Demonstration:
 * Enter the integers (n >= 0) and k: 250 200
 * 1347792027058843260910128541468884065586558699863725912545
 * 1347792027058843260910128541468884065586558699863725912545
 */
// binom: Binomials based on class large
//  (to be linked with large.cpp)
#include "large.h"

large binom1(int n, int k)
{   if (k < 0 || n < k) return 0;
	if (k > n/2) k = n - k;
	int idenom = 1, inum = n - k + 1;
	large num = inum, denom = idenom;
	while (idenom < k)
	{   num *= ++inum;
		denom *= ++idenom;
	}
	return num/denom;
}

large binom2(int n, int k) {
	if (k < 0 || k > n) return 0;
	if (k > n/2) k = n - k;
	large *a = new large[k + 1];
	int limit;
	a[0] = 1;
	for (int i=1; i<=n; i++)
	{   limit = k - (n - i) - 1;
		if (limit < 0) limit = 0;
		for (int j=k; j>limit; j--)
			a[j] += a[j-1];
	}
	large result = a[k];
	delete[] a;
	return result;
}

int main()
{   int n, k;
	do
	{   cout << "Enter the integers (n >= 0) and k: ";
		cin >> n >> k;
	}   while (n < 0);
	cout << binom1(n, k) << endl;
	cout << binom2(n, k) << endl;
	return 0;
}
