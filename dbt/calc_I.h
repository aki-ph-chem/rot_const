#ifndef _CALC_I_H_
#define _CALC_I_H_
#include<eigen3/Eigen/Core>

#include "calc_g.h"


// calc_gを継承した

class I_tensor: public calc_g
{

public: double conv; // main_2中で　[インスタンス].conv = conv;とする
        Eigen::Matrix3d I;

public: double calc_crs_term(int x1,int x2);
        double calc_drt_term(int x1);
        void calc_I_tensor();

};





#endif //_CALC_I_H_