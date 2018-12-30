#include"mystring.h"
#include<sstream>
#include<string>
#include<string.h>
#include<vector>
using namespace std;
mystring::mystring(){
    stri = "null";
}

mystring::mystring(const string &s){
    stri = s ;
}

void mystring::split(){
    int i = 0;
    //string str2;
    string str3;
    //str2 = stri;
    stringstream ss(stri);
    while(ss.eof()!=true){
        getline(ss,str3,' ');
        if(str3!=""){i = i + 1;}
    }
   // str = (string*)realloc(str,i*sizeof(string));
    str.resize(i);
    ss.clear();
    stringstream ss1(stri) ;
    //cout<<i<<endl;
    i = 0;
    while(ss1.eof()!=true){
        getline(ss1,str3,' ');
        if(str3!=""){str[i]=str3;
        i = i + 1;}
}
}

mystring::~mystring(){

}
