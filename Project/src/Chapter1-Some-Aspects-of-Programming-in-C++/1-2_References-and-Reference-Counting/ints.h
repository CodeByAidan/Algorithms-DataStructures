// ints.h: Dynamic arrays based on referenced coutning.

#include <iostream>

class ints {
public:
	ints()
	{	pRep = new intsrep;
		pRep->p = nullptr;
		pRep->length = pRep->refcount = 1;
	}

	ints(int* a, int n);	// Defined in ints.cpp

	ints(const ints &r)
	{	r.pRep->refcount++;
		pRep = r.pRep;
	}

	~ints()
	{	if (--pRep->refcount == 0)
		{	delete[] pRep->p;
			delete pRep;
		}
	}

	ints &operator=(const ints &r)
	{	r.pRep->refcount++;
		if (--pRep->refcount == 0)
		{	delete[] pRep->p;
			delete pRep;
		}
		pRep = r.pRep;
		return *this;
	}
	int len()const {return pRep->length;}
private:
	struct intsrep {int* p;
		int length;
		int refcount;} *pRep;
};