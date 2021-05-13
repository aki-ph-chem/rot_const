#include"function.h"
#include"grad_n.h"

void function::d_func(vector_d& input){

 
 d_f =  2*input;

  


}

void function::calc_df(){

    d_func(x_old);
}