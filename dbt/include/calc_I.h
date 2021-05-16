#ifndef _CALC_I_H_
#define _CALC_I_H_
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigenvalues>

#include "calc_g.h"


// This class inherits from class calc_g

class I_tensor: public calc_g
{

public:
       // for inercital tensor
       Eigen::Matrix3d    I;
       void  calc_I_tensor();


       // for eigenvalues
       Eigen::Vector3d  result;
       void eigen_value();

       virtual ~I_tensor();


private: 
        // for calclation of elements of inertial tensor
        double calc_crs_term(int x1,int x2);
        double calc_drt_term(int x1);

        // declear eigensolver
        Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigensolver;

};





#endif //_CALC_I_H_