#include<map>
#include<string>
#include<algorithm>
#include<iostream>
#include<fstream>
using namespace std;

typedef map<double,int> file;
typedef map<double,string> str;

double trans(string s){
    int n,i=0;
    double m=0.0;
    char a;
    n = s.length();

    for(i=0;i<n;i++){
        a=s[i];
        switch (a) {
        case 'A': m = m + 0.001;break;
        case 'B': m = m + 0.01;break;
        case 'C': m = m + 0.1;break;
        case 'D': m = m + 1.0;break;
        case 'E': m = m + 10.0;break;
        case 'F': m = m + 100.0;break;
        case 'G': m = m + 1000.0;break;
        case 'H': m = m + 10000.0;break;
        case 'I': m = m + 100000.0;break;
        case 'J': m = m + 1000000.0;break;
        }
    }
    return m;
}


void count(file& mapping, double m){
    int i = 0;

    file::iterator intr;

    for(intr= mapping.begin();intr!=mapping.end();intr++){
        if((*intr).first==m){
            i = 1;
            (*intr).second = (*intr).second + 1;
            break;
        }
    }
    if(i==0){
        mapping.insert(make_pair(m,1));
    }
}
int main(int argc, char *argv[])
{

    double m;
    char a[6];
    file mapping;
    str stringmap;
    
	ofstream out("out.txt");

    string string1;
    ifstream inFile;
    inFile.open("seq.txt");

    while(inFile.eof()!=true){
        inFile.getline(a,6);
        inFile>>string1;
        m = trans(string1);
        count(mapping,m);
        stringmap.insert(make_pair(m, string1));

        //mapping.insert(file::value_type(m,0));
    }
    inFile.close();

    cout<<"string"<<"\t"<<"number"<<endl;
    out<<"string"<<"\t"<<"number"<<endl;
    for(file::iterator iter = mapping.begin();iter!=mapping.end();++iter){
        m = (*iter).first;
        auto p = stringmap.find(m);
                string1 = p->second;
        cout<<string1<<"\t"<<(*iter).second<<endl;
         out<<string1<<"\t"<<(*iter).second<<endl;
    }
    
    }



