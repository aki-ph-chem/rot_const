#include <iostream>
#include <math.h>
#include<eigen3/Eigen/Core>
#include "calc_I.h"

//num_of_atoms はclss calc_gのものを用いる
//coordinatesは class calc_gのものを用いるsetするにはset_coordinates()を用いる
//double* Massもcalc_gのものを用いる　setするにはser_info()を用いる

double I_tensor::crs(int x1,int x2){
     double constant = 0;
    for(int j=0;j<num_of_atoms;j++){
   
    constant += conv*Mass[(int)coordinates(j,0)]*coordinates(j,x1)*coordinates(j,x2);
    }
 return constant;

}

double I_tensor::drc(int x1){
  double constant = 0;
  for(int i=0;i<num_of_atoms;i++){
    for(int j=1;j<4;j++){

      constant +=conv*Mass[(int)coordinates(i,0)]*(pow(coordinates(i,j),2)-pow(coordinates(i,x1),2)/3);
  
    }
  }

  return constant;
}

/*

double I_tensor::crs(double *Mass,Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double conv,int atoms,int x1,int x2){
     double constant = 0;
    for(int j=0;j<atoms;j++){
   
    constant += conv*Mass[(int)coor(j,0)]*coor(j,x1)*coor(j,x2);
    }
 return constant;

}

double I_tensor::drc(double *Mass, Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double conv,int atoms,int x1){
  double constant = 0;
  for(int i=0;i<atoms;i++){
    for(int j=1;j<4;j++){

      constant +=conv*Mass[(int)coor(i,0)]*(pow(coor(i,j),2)-pow(coor(i,x1),2)/3);
  
    }
  }

  return constant;
}


*/