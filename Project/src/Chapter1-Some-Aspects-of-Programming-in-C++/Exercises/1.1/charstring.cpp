/*
 * Demonstration:
 * Smith
 * Smith Smith
 * Smith Johnson Smith Smith
 */
// Application, to be linked with charstring.cpp.
#include "charstring.h"

int main() {
	charstring s("Smith ");
	charstring t = s;
	charstring u = t + s;
	s = t + charstring("Johnson ") + u;
	std::cout << t << std::endl << u << std::endl << s << std::endl;
	return 0;
}