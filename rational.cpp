#include "rational.h"
#include "float.h"
#include "complex.h"
#include "char.h"
#include "string.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <cmath>
#include "ito.h"
#define MAXN 500

//Rational::Rational(int numerator, int denominator) : numerator_(numerator),denominator_(denominator){
//	type_ = RATIONAL;
//	reduce();
//}

//Rational::Rational(char* numerator, char* denominator):numerator_(numerator), denominator_(denominator){
//	type_ = RATIONAL;
//	reduce();
//};

Rational::Rational(LongInt numerator, LongInt denominator) : numerator_(numerator),	denominator_(denominator){
	type_ = RATIONAL;
	btype_ = NUMBER;
	reduce();
}

Rational::Rational(const Rational &obj) : numerator_(obj.numerator_), denominator_(obj.denominator_) {
	type_ = obj.type_;
	btype_ = obj.btype_;
}

Rational::~Rational(){

}

void Rational::reduce(){
	assert(denominator_ && "denominator is zero");
	if(!numerator_){
		denominator_ = 1;
		return;
	}
	LongInt big, small, tmp;
	big = max(numerator_, denominator_);
	small = min(numerator_, denominator_);
//	std::cout << big << ' ' << small << std::endl;
	while(tmp = big % small){
		big = small;
		small = tmp;
//		std::cout << tmp << std::endl;
	}
//	std::cout << small << std::endl;
	numerator_ = numerator_ / small;
	denominator_ = denominator_ / small;
	if(denominator_ < LongInt(0)){
		numerator_ = LongInt(0)-numerator_;
		denominator_ = LongInt(0)-denominator_;
	}
}


Number *Rational::convert(Number *number2){
//	std::cout << type_ << ' ' << number2->type_ << std::endl;
	assert(number2->type_ <= type_);
	Rational *result = new Rational();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->numerator_ = tmp->numerator_;
			result->denominator_ = tmp->denominator_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	result->reduce();
	return result;
}

