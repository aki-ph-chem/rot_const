#include<iostream>
#ifndef _GRAD_H_
#define _GRAD_H_

class grad {

    public: double x_old,x_new;

            double f_dx;

            double learning_rate;
            
            void x_reset();
};


#endif //_GRAD_H_