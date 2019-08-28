/*
 * parsetree.h
 */

#ifndef PARSETREE_H_
#define PARSETREE_H_


#include <vector>
#include <map>
#include <string>
using std::vector;
using std::map;

// NodeType represents all possible types
enum NodeType { ERRTYPE, INTTYPE, STRTYPE };
#include "value.h"

class ParseTree {
 	int 		nodecount;
 	int 		leafcount;
	int 		identcount;
 	int 		uniqueidentcount;
protected:
 	int			linenum;
 	ParseTree	*left;
	ParseTree	*right;
 	
public:
 	map<string, int> ident;
 	static map<string, Value> symboltable;
	
	ParseTree(int linenum, ParseTree *l = 0, ParseTree *r = 0)
		: linenum(linenum), left(l), right(r) {}

	virtual ~ParseTree() {
		delete left;
		delete right;
	}
 	void ParseError(int line, string msg)
	{
 	cout<<line<<": "<<msg<<endl;
	}
 	virtual Value Eval() = 0 ; 

 	
 
 	virtual bool isIdent(){
 	bool isident = false;
 	return isident;
	}
 	
 	virtual bool isVar(){
 	bool isvar = false;
 	return isvar;
 	}

	int GetLineNumber() const { return linenum; }

	virtual NodeType GetType() const { return ERRTYPE; }
 

 
int LeafCount() {
	int leafcount = 0;
	if( left )
 		leafcount += left->LeafCount();
	if( right )
 		leafcount += right->LeafCount();
	if(!left && !right)
		leafcount++;
	return leafcount;
} 
//this is correct
int IdentCount() {
  //need to create a virtual function for isIdent() checking if it is an ident
	int identcount = 0;
	if(left){
		if( left->isIdent() ){
			identcount += 1;}
		identcount+=left->IdentCount();
	}
 	if(right){
		if(right->isIdent() )
 			identcount +=1;
 		identcount+=right->IdentCount();
	}
return identcount;
}
 
int uniqueIdentCount(){
  //need to create a virtual function for isVar() checking if it is an var
	int uniqueidentcount = 0;
	if(left){
		if( left->isVar() ){
			uniqueidentcount += 1;}
		uniqueidentcount+=left->uniqueIdentCount();
	}
 	if(right){
		if(right->isVar() )
 			uniqueidentcount +=1;
 		uniqueidentcount+=right->uniqueIdentCount();
	}
return uniqueidentcount;
 }
 virtual void getType(){}
 
 virtual void insertSymb(){}
 
 void insertVar(){
 if(left){
 left->insertSymb();
 left->insertVar();
 }
 if(right){
 right->insertSymb();
 right->insertVar();
 }
 
 
 }
 void printTraverse(){
 if(left){
 	left->getType();
 	left->printTraverse();
 }
 if(right){
 	right->getType();
 	right->printTraverse();
 }
 }
 
 void traverse(){
 if(left){
 	left->Eval();
 	//left->traverse();
 }
 if(right){
 	right->Eval();
 	//right->traverse();
 }
 }
 
};
 



class StmtList : public ParseTree {

public:
	StmtList(ParseTree *l, ParseTree *r) : ParseTree(0, l, r) {}
/*
 NodeType GetType() const {

 		NodeType lt = left->GetType();
 		NodeType rt = right->GetType();
 		if( lt == rt && lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
}
 */
 
 Value Eval(){//check for ERROR Here
 if(left)
 	left->Eval();
 
 	//left = left->Eval();
 	//if(left == ERRTYPE)
 	//return 0;
 if(right)
 	right->Eval();
 	//right = right->Eval();
 	//if(right == ERRTYPE)
 	//return 0;
 return 0;
 }
 
 
 
};

class VarDecl : public ParseTree {
 string tok;
 int line;
 public:
	VarDecl(Token& t, ParseTree *e) : ParseTree(t.GetLinenum(), e), tok(t.GetLexeme()) {}
 		
 
 //symboltable method
 	/*
 void insertSymb(){//CHECK IF THS SYMBOLS ARE GOING IN APPROPRIATELY
 	NodeType lt = left->GetType();
 if(lt!=ERRTYPE){
 	if(lt == INTTYPE){
 	symboltable[tok] = (left->Eval()).GetIntValue();
 }
 	else if(lt == STRTYPE){
 	symboltable[tok] = (left->Eval()).GetStrValue();
 }
 
map<string,Value>::iterator it;
for( it = symboltable.begin();it != symboltable.end(); it++ ){
cout << it->first << endl;
 }
 }
 }
 */
 
 		bool isVar(){
 		bool isvar = true;
 		ident[tok]++;
 		return isvar;
 	}
 /*
  NodeType GetType() const {
 		NodeType lt = left->GetType();
 		if( lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
}
 */
 Value Eval(){//CHECK IF THS SYMBOLS ARE GOING IN APPROPRIATELY
 	NodeType lt = left->GetType();
 if(lt!=ERRTYPE){
 	if ( symboltable.find(tok) != symboltable.end() ) {
 	ParseError(linenum, "Multiple Variable Declarations");
 	return 0;
 }
 	if(lt == INTTYPE){
 	symboltable[tok] = (left->Eval()).GetIntValue();
 }
 	else if(lt == STRTYPE){
 	symboltable[tok] = (left->Eval()).GetStrValue();
 }

 

}
 return symboltable[tok];
 
	}
 
 };

