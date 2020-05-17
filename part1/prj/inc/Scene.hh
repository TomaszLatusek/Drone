#pragma once

#include "WaterSurface.hh"
#include "BottomSurface.hh"
#include "Cuboid.hh"
#include <vector>

class Scene{
    WaterSurface water;
    BottomSurface bottom;
    Cuboid drone; // Drone class coming next, not yet though
    // vector<Cuboid> objects;

    public:
    Scene(Cuboid c, WaterSurface w, BottomSurface b);
    void draw() const;
};