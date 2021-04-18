#include <iostream>
#include <vector>
#include <string>

#include <fstream>
#include <sstream>

#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigenvalues>


#include "calc_g.h"
#include "calc_I.h"
#include "csv_class.h"
#include "data.h"


int num_of_atoms;
const double conv = pow(10,-26)/6.02;                  
double g_point_0[4] = {0,0,0,0};

// input file name
std::string name_of_input_file = "dbt.csv" ;

//output file name
std::string name_of_output_file = "rot_const_test.csv";

int main(){

/*
std::cout<<"Let enter input file name "<<std::endl;
std::cin>> name_of_input_file;

std::cout<< "Let enter output file name" <<std::endl;
std::cin>> name_of_output_file;
*/

data Data;                 //information of atoms 
csv_class* CC = nullptr;   // csv class

I_tensor C;               // calc_gを継承したclass 

//load coordinates data from .csv file


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


Matrix_dx4 g_sys;
g_sys = Eigen::MatrixXd::Zero(num_of_atoms,4);

// decrear 3x3 matrix for Inercial tensor
Eigen::Matrix3d  I;

// decrear solver
Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver;

Eigen::Array3d  e_val;
Eigen::Array3d rot_const;

// calc center of mass , calc center of mass system

C.set_info(Mass,g_point);
C.conv = conv;
C.num_of_atoms = num_of_atoms;
C.G_sys = g_sys;

C.set_coordinates(coordinates_0);
C.calc_g_point();
C.cal_g_sys(g_point);



//calc elements of inercial tencer
C.calc_I_tensor();
I = C.I;

// solve eigen value probrem

eigensolver.compute(I);
 
if (eigensolver.info() != Eigen::Success) abort();

e_val = eigensolver.eigenvalues();

rot_const = 2.799275*pow(10,-26)/e_val ;


std::ofstream ofs(name_of_output_file);

ofs<<"This file is rotational constant A,B,C (cm-1)"<<std::endl;
ofs<<rot_const(0)<<","<<rot_const(1)<<","<<rot_const(2)<<std::endl;





return 0;

}