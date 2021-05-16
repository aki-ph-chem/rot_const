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
            
            //  value of error
            double delta;
            // calclation of error
            double calc_delta();
            

            // set protected x_old value from main()
            void set_x_old(vector_d& input_vector);
            // for seting  d_f
            void set_df(vector_d& input_df_value);


            // searching method
            void method();
            // update x_old
            void update();


            grad();
            ~grad();
            void show_result();

             
    
               // variavles 
  public:    vector_d  x_old;
  protected:       vector_d x_new;  
               // value of delivative cofficient
    protected: vector_d d_f;
};





#endif // _GRAD_N_H_
