/*
 * parse.cpp
 */
#include <iostream>
#include <fstream>
#include "parse.h"
#include "parsetree.h"
//#include "value.h"
#include <map>
#include <cstring>
#include <string>

map<string, Value> ParseTree::symboltable;


namespace Parser {
bool pushed_back = false;
Token	pushed_token;

static Token GetNextToken(istream *in, int *line) {
	if( pushed_back ) {
		pushed_back = false;
		return pushed_token;
	}
	return getNextToken(in, line);
}

static void PushBackToken(Token& t) {
	if( pushed_back ) {
		abort();
	}
	pushed_back = true;
	pushed_token = t;
}

}

static int error_count = 0;



int *linenum = 0;
int *nodecount = 0;
ifstream infile;
istream *in = &infile;
static int ident_count = 0;
map<string, int> ident;
static int leafcount = 0;
/*
static int ans = 0;
static bool add = false;
static bool minusss = false;
static bool mult = false;
static bool added = false;
static int prevs = 0;
static bool rparen = false;
static bool lparen = false;
static int prevmult = 0;
static bool multiplied = false;
*/
void ParseError(int line, string msg)
{
 cout<<line<<": "<<msg<<endl;
}

ParseTree *Prog(istream *in, int *line)
{
	ParseTree *sl = Slist(in, line);

	if( sl == 0 ){
		ParseError(*line, "No statements in program");
    }
	if( error_count )
		return 0;
 	//int count = sl->LeafCount();
 	//int countident = sl->IdentCount();
 	//int uniqueidentcount = sl->uniqueIdentCount();

 	//cout<<uniqueidentcount<<endl;
 
 //call traversal here for eval
 	//int val = sl->traverse();
 	//cout<<val<<endl;
 	sl->traverse();
 

 	return sl;
}

// Slist is a Statement followed by a Statement List
ParseTree *Slist(istream *in, int *line) {
   ParseTree *s = Stmt(in, line);
   if( s == 0 )
     return 0;

 if( Parser::GetNextToken(in, line) != SC ) {
     ParseError(*line, "Missing semicolon");
     delete s;
     return 0;
   }
       return new StmtList(s, Slist(in,line));
}
ParseTree *Stmt(istream *in, int *line) {
	Token s = Parser::GetNextToken(in, line);
 
	if(s == VAR){
    ParseTree *v = VarStmt(in, line);
    if(v == 0){
    ParseError(*line, "Missing expression after Var");
		return 0;
    }

	return v;
    }
     
    else if(s == SET){
    ParseTree *s = SetStmt(in, line);
     if(s == 0){
     ParseError(*line, "Missing expression after Set");
		return 0;
    }
	return s;
    }
    
    else if(s == PRINT){
    ParseTree *p = PrintStmt(in, line);
	if(p == 0){
     ParseError(*line, "Missing expression after Print!");
		return 0;
    }
	return p;
    }
     
    else if(s == REPEAT){
    ParseTree *r = RepeatStmt(in, line);
    if(r == 0){
     ParseError(*line, "Missing expression after Repeat");
		return 0;
    }
	return r;
    }
 

    else if(s != DONE){
    ParseError(*line, "Missing statements");
	return 0;
    }

 	
 //my thinking here is wrong probably have to work with nodes
 /*
 	else if(s == DONE){
    cout<<"LEAF COUNT: "<<leafcount<<endl;//(think about this a bit more)
    cout<<"IDENT COUNT: "<<ident_count<<endl;
	if(ident.size()>0 && ident_count>0){
    cout<<"UNIQUE IDENT COUNT: "<<ident.size()<<endl;
    map<string,int>::iterator it;
    string temp;
	for( it = ident.begin();it != ident.end(); it++ ){
	temp += it->first;
    temp += ", "; 
    }
    temp.erase(temp.size()-2);
    cout<<temp<<endl;
    }
    
    }
    */
 return 0;
}


ParseTree *VarStmt(istream *in, int *line) {
 
 	Token v2 = Parser::GetNextToken(in, line);
 	if(v2 != IDENT){
     ParseError(*line, "Missing identifier after var");
     return 0;
    }
 	//ident[v2.GetLexeme()]++;
 	ParseTree *ex1 = Expr(in, line);
 	//symboltable[v2.GetLexeme()] = ex1;
	if( ex1 == 0 ) {
		ParseError(*line, "Missing expression after IDENT");
		return 0;
	}
 
 	return new VarDecl(v2, ex1);//might be wrong


}

ParseTree *SetStmt(istream *in, int *line) {

 	Token s2 = Parser::GetNextToken(in, line);
 	if(s2 != IDENT){
     ParseError(*line, "Missing identifier after set");
     return 0;
    }
 	//ident[s2.GetLexeme()]++;

 	ParseTree *ex2 = Expr(in, line);
	if( ex2 == 0 ) {
		ParseError(*line, "Missing expression after IDENT");
		return 0;
	}
 return new Assignment(s2, ex2); //might be wrong
}

