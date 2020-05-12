#pragma once

#include "Shape.hh"

const std::string kModelWater("solid/waterRead.dat");
class WaterSurface: public Shape{
    public:
        WaterSurface();
        void draw(std::string filename) const;
};