#include <iostream>
#include <math.h>
#include <eigen3/Eigen/Dense>
using namespace std;
using namespace Eigen;


//---------------data for calc------------------------------------

int atoms = 26;
double mass[9] = {0,1.008,4.003,6.941,9.012,10.81,12.01,14.01,16.00};

double g_system[][4] = {
6,0.063906,0.70559,0,
6,-0.063906,-0.70559,0,
6,-1.279802,-1.409504,0,
6,-2.560087,-0.760278,0,
6,-3.724623,-1.49895,0,
1,-4.681875,-0.986327,0,
6,-3.690237,-2.894662,0,
6,-2.450567,-3.557013,0,
6,-1.279802,-2.840175,0,
1,-4.613348,-3.464565,0,
1,-2.419067,-4.641985,0,
1,-0.323273,-3.355307,0,
6,1.279802,1.409504,0,
6,1.279802,2.840175,0,
6,2.560087,0.760278,0,
6,2.450567,3.557013,0,
1,0.323273,3.355307,0,
6,3.724623,1.49895,0,
1,2.613527,-0.322184,0,
6,3.690237,2.894662,0,
1,2.419067,4.641985,0,
1,4.681875,0.986327,0,
1,4.613348,3.464565,0,
1,-2.613527,0.322184,0,
1,0.841896,-1.303675,0,
1,-0.841896,1.303675,0};

double conv = pow(10,-26)/6.02;

//--------------------------------------------------------------

// for calc cross term

 double crs(double *Mass,double *coor,int x1,int x2){
   double constant = 0;
    for(int j=0;j<atoms;j++){
   
    constant += conv*Mass[(int)coor[4*j+0]]*coor[4*j+x1]*coor[4*j+x2];
    }
 return constant;
 }

// for calc dorect term

double drc(double *Mass,double *coor,int x1){
  double constant = 0;
  for(int i=0;i<atoms;i++){
    for(int j=1;j<=3;j++){

      constant +=conv*Mass[(int)coor[4*i+0]]*(pow(coor[4*i+j],2)-pow(coor[4*i+x1],2)/3);
  
    }
  }

  return constant;
}



int main(){

double xx,yy,zz,xy,yz,zx;

xx=0;
yy=0;
zz=0;
xy=0;
yz=0;
zx=0;


double* g = &g_system[0][0];
double* M = &mass[0];

                              
xy = crs(M,g,1,2);
yz = crs(M,g,2,3);
zx = crs(M,g,1,3);

xx = drc(M,g,1);
yy = drc(M,g,2);
zz = drc(M,g,3);



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

return 0;
}  