#ifndef _GRAD_N_H_
#define _GRAD_N_H_
#include<eigen3/Eigen/Core>

using vector_d = Eigen::Matrix<double,Eigen::Dynamic,1>;

class grad{
    public: 
            //number of variables
            static int size_of_vector;
            // learning rate
            double learning_rate;
            
            // error
            double delta;
            // calclation of error
            double calc_delta();
            
            // set protected x_old value from main()
            void set_x_old(vector_d& input_vector);
            // searching method
            void method();
            // update x_old
            void update();

            // value of delivative cofficient
            vector_d d_f;

            grad();
            ~grad();

            void show_result();

             
    protected: 
               // variavles 
               vector_d x_old, x_new;  
};





#endif // _GRAD_N_H_