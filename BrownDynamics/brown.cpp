#include "myvector.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <random>

using namespace std;

//generate a seed for random numbers of normal distribution
std::random_device rd{};
std::mt19937 gen{rd()};
std::normal_distribution<> d;

//class of arguments
class Args {
public:
    double gamma,mass,delta_t,k_b,T;
    double total_f,viscous_f,brown_f;
    int total_num,out_num;
    string program;

    Args(int, char**);
    void usage();
};

//get arguments from prompt line
Args::Args(int argc,char** argv){
    gamma = 1.0;
    mass = 1.0;
    delta_t = 1.0;
    k_b = 1.0;
    T = 1.0;

    total_num = 1000000;
    out_num = 1000;

    program = argv[0];

    char ch;
    while((ch=getopt(argc,argv,"g:m:d:k:T:n:o:h:?"))!=-1){
        switch (ch) {
        case 'g':gamma = strtod(optarg,NULL);break;
        case 'm':mass = strtod(optarg,NULL);break;
        case 'd':delta_t = strtod(optarg,NULL);break;
        case 'k':k_b = strtod(optarg,NULL);break;
        case 'T':T = strtod(optarg,NULL);break;
        case 'n':total_num = atoi(optarg);break;
        case 'o':out_num = atoi(optarg);break;

        case 'h':usage();
        case '?':usage();


        }
    }
   total_f = 1/(mass*(1+0.5*gamma*delta_t));
   viscous_f = -mass*gamma;
   brown_f = sqrt(2*mass*gamma*k_b*T/delta_t);

}

//display help message
void Args::usage(){
    cerr<<"\nprogram usage \n"
       <<program<<"\n"
       <<" [ g  1.0 ]    value of gamma, default 1.0\n"
       <<" [ m  1.0 ]    value of mass, default 1.0\n"
       <<" [ d  0.01 ]    value of delta_t,default 0.01\n"
       <<" [ k  1.0 ]    value of boltzmann's constant,default 1.0\n"
       <<" [ T  1.0 ]    value of temperature,default 1.0\n"
       <<" [ n  1000000]  total numbers of steps to run,default 1000000\n"
       <<" [ o  10000]    number of steps to output the result,default 10000\n"
       <<endl;
    exit(1);
}

//a class for brown motion
class brownvec: public MyVector{

   public:
    brownvec();
    ~brownvec();

   void gauss_rand();
   brownvec& operator=(const brownvec&);


};

brownvec::brownvec(){
    dim = 2;
    vec = (double*)realloc(vec,sizeof(double)*dim);
    if(vec == NULL){
            printf("Alloc memory failure");
            exit(1);}

    vec[0]=0.0;
    vec[1]=0.0;
}

brownvec::~brownvec(){
    //free(vec);
}

void brownvec::gauss_rand(){

    vec[0]=d(gen);
    vec[1]=d(gen);
    normalize(*this);
}

brownvec& brownvec::operator =(const brownvec& s1){
    this->vec[0]=s1.vec[0];
    this->vec[1]=s1.vec[1];
    return *this;
}

void output(int i,brownvec& site,Args myargs,ofstream& outfile){

            if(((i+1)/myargs.out_num)==0){
                outfile<<site.vec[0]<<"     "<<site.vec[1]<<endl;
            }

}

int main(int argc, char *argv[])
{
    brownvec site;
    brownvec vel;
    brownvec acc;
    brownvec phi;
    //cout<<2*site+vel<<endl;


    Args myargs(argc,argv);

    char filename[50]="output.txt";
    ofstream outfile;
    outfile.open(filename);
    outfile<<"x"<<"     "<<"y"<<endl;

    int i = 0;
    for(i=0;i<myargs.total_num;i++){
        phi.gauss_rand();
        acc.vec[0] = (vel.vec[0]*myargs.viscous_f + phi.vec[0]* myargs.brown_f )*myargs.total_f;
        acc.vec[1] = (vel.vec[1]*myargs.viscous_f + phi.vec[1]* myargs.brown_f )*myargs.total_f;

        vel+=acc*myargs.delta_t;

        site+=vel*myargs.delta_t;

        output(i,site,myargs,outfile);

    }
    outfile.close();

}
