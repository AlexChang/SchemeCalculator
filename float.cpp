#include "float.h"
#include "rational.h"
#include "complex.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <cmath>
#include "ito.h"
#define ABS(x) ((x)<0?(-(x)):(x))

#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)<(y)?(x):(y))

Float::Float(double number) : number_(number){
	type_ = FLOAT;
	btype_ = NUMBER;
}

Float::Float(const Float &obj): number_(obj.number_){
	type_ = FLOAT;
	btype_ = NUMBER;
}

Float::~Float(){

}

Number *Float::convert(Number *number2){
//	std::cout << type_ << ' ' << number2->type_ << std::endl;
	assert(number2->type_ <= type_);
	Float *result = new Float();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->number_ = (double)tmp->numerator_ / (double)tmp->denominator_;
			// printf("%lf", result->number_);
			break;
		}
		case FLOAT:{
			Float *tmp = SCAST_FLOAT(number2);
			result->number_ = tmp->number_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	return result;
}

Number *Float::add(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ + tmp->number_);
	return result;
}

Number *Float::sub(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ - tmp->number_);
	return result;
}

Number *Float::mul(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ * tmp->number_);
	return result;
}

Number *Float::div(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	assert(ABS(tmp->number_)>1e-500 && "divide zero");
	Float *result = new Float(number_ / tmp->number_);
	return result;
}

void Float::print(std::ostream& o)const{
	o << std::setprecision(18) << number_ ;
}

Float *Float::from_string(const char *expression){
	char *separate_pos;
	separate_pos = strchr(expression,'i');
    if(separate_pos) return NULL;
    
    char *end_pointer;
    double val = strtod(expression, &end_pointer);
    if (end_pointer == expression || end_pointer != expression + strlen(expression))
	    return NULL;
    return new Float(val);
}

int Float::judge_sign(){
	if(number_ == 0) return 0;
	if(number_ > 0) return 1;
	return -1;
}

Number *Float::abs(){
	Float *result = new Float(std::abs(number_));
	return result;
}

Number *Float::floor(){
	Float *result = new Float(std::floor(number_));
	return result;
}

Number *Float::ceiling(){
	Float *result = new Float(std::ceil(number_));
	return result;
}

Number *Float::truncate(){
	Float *result = new Float(std::trunc(number_));
	return result;
}

Number *Float::round(){
	Float *result = new Float(std::round(number_));
	return result;
}

Number *Float::numerator(){
	assert(1!=1&&"Not Rational");
}

Number *Float::denominator(){
	assert(1!=1&&"Not Rational");
}

Number *Float::real_part(){
	Float *result = new Float(number_);
	return result;
}

Number *Float::imag_part(){
	Float *result = new Float(0.0);
	return result;
}

Number *Float::quotient(Number *number2){
	Float *result;
	Float *tmp = SCAST_FLOAT(number2);
	long long num1 = trunc(number_);
	long long num2 = trunc(tmp->number_);
	assert(num1==number_ && tmp->number_ == num2 && "Not Integer");
	result=new Float(num1/num2);
	return result;
}

Number *Float::remainder(Number *number2){
	Float *result;
	Float *tmp = SCAST_FLOAT(number2);
	long long num1 = trunc(number_);
	long long num2 = trunc(tmp->number_);
	assert(num1==number_ && tmp->number_ == num2 && "Not Integer");
	result=new Float(num1%num2);
	return result;
}

Number *Float::modulo(Number *number2){
	Float *result;
	Float *tmp = SCAST_FLOAT(number2);
	long long num1 = trunc(number_);
	long long num2 = trunc(tmp->number_);
	assert(num1==number_ && tmp->number_ == num2 && "Not Integer");
	if(judge_sign()==number2->judge_sign()){
		result=new Float(num1%num2);
	}
	else{
		result=new Float(num1%num2+num2);
	}
	
	return result;
}

