#pragma once

#include <vector>
#include <string>
#include "Vector.hh"

const std::string kModelCuboid("solid/model.dat");
using Vector3D = Vector<double,3>;

class Cuboid{
    std::vector<Vector3D> points;
    Vector3D translation;
    double angle;

public:
    Cuboid();
    void draw(std::string filename) const;
    void translate(Vector3D change)
    {
        translation = translation + change;
    }
    void rotate(char axis, double angle);
    void move(double angleZ, double angle, double distance);
};