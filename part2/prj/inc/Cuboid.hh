#pragma once

#include "Shape.hh"
#include "Obstacle.hh"

const std::string kModelCuboid("solid/cuboidRead.dat");
const std::string kCuboidFile("solid/cuboid.dat");

class Cuboid: public Obstacle{
  public:
    Cuboid();
    virtual ~Cuboid() override;
    virtual void draw(std::string filename) const override;
};