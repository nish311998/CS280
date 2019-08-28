
#include <iostream>
#include <cstring>
#include <string> 
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "projlex.h"
using namespace std;


Token getNextToken(istream *in, int *lineNum){

bool comment = false;
string temp ="";
char ch;
int parencount = 0;
string sectemp = "";
 
if(in -> eof())
in = &cin;
 
while(in -> get(ch)){

if(ch == '\n'){
*lineNum = *lineNum + 1;
}
if(ch == '+'){
if(parencount == 0)
return Token(PLUS, temp, *lineNum);}


if(ch == '-'){
if(in -> peek() == ' '){
if(parencount == 0)
return Token(MINUS, temp, *lineNum);}}
 
if(ch == ';'){
if(parencount == 0)
return Token(SC, temp, *lineNum);}
 
if(ch == '('){
if(parencount == 0)
return Token(LPAREN, temp, *lineNum);}
 
if(ch == ')'){
if(parencount == 0)
return Token(RPAREN, temp, *lineNum);}

if(ch == '['){
if(parencount == 0)
return Token(LSQ, temp, *lineNum);}

if(ch == ']'){
if(parencount == 0)
return Token(RSQ, temp, *lineNum);
}

if(ch == '*'){
if(parencount == 0)
return Token(STAR, temp, *lineNum);}
 
if(ch == ':'){
if(parencount == 0)
return Token(COLON, temp, *lineNum);}

if(ch == '#' && parencount == 0){
while(in->get(ch)){
 if(ch == '\n'){
  *lineNum = *lineNum + 1;
  break;
 }
}
  continue;


}


 
 	//isSCONST
 	if(ch == '"'){
     temp+=ch;
     parencount++;
     while(in->get(ch)){
      if(ch != '\n' && parencount==1){
          if(comment==false){
          temp+=ch;
          }
          if(ch == '"')
           parencount++;
          
         }
          if(ch == '#'&& parencount == 0){
          comment = true;

          }
          if(ch == '\n') {
           //error with lineNum
           *lineNum = *lineNum + 1;
           temp+=ch;
           return Token(ERR, temp, *lineNum);
          }
          if(parencount == 2){
          return Token(SCONST, temp, *lineNum);
          }
         
         
        
           
        }
    }
 else if(isdigit(ch) || ch == '-'){
  temp+=ch;
 	while(in->get(ch)){
         if(isdigit(ch)){
            temp+=ch;
         }
 		else{
         if(ch != '\n')
         	in -> putback(ch);
            if(isspace(ch)){
            if(ch == '\n')
             *lineNum = *lineNum + 1;
            return Token(ICONST, temp, *lineNum);
            }   
         	if(!isdigit(ch) && !isalpha(ch)){
             return Token(ICONST, temp, *lineNum);
            }
         	temp+=ch;
            return Token(ERR, temp,*lineNum);
         }
       
            }
 }
 //isIDENT
 else if(isalpha(ch)){
  temp+=ch;
  while(in -> get(ch)){
       if(temp == "var")
         return Token(VAR, temp,*lineNum);
        if(temp == "print")
         return Token(PRINT, temp,*lineNum);
        if(temp == "set")
         return Token(SET, temp,*lineNum);
        if(temp == "repeat")
         return Token(REPEAT, temp,*lineNum);
         
        if(isalnum(ch)){
         	temp+=ch;
        }
        else{
         if(ch != '\n')
         in -> putback(ch);
         	if(isspace(ch)){
             if(ch == '\n'){
              *lineNum = *lineNum + 1;
               return Token(IDENT, temp, *lineNum);
             }
             }
             if(!isalnum(ch))
             	return Token(IDENT, temp, *lineNum);
            
         	return Token(ERR, temp, *lineNum);
        }
  }
 }
 



            




            }
            return Token(DONE, temp, *lineNum);

           }

ostream& operator<<(ostream& out, const Token& tok){
if(tok.GetTokenType() == IDENT)
return out<<"IDENT("<<tok.GetLexeme()<<")"<<endl;


if(tok.GetTokenType() == SCONST){
 string temp = tok.GetLexeme();
 temp = temp.erase(0,1);
 temp = temp.erase(temp.length()-1,1);
                                 
 return out<<"SCONST("<<temp<<")"<<endl;
 
}
if(tok.GetTokenType() == ICONST)
return out<<"ICONST("<<tok.GetLexeme()<<")"<<endl;

 
if(tok.GetTokenType() == SET)
return out<<"SET"<<endl;
 
if(tok.GetTokenType() == PRINT)
return out<<"PRINT"<<endl;
 
if(tok.GetTokenType() == VAR)
return out<<"VAR"<<endl;
 
if(tok.GetTokenType() == REPEAT)
return out<<"REPEAT"<<endl;
 
if(tok.GetTokenType() == PLUS)
return out<<"PLUS"<<endl;
 
if(tok.GetTokenType() == MINUS)
return out<<"MINUS"<<endl;
  
if(tok.GetTokenType() == COLON)
return out<<"COLON"<<endl;

if(tok.GetTokenType() == LSQ)
return out<<"LSQ"<<endl;
 
if(tok.GetTokenType() == RSQ)
return out<<"RSQ"<<endl;
 
if(tok.GetTokenType() == LPAREN)
return out<<"LPAREN"<<endl;
 
if(tok.GetTokenType() == RPAREN)
return out<<"RPAREN"<<endl;
 
if(tok.GetTokenType() == STAR)
return out<<"STAR"<<endl;
 
if(tok.GetTokenType() == SC)
return out<<"SC"<<endl;
 
return out<<"";
}
