
#ifndef _CALC_G_H_
#define _CALC_G_H_
#include<eigen3/Eigen/Core>



class calc_g{
       
       
       public:

       typedef Eigen::Matrix<double,Eigen::Dynamic,4,Eigen::RowMajor> Matrix_dx4;


       
       int num_of_atoms;
       
       void cal_g_sys(double* g);
       void calc_g_point();
       void set_info(double*mass,double* g_point_0); 
       

       public:    Matrix_dx4 G_sys;
       protected: Matrix_dx4 coordinates;

       public:  void set_coordinates(Matrix_dx4 coordinates_for_calc);
       
       protected: double* Mass;
                  double* g_point;

};






# endif //_CALC_G_H_