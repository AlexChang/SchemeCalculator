// string.cpp
#include "string.h"
#include "number.h"
#include "rational.h"
#include "float.h"
#include "complex.h"
#include "ito.h"
#include <cstring>
#include <string>
#include <iostream>

String::String(std::string s){
	str=s;
	len=s.length();
	btype_=STRING;
}

String::~String(){}

String *String::from_string(char *expression){
	if(expression[0]=='"') {
		std::string tmp="";
		int i=1;
		while(expression[i]!='"'){
			tmp+=expression[i++];
		}
		return new String(tmp);
	}
	else return NULL;
}

Base *String::judge_integer(){
	return new Boolean(false);
}

Base *String::judge_rational(){
	return new Boolean(false);
}

Base *String::judge_real(){
	return new Boolean(false);
}

Base *String::judge_complex(){
	return new Boolean(false);
}

Base *String::judge_number(){
	return new Boolean(false);
}

Base *String::judge_char(){
	return new Boolean(false);
}

Base *String::judge_string(){
	return new Boolean(true);
}

Base *String::s_string(Char *char2){
	std::string tmp=str;
	tmp+=char2->cha;
	return new String(tmp);
}
Base *String::string_length(){
	Rational *res;
	res=new Rational(LongInt(len),LongInt(1));
	return res;
}
Base *String::string_ref(Number *number2){
	assert(number2->type_==1&&"Not nonnegative integer");
	assert(SCAST_RATIONAL(number2)->denominator_==LongInt(1)&&SCAST_RATIONAL(number2)->judge_sign()!=-1&&"Not nonnegative integer");
	int tmp=(int)SCAST_RATIONAL(number2)->numerator_;
	Char *res;
	char ctmp;
	assert(tmp>=0&&tmp<len&&"index is out of range");
	ctmp=str[tmp];
	res=new Char(ctmp);
	return res;
}

Base *String::subtring(Number *number2){
	assert(number2->type_==1&&"Not nonnegative integer");
	assert(SCAST_RATIONAL(number2)->denominator_==LongInt(1)&&SCAST_RATIONAL(number2)->judge_sign()!=-1&&"Not nonnegative integer");
	int tmp=(int)SCAST_RATIONAL(number2)->numerator_;
	String *res;
	std::string stmp="";
	assert(tmp>=0&&tmp<=len&&"index is out of range");
	stmp=str.substr(tmp);
	res =new String(stmp);
	return res;
}
Base *String::substring_two(Number *number2, Number *number3){
	assert(number2->type_==1&&"Not nonnegative integer");
	assert(number3->type_==1&&"Not nonnegative integer");
	assert(SCAST_RATIONAL(number2)->denominator_==LongInt(1)&&SCAST_RATIONAL(number2)->judge_sign()!=-1&&"Not nonnegative integer");
	assert(SCAST_RATIONAL(number3)->denominator_==LongInt(1)&&SCAST_RATIONAL(number3)->judge_sign()!=-1&&"Not nonnegative integer");
	int tmp=(int)SCAST_RATIONAL(number2)->numerator_;
	int tmp2=(int)SCAST_RATIONAL(number3)->numerator_;
	String *res;
	std::string stmp="";
	assert(tmp>=0&&tmp<=len&&"index is out of range");
	assert(tmp2>=tmp&&tmp<=len&&"index is out of range");
	stmp=str.substr(tmp,tmp2-tmp);
	res =new String(stmp);
	return res;
}

Base *String::s_string_append_one(){
	String *res;
	std::string stmp="";
	stmp+=str;
	res=new String(stmp);
	return res;
}
Base *String::s_string_append(String *string2){
	String *res;
	std::string stmp="";
	stmp+=str;
	stmp+=string2->str;
	res=new String(stmp);
	return res;
}

Base *String::s_string_copy(){
	String *res;
	std::string stmp="";
	stmp+=str;
	res=new String(stmp);
	return res;
}

Base *String::judge_stringless(String *string2){
	return new Boolean(str<string2->str);
}
Base *String::judge_string_ciless(String *string2){
	if(len==0){
		if(string2->len==0) return new Boolean(false);
		else return new Boolean(true);
	}
	else if(string2->len==0) return new Boolean(false);
	int minlen,i;
	if(len<string2->len) minlen=len;
	else minlen=string2->len;
	char p,q;
	bool flag=true,flag2=false;
	for(i=0; i<minlen; ++i){
		p=str[i];
		q=string2->str[i];
		if(p-'A'>=0&&p-'Z'<=0) p=p-'A'+'a';
		if(q-'A'>=0&&q-'Z'<=0) q=q-'A'+'a';
//		std::cout << i << ' ' << flag << std::endl;
		if(p>q) flag=false;
		else if(p<q){
			flag2=true;
			break;
		}
		else continue;
		if(flag=false) break;
	}
	if(i==minlen&&!flag2){
		if(len>minlen) flag=false;
		else if(len==minlen&&string2->len==minlen) flag=false;
	}
//	std::cout << flag << std::endl;
	return new Boolean(flag);
}

Base *String::judge_stringeless(String *string2){
	return new Boolean(str<=string2->str);
}
Base *String::judge_string_cieless(String *string2){
	if(len==0){
		return new Boolean(true);
	}
	else if(string2->len==0) return new Boolean(false);
	int minlen,i;
	if(len<string2->len) minlen=len;
	else minlen=string2->len;
	char p,q;
	bool flag=true,flag2=false;
	for(i=0; i<minlen; ++i){
		p=str[i];
		q=string2->str[i];
		if(p-'A'>=0&&p-'Z'<=0) p=p-'A'+'a';
		if(q-'A'>=0&&q-'Z'<=0) q=q-'A'+'a';
//		std::cout << i << ' ' << flag << std::endl;
		if(p>q){
			flag=false;
			break;
		}
		else if(p<q){
			flag2=true;
			break;
		}
		else continue;
	}
	if(i==minlen&&!flag2){
		if(len>minlen) flag=false;
		else flag=true;
	}
//	std::cout << flag << std::endl;
	return new Boolean(flag);
}
Base *String::judge_stringequal(String *string2){
	return new Boolean(str==string2->str);
}
Base *String::judge_string_ciequal(String *string2){
	if(len!=string2->len) return new Boolean(false);
	char p,q;
	bool flag=true;
	for(int i=0; i<len; ++i){
		p=str[i];
		q=string2->str[i];
		if(p-'A'>=0&&p-'Z'<=0) p=p-'A'+'a';
		if(q-'A'>=0&&q-'Z'<=0) q=q-'A'+'a';
//		std::cout << i << ' ' << flag << std::endl;
		if(p!=q){
			flag=false;
			break;
		}
	}
//	std::cout << flag << std::endl;
	return new Boolean(flag);
}

Base *String::judge_equal(String *string2){
	return new Boolean(str==string2->str);
}

Base *String::string_number(){
	Number *res;
	try{
//		std::cout << '*' << std::endl;
		res=new Rational(fromString<Rational>(str));
//		std::cout << '*' << std::endl;
	}
	catch(int){
		try{
			res=new Float(fromString<Float>(str));
		}
		catch(int){
			try{
				res=new Complex(fromString<Complex>(str));
			}
			catch(int){
				throw 0;
			}
			return res;
		}
		return res;
	}
	return res;
}

void String::print(std::ostream& o)const{
	o << "\"" << str << "\"";
}

	
