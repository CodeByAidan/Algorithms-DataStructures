/*
 * Demonstration:
 * Enter a sequence of positive integers followed by 0:
 * 1 2 3 4 5 6 7 8 9 10 20 30 40
 * 40 30 20 10 9 8 7 6 5 4 3 2 1
 */
#include <iostream>
#include "ReversePrint.h"

using namespace std;

int main() {
    cout << "Enter a sequence of positive integers followed by 0:\n";
    reversePrint(cin);
    cout << endl;
    return 0;
}