#include<iostream>
#include<eigen3/Eigen/Core>
#include "grad_n.h"

using std::cout;
using std::endl;
using vector_d = Eigen::Matrix<double,Eigen::Dynamic,1>;

double d_f(double input){

    double output;

    output = 2*input;

    return output;
}



int main(){

grad::size_of_vector = 1;
grad G;

bool loop_flag = true;


vector_d x_old;
x_old(0) = -2;

G.d_func(0) = d_f(-2);

double e = 0.01;

G.set_x_old(x_old);


while (loop_flag)
{   

   
G.method();

loop_flag = G.delta >= e ;



}



    return 0;
}