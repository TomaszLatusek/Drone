#pragma once

#include <vector>
#include "Vector.hh"

class Shape{
protected:
    std::string filename;
    std::vector<Vector3D> points;
    Vector3D translation;
public:
    void translate(Vector3D change)
        {translation = translation + change;}
    inline static int counterTotal = 0;
    inline static int counterCurrent = 0;
};