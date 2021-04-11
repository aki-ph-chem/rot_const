#include<iostream>
#include<vector>
#include"sloop_2.h"

void sloop::set(double sign_h,double x_0,double h_0){

    h = h_0;
    h = sign_h*h;
    x_now = x_0 + h;
}

void sloop::forward(){

    //h = 2*h;
    x_now = x_now + h;
}

void sloop::Memo(std::vector<std::vector<double>>& Result,
                std::vector<double>& Res_set  ){

Res_set[0] = x_now;
Res_set[1] =  f;
Res_set[2] = dx_f;


Result.push_back(Res_set);

}