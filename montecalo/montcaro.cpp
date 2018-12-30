#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<math.h>
#include<time.h>
#define PI 3.1415927
using namespace std;

//standard error information
void usage(char* program){
    fprintf(stderr, "\nProgram Usage:\n%s\n", program);
    fprintf(stderr, "     [ -n  100000 ]    number of total steps, default 10000\n");
    fprintf(stderr, "     [ -T  1.0 ]    value of temperature, default 1.0  \n");
    fprintf(stderr, "     [ -l  1.0 ]    value of each step's length, default 1.0  \n");
    fprintf(stderr, "     [ -i  10000 ]  value of interval of print the result on screen, default 10000  \n");
    fprintf(stderr, "     [ -h ]             display this information\n");
    fprintf(stderr, "\n");
    exit(1);
}

//get my args of number of steps,temperature and length of step

void getargs(int &n,double &T,double &length,int &interval,int argc,char** argv)
{
char ch;
while((ch=getopt(argc,argv,"n:T:l:i:h"))!=-1)
switch(ch)
{case 'n':n=atoi(optarg);break;
 case 'i':interval=atoi(optarg);break;
 case 'T':T=strtod(optarg,NULL);break;
 case 'l':length = strtod(optarg,NULL);break;
 case 'h':usage(argv[0]);
 case '?':usage(argv[0]);
 }
}

//distance from the original point
double dist(double* site)
{
    double distance;
    distance = sqrt(site[0]*site[0]+site[1]*site[1]);
    return distance;

}

//energy of the certain site
double getenergy(double* site)
{
    double energy;
    energy = -0.5*cos(0.5*PI*dist(site)) - cos(1.5*PI*dist(site));
    return energy;
}

//get the next step of two directions
void getstep(double* step,double length,double* site)
{
    double ang=(rand()/(double)(RAND_MAX))*2*PI;
    step[0]=length * cos(ang);
    step[1]=length * sin(ang);
    //printf("%f\n",step[0]);
}
 //the probability of taking the step
double getprob(double denergy, double T)
{
    double prob;
    prob = exp((-denergy)/T);
    return prob;
}

//the count amount of steps in stationary state
void getcount(int &j,double* site)
{
    if(dist(site)<0.75)
        j=j+1;
    else
        j=j;
}

//the position of next step considering the probabilty and boundary
void nextstep(double* site, double comp, double* step,double T)
{
    double isite[2]={0.0,0.0};
    double denergy;
    isite[0]= site[0]+step[0];
    isite[1]= site[1]+step[1];
    denergy = getenergy(isite)-getenergy(site);
    if(comp < getprob(denergy,T))
        {
            if(dist(isite)<2.0)//boundary can not be crossed
            {site[0]=isite[0];
             site[1]=isite[1];}
         else
            {site[0]=-site[0]+step[0];
            site[1]=-site[1]+step[1];}}//jump to the centralsymmetric point when across the boundary
         else
    {
        site[0]=site[0];
        site[1]=site[1];
    }

}

void printer(int j,int i,int interval)
{
	if((i+1)%interval==0)
	printf("%-10d\t%-10d\t%f\n",j,i+1,(double)j/(i+1));
}

int main(int argc, char* argv[])
{
int n=100000,interval=10000,i=0,j=0;
double T=1.0,length=1.0,comp;
double site[2]={0.0,0.0};
char filename[100] = "output.txt";
FILE* fp = fopen(filename, "w");

getargs(n,T,length,interval,argc,argv);
//printf("%d %f %f\n",n,T,length);
srand((int)time(NULL));

printf("in_counts\ttotal_counts\tprobability\n");
for(i=0;i<n;i++)
{
    double step[2]={0.0,0.0};

    comp = rand()/(double)(RAND_MAX);
    getstep(step,length,site);
    nextstep(site,comp,step,T);
    getcount(j,site);
   // printf("in_counts\ttotal_counts\tprobability\n");
    printer(j,i,interval);

    //fprintf(fp,"%f\t%f\n",site[0],site[1]);
   //printf("%d %d\n",j,i);
   // printf("total probability is %f\n",(double)j/(i+1));
}
fclose(fp);
printf("the probability of finding the particle in stationary state is : %f\n",(double)j/n);
}
