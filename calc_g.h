
#ifndef _CALC_G_H_
#define _CALC_G_H_

class calc_g{


public:
       

       void g(double* coor,double* Mass,int atoms,double* y);
       void cal_g_sys(double* coor,double* g,int atoms,double* G_sys);

};


# endif //_CALC_G_H_