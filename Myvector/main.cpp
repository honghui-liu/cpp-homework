#include "myvector.h"
#include<math.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<initializer_list>
using namespace std;
int main(int argc, char* argv[]){
    MyVector vector0,vector1(4,1.1),vector2;
    MyVector vector4(4,1.1);
    cout<<"initial dimetion of vectors: "<< vector0.dim<<endl;
    vector0.setdim(4);
    cout<<"set dimention with function vector.setdim(4),then we have dimetion: "<<vector0.dim<<endl;
    cout<<"initialize vector when define it with vector(4,1.1),we get: "<<vector1<<endl;
    vector0 = {1,2,3};
    cout<<"set vector's value by a list vector={1,2,3}: "<<vector0<<endl;
    vector0={1,2,3};
    vector1={2,3,4};
    cout<<"vector0=: "<<vector0<<endl;
    cout<<"vector1=: "<<vector1<<endl;
    vector0+=vector1;
    cout<<"the outcome of vector0+=vector1 is: "<<vector0<<endl;
    vector0={1,2,3};
    vector0-=vector1;
    cout<<"the outcome of vector0-=vector1 is: "<<vector0<<endl;
    vector0={1,2,3};
    vector0*=2;
    cout<<"the outcome of vector0*=2 is: "<<vector0<<endl;
    normalize(vector0);
    cout<<"result of normalize(vector0)"<<vector0<<endl;
    cout<<"get the module of a vector by module(vector0): "<<module(vector0)<<endl;
    vector2.randvec(2);
    cout<<"get a random vec with module a by vec.(double 2): "<<vector2<<endl;
    cout<<"get angles between two vecs by anglebetween(vec0,vec1): "<<anglebetween(vector0,vector1)<<endl;
    cout<<"cross multiply of two vectors by cross(vec0,vec1):"<< cross(vector0,vector1)<<endl;
    cout<<"vector times a number by mult(vec,num) or mult(num,vec): "<<mult(vector4,5)<<endl;
    cout<<"dot between two vecs by dot(vec0,vec1): "<<dot(vector0,vector1)<<endl;
    cout<<"result of vec0+vec1: "<<vector0+vector1<<endl;
}
