#include "csv_class.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;


int main(){

    csv_class* CC = NULL;

    ifstream ifs("test2.csv");
    string line;
   vector<string> strvec ;
    vector<double> v;
    vector<vector<string>> ww;
    while (getline(ifs, line)) {
        
         strvec = CC->split(line, ' ');
        
        ww.push_back(strvec);
       
    }

for (int i=0; i<26;i++){
       for (int j=0; j<strvec.size();j++)  
          {

          cout <<ww[i][j]<<endl;
          //cout <<stod(w[i][j])<<endl;　　　　　　　　//明らかに数字だったらおｋ

          }
       
        }     




    return 0;
}




/*
int main()
{   
   csv_class c;

    ifstream ifs("data.csv");

    string line;
    while (getline(ifs, line)) {
        
        vector<string> strvec = c.split(line, ',');
        
        for (int i=0; i<strvec.size();i++){
            printf("%5d\n", stoi(strvec.at(i)));
        }
        
    }
}  */