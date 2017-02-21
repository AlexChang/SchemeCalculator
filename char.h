// char.h
#pragma once
#include "base.h"
#include "number.h"

#define SCAST_CHAR(x) static_cast<Char*>(x)
class Number;

class Char : public Base{
public:
	char cha;
	int spe=0;
	
	Char(char c);
	Char(char c, int spe);
	~Char();
	
	virtual Base *judge_integer();
	virtual Base *judge_rational();
	virtual Base *judge_real();
	virtual Base *judge_complex();
	virtual Base *judge_number();
	virtual Base *judge_char();
	virtual Base *judge_string();
	
	virtual Base *judge_charless(Char *char2);
	virtual Base *judge_chareless(Char *char2);
	virtual Base *judge_charciless(Char *char2);
	virtual Base *judge_charcieless(Char *char2);
	virtual Base *judge_char_alphabetic();
	virtual Base *judge_char_numeric();
	virtual Base *judge_char_whitespace();
	virtual Base *judge_char_upper_case();
	virtual Base *judge_char_lower_case();
	virtual Number *char_integer();
	virtual Base *char_upcase();
	virtual Base *char_downcase();
	virtual Base *s_string_one();
	virtual Base *s_string(Char *char2);
	virtual Base *judge_charequal(Char *char2);
	virtual Base *judge_char_ciequal(Char *char2);
	virtual Base *judge_equal(Char *char2);

	
	virtual void print(std::ostream& o = std::cout)const;
	static Char *from_string(char *expression);
};