class Assignment : public ParseTree {
 string tok;
public:
	Assignment(Token& t, ParseTree *e) : ParseTree(t.GetLinenum(), e), tok(t.GetLexeme()) {}
 /*
  void changeSymb(){//Need to figure out where to call so I am not printing and then changing again etc.
 	NodeType lt = left->GetType();
 if(lt!=ERRTYPE){
 	 	map<string,Value>::iterator it;
		it = symboltable.find(tok);
 		symboltable.erase(it);
 	
 	if(lt == INTTYPE){
 	symboltable[tok] = (left->Eval()).GetIntValue();
 }
 	else if(lt == STRTYPE){
 	symboltable[tok] = (left->Eval()).GetStrValue();
 }
 }
 }
 */
 /*
 NodeType GetType() const {
 		NodeType lt = left->GetType();
 		if( lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
}
 */
 
 Value Eval(){
	NodeType lt = left->GetType();
 if(lt!=ERRTYPE){
 	if(lt != symboltable[tok].GetType()){
 	ParseError(linenum, "Different Types");
 	return 0;
 }
 	if(lt == INTTYPE){
 		int temp = (left->Eval()).GetIntValue();
 		map<string,Value>::iterator it;
		it = symboltable.find(tok);
 		symboltable.erase(it);
 		symboltable[tok] = temp;
 }
 	else if(lt == STRTYPE){
 		string temp = (left->Eval()).GetStrValue();
	 	map<string,Value>::iterator it;
		it = symboltable.find(tok);
 		symboltable.erase(it);
 		symboltable[tok] = temp;
 }
 }
 return symboltable[tok];
 }
};

class Print : public ParseTree {
string stmt;
public:
 
	Print(int line, ParseTree *e) : ParseTree(line, e) {}
 
 /*
 void getType(){
 NodeType lt = left->GetType();
 if(lt!=ERRTYPE){
 	if(lt == INTTYPE){
 	int val = (left->Eval()).GetIntValue();
 	cout<<val<<endl;
 }
 	else if(lt == STRTYPE){
 	string val = (left->Eval()).GetStrValue();
 	cout<<val<<endl;
 }

 
 
 }
 }
 
 

 NodeType GetType() const {
 		NodeType lt = left->GetType();
 		if(lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
}
 
*/
 
Value Eval(){
  NodeType lt = left->GetType();
 if(lt!=ERRTYPE){
 	if(lt == INTTYPE){
 	int val = (left->Eval()).GetIntValue();
 	cout<<val<<endl;
 	return val;
 }
 	else if(lt == STRTYPE){
 	string val = (left->Eval()).GetStrValue();
 	cout<<val<<endl;
 	return val;
 }

 
 
 }
 return 0;
 
 }
 
 

};

class Repeat : public ParseTree {
string stmt;
public:
	Repeat(int line, ParseTree *e, ParseTree *s) : ParseTree(line, e, s) {}
 /*
 NodeType GetType() const {
 		NodeType lt = left->GetType();
 		NodeType rt = right->GetType();
 		if( lt == rt && lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
}
 */
 /*
 Value Eval(){
 if(left)
 return left->Eval();
 */
 Value Eval(){
 return 0;
 }
};

