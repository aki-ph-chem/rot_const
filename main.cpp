# include <iostream>
# include "calc_g.h"
#include "data.h"
using namespace std;


int atoms = 26;                    
double x[4] = {0,0,0,0};
double g_sys[26][4];  



int main(){

calc_g calc; //重心計算クラスのインスタンス化
data   Data; // 座標データのインスタンス化　


double *co = &Data.sys[0][0];
double *M = &Data.mass[0];


double *g = &x[0];
double *y = &x[0];
double *G_sys = &g_sys[0][0];

calc.g(co,M,atoms,y);
calc.cal_g_sys(co,g,atoms,G_sys);


for(int i= 0;i<4;i++){

    cout<<x[i]<<endl;
}  

cout<<endl<<endl;

for(int i=0;i<atoms;i++){
   
      cout<<g_sys[i][0]<<","<<g_sys[i][1]<<","<<g_sys[i][2]<<","<<g_sys[i][3]<<endl;
      }   



return 0;
}


