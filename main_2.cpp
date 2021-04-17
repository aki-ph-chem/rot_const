#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <sstream>

#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigenvalues>
#include<eigen3/Eigen/Geometry>

#include "calc_g.h"
#include "calc_I.h"
#include "geo.h"
#include "csv_class.h"
#include "data.h"


int num_of_atoms;
const double conv = pow(10,-26)/6.02;                  
double g_point_0[4] = {0,0,0,0};

std::string name_of_input_file = "test2.csv" ;

int main(){


calc_g    calc;  //重心計算クラスのインスタンス化　
I_tensor  IT;    //慣性テンソル計算クラスのインスタンス化


rod_rot   RR;   //回転クラスのインスタンス化
csv_class* CC = nullptr; //csv読み込みクラスのインスタンス化

data      Data;  // 座標データのインスタンス化

I_tensor C; //calc_gを継承したI_tensorのインスタンス化


    
//データの読み込み

    std::ifstream ifs(name_of_input_file);
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

num_of_atoms = num_of_row;

typedef Eigen::Matrix<double,Eigen::Dynamic,4,Eigen::RowMajor> Matrix_dx4;

Matrix_dx4 coordinates_0;
coordinates_0= Eigen::Map<Matrix_dx4>(&v_data[0][0],num_of_atoms,4);


double *Mass = &Data.mass[0];
double *g_point = &g_point_0[0];


// 101行目で定義した型を用いる

Matrix_dx4 g_sys;
g_sys = Eigen::MatrixXd::Zero(num_of_atoms,4);

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


/*

// 重心、重心座標系の計算(1)

calc.set_info(Mass,g_point);
calc.num_of_atoms = num_of_atoms;
calc.G_sys = g_sys;


calc.set_coordinates(coordinates_0);
calc.calc_g_point();
calc.cal_g_sys(g_point);

*/

//重心、重心座標系の計算(1)

C.set_info(Mass,g_point);
C.conv = conv;
C.num_of_atoms = num_of_atoms;
C.G_sys = g_sys;

C.set_coordinates(coordinates_0);
C.calc_g_point();
C.cal_g_sys(g_point);





// set axis (このaxisはフェニル基の2)
int atom_1,atom_2;

atom_1 = 13;
atom_2 = 1;

// 13~23の原子を回転させる
std::vector<int> phenyl_2 = {13,14,15,16,17,18,19,20,21,22,23};


//RR.axis = calc.G_sys.row(atom_1).tail(3) - calc.G_sys.row(atom_2).tail(3);

RR.axis = C.G_sys.row(atom_1).tail(3) - C.G_sys.row(atom_2).tail(3);

double norm_of_axis = RR.axis.norm();

RR.axis = RR.axis/norm_of_axis ;





//ループに関する変数の宣言

double angle_end;
double angle_now;
double step;

//30°を1°ごと回転
angle_now = 0;
angle_end = 0;
step = 0;

// 総計算回数
 const int num_of_calc = 1 //angle_end/step ;

//結果を格納する配列の宣言
;std::vector<std::vector<double>> Result(num_of_calc,std::vector<double>(4));





//std::ofstream ofs("angle_vs_rot_const.csv");


std::string name_of_output_file;
            name_of_output_file = "angle_vs_rot_const.csv";
std::ofstream ofs(name_of_output_file);



//ここからループ

for(int i=0;i<num_of_calc;i++){

angle_now = angle_now + step;

RR.set(angle_now);


// 13~23の原子を回転させる
for(int &i : phenyl_2){

Eigen::Vector3d v = C.G_sys.row(i).tail(3);
C.G_sys.row(i).tail(3) = RR.Rot*v;
//calc.G_sys.row(i).tail(3) = RR.Rot*v;

}


/*
calc.set_coordinates(calc.G_sys);
calc.calc_g_point();
calc.cal_g_sys(g_point);
*/


C.set_coordinates(C.G_sys);
C.calc_g_point();
C.cal_g_sys(g_point);


std::cout<<C.G_sys<<std::endl;

//慣性テンソルの計算

/*
xy = IT.crs(M,calc.G_sys,conv,num_of_atoms,1,2);
yz = IT.crs(M,calc.G_sys,conv,num_of_atoms,2,3);
zx = IT.crs(M,g_sys,conv,num_of_atoms,1,3);

xx = IT.drc(M,calc.G_sys,conv,num_of_atoms,1);
yy = IT.drc(M,calc.G_sys,conv,num_of_atoms,2);
zz = IT.drc(M,calc.G_sys,conv,num_of_atoms,3);   

*/




xy = C.crs(1,2);
yz = C.crs(2,3);
zx = C.crs(1,3);

xx = C.drc(1);
yy = C.drc(2);
zz = C.drc(3);



//atoms

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

/*

for(int j=0;j<num_of_calc;j++){

       std::cout<<Result[j][0]<<","<<Result[j][1]<<","<<Result[j][2]<<","<<Result[j][3]<<std::endl;
}

*/


return 0;
}