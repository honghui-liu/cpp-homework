#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<math.h>
#include<fstream>
#include<string.h>
#define PI 3.14159
using namespace std;

void getarg(int argc, char** argv, int &n,char* filename);
void next_site(float comp_1,float comp_2,float* site,float ang );
float distance(float *site);
void usage(char* program);

int main(int argc, char *argv[])
{
    int n=100,i;
    float site[2]={0.0,0.0};
    float comp_1,comp_2,ang;
    char filename[50]="output.dat";
    getarg(argc,argv,n,filename);
    //cout<<filename<<endl;
    srand((int)time(NULL));
    ofstream outfile;
    outfile.open(filename);
    outfile<<"x_posi"<<"	"<<"y_posi"<<"    "<<"distance"<<endl;
    for(i=0;i<n;i++)
        {

            outfile<<site[0]<<"    "<<site[1]<<"    "<<distance(site)<<endl;

            comp_1 = rand()/(double)(RAND_MAX);//create a random number between 0 and 1
            comp_2 = rand()/(double)(RAND_MAX);
            ang = rand()/(double)(RAND_MAX)*2*PI;//random number between 0 and 2*pi
           // printf("%f\t%f\t%f\t%f\n",site[0],site[1],comp_1,comp_2);
            next_site(comp_1,comp_2,site,ang);

        }
        outfile.close();
}
//get all the arguments
void getarg(int argc, char** argv,int &n,char* filename)
{
   char ch;
	while((ch = getopt(argc, argv, "n:o:h"))!=-1)
    {
	switch(ch){
	case 'n':n = atoi(optarg);break;
	case 'o':strcpy(filename,optarg);break;
	case 'h':usage(argv[0]);
	case '?':usage(argv[0]);
	}
    }
}

void usage(char* program){
    fprintf(stderr, "\nProgram Usage:\n%s\n", program);
    fprintf(stderr, "     [ -n  1000000 ]    number of steps\n");
    fprintf(stderr, "     [ -o output.dat ]  the output file name \n");
    fprintf(stderr, "     [ -h ]             display this information\n");
    fprintf(stderr, "\n");
    exit(1);
}
//site of the next step
void next_site(float comp_1,float comp_2,float* site,float ang )
{
    if(comp_1>0.8)
    {site[0]=site[0];
        site[1]=site[1];
        }
        else if(comp_2 <0.5)
        {site[0]=site[0]+0.5*cos(ang);
            site[1]=site[1]+0.5*sin(ang);
            }
            else
            {site[0]=site[0]+cos(ang);
            site[1]=site[1]+sin(ang);

            }
        }

//distance away from the original site
float distance(float *site)
{
float dis;
dis = sqrt(site[0]*site[0]+site[1]*site[1]);
return dis;}



