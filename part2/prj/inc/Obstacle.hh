#pragma once

#include "Shape.hh"
#include "Drone.hh"

class Obstacle: public Shape{
    public:
        virtual void draw(std::string filename) const = 0;
        virtual bool checkCollision(const Drone &drone) const = 0;
        virtual void getName() const = 0;
};