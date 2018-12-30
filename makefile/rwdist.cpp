#include "rwdist.h"
#include<math.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<unistd.h>
#include<initializer_list>
#include<time.h>
using namespace std;

void usage(char* program){
    fprintf(stderr, "\nProgram Usage:\n%s\n", program);
    fprintf(stderr, "     [ -n  1000000 ]    number of steps\n");
    fprintf(stderr, "     [ -o output.dat ]  the output file name \n");
    fprintf(stderr, "     [ -d  100.0]    distance");
    fprintf(stderr, "     [ -h ]             display this information\n");
    fprintf(stderr, "\n");
    exit(1);
}

void getarg(int argc, char** argv,int &n,double &dist,char* filename)
{
   char ch;
    while((ch = getopt(argc, argv, "n:o:d:h"))!=-1)
    {
    switch(ch){
    case 'n':n = atoi(optarg);break;
    case 'o':strcpy(filename,optarg);break;
    case 'd':dist = strtod(optarg,NULL);break;
    case 'h':usage(argv[0]);
    case '?':usage(argv[0]);
    }
    }
}

//get the length of one step according to the probability
void getlen(double& len){
    double comp1,comp2;
    comp1 = rand()/(double)(RAND_MAX);
    comp2 = rand()/(double)(RAND_MAX);
    if(comp1>0.8){
        len = 0.0;
    }else if(comp2<0.5){
        len = 0.5;
    }else{
        len = 1.0;
    }

}

int main(int argc, char* argv[]){
       int ntime=100,nstep=100000;
       int i = 0,j = 0;
       double dist = 100.0;
       double len = 1.0;
       srand((int)time(NULL));
       MyVector site(2),step(2);//position of the object and the next step it is going to take
       char filename[50]="rwdist.txt";

       getarg(argc,argv,nstep,dist,filename);//get my args
       ofstream outfile;
       outfile.open(filename);//open a file to write outcome
       outfile<<"time"<<"\t"<<"nstep"<<endl;

       for(i=0,j=0;i<ntime;i++){
           site={0.0,0.0};
           step={0.0,0.0};
	   j=0;
           while(j<nstep && site.module()<dist){
               getlen(len);
	       step.randvec(len);//get a random vector according to the length, based on class Myvector
	       
	       site+=step;
               j++;
           }
           outfile<<i<<"\t"<<j<<endl;
       }
       outfile.close();
}

