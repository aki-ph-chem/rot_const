#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iostream>

#include<eigen3/Eigen/Core>

// 半角スペース区切りファイル用

/*このプログラムをカスタムしたものをclass化して,
他のプログラムに#includeして使えるようにする */


using namespace std;


// split 関数の定義
vector<string> split(string& input, char delimiter)
{
    istringstream stream(input);
    string field;
    vector<string> result;
    while (getline(stream, field, delimiter)) {
        result.push_back(field);
    }
    return result;
}

int main()
{
    ifstream ifs("test2.csv");
    
    /*
    string line;
   vector<string> strvec ;
    vector<double> v;
    vector<vector<string>> ww;
    
    //この方法ではメモリのアドレスがバラバラになってしまう
    while (getline(ifs, line)) {
        
         strvec = split(line, ' ');
        
        ww.push_back(strvec);
       
    }
    */

    // そこで改善策をここに示す

    string         reading_now;
    vector<string> buffer_array;
    vector<double> res;
    
    int num_of_col = 0;
    int buffer_size;
    
    
    while(getline(ifs,reading_now)){

        buffer_array = split(reading_now,' ');

        buffer_size = buffer_array.size();

        for(int i=0;i<buffer_size;i++){

            res.push_back(stod(buffer_array[i]));
        }

       num_of_col++; 

    }

using my_matrix = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>;

my_matrix matrix_a;

// メモリが連続なのでそれゆえきちんと働いた
matrix_a = Eigen::Map<my_matrix>(&res[0],num_of_col,buffer_size);

std::cout<<matrix_a<<std::endl;

// ちゃんと連続になった
/*
for(int i=0;i<num_of_col*6;i++){

    std::cout<<&res[i]<<std::endl;
}
*/

    
     
/*
   for (int i=0; i<26;i++){
       for (int j=0; j<strvec.size();j++)  
          {

          cout <<ww[i][j]<<endl;
          //cout <<stod(w[i][j])<<endl;　　　　　　　　//明らかに数字だったらおｋ

          }
       
        }  
*/   

  return 0;       
} 

