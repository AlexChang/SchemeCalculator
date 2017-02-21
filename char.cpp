// char.cpp
#include "char.h"
#include "boolean.h"
#include "rational.h"
#include "number.h"
#include "string.h"
#include <cstring>
#include <string>
#include <iostream>

Char::Char(char c){
	cha=c;
	btype_=CHAR;
}

Char::Char(char c, int s){
	cha=c;
	spe=s;
	btype_=CHAR;
}

Char::~Char(){}

Char *Char::from_string(char *expression){
	if(strncmp(expression,"#\\",2)==0) return new Char(expression[2]);
	else return NULL;
}

Base *Char::judge_integer(){
	return new Boolean(false);
}

Base *Char::judge_rational(){
	return new Boolean(false);
}

Base *Char::judge_real(){
	return new Boolean(false);
}

Base *Char::judge_complex(){
	return new Boolean(false);
}

Base *Char::judge_number(){
	return new Boolean(false);
}

Base *Char::judge_char(){
	return new Boolean(true);
}

Base *Char::judge_string(){
	return new Boolean(false);
}

Base *Char::judge_charless(Char *char2){
	return new Boolean(cha<char2->cha);
}

Base *Char::judge_chareless(Char *char2){
	return new Boolean(cha<=char2->cha);
}

Base *Char::judge_charciless(Char *char2){
	char p,q;
	p=cha;
	q=char2->cha;
	if(p-'A'>=0 && p-'Z'<=0) p=p-'A'+'a';
	if(q-'A'>=0 && q-'Z'<=0) q=q-'A'+'a';
	return new Boolean(p<q);
}

Base *Char::judge_charcieless(Char *char2){
	char p,q;
	p=cha;
	q=char2->cha;
	if(p-'A'>=0 && p-'Z'<=0) p=p-'A'+'a';
	if(q-'A'>=0 && q-'Z'<=0) q=q-'A'+'a';
	return new Boolean(p<=q);
}

Base *Char::judge_char_alphabetic(){
	return new Boolean((cha>='A'&&cha<='Z')||(cha>='a'&&cha<='z'));
}

Base *Char::judge_char_numeric(){
	return new Boolean(cha>='0'&&cha<='9');
}

Base *Char::judge_char_whitespace(){
	return new Boolean(cha==' ');
}

Base *Char::judge_char_upper_case(){
	return new Boolean(cha>='A'&&cha<='Z');
}

Base *Char::judge_char_lower_case(){
	return new Boolean(cha>='a'&&cha<='z');
}

Number *Char::char_integer(){
	int tmp;
	tmp=(int)cha;
	Rational *res;
	res=new Rational(LongInt(tmp),LongInt(1));
	return res;
}

Base *Char::char_upcase(){
	char tmp;
	tmp=cha;
	if(tmp-'a'>=0&&tmp-'z'<=0) tmp=tmp-'a'+'A';
	return new Char(tmp);
}
Base *Char::char_downcase(){
	char tmp;
	tmp=cha;
	if(tmp-'A'>=0&&tmp-'Z'<=0) tmp=tmp-'A'+'a';
	return new Char(tmp);
}

Base *Char::s_string_one(){
	String *res;
	std::string tmp="";
	tmp+=cha;
	res=new String(tmp);
	return res;
}
Base *Char::s_string(Char *char2){
	String *res;
	std::string tmp="";
	tmp+=cha;
	tmp+=char2->cha;
	res=new String(tmp);
	return res;
}

Base *Char::judge_charequal(Char *char2){
	Boolean *res;
	res=new Boolean(cha==char2->cha);
	return res;
}
Base *Char::judge_char_ciequal(Char *char2){
	Boolean *res;
	char p,q;
	p=cha;
	q=char2->cha;
	if(p-'A'>=0&&p-'Z'<=0) p=p-'A'+'a';
	if(q-'A'>=0&&q-'Z'<=0) q=q-'A'+'a';
	res=new Boolean(p==q);
	return res;
}

Base *Char::judge_equal(Char *char2){
	return new Boolean(cha==char2->cha);
}

void Char::print(std::ostream& o)const{
	if(cha==' ') o << "#\\space";
	else if(cha=='\n') o << "#\\return";
	else if(cha=='\t') o << "#\\tab";
	else o << "#\\" << cha;
}

	
