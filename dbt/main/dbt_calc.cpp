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

#include "grad_n.h"



using string   = std::string;
using vector_s = std::vector<std::string>;

double g_point_0[4] = {0,0,0,0};
double d_angel = pow(10,-3);  //微分の刻み幅

string name_of_input_file = "dbt.csv";
string name_of_output_file = "result.csv";



// for calc gradient
namespace vector_io{

vector_d x_old;
vector_d d_f;

double error;

}

// for inilialize vector_io member
void init(int num_of_var){

vector_io::x_old = Eigen::VectorXd::Zero(num_of_var);
vector_io::d_f   = Eigen::VectorXd::Zero(num_of_var);

vector_io::error = pow(10,-2);

}



// sample data
Eigen::Vector3d obs_30;
// Delivative of Error function
void d_eroor(vector_d value,vector_d d_value ,vector_d obs){

    double result = 0;

       for(int i=0 ;i < 3 ;i++){
           
           result += -2*d_value(i)*(obs(i) - value(i) );

       }
          
          vector_io::d_f(0) = result;
       
}


            
int main(){

////////for gradien calclation \\\\\\

// set sample value 
obs_30<< 3324.591,897.274,1191.0;

// number of valuable
grad::size_of_vector = 1;

grad G;      // gradient class  

// initialize vector_io member
init(grad::size_of_vector);

// satart value 
vector_io::x_old(0) = 1;

// learning rate
G.learning_rate = 0.001;

// error
vector_io::error = pow(10,-5);

G.set_x_old(vector_io::x_old);

/////////// for gradient calclation  \\\\\\\\\\


data Data;  // mass & coordinates data
csv  CC;    // csv loading class

rod_rot   RR;   // rotational matrix class
rod_rot   RR_1;
rod_rot   RR_2;

I_tensor C;     //I_tensor class (It inherits class calc_g.)
I_tensor C_1;
I_tensor C_2;

// declear type of Matrix
using Matrix_dx4 = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>;


// reading CSV data
CC.delimiter = ' ';
CC.read_file(name_of_input_file);

Matrix_dx4 coordinates_0;

// convert 1_dimentional_array to Matrix;
int num_of_atoms = CC.num_of_col;
coordinates_0= Eigen::Map<Matrix_dx4>(&CC.res[0],num_of_atoms,4);


double *Mass = &Data.mass[0];
double *g_point = &g_point_0[0];


Matrix_dx4 g_sys;
g_sys = Eigen::MatrixXd::Zero(num_of_atoms,4);


Eigen::Array3d rot_const;
Eigen::Array3d rot_const_1;
Eigen::Array3d rot_const_2;

Eigen::Vector3d v;

//データの初期化


I_tensor::set_info(Mass,g_point);
I_tensor::num_of_atoms = num_of_atoms;


C.G_sys = g_sys;
C_1.G_sys = g_sys;
C_2.G_sys = g_sys;


//重心、重心座標系の計算(1)

C.set_coordinates(coordinates_0);
C.calc_g_point();
C.cal_g_sys(g_point);

Matrix_dx4 G_system_old = C.G_sys;

Matrix_dx4 G_system_new = G_system_old;
Matrix_dx4 G_system_1 = G_system_old;
Matrix_dx4 G_system_2 = G_system_old;


// set axis 
int atom_1,atom_2;

atom_1 = 17;
atom_2 = 5;

// rot S atom 


RR.axis  = G_system_old.row(atom_1).tail(3) - G_system_old.row(atom_2).tail(3);

double norm_of_axis = RR.axis.norm();

RR.axis = RR.axis/norm_of_axis;
RR_1.axis = RR.axis;
RR_2.axis = RR.axis;


//ループに関する変数の宣言

double angle_end;
double angle_now;
double step;

//30°を1°ごと回転
angle_now = -0.1;
angle_end = 31;
step = 0.1;

// 総計算回数
const int num_of_calc = (angle_end-angle_now)/step ;

;std::ofstream ofs(name_of_output_file);

//for buffer
Eigen::Vector3d e_val,e_val_1, e_val_2,Result;

bool loop_flag = true;
int num_of_loop = 0;

// loop start !!

//for(int i=0;i<num_of_calc;i++){

while(loop_flag){ 

angle_now = angle_now + step;

RR.set(angle_now);
RR_1.set(angle_now + d_angel);
RR_2.set(angle_now - d_angel);


// rot S atom
v = G_system_old.row(20).tail(3);

G_system_new.row(20).tail(3) = RR.Rot*v;
G_system_1.row(20).tail(3) = RR_1.Rot*v;
G_system_2.row(20).tail(3) = RR_2.Rot*v;

// calclation of center of mass system

C.set_coordinates(G_system_new);
C.calc_g_point();
C.cal_g_sys(g_point);

C_1.set_coordinates(G_system_1);
C_1.calc_g_point();
C_1.cal_g_sys(g_point);


C_2.set_coordinates(G_system_2);
C_2.calc_g_point();
C_2.cal_g_sys(g_point);


//慣性テンソルの計算

C.calc_I_tensor();
C_1.calc_I_tensor();
C_2.calc_I_tensor();

C.eigen_value();
C_1.eigen_value();
C_2.eigen_value();

e_val   = C.result;
e_val_1 = C_1.result;
e_val_2 = C_2.result;


ofs <<angle_now<<","<<e_val(0)<<","<<e_val(1)<<","<<e_val(2) <<std::endl;


Result = (e_val_1 - e_val_2)/(2*d_angel);



d_eroor(e_val,Result,obs_30);

G.set_df(vector_io::d_f);

G.method();

G.calc_delta();

loop_flag = vector_io::error <= G.delta;

G.update();

num_of_loop++;

}
// end loop




std::cout << "moment of inercia " <<std::endl;

std::cout<<e_val_1.transpose()<<std::endl;
std::cout<<e_val_2.transpose()<<std::endl;


std::cout<< "Derivative" <<std::endl; 

std::cout<<Result.transpose()<<std::endl;

std::cout<<num_of_loop<<std::endl;
std::cout<<angle_now<<std::endl;

return 0;

}