// boolean.cpp
#include "boolean.h"
#include <cstring>
#include <iostream>

Boolean::Boolean(bool f){
	flag=f;
	btype_=BOOLEAN;
}

Boolean::~Boolean(){}

Boolean *Boolean::from_string(char *expression){
	if(strcmp(expression,"#t")==0) return new Boolean(true);
	else if(strcmp(expression,"#f")==0) return new Boolean(false);
	else return NULL;
}

Base *Boolean::judge_integer(){
	return new Boolean(false);
}

Base *Boolean::judge_rational(){
	return new Boolean(false);
}

Base *Boolean::judge_real(){
	return new Boolean(false);
}

Base *Boolean::judge_complex(){
	return new Boolean(false);
}

Base *Boolean::judge_number(){
	return new Boolean(false);
}

Base *Boolean::judge_char(){
	return new Boolean(false);
}
Base *Boolean::judge_string(){
	return new Boolean(false);
}
Base *Boolean::judge_equal(Boolean *boolean2){
	return new Boolean(flag==boolean2->flag);
}

void Boolean::print(std::ostream& o)const{
	if(flag) o << "#t";
	else o << "#f";
}

	
