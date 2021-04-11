#include<iostream>
#include"newton.h"

void newton::x_reset(){

    x_new = x_old - f_dx/f_dxx ;  
 
}
