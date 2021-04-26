#ifndef _GRAD_N_H_
#define _GRAD_N_H_
#include<eigen3/Eigen/Core>

using vector_d = Eigen::Matrix<double,Eigen::Dynamic,1>;

class grad{
    public: 
            static int size_of_vector;

            double learning_rate;
            double delta;
            double calc_delta();
            
            void set_x_old(vector_d& input_vector);
            void method();
            vector_d d_func;

            grad();
            ~grad();


    private: vector_d x_old,x_new;  
};





#endif // _GRAD_N_H_