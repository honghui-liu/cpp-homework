#include "myvector.h"
#include<math.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<initializer_list>
#include<time.h>
using namespace std;

MyVector::MyVector(){
    dim = 3;
    vec = (double*)malloc(sizeof(double)*dim);
}
MyVector::MyVector(double a, double b, double c){
    dim =3;
    vec = (double*)malloc(sizeof(double)*dim);
    vec[0] = a;
    vec[1] = b;
    vec[2] = c;

}

MyVector::MyVector(int a){
    dim = a;
    this->vec = (double*)malloc(sizeof(double)*dim);
    if(this->vec == NULL){
        printf("Alloc memory failure");
        exit(1);
    }
}

MyVector::MyVector(int a, double b){
    int i = 0;
    dim = a;
    vec = (double*)malloc(sizeof(double)*dim);
    if(vec == NULL){
            printf("Alloc memory failure");
            exit(1);}else{
        for(i=0;i<dim;i=i+1){
            vec[i] = b;
        }
    }
}

MyVector::MyVector(initializer_list<double> list){
    int i = 0 , m = distance(list.begin(),list.end());
    dim = m;
    vec = (double*)malloc(sizeof(double)*dim);
    if(vec == NULL){
            printf("Alloc memory failure");
            exit(1);}else{
        for(auto it=list.begin();it!=list.end();it++){
            vec[i] = *it;
            i = i + 1;
        }
    }

}

MyVector::~MyVector(){
    free(vec);
}

MyVector::MyVector(double* a){
    vec = (double*)malloc(sizeof(double)*dim);
    if(vec == NULL){
            printf("Alloc memory failure");
            exit(1);}
    int len ,i;
    len = sizeof(a);
    for (i = 0; i < len; i++){
        vec[i] = a[i];
    }

}


double module(const MyVector& s){
    int i = 0;
    double mol = 0.0;
    for(i=0;i<s.dim;i=i+1){
        mol = mol + s.vec[i]*s.vec[i];
    }
    mol = sqrt(mol);
    return mol;
}

double MyVector::module(){
    int i = 0;
    double mol = 0.0;
    for(i=0;i<(this->dim);i=i+1){
        mol = mol + (this->vec[i])*(this->vec[i]);
    }
    mol = sqrt(mol);
    return mol;
}

void MyVector::setdim(int a){
    this->dim=a;
    this->vec = (double*)malloc(sizeof(double)*(this->dim));
    if(this->vec == NULL){
            printf("Alloc memory failure");
            exit(1);}
}

void MyVector::setmag(double a){
    double mol = this->module();
    double factor = a/mol;
    int i = 0;
    for(i=0;i<this->dim;i=i+1){
        this->vec[i] = factor * this->vec[i];
    }

}


MyVector sub(const MyVector& s1, const MyVector& s2){
    MyVector s;
    int i = 0;
    if(s1.dim!=s2.dim){
        printf("vectors can not do substrcation not in the same dimention");
        exit(1);
    }else{
        s.dim = s1.dim;
        s.vec = (double*)malloc(sizeof(double)*(s.dim));
        if(s.vec == NULL){
                printf("Alloc memory failure");
                exit(1);}else{
            for(i = 0; i < s.dim;i=i+1){
                s.vec[i] = s1.vec[i]-s2.vec[i];
            }
        }
    }
    return s;
}

MyVector add(const MyVector& s1, const MyVector& s2){
    MyVector s;
    int i = 0;
    if(s1.dim!=s2.dim){
        printf("vectors can not be added for not in the same dimention");
        exit(1);
    }else{
        s.dim = s1.dim;
        s.vec = (double*)malloc(sizeof(double)*(s.dim));

        if(s.vec == NULL){
                printf("Alloc memory failure");
                exit(1);}

        for(i = 0; i < s.dim;i=i+1){
            s.vec[i] = s1.vec[i]+s2.vec[i];
        }

    }
    return s;
}

MyVector mult(double a, const MyVector& s1){
    MyVector s;
    s.dim = s1.dim;
    s.vec = (double*)malloc(sizeof(double)*(s.dim));
    if(s.vec == NULL){
            printf("Alloc memory failure");
            exit(1);}
    int i = 0;
    for(i=0;i<s1.dim;i=i+1){
        s.vec[i] = a * s1.vec[i];
    }
    return s;
}

MyVector mult(const MyVector& s1, double a){
    MyVector s;
    s.dim = s1.dim;
    s.vec = (double*)malloc(sizeof(double)*(s.dim));
    if(s.vec == NULL){
            printf("Alloc memory failure");
            exit(1);}
    int i = 0;
    for(i=0;i<s1.dim;i=i+1){
        s.vec[i] = a * s1.vec[i];
    }
    return s;
}

MyVector div(const MyVector& s1, double a){
    MyVector s;
    s.dim = s1.dim;
    s.vec = (double*)malloc(sizeof(double)*(s.dim));
    if(s.vec == NULL){
            printf("Alloc memory failure");
            exit(1);}
    int i = 0;
    for(i=0;i<s1.dim;i=i+1){
        s.vec[i] = s1.vec[i]/a;
    }
    return s;
}

