/*
 * Demonstration:
 * Enter a Roman numeral: VIXLMVV
 * Illegal character.
 */
#include <ctype.h>

#include <iomanip>
#include <iostream>
#include <map>
#include <regex>

using namespace std;

class __attribute__((unused)) FromRoman {
public:
	__attribute__((unused)) explicit FromRoman(const string& s);
	int number;

private:
	static int val(char ch) ;
};

__attribute__((unused)) FromRoman::FromRoman(const string& s) {
	number = 0;
	regex romanRegex(
		R"(^(M{0,3})(C(?:D|M)|D?C{0,3})(X(?:L|C)|L?X{0,3})(I(?:V|X)|V?I{0,3})$)");

	if (!regex_match(s, romanRegex)) {
		cout << "Invalid Roman numeral.\n";
		exit(1);
	}

	int i = 0;
	int si;
	int si1;
	while (i < s.length()) {
		si = val(s[i]);
		if (i + 1 < s.length() && (si1 = val(s[i + 1])) > si) {
			number = number + si1 - si;
			i += 2;
		}
		else {
			number += si;
			i++;
		}
	}
}

int FromRoman::val(char ch) {
	static const map<char, int> romanMap = { {'M', 1000}, {'D', 500}, {'C', 100},
											{'L', 50},   {'X', 10},  {'V', 5},
											{'I', 1} };

	char upperCh = toupper(ch);
	auto it = romanMap.find(upperCh);
	if (it != romanMap.end()) {
		return it->second;
	}
	cout << "Illegal character.\n";
	exit(1);
}

int main() {
	string str;
	cout << "Enter a Roman numeral: ";
	cin >> str;
	cout << "Value: " << FromRoman(str).number << endl;
	return 0;
}