class PlusExpr : public ParseTree {
 //type is addition
 //value is summation
 
public:
 	PlusExpr(int line, ParseTree *p1, ParseTree *p2) : ParseTree(line, p1, p2) {}
 	NodeType GetType() const {
 		NodeType lt = left->GetType();
 		NodeType rt = right->GetType();
 		if( lt == rt && lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
} 

Value Eval() {
 	
 	int a1 = 0;
 	int a2 = 0;
 	string a3 = "";
 	string a4 = "";
 	NodeType lt = left->GetType();
 	NodeType rt = right->GetType();
 	if(left){
 	if(lt == INTTYPE){
 	a1 = (left->Eval()).GetIntValue();
 	}
 	else if(lt == STRTYPE){
	a3 = (left->Eval()).GetStrValue();
 }
 }
 	if(right){
 	if(rt == INTTYPE){
 a2 = (right->Eval()).GetIntValue();
 }
 	else if(rt == STRTYPE){
	a4 = (right->Eval()).GetStrValue();
 }
 }
 	if(rt == INTTYPE && lt == INTTYPE){
 	return a1 + a2 ; 
 }
 	else if( rt == STRTYPE && lt == STRTYPE)
 	return a3 + a4;
 return 0;
 

 
} 

};

class MinusExpr : public ParseTree {
 
public:
 	MinusExpr(int line, ParseTree *m1, ParseTree *m2) : ParseTree(line, m1, m2){}
  	NodeType GetType() const {
 		NodeType lt = left->GetType();
 		NodeType rt = right->GetType();
 		if( lt == rt && lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
}

Value Eval() {
 		int a1 = 0;
 	int a2 = 0;
 	string a3 = "";
 	string a4 = "";
 	NodeType lt = left->GetType();
 	NodeType rt = right->GetType();
 	if(left){
 	if(lt == INTTYPE){
 	a1 = (left->Eval()).GetIntValue();
 	}
 	else if(lt == STRTYPE){
	a3 = (left->Eval()).GetStrValue();
 }
 }
 	if(right){
 	if(rt == INTTYPE){
 	a2 = (right->Eval()).GetIntValue();
 }
 	else if(rt == STRTYPE){
	a4 = (right->Eval()).GetStrValue();
 }
 }
 	if(rt == INTTYPE && lt == INTTYPE){
 	return a1 - a2 ; 
 }
 	else if( rt == STRTYPE && lt == STRTYPE){
 	if (a3.find(a4) != string::npos) {
	int len = a4.length();
 	int i = a3.find(a4);
    a3.erase(i, len);
 	return a3;
 }
 
 }
 return a3;
 
}
 
};

class TimesExpr : public ParseTree { 
public:
 	TimesExpr(int line, ParseTree *m1, ParseTree *m2) : ParseTree(line, m1, m2){}
  	NodeType GetType() const {
 		NodeType lt = left->GetType();
 		NodeType rt = right->GetType();
 		if(  lt != ERRTYPE && rt !=ERRTYPE ){//error here with my type figure it out later....
 			if(lt == STRTYPE)
 			return lt;
 			if(rt == STRTYPE)
 			return rt;
 			if(rt == lt)
 			return rt;
 		return lt;
 }
 		return ERRTYPE;
}
 
Value Eval() {
 	int a1 = 0;
 	int a2 = 0;
 	string a3 = "";
 	string a4 = "";
 	string temp = "";
 	NodeType lt = left->GetType();
 	NodeType rt = right->GetType();
 	if(lt == INTTYPE){
 	Value val = 5;
 	a1 = (left->Eval()).GetIntValue();
 	}
 	else if(lt == STRTYPE){
	a3 = (left->Eval()).GetStrValue();
 }

 	if(rt == INTTYPE){
 	a2 = (right->Eval()).GetIntValue();
 	}
 	else if(rt == STRTYPE){
	a4 = (right->Eval()).GetStrValue();
 	}
 
 	if(rt == INTTYPE && lt == INTTYPE){
 	return a1 * a2 ; 
 }
 	else if( rt == INTTYPE && lt == STRTYPE){
 	for(int i = 0; i<a2; i++){
    	temp += a3;                     
    }
 	
	  	return temp;

   }

 
 
 else if( rt == STRTYPE && lt == INTTYPE){
 for(int i = 0; i<a1; i++){
    temp+=a4;
 }
 return temp;
 }
 return 0;
 
}
 
};


class SliceExpr : public ParseTree {
  
public:
 	SliceExpr(int line, ParseTree *m1, ParseTree *m2) : ParseTree(line, m1, m2){}
 /*
 NodeType GetType() const {
 		NodeType lt = left->GetType();
 		NodeType rt = right->GetType();
 		if( lt == rt && lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
}
 */
 
 Value Eval(){
	if(left){
 	return left->Eval();
 }
 	if(right)
 	return right->Eval(); 
 return 0;
 }
};


class SliceOperand : public ParseTree {
  
public:
 	SliceOperand(int line, ParseTree *m1, ParseTree *m2) : ParseTree(line, m1, m2){}
 /*
 NodeType GetType() const {
 		NodeType lt = left->GetType();
 		NodeType rt = right->GetType();
 		if( lt == rt && lt != ERRTYPE )
 			return lt;
 		return ERRTYPE;
}
 */
	Value Eval(){
 	if(left)
 	return left->Eval();
 	if(right)
 	return right->Eval();
 return 0;
 }
 };


class IConst : public ParseTree {
	int val;

public:
	IConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = stoi(t.GetLexeme());
	}

	NodeType GetType() const { return INTTYPE; }
 	Value Eval() {
 		return Value(val);
	} 
};

class SConst : public ParseTree {
 	string val;

public:
	SConst(Token& t) : ParseTree(t.GetLinenum()) {
		val = t.GetLexeme();
	}

	NodeType GetType() const { return STRTYPE; } //return INTTYPE might be wrong
 	Value Eval() {
 		return Value(val);
	} 
};

class Ident : public ParseTree {
 string val;

public:
	Ident(Token& t) : ParseTree(t.GetLinenum()) {
		val = t.GetLexeme();
	}
	bool isIdent(){
 	bool isident = true;
 	return isident;
 	}
 	
 	Value Eval() {
 	map<string,Value>::iterator it;
    string temp;
	for( it = symboltable.begin();it != symboltable.end(); it++ ){
	if(it->first == val){
 	return it->second;
 	}
 }
 return 0;
 }
 
	NodeType GetType() const { return symboltable[val].GetType(); } 
};


#endif /* PARSETREE_H_ */
