# include "calc_g.h"
# include <iostream>

using namespace std;

void calc_g_coor::calc_g(double* coor,double* Mass){

double mass_total = 0;

   for(int k =1;k<4;k++){
    for(int i= 0;i<atoms;i++){

       x[k] +=  Mass[(int)coor[4*i+0]]*coor[4*i+k]; 
       
       mass_total +=Mass[(int)coor[4*i+0]]/3;   
  
    }
   }

for(int j=1;j<4;j++){

x[j]  = x[j]/mass_total;

}


}



void calc_g_coor::calc_g_sys(double* coor,double* g){
for(int i=0;i<4;i++){
   for(int j=0;j<atoms;j++){

      g_sys[j][i] = coor[4*j+i] - g[i];  
   }
}

}