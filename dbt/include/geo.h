#ifndef _ROT_H_
#define _ROT_H_
#include<eigen3/Eigen/Core>
#include<eigen3/Eigen/Geometry>

class rod_rot{

public: Eigen::Vector3d axis;
        Eigen::Matrix3d Rot;
        void set(double angle);

};


#endif //_ROT_H_