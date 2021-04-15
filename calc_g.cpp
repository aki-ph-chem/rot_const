# include "calc_g.h"
# include <iostream>
#include<eigen3/Eigen/Core>



//これだけはうまく動く
//void calc_g::g( Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y){


//void calc_g::g( Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y){
//void calc_g::g(Eigen::MatrixXd& coor(atoms,4),double* Mass,int atoms,double* y){

void calc_g::g(double* Mass,double* y){

double mass_total = 0;

   for(int k =1;k<4;k++){
    for(int i= 0;i<atoms;i++){

       y[k] +=  Mass[(int)coor(i,0)]*coor(i,k); 
       
       mass_total +=Mass[(int)coor(i,0)]/3;   
  
    }
   }

for(int j=1;j<4;j++){

y[j]  = y[j]/mass_total;

  }


}


void calc_g::set_coordinates(Eigen::MatrixXd& coordinates_for_calc(atoms,4)){

   coor = coordinates_for_calc;
}


/*　これはうまく動く
void calc_g::cal_g_sys( Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,26,4,Eigen::RowMajor>& G_sys){

//void calc_g::cal_g_sys( Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& G_sys){
//void calc_g::cal_g_sys(Eigen::MatrixXd& coor(atoms,4),double* g,int atoms,Eigen::MatrixXd& G_sys(atoms,4)){

for(int i=0;i<4;i++){
   for(int j=0;j<atoms;j++){

      G_sys(j,i) = coor(j,i) - g[i];  
   }
}

} 
*/

