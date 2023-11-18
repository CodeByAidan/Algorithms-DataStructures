/*
 * Demonstration:
 * Enter two numbers: 5 0
 * Division by zero
 */
#include <iostream>
#include <stdexcept>

using namespace std;

int main()
{
	int a;
	int b;
	cout << "Enter two numbers: ";
	cin >> a >> b;
	try
	{
		if (b == 0) {
			throw runtime_error("Division by zero");
			cin.get();
			return 1;
		};
		cout << a << " / " << b << " = " << a / b << endl;
	}
	catch (runtime_error& err)
	{
		cout << err.what() << endl;
		cin.get();
		return 1;
	}
	return 0;
}
