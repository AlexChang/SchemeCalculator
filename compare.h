#include "opt.h"
#include "float.h"
#include "rational.h"
#include "complex.h"
#include "number.h"
#include "boolean.h"
#include "char.h"
#include "string.h"
#include "base.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <complex>
#include <cstdlib>
#define SCAST_RATIONAL(x) static_cast<Rational*>(x)
#define SCAST_FLOAT(x) static_cast<Float*>(x)
#define SCAST_COMPLEX(x) static_cast<Complex*>(x)
#define SCAST_NUMBER(x) static_cast<Number*>(x)

class Add : public Opt {
    /* Use the lowest level type */
    Number *calc(Cons *con) {
		
		Number *res = new Rational("0","1");
		Number *last;	
        for (; con; con = con->cdr)
        {
        	if(con->car->btype_!=2) throw 0;
			if(SCAST_NUMBER(con->car)->type_>3||SCAST_NUMBER(con->car)->type_<1)
			{
				throw 0;
			}
            Number *opr = SCAST_NUMBER(con->car), *conv;
            last = res;
            if (res->type_ > opr->type_)
			{
				res = res->add(conv = res->convert(opr));
			}
            else
			{
                res = (conv = opr->convert(res))->add(opr);
			}
			
            delete last;
            delete conv;
			
        }
        return res;
    }
};
class Sub : public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(con->car->btype_!=2) throw 0;
			if(SCAST_NUMBER(con->car)->type_>3||SCAST_NUMBER(con->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt==0) throw;
		Number *res=new Rational("0", "1"),*last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		last=res;
		if(cnt==1)
		{
			if (res->type_ > opr->type_)
				res = res->sub(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->sub(opr);
			delete last;
			delete conv;
			return res;
		}
		if (res->type_ > opr->type_)
            res = res->add(conv = res->convert(opr));
        else
            res = (conv = opr->convert(res))->add(opr);
        con=con->cdr;
        delete last;
        delete conv;
		for(;con;con=con->cdr)
		{
			opr=SCAST_NUMBER(con->car);
			last=res;
			if(res->type_>opr->type_)
				res=res->sub(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->sub(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};
class Mul : public Opt {
    /* Use the lowest level type */
    Number *calc(Cons *con) {
        Number *res = new Rational("1", "1"), *last;
        for (; con; con = con->cdr)
        {
			if(con->car->btype_!=2) throw 0;
			if(SCAST_NUMBER(con->car)->type_>3||SCAST_NUMBER(con->car)->type_<1)
			{
				throw 0;
			}
            Number *opr = SCAST_NUMBER(con->car), *conv;
            last = res;
            if (res->type_ > opr->type_)
                res = res->mul(conv = res->convert(opr));
            else
                res = (conv = opr->convert(res))->mul(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};
class Div:public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(con->car->btype_!=2) throw 0;
			if(SCAST_NUMBER(con->car)->type_>3||SCAST_NUMBER(con->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt==0) throw 0;
		Number *res=new Rational("1","1"),*last;
		Number *opr=SCAST_NUMBER(con->car),*conv;
		last=res;
//		Number *zero = new Float(0.0);
		if(cnt==1)
		{
			if(res->type_>opr->type_)
				res=res->div(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->div(opr);
			delete last;
			delete conv;
			return res;
		}
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=SCAST_NUMBER(con->car);
			last=res;
			if(res->type_>opr->type_)
				res=res->div(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->div(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};

class Abs : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->abs();

        return res;
    }
};


class Floor : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->floor();

        return res;
    }
};

class Ceiling : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->ceiling();

        return res;
    }
};

class Truncate : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->truncate();

        return res;
    }
};

class Round : public Opt{
	Number *calc(Cons *con){
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->round();
		
		return res;
	}
};

class Numerator : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->numerator();

        return res;
    }
};

class Denominator : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->denominator();

        return res;
    }
};

class Real_part : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->real_part();

        return res;
    }
};

class Imag_part : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->imag_part();

        return res;
    }
};


