#pragma once

#include "Obstacle.hh"

const std::string kModelPole("solid/poleRead.dat");
const std::string kPoleFile("solid/pole.dat");

/**
 * @brief 1D type of obstacle
 * 
 */
class Pole: public Obstacle{
  public:
    Pole();
    virtual ~Pole() override;
    virtual void draw(std::string filename) const override;
    virtual bool checkCollision(const Drone& drone) const;
    virtual void getName() const{std::cout << "pole";};
};