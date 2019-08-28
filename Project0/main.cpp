/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Nishanth_user
 *
 * Created on January 20, 2018, 10:51 AM
 */

#include <iostream>
#include <cstring>
#include <string> 
using namespace std;
int main(int argc, char *argv[]) {
    int length;
    if(argc <= 1){
        cout<<"MISSING SIZE"<< endl;
        return 0;
    }
    if((strcmp(argv[1], "small") == 0) || (strcmp(argv[1], "medium") == 0 )|| (strcmp(argv[1], "large") == 0)){
        for(int i = 2; i<argc;i = i+1){    
        if(strcmp(argv[1], "small") == 0){
            length = strlen(argv[i]);
            if(length>=5)
                cout<<argv[i]<<endl;
            }
        if(strcmp(argv[1], "medium") == 0){
            length = strlen(argv[i]);
            if(length>=10)
                cout<<argv[i]<<endl;
            }
        if(strcmp(argv[1], "large") == 0){
            length = strlen(argv[i]);
            if(length>=20)
                cout<<argv[i]<<endl;
            }
        }
    }
    else{   
        string fail = strcat(argv[1]," NOT A VALID SIZE");
        cout <<fail<< endl;
                return 0;
    }
    
    
    return 0;
    
}
    
    