Number *Rational::add( Number *number2) {
//	std::cout << '*' << std::endl;
	Rational *tmp = SCAST_RATIONAL(number2);
//	std::cout << "**" << std::endl;
	Rational *result = new Rational;
//	std::cout <<  '*' << result->numerator_ << std::endl;
	result->numerator_ = numerator_*tmp->denominator_ + denominator_*tmp->numerator_;
	
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::sub(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
//	std::cout <<  '*' << result->numerator_ << std::endl;
	result->denominator_ = denominator_ * tmp->denominator_;
//	std::cout << result->denominator_ << std::endl;
	result->reduce();
	return result;
}

Number *Rational::mul(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::div(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->denominator_;
	result->denominator_ = denominator_ * tmp->numerator_;
	result->reduce();
	return result;
}

void Rational::print(std::ostream& o)const{
	numerator_.print(o);
//	std::cout << std::endl << denominator_ << ' ' << (LongInt)1 <<  ' ' <<(denominator_ != LongInt(1))<< std::endl;
	if(denominator_ != LongInt(1)){
		printf("/");
		denominator_.print(o);
	}
}

Rational *Rational::from_string(const char *expression){
	
	char *num;
    num = new char[MAXN];
    char *separate_pos;
    separate_pos = strchr(expression,'.');
    if(separate_pos) return NULL;
    separate_pos = strchr(expression,'e');
    if(separate_pos) return NULL;
    separate_pos = strchr(expression,'i');
    if(separate_pos) return NULL;

    separate_pos = strchr(expression, '/');
    if(separate_pos){
        strncpy(num,expression,strlen(expression)-strlen(separate_pos));
        if(!num || expression==separate_pos)
        	return NULL;
        num[strlen(expression)-strlen(separate_pos)]='\0';
//      char *a;
//		memcpy(num,a,sizeof(char)*(strlen(expression)-strlen(separate_pos)));
        LongInt numerator(num);

        strcpy(num,separate_pos+1);
        if(!num)
        	return NULL;
//      char *b;
//		memcpy(num,b,sizeof(char)*(strlen(separate_pos)+1));
        LongInt denominator(num);

        delete []num;
        return new Rational(numerator,denominator);
    }else{
    	strcpy(num,expression);
        if(!num)
        	return NULL;
//        char *a;
//		memcpy(num,a,sizeof(char)*(strlen(expression)));
        LongInt numerator(num);
        delete []num;
        return new Rational(numerator , "1");
    }
	
}

int Rational::judge_sign(){
	if(numerator_ == LongInt(0)) return 0;
	if(numerator_.sign^denominator_.sign) return -1;
	return 1;
}

Number *Rational::abs() {
	Rational *result = new Rational(*this);
	result->numerator_.sign=true;
	result->denominator_.sign=true;
	return result;
}

Number *Rational::floor(){
	Rational *result;
	if(numerator_.sign^denominator_.sign){
//		std::cout << numerator_%denominator_ << std::endl;
		if(numerator_%denominator_!=LongInt(0)){
			result = new Rational(numerator_/denominator_-LongInt(1));
			return result;
		}
		else{
//			std::cout << numerator_%denominator_ << std::endl;
			result = new Rational(numerator_/denominator_);
			return result;
		}
	}
	else{
		result = new Rational(numerator_/denominator_);
		return result;
	}
}
Number *Rational::ceiling(){
	Rational *result;
	if(numerator_.sign^denominator_.sign){
		result = new Rational(numerator_/denominator_);
		return result;
	}
	else{
		if(numerator_%denominator_!=LongInt(0)){
			result = new Rational(numerator_/denominator_+LongInt(1));
			return result;
		}
		else{

			result = new Rational(numerator_/denominator_);
			return result;
		}
	}
}

Number *Rational::truncate(){
	Rational *result;
	result = new Rational(numerator_/denominator_);
	return result;
}

Number *Rational::round(){
	Rational *result;
//	std::cout << '*' << std::endl;
	if(numerator_%denominator_==LongInt(0)){
		result=new Rational(numerator_/denominator_);
		return result;
	}
	if(numerator_/denominator_%LongInt(2)==LongInt(1)){
		if(!((numerator_%denominator_).abscmp(denominator_/LongInt(2)))){
			result=new Rational(numerator_/denominator_+LongInt(1));
			return result;
		}
		else{
			result=new Rational(numerator_/denominator_);
			return result;
		}
	}
	if(numerator_/denominator_%LongInt(2)==LongInt(-1)){
		if(!((numerator_%denominator_).abscmp(denominator_/LongInt(2)))){
			result=new Rational(numerator_/denominator_+LongInt(-1));
			return result;
		}
		else{
			result=new Rational(numerator_/denominator_);
			return result;
		}
	}
	if(((numerator_/denominator_)%LongInt(2))==LongInt(0)){
		if((denominator_/LongInt(2)).abscmp(numerator_%denominator_)){
			if(numerator_.sign^denominator_.sign) result=new Rational(numerator_/denominator_+LongInt(-1));
			else result=new Rational(numerator_/denominator_+LongInt(1));
			return result;
		}
		else{
			result=new Rational(numerator_/denominator_);
			return result;
		}
	}
}

Number *Rational::numerator(){
	Rational *result;
	result=new Rational(numerator_);
	return result;
}

Number *Rational::denominator(){
	Rational *result;
	result=new Rational(denominator_);
	return result;
}

Number *Rational::real_part(){
	Rational *result;
	result=new Rational(numerator_,denominator_);
	return result;
}

Number *Rational::imag_part(){
	Rational *result;
	result=new Rational("0","1");
	return result;
}

Number *Rational::quotient(Number *number2){
	Rational *result;
	Rational *tmp = SCAST_RATIONAL(number2);
	assert(denominator_ == LongInt(1) && tmp->denominator_ == LongInt(1) && "Not Integer");
	result=new Rational(numerator_/tmp->numerator_, LongInt(1));
	return result;
}

Number *Rational::remainder(Number *number2){
	Rational *result;
	Rational *tmp = SCAST_RATIONAL(number2);
	assert(denominator_ == LongInt(1) && tmp->denominator_ == LongInt(1) && "Not Integer");
	result=new Rational(numerator_%tmp->numerator_, LongInt(1));
	return result;
}

Number *Rational::modulo(Number *number2){
	Rational *result;
	Rational *tmp = SCAST_RATIONAL(number2);
	assert(denominator_ == LongInt(1) && tmp->denominator_ == LongInt(1) && "Not Integer");
	if(judge_sign()==number2->judge_sign()){
		result=new Rational(numerator_%tmp->numerator_, LongInt(1));
	}
	else{
		result=new Rational(numerator_%tmp->numerator_+tmp->numerator_);
	}
	
	return result;
}

Number *Rational::gcd(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	LongInt a = gcdd(numerator_, tmp->numerator_);
	LongInt b = lcmm(denominator_, tmp->denominator_);
	return new Rational(a,b);
}

Number *Rational::lcm(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	LongInt a = lcmm(numerator_, tmp->numerator_);
	LongInt b = gcdd(denominator_, tmp->denominator_);
	return new Rational(a,b);	
}

Number *Rational::expt(Number *number2){
	Float *result;
	Rational *tmp = SCAST_RATIONAL(number2);
	result=new Float(std::pow((double)numerator_/(double)denominator_, (double)tmp->numerator_/(double)tmp->denominator_));
	return result;
}

Number *Rational::sqrt(){
	if(judge_sign()==-1){
		Float *a,*b;
		a=new Float(0.0);
		b=new Float(std::sqrt(std::abs((double)numerator_/(double)denominator_)));
		Complex *result=new Complex(a,b);
		delete a,b;
		return result;
	}
	else{
		Float *result;
		result=new Float(std::sqrt((double)numerator_/(double)denominator_));
		return result;
	}
}


Number *Rational::minn(Number *number2){
	if(sub(number2)->judge_sign()==1) return new Rational(*SCAST_RATIONAL(number2));
	else return new Rational(*this);
}

Number *Rational::maxx(Number *number2){
	if(sub(number2)->judge_sign()==-1) return new Rational(*SCAST_RATIONAL(number2));
	else return new Rational(*this);
}

Number *Rational::inexact_exact(){
	Rational *result;
	result=new Rational(*this);
	return result;
}

Number *Rational::exact_inexact(){
	Number *result;
	Number *tmp=new Float();
	result = tmp->convert(this);
	delete tmp;
	return result;
}

Base *Rational::judge_integer(){
	if(denominator_ == LongInt(1)) return new Boolean(true);
	return new Boolean(false);
}

Base *Rational::judge_rational(){
	return new Boolean(true);
}

Base *Rational::judge_real(){
	return new Boolean(true);
}
	
Base *Rational::judge_complex(){
	return new Boolean(true);
}

Base *Rational::judge_number(){
	return new Boolean(true);
}

Base *Rational::judge_less(Number *number2){
	bool flag;
	Number *tmp = this;
	tmp = number2->sub(tmp);
	if(tmp->judge_sign() == 1) flag = true;
	else flag = false;
	delete tmp;
	return new Boolean(flag);
}

Base *Rational::judge_eless(Number *number2){
	bool flag;
	Number *tmp = this;
	tmp = number2->sub(tmp);
	if(tmp->judge_sign() != -1) flag = true;
	else flag = false;
	delete tmp;
	return new Boolean(flag);
}

Base *Rational::judge_greater(Number *number2){
	bool flag;
	Number *tmp = this;
	tmp = tmp->sub(number2);
	if(tmp->judge_sign() == 1) flag = true;
	else flag = false;
	delete tmp;
	return new Boolean(flag);	
}

Base *Rational::judge_egreater(Number *number2){
	bool flag;
	Number *tmp = this;
	tmp = tmp->sub(number2);
	if(tmp->judge_sign() != -1) flag = true;
	else flag = false;
	delete tmp;
	return new Boolean(flag);
}

Base *Rational::judge_exact(){
	return new Boolean();
}

Base *Rational::judge_inexact(){
	return new Boolean(false);
}

Base *Rational::judge_zero(){
	if(judge_sign() == 0) return new Boolean(true);
	return new Boolean(false);
}

Base *Rational::judge_negative(){
	if(judge_sign() == -1) return new Boolean(true);
	return new Boolean(false);
}

Base *Rational::judge_positive(){
	if(judge_sign() == 1) return new Boolean(true);
	return new Boolean(false);
}

Base *Rational::judge_odd(){
	assert(denominator_ == LongInt(1) && "Not Integer");
	if(numerator_%LongInt(2) == LongInt(1)) return new Boolean(true);
	return new Boolean(false);
}

Base *Rational::judge_even(){
	assert(denominator_ == LongInt(1) && "Not Integer");
	if(numerator_%LongInt(2) == LongInt(0)) return new Boolean(true);
	return new Boolean(false);
}

Number *Rational::sinn(){
	return new Float(std::sin((double)numerator_/(double)denominator_));
}

Number *Rational::coss(){
	return new Float(std::cos((double)numerator_/(double)denominator_));
}

Number *Rational::tann(){
	return new Float(std::tan((double)numerator_/(double)denominator_));
}

Number *Rational::asinn(){
	double tmp=std::asin((double)numerator_/(double)denominator_);
	if(std::isnan(tmp)){
		Number *zero=new Rational(0);
		Number *num=new Complex(this, zero);
		Number *res=num->asinn();
		delete zero;
		delete num;
		return res;
	}
	return new Float(tmp);
}

Number *Rational::acoss(){
	double tmp=std::acos((double)numerator_/(double)denominator_);
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

Number *Rational::atann(){
	double tmp=std::atan((double)numerator_/(double)denominator_);
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

Number *Rational::expp(){
	return new Float(std::exp((double)numerator_/(double)denominator_));
}

Number *Rational::logg(){
	return new Float(std::log((double)numerator_/(double)denominator_));
}

Number *Rational::make_rectangular(Number *number2){
	return new Complex(this,number2);
}

Number *Rational::make_polar(Number *number2){
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

Number *Rational::magnitude(){
	Rational *result;
	result=new Rational(*this);
	result->numerator_.sign=true;
	result->denominator_.sign=true;
	return result;
}

Number *Rational::angle(){
	assert(judge_sign()!=0 && "Undefined for 0");
	if(judge_sign()==-1) return new Float(std::acos(-1));
	else return new Rational("0","1");
}

Base *Rational::judge_char(){
	return new Boolean(false);
}
Base *Rational::judge_string(){
	return new Boolean(false);
}

Base *Rational::integer_char(){
	assert(denominator_==LongInt(1)&&"Not Integer");
	int tmp;
	tmp=(int)numerator_;
	Char *res;
	res=new Char((char)tmp);
	return res;
}
Base *Rational::make_string(Char *char2){
	assert(denominator_==LongInt(1)&&judge_sign()!=-1&&"Not Integer");
	int tmp;
	tmp=(int)numerator_;
	String *res;
	std::string conv;
	for(int i=0; i<tmp; ++i){
		conv+=char2->cha;
	}
	res=new String(conv);
	return res;
}

Base *Rational::judge_equal(Number *number2){
	Rational *tmp=SCAST_RATIONAL(number2);
	return new Boolean(numerator_==tmp->numerator_&&denominator_==tmp->denominator_);
}

Base *Rational::number_string()
{
	return new String( toString(*this) );
}


std::ostream & operator<<(std::ostream &os, const Rational &obj){
	obj.print(os);
	return os;
}

std::istream & operator>>(std::istream &is, Rational &obj){
	std::string tmp;
	is >> tmp;
//	std::cout << tmp << std::endl;
	Rational *ttmp=Rational::from_string(tmp.c_str());
//	std::cout << '*' << std::endl;
	if(ttmp==NULL) throw 0;
	else obj=*ttmp;
	return is;
}


// int main(){
// 	Rational *a = new Rational(-18,18);
// 	// Rational *b = new Rational(4,5);
// 	printf("%d %d\n", a->numerator_.number_, a->denominator_.number_);
// 	// (a->div(b))->print();
// }
