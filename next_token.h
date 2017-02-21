#pragma once
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;
FILE *input = stdin;
string s="";
int len=0;
char *next_token() {
    char *res = NULL;
	string ans;
    int cur=0;
    int ch;
    bool flag=false,flag2=false;
    while (!cur)
    {
//		std::cout  << ans << '*' << std::endl;
//		std::cout << '*' << cur  << std::endl;
//		std::cout << s << std::endl;
		if(flag2) break;
		if(flag){
			if ((ch = fgetc(input)) == EOF) break;
			switch(ch)
			{
				case '"':
	   				flag2=true;
	   				s=s+(char)ch;
	   				len++;
	   				ans=s;
	   				cur=len;
	   				s="";
	   				len=0;
	   				break;
	   			default:
	   				s=s+(char)ch;
	   				len++;
			}
			continue;
		}
        if(len > 0 && (s[0] == '(' || s[0] == ')'))// for cases:'(' ')'
        {
            ans=s;
            cur=len;
            s="";
            len=0;
            break;
        }
        if ((ch = fgetc(input)) == EOF)
            break;
//      	std::cout << ch << std::endl;
        switch (ch)
        {
            case '(':
            case ')':
                if(len>0)
                    ans=s;cur=len;
                s="";
                s=s+(char)ch;
                len=1;
                break;
            case '"':
            	if(len>0){
            		s=s+(char)ch;
            		len++;
				}
				else{
					flag=true;
					s=s+(char)ch;
					len++;
				}
				break;
            default:
                if (isspace(ch))
                {
                	if(s=="#\\"){
    					if(ch==' '){
							s+=' ';
							++len;
						}
						else if(ch=='\n'){
							s+='\n';
							++len;
						}
						else if(ch=='\t'){
							s+='\t';
							++len;
						}
					}
                    if(len>0)
                         ans=s;cur=len;
                    s="";
                    len=0;
                }
                else
				{
					s=s+(char)ch;
                    len++;
                }
        }
    }
    if(cur>0)
    {
        res=new char[cur+3];
        for(int i=0;i<=cur-1;i++)
            res[i]=ans[i];
		res[cur]='\0';
	}	
//	std::cout << '*' << '*' << res << '*' << std::endl;
    return res;
}
