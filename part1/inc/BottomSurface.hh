#pragma once

#include "Shape.hh"

const std::string kModelBottom("solid/bottomRead.dat");
class BottomSurface: public Shape{
    public:
        BottomSurface();
        void draw(std::string filename) const;
};