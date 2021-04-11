#include<iostream>
#include<math.h>
#include<vector>
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

    x_0 = -0.3;
    h_0 = 0.001;
    e = pow(10,-2);

    std::vector<std::vector<double>> Result;
    std::vector<double> Res_set(4);
    
    sloop S;
    
    sign_h = sign(dx_func(x_0));
    S.set(sign_h,x_0,h_0);

    S.f = func(S.x_now);
    S.dx_f = dx_func(S.x_now);
    S.Memo(Result,Res_set); 
    
    int num_of_loop = 0;
    
    while( abs(dx_func(S.x_now)) > e ) {

        S.forward();
        S.f = func(S.x_now);
        S.dx_f = dx_func(S.x_now);

        S.Memo(Result,Res_set);

        num_of_loop++;
    }
    

std::cout<<"x = "<<S.x_now<<": f(x) = "<<func(S.x_now)<<std::endl;
std::cout<<"df(x)/dx = "<<dx_func(S.x_now)<<std::endl;
std::cout<<num_of_loop<<std::endl;


for(int i=0;i<num_of_loop;i++ ){

    std::cout<<Result[0][i]<<","<<Result[1][i]<<","<<Result[2][i]<<std::endl;
}


    return 0;
}