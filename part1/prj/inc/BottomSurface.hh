#pragma once

#include "Shape.hh"

const std::string kModelBottom("solid/bottomRead.dat");
const std::string kBottomFile("solid/bottom.dat");

class BottomSurface: public Shape{
    public:
        BottomSurface();
        ~BottomSurface();
        void draw(std::string filename) const;
};