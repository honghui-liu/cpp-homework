#include <fstream>
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "myvector.h"
#include "mystring.h"
#include "atoms.h"
using namespace std;

class Args{
public:
    string program, infile, outfile;

    Args(int , char**);
    void usage();
};

void Args::usage(){
    cerr<<"\nprogram usage \n"
           <<program<<"\n"
           <<" [ i  1COA.pdb ]    input file's name\n"
           <<" [ o  out.pdb ]    output file's name\n"
           <<" [ h ]    display this message\n"

           <<endl;
        exit(1);
}
Args::Args(int argc,char** argv){
    infile = "1COA.pdb";
    outfile = "out.pdb";

    program = argv[0];

    char ch;
    while((ch=getopt(argc,argv,"i:o:h"))!=-1){
        switch (ch) {
        case 'i':infile = optarg;break;
        case 'o':outfile = optarg;break;
        case 'h':usage();
        }
    }

}

double pickatoms(Args& myargs,vector<atoms>& atom){

    ifstream inFile;
    ofstream tmp;
    tmp.open("tmpt.pdb");
    inFile.open(myargs.infile);
    string str;
    string str2;
    int i = 0;

    while(inFile.eof()!=true){
        getline(inFile,str);
        stringstream ss(str);
        getline(ss,str2,' ');

        if(str2=="ATOM"){
             tmp<<str<<endl;
             i = i+1;
        /*while(ss.eof()!=true){
        getline(ss,str2,' ');
        cout<<str2<<" ";
}cout<<endl;*/
}
 }
    atom.resize(i+1);
    return i+1;
   }

double tran(const string& s){
    double n;
    const char ch = s[0];
    switch (ch) {
    case 'C':n = 12;break;
    case 'N':n = 14;break;
    case 'S':n = 32;break;
    case 'O':n = 16;break;
    }
    return n;
}
void readatoms(Args& myargs,ofstream& output,vector<atoms>& atom){
    ifstream inFile;
    inFile.open("tmpt.pdb");
    int i = 0,j = 0,k = 0;
    mystring str;

    //while(inFile.eof()!=true)
        while(str.stri!="")
    {

        getline(inFile,str.stri);
        str.split();

        atom[i].name = str.str[3];
        atom[i].site.vec[0]=stod(str.str[6]);
        atom[i].site.vec[1]=stod(str.str[7]);
        atom[i].site.vec[2]=stod(str.str[8]);
        atom[i].mass = tran(str.str[11]);
        atom[i].number = stod(str.str[5])-20;
        if(str.str[2]=="CA"){
            atom[i].ele = str.str[2];
        }
        //cout<<atom[i].site.vec[1]<<" "<<atom[i].ele<<" "<<i<<endl;
        i = i + 1;
    }
        for(j=0;j<i-1;j++){
            if(atom[j].ele=="CA"){
                for(k=0;k<i-1;k++){
                    if(k!=j&&atom[k].number==atom[j].number){
                        atom[j].mass = atom[j].mass + atom[k].mass;
                    }
                }
                output<<atom[j];
            }
        }

}
void gethar(const int num,vector<atoms>& atom,int i, ofstream& output){
    int j = 0;
    double dist;
    MyVector dis;
    for(j=0;j<num;j++){
        if(atom[j].ele=="CA"&&atom[j].number==(atom[i].number+1)){
            dis = atom[j].site - atom[i].site;
            dist = dis.module();
            output<<"HAR"<<"\t"<<atom[i].number<<"\t"<<atom[j].number<<"\t"<<"100.0"<<"\t"<<
                    dist<<endl;
        }
    }
}

void getlj(const int num,vector<atoms>& atom,int i, ofstream& output){
    int j = 0, k = 0,n=0;
    int m = 0;
    double dist;
    MyVector dis;
    for(j=0;j<num;j++){
        if(atom[j].ele=="CA"&&atom[j].number>(atom[i].number+1)){
            for(k=0;k<num;k++){
                if(atom[k].number==atom[j].number){
                    for(n=0;n<num;n++){
                        if(atom[n].number==atom[i].number){
                            dis = atom[n].site - atom[k].site;
                            dist = dis.module();
                            if(dist<5.0){m = m + 1;}
                        }
                    }
                }
}
            dis = atom[j].site - atom[i].site;
            dist = dis.module();
            if(m>0){output<<"LJ"<<"\t"<<atom[i].number<<"\t"<<atom[j].number<<"\t"<<m<<"\t"
                         <<dist<<endl;}
            m = 0;
        }
    }

}

void getrep(const int num,vector<atoms>& atom,int i, ofstream& output){
    int j = 0;
    for(j=0;j<num;j++){
        if(atom[j].ele=="CA"&&atom[j].number!=atom[i].number){
            output<<"REP"<<"\t"<<atom[i].number<<"\t"<<atom[j].number<<"\t"<<"1"<<"\t"<<
                    "4"<<endl;
        }
    }

}
void getforce(ofstream& output,vector<atoms>& atom,const int num){
    int i = 0,j = 0;
    for(i=0;i<num;i++){
        if(atom[i].ele=="CA"){
            gethar(num,atom,i,output);
            getlj(num,atom,i,output);
            getrep(num,atom,i,output);
        }
    }

}

void readfile(Args& myargs,vector<atoms>& atom){
    int num;
    ofstream output;
    output.open(myargs.outfile.c_str());
    num = pickatoms(myargs,atom);
    readatoms(myargs,output,atom);
    getforce(output,atom,num);
}

int main(int argc, char *argv[])
{
    Args myargs(argc, argv);

    vector<atoms> atom;
    readfile(myargs,atom);

}
