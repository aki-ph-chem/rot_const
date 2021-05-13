#include<iostream>
#include<eigen3/Eigen/Core>
#include "grad_n.h"
#include "function.h"


using std::cout;
using std::endl;
using vector_d = Eigen::Matrix<double,Eigen::Dynamic,1>;


int main(){

function G;
function::size_of_vector = 1;



vector_d x_old;
x_old = Eigen::VectorXd::Zero(1);

x_old(0) = -1;
G.learning_rate = 0.01;
double error = 0.0000101;


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