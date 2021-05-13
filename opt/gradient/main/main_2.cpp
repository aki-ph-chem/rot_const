#include<iostream>
#include<eigen3/Eigen/Core>
#include "grad_n.h"
#include "func_2.h"


using std::cout;
using std::endl;
using vector_d = Eigen::Matrix<double,Eigen::Dynamic,1>;


int main(){

func_2 G;
func_2::size_of_vector = 2;



vector_d x_old;


x_old = Eigen::VectorXd::Zero(func_2::size_of_vector);

x_old(0) = -1;
x_old(1) = -1;


G.learning_rate = 0.01;
double error = pow(10,-5);


G.set_x_old(x_old);
bool loop_flag = true;

int num_of_loop = 0;


while (loop_flag)
{   

G.calc_df();

G.method();

G.calc_delta();


loop_flag =  error <= G.delta ;


G.update();

num_of_loop++;

}


cout<<num_of_loop<<endl;

G.show_result();



    return 0;
}