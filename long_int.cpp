// long_int.cpp

#include "long_int.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iomanip>


LongInt::LongInt(int number){
	int temp;
	if(number>=0){
		sign=true;
		temp=number;
	}
	else{
		sign=false;
		temp=number*(-1);
	}
	
	a=new int[mlen];
	memset(a,0,sizeof(int)*mlen);
	
	if(number==0){
		a[0]=0;
		len=1;
		return;
	}
	else{
		while(true){
			if(temp!=0){
				a[len++]=temp%1000;
				temp=temp/1000;
			}
			else break;
		}
	}
	
	//std::cout << "OK" << std::endl;
}

LongInt::LongInt(long long number){
	long long temp;
	if(number>=0){
		sign=true;
		temp=number;
	}
	else{
		sign=false;
		temp=number*(-1);
	}
	
	a=new int[mlen];
	memset(a,0,sizeof(int)*mlen);
	
	if(number==0){
		a[0]=0;
		len=1;
		return;
	}
	else{
		while(true){
			if(temp!=0){
				a[len++]=temp%1000;
				temp=temp/1000;
			}
			else break;
		}
	}
	
	//std::cout << "OK" << std::endl;
}

LongInt::LongInt(const char* s){
//	mlen=strlen(s)/4*2;
	a=new int[mlen];
	memset(a,0,sizeof(int)*mlen);
	if(s[0]=='-'){
		sign=false;
		s+=1;
	}
	else{
		sign=true;
	}
	
	bool flag=true;
	for(int i=0; i<strlen(s); ++i){
		if(s[i]!='0') flag=false;
	}
	if(flag){
		len=1;
		a[0]=0;
	}
	else{
		while(s[0]!='\0'&&s[0]=='0'){
			s+=1;
		}
	}
	
//	std::cout << s << std:: endl;
	len=(strlen(s))/3;
	if((strlen(s))%3) ++len;
	int temp=0,index=0,k;
    for(int i=strlen(s)-1; i>=0; i-=3){
    	temp=0;
        k=i-2;
        if(k<0) k=0;
        for(int j=k; j<=i; ++j){
        	temp=temp*10+(s[j]-'0');
		}
       	a[index++]=temp;
	}
//	std::cout << len << ' ' << *this << std::endl;
}

LongInt::LongInt(const LongInt &long_int2){
	len=long_int2.len;
	mlen=long_int2.mlen;
	sign=long_int2.sign;
	a=new int[mlen];
	memset(a,0,sizeof(int)*mlen);
	
	for(int i=0; i<len; ++i){
		a[i]=long_int2.a[i];
	}
}

LongInt::operator bool(){
	if(len==1&&a[0]==0) return false;
	else return true;
}

LongInt::operator double(){
	double temp=0;
	for(int i=len-1; i>=0; --i){
		temp=temp*1e3+a[i];
	}
	if(sign) return temp;
	else return -temp;
}

LongInt::operator int(){
	int temp=0;
	for(int i=len-1; i>=0; --i){
		temp=temp*1000+a[i];
	}
	if(sign) return temp;
	else return -temp;
}

bool LongInt::operator!=(const LongInt &long_int2) const{
	if(len==1&&long_int2.len==1&&a[0]==0&&long_int2.a[0]==0){
		return false;
	}
	if(len==long_int2.len&&sign==long_int2.sign){
		bool flag=true;
		int i=0;
		while(flag){
			if(a[i]==long_int2.a[i]) ++i;
			else flag=false;
			if(i==len) break;
		}
		if(!flag)return true;
		else return false;
	}
	else return true;
}

bool LongInt::operator<(const LongInt &long_int2) const{
	if(sign&&long_int2.sign){
		if(len<long_int2.len) return true;
		else{
			if(len>long_int2.len) return false;
			else{
				for(int i=len-1; i>0; --i){
					if(a[i]!=long_int2.a[i]) return a[i]<long_int2.a[i];
				}
				return a[0]<long_int2.a[0];
			}
		}
	}
	else{
		if((!sign)&&(!long_int2.sign)){
			if(len<long_int2.len) return false;
			else{
				if(len>long_int2.len) return true;
				else{
					for(int i=len-1; i>0; --i){
						if(a[i]!=long_int2.a[i]) return a[i]>long_int2.a[i];
					}
					return a[0]>long_int2.a[0];
				}
			}
		}
		else{
			if(!sign) return true;
			else return false;
		}
	}
}

bool LongInt::operator==(const LongInt &long_int2) const{
	if(len==1&&long_int2.len==1&&a[0]==0&&long_int2.a[0]==0){
		return true;
	}
	if((len==long_int2.len)&&(sign==long_int2.sign)){
		for(int i=len-1; i>=0; --i){
			if(a[i]!=long_int2.a[i]) return false;
		}
		return true;
	}
	else return false;
}

bool LongInt::abscmp(const LongInt &long_int2) const{
	if(len<long_int2.len) return true;
	else{
		if(len>long_int2.len) return false;
		else{
			for(int i=len-1; i>0; --i){
				if(a[i]!=long_int2.a[i]) return a[i]<long_int2.a[i];
			}
			return a[0]<long_int2.a[0];
		}
	}
}

