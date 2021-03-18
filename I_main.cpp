#include<iostream>
#include<math.h>
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Eigenvalues>
#include<eigen3/Eigen/Geometry>

#include"calc_I.h" 
#include"calc_g.h" 


#include"data.h"  //for test data

using namespace std;
using namespace Eigen;


int main(){

I_tensor IT;
data     D;
calc_g   G;

SelfAdjointEigenSolver<Matrix3d> eigensolver;
 
double conv = pow(10,-26)/6.02;
int    atoms = 26;

double xx,yy,zz,xy,yz,zx;
       xx=0,yy=0,zz=0,xy=0,yz=0,zx=0;

double angle;
Vector3d axis;
Matrix3d Rot;
double x[4] = {0,0,0,0};


axis<<0,0,1;

Rot = AngleAxisd(angle*M_PI/180,axis);


double* g = &D.sys[0][0];
double* M = &D.mass[0];
double* y = &x[0];



///////////////////////////////////////////////////////


G.g(g,M,atoms,y);
G.cal_g_sys(g,y,atoms,g);


xy = IT.crs(M,g,conv,atoms,1,2);
yz = IT.crs(M,g,conv,atoms,2,3);
zx = IT.crs(M,g,conv,atoms,1,3);

xx = IT.drc(M,g,conv,atoms,1);
yy = IT.drc(M,g,conv,atoms,2);
zz = IT.drc(M,g,conv,atoms,3);   



Matrix3d  I;
Matrix3d  I_cross;
Matrix3d  I_direct;
Array3d  e_val;

I_cross << 0,-xy,-zx,
           0,0,-yz,
           0,0,0;

I_direct << xx,0,0,
            0,yy,0,
            0,0,zz;


I = I_direct +I_cross + I_cross.transpose();


 eigensolver.compute(I);
 
if (eigensolver.info() != Success) abort();    // eigen value problem 
 e_val = eigensolver.eigenvalues(); 
 
Array3d rot_const = 2.799275*pow(10,-26)/e_val ;






cout <<rot_const<<endl;    





    return 0;
}