#include<iostream>
#include<eigen3/Eigen/Core>
#include "grad_2.h"


void grad::x_reset(){

    x_new = x_old -lerning_rate*grad;
}