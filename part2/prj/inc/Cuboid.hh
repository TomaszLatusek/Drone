#pragma once

#include "Shape.hh"
#include "Obstacle.hh"

const std::string kModelCuboid("solid/cuboidRead.dat");
const std::string kCuboidFile("solid/cuboid.dat");

class Cuboid: public Obstacle{
  public:
    Cuboid(std::string filename);
    virtual ~Cuboid() override;
    virtual void draw(std::string filename) const override;
    virtual bool checkCollision(const Drone& drone) const;
    Vector3D getVector(int index){return points[index];};
    int size()const{return points.size();};
    virtual bool checkCollision(const Drone& drone) const;
};