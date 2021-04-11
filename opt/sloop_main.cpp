#include<iostream>
#include<math.h>
#include "sloop.h"

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

      x_0 = 1;
      h_0 = 0.01;

double e;

      e = std::pow(10,-1);

sloop S;

S.x = x_0;
S.h = h_0;

int num_of_loop = 0;

while(abs( dx_func(S.x)) >e){

double sign_h = sign(dx_func(S.x));
S.start_x(sign_h);


if(func(S.x_after)>=func(S.x_before))
{
    while(func(S.x_after)>=func(S.x_before)){
        S.forward_x();
        num_of_loop ++;
    }

    S.forward_stop();
}


else
{
    while(func(S.x_after)<=func(S.x_before)){
        S.back_x();
        num_of_loop ++;
    }

    S.back_stop();
} 


}


std::cout<<"x = "<<S.x<<": f(x) = "<<func(S.x)<<std::endl;
std::cout<<"df(x)/dx = "<<dx_func(S.x)<<std::endl;
std::cout<<num_of_loop<<std::endl;
    return 0;
}