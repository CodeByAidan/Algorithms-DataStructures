// ints0.h: Dynamic arrays without reference counting.
#include <cstddef>

class ints {
public:
	ints(){p = NULL; length = 0;}
	ints(int* a, int n);
	ints(const ints& r);
	~ints(){delete[]p;}
	ints &operator=(const ints& r);
	int len()const {return length;}
private:
	int* p;
	int length;
};