class Quotient:public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt!=2) throw 0;
		Number *result,*conv;
		Number *p = SCAST_NUMBER(con->car);
		Number *q = SCAST_NUMBER(con->cdr->car);
		if(p->type_>q->type_)
			result=p->quotient(conv=p->convert(q));
		else
			result=(conv=q->convert(p))->quotient(q);
		delete conv;
		return result;
	}
};

class Remainder:public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
			if(cnt != 2) throw 0;
		Number *result,*conv;
		Number *p = SCAST_NUMBER(con->car);
		Number *q = SCAST_NUMBER(con->cdr->car);
		if(p->type_>q->type_)
			result=p->remainder(conv=p->convert(q));
		else
			result=(conv=q->convert(p))->remainder(q);
		delete conv;
		return result;
	}
};

class Modulo:public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 2) throw 0;
		Number *result,*conv;
		Number *p = SCAST_NUMBER(con->car);
		Number *q = SCAST_NUMBER(con->cdr->car);
		if(p->type_>q->type_)
			result=p->modulo(conv=p->convert(q));
		else
			result=(conv=q->convert(p))->modulo(q);
		delete conv;
		return result;
	}	
};

class Gcd : public Opt {
/*
    Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ == 1) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res=new Rational("0","1"),*last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		last=res;
		if(cnt > 0){
			if (res->type_ > opr->type_)
      	      	res = res->add(conv = res->convert(opr));
      		else
				res = (conv = opr->convert(res))->add(opr);
      	  	con=con->cdr;
      	  	delete last;
      	  	delete conv;
    	}
		for(;con;con=con->cdr)
		{
			opr=SCAST_NUMBER(con->car);
			last=res;
			if(res->type_>opr->type_)	
				res=res->gcd(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->gcd(opr);
			delete last;
			delete conv;
		}
		return res;
	}
*/
	Number *calc(Cons *con) {
        Number *res = new Rational(1, 1), *last;
        for (; con; con = con->cdr)
        {
        	if(con->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(con->car)->type_>3||SCAST_NUMBER(con->car)->type_<1)
			{
				throw 0;
			}
            Number *opr = SCAST_NUMBER(con->car), *conv;
            last = res;
            if (res->type_ > opr->type_)
                res = res->gcd(conv = res->convert(opr));
            else
                res = (conv = opr->convert(res))->gcd(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};

class Lcm : public Opt {
/*
    Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ == 1) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res=new Rational("1","1"),*last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		last=res;
		if(cnt > 0){
			if (res->type_ > opr->type_)
      	    	res = res->mul(conv = res->convert(opr));
      		else
				res = (conv = opr->convert(res))->mul(opr);
      		con=con->cdr;
      		delete last;
      		delete conv;
    	}
		for(;con;con=con->cdr)
		{
			opr=SCAST_NUMBER(con->car);
			last=res;
			if(res->type_>opr->type_)	
				res=res->lcm(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->lcm(opr);
			delete last;
			delete conv;
		}
		return res;
	}
*/
	Number *calc(Cons *con) {
        Number *res = new Rational(1, 1), *last;
        for (; con; con = con->cdr)
        {
        	if(con->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(con->car)->type_>3||SCAST_NUMBER(con->car)->type_<1)
			{
				throw 0;
			}
            Number *opr = SCAST_NUMBER(con->car), *conv;
            last = res;
            if (res->type_ > opr->type_)
                res = res->lcm(conv = res->convert(opr));
            else
                res = (conv = opr->convert(res))->lcm(opr);
            delete last;
            delete conv;
        }
        return res;
    }
};

class Sqrt : public Opt {
    Number *calc(Cons *con) {
		if(con->car->btype_!=2) throw 0;
		Number *res = SCAST_NUMBER(con->car)->sqrt();

        return res;
    }
};

class Expt:public Opt{
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 2) throw 0;
		Number *result,*p,*q,*conv;
		p = SCAST_NUMBER(con->car);
		q = SCAST_NUMBER(con->cdr->car);
		if(p->type_>q->type_)
			result=p->expt(conv=p->convert(q));
		else
			result=(conv=q->convert(p))->expt(q);
		delete conv;
		return result;
	}	
};

class Inexact_exact : public Opt {
    Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->inexact_exact();
	}
};

