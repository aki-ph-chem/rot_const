#ifndef _CALC_I_H_
#define _CALC_I_H_
#include<eigen3/Eigen/Core>

#include "calc_g.h"

//前verでのクラス
/*
class I_tensor{

public: double crs(double *Mass,Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double conv,int atoms,int x1,int x2);
        double drc(double *Mass,Eigen::Matrix<double,26,4,Eigen::RowMajor>& coor,double conv,int atoms,int x1);

};
*/


// calc_gを継承した

class I_tensor: public calc_g
{

public: double conv; // main_2中で　[インスタンス].conv = conv;とする

public: double crs(int x1,int x2);
        double drc(int x1);

};



#endif //_CALC_I_H_