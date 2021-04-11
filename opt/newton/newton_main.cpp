#include<iostream>
#include<math.h>
#include "newton.h"

double func(double x){
     return -x*x*x*x + 4;
    
}

double func_dx(double x){

     return -4*x*x*x;

}

double func_dxx(double x){

    return -12*x*x;
}



int main(){

double x_0;

      x_0 = 10;
     
double delta;

     delta = std::pow(10,-4);

newton N;

N.x_new = x_0;
N.x_old = 0;

while(abs( N.x_new - N.x_old ) > delta){

N.x_old = N.x_new;

N.f_dx = func_dx(N.x_old);
N.f_dxx = func_dxx(N.x_old);

N.x_reset();

}

double x_anser = N.x_new;

std::cout<<"x_anser = "<<x_anser<<" : Max{func(x)} = "<<func(x_anser)<<std::endl;


return 0;
}