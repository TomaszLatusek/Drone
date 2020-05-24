#pragma once

#include "Shape.hh"

const std::string kModelPrism("solid/prismX.dat");
const std::string kLPrismFile("solid/rotorLeft.dat");
const std::string kRPrismFile("solid/rotorRight.dat");

/**
 * @brief Represents rotor of a drone
 * 
 */
class Prism: public Shape{
    double angleX;
public:
    Prism();
    virtual ~Prism();
    virtual void draw(std::string filename) const override{};
    Vector3D fitToDrone(double y) const;
    void followDrone(std::string filename,double angle,Vector3D translation);
};