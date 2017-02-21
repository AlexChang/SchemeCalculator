// complex.h
#pragma once
#include "rational.h"
#include "float.h"
#include "number.h"
#include "char.h"
#include "string.h"
#include <iostream>

#define SCAST_COMPLEX(x) static_cast<Complex*>(x)

class Complex : public Number {
private:
	Number *real_;
	Number *imag_;
	bool ise;	
	
public:
	Complex(Number *real, Number *imag);
	Complex(char* rstr="0", char* istr="0");
	Complex(const Complex &obj);
	virtual ~Complex();

	void judge();
	Complex *inexact();
	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	
	virtual Number *abs();
	virtual Number *floor();
	virtual Number *ceiling();
	virtual Number *truncate();
	virtual Number *round();
	
	virtual Number *quotient(Number *number2);
	virtual Number *remainder(Number *number2);
	virtual Number *modulo(Number *number2);
	virtual Number *gcd(Number *number2);
	virtual Number *lcm(Number *number2);
	virtual Number *expt(Number *number2);
	virtual Number *sqrt();
	
	virtual Number *numerator();
	virtual Number *denominator();
	virtual Number *real_part();
	virtual Number *imag_part();
	

	virtual Number *minn(Number *number2);
	virtual Number *maxx(Number *number2);
	virtual Number *inexact_exact();
	virtual Number *exact_inexact();
	
	virtual Base *judge_integer();
	virtual Base *judge_rational();
	virtual Base *judge_real();
	virtual Base *judge_complex();
	virtual Base *judge_number();
	
	virtual Base *judge_less(Number *number2);
	virtual Base *judge_eless(Number *number2);
	virtual Base *judge_greater(Number *number2);
	virtual Base *judge_egreater(Number *number2);
	virtual Base *judge_exact();
	virtual Base *judge_inexact();
	virtual Base *judge_zero();
	virtual Base *judge_negative();
	virtual Base *judge_positive();
	virtual Base *judge_odd();
	virtual Base *judge_even();
	
	virtual Number *sinn();
	virtual Number *coss();
	virtual Number *tann();
	virtual Number *asinn();
	virtual Number *acoss();
	virtual Number *atann();
	virtual Number *expp();
	virtual Number *logg();
	
	virtual Number *make_rectangular(Number *number2);
	virtual Number *make_polar(Number *number2);
	virtual Number *magnitude();
	virtual Number *angle();
	
	virtual Base *judge_char();
	virtual Base *judge_string();
	
	virtual Base *integer_char();
	virtual Base *make_string(Char *char2);
	
	virtual Base *judge_equal(Number *number2);
	
	virtual Base *number_string();
	
	friend std::ostream & operator<<(std::ostream &os, const Complex &obj);
	friend std::istream & operator>>(std::istream &is, Complex &obj);
	
	virtual void print(std::ostream& o = std::cout)const;
	virtual int judge_sign();
	static Complex *from_string(const char *expression);


};

