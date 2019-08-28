#include <iostream>
#include <cstring>
#include <string> 
#include <vector>
#include <fstream>
#include <cctype>
#include <algorithm>
using namespace std;
int main(int argc, char *argv[]) {
 	vector<string> file;
 	
 	int size = argc-1;
        string badfile;
        ifstream infile;
        
        if(argc>=2){
        bool qcheck = false;
        bool scheck = false;
        bool ccheck = false;
        bool pcheck = false;
        bool lcheck = false;
        for(int i = 0; i<size; i++){
         	file.push_back(argv[i+1]);
            if(strcmp(argv[i+1], "-q") == 0){
                qcheck = true;
            }
            else if(strcmp(argv[i+1], "-s") == 0 ){
                scheck = true;

            }
            else if(strcmp(argv[i+1], "-c") == 0){
                ccheck = true;
            }
            else if(strcmp(argv[i+1], "-p") == 0){
            	  pcheck = true;
            }
            else if(strcmp(argv[i+1], "-l") == 0){
              lcheck = true;
            }
         	if((qcheck && scheck) || (qcheck && ccheck) || (qcheck && ccheck && scheck)){
            cout<<"CONFLICTING FLAGS"<<endl;
        	return 0;
                }
            else if((strcmp(argv[i+1], "-q") != 0) && (strcmp(argv[i+1], "-s") != 0 ) && (strcmp(argv[i+1], "-c") != 0) && (strcmp(argv[i+1], "-p") != 0) && (strcmp(argv[i+1], "-l") != 0) ){                
             	string err = argv[i+1];
             	char hyphen = '-';
                if(err[0] == hyphen){
                string error = strcat(argv[i+1]," INVALID FLAG");
                cout<< error <<endl;
                return 0;
                }
                else{
                    if(i != size-1){
                        cout<<"TOO MANY FILES"<<endl;
                    return 0;
                }
                   else{
                    infile.open(argv[size]);
                  if(infile.is_open() == false){
                        badfile = strcat(argv[size]," CANNOT OPEN");
                        cout<<badfile<<endl;
                   		infile.close();
                   		return 0;
                  }
                
                    
                   
                   }
                    
                }
            }
        }
        
      //when trying to choose the order of each flag store all the command line flags into a vector and based on the index do the flag
      //creation of vector with words and spaces
      vector<string> words;
 	  vector<string> whitespace;
      vector<string> longestwords;
      vector<string> longestgoodwords;
      vector<string> longestrealwords;
      char ch;
     istream *in = &infile;
      
      
     string wordholder;
     string spaceholder;
      int wordclearcount = 0;
      int spaceclearcount = 0;
      //inital counter variables
      int initcharcount = 0;
      int initlines = 0;
      int initgoodwordcount = 0;
      int initrealwordcount = 0;
      int initcapword = 0;
      int initacronymcount = 0;
         
      //p flag variables
      int charcount = 0;
      int lines = 0;
      int goodwordcount = 0;
      int realwordcount = 0;
      int capword = 0;
      int acronymcount = 0;
      string charnext = "";

      if(in -> get(ch)){
       charnext += ch;
       wordholder+=charnext;

       }
       else{
        in = &cin;
       }
      while( in-> get(ch)){
      
      if(!isspace(ch)){
      if(spaceholder.length() > 0){
      whitespace.push_back(spaceholder);
      spaceholder.clear();
      }
      wordholder += ch;
      }
      else{
      if(wordholder.length() > 0){
      words.push_back(wordholder);
      wordholder.clear();
      }
      spaceholder += ch;
      }
      }   
      if(spaceholder != ""){   
      whitespace.push_back(spaceholder);
      }
      
      int spacesize = whitespace.size();
      int wordssize = words.size();
      if(spacesize != wordssize) whitespace.push_back("");
      
      
         
         //inital statistics
      
     
       for(int i = 0; i<wordssize;i++){
		bool initrealword = true;
        bool initgoodword = true;
        bool initacronym = true;
        initcharcount+=words[i].length();
        initcharcount+=whitespace[i].length();
        int wordlength = words[i].length();
        int spacelength = whitespace[i].length();
        string word = words[i];
        string space = whitespace[i];
	for(int l = 0; l<spacelength; l++){
      	if(space[l] == '\n')
         initlines++;
    }
    for( int k = 0; k<wordlength; k++){
     	if(!isupper(word[k])){
         initacronym = false;
        }
     	if(!isalpha(word[k])){
         initrealword = false;
        }
     	if(!isalnum(word[k])){
         initgoodword = false;
        }
    }
        if(initacronym){initacronymcount++;}
        if(initrealword){ initrealwordcount++;}
        if(initgoodword){ initgoodwordcount++;}
        
     	if(isupper(word[0])){
         initcapword++;
        }
        }
      //start of part 2
      int wordl = 0;
      int goodwordl = 0;
      int realwordl = 0;   
     for(int i = 0; i<wordssize; i++){
      if(lcheck){
      
      bool realwordn = true;//bools for l
      bool goodwordn = true;
      bool wordn = true;
      string word = words[i];
      int wordlength = word.length();
      for(int j = 0; j<wordlength; j++){
      if(!isalpha(word[j])) {
       realwordn = false;}
      if(!isalnum(word[j])){
       goodwordn = false;}
      }
      if(goodwordn){
      if(wordlength>goodwordl){
       goodwordl = wordlength;
       longestgoodwords.clear();
       longestgoodwords.push_back(word);
      }
      else if(wordlength == goodwordl){
       if (find(longestgoodwords.begin(), longestgoodwords.end(), word) != longestgoodwords.end())
		continue;
       else
       longestgoodwords.push_back(word);
      }
      }
       
      if(realwordn){
      if(wordlength>realwordl){
       realwordl = wordlength;
       longestrealwords.clear();
       longestrealwords.push_back(word);
      }
      else if(wordlength == realwordl){
      if (find(longestrealwords.begin(), longestrealwords.end(), word) != longestrealwords.end())
		continue;
       else
       longestrealwords.push_back(word);
      }
      }
      
        if(wordn){
      if(wordlength>wordl){
       wordl = wordlength;
       longestwords.clear();
       longestwords.push_back(word);
      }
      else if(wordlength == wordl){
       if (find(longestwords.begin(), longestwords.end(), word) != longestwords.end())
		continue;
       else
       longestwords.push_back(word);
      }
      }
       
   
       
      }   
      if(scheck){	 
      string word = whitespace[i];
      int spacelength = word.length()-1;
       whitespace[i] = word[spacelength];
      }
      
	if(ccheck){	 
   int wordlength = words[i].length();
      string word = words[i];
	for(int j = 0; j<wordlength; j++){
       if(!isalpha(word[j])){
     	words[i].clear();
     	whitespace[i].clear();
        wordclearcount++;
        spaceclearcount++;
        break;
       }
      }
      }      
       
       if(pcheck){
        bool realword = true;
        bool goodword = true;
        bool acronym = true;

        charcount+=words[i].length();
        charcount+=whitespace[i].length();
        int wordlength = words[i].length();
        int spacelength = whitespace[i].length();
        string word = words[i];
        string space = whitespace[i];
	for(int l = 0; l<spacelength; l++){
      	if(space[l] == '\n')
         lines++;
    }
    for( int k = 0; k<wordlength; k++){
     	if(!isupper(word[k])){
         acronym = false;
        }
     	if(!isalpha(word[k])){
         realword = false;
        }
     	if(!isalnum(word[k])){
         goodword = false;
        }
    }
        if(acronym){acronymcount++;}
        if(realword){ realwordcount++;}
        if(goodword){ goodwordcount++;}
        
     	if(isupper(word[0])){
         capword++;
        }
       }
      
    
      
      
      
       
	if(qcheck == false) {     
   cout<<words[i]<<whitespace[i];
      }
     
     
     }
     if(pcheck && qcheck) {    
     cout<<"Characters "<< initcharcount<<" in "<< 0<< " out"<<endl; 
    cout<<"Lines "<< initlines<<" in "<< 0<< " out"<<endl; 
   cout<<"Words "<< spacesize<<" in "<<0<< " out"<<endl; 
     cout<<"Goodwords "<< initgoodwordcount<<" in"<<endl;
     cout<<"Realwords "<< initrealwordcount<<" in"<<endl; 
     cout<<"Capwords "<< initcapword<<" in"<<endl; 
     cout<<"Acronyms "<< initacronymcount<<" in"<<endl; 
}
     
     else {
      if(pcheck){
       if(ccheck){
      cout<<"Characters "<< initcharcount<<" in "<< charcount<< " out"<<endl; 
    cout<<"Lines "<< initlines<<" in "<< lines<< " out"<<endl; 
   cout<<"Words "<< wordssize<<" in "<<wordssize-wordclearcount<< " out"<<endl; 
     cout<<"Goodwords "<< initgoodwordcount<<" in"<<endl;
     cout<<"Realwords "<< initrealwordcount<<" in"<<endl; 
     cout<<"Capwords "<< initcapword<<" in"<<endl; 
     cout<<"Acronyms "<< initacronymcount<<" in"<<endl;
       }
       else{
        cout<<"Characters "<< initcharcount<<" in "<< charcount<< " out"<<endl; 
    cout<<"Lines "<< initlines<<" in "<< lines<< " out"<<endl; 
   cout<<"Words "<< wordssize<<" in "<<wordssize<< " out"<<endl; 
     cout<<"Goodwords "<< initgoodwordcount<<" in"<<endl;
     cout<<"Realwords "<< initrealwordcount<<" in"<<endl; 
     cout<<"Capwords "<< initcapword<<" in"<<endl; 
     cout<<"Acronyms "<< initacronymcount<<" in"<<endl;
       }
     }
     }
 	string temp ;
     //need to sort vectors and check for duplicate values, also delete commas
     if(lcheck){
     int len = longestwords.size();
     if(len>1){
     sort(longestwords.begin(), longestwords.end());
     for(int i=0;i<len;i++){
      temp+=longestwords[i];
      if(i<len-1)
      temp+=", ";
     }
     cout<<"Word (length "<<wordl<<"): "<<temp<<endl;
     temp.clear();
     }
     else cout<<"Word (length "<<wordl<<"): "<<longestwords[0]<<endl;
    int len2 = longestgoodwords.size();
     if(len2>1){
	 sort(longestgoodwords.begin(), longestgoodwords.end());

     for(int i =0;i<len2;i++){
      temp+=longestgoodwords[i];
      if(i<len2-1)
      temp+=", ";
     }
     cout<<"Goodword (length "<<goodwordl<<"): "<<temp<<endl;
      temp.clear();
     }
     else cout<<"Goodword (length "<<goodwordl<<"): "<<longestgoodwords[0]<<endl;
	    int len3 = longestrealwords.size();

      if(len3>1){
	 sort(longestrealwords.begin(), longestrealwords.end());

 for(int i =0;i<len3;i++){
      temp+=longestrealwords[i];
      if(i<len3-1)
      temp+=", ";
     }
	 cout<<"Realword (length "<<realwordl<<"): "<<temp<<endl;
	temp.clear();
     }
     else cout<<"Realword (length "<<realwordl<<"): "<<longestrealwords[0]<<endl;

      
     }
      
        
        return 0;
        }
 return 1;
}