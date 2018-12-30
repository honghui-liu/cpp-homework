#ifndef ATOMS_H
#define ATOMS_H
#include<string>
#include "myvector.h"
#include<iostream>
using namespace std;
class atoms{
public:
    MyVector site;
    double mass;
    double number;
    string name;
    string ele;

    atoms();
    atoms(const MyVector&, double, string);
    ~atoms();

    friend ostream& operator<<(ostream&, const atoms&);


};
#endif // ATOMS_H
