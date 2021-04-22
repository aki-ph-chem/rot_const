# include "csv_i.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using string   = std::string;
using vector_d = std::vector<double>;
using vector_s = std::vector<std::string>;


string input_file_name = "test2.csv";



int main(){
    //csv* C = nullptr; //インスタンス化
      csv C;

    std::ifstream ifs(input_file_name);

    string   reading_now;
    vector_s buffer_array;
    vector_d res;
    
    int num_of_col = 0;
    int buffer_size;

   // C->delimiter = ' '; //区切り文字

    C.delimiter = ' ';

    
    
    while(getline(ifs,reading_now)){

        //buffer_array = C->split(reading_now,' ');
        // buffer_array.push_back(reading_now);


        //buffer_array = C->split(reading_now);
        buffer_array = C.split(reading_now);


        buffer_size = buffer_array.size();

        for(int i=0;i<buffer_size;i++){

            res.push_back(stod(buffer_array[i]));
        }

     
   
       num_of_col++; 

    }
    



    //for(int i=0;i<num_of_col*buffer_size;i++)
    for(int i=0;i<num_of_col*buffer_size;i++)
    {

    std::cout<<res[i]<<std::endl;

      //std::cout<<buffer_array[i]<<std::endl;
 }



return 0;

}