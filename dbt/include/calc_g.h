
#ifndef _CALC_G_H_
#define _CALC_G_H_
#include<eigen3/Eigen/Core>

using Matrix_dx4 = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>;

class calc_g{
       
       
           


       public:  // set number of atoms
                static int num_of_atoms;

                // set mass & initialize center of mass
                static void set_info(double* mass, double* g_point_0);

                // center of mass 
                Matrix_dx4  G_sys;
                
                // setting coordinates
                 void  set_coordinates(Matrix_dx4 coordinates_for_calc);

                 // calclation of center of mass & center of mass sysytem
                 void cal_g_sys(double* g);
                 void calc_g_point();
       

       protected: 
                  // setted by function set_coordinates
                  Matrix_dx4 coordinates;

                  // setted by function set_info
                  static double* Mass;
                  static double* g_point;

};






# endif //_CALC_G_H_