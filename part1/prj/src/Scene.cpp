#include "Scene.hh"

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
Scene::Scene(Cuboid c, WaterSurface w, BottomSurface b)
{
    drone = c;
    water = w;
    bottom = b;
}

/**
 * @brief Wanted to use it to simplify main, not yet though 
 * 
 */
void Scene::draw() const
{
    // drone.draw();
    // water.draw();
    // bottom.draw();
}
