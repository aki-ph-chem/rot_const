#include<iostream>
#include"sloop_2.h"

void sloop::set(double sign_h,double x_0,double h_0){

    h = h_0;
    h = sign_h*h;
    x_now = x_0 + h;
}

void sloop::forward(){

    h = 2*h;
    x_now = x_now + h;
}