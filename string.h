// string.h
#pragma once
#include "base.h"
#include "boolean.h"
#include "char.h"
#include "rational.h"
#include "number.h"
#include <string>
#include <cassert>

#define SCAST_STRING(x) static_cast<String*>(x)

class String : public Base{
public:
	std::string str="";
	int len=str.length();
	
	String(std::string s);
	~String();
	
	virtual Base *judge_integer();
	virtual Base *judge_rational();
	virtual Base *judge_real();
	virtual Base *judge_complex();
	virtual Base *judge_number();
	virtual Base *judge_char();
	virtual Base *judge_string();
	
	virtual Base *s_string(Char *char2);
	virtual Base *string_length();
	virtual Base *string_ref(Number *number2);
	virtual Base *subtring(Number *number2);
	virtual Base *substring_two(Number *number2, Number *number3);
	
	virtual Base *s_string_append_one();
	virtual Base *s_string_append(String *string2);
	virtual Base *s_string_copy();
	
	virtual Base *judge_stringless(String *string2);
	virtual Base *judge_string_ciless(String *string2);
	virtual Base *judge_stringeless(String *string2);
	virtual Base *judge_string_cieless(String *string2);
	virtual Base *judge_stringequal(String *string2);
	virtual Base *judge_string_ciequal(String *string2);
	virtual Base *judge_equal(String *string2);
	virtual Base *string_number();
	
	virtual void print(std::ostream& o = std::cout)const;
	static String *from_string(char *expression);
};

