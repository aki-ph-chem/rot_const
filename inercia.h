#ifndef _INERCIA_H_
#define _INERCIA_H_

class I_tensor{

public: double crs(double *Mass, double *coor,double conv,int atoms,int x1,int x2);
        double drc(double *Mass, double *coor,double conv,int atoms,int x1);

};



#endif //_INERCIA_H_