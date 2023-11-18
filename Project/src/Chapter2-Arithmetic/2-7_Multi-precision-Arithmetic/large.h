// large.h: Multi-precision integer arithmetic.
#include <iostream>

using namespace std;
typedef unsigned int uint;

class large {
public:
	large(const char *str);
	large(int i);
	large(uint i=0);
	large(long i);
	large(const large &v);
	~large(){delete[]p;}
	friend large operator+(large x, const large &y);
	friend large operator-(large x, const large &y);
	friend large operator*(large x, const large &y);
	friend large operator/(large x, const large &y);
	friend large operator%(large x, const large &y);
	friend large operator<<(large u, uint k);
	friend large operator>>(large u, uint k);
	large operator-()const;
	large &operator=(const large &v);
	large &operator+=(const large &v);
	large &operator-=(const large &v);
	large &operator*=(int y);
	large &operator*=(large y);
	large &operator/=(const large &divisor);
	large &operator%=(const large &divisor);
	large &operator<<=(uint k);
	large &operator>>=(uint k);
	friend int operator==(const large &x, const large &y)
		{return x.compare(y)==0;}
	friend int operator!=(const large &x, const large &y)
		{return x.compare(y)!=0;}
	friend int operator<(const large &x, const large &y)
		{return x.compare(y) < 0;}
	friend int operator>(const large &x, const large &y)
		{return x.compare(y) > 0;}
	friend int operator<=(const large &x, const large &y)
		{return x.compare(y)<=0;}
	friend int operator>=(const large &x, const large &y)
		{return x.compare(y)>=0;}
	friend ostream &operator<<(ostream &os, const large &v);
	friend istream &operator>>(istream &is, large &v);
	friend large power(large x, uint n);
	friend large sqrt(const large &x);
	friend large abs(const large &x);
private:
	uint *p;
	int len, Len, neg; // len in use, Len allocated
	void IncrLen(int lenNew);
	int RoundUp(int i)const;
	void SetLen(uint n);
	void reduce();
	void MakeLarge(uint i);
	int compare(const large &y)const;
	void DDproduct(uint A, uint B, uint &Hi, uint &Lo)const;
	uint DDquotient(uint A, uint B, uint d)const;
	void subtractmul(uint *a, uint *b, int n, uint &q)const;
	int normalize(large &denom, large &num, int &x)const;
	void unnormalize(large &rem, int x, int SecondDone)const;
	void divide(large denom,
	   large &quot, large &rem, int RemDesired)const;
	friend class numstring;
};