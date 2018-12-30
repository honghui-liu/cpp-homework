#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct MyString{

    char *pstr;

    MyString();
    MyString(char);
    MyString(const char*);
    MyString(const MyString&);
    ~MyString();

    int count(char);
    int count(const char*);

    void operator=(char);
    void operator=(const char*);
    void operator=(const MyString&);
    //void operator=(string);

    MyString operator+(char);
    MyString operator+(const char*);
    MyString operator+(const MyString&);

public:
    friend MyString operator+(char, const MyString&);
    friend MyString operator+(const char*, const MyString&);
    friend ostream& operator<<(ostream&, MyString&);
};

MyString::MyString(){
    char* pTmp = (char*) malloc(1);
    if(pTmp == NULL){
        printf("Alloc memory failure");
        exit(1);
    }else{
        pTmp[0] = '\0';
        pstr = pTmp;
    }
}

MyString::MyString(char v){
    pstr = NULL;
    *this = v;
}

MyString::MyString(const char* v){
    pstr = NULL;
    *this = v;
}

MyString::MyString(const MyString& v){
    pstr = NULL;
    *this = v;
}

MyString::~MyString(){
    free(pstr);
}


int MyString::count(char v){
    int n = 0;
    for(int i=0; i<strlen(pstr); ++i){
        if(pstr[i] == v)
            ++n;
    }
    return n;
}

int MyString::count(const char* v){
    int n = 0;
    for(int i=0; i<strlen(v); ++i){
        n += count(v[i]);
    }
    return n;
}

void MyString::operator=(const char* v){
    char* pTmp = (char*)realloc(pstr, strlen(v)+1);
    if(pTmp == NULL){
        printf("Alloc memory failure");
        exit(1);
    }else{
        strcpy(pTmp, v);
        pstr = pTmp;
    }
}

void MyString::operator=(char v){
    char s[2] = {v,'\0'};
    *this = s;
}

void MyString::operator=(const MyString& v){
    *this = v.pstr;
}

MyString MyString::operator+(char v){
    //char s1[2]={v,'\0'};
    //string s = pstr;
    MyString s;
    s=v;
    //const char *p=s.data();
    MyString temp;
    //temp.pstr=(char*)realloc(pstr,strlen(s)+1);
    temp = *this + s;
    return temp;
}

MyString MyString::operator+(const char* v){
 char* s = pstr;
 MyString s1;
 s1=s;
 //strcpy(s,pstr);
 strcat(s1.pstr,v);
 MyString temp;
 temp = s1;
 return temp;
}

MyString MyString::operator+(const MyString& v){
    MyString temp;
    char* s=pstr;
    MyString s1;
    s1=s;
    //strcpy(s,pstr);
    strcat(s1.pstr,v.pstr);
    temp = s1;
    return temp;
}

MyString operator+(char v,const MyString& s){
    //char s1[2]={v,'\0'};
    //string s2=s.pstr;
    //string s3=s1+s2;
    //const char *p=s3.data();
    MyString s2;
    s2=v;
    MyString temp;
    temp = s2+s;
    return temp;
}

MyString operator+(const char* v, const MyString& s){
    //string s1=v,s2=s.pstr;
    //string s3=s1+s2;
    MyString s1;
    s1=v;
    //const char *p=s3.data();
    MyString temp;
    temp = s1+s;
    return temp;
}

ostream& operator<<(ostream& os, MyString& v){
    os << v.pstr;
    return os;
}

int main(){
    MyString str = "love",str1,str2="physics",str3(str2),str4,str5,str6;
    char a='i';
    const char* b="shanghai";
    cout<<"str= "<<str<<endl;
    cout<<"str2="<<str2<<endl;
    cout<<"char a= "<<a<<endl;
    cout<<"const char* b= "<<b<<endl;
    cout<<endl;
    str1 =a;
    cout<<"result of str1 = a: "<<str1<<endl;
    str1=b;
    cout<<"result of str1 = b: "<<str1<<endl;
    str1=str;
    cout<<"result of str1 = str: "<<str1<<endl;
    cout<<endl;
    str4=str+a;
    cout<<"result of str+a: "<<str4<<endl;
    str4=a+str;
    cout<<"result of a+str: "<<str4<<endl;
    cout<<endl;
    str6 = str + str2;
    cout<<"result of str+str2: "<< str6<<endl;
    cout<<endl;
    str5=b+str;
    cout<<"result of b+str: "<<str5<<endl;
    str5=str+b;
    cout<<"result of str+b: "<<str5<<endl;
    cout<<endl;

}
