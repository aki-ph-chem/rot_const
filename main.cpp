# include <iostream>
#include<eigen3/Eigen/Core>
# include "calc_g.h"
#include "data.h"
using namespace std;


 int atoms = 26;                    
double x_1[4] = {0,0,0,0};
double x_2[4] = {0,0,0,0};


int main(){

calc_g calc; //重心計算クラスのインスタンス化
data   Data; // 座標データのインスタンス化　

// データの読み込みfrom data.h

Eigen::Matrix<double,26,4,Eigen::RowMajor> co = Eigen::Map<Eigen::Matrix<double ,26,4,Eigen::RowMajor>> (&Data.sys[0][0],26,4);
//Eigen::Matrixの左辺はMatrixXdよりtemplateを使うべき(そうしないと参照渡しした時にlvalueとrvalueがbindできなくなる)

double *M = &Data.mass[0];


double *g = &x_1[0];
double *y = &x_2[0];

Eigen::Matrix<double,26,4,Eigen::RowMajor> g_sys;
g_sys = Eigen::MatrixXd::Zero(26,4);



// 計算
calc.g(co,M,atoms,y);
calc.cal_g_sys(co,g,atoms,g_sys);  







////////////結果の表示///////////////////

for(int i= 0;i<4;i++){

    cout<<g[i]<<endl;
}  

cout<<endl<<endl;

for(int i=0;i<atoms;i++){
   
      cout<<g_sys(i,0)<<","<<g_sys(i,1)<<","<<g_sys(i,2)<<","<<g_sys(i,3)<<endl;   
      }   



return 0;
}


