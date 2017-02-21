#include "calc_exp.h"
#include "rational.h"
#include "complex.h"
#include <cmath>
#include <iostream>
using namespace std;

int main() {

    try {
    	Base *res;
		res=calc_exp();
		res->print();  
	}
	catch(int){cerr<<"Wrong";}
	
    return 0;
}
