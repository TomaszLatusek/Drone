#pragma once

#include "WaterSurface.hh"
#include "BottomSurface.hh"
#include "Drone.hh"
#include "Obstacle.hh"
#include "Pole.hh"
#include "Rectangle.hh"
#include "Cuboid.hh"
#include <vector>
#include <memory>


class Scene{
    Drone* drone;
    WaterSurface* water;
    BottomSurface* bottom;
    std::vector<std::shared_ptr<Obstacle>> objects;
    public:
        Scene();
        ~Scene();
        void draw()const;
        void drawDrone(){drone->draw(kDroneFile);};
        void rotateDrone(double angle){drone->rotate(angle);};
        void moveDrone(double angle, double distance)
            {drone->move(angle,distance);};
        bool dronePosition() const {drone->position();};
        void initObstacles();
        bool checkCollision() const;
};