# include <iostream>
# include <vector>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigenvalues>
#include<eigen3/Eigen/Geometry>

#include "calc_g.h"
#include "calc_I.h"
#include "geo.h"

#include "data.h"

const int atoms = 26;  
const double conv = pow(10,-26)/6.02;                  
double x_1[4] = {0,0,0,0};
double x_2[4] = {0,0,0,0};



int main(){

calc_g    calc;  //重心計算クラスのインスタンス化
data      Data;  // 座標データのインスタンス化　
I_tensor  IT;    //慣性テンソル計算クラスのインスタンス化
rod_rot   RR;   //回転クラスのインスタンス化


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

// 各種行列の宣言
Eigen::Matrix3d  I;
Eigen::Matrix3d  I_cross;
Eigen::Matrix3d  I_direct;
//ソルバの宣言
Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver;

Eigen::Array3d  e_val;
Eigen::Array3d rot_const;
Eigen::Vector3d v;


// 重心、重心座標系の計算(1)
calc.g(co,M,atoms,y);
calc.cal_g_sys(co,g,atoms,g_sys);  

// set axis (このaxisはフェニル基の2)
int i,j;
i = 13;
j = 1;

RR.axis = g_sys.row(i).tail(3) - g_sys.row(j).tail(3);

double norm = RR.axis.norm();

RR.axis = RR.axis/norm ;

//ここから下の処理をループする予定

//set angle (axisに対して90°)

double angle = 360;
RR.set(angle);

// 13~23の原子を回転させる
std::vector<int> b = {13,14,15,16,17,18,19,20,21,22,23};


for(int &i : b){

Eigen::Vector3d v = g_sys.row(i).tail(3);
g_sys.row(i).tail(3) = RR.Rot*v;

}


// 重心、重心座標系の計算(2)
calc.g(g_sys,M,atoms,y);
calc.cal_g_sys(g_sys,g,atoms,g_sys); 



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

//対角化計算
eigensolver.compute(I);
 
if (eigensolver.info() != Eigen::Success) abort();

e_val = eigensolver.eigenvalues();

rot_const = 2.799275*pow(10,-26)/e_val ;


//結果を表示
std::cout<<angle<<"°　"<<"回転させた結果"<<std::endl<<std::endl;

std::cout <<rot_const<<std::endl;      


return 0;
}


