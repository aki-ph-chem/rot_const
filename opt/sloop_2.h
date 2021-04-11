#ifndef _SLOOP_2_H_
#define _SLOOP_2_H_

class sloop{

public:  double x_now,h;

         void set(double sign_h,double x_0,double h_0);
         void forward();
};




#endif// _SLOOP_2_H_