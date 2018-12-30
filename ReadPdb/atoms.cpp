#include "atoms.h"
using namespace std;
atoms::atoms(){
    ele = "null";

}

atoms::atoms(const MyVector &s, double m, string str){
    site = s;
    mass = m;
    name = str;
}

atoms::~atoms(){}

ostream& operator<<(ostream& os,const atoms& s){
    os<< s.name <<"\t"<<s.number<<"\t"<<s.mass<<"\t"<<s.site.vec[0]<<"\t"<<
        s.site.vec[1]<<"\t"<<s.site.vec[2]<<endl;
    return os;
}
