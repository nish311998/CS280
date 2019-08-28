#include <iostream>
#include <cstring>
#include <string> 
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "projlex.h"
#include <map>
#include "parse.h"
#include "parsetree.h"
//#include "value.h"
using namespace std;

int main(int argc, char *argv[]) {

ifstream infile;
int linenum = 0;
//static int nodecount = 0;
istream *in = &infile;
char ch;

if(argc > 2){
    cout<<"TOO MANY FILENAMES"<<endl;
    return 0;
}
if(argc == 2){
     infile.open(argv[1]);
     if(infile.is_open() == false){
        cout<<"COULD NOT OPEN "<<argv[1]<<endl;
         infile.close();
        return 0;
    }
     
   }
 
if(argc  == 1){
   in = &cin;
}

if(in -> get(ch)){
 in->putback(ch);
}
 
else if((in->peek())!=EOF){
 in = &cin;
}
 
Prog(in, &linenum);

//ParseTree *parsetree = Prog(in, &linenum);
//NodeCount(&linenum, *parsetree ->left, *parsetree ->right);
//int node = NodeCount();
return 0;
}

