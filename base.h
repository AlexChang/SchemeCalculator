// base.h
#pragma once
#include <iostream>

class Base{
public:
	enum{
		BOOLEAN = 1,
		NUMBER = 2,
		CHAR = 3,
		STRING = 4
	} btype_;
	Base(){}
	virtual ~Base(){}
	virtual void print(std::ostream& o = std::cout) const = 0;
	virtual Base *judge_integer() = 0;
	virtual Base *judge_rational() = 0;
	virtual Base *judge_real() = 0;
	virtual Base *judge_complex() = 0;
	virtual Base *judge_number() = 0;
	virtual Base *judge_char() = 0;
	virtual Base *judge_string() = 0;

};

