#pragma once

#include "Shape.hh"

const std::string kModelWater("solid/waterRead.dat");
const std::string kWaterFile("solid/water.dat");

/**
 * @brief Representation of water surface
 * 
 */
class WaterSurface: public Shape{
    public:
        WaterSurface();
        ~WaterSurface();
        virtual void draw(std::string filename) const override;
};