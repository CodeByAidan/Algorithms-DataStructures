#include "ReversePrint.h"
#include <iostream>

using namespace std;

void reversePrint(istream& input) {
    int num;
    input >> num;

    if (num != 0) {
        reversePrint(input);
        cout << num << " ";
    }
}