// complex.cpp
#include "complex.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "ito.h"

Complex::Complex(Number *real, Number *imag): real_(real), imag_(imag) {
	switch(real->type_){
		case RATIONAL: real_ = new Rational(*SCAST_RATIONAL(real)); break;
		case FLOAT: real_ = new Float(*SCAST_FLOAT(real)); break;
		default: throw 1;
	}
	switch(imag->type_){
		case RATIONAL: imag_ = new Rational(*SCAST_RATIONAL(imag)); break;
		case FLOAT: imag_ = new Float(*SCAST_FLOAT(imag)); break;
		default: throw 1;	
	}
	type_ = COMPLEX;
	btype_ = NUMBER;
	judge();
}

Complex::Complex(char *rstr, char *istr){
	real_ = Rational::from_string(rstr);
	if(!real_) real_ = Float::from_string(rstr);
	
	imag_ = Rational::from_string(istr);
	if(!imag_) imag_ = Float::from_string(istr);
	
	type_ = COMPLEX;
	btype_ = NUMBER;
	judge();
}

Complex::Complex(const Complex &obj){
	switch(obj.real_->type_){
		case RATIONAL: real_ = new Rational(*SCAST_RATIONAL(obj.real_)); break;
		case FLOAT: real_ = new Float(*SCAST_FLOAT(obj.real_)); break;
		default: break;
	}
	switch(obj.imag_->type_){
		case RATIONAL: imag_ = new Rational(*SCAST_RATIONAL(obj.imag_)); break;
		case FLOAT:	imag_ = new Float(*SCAST_FLOAT(obj.imag_)); break;
		default: break;	
	}
	type_ =obj.type_;
	btype_=obj.btype_;
	judge();
}

Complex::~Complex(){
	delete real_;
	delete imag_;
}

void Complex::judge(){
	if(real_->type_ == RATIONAL && imag_->type_ == RATIONAL){
		ise=true;
//		std::cout << '*' << std::endl;
	}else{
		ise=false;
		if(real_->type_==RATIONAL){
			Number *tmp=imag_->convert(real_);
			real_=tmp;
		}
		if(imag_->type_==RATIONAL){
			Number *tmp=real_->convert(imag_);
			imag_=tmp;
		}
	}
//	real_->print();
//	imag_->print();
//	std::cout << '&' << std::endl;
}

Complex* Complex::inexact(){
	Complex *result;
	Number *r,*i;
	if(ise){
		Float *tmp=new Float();
		r=tmp->convert(real_);
		i=tmp->convert(this->imag_);
		result=new Complex(r,i);
		
		delete tmp;
		delete r;
		delete i;
	}
	else{
		result=new Complex(*this);
	}
	return result;
}

Number *Complex::convert(Number *number2){
	assert(number2->type_ <= type_);
	Complex *result = new Complex();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2); 
			result->real_ = new Rational(*tmp);
			result->imag_ = new Rational("0","1");
			break;
		}
		case FLOAT:{
			Float *tmp = SCAST_FLOAT(number2);
			result->real_ = new Float(*tmp);
			result->imag_ = new Float(0);
			break;
		}
		case COMPLEX:{
			Complex *tmp = SCAST_COMPLEX(number2);
			result = new Complex(*tmp);
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	result->judge();
	return result;
}

Number *Complex::add(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	Complex *num1,*num2;
	if(ise && tmp->ise){
		num1 = new Complex(*this);
		num2 = new Complex(*tmp);
	}else{
		num1 = inexact();
		num2 = tmp->inexact();
	}
	result->real_ = num1->real_->add(num2->real_);
	
	result->imag_ = num1->imag_->add(num2->imag_);
	

	delete num1;
	delete num2;
	
	result->judge();
//	result->print();
	return result;
}

Number *Complex::sub(Number *number2){
//	std::cout << '*' << std::endl;
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	Complex *num1,*num2;
	if(ise && tmp->ise){
		num1 = new Complex(*this);
		num2 = new Complex(*tmp);
	}else{
		num1 = inexact();
		num2 = tmp->inexact();
	}
	result->real_ = num1->real_->sub(num2->real_);
	result->imag_ = num1->imag_->sub(num2->imag_);
	delete num1;
	delete num2;
	
	result->judge();
	return result;
}

