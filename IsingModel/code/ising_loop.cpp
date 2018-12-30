#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<string>
#include<sstream>
#include<string.h>
#include<limits>
using namespace std;
#define N 100

void usage(char* program){
    fprintf(stderr, "\nProgram Usage:\n%s\n", program);
    fprintf(stderr, "     [ -n  1000000 ]    number of total steps, default 1000000\n");
    fprintf(stderr, "     [ -o  100000 ]  steps to output magnetic moment, default 100000\n");
    fprintf(stderr, "     [ -T  1.0 ]    value of temperature, default 1.0\n");
    fprintf(stderr, "     [ -h ]             display this information\n");
    fprintf(stderr, "\n");
    exit(1);}


void getargs(int argc, char** argv, int& total_num, int& out_num, double& T){
    char ch;
    while((ch=getopt(argc,argv,"n:o:T:h"))!=-1)
        switch (ch) {
        case 'n': total_num = atoi(optarg);break;
        case 'o': out_num = atoi(optarg);break;
        case 'T': T = strtod(optarg,NULL);break;
        case 'h':usage(argv[0]);
        }
}

int choosegrid(){
    int n;
    n = rand()%N;
    return n;
}

double randnum(){
    double n;
    n = rand()/(double)RAND_MAX;
    //printf("%f\n",n);
    return n;
}

void initialize(int* grid[N]){
    int i = 0, j = 0, m = 0;
    double prob;
    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            prob = randnum();
            if(prob < 0.5){
                *(grid[i]+j)= 1;
            }else{
                *(grid[i]+j)= -1;
            }
        }
    }

    for(i=0;i<N;i++){
        for(j=0;j<N;j++){
            m = m + *(grid[i]+j);
        }
    }
    //printf("%d \n",m);
}

double energy(int x, int y, int *grid[N]){
    int left,right,up,down;
    double  energy;
    left = (y + N -1)%N;
    right = (y + 1)%N;
    up = (x + N -1)%N;
    down  = (x + 1)%N;
    energy  = -(double)(*(grid[x]+y))*(*(grid[x]+left)+(*(grid[x]+right))+(*(grid[up]+y))+(*(grid[down]+y)));
    return energy;

}

double getprob(double dene, double T){
    double prob;
	if(dene < 0){
	prob  = 1;}else{
    prob  = exp(-dene/T);}
    return prob;
}

void turnornot(int x,int y, double T, int *grid[N]){
    double ene,dene,prob,rannum;
    rannum = randnum();
    ene = energy(x,y,grid);
    dene = (-2)*ene;
    prob = getprob(dene,T);
    if(rannum < prob){
        *(grid[x]+y) = (-1)*(*(grid[x]+y));
    }else{
        *(grid[x]+y) = *(grid[x]+y);
    }
    //printf("%f \n",ene);
}

void run(int *grid[N], double T){
  int x,y;
  x = choosegrid(); y = choosegrid();
  turnornot(x,y,T,grid);
  //printf("%f \n",randnum());
}

void output(FILE*fp,int *grid[N],int out_num,int i){
    int j = 0, k = 0, m = 0;

    if(i%out_num == 0){
        for(j=0;j<N;j++){
            for(k=0;k<N;k++){
                m = m + *(grid[j]+k);
            }
        }
        fprintf(fp,"%d\t%d\n",i,m);
    }
}

string do_fraction(long double value, int decplaces=3)
{
 char DECIMAL_POINT='.';
 ostringstream out;
 int prec = numeric_limits<float>::digits10; // 18
 out.precision(prec);//覆盖默认精度
 out<<value;
 string str= out.str(); //从流中取出字符串
 size_t n=str.find(DECIMAL_POINT);

 if ((n!=string::npos) //有小数点吗？
     && (str.size()>n+decplaces)) //后面至少还有decplaces位吗？
 {
 str[n+decplaces]='\0'; //覆盖第一个多余的数
 }

 //str.swap(string(str.c_str()));//删除nul之后的多余字符
  string temp=str.c_str();
   str=temp;
 
    return str;
    }

int main(int argc, char *argv[])
{
    int i = 0;
    int *grid[N];
    for(i=0;i<N;i++){
        grid[i]= new int[N];
    }
    //char filename[100] = "ising";
    string filename="ising";
	string tem;
	
    int total_num = 1000000000, out_num = 10000000;
    double T = 1.0;//temperature
    double m;//magnetic moment
    srand((int)time(NULL));

    getargs(argc,argv,total_num,out_num,T);
for(T=0.1;T<3.0;T=T+0.1){
    initialize(grid);
    tem = do_fraction(T);
	filename = "ising_"+tem+".txt";
const char* file = filename.c_str();
FILE* fp = fopen(file,"w");
    for(i=0;i<total_num;i++){
        run(grid,T);
        output(fp,grid,out_num,i);
    }
fclose(fp);
}
    for(i=0;i<N;i++){
	delete [] grid[i];}
}
