#include "calc_exp.h"
#include "opt.h"
#include "compare.h"
#include "next_token.h"
#include <cstdio>

Base *calc_exp(){
    char *tk0 = next_token();
    Base *res;
    if (*tk0 == '(')
    {
        char *tk1 = next_token();
        Opt *opt;
        Cons *cons = new Cons(NULL, NULL), *tail = cons;
        Base *val;
		if(tk1==NULL){printf("123");throw 0;}
		if(strcmp(tk1,"+")==0)opt=new Add();
		else if(strcmp(tk1,"-")==0)opt=new Sub();
		else if(strcmp(tk1,"*")==0)opt=new Mul();
		else if(strcmp(tk1,"/")==0)opt=new Div();
		else if(strcmp(tk1,"abs")==0)opt=new Abs();
		else if(strcmp(tk1,"floor")==0)opt=new Floor();
		else if(strcmp(tk1,"ceiling")==0)opt=new Ceiling();
		else if(strcmp(tk1,"truncate")==0)opt=new Truncate();
		else if(strcmp(tk1,"round")==0)opt=new Round();
		
		else if(strcmp(tk1,"quotient")==0)opt=new Quotient();
		else if(strcmp(tk1,"remainder")==0)opt=new Remainder();
		else if(strcmp(tk1,"modulo")==0)opt=new Modulo();
		else if(strcmp(tk1,"gcd")==0)opt=new Gcd();
		else if(strcmp(tk1,"lcm")==0)opt=new Lcm();
		else if(strcmp(tk1,"expt")==0)opt=new Expt();
		else if(strcmp(tk1,"sqrt")==0)opt=new Sqrt();

		else if(strcmp(tk1,"numerator")==0)opt=new Numerator();
		else if(strcmp(tk1,"denominator")==0)opt=new Denominator();
		else if(strcmp(tk1,"real-part")==0)opt=new Real_part();
		else if(strcmp(tk1,"imag-part")==0)opt=new Imag_part();
		
		else if(strcmp(tk1,"inexact->exact")==0)opt=new Inexact_exact();
		else if(strcmp(tk1,"exact->inexact")==0)opt=new Exact_inexact();
		else if(strcmp(tk1,"min")==0)opt=new Minn();
		else if(strcmp(tk1,"max")==0)opt=new Maxx();
		
		else if(strcmp(tk1,"integer?")==0)opt=new J_integer();
		else if(strcmp(tk1,"rational?")==0)opt=new J_rational();
		else if(strcmp(tk1,"real?")==0)opt=new J_real();
		else if(strcmp(tk1,"complex?")==0)opt=new J_complex();
		else if(strcmp(tk1,"number?")==0)opt=new J_number();
		
		else if(strcmp(tk1,"<")==0)opt=new J_less();
		else if(strcmp(tk1,"<=")==0)opt=new J_eless();
		else if(strcmp(tk1,">")==0)opt=new J_greater();
		else if(strcmp(tk1,">=")==0)opt=new J_egreater();
		else if(strcmp(tk1,"exact?")==0)opt=new J_exact();
		else if(strcmp(tk1,"inexact?")==0)opt=new J_inexact();
		else if(strcmp(tk1,"zero?")==0)opt=new J_zero();
		else if(strcmp(tk1,"negative?")==0)opt=new J_negative();
		else if(strcmp(tk1,"positive?")==0)opt=new J_positive();
		else if(strcmp(tk1,"odd?")==0)opt=new J_odd();
		else if(strcmp(tk1,"even?")==0)opt=new J_even();
		
		else if(strcmp(tk1,"sin")==0)opt=new Sin();
		else if(strcmp(tk1,"cos")==0)opt=new Cos();
		else if(strcmp(tk1,"tan")==0)opt=new Tan();
		else if(strcmp(tk1,"asin")==0)opt=new Asin();
		else if(strcmp(tk1,"acos")==0)opt=new Acos();
		else if(strcmp(tk1,"atan")==0)opt=new Atan();
		else if(strcmp(tk1,"exp")==0)opt=new Exp();
		else if(strcmp(tk1,"log")==0)opt=new Log();
		
		else if(strcmp(tk1,"make-rectangular")==0)opt=new M_rectangular();
		else if(strcmp(tk1,"make-polar")==0)opt=new M_polar();
		else if(strcmp(tk1,"magnitude")==0)opt=new Magnitude();
		else if(strcmp(tk1,"angle")==0)opt=new Angle();
	
		else if(strcmp(tk1,"char?")==0)opt=new J_char();
		else if(strcmp(tk1,"char<?")==0)opt=new J_charless();
		else if(strcmp(tk1,"char-ci<?")==0)opt=new J_char_ciless();
		else if(strcmp(tk1,"char<=?")==0)opt=new J_chareless();
		else if(strcmp(tk1,"char-ci<=?")==0)opt=new J_char_cieless();
		else if(strcmp(tk1,"char-alphabetic?")==0)opt=new J_char_alphabetic();
		else if(strcmp(tk1,"char-numeric?")==0)opt=new J_char_numeric();
		else if(strcmp(tk1,"char-whitespace?")==0)opt=new J_char_whitespace();
		else if(strcmp(tk1,"char-upper-case?")==0)opt=new J_char_upper_case();
		else if(strcmp(tk1,"char-lower-case?")==0)opt=new J_char_lower_case();
		else if(strcmp(tk1,"char->integer")==0)opt=new C_char_integer();
		else if(strcmp(tk1,"integer->char")==0)opt=new C_integer_char();
		else if(strcmp(tk1,"char-upcase")==0)opt=new C_char_upcase();
		else if(strcmp(tk1,"char-downcase")==0)opt=new C_char_downcase();



		else if(strcmp(tk1,"string?")==0)opt=new J_string();
		else if(strcmp(tk1,"make-string")==0)opt=new M_string();
		else if(strcmp(tk1,"string")==0)opt=new S_string();
		else if(strcmp(tk1,"string-length")==0)opt=new S_string_length();
		else if(strcmp(tk1,"string-ref")==0)opt=new S_string_ref();

		else if(strcmp(tk1,"string<?")==0)opt=new J_stringless();
		else if(strcmp(tk1,"string-ci<?")==0)opt=new J_string_ciless();
		else if(strcmp(tk1,"string<=?")==0)opt=new J_stringeless();
		else if(strcmp(tk1,"string-ci<=?")==0)opt=new J_string_cieless();

		else if(strcmp(tk1,"substring")==0)opt=new S_substring();
		else if(strcmp(tk1,"string-append")==0)opt=new S_string_append();
		else if(strcmp(tk1,"string-copy")==0)opt=new S_string_copy();


		else if(strcmp(tk1,"equal?")==0)opt=new Equal();

		else if(strcmp(tk1,"string=?")==0)opt=new J_stringe();
		else if(strcmp(tk1,"string-ci=?")==0)opt=new J_string_cie();
		else if(strcmp(tk1,"char=?")==0)opt=new J_chare();
		else if(strcmp(tk1,"char-ci=?")==0)opt=new J_char_cie();

		else if(strcmp(tk1,"number->string")==0)opt=new S_number_string();
		else if(strcmp(tk1,"string->number")==0)opt=new S_string_number();


		
		else throw 0;
        while ((val = calc_exp()))
        {
            tail->cdr = new Cons(val, NULL);
            tail = tail->cdr;
        }
        res = opt->calc(cons->cdr);
        for (Cons *np; cons; cons = np)
        {
            np = cons->cdr;
            delete cons;
        }
    }
    else if (*tk0 == ')')
	{
        return NULL;
	}
    else
    {
		res=Boolean::from_string(tk0);
		if(!res) {res = Char::from_string(tk0);}
		if(!res) {res = String::from_string(tk0);}
		if(!res) {res = Rational::from_string(tk0);}
		if(!res) {res = Float::from_string(tk0);}
		if(!res) {res = Complex::from_string(tk0);}
		if(res==NULL){throw 0;}
    }
    return res;
}
