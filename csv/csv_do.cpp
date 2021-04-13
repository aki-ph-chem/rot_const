#include "csv_class.h"

#include <fstream>
#include <sstream>

#include <string>
#include <vector>
#include <iostream>

using namespace std;


int main(){

    csv_class* CC = NULL;

    ifstream ifs("test2.csv");
    string line;
    
    vector<string> strvec;
    vector<double> v;
    
    vector<vector<string>> ww;
    vector<vector<double>> www;
    int length;

    
    while (getline(ifs, line)) {
        
         strvec = CC->split(line, ' ');

         length = strvec.size();

     for(int i=0;i<length;i++){
         
         v.push_back(std::stod(strvec.at(i)));

         std::cout<<std::stod(strvec.at(i))<<","<<v[i]<<std::endl;
     }
     
   
         ww.push_back(strvec);
        //www.push_back(v);
    }

 



/*

for (int i=0; i<26;i++){
       for (int j=0; j<length;j++)  
          {

          cout <<www[i][j]<<endl;
          
          }
       
        }     


*/

    return 0;
}



