#pragma once

#include <vector>
#include "Vector.hh"

class Shape{
protected:
    std::vector<Vector3D> points;
    Vector3D translation;
public:
    void translate(Vector3D change)
        {translation = translation + change;}
    inline static int counter = 0;
};