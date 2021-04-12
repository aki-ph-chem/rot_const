#include<iostream>
#include<eigen3/Eigen/Core>

#ifndef _GRAD_2_H_
#define _GRAD_2_H_

class grad{

public: Eigen::Vector2d x_old,x_new,grad;


        double lerning_rate;


        void x_reset();
        

};


#endif // _GRAD_H_