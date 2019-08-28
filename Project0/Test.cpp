#include <iostream>
#include <cstring>
#include <string> 
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "projlex.h"
#include <map>
using namespace std;


 

int main(int argc, char *argv[]) {
//checking the flags in argv
vector<string> vlexemes;
map<string,int>::iterator it;
map<string, int> mlexemes;
vector<string> bigident;
ifstream infile;
int linenum = 0;
bool vcheck = false;
bool mci = false;
bool sum = false;
int strcount = 0;
int tokcount = 0;
int max = 0;
string strmax = "";
if(argc > 1){
   for(int i = 1; i<argc; i++ ){
      if(strcmp(argv[i], "-v") == 0){
                vcheck = true;
            }
    if(strcmp(argv[i], "-mci") == 0){
                mci = true;
            }
    if(strcmp(argv[i], "-sum") == 0){
                sum = true;
            }
    
    string firstchar = argv[i];
	  if(strcmp(argv[i], "-v") != 0  && strcmp(argv[i], "-mci") != 0 && strcmp(argv[i], "-sum") != 0 && firstchar[0] == '-'){
      	cout<<"INVALID FLAG "<<argv[i]<<endl;
    	return 1;
      }
    
      if( (i != argc - 1) && firstchar[0] != '-'){
       cout<<"TOO MANY FILE NAMES"<<endl;
       return 1;
      }
   }
     infile.open(argv[argc-1]);
     if(infile.is_open() == false){
        cout<<"UNABLE TO OPEN "<<argv[argc-1]<<endl;
         infile.close();
        return 0;
    }
    
   	
   } 


istream *in = &infile;//want to point to a file if it is there
int *linenumber = &linenum;
Token tok;
while( (tok = getNextToken(in, linenumber)) != DONE && tok != ERR ){
 if(tok.GetTokenType() == IDENT){
  mlexemes[tok.GetLexeme()]++;
 }
 if(tok.GetTokenType() == SCONST){
  vlexemes.push_back(tok.GetLexeme());
  strcount++;
 }
 tokcount++;


 	if(vcheck){
     operator<<(cout,tok);    
     }
}

 if(tok.GetTokenType() == ERR){
 cout<<"Error on line "<<tok.GetLinenum()<<" ("<<tok.GetLexeme()<<")"<<endl;
  return 0;
}
 

 if(mci){
  for(it = mlexemes.begin();it!=mlexemes.end();it++){
   if(it->second >max){
    max = it->second;
    bigident.clear();
    bigident.push_back(it -> first);
   }
    //strmax = it->first;
   }
  if(it->second == max){
   bigident.push_back(it->first);
  }
  int bigmax = bigident.size();
   for(int i =0;i<bigmax;i++){
      strmax+=bigident[i];
      if(i<bigmax-1)
      strmax+=", ";
     }
  cout<<"Most Common Identifier: "<<strmax<<endl;
 }
 if(sum){
  cout<<"Total lines: "<<linenum<<endl;
  cout<<"Total tokens: "<<tokcount<<endl;
  cout<<"Total strings: "<<strcount<<endl;
  int vsize = vlexemes.size();
  int len;
  for(int i = 0;  i<vsize;i++){
     len = vlexemes[i].length() - 2;
     if(len > max)
      max = len;
    }
  cout<<"Length of longest string: "<<max<<endl;
 }
 return 0;
}




