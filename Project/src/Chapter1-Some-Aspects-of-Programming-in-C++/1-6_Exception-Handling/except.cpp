/*
 * Demonstration:
 * See what happens if, somewhere in the input,
 * you type some incorrect character.
 * Enter 10 integers:
 * 0 9 8 7 6 5 4 3 2 1
 * 10 integers read. Average: 4.5
 * Enter 12 integers:
 * 1 2 3 x
 * Only 3 integers read due to incorrect input.
 * End of program.
 */
// except: Program demonstrating exception handling.
#include <iostream>

using namespace std;

float ReadIntArray(int *p, int n)
{	float sum = 0;
	cout << "Enter " << n << " integers:\n";
	for (int i = 0; i < n; i++)
	{	cin >> p[i];
		if (cin.fail()) throw i;
		sum += p[i];
	}
	return sum / n;
}

int main()
{	float avg;
	int a[10];
	int b[12];
	cout << "See what happens if, somewhere in the input,\n"
			"you type some incorrect character.\n";
	try
	{	avg = ReadIntArray(a, 10);
		cout << "10 integers read. Average: " << avg << endl;
		avg = ReadIntArray(b, 12);
		cout << "12 integers read. Average: " << avg << endl;
	}
	catch (int k)
	{	cout << "Only " << k << " integers read "
			"due to incorrect input.\n";
	}
	cout << "End of program.\n";
	return 0;
}