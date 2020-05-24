#pragma once

#include "Shape.hh"
#include "Prism.hh"
#include <cmath>

const std::string kModelDrone("solid/model.dat");
const std::string kDroneFile("solid/drone.dat");

/**
 * @brief Represents a drone with 2 rotors
 * 
 */
class Drone: public Shape{
    Prism* leftRotor;
    Prism* rightRotor;
    double angle;
public:
    std::vector<Vector3D> contour;
    Drone();
    virtual ~Drone() override;
    virtual void draw(std::string filename) const override;
    void rotate(double change)
        {angle += (change*M_PI/180);}//degrees to radians
    void move(double angle, double distance);
    bool position() const;
};