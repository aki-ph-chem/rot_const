#include<iostream>
#include<fstream>
#include<math.h>
#include"grad.h"

double function(double x){
    
    return x*x + 4*x + 6;
}

double fun_dx(double x){

    return 2*x + 4;
}

double sign(double value){

    return (value>0) -(value<0);
}

int main(){

double x_0;
double delta;
double l_rate;
int num_of_loop = 0;


       x_0 = 3;
       delta  = pow(10,-5);
       l_rate = 0.001; 

grad G;

G.x_new = x_0;
G.x_old = 0;

G.learning_rate = l_rate;


std::ofstream ofs("grad_result.csv");

while( abs( G.x_new - G.x_old) > delta){

    G.x_old = G.x_new;
    G.f_dx = fun_dx(G.x_old);

   ofs<<num_of_loop<<","<<G.x_new<<std::endl;

    G.x_reset();

    num_of_loop++;
 

 std::cout<<num_of_loop<<"　回目のループでxの値は "<<G.x_new<<std::endl;

}


double x_anser = G.x_new;


std::cout<<"x_anser = "<<x_anser<<std::endl;
std::cout<<"function(x_anser) = "<<function(x_anser)<<std::endl;
std::cout<<num_of_loop<<std::endl;

    return 0;
}