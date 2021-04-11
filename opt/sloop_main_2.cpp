#include<iostream>
#include<math.h>
#include "sloop_2.h"

double func(double x){

     return -x*x + 4;
    //return sin(x);
}

double dx_func(double x){

     return -2*x;

    //return cos(x);
}

double sign(double value){

    return (value > 0) - (value < 0);
}

int main(){

    double x_0,h_0;
    double sign_h;
    double e;

    x_0 = 0.01;
    h_0 = 0.001;
    e = pow(10,-3);

    sloop S;
    
    sign_h = sign(dx_func(x_0));
    S.set(sign_h,x_0,h_0);

    while( abs( dx_func(S.x_now) ) < e){

        S.forward();
    }

std::cout<<"x = "<<S.x_now<<": f(x) = "<<func(S.x_now)<<std::endl;
std::cout<<"df(x)/dx = "<<dx_func(S.x_now)<<std::endl;

    return 0;
}