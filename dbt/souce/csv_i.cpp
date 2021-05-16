# include "csv_i.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using string   = std::string;
using vector_d = std::vector<double>;
using vector_s = std::vector<std::string>;


//std::vector<string> csv::split(string& reading_now,char delimiter)
std::vector<string> csv::split(string& reading_now)
{
    
    std::istringstream stream(reading_now);
    string field;
    std::vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}



void csv::read_file(std::string name_of_input_file){

 std::ifstream ifs(name_of_input_file);
 string   reading_now;
 vector_s buffer_array;


    int buffer_size;
    int area[4] = {1,3,4,5};

    while(getline(ifs,reading_now)){

        buffer_array = split(reading_now);
        
        buffer_size = buffer_array.size();

        for(int i=0;i<buffer_size - 2 ;i++){

            res.push_back(stod(buffer_array[area[i]]));
        }

       num_of_col++; 


    }

    
}
