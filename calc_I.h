#ifndef _CALC_I_H_
#define _CALC_I_H_

class I_tensor{

public: double crs(double *Mass, double *coor,double conv,int atoms,int x1,int x2);
        double drc(double *Mass, double *coor,double conv,int atoms,int x1);

};



#endif //_CALC_I_H_