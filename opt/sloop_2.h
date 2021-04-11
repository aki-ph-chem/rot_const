#ifndef _SLOOP_2_H_
#define _SLOOP_2_H_

class sloop{

public:  double x_now,h;
         
         double f,dx_f;
            
         void set(double sign_h,double x_0,double h_0);
         void forward();

         void Memo(std::vector<std::vector<double>>& Result,
                std::vector<double>& Res_set  );
};




#endif// _SLOOP_2_H_