ParseTree *PrintStmt(istream *in, int *line) {
	int l = *line;

	ParseTree *ex = Expr(in, line);
	if( ex == 0 ) {
		//ParseError(*line, "Missing expression after print");
		return 0;
	}
 	//cout<<ans<<endl;
 	//ans = 0;
	return new Print(l, ex);
}

ParseTree *RepeatStmt(istream *in, int *line) {
 	int l = *line;

	ParseTree *ex = Expr(in, line);
	if( ex == 0 ) {
		ParseError(*line, "Missing expression after repeat");
		return 0;
	}

 	
 ParseTree *s = Stmt(in, line);
 if(s == 0){
  return 0;
 }
return new Repeat(l, ex,s);
}

ParseTree *Expr(istream *in, int *line) {
	ParseTree *t1 = Term(in, line);
	if( t1 == 0 ) {
		return 0;
	}

	while ( true ) {
		Token t = Parser::GetNextToken(in, line);

		if( t != PLUS && t != MINUS ) {
			Parser::PushBackToken(t);
			return t1;
		}/*
     if( t == PLUS ){
         	add = true;
      		added = true;
     }
     else{
		minusss = true;
     }
*/
		ParseTree *t2 = Term(in, line);
		if( t2 == 0 ) {
			ParseError(*line, "Missing expression after operator");
			return 0;
		}

		if( t == PLUS ){
			t1 = new PlusExpr(t.GetLinenum(), t1, t2);
     		}
     	else
         	t1 = new MinusExpr(t.GetLinenum(), t1, t2);
        
     		
	}
}

ParseTree *Term(istream *in, int *line) {
 	ParseTree *f1 = Factor(in, line);
	if( f1 == 0 ) {

		return 0;
	}
 	while(true){
     	Token f = Parser::GetNextToken(in, line);
		if( f != STAR ) {
			Parser::PushBackToken(f);
			return f1;
		}
		//mult = true;

     	ParseTree *f2 = Factor(in, line);
		if( f2 == 0 ) {
			ParseError(*line, "Missing expression after operator");
			return 0;
		}
		f1 = new TimesExpr(f.GetLinenum(), f1, f2);
    }
}

ParseTree *Factor(istream *in, int *line) {
	ParseTree *p1 = Primary(in, line);
	if( p1 == 0 ) {
		return 0;
	}
 	while ( true ) {
		Token p = Parser::GetNextToken(in, line);

		if( p != LSQ ) {
			Parser::PushBackToken(p);
			return p1;
		}


        ParseTree *p2 = Expr(in, line);
		if( p2 == 0 ) {
			ParseError(*line, "Missing expression after LSQ");
			return 0;
		}
     
		Token pp = Parser::GetNextToken(in, line);
		if( pp == COLON ){
        
        ParseTree *p3 = Expr(in, line);
		if( p3 == 0 ) {
			ParseError(*line, "Missing expression after COLON");
			return 0;
		}
         
        Token ppp = Parser::GetNextToken(in, line);
        if(ppp != RSQ){
         return 0;
        }

		p1 = new SliceExpr( p.GetLinenum(), p1, new SliceOperand(*line,p2,p3));
     	 
			
	}
     else{
      ParseError(*line, "Missing Colon");
     return 0;
     }
}
}
    


ParseTree *Primary(istream *in, int *line) {
 		Token to = Parser::GetNextToken(in, line);
 		if(to != IDENT && to != ICONST && to != SCONST && to != LPAREN){
         return 0;
        }
 		 if(to == LPAREN){
         	ParseTree *e1 = Expr(in, line);
             if(e1 == 0){
             ParseError(*line, "Missing expression after LPAREN");
				return 0;
             }
         	//lparen = true;
            Token to1 = Parser::GetNextToken(in, line);
            if(to1 != RPAREN){
             ParseError(*line, "Missing RPAREN");
             return 0;
            }
          //rparen = true;
		return e1;
            }
        
 
 if(to == ICONST){
/*
 if(add == true){
 prevs = stoi(to.GetLexeme());
 ans+=stoi(to.GetLexeme());
 add = false;
 }
  else if(minusss == true && multiplied == false){
 ans-=stoi(to.GetLexeme());
minusss = false;
 } 

else if(mult && added && rparen==false){
 ans = ans-prevs;
 prevs = prevs*stoi(to.GetLexeme());
 ans+=prevs;
 mult = false;
 multiplied = true;
 prevs=0;
 }
else if(mult){
 ans*=stoi(to.GetLexeme());
 mult = false;
 multiplied = true;
 prevmult = stoi(to.GetLexeme());
}
else if(multiplied && added && rparen == true && lparen == true && (minusss == true || add == true)){
 int temp = 0;
 ans = ans/prevmult;
 if(minusss == true)
 temp = prevmult - stoi(to.GetLexeme());
 if(add == true)
 temp = prevmult + stoi(to.GetLexeme());
 ans = ans*temp;
}
  else{
  ans = stoi(to.GetLexeme());
  }
  */
 leafcount++;
 return new IConst(to);
 }
 
 if(to == IDENT){
  leafcount++;
  ident_count++;
 return new Ident(to);}
 if(to == SCONST){
 leafcount++;
 return new SConst(to);}
 
 
 return 0;
}