class Exact_inexact : public Opt {
    Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->exact_inexact();
	}
};


class Minn : public Opt {
    Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt==0) throw 0;
		Number *res=new Rational("0","1"),*last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		last=res;
		if (res->type_ > opr->type_)
            res = res->add(conv = res->convert(opr));
        else
			res = (conv = opr->convert(res))->add(opr);
        con=con->cdr;
        delete last;
        delete conv;
		for(;con;con=con->cdr)
		{
			opr=SCAST_NUMBER(con->car);
			last=res;
			if(res->type_>opr->type_)	
				res=res->minn(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->minn(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};

class Maxx : public Opt {
    Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt==0) throw 0;
		Number *res=new Rational("0","1"),*last;
		Number *opr = SCAST_NUMBER(con->car), *conv;
		last=res;
		if (res->type_ > opr->type_)
            res = res->add(conv = res->convert(opr));
        else
			res = (conv = opr->convert(res))->add(opr);
        con=con->cdr;
        delete last;
        delete conv;
		for(;con;con=con->cdr)
		{
			opr=SCAST_NUMBER(con->car);
			last=res;
			if(res->type_>opr->type_)	
				res=res->maxx(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->maxx(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};

class J_integer:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_<1||tmp->car->btype_>4) throw 0;
			if(tmp->car->btype_ == 2) if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return con->car->judge_integer();
	}
};

class J_rational:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_<1||tmp->car->btype_>4) throw 0;
			if(tmp->car->btype_ == 2) if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return con->car->judge_rational();
	}
};

class J_real:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_<1||tmp->car->btype_>4) throw 0;
			if(tmp->car->btype_ == 2) if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return con->car->judge_real();
	}
};

class J_complex:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_<1||tmp->car->btype_>4) throw 0;
			if(tmp->car->btype_ == 2) if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return con->car->judge_complex();
	}
};

class J_number:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_<1||tmp->car->btype_>4) throw 0;
			if(tmp->car->btype_ == 2) if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return con->car->judge_number();
	}
};

class J_exact:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->judge_exact();
	}	
};

class J_inexact:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->judge_inexact();
	}	
};

class J_less:public Opt {	
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Number *p,*q,*conv;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_NUMBER(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_NUMBER(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			if(p->type_>q->type_)
				res=p->judge_less(conv=p->convert(q));
			else
				res=(conv=q->convert(p))->judge_less(q);
			delete conv;
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_eless:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Number *p,*q,*conv;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_NUMBER(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_NUMBER(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			if(p->type_>q->type_)
				res=p->judge_eless(conv=p->convert(q));
			else
				res=(conv=q->convert(p))->judge_eless(q);
			delete conv;
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_greater:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Number *p,*q,*conv;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_NUMBER(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_NUMBER(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			if(p->type_>q->type_)
				res=p->judge_greater(conv=p->convert(q));
			else
				res=(conv=q->convert(p))->judge_greater(q);
			delete conv;
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_egreater:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Number *p,*q,*conv;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_NUMBER(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_NUMBER(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			if(p->type_>q->type_)
				res=p->judge_egreater(conv=p->convert(q));
			else
				res=(conv=q->convert(p))->judge_egreater(q);
			delete conv;
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_zero:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->judge_zero();
	}
};

class J_negative:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->judge_negative();
	}
};

class J_positive:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->judge_positive();
	}
};

class J_odd:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->judge_odd();
	}
};

class J_even:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->judge_even();
	}
};

class Sin:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->sinn();
	}
};

class Cos:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->coss();
	}
};

class Tan:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->tann();
	}
};

class Asin:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->asinn();
	}
};

class Acos:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->acoss();
	}
};

class Atan:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->atann();
	}
};

class Exp:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->expp();
	}
};

class Log:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->logg();
	}
};

