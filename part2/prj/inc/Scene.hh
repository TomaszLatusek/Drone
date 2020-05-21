#pragma once

#include "WaterSurface.hh"
#include "BottomSurface.hh"
#include "Drone.hh"
#include <vector>

class Scene{
    Drone* drone;
    WaterSurface* water;
    BottomSurface* bottom;
    public:
        Scene();
        ~Scene();
        void draw() const;
        void drawDrone(){drone->draw(kDroneFile);};
        void rotateDrone(double angle){drone->rotate(angle);};
        void moveDrone(double angle, double distance)
            {drone->move(angle,distance);};
        bool dronePosition(){drone->position();};
};