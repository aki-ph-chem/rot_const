#include<iostream>
#include<math.h>
//#include<eigen3/Eigen/Dense>
#include"inercia.h"
#include"data.h"

using namespace std;
//using namespace Eigen;

int main(){

I_tensor IT;
data    D;

double conv = pow(10,-26)/6.02;
int atoms;

double xx,yy,zz,xy,yz,zx;


xx=0;
yy=0;
zz=0;
xy=0;
yz=0;
zx=0;   


double* g = &D.sys[0][0];
double* M = &D.mass[0];

                              
xy = IT.crs(M,g,conv,atoms,1,2);
yz = IT.crs(M,g,conv,atoms,2,3);
zx = IT.crs(M,g,conv,atoms,1,3);

xx = IT.drc(M,g,conv,atoms,1);
yy = IT.drc(M,g,conv,atoms,2);
zz = IT.drc(M,g,conv,atoms,3);


cout<<IT.crs(M,g,conv,atoms,1,2)<<endl;

/*
cout<<xy<<" "<<yz<<" "<<zx<<endl<<endl;
cout<<xx<<" "<<yy<<" "<<zz<<endl;      */



/*

Matrix3d  I;
Matrix3d  I_cross;
Matrix3d  I_direct;

I_cross << 0,-xy,-zx,
           0,0,-yz,
           0,0,0;

I_direct << xx,0,0,
            0,yy,0,
            0,0,zz;

I = I_direct +I_cross + I_cross.transpose();



SelfAdjointEigenSolver<Matrix3d> eigensolver;
 
 eigensolver.compute(I);
 
if (eigensolver.info() != Success) abort();    // eigen value problem 
 
Array3d  e_val;
Array3d rot_const;

e_val = eigensolver.eigenvalues();

rot_const = 2.799275*pow(10,-26)/e_val ;

cout <<rot_const<<endl;    


*/


    return 0;
}