#include <iostream>
#include <math.h>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigenvalues>
#include "calc_I.h"

//num_of_atoms はclss calc_gのものを用いる
//coordinatesは class calc_gのものを用いるsetするにはset_coordinates()を用いる
//double* Massもcalc_gのものを用いる　setするにはser_info()を用いる


double I_tensor::calc_crs_term(int x1,int x2){

   double constant = 0;

    for(int j=0;j<num_of_atoms;j++){
   
       constant += Mass[(int)coordinates(j,0)]*coordinates(j,x1)*coordinates(j,x2);
    }
    
       return constant;

}

double I_tensor::calc_drt_term(int x1){

   double constant = 0;

      for(int i=0;i<num_of_atoms;i++){
         for(int j=1;j<4;j++){

            constant +=Mass[(int)coordinates(i,0)]*(pow(coordinates(i,j),2)-pow(coordinates(i,x1),2)/3);
  
         }
      }

  return constant;
}


void I_tensor::calc_I_tensor(){

      double xx,yy,zz,xy,yz,zx;
       xx=0,yy=0,zz=0,xy=0,yz=0,zx=0;

          xy = this->calc_crs_term(1,2);
          yz = this->calc_crs_term(2,3);
          zx = this->calc_crs_term(1,3);

          xx = this->calc_drt_term(1);
          yy = this->calc_drt_term(2);
          zz = this->calc_drt_term(3);

             Eigen::Matrix3d I_cross;
             Eigen::Matrix3d I_direct;

I_cross << 0,-xy,-zx,
           0,0,-yz,
           0,0,0;

I_direct << xx,0,0,
            0,yy,0,
            0,0,zz;

I = I_direct +I_cross + I_cross.transpose();


}



void I_tensor::eigen_value(){

  eigensolver.compute(I);
     
     if(eigensolver.info() != Eigen::Success) 
        
        abort();

           result = eigensolver.eigenvalues();

}

I_tensor::~I_tensor()
{

}