class M_rectangular:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 2) throw 0;
		Number *result;
		Number *conv;
		Number *p = SCAST_NUMBER(con->car);
		Number *q = SCAST_NUMBER(con->cdr->car);
		if(p->type_>q->type_)
			result=p->make_rectangular(conv=p->convert(q));
		else
			result=(conv=q->convert(p))->make_rectangular(q);
		delete conv;
		return result;
	}
};
class M_polar:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 2) throw 0;
		Number *result;
		Number *conv;
		Number *p = SCAST_NUMBER(con->car);
		Number *q = SCAST_NUMBER(con->cdr->car);
		if(p->type_>q->type_)
			result=p->make_polar(conv=p->convert(q));
		else
			result=(conv=q->convert(p))->make_polar(q);
		delete conv;
		return result;
	}
};
class Magnitude:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->magnitude();
	}
};
class Angle:public Opt {
	Number *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ == 1) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->angle();
	}
};

class J_char:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_<1||tmp->car->btype_>4) throw 0;
			if(tmp->car->btype_ == 2) if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return con->car->judge_char();
	}
};

class J_string:public Opt {
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_<1||tmp->car->btype_>4) throw 0;
			if(tmp->car->btype_ == 2) if(SCAST_NUMBER(tmp->car)->type_>3||SCAST_NUMBER(tmp->car)->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if(cnt != 1) throw 0;
		return con->car->judge_string();
	}
};


class J_charless:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 3) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Char *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_CHAR(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_CHAR(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_charless(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_char_ciless:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 3) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Char *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_CHAR(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_CHAR(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_charciless(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_chareless:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 3) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Char *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_CHAR(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_CHAR(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_chareless(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_char_cieless:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 3) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Char *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_CHAR(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_CHAR(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_charcieless(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_char_alphabetic:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_CHAR(con->car)->judge_char_alphabetic();
	}
};

class J_char_numeric:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_CHAR(con->car)->judge_char_numeric();
	}
};

class J_char_whitespace:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_CHAR(con->car)->judge_char_whitespace();
	}
};

class J_char_upper_case:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_CHAR(con->car)->judge_char_upper_case();
	}
};

class J_char_lower_case:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_CHAR(con->car)->judge_char_lower_case();
	}
};

class C_char_integer:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_CHAR(con->car)->char_integer();
	}
};

class C_integer_char:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=2) throw 0;
			if(SCAST_NUMBER(tmp->car)->type_!=1) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_NUMBER(con->car)->integer_char();
	}
};


class C_char_upcase:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_CHAR(con->car)->char_upcase();
	}
};

class C_char_downcase:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_CHAR(con->car)->char_downcase();
	}
};

class M_string:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			cnt++;
			if(cnt==1&&tmp->car->btype_!=2) throw 0;
			if(cnt==2&&tmp->car->btype_!=3) throw 0;
		}
		if(cnt != 2) throw 0;
		return SCAST_NUMBER(con->car)->make_string(SCAST_CHAR(con->cdr->car));
	}
};

class S_string:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=3) throw 0;
			cnt++;
		}
		if(cnt == 0) return new String("");
		if(cnt == 1){
			Base *res;
			res=SCAST_CHAR(con->car)->s_string_one();
			return res;
		}
		
		Base *res,*last;
		Char *opr = SCAST_CHAR(con->car), *conv = SCAST_CHAR(con->cdr->car);
        res = opr->s_string(conv);
        if(cnt == 2) return res;
        con=con->cdr;
        con=con->cdr;
		for(;con;con=con->cdr)
		{
			opr=SCAST_CHAR(con->car);
			last=res;
			res = SCAST_STRING(res)->s_string(opr);
			delete last;
		}
		return res;
	}
};

class S_string_length:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=4) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_STRING(con->car)->string_length();
	}
};

class S_string_ref:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			cnt++;
			if(cnt==1&&tmp->car->btype_!=4) throw 0;
			if(cnt==2&&tmp->car->btype_!=2) throw 0;
		}
		if(cnt != 2) throw 0;
		return SCAST_STRING(con->car)->string_ref(SCAST_NUMBER(con->cdr->car));
	}
};