Number *Float::gcd(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	if(judge_sign()==0&&tmp->judge_sign()==0) return new Float(0);
	if(judge_sign() == 0) return new Float(*tmp);
	if(tmp->judge_sign()==0) return new Float(*this);
	
	long long num1 = trunc(number_);
	long long num2 = trunc(tmp->number_);
	
	assert(num1==number_ && num2==tmp->number_ && "Not Rational");
	long long a,b,c;
	a = MAX(num1,num2);
	b = MIN(num1,num2);
	while(c=a%b){
		a = b;
		b = c;
	}
	return new Float(std::abs(b));
}

Number *Float::lcm(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	if(judge_sign() == 0 || tmp->judge_sign() == 0) return new Float(0);
	long long num1 = trunc(number_);
	long long num2 = trunc(tmp->number_);
	
	assert(num1==number_ && num2==tmp->number_ && "Not Rational");
	long long a,b,c;
	a = MAX(num1,num2);
	b = MIN(num1,num2);
	while(c=a%b){
		a = b;
		b = c;
	}
	return new Float(std::abs(num1*num2/b));	
}

Number *Float::expt(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result=new Float(std::pow(number_, tmp->number_));
	return result;
}

Number *Float::sqrt(){
//	std::cout << '*' << std::endl;
	if(judge_sign()==-1){
		Number *a,*b;
		a=new Float(0.0);
		b=new Float(std::sqrt(std::abs(number_)));
//		std::cout << '*' << std::endl;
		Complex *result=new Complex(a,b);
//		std::cout << '*' << std::endl;
		delete a,b;
		return result;
	}
	else{
		Float *result=new Float(std::sqrt(number_));
		return result;
	}
}


Number *Float::minn(Number *number2){
	if(sub(number2)->judge_sign()==1) return new Float(*SCAST_FLOAT(number2));
	else return new Float(*this);
}

Number *Float::maxx(Number *number2){
	if(sub(number2)->judge_sign()==-1) return new Float(*SCAST_FLOAT(number2));
	else return new Float(*this);
}

Number *Float::inexact_exact(){
	LongInt i(1);
	double middle=number_;
	while(trunc(middle) != middle){
		middle=middle*2;
		i=i*LongInt(2);
	}
//	for(i=2;i<pow(2,60);i=LongInt(2)){
//		middle = number_ * i;
//		if(trunc(middle) == middle) break;
//	}
	char *str=new char[1000];
	sprintf(str,"%.0f",middle);
	LongInt n = LongInt(str);
	delete str;
	return new Rational(n,i);
}

Number *Float::exact_inexact(){
	Float *result;
	result=new Float(*this);
	return result;
}

Base *Float::judge_integer(){
	if(trunc(number_) == number_) return new Boolean(true);
	return new Boolean(false);
}

Base *Float::judge_rational(){
	return new Boolean(true);
}

Base *Float::judge_real(){
	return new Boolean(true);
}
	
Base *Float::judge_complex(){
	return new Boolean(true);
}

Base *Float::judge_number(){
	return new Boolean(true);
}

Base *Float::judge_less(Number *number2){
	bool flag;
	Number *tmp = this;
	tmp = number2->sub(tmp);
	if(tmp->judge_sign() == 1) flag = true;
	else flag = false;
	delete tmp;
	return new Boolean(flag);
}

Base *Float::judge_eless(Number *number2){
	bool flag;
	Number *tmp = this;
	tmp = number2->sub(tmp);
	if(tmp->judge_sign() != -1) flag = true;
	else flag = false;
	delete tmp;
	return new Boolean(flag);
}

Base *Float::judge_greater(Number *number2){
	bool flag;
	Number *tmp = this;
	tmp = tmp->sub(number2);
	if(tmp->judge_sign() == 1) flag = true;
	else flag = false;
	delete tmp;
	return new Boolean(flag);
}

Base *Float::judge_egreater(Number *number2){
	bool flag;
	Number *tmp = this;
	tmp = tmp->sub(number2);
	if(tmp->judge_sign() != -1) flag = true;
	else flag = false;
	delete tmp;
	return new Boolean(flag);
}

Base *Float::judge_exact(){
	return new Boolean(false);
}

Base *Float::judge_inexact(){
	return new Boolean();
}

