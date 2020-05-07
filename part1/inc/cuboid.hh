#pragma once

#include <vector>
#include <string>
#include "Vector.hh"
using Vector3D = Vector<double,3>;

const std::string kModelCuboid("solid/model.dat");

class Cuboid{
    std::vector<Vector3D> points;
    Vector3D translation;
    double angle;

public:
    Cuboid();
    void draw(std::string filename) const;
    void translate(const Vector3D& change)
    {
        translation = translation + change;
    }
    void rotate(double angle);
};