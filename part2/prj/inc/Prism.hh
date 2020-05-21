#pragma once

#include "Shape.hh"

const std::string kModelPrismL("solid/prismX.dat");
const std::string kModelPrismR("solid/prismY.dat");
const std::string kLPrismFile("solid/rotorLeft.dat");
const std::string kRPrismFile("solid/rotorRight.dat");

class Prism: public Shape{
public:
    Prism(std::string filename);
    virtual ~Prism();
    virtual void draw(std::string filename) const override;
    void followDrone(std::string filename,double angle,Vector3D translation);
};