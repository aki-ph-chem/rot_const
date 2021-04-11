#include<iostream>
#ifndef _NEWTON_H_
#define _NEWTON_H_

class newton{

public: double x_old,x_new;
        
        double f_dx,f_dxx;

        void x_reset();

};

#endif //_NEWTON_H_