class S_substring:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			cnt++;
			if(cnt==1&&tmp->car->btype_!=4) throw 0;
			if(cnt==2&&tmp->car->btype_!=2) throw 0;
			if(cnt==3&&tmp->car->btype_!=2) throw 0;
		}
		if(cnt == 2){
			return SCAST_STRING(con->car)->subtring(SCAST_NUMBER(con->cdr->car));
		}
		else if(cnt == 3){
			return SCAST_STRING(con->car)->substring_two(SCAST_NUMBER(con->cdr->car),SCAST_NUMBER(con->cdr->cdr->car));
		}
		else throw 0;		
	}
};

class S_string_append:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=4) throw 0;
			cnt++;
		}
		if(cnt == 0) return new String("");
		if(cnt == 1){
			Base *res;
			res=SCAST_STRING(con->car)->s_string_append_one();
			return res;
		}
		Base *res,*last;
		String *opr;
        res = SCAST_STRING(con->car)->s_string_append_one();
        con=con->cdr;
		for(;con;con=con->cdr)
		{
			opr=SCAST_STRING(con->car);
			last=res;
			res = SCAST_STRING(res)->s_string_append(opr);
			delete last;
		}
		return res;
	}
};

class S_string_copy:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_!=4) throw 0;
			cnt++;
		}
		if(cnt != 1) throw 0;
		return SCAST_STRING(con->car)->s_string_copy();
	}
};

class J_stringless:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 4) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		String *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_STRING(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_STRING(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_stringless(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_string_ciless:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 4) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		String *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_STRING(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_STRING(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_string_ciless(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_stringeless:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 4) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		String *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_STRING(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_STRING(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_stringeless(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_string_cieless:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 4) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		String *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_STRING(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_STRING(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_string_cieless(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_stringe:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 4) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		String *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_STRING(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_STRING(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_stringequal(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_string_cie:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 4) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		String *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_STRING(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_STRING(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_string_ciequal(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_chare:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 3) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Char *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_CHAR(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_CHAR(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_charequal(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}
};

class J_char_cie:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 3) throw 0;
			cnt++;
		}
		if(cnt<=1) throw 0;
		Base *res,*last;
		Char *p,*q;
		Boolean *judge_re;
		bool flag=true;
        for(;con;con=con->cdr)
		{
			p=SCAST_CHAR(con->car);
			if(con->cdr==NULL) break;
			q=SCAST_CHAR(con->cdr->car);
			if(flag) flag=false;
			else delete last;
			res=p->judge_char_ciequal(q);
			judge_re=SCAST_BOOLEAN(res);
			if(!judge_re->flag) return res;
			last=res;
		}
		return res;
	}	
};

class Equal:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_<1||tmp->car->btype_>4) throw 0;
			cnt++;
		}
		if(cnt!=2) throw 0;
		Base *res;
		if(con->car->btype_!=con->cdr->car->btype_){
			return new Boolean(false);
		}
		else{
			int t=con->car->btype_;
			switch(t){
				case 1:
					res=SCAST_BOOLEAN(con->car)->judge_equal(SCAST_BOOLEAN(con->cdr->car));
					break;
				case 2:
					if(SCAST_NUMBER(con->car)->type_!=SCAST_NUMBER(con->cdr->car)->type_){
						res=new Boolean(false);
					}
					else{
						res=SCAST_NUMBER(con->car)->judge_equal(SCAST_NUMBER(con->cdr->car));
					}
					break;
				case 3:
					res=SCAST_CHAR(con->car)->judge_equal(SCAST_CHAR(con->cdr->car));
					break;
				case 4:
					res=SCAST_STRING(con->car)->judge_equal(SCAST_STRING(con->cdr->car));
					break;
			}
			return res;
		}
	}	
};

class S_number_string:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 2) throw 0;
			cnt++;
		}
		if(cnt!=1) throw 0;
		Base *res;
		res=SCAST_NUMBER(con->car)->number_string();
		return res;
	}	
};

class S_string_number:public Opt{
	Base *calc(Cons *con){
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->btype_ != 4) throw 0;
			cnt++;
		}
		if(cnt!=1) throw 0;
		Base *res;
		res=SCAST_STRING(con->car)->string_number();
		return res;
	}
};

