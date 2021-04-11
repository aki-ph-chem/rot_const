#include<iostream>

#ifndef _SLOOP_H_
#define _SLOOP_H_

class sloop{

  public: 
          double x,h;

          void start_x(double sign_h);

          void forward_x();
          void back_x();

          void forward_stop();
          void back_stop();



   
           double x_after,x_before;

};




#endif // _SLOOP_H_