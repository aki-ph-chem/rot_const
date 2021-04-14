
#ifndef _CALC_G_H_
#define _CALC_G_H_
#include<eigen3/Eigen/Core>

class calc_g{


public:
       
       
       void g(Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y);
       void cal_g_sys(Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,26,4,Eigen::RowMajor>& G_sys);

       
       /*
       
       static const int atoms = 26;

       void g(Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y);
       void cal_g_sys(Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& G_sys);

       
       */
};






# endif //_CALC_G_H_