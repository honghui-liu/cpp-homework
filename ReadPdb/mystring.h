#ifndef MYSTRING_H
#define MYSTRING_H
#include<string>
#include<sstream>
#include<vector>
using namespace std;
class mystring{
public:
    vector<string> str;
    string stri;

    mystring(const string&);
    mystring();
    ~mystring();
    void split();


};
#endif // MYSTRING_H
