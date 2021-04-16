# include "calc_g.h"
# include <iostream>
#include<eigen3/Eigen/Core>

typedef Eigen::Matrix<double,Eigen::Dynamic,4,Eigen::RowMajor> Matrix_dx4;


//これだけはうまく動く
//void calc_g::g( Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y){


//void calc_g::g( Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y){
//void calc_g::g(Eigen::MatrixXd& coor(atoms,4),double* Mass,int atoms,double* y){



//void calc_g::g(Matrix_dx4& coor,double* Mass,double* y){

//void calc_g::g(double* Mass,double* y){

void calc_g::calc_g_point(){

double mass_total = 0;

   for(int k =1;k<4;k++){
    for(int i= 0;i < num_of_atoms;i++){

       g_point[k] +=  Mass[(int)coordinates(i,0)]*coordinates(i,k); 
       
       mass_total +=Mass[(int)coordinates(i,0)]/3;   
  
    }
   }

for(int j=1;j<4;j++){

g_point[j]  = g_point[j]/mass_total;

  }


}



void calc_g::set_coordinates(Matrix_dx4 coordinates_for_calc){

   coordinates = coordinates_for_calc;
}

void calc_g::set_info(double*mass,double* g_point_0){

   Mass = mass;
   g_point = g_point_0;

}



//これはうまく動く
//void calc_g::cal_g_sys( Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,26,4,Eigen::RowMajor>& G_sys){

//void calc_g::cal_g_sys( Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& G_sys){
//void calc_g::cal_g_sys(Eigen::MatrixXd& coor(atoms,4),double* g,int atoms,Eigen::MatrixXd& G_sys(atoms,4)){


void calc_g::cal_g_sys(double* g){

for(int i=0;i<4;i++){
   for(int j=0;j<num_of_atoms;j++){

      G_sys(j,i) = coordinates(j,i) - g[i];  
   }
}

} 