Number *Complex::mul(Number *number2){
//	std::cout << '*' << std::endl; 
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	Complex *num1,*num2;
	if(ise && tmp->ise){
		num1 = new Complex(*this);
		num2 = new Complex(*tmp);
	}else{
		num1 = inexact();
		num2 = tmp->inexact();
	}
//	std::cout << '*' << std::endl;
//	real_->print();
//	imag_->print();
	result->real_ = num1->real_->mul(num2->real_)->sub(num1->imag_->mul(num2->imag_));
	result->imag_ = num1->real_->mul(num2->imag_)->add(num1->imag_->mul(num2->real_));
//	result->real_->print();
//	result->imag_->print();
	delete num1;
	delete num2;
	
	result->judge();
	return result;
}

Number *Complex::div(Number *number2){
//	std::cout << real_->print() << ' ' <<imag_->print() << std::endl;
//	std::cout << number2->print() << ' ' << std::endl;
	//std::cout << '*';
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	Complex *num1,*num2;
	Number *p,*middle,*zero;
	if(ise && tmp->ise){
		num1 = new Complex(*this);
		num2 = new Complex(*tmp);
		p = num2->real_->mul(num2->real_)->add(num2->imag_->mul(num2->imag_));
		middle = new Rational(*SCAST_RATIONAL(p));
		zero = new Rational();
	}else{
		num1 = inexact();
		num2 = tmp->inexact();
		p = num2->real_->mul(num2->real_)->add(num2->imag_->mul(num2->imag_));
		middle = new Float(*SCAST_FLOAT(p));
		zero = new Float();
	}
	num2->imag_ = zero->sub(num2->imag_);
	result = SCAST_COMPLEX(num1->mul(num2));
	result->real_ = result->real_->div(middle);
	result->imag_ = result->imag_->div(middle);
	delete num1;
	delete num2;
	delete middle;
	delete zero;
	delete p;
	
	result->judge();
	return result;
}

void Complex::print(std::ostream& o)const{
	Number *one;
//	std::cout << real_->type_ << std::endl;
//	std::cout << '*';
	if(real_->judge_sign()==0&&imag_->judge_sign()==0){
		real_->print(o);
	}
	else{
		if(real_->judge_sign() != 0) real_->print(o);
		if(imag_->judge_sign() == 1){
			one = new Rational("1","1");
			if(real_->judge_sign() != 0) o << '+';
			if(imag_->sub(imag_->convert(one))->judge_sign() != 0) imag_->print(o);
			o << 'i';
			delete one;
		}else if(imag_->judge_sign() == -1){
			one = new Rational("-1","1");
			if(imag_->sub(imag_->convert(one))->judge_sign() == 0){
				o << '-';
			}else imag_->print(o);
			o << 'i';
			delete one;
		}	
	}
}

int Complex::judge_sign(){
	assert(imag_->judge_sign() == 0 && "Not Real");
	return real_->judge_sign();
}

Complex *Complex::from_string(const char *expression){
	Number *real,*imag;
	char *ri_pos;
	ri_pos = strchr(expression,'i');
	if(!ri_pos) return NULL;
	char *rstr = new char[1000];
	char *istr = new char[1000];
	ri_pos = strchr(expression,'+');
//	std::cout << '1' << std::endl;
	if(!ri_pos){
		ri_pos = strchr(expression,'-');
		if(ri_pos == expression){
			ri_pos = strchr(expression+1,'-');
		}
		if(ri_pos){
			strncpy(rstr,expression,strlen(expression)-strlen(ri_pos));
			while(rstr[strlen(expression)-strlen(ri_pos)-1] == 'e' || rstr[strlen(expression)-strlen(ri_pos)-1] == '/'){
				//std::cout << '1' << std::endl;
				ri_pos = strchr(ri_pos+1,'-');
				if(!ri_pos) break;
				strncpy(rstr,expression,strlen(expression)-strlen(ri_pos));
			}
		}
		if(!ri_pos){
			rstr[0] = '0';
			rstr[1] = '\0';
			strncpy(istr,expression,strlen(expression)-1);
			istr[strlen(expression)-1] = '\0';
		}else{
			strncpy(rstr,expression,strlen(expression)-strlen(ri_pos));
			rstr[strlen(expression)-strlen(ri_pos)] = '\0';
			strncpy(istr,ri_pos,strlen(ri_pos)-1);
			istr[strlen(ri_pos)-1] = '\0';
		}
	}else{
		strncpy(rstr,expression,strlen(expression)-strlen(ri_pos));
		rstr[strlen(expression)-strlen(ri_pos)] = '\0';
		strncpy(istr,ri_pos+1,strlen(ri_pos)-2);
		istr[strlen(ri_pos)-2] = '\0';		
	}
//	std::cout << 1 << std::endl;
	if(!strlen(istr)){
		istr[0] = '1';
		istr[1] = '\0';
	}
//	std::cout << rstr << ' ' << istr << std::endl;
	real = Rational::from_string(rstr);
//	std::cout << '*' << std::endl;
	if(!real) real = Float::from_string(rstr);
//	std::cout << '&' << std::endl;
	imag = Rational::from_string(istr);
	if(!imag) imag = Float::from_string(istr);
	//std::cout << 1 << std::endl;
	delete [] rstr;
	//std::cout << 1 << std::endl;
	delete [] istr;
//	std::cout << 1 << std::endl;
//	imag->print();
	return new Complex(real,imag);
}

