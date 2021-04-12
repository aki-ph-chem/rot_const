#include<iostream>
#include"grad.h"


void grad::x_reset(){

    x_new = x_old - learning_rate*f_dx;
}

