#include<iostream>
#include<eigen3/Eigen/Core>
#include<fstream>
#include<math.h>
#include "grad_2.h"

double func(double x,double y,double z){

    return x*x + y*y + z*z + 4;
}

double func_dx(double x){

    return 2*x;
}

double func_dy(double y){

    return 2*y;
}

double func_dz(double z){

    return 2*z;
}

int main(){

grad G;

Eigen::Vector3d x_0;
double alpha;
double delta;


x_0<<1,1,1;   


alpha = 0.001;
 
delta = pow(10,-5);

G.lerning_rate = alpha;

G.x_new = x_0;

G.x_old<<0,0,0;


bool loop_flag = true;

int num_of_loop = 0;

while(loop_flag){
   
   G.x_old = G.x_new;

   G.grad(0) = func_dx(G.x_old(0));
   G.grad(1) = func_dy(G.x_old(1));
   G.grad(2) = func_dz(G.x_old(2));

   G.x_reset();

  loop_flag = (G.x_new - G.x_old).norm() > delta;

  num_of_loop++;

}

Eigen::Vector3d result;

result = G.x_new;

std::cout<<result.transpose()<<std::endl;
std::cout<<num_of_loop<<std::endl;
std::cout<<(G.x_new - G.x_old).norm()<<std::endl;


    return 0;
}