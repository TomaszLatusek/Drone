#pragma once

#include "WaterSurface.hh"
#include "BottomSurface.hh"
#include "Cuboid.hh"
#include <vector>

class Scene{
    WaterSurface water;
    BottomSurface bottom;
    Cuboid drone; //trzeba bedzie dodac klase drona, ale na razie obejdzie sie bez niej
    // vector<Cuboid> objects;

    public:
    Scene(Cuboid c, WaterSurface w, BottomSurface b);
    void draw() const;
};