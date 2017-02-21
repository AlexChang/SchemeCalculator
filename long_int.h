// long_int.h

#include <iostream>

#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)<(y)?(x):(y))

class LongInt {
public:
	
	int *a;
	int len=0;
	int mlen=500;
	bool sign;
	
	LongInt Radd(const LongInt &long_int2) const;
	LongInt Rmin(const LongInt &long_int2) const;
	LongInt Rmul(const LongInt &long_int2) const;
	LongInt Rdiv(const LongInt &long_int2) const;
	
	LongInt(int number = 0);
	LongInt(long long number);
	LongInt(const char* s);
	LongInt(const LongInt &long_int2);
	~LongInt(){delete [] a;};

	operator bool();
	operator double();
	operator int();
	bool operator!=(const LongInt &long_int2) const;
	bool operator<(const LongInt &long_int2) const;
	bool operator==(const LongInt &long_int2) const;
	bool abscmp(const LongInt &long_int2) const;
	LongInt &operator=(const LongInt &long_int2);
	LongInt operator+(const LongInt &long_int2) const;
	LongInt operator-(const LongInt &long_int2) const;
	LongInt operator*(const LongInt &long_int2) const;
	LongInt operator/(const LongInt &long_int2) const;
	LongInt operator%(const LongInt &long_int2) const;
	
	friend LongInt gcdd(LongInt &long_int1, LongInt &long_int2);
	friend LongInt lcmm(LongInt &long_int1, LongInt &long_int2);
	friend LongInt max(const LongInt &long_int1, const LongInt &long_int2);
	friend LongInt min(const LongInt &long_int1, const LongInt &long_int2);
	friend std::ostream & operator<<(std::ostream &os, const LongInt &obj);
	void print(std::ostream& o = std::cout)const;
	void double_space();
	void clean();

	int number_;
};
