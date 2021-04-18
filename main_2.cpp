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
std::string name_of_output_file = "angle_vs_rot_const.csv";
            

int main(){

data      Data;  // 座標データのインスタンス化
rod_rot   RR;   //回転クラスのインスタンス化
csv_class* CC = nullptr; //csv読み込みクラスのインスタンス化

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


// 70行目で定義した型を用いる

Matrix_dx4 g_sys;
g_sys = Eigen::MatrixXd::Zero(num_of_atoms,4);


// 各種行列の宣言
Eigen::Matrix3d  I;
//ソルバの宣言
Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver;

Eigen::Array3d  e_val;
Eigen::Array3d rot_const;
Eigen::Vector3d v;

//重心、重心座標系の計算(1)

C.set_info(Mass,g_point);
C.conv = conv;
C.num_of_atoms = num_of_atoms;
C.G_sys = g_sys;

C.set_coordinates(coordinates_0);
C.calc_g_point();
C.cal_g_sys(g_point);

Matrix_dx4 G_system_old = C.G_sys;
Matrix_dx4 G_system_new = G_system_old;


// set axis (このaxisはフェニル基の2)
int atom_1,atom_2;

atom_1 = 13;
atom_2 = 1;

// 13~23の原子を回転させる
std::vector<int> phenyl_2 = {13,14,15,16,17,18,19,20,21,22,23};


RR.axis = G_system_old.row(atom_1).tail(3) - G_system_old.row(atom_2).tail(3);

double norm_of_axis = RR.axis.norm();

RR.axis = RR.axis/norm_of_axis ;


//ループに関する変数の宣言

double angle_end;
double angle_now;
double step;

//30°を1°ごと回転
angle_now = 0;
angle_end = 360;
step = 10;

// 総計算回数
 const int num_of_calc = (angle_end-angle_now)/step ;

;std::ofstream ofs(name_of_output_file);

//ここからループ


for(int i=0;i<num_of_calc;i++){

angle_now = angle_now + step;

RR.set(angle_now);



// 13~23の原子を回転させる
for(int &i : phenyl_2){

Eigen::Vector3d v = G_system_old.row(i).tail(3);
G_system_new.row(i).tail(3) = RR.Rot*v;

}


C.set_coordinates(G_system_new);
C.calc_g_point();
C.cal_g_sys(g_point);


//慣性テンソルの計算

C.calc_I_tensor();
I = C.I;


//対角化計算
eigensolver.compute(I);
 
if (eigensolver.info() != Eigen::Success) abort();

e_val = eigensolver.eigenvalues();

rot_const = 2.799275*pow(10,-26)/e_val ;


ofs<<angle_now<<","<<rot_const(0)<<","<<rot_const(1)<<","<<rot_const(2)<<std::endl;

}


return 0;
}