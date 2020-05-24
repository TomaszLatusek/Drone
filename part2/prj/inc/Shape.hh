#pragma once

#include <vector>
#include "Vector.hh"

/**
 * @brief Base class every drawable(?) element inherits from
 * 
 */
class Shape{
protected:
    std::vector<Vector3D> points;
    Vector3D translation;
public:
    void translate(Vector3D change)
        {translation = translation + change;}
    virtual void draw(std::string filename) const = 0;
    virtual ~Shape(){};

    inline static int counterTotal = 0;
    inline static int counterCurrent = 0;
};