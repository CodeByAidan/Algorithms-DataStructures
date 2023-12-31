/*
 * Demonstration:
 * Enter nonzero numbers, the last one
 * followed by 0:
 * 1 2 3 4 5 6 7 8 9 10 20 30 40
 * The following 13 nonzero numbers have been read:
 * 1 2 3 4 5 6 7 8 9 10 20 30 40
 */
// chunk: Variable number of float numbers stored.

#include <iostream>

using namespace std;

const int ChunkSize = 4; // May be larger in practice

class list {
public:
	list() { LEN = ChunkSize; a = new float[LEN]; len = 0; }
	~list() { delete[] a; }
	void AddItem(float x); // Defined below
	float& operator[](unsigned i)
	{	if (i >= len){cout << "Out of bounds. \n"; exit(1); }
		return a[i];
	}
	int GetLen()const { return len; }
private:
	int len;
	int LEN; // Logical and physical lengths
	float* a;
};

void list::AddItem(float x)
{	if (len == LEN)
	{	float *aOld = a;
		a = new float[LEN += ChunkSize];
		for (int i=0; i<len; i++) a[i] = aOld[i];
		delete[] aOld;
	}
	a[len++] = x;
}

int main()
{	list L;
	float x;
	int n;
	cout << "Enter nonzero numbers, the last one\n"
			"followed by 0:\n";
	while (cin >> x, x != 0) L.AddItem(x);
	n = L.GetLen();
	cout << "The following " << n <<
			" nonzero numbers have been read:\n";
	for (int i = 0; i < n; i++) cout << L[i] << " ";
	cout << endl;
	return 0;
}