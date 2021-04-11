#include<iostream>
#include"sloop.h"

void sloop::start_x(double sign_h){
    
    h = sign_h*h;

    x_before = x;
    x_after = x_before+h;
}

void sloop::forward_x(){
    
         h   = 2*h;
    x_before = x_after; 
    x_after  = x_before + h;
}

void sloop::back_x(){

    h = h/2 ;
    x_after = x_after - h;
}

void sloop::forward_stop(){

    x = x_before;
    h = h/2;

}

void sloop::back_stop(){

    x = x_after;
    h = 2*h;
}
