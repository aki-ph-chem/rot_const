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
#include "csv_i.h"
#include "data.h"



using string   = std::string;
using vector_d = std::vector<double>;
using vector_s = std::vector<std::string>;


int num_of_atoms;
const double conv = pow(10,-26)/6.02;                  
double g_point_0[4] = {0,0,0,0};

string name_of_input_file = "dbt.csv" ;
string name_of_output_file = "angle_vs_rot_const_dbt.csv";
            

int main(){

data      Data;  // 座標データのインスタンス化
rod_rot   RR;   //回転クラスのインスタンス化
csv CC;         // csv loading
I_tensor C;     //calc_gを継承したI_tensorのインスタンス化

// loading data

std::ifstream ifs(name_of_input_file);

    string   reading_now;
    vector_s buffer_array;
    vector_d res;
    
    int num_of_col = 0;
    int buffer_size;
    int area[4] = {1,3,4,5};

    CC.delimiter = ' ';

    while(getline(ifs,reading_now)){

        buffer_array = CC.split(reading_now);
        
        buffer_size = buffer_array.size();

        for(int i=0;i<buffer_size - 2 ;i++){

            res.push_back(stod(buffer_array[area[i]]));
        }

       num_of_col++; 

    }

    

num_of_atoms = num_of_col;


using Matrix_dx4 = Eigen::Matrix<double,Eigen::Dynamic,4,Eigen::RowMajor>;

Matrix_dx4 coordinates_0;
coordinates_0= Eigen::Map<Matrix_dx4>(&res[0],num_of_atoms,4);



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

//データの初期化

C.set_info(Mass,g_point);
C.conv = conv;
C.num_of_atoms = num_of_atoms;
C.G_sys = g_sys;


//重心、重心座標系の計算(1)

C.set_coordinates(coordinates_0);
C.calc_g_point();
C.cal_g_sys(g_point);

Matrix_dx4 G_system_old = C.G_sys;
Matrix_dx4 G_system_new = G_system_old;


// set axis 
int atom_1,atom_2;

atom_1 = 17;
atom_2 = 5;

// rot S atom 

RR.axis = G_system_old.row(atom_1).tail(3) - G_system_old.row(atom_2).tail(3);

double norm_of_axis = RR.axis.norm();

RR.axis = RR.axis/norm_of_axis ;



//ループに関する変数の宣言

double angle_end;
double angle_now;
double step;

//30°を1°ごと回転
angle_now = -0.1;
angle_end = 30;
step = 0.1;

// 総計算回数
const int num_of_calc = (angle_end-angle_now)/step ;

;std::ofstream ofs(name_of_output_file);

//ここからループ


for(int i=0;i<num_of_calc;i++){

angle_now = angle_now + step;

RR.set(angle_now);


// rot S atom
v = G_system_old.row(20).tail(3);
G_system_new.row(20).tail(3) = RR.Rot*v;



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