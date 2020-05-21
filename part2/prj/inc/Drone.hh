#pragma once

#include "Shape.hh"
#include <cmath>

const std::string kModelDrone("solid/model.dat");
const std::string kDroneFile("solid/drone.dat");

class Drone: public Shape{
    double angle;
public:
    Drone();
    virtual ~Drone() override;
    virtual void draw(std::string filename) const override;
    void rotate(double change)
        {angle += (change*M_PI/180);}//degrees to radians
    void move(double angle, double distance);
    bool position() const;
};