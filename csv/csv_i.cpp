# include "csv_i.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using string = std::string;



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

