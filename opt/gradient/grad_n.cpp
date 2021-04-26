#include<eigen3/Eigen/Core>
#include "grad_n.h"

using vector_d = Eigen::Matrix<double,Eigen::Dynamic,1>;

int grad::size_of_vector = 1;

// コンストラクタ、デストラクタ

grad::grad():learning_rate(0),x_old(Eigen::VectorXd::Zero(size_of_vector)),
                              x_new(Eigen::VectorXd::Zero(size_of_vector)),
                              d_func(Eigen::VectorXd::Zero(size_of_vector))
{

}

grad::~grad(){

}

void grad::set_x_old(vector_d& input_vector){

    this->d_func = input_vector;
}


void grad::method(){

    x_new = -learning_rate * d_func  + x_old;
}

double grad::calc_delta(){

    delta = (x_new - x_old).norm();

    return delta;
}