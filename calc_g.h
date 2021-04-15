
#ifndef _CALC_G_H_
#define _CALC_G_H_
#include<eigen3/Eigen/Core>

class calc_g{

       
       /*
　　　　このクラスはうまく動く

       public:
       
       void g(Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y);
       void cal_g_sys(Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,26,4,Eigen::RowMajor>& G_sys);
       
       */
       
       
       public:
       
       int atoms = 3;

       void g(double* Mass,double* y);
       
       //void set_coordinates(auto coordinates_for_calc);
         void set_coordinates(Eigen::MatrixXd& coordinates_for_calc(atoms,4));

       //void cal_g_sys(Eigen::MatrixXd& coor(atoms,4),double* g,int atoms,Eigen::MatrixXd& G_sys(atoms,4));
       
       private:

       Eigen::MatrixXd coor;
         

       
       /*
       
       public:

       static const int atoms = 26;

       void g(Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y);
       void cal_g_sys(Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& G_sys);

       
       */
};






# endif //_CALC_G_H_