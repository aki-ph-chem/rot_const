#include<eigen3/Eigen/Core>
#include<iostream>
#include "grad_n.h"

// definition of the type of vector
using vector_d = Eigen::Matrix<double,Eigen::Dynamic,1>;
// initialize the number of variables (static member)
int grad::size_of_vector = 1;


// constuructor...initialize variables shuch as x_old, x_new, d_func

grad::grad():learning_rate(1),x_old(Eigen::VectorXd::Zero(size_of_vector)),
                              x_new(Eigen::VectorXd::Zero(size_of_vector)),
                              d_f(Eigen::VectorXd::Zero(size_of_vector))
{

std::cout<<" The constructer has been exected!"<<std::endl;


}

// destructor

grad::~grad(){

}





// set x_old(n-dimentional vector)

void grad::set_x_old(vector_d& input_vector){

    x_old = input_vector;
}

// for setting  of d_f

void grad::set_df(vector_d& input_df_value){

d_f = input_df_value;

}


// searching method

void grad::method(){

    x_new = -learning_rate * d_f  + x_old;

}


void grad::update(){

    x_old = x_new;
}


// calclation of error

double grad::calc_delta(){

    delta = (x_new - x_old).norm();

    return delta;
}

// for viewing result

void grad::show_result(){

    std::cout<<"error of this calclation"<<std::endl;

    std::cout<<delta<<std::endl;

    std::cout<<"result of this calclation :"<<std::endl;

    std::cout<<x_new.transpose() <<std::endl;
}