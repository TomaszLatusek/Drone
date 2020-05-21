#include "Scene.hh"
#include <memory>

using namespace std;

/**
 * @brief Construct a new Scene:: Scene object
 * Its just a first draft.
 * Don'r really know how to use it yet
 * 
 * @param c cuboid
 * @param w water surface
 * @param b bottom
 */
Scene::Scene()
{
    drone = new Drone;
    water = new WaterSurface;
    bottom = new BottomSurface;
}


Scene::~Scene()
{
    delete drone;
    delete water;
    delete bottom;
}

/**
 * @brief Wanted to use it to simplify main, not yet though 
 * 
 */
void Scene::draw() const
{
    drone->draw(kDroneFile);
    water->draw(kWaterFile);
    bottom->draw(kBottomFile);
}