Number *Complex::abs(){
	assert(imag_->judge_sign()==0 && "Not Rational");
	return real_->abs();
}

Number *Complex::floor(){
	assert(imag_->judge_sign() == 0 && "Not Rational");
	return real_->floor();	
}

Number *Complex::ceiling(){
	assert(imag_->judge_sign() == 0 && "Not Rational");
	return real_->ceiling();
}

Number *Complex::truncate(){
	assert(imag_->judge_sign() == 0 && "Not Rational");
	return real_->truncate();
}

Number *Complex::round(){
	assert(imag_->judge_sign() == 0 && "Not Rational");
	return real_->round();
}

Number *Complex::numerator(){
	assert(1!=1&&"Not Rational");
}

Number *Complex::denominator(){
	assert(1!=1&&"Not Rational");
}

Number *Complex::real_part(){
	if(ise) return new Rational(*SCAST_RATIONAL(real_));
	else return new Float(*SCAST_FLOAT(real_));
}

Number *Complex::imag_part(){
	if(ise) return new Rational(*SCAST_RATIONAL(imag_));
	else return new Float(*SCAST_FLOAT(imag_));
}

Number *Complex::quotient(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Integer");
	return real_->quotient(tmp->real_);
}

Number *Complex::remainder(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Integer");
	return real_->remainder(tmp->real_);
}

Number *Complex::modulo(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Integer");
	return real_->modulo(tmp->real_);
}

Number *Complex::gcd(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Rational");
	return real_->gcd(tmp->real_);	
}

Number *Complex::lcm(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Rational");
	return real_->lcm(tmp->real_);	
}

Number *Complex::expt(Number *number2){
/*	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *num1 = inexact();
	Complex *num2 = tmp->inexact();
	double a = SCAST_FLOAT(num1->real_)->number_;
	double b = SCAST_FLOAT(num1->imag_)->number_;
	double c = SCAST_FLOAT(num2->real_)->number_;
	double d = SCAST_FLOAT(num2->imag_)->number_;
	double x,y;
	x = log(a*a+b*b)/2;
	y = atan(b/a);
	a = exp(c*x-d*y)*cos(x*d-y*c);
	b = exp(c*x-d*y)*sin(x*d-y*c);
	std::cout << a << '+' << b << 'i' << std::endl;
	Number *real = new Float(a);
	Number *imag = new Float(b);
	Number *result = new Complex(real,imag);
	delete num1;
	delete num2;
	delete real;
	delete imag;
	return result;
*/
	Complex *tmp = SCAST_COMPLEX(number2);
	Number *num1 = inexact();
	Number *num2 = tmp->inexact();
	Number *num3 = num1->logg();
	num1 = num2->mul(num3);
	Number *result = num1->expp();
	/*Complex *num1 = unexact();
	Complex *num2 = tmp->unexact();
	long double a = SCAST_FLOAT(num1->real_)->number_;
	long double b = SCAST_FLOAT(num1->imag_)->number_;
	long double c = SCAST_FLOAT(num2->real_)->number_;
	long double d = SCAST_FLOAT(num2->imag_)->number_;
	long double x,y;
	x = log(a*a+b*b)/2;
	y = atan(b/a);
	a = exp(c*x-d*y)*cos(x*d-y*c);
	b = exp(c*x-d*y)*sin(x*d-y*c);
	Number *real = new Float(a);
	Number *imag = new Float(b);
	Number *result = new Complex(real,imag);
	delete num1;
	delete num2;
	delete real;
	delete imag;*/
	return result;
}

