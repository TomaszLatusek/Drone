#pragma once

#include <vector>
#include <string>
#include "Vector.hh"
#include "Shape.hh"
#include <cmath>

const std::string kModelCuboid("solid/model.dat");
const std::string kDroneFile("solid/drone.dat");

class Cuboid: public Shape{
    double angle;
public:
    Cuboid();
    ~Cuboid();
    void draw(std::string filename) const;
    void rotate(double change)
        {angle += (change*M_PI/180);}//degrees to radians
    void move(double angle, double distance);
    bool position() const;
};