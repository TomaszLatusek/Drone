#pragma once

#include "Shape.hh"

const std::string kModelWater("solid/waterRead.dat");
const std::string kWaterFile("solid/water.dat");

class WaterSurface: public Shape{
    public:
        WaterSurface();
        ~WaterSurface();
        virtual void draw(std::string filename) const override;
};