LongInt &LongInt::operator=(const LongInt &long_int2){
	if (this==&long_int2) return *this;
	
	delete [] a;
	len=long_int2.len;
	mlen=long_int2.mlen;
	sign=long_int2.sign;
	a=new int[mlen];
	memset(a,0,sizeof(int)*mlen);
	
	for(int i=0; i<len; ++i){
		a[i]=long_int2.a[i];
	}
	
//	std::cout << *this << std::endl;

	return *this;
}

LongInt LongInt::Radd(const LongInt &long_int2) const{
	LongInt t(*this);
	int lener;
	lener=long_int2.len>len ? long_int2.len:len;
//	t.len=lener;
	
	while(lener>=t.mlen){
		t.double_space();
	}
	
    for(int i=0 ; i<lener ; ++i) 
    { 
        t.a[i]+=long_int2.a[i]; 
        if(t.a[i]>999) 
        { 
            ++t.a[i+1]; 
            t.a[i]-=1000; 
        }
    }
    
    if(t.a[lener]!=0) 
		t.len=lener+1;
    else
        t.len=lener;   

    return t;
}

LongInt LongInt::operator+(const LongInt &long_int2) const{
	if((sign&&long_int2.sign) || ((!sign)&&(!long_int2.sign))){
		return Radd(long_int2);
	}
	else{
		if(abscmp(long_int2)){
			if(sign){
				LongInt tmp;
				tmp=Rmin(long_int2);
				tmp.sign=false;
				return tmp;
			}
			else{
				LongInt tmp;
				tmp=Rmin(long_int2);
				tmp.sign=true;
				return tmp;
			}
		}
		else{
			if(sign){
				LongInt tmp;
				tmp=Rmin(long_int2);
				tmp.sign=true;
				return tmp;
			}
			else{
				LongInt tmp;
				tmp=Rmin(long_int2);
				tmp.sign=false;
				return tmp;
			}
		}
	}
}

LongInt LongInt::Rmin(const LongInt &long_int2) const{
	LongInt t1,t2;
	int lener;
    
    if(!abscmp(long_int2))
    {
        t1=*this;
        t2=long_int2;
    }
    else
    {
        t1=long_int2;
        t2=*this;
    }
    lener=t1.len;
//    std::cout << '*' << lener << std::endl;
    for(int i=0; i<lener ; ++i)
    {
        if(t1.a[i] < t2.a[i])
        { 
            int j = i + 1; 
            while(t1.a[j] == 0)
                j++; 
            t1.a[j--]--; 
            while(j > i)
                t1.a[j--]+=999;
            t1.a[i] = t1.a[i]+1000-t2.a[i]; 
        } 
        else
            t1.a[i] = t1.a[i]-t2.a[i];
    }
//  std::cout << t1 << std::endl;
//  t1.len = lener;
    while(t1.a[t1.len-1] == 0 && t1.len > 1)
    {
//    	std::cout << t1.a[t1.len-1] << std::endl;
        t1.len--; 
    }
//    std::cout << t1.len << std::endl;
    return t1; 
}
	

LongInt LongInt::operator-(const LongInt &long_int2) const{
	if((sign&&(!long_int2.sign)) || ((!sign)&&(long_int2.sign))){
		return Radd(long_int2);
	}
	else{
		if(abscmp(long_int2)){
			if(sign){
				LongInt tmp;
				tmp=Rmin(long_int2);
				tmp.sign=false;
				return tmp;
			}
			else{
				LongInt tmp;
				tmp=Rmin(long_int2);
				tmp.sign=true;
				return tmp;
			}
		}
		else{
			if(sign){
				LongInt tmp;
				tmp=Rmin(long_int2);
				tmp.sign=true;
				return tmp;
			}
			else{
				LongInt tmp;
				tmp=Rmin(long_int2);
				tmp.sign=false;
				return tmp;
			}
		}
	}
}

LongInt LongInt::Rmul(const LongInt &long_int2) const{
	LongInt ans; 
    int up; 
    int temp,temp1;
	int i,j;   
    for(i=0; i<len; ++i)
    { 
        up = 0; 
        for(j=0; j<long_int2.len; ++j)
        { 
            temp = a[i] * long_int2.a[j] + ans.a[i + j] + up; 
            if(temp>999)
            { 
                temp1 = temp - temp / (1000) * (1000); 
                up = temp / 1000;
				while(i+j>=ans.mlen) ans.double_space();
                ans.a[i + j] = temp1; 
            } 
            else
            { 
                up = 0;
				while(i+j>=ans.mlen) ans.double_space(); 
                ans.a[i + j] = temp; 
            } 
        } 
        if(up != 0) {
        	while(i+j>=ans.mlen) ans.double_space();
			ans.a[i + j] = up;
		}
    } 
    ans.len = i + j; 
    while(ans.a[ans.len - 1] == 0 && ans.len > 1) ans.len--; 
    return ans; 
}

