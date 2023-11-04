// ints0.h: Dynamic arrays without reference counting.
#pragma once
#include <cstddef>

class ints0 {
public:
	ints0() { p = NULL; length = 0; }
	ints0(int* a, int n);
	ints0(const ints0& r);
	~ints0() { delete[]p; }
	ints0& operator=(const ints0& r);
	int len()const { return length; }
private:
	int* p;
	int length;
};