Number *Complex::sqrt(){
/*	if(!imag_->judge_sign()){
		return real_->sqrt();
	}else if(!real_->judge_sign()){
		Number *a,*b,*two;
		two=new Float(2);
		a=(two->convert(imag_))->div(two)->abs()->sqrt();
		b=(two->convert(imag_))->div(two)->abs()->sqrt();
		if(imag_->judge_sign()==-1){
			b=two->sub(two)->sub(b);
		}
		Complex *result=new Complex(a,b);
		delete a;
		delete b;
		return result;
	}else{
		Number *result,*real,*imag,*two;
		two = new Float(2);
		real = real_->mul(real_)->add(imag_->mul(imag_))->sqrt()->add(two->convert(real_))->div(two)->sqrt();
		imag = real_->mul(real_)->add(imag_->mul(imag_))->sqrt()->sub(two->convert(real_))->div(two)->sqrt();
		if(imag_->judge_sign() == -1) imag = two->sub(two)->sub(imag);
		result = new Complex(real,imag);
		delete two;
		delete real;
		delete imag;
		return result;
	}
*/
	if(!imag_->judge_sign()){
		return real_->sqrt();
	}else if(!real_->judge_sign()){
		throw 0;
	}else{
		Number *result,*real,*imag,*two,*p,*q,*conv,*zero;
		two = new Float(2);
		zero = new Float(0);
		p = real_->mul(real_);
		q = imag_->mul(imag_);
		conv = p->add(q);
		delete p;
		delete q;
		p = conv->sqrt();
		delete conv;
		q = two->convert(real_);
		real = p->add(q);
		imag = p->sub(q);
		delete p;
		delete q;
		p = real->div(two);
		q = imag->div(two);
		delete real;
		delete imag;
		real = p->sqrt();
		imag = q->sqrt();
		delete p;
		delete q;
		//real = real_->mul(real_)->add(imag_->mul(imag_))->sqrt_()->add(two->convert(real_))->div(two)->sqrt_();
		//imag = real_->mul(real_)->add(imag_->mul(imag_))->sqrt_()->sub(two->convert(real_))->div(two)->sqrt_();
		if(imag_->judge_sign() == -1){
			conv = zero->sub(imag);
			delete imag;
			imag = conv;
		}
		result = new Complex(real,imag);
		delete two;
		delete zero;
		delete real;
		delete imag;
		return result;
	}
}


Number *Complex::minn(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Real");
	return real_->minn(tmp->real_);
}

Number *Complex::maxx(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Real");
	return real_->maxx(tmp->real_);
}

Number *Complex::inexact_exact(){
	Complex *result;
	result=new Complex(real_->inexact_exact(),imag_->inexact_exact());
	return result;
}

Number *Complex::exact_inexact(){
	Complex *result;
	result=new Complex(real_->exact_inexact(),imag_->exact_inexact());
	return result;
}

Base *Complex::judge_integer(){
	if(imag_->judge_sign() == 0) return real_->judge_integer();
	return new Boolean(false);
}

Base *Complex::judge_rational(){
	if(imag_->judge_sign() == 0) return real_->judge_rational();
	return new Boolean(false);
}

Base *Complex::judge_real(){
	if(imag_->judge_sign() == 0) return real_->judge_real();
	return new Boolean(false);
}
	
Base *Complex::judge_complex(){
	return new Boolean(true);
}

Base *Complex::judge_number(){
	return new Boolean(true);
}

Base *Complex::judge_less(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Real");
	return real_->judge_less(tmp->real_);
}

Base *Complex::judge_eless(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Real");
	return real_->judge_eless(tmp->real_);
}

Base *Complex::judge_greater(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Real");
	return real_->judge_greater(tmp->real_);
}

Base *Complex::judge_egreater(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Real");
	return real_->judge_egreater(tmp->real_);
}

Base *Complex::judge_exact(){
	return new Boolean(ise);
}

Base *Complex::judge_inexact(){
	return new Boolean(!ise);
}

Base *Complex::judge_zero(){
	if(judge_sign() == 0) return new Boolean(true);
	return new Boolean(false);
}

Base *Complex::judge_negative(){
	if(judge_sign() == -1) return new Boolean(true);
	return new Boolean(false);
}

Base *Complex::judge_positive(){
	if(judge_sign() == 1) return new Boolean(true);
	return new Boolean(false);
}

Base *Complex::judge_odd(){
	assert(imag_->judge_sign() == 0 && "Not Real");
	return real_->judge_odd();
}

Base *Complex::judge_even(){
	assert(imag_->judge_sign() == 0 && "Not Real");
	return real_->judge_even();
}

Number *Complex::sinn(){
	Number *result,*real,*imag,*p,*q,*conv,*zero = new Float(0),*two = new Float(2);
	q = zero->sub(p=zero->convert(imag_));
	delete p;
	p = q->expp();
	delete q;
	q = imag_->expp();
	real = q->add(p);
	imag = q->sub(p);
	delete p;
	delete q;
	p = real->div(two);
	q = imag->div(two);
	delete real;
	delete imag;
	conv = real_->sinn();
	real = p->mul(conv);
	delete conv;
	conv = real_->coss();
	imag = q->mul(conv);
	delete conv;
	result = new Complex(real,imag);
	delete p;
	delete q;
	delete real;
	delete imag;
	delete zero;
	delete two;
	return result;
}

Number *Complex::coss(){
	Number *result,*real,*imag,*p,*q,*conv,*zero = new Float(0),*two = new Float(2);
	q = zero->sub(p=zero->convert(imag_));
	delete p;
	p = q->expp();
	delete q;
	q = imag_->expp();
	real = q->add(p);
	imag = q->sub(p);
	delete p;
	delete q;
	p = real->div(two);
	q = imag->div(two);
	delete real;
	delete imag;
	conv = real_->coss();
	real = p->mul(conv);
	delete conv;
	delete p;
	conv = real_->sinn();
	p = q->mul(conv);
	imag = zero->sub(p);
	delete conv;
	result = new Complex(real,imag);
	delete p;
	delete q;
	delete real;
	delete imag;
	delete two;
	delete zero;
	return result;
}

Number *Complex::tann(){
	Number *s = sinn();
	Number *c = coss();
	Number *result = s->div(c);
	delete s;
	delete c;
	return result;
}

Number *Complex::asinn(){
	Number *i = new Complex("0","1");
	Number *one = new Complex("1","0");
	Number *result,*p,*q,*tmp=this,*t;
	bool flag=false;
	if(real_->judge_sign()==-1 && imag_->judge_sign()==0){
		t=new Complex(real_->abs(),imag_);
		tmp=t;
		flag=true;
	}
	result = tmp->mul(tmp);
	p = one->sub(result);
	delete result;
	q = tmp->mul(i);
	result = p->sqrt();
	delete p;
	p = q->add(result);
	delete q;
	delete result;
	q = p->logg();
	delete p;
	result = q->div(i);
	delete q;
	delete i;
	delete one;
	if(flag){
		Number *zero=new Complex("0","0");
		p=zero->sub(result);
		delete result;
		result=p;
		delete zero;
		delete t;
	}
	return result;
}

Number *Complex::acoss(){
	Number *i = new Complex("0","1");
	Number *one = new Complex("1","0");
	Number *result,*p,*q,*tmp=this,*t;
	bool flag=false;
	if(real_->judge_sign()==-1 && imag_->judge_sign()==0){
		t=new Complex(real_->abs(),imag_);
		tmp=t;
		flag=true;
	}
	result = tmp->mul(tmp);
	p = one->sub(result);
	delete result;
	result = p->sqrt();
	delete p;
	q = result->mul(i);
	delete result;
	p = q->add(tmp);
	delete q;
	q = p->logg();
	delete p;
	result = q->div(i);
	delete q;
	delete i;
	delete one;
	if(flag){
		p=new Float(0);
		q=new Float(0);
		Number *pai=new Complex(q,p);
		delete p;
		delete q;
		p=pai->sub(result);
		delete result;
		result=p;
		delete pai;
		delete t;
	}
	return result;
}

Number *Complex::atann(){
	Number *i = new Complex("0","1");
	Number *one = new Complex("1","0");
	Number *result,*p,*q,*tmp=this;
	result = tmp->mul(i);
	p = one->add(result);
	q = one->sub(result);
	delete result;
	result = p->div(q);
	delete p;
	delete q;
	p = result->logg();
	delete result;
	delete i;
	i = new Complex("0","2");
	result = p->div(i);
	delete p;
	delete i;
	delete one;
	return result;
}

Number *Complex::expp(){
	Number *result,*real,*imag,*p,*q,*conv,*middle;
	conv = real_->expp();
	p = imag_->coss();
	q = imag_->sinn();
	middle = p->convert(conv);
	real = middle->mul(p);
	imag = middle->mul(q);
	result = new Complex(real,imag);
	delete conv;
	delete middle;
	delete p;
	delete q;
	delete real;
	delete imag;
	return result;
}

Number *Complex::logg(){
	Number *result,*real,*imag,*p,*q,*conv,*pai;
	pai = new Float(std::acos(-1));
/*
	conv = imag_->div(real_);
	imag = conv->atann();
	delete conv;
	if(real_->judge_sign() == -1){
		conv = imag->add(pai);
		delete imag;
		imag = conv;
	}
	conv = imag->coss();
	q = conv->convert(real_);
	p = q->div(conv);
	real = p->logg();
	result = new Complex(real,imag);
	delete q;
	delete p;
	delete conv;
	delete real;
	delete imag;
	return result;
*/
	if(real_->judge_sign() == 0 && imag_->judge_sign() == 0) return new Float(log(0));
	if(real_->judge_sign() != 0){
		conv = imag_->div(real_);
		imag = conv->atann();
		delete conv;
		if(real_->judge_sign() == -1){
			conv = imag->add(pai);
			delete imag;
			imag = conv;
		}
		conv = imag->coss();
		q = conv->convert(real_);
		p = q->div(conv);
		real = p->logg();
		result = new Complex(real,imag);
		delete q;
		delete p;
		delete conv;
		delete real;
		delete imag;
	}else if(imag_->judge_sign() != 0){
		imag = new Float(acos(0));
		q = imag->convert(imag_);
		real = q->logg();
		result = new Complex(real,imag);
		delete q;
		delete real;
		delete imag;
	}
	return result;
}

Number *Complex::make_rectangular(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Real");
	return real_->make_rectangular(tmp->real_);
}

Number *Complex::make_polar(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	assert(imag_->judge_sign() == 0 && tmp->imag_->judge_sign() == 0 && "Not Real");
	return real_->make_polar(tmp->real_);
}

Number *Complex::magnitude(){
	Number *result,*a,*b,*tmp;
	a = real_->mul(real_);
	b = imag_->mul(imag_);
	tmp = a->add(b);
	result = tmp->sqrt();
	delete a,b,tmp;
	return result;
}

Number *Complex::angle(){
	Number *result,*tmp;
	tmp = imag_->div(real_);
	result = tmp->atann();
	delete tmp;
	return result;
}

Base *Complex::judge_char(){
	return new Boolean(false);
}
Base *Complex::judge_string(){
	return new Boolean(false);
}

Base *Complex::integer_char(){
	assert(1!=1&&"Not Integer");
}
Base *Complex::make_string(Char *char2){
	assert(1!=1&&"Not Integer");
}

Base *Complex::judge_equal(Number *number2){
	Complex *tmp=SCAST_COMPLEX(number2);
	int tmp1,tmp2,tmp3,tmp4;
	tmp1=real_->type_;
	tmp2=imag_->type_;
	tmp3=tmp->real_->type_;
	tmp4=tmp->imag_->type_;
	if(tmp1!=tmp3||tmp2!=tmp4) return new Boolean(false);
	else{
		Base *res1, *res2;
		res1=real_->judge_equal(tmp->real_);
		res2=imag_->judge_equal(tmp->imag_);
		if(SCAST_BOOLEAN(res1)->flag&&SCAST_BOOLEAN(res2)->flag){
			delete res1;
			delete res2;
			return new Boolean(true);
		}
		else{
			delete res1;
			delete res2;
			return new Boolean(false);
		}
	}
}

Base *Complex::number_string(){
	return new String( toString(*this) );
}


std::ostream & operator<<(std::ostream &os, const Complex &obj){
	obj.print(os);
	return os;
}

std::istream & operator>>(std::istream &is, Complex &obj){
	std::string tmp;
	is >> tmp;
	Complex *ttmp=Complex::from_string(tmp.c_str());
	if(ttmp==NULL) throw 0;
	else obj=*ttmp;
	return is;
}

