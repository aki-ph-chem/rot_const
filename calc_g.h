
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

       typedef Eigen::Matrix<double,Eigen::Dynamic,4,Eigen::RowMajor> Matrix_dx4;
       
       int atoms;

       //void g(double* Mass,double* y);
       //void cal_g_sys(double* g,int atoms,Eigen::MatrixXd& G_sys(atoms,4));
       
       void cal_g_sys(double* g);

       void g();
       
       public:  Matrix_dx4 G_sys;

       private: Matrix_dx4 coor;

       public:  void set_coordinates(Matrix_dx4 coordinates_for_calc);

       private: double* Mass;
                double* y;

       public:  void set_info(double*mass,double*y_0); 

        
       
       

       //void cal_g_sys(Eigen::MatrixXd& coor(atoms,4),double* g,int atoms,Eigen::MatrixXd& G_sys(atoms,4));
       
      
         

       
       /*
       
       public:

       static const int atoms = 26;

       void g(Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* Mass,int atoms,double* y);
       void cal_g_sys(Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& coor,double* g,int atoms,Eigen::Matrix<double,atoms,4,Eigen::RowMajor>& G_sys);

       
       */
};






# endif //_CALC_G_H_