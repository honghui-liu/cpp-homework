#ifndef STL_H
#define STL_H
#include<math.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<initializer_list>
using namespace std;
class MyVector {
public:
    double *vec;
    int dim = 3;

    MyVector();
    MyVector(double, double, double);
    MyVector(double*);
    MyVector(int);
    MyVector(int,double);
    MyVector(initializer_list<double>);
    ~MyVector();

    MyVector operator+(const MyVector&);
    MyVector operator-(const MyVector&) const;
    MyVector operator*(double) const;
    MyVector operator/(double) const;

    MyVector& operator+=(const MyVector&);
    MyVector& operator-=(const MyVector&);
    MyVector& operator*=(double);

    void operator=(const MyVector&);
    void operator=(initializer_list<double>);
    void randvec(double);
    void setdim(int);

    void setmag(double);

    double module();

public:
   friend double magitude(const MyVector&);
   friend MyVector sub(const MyVector&, const MyVector&);
   friend MyVector add(const MyVector&, const MyVector&);
   friend MyVector mult(const double, const MyVector&);
   friend MyVector mult(const MyVector&, const double);
   friend MyVector div(const MyVector&, const double);
   friend double  dot(const MyVector&, const MyVector&);
   friend double module(const MyVector&);
   friend MyVector cross(const MyVector&, const MyVector&);

   friend void normalize(MyVector&);
   friend double anglebetween(const MyVector&,const MyVector&);

   friend MyVector operator*(double, const MyVector&);

   friend ostream& operator<<(ostream&, const MyVector&);


};

#endif // STL_H
