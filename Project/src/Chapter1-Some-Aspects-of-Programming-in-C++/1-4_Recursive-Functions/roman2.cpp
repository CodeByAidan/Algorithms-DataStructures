/*
 * Demonstration:
 * Enter a Roman number: MCMXCIX
 * Value: 1999
 * Enter a Roman number: MIX
 * 1009
 */
// roman2: Evaluating a Roman numeral.

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

class __attribute__((unused)) FromRoman {
public:
	explicit FromRoman(const char* s);
	int number;
private:
	static int val(char ch) ;
};

FromRoman::FromRoman(const char *s)
{	number = 0;
	int i = 0;
	int si;
	int si1;
	while (s[i])
	{	si = val(s[i]);
		if (s[i+1] && (si1 = val(s[i+1])) > si)
		{	number = number + si1 - si;
			i += 2;
		}	else
		{	number += si;
			i++;
		}
	}
}

int FromRoman::val(char ch)
{	switch(toupper(ch))
	{	case 'M': return 1000;
		case 'D': return 500;
		case 'C': return 100;
		case 'L': return 50;
		case 'X': return 10;
		case 'V': return 5;
		case 'I': return 1;
		default: break;
	}
	cout << "Illegal character.\n"; exit(1);
}

int main()
{	char str[100];
	cout << "Enter a Roman numeral: ";
	cin >> setw(100) >> str;
	cout << "Value: " << FromRoman(str).number << endl;
	return 0;
}