#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <sstream>

#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigenvalues>

//#include<eigen3/Eigen/Geometry>

#include "calc_g.h"
/*
#include "calc_I.h"
#include "geo.h"

*/

#include "csv_class.h"
#include "data.h"

//const int atoms = 26;  //tamplateで行列のサイズを決定する用

int atoms;

std::string input_file = "test2.csv" ;


const double conv = pow(10,-26)/6.02;                  
double x_1[4] = {0,0,0,0};
double x_2[4] = {0,0,0,0};


int main(){


calc_g    calc;  //重心計算クラスのインスタンス化
data      Data;  // 座標データのインスタンス化　
/*
I_tensor  IT;    //慣性テンソル計算クラスのインスタンス化
rod_rot   RR;   //回転クラスのインスタンス化
*/

csv_class* CC = nullptr; //csv読み込みクラスのインスタンス化


    
//データの読み込み

    std::ifstream ifs(input_file);
    std::string line;
    std::vector<std::string> strvec;
    std::vector<double> nume_vec(4);
    double v_data[100][4];

    int num_of_row = 0;

    std::vector<int> area = {1,3,4,5};
    
    while (getline(ifs, line)) {
        
         strvec = CC->split(line, ' ');

         
     for(int i = 0 ;i<4;i++){
       
            nume_vec[i] = stod(strvec[area[i]]);
     }


     for(int j = 0;j<4;j++){

         v_data[num_of_row][j] = nume_vec[j]; 

     }
         num_of_row++;

    }


atoms = num_of_row;

// データの読み込みfrom data.h これはうまく動く
//Eigen::Matrix<double,26,4,Eigen::RowMajor> co = Eigen::Map<Eigen::Matrix<double ,26,4,Eigen::RowMajor>> (&Data.sys[0][0],26,4);//Eigen::Matrixの左辺はMatrixXdよりtemplateを使うべき(そうしないと参照渡しした時にlvalueとrvalueがbindできなくなる)

// v_dataに格納したcsvファイルからデータ読み込み　これはうまく動かない
//Eigen::Matrix<double,26,4,Eigen::RowMajor> co = Eigen::Map<Eigen::Matrix<double ,26,4,Eigen::RowMajor>> (&v_data[0][0],26,4);  
//Eigen::Matrix<double,26,4> co = Eigen::Map<Eigen::Matrix<double ,26,4>> (&v_data[0][0],26,4);

// 静的配列を使って力技で動くようにした  これはうまく動く
//Eigen::Matrix<double,atoms,4,Eigen::RowMajor> co = Eigen::Map<Eigen::Matrix<double ,atoms,4,Eigen::RowMajor>> (&v_data[0][0],26,4);


Eigen::MatrixXd coordinates(4,atoms); 
coordinates= Eigen::Map<Eigen::MatrixXd>(&v_data[0][0],4,atoms);
auto coordinates_for_calc = coordinates.transpose();

/*
Eigen::MatrixXd A(atoms,4);

A = coordinates_for_calc;



for(int i=0;i<26;i++){

       std::cout<<v_data[i][0]<<","<<v_data[i][1]<<","<<v_data[i][2]<<","<<v_data[i][3]<<std::endl;

}



std::cout<<" from data.h" <<std::endl;


for(int i=0;i<26;i++){

       std::cout<<Data.sys[i][0]<<","<<Data.sys[i][1]<<","<<Data.sys[i][2]<<","<<Data.sys[i][3]<<std::endl;
}


*/




double *M = &Data.mass[0];
double *g = &x_1[0];
double *y = &x_2[0];

/*
Eigen::Matrix<double,atoms,4,Eigen::RowMajor> g_sys;
g_sys = Eigen::MatrixXd::Zero(atoms,4);
*/

Eigen::MatrixXd g_sys(atoms,4);
g_sys = Eigen::MatrixXd::Zero(atoms,4);


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


calc.atoms = atoms;
calc.set_coordinates(coordinates_for_calc);
calc.g(M,y);


/* これはうまく動く
calc.g(co,M,atoms,y);
calc.cal_g_sys(co,g,atoms,g_sys);  
*/


/*

// set axis (このaxisはフェニル基の2)
int i,j;
i = 13;
j = 1;

RR.axis = g_sys.row(i).tail(3) - g_sys.row(j).tail(3);

double norm = RR.axis.norm();

RR.axis = RR.axis/norm ;

// 13~23の原子を回転させる
std::vector<int> b = {13,14,15,16,17,18,19,20,21,22,23};

//ループに関する変数の宣言

double angle;
double angle_now;
double step;

//30°を1°ごと回転
angle_now = 360;
angle = 360;
step = 0;

// 総計算回数
 const int num_of_calc = 1//  angle/step ;

//結果を格納する配列の宣言
;std::vector<std::vector<double>> Result(num_of_calc,std::vector<double>(4));



std::ofstream ofs("angle_vs_rot_const.csv");

//ここからループ

for(int i=0;i<num_of_calc;i++){

angle_now = angle_now + step;

RR.set(angle_now);

// 13~23の原子を回転させる
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

Result[i][0] = angle_now;
Result[i][1] = rot_const(0);
Result[i][2] = rot_const(1);
Result[i][3] = rot_const(2);

ofs<<angle_now<<","<<rot_const(0)<<","<<rot_const(1)<<","<<rot_const(2)<<std::endl;

}

//ここまでループ


//結果を表示
//std::cout<<angle<<"°　"<<"回転させた結果"<<std::endl<<std::endl;

//std::cout <<rot_const<<std::endl;  

for(int j=0;j<num_of_calc;j++){

       std::cout<<Result[j][0]<<","<<Result[j][1]<<","<<Result[j][2]<<","<<Result[j][3]<<std::endl;
}


*/

return 0;
}