double dot(const MyVector& s1,const MyVector& s2){
    int i = 0;
    double scalar = 0.0;
    if(s1.dim!=s2.dim){
        printf("vectors can not be dotted for not in the same dimention");
        exit(1);
    }else{
        for(i=0;i<s1.dim;i=i+1){
            scalar = scalar + s1.vec[i]*s2.vec[i];
        }
        return scalar;
    }
}

double anglebetween(const MyVector& s1, const MyVector& s2){
    double ang, cos_ang;
    if(s1.dim!=s2.dim){
        printf("vectors are not in the same dimention\n");
        exit(1);
    }else{
    cos_ang = dot(s1,s2)/(module(s1)*module(s2));
    ang = acos(cos_ang);}

    return ang;
}

MyVector cross(const MyVector& s1, const MyVector& s2){
    MyVector s;
    if(s1.dim!=3||s2.dim!=3){
        printf("dimention of vectors are not 3\n");
        exit(1);
    }else{
        s.dim = 3;
        s.vec=(double*)malloc(sizeof(double)*(s.dim));
        if(s.vec == NULL){
                printf("Alloc memory failure");
                exit(1);}else{
            s.vec[0] = s1.vec[1]*s2.vec[2] - s2.vec[1]*s1.vec[2];
            s.vec[1] = -s1.vec[0]*s2.vec[2] + s2.vec[0]*s1.vec[2];
            s.vec[2] = s1.vec[0]*s2.vec[1] - s2.vec[0]*s1.vec[1];
        }

    }
    return s;
}

void MyVector::randvec(double a){
    double ang;
    MyVector s;
    s.dim = 2;
    s.vec = (double*)malloc(sizeof(double)*(s.dim));
    if(s.vec == NULL){
            printf("Alloc memory failure");
            exit(1);}
    //srand((int)time(NULL));
    ang = rand()/(double)RAND_MAX;
    ang = 2*3.14159*ang;
    s.vec[0]=a*cos(ang);
    s.vec[1]=a*sin(ang);
    *this =s;
}
void normalize(MyVector &s){
    double mol = s.module();
    int i = 0;
    for(i=0;i<s.dim;i=i+1){
        s.vec[i]=s.vec[i]/mol;
    }
}

void MyVector::operator=(const MyVector& s1){
    int i = 0;
    if(this->dim!=s1.dim){
        //printf("WARNING: Dimention of Vector Will Be Changed 1\n");
    }
    this->dim = s1.dim;
    this->vec = (double*)malloc(sizeof(double)*(this->dim));
    if(this->vec==NULL){
        printf("Alloc Memory Failure\n");
        exit(1);
    }else{
        for(i =0;i<this->dim;i=i+1){
            this->vec[i]=s1.vec[i];
        }
    }
}

void MyVector::operator=(initializer_list<double> list){
    int i = 0 , m = distance(list.begin(),list.end());
    if(this->dim!=m){
        //printf("WARNING: Dimention of Vector Will Be Changed 2\n");
    }
    this->dim = m;
    this->vec = (double*)malloc(sizeof(double)*(this->dim));
    if(this->vec == NULL){
            printf("Alloc memory failure");
            exit(1);}else{
        for(auto it=list.begin();it!=list.end();it++){
            this->vec[i] = *it;
            i = i + 1;
        }
    }
}

MyVector MyVector::operator+(const MyVector& s1){
     MyVector s;
    if(this->dim!=s1.dim){
        printf("vectors are not in the same dimention for '+' \n");
        exit(1);
    }else{
            s = add(*this,s1);//how to transfer variables
    }
            return s;
}

MyVector MyVector::operator-(const MyVector& s1) const{
    MyVector s;
   if(this->dim!=s1.dim){
       printf("vectors are not in the same dimention \n");
       exit(1);
   }else{
       s = sub(*this,s1);
   }
   return s;
}

MyVector MyVector::operator*(double a) const{
    MyVector s;
   s = mult(*this,a);
   return s;
}

MyVector operator *(double a, const MyVector& s1){
    MyVector s;
   s = mult(s1,a);
   return s;
}

MyVector MyVector::operator /(double a) const{
    MyVector s;
    s = div(*this,a);
    return s;
}

MyVector& MyVector::operator+=(const MyVector& s1){
    *this = *this + s1;
    return *this;
}

MyVector& MyVector::operator-=(const MyVector& s1){
    *this = *this - s1;
    return *this;
}

MyVector& MyVector::operator*=(double a){
    *this = (*this)*a;
    return *this;
}

ostream& operator<<(ostream& os,const MyVector& s){
    int i = 0;
    os << "[";
    for(i=0;i<s.dim - 1;i=i+1){
        os << s.vec[i]<<"," ;
    }
    os <<s.vec[s.dim-1];
    os << "]";
    return os;
}
