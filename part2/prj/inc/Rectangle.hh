#pragma once

#include "Obstacle.hh"

const std::string kModelRectangle("solid/rectangleRead.dat");
const std::string kRectangleFile("solid/rectangle.dat");

class Rectangle: public Obstacle{
  public:
    Rectangle();
    virtual ~Rectangle() override;
    virtual void draw(std::string filename) const override;
    virtual bool checkCollision(const Drone& drone) const;
    virtual void getName() const{std::cout << "rectangle";};
};