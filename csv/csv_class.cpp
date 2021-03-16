# include "csv_class.h"
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std;

vector<string> csv_class::split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}