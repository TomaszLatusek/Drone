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
    for (int i = 0; i < objects.size(); i++)
    {
        objects.pop_back();
    }
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
    // for(int i = 0; i < objects.size(); i++)
    // {
    //     objects[0]->draw(kRectangleFile);
    // }
    objects[0]->draw(kPoleFile);
    objects[1]->draw(kCuboidFile);
    objects[2]->draw(kRectangleFile);
}



void Scene::initObstacles()
{
    shared_ptr<Pole> pole = make_shared<Pole>();
    shared_ptr<Cuboid> cuboid = make_shared<Cuboid>(kModelCuboid);
    shared_ptr<Rectangle> rec = make_shared<Rectangle>();

    objects.push_back(pole);
    objects.push_back(cuboid);
    objects.push_back(rec);
}


bool Scene::checkCollision(const Drone& drone) const
{
    for(const auto& obstacle : objects){
        if(obstacle->checkCollision(drone))
        {
            cout << "Przyjebales w cos" << endl;
            return 1;
        }
    }
    return 0;
}