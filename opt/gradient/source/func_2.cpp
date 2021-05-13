#include"func_2.h"

void func_2::d_func(vector_d& input){

/*
 d_f(0) = 2*input(0);
 d_f(1) = 2*input(1);
*/

d_f = 2*input;

}

void func_2::calc_df(){

    d_func(x_old);
}