LongInt LongInt::operator*(const LongInt &long_int2) const{
	if((sign&&long_int2.sign) || (!sign)&&(!long_int2.sign)){
		LongInt tmp=Rmul(long_int2);
		tmp.sign=true;
		return tmp;
	}
	else{
		LongInt tmp=Rmul(long_int2);
		tmp.sign=false;
		return tmp;
	}
}

LongInt LongInt::Rdiv(const LongInt &long_int2) const{
	
	if(long_int2.len == 1 ) assert(long_int2.a[0] && "devide zero");
	
 	LongInt ans(*this);
 	ans.clean();
 	LongInt t1(*this),t2(long_int2);
 	
 	if(abscmp(long_int2)){
 		return ans;
	}
	ans.len = t1.len-t2.len+1;
	int i,j,l;
	l = ans.len;

	while(l--){
		ans.a[l] = 111;
		while(!(abscmp(ans*t2)) || ans*t2==t1){
			ans.a[l] += 100;
		}
		ans.a[l] -= 100;
		while(!(abscmp(ans*t2)) || ans*t2==t1){
			ans.a[l] += 10;
		}
		ans.a[l] -= 10;
		while(!(abscmp(ans*t2)) || ans*t2==t1){
			ans.a[l] += 1;
		}
		ans.a[l] -= 1;
//		while(!(abscmp(ans*t2)) || ans*t2==t1){
//			ans.a[l] += 1;
//		}
//		ans.a[l] -= 1;		
	}
	while(ans.a[ans.len-1] == 0 && ans.len > 1) ans.len--;
    return ans; 
}

LongInt LongInt::operator/(const LongInt &long_int2) const{
	if((sign&&long_int2.sign) || (!sign)&&(!long_int2.sign)){
		LongInt tmp=Rdiv(long_int2);
		tmp.sign=true;
		return tmp;
	}
	else{
		LongInt tmp=Rdiv(long_int2);
		tmp.sign=false;
		return tmp;
	}
}

LongInt LongInt::operator%(const LongInt &long_int2) const{
	if(long_int2.len == 1 ) assert(long_int2.a[0] && "devide zero");
	LongInt ans;
//	std::cout << (*this/long_int2) << std::endl;
//	std::cout << long_int2*(*this/long_int2) << std::endl;
	ans = *this - long_int2*(*this/long_int2);
	bool flag=*this<long_int2*(*this/long_int2);
//	std::cout << flag << std::endl;
//	std::cout << ans << std::endl;
//	if(sign) ans.sign=true;
//	else ans.sign=false;
	return ans;
}

LongInt gcdd(LongInt &long_int1, LongInt &long_int2){
	if(long_int1==LongInt(0) && long_int2==LongInt(0)) return LongInt(0);
	if(long_int1==LongInt(0)) return long_int2;
	if(long_int2==LongInt(0)) return long_int1;
	LongInt a,b,c;
	a = max(long_int1,long_int2);
	b = min(long_int1,long_int2);
	while((c=a%b)!=LongInt(0)){
		a = b;
		b = c;
	}
	b.sign=true;
	return b;	
}

LongInt lcmm(LongInt &long_int1, LongInt &long_int2){
	LongInt tmp;
	if(long_int1 == LongInt(0) || long_int2 == LongInt(0)) return LongInt(0);
	tmp=long_int1*long_int2/gcdd(long_int1,long_int2);
	tmp.sign=true;
	return tmp;
}

LongInt max(const LongInt &long_int1, const LongInt &long_int2){
	return long_int1<long_int2?long_int2:long_int1;
}

LongInt min(const LongInt &long_int1, const LongInt &long_int2){
	return long_int1<long_int2?long_int1:long_int2;
}

void LongInt::print(std::ostream& o)const{
	if(len==1&&a[0]==0) o << 0;
	else{
		if(!sign) o << '-'; 
    	o << a[len - 1]; 
   		for(int i=len - 2 ; i>= 0; --i){
   			o << std::setw(3) << std::setfill('0') << a[i];
		   }
	}
}

void LongInt::double_space(){
	int *b;
	mlen=2*mlen;
	if(mlen<=1) mlen=2;
	while(mlen<=len) mlen*=2;
	b=new int[mlen];
	memset(b,0,sizeof(int)*mlen);
	
	for(int i=0; i<len; ++i){
		b[i]=a[i];
	}
	
	delete [] a;
	a=b;
}

void LongInt::clean(){
	memset(a,0,sizeof(int)*mlen);
	len = 1;
}

std::ostream & operator<<(std::ostream &os, const LongInt &obj){
	if(obj.len==1&&obj.a[0]==0){
		os << 0;
		return os;
	}
	else{
		if(!obj.sign) os << '-'; 
    	os << obj.a[obj.len - 1]; 
   		for(int i=obj.len - 2 ; i>= 0; --i){
   			os.width(3);
   			os.fill('0');
   			os<<obj.a[i];
		   }
    	return os;
	}
}