Base *Float::judge_zero(){
	if(judge_sign() == 0) return new Boolean(true);
	return new Boolean(false);
}

Base *Float::judge_negative(){
	if(judge_sign() == -1) return new Boolean(true);
	return new Boolean(false);
}

Base *Float::judge_positive(){
	if(judge_sign() == 1) return new Boolean(true);
	return new Boolean(false);
}

Base *Float::judge_odd(){
	assert(trunc(number_) == number_ && "Not Integer");
	if((long long)number_%2 == 1) return new Boolean(true);
	return new Boolean(false);
}

Base *Float::judge_even(){
	assert(trunc(number_) == number_ && "Not Integer");
	if((long long)number_%2 == 0) return new Boolean(true);
	return new Boolean(false);
}

Number *Float::sinn(){
	return new Float(std::sin(number_));
}

Number *Float::coss(){
	return new Float(std::cos(number_));
}

Number *Float::tann(){
	return new Float(std::tan(number_));
}

Number *Float::asinn(){
	double tmp=std::asin(number_);
	if(std::isnan(tmp)){
		Number *zero=new Rational();
		Number *num=new Complex(this, zero);
		Number *res=num->asinn();
		delete zero;
		delete num;
		return res;
	}
	return new Float(tmp);
}

Number *Float::acoss(){
	double tmp=std::acos(number_);
	if(std::isnan(tmp)){
		Number *zero=new Rational();
		Number *num=new Complex(this, zero);
		Number *res=num->acoss();
		delete zero;
		delete num;
		return res;
	}
	return new Float(tmp);
}

Number *Float::atann(){
	double tmp=std::atan(number_);
	if(std::isnan(tmp)){
		Number *zero=new Rational();
		Number *num=new Complex(this, zero);
		Number *res=num->atann();
		delete zero;
		delete num;
		return res;
	}
	return new Float(tmp);
}

Number *Float::expp(){
	return new Float(std::exp(number_));
}

Number *Float::logg(){
	double res = log(number_);
	if(std::isnan(res)){
		Number *zero = new Float();
		Number *num1 = new Complex(this,zero);
		Number *result = num1->logg();
		delete zero;
		delete num1;
		return result;
	}
	return new Float(res);
}

Number *Float::make_rectangular(Number *number2){
	return new Complex(this,number2);
}

Number *Float::make_polar(Number *number2){
	Number *result,*real,*imag,*p,*q,*tmp;
	p = number2->coss();
	q = number2->sinn();
	tmp=p->convert(this);
	real = tmp->mul(p);
	delete tmp;
	tmp=q->convert(this);
	imag = tmp->mul(q);
	delete tmp;
	result = new Complex(real,imag);
	delete p;
	delete q;
	delete real;
	delete imag;
	return result;
}

Number *Float::magnitude(){
	Float *result;
	result=new Float(std::abs(number_));
	return result;
}

Number *Float::angle(){
	assert(judge_sign()!=0 && "Undefined for 0");
	if(judge_sign()==1) return new Float(0);
	else return new Float(std::acos(-1));
}

Base *Float::judge_char(){
	return new Boolean(false);
}
Base *Float::judge_string(){
	return new Boolean(false);
}

Base *Float::integer_char(){
	assert(1!=1&&"Not Integer");
}
Base *Float::make_string(Char *char2){
	assert(1!=1&&"Not Integer");
}

Base *Float::judge_equal(Number *number2){
	double tmp=SCAST_FLOAT(number2)->number_;
	return new Boolean(tmp==number_);
}

Base *Float::number_string(){
	return new String( toString(number_) );
}

std::istream & operator>>(std::istream &is, Float &obj){
	std::string tmp;
	is >> tmp;
	Float *ttmp=Float::from_string(tmp.c_str());
	if(ttmp==NULL) throw 0;
	else obj=*ttmp;
	return is;
}

/*
std::ostream & operator<<(std::ostream &os, const Float &obj){
	os << obj.number_;
	return os;
}
*/

// int main(){
// 	Float *a = new Float(1.2);
// 	Float *b = new Float(1.3);
// 	(a->add(b))->print();
// }
