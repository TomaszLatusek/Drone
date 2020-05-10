#pragma once

#include "Matrix.hh"
#include <cmath>

class Matrix3D : public Matrix<double,3>
{
public:
    Matrix3D(double angle)
    {
        data[0][0] = cos(angle);
        data[0][1] = sin(angle);
        data[0][2] = 0;
        data[1][0] = -sin(angle);
        data[1][1] = cos(angle);
        data[1][2] = 0;
        data[2][0] = 0;
        data[2][1] = 0;
        data[2][2] = 1;
    }
};