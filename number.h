#pragma once

#include "base.h"
#include "boolean.h"
#include "char.h"
#define SCAST_NUMBER(x) static_cast<Number*>(x)
class Char;

class Number : public Base {
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
		COMPLEX = 3
	} type_;
	Number(){}
	virtual ~Number(){}
	virtual Number *convert(Number *number2) = 0;
	virtual Number *add(Number *number2)  = 0;
	virtual Number *sub(Number *number2)  = 0;
	virtual Number *mul(Number *number2)  = 0;
	virtual Number *div(Number *number2)  = 0;
	
	virtual Number *abs()=0; //real
	virtual Number *floor()=0; //real
	virtual Number *ceiling()=0; //real
	virtual Number *truncate()=0; //real
	virtual Number *round()=0; //real
	
	virtual Number *quotient(Number *number2)=0; //integer
	virtual Number *remainder(Number *number2)=0; //integer
	virtual Number *modulo(Number *number2)=0; //integer
	virtual Number *gcd(Number *number2)=0;  //rational
	virtual Number *lcm(Number *number2)=0;
	virtual Number *expt(Number *number2)=0; //number
	virtual Number *sqrt()=0; //number

	virtual Number *minn(Number *number2)=0;  //real
	virtual Number *maxx(Number *number2)=0;
	virtual Number *inexact_exact()=0;  //number
	virtual Number *exact_inexact()=0;

	virtual Number *real_part()=0; //number
	virtual Number *imag_part()=0;
	virtual Number *numerator()=0; //rational
	virtual Number *denominator()=0;
	
	virtual Base *judge_integer() = 0;
	virtual Base *judge_rational() = 0;
	virtual Base *judge_real() = 0;
	virtual Base *judge_complex() = 0;
	virtual Base *judge_number() = 0;
	
	virtual Base *judge_less(Number *number2) = 0;
	virtual Base *judge_eless(Number *number2) = 0;
	virtual Base *judge_greater(Number *number2) = 0;
	virtual Base *judge_egreater(Number *number2) = 0;
	virtual Base *judge_exact() = 0;
	virtual Base *judge_inexact() = 0;
	virtual Base *judge_zero() = 0;
	virtual Base *judge_negative() = 0;
	virtual Base *judge_positive() = 0;
	virtual Base *judge_odd() = 0;
	virtual Base *judge_even() = 0;
	
	virtual Number *sinn() = 0;
	virtual Number *coss() = 0;
	virtual Number *tann() = 0;
	virtual Number *asinn() = 0;
	virtual Number *acoss() = 0;
	virtual Number *atann() = 0;
	virtual Number *expp() = 0;
	virtual Number *logg() = 0;
	
	virtual Number *make_rectangular(Number *number2) = 0;
	virtual Number *make_polar(Number *number2) = 0;
	virtual Number *magnitude() = 0;
	virtual Number *angle() = 0;
	
	virtual Base *judge_char() = 0;
	virtual Base *judge_string() = 0;
	
	virtual Base *integer_char() = 0;
	virtual Base *make_string(Char *char2) = 0;
	
	virtual Base *judge_equal(Number *number2) = 0;
	
	virtual Base *number_string() = 0;

	virtual void print(std::ostream& o = std::cout) const = 0;
	virtual int judge_sign() = 0;
};
