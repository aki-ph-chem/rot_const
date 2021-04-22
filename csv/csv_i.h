// for csv reading

#ifndef _CSV_I_H_
#define _CSV_I_H_

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

class csv{

    public: 
            //std::string& reading_now;
            char delimiter;
            

            
            //std::vector<std::string> split(std::string& reading_now,char delimiter);
            
            std::vector<std::string> split(std::string& reading_now);

};





#endif //_CSV_I_H_