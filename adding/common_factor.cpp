#include<stdio.h>
#include<iostream>
#include<ostream>
#include<stdlib.h>
using namespace std;

int Argv(int a,int b)
{
if (a==b)
return 1;
 else if (a > b)
return 0;
else
return -1;
}

int main(int argc,char *argv[])
{
 int a=1,b=1;
 // std::cin>>a;
 // std::cin>>b;

 a = atoi(argv[1]);//get argument
 b = atoi(argv[2]);
 std::cout<<"the largest common factor of "<<a<<" and "<<b<<" is:";

while (Argv(a,b) < 1)
{
  if (Argv(a,b) == 0) 
a = a-b;
  else
b = b-a;
}
 std::cout<<a<<std::endl;
 return 0;
}
