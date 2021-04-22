#include<iostream>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Geometry>

#include"geo.h"

void rod_rot::set(double angle){

   Rot = Eigen::AngleAxisd(angle*M_PI/180,axis);

}