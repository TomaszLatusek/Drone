#pragma once

#include "Shape.hh"

class Obstacle: public Shape{
    public:
        virtual void draw(std::string filename) const = 0;
};