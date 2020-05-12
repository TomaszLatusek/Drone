#include "Scene.hh"

using namespace std;

Scene::Scene(Cuboid c, WaterSurface w, BottomSurface b)
{
    drone = c;
    water = w;
    bottom = b;
}

void Scene::draw() const
{
    // drone.draw();
    // water.draw();
    // bottom.draw();
}
