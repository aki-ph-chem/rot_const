#include <iostream>
#include <math.h>
#include "inercia.h"
using namespace std;

double I_tensor::crs(double *Mass,double *coor,double conv,int atoms,int x1,int x2){
     double constant = 0;
    for(int j=0;j<atoms;j++){
   
    constant += conv*Mass[(int)coor[4*j+0]]*coor[4*j+x1]*coor[4*j+x2];
    }
 return constant;

}

double I_tensor::drc(double *Mass,double *coor,double conv,int atoms,int x1){
  double constant = 0;
  for(int i=0;i<atoms;i++){
    for(int j=1;j<=3;j++){

      constant +=conv*Mass[(int)coor[4*i+0]]*(pow(coor[4*i+j],2)-pow(coor[4*i+x1],2)/3);
  
    }
  }

  return constant;
}