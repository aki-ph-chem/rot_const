# include "calc_g.h"
# include <iostream>
#include<eigen3/Eigen/Core>

using namespace std;

void calc_g::g( Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y){

//void calc_g::g( Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y){

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


void calc_g::cal_g_sys( Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,26,4,Eigen::RowMajor>& G_sys){

//void calc_g::cal_g_sys( Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& G_sys){

for(int i=0;i<4;i++){
   for(int j=0;j<atoms;j++){

      G_sys(j,i) = coor(j,i) - g[i];  
   }
}

} 


// I am in matrix_branch
