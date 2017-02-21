// boolean.h
#pragma once
#include "base.h"

#define SCAST_BOOLEAN(x) static_cast<Boolean*>(x)

class Boolean : public Base{
public:
	bool flag;
	
	Boolean(bool f=true);
	~Boolean();

	virtual Base *judge_integer();
	virtual Base *judge_rational();
	virtual Base *judge_real();
	virtual Base *judge_complex();
	virtual Base *judge_number();
	virtual Base *judge_char();
	virtual Base *judge_string();
	virtual Base *judge_equal(Boolean *boolean2);
	
	virtual void print(std::ostream& o = std::cout)const;
	
	static Boolean *from_string(char *expression);


};

