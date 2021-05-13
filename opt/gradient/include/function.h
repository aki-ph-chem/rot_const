#include "grad_n.h"

#ifndef _FUNCTION_H_
#define _FUNCTION_H_

class function : public grad{

public: void d_func(vector_d& input);

        void   calc_df();

};




#endif // _FUNCTION_H_
