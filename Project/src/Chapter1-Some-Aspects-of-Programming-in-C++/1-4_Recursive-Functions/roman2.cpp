// roman2: Evaluating a Roman numeral.

//#include <iostream>
//#include <iomanip>
//#include <stdlib.h>
//#include <ctype.h>
//
//using namespace std;
//
//class FromRoman {
//public:
//	FromRoman(const char* s);
//	int number;
//private:
//	int val(char ch);
//};
//
//FromRoman::FromRoman(const char *s)
//{	number = 0;
//	int i = 0, si, si1;
//	while (s[i])
//	{	si = val(s[i]);
//		if (s[i+1] && (si1 = val(s[i+1])) > si)
//		{	number = number + si1 - si;
//			i += 2;
//		}	else
//		{	number += si;
//			i++;
//		}
//	}
//}
//
//int FromRoman::val(char ch)
//{	switch(toupper(ch))
//	{	case 'M': return 1000;
//		case 'D': return 500;
//		case 'C': return 100;
//		case 'L': return 50;
//		case 'X': return 10;
//		case 'V': return 5;
//		case 'I': return 1;
//	}
//	cout << "Illegal character.\n"; exit(1);
//	return 0;
//}

//int main()
//{	char str[100];
//	cout << "Enter a Roman numeral: ";
//	cin >> setw(100) >> str;
//	cout << "Value: " << FromRoman(str).number << endl;
//	return 0;
//}