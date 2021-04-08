# include <iostream>
#include<eigen3/Eigen/Core>
#include "calc_g.h"
#include "calc_I.h"
#include "data.h"



int atoms = 26;  
double conv = pow(10,-26)/6.02;                  
double x_1[4] = {0,0,0,0};
double x_2[4] = {0,0,0,0};


int main(){

calc_g    calc; //重心計算クラスのインスタンス化
data      Data; // 座標データのインスタンス化　
I_tensor  IT;   //慣性テンソル計算クラスのインスタンス化

// データの読み込みfrom data.h

Eigen::Matrix<double,26,4,Eigen::RowMajor> co = Eigen::Map<Eigen::Matrix<double ,26,4,Eigen::RowMajor>> (&Data.sys[0][0],26,4);
//Eigen::Matrixの左辺はMatrixXdよりtemplateを使うべき(そうしないと参照渡しした時にlvalueとrvalueがbindできなくなる)

double *M = &Data.mass[0];


double *g = &x_1[0];
double *y = &x_2[0];

Eigen::Matrix<double,26,4,Eigen::RowMajor> g_sys;
g_sys = Eigen::MatrixXd::Zero(26,4);



double xx,yy,zz,xy,yz,zx;
       xx=0,yy=0,zz=0,xy=0,yz=0,zx=0;

Eigen::Matrix3d  I;
Eigen::Matrix3d  I_cross;
Eigen::Matrix3d  I_direct;
Eigen::Array3d  e_val;


// 重心、重心座標系の計算
calc.g(co,M,atoms,y);
calc.cal_g_sys(co,g,atoms,g_sys);  

//慣性テンソルの計算

xy = IT.crs(M,g_sys,conv,atoms,1,2);
yz = IT.crs(M,g_sys,conv,atoms,2,3);
zx = IT.crs(M,g_sys,conv,atoms,1,3);

xx = IT.drc(M,g_sys,conv,atoms,1);
yy = IT.drc(M,g_sys,conv,atoms,2);
zz = IT.drc(M,g_sys,conv,atoms,3);   

I_cross << 0,-xy,-zx,
           0,0,-yz,
           0,0,0;

I_direct << xx,0,0,
            0,yy,0,
            0,0,zz;


I = I_direct +I_cross + I_cross.transpose();


std::cout<<I<<std::endl;


/*

////////////結果の表示///////////////////

for(int i= 0;i<4;i++){

    cout<<y[i]<<endl;
}  

cout<<endl<<endl;

for(int i=0;i<atoms;i++){
   
      cout<<g_sys(i,0)<<","<<g_sys(i,1)<<","<<g_sys(i,2)<<","<<g_sys(i,3)<<endl;   
      }   

*/

return 0;
}


