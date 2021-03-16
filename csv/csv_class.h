
// csvの読み書き用のclass

# ifndef    _CSV_CLASS_H_
# define   _CSV_CLASS_H_
#include <vector>
#include <string>


class csv_class {

public: 

        std::string& input;
        char delimiter; 


         std::vector<std::string> split(std::string& input,char delimiter);

};


#endif   //_CSV_CLASS_H_