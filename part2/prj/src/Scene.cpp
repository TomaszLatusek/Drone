#include "Scene.hh"

using namespace std;

/**
 * @brief Construct a new Scene:: Scene object
 * 
 */
Scene::Scene()
{
    drone = new Drone;
    water = new WaterSurface;
    bottom = new BottomSurface;
    initObstacles();
}

/**
 * @brief Destroy the Scene:: Scene object
 * 
 */
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
 * @brief Executes draw function of each scene element
 * 
 */
void Scene::draw() const
{
    drone->draw(kDroneFile);
    water->draw(kWaterFile);
    bottom->draw(kBottomFile);
    objects[0]->draw(kPoleFile);
    objects[1]->draw(kCuboidFile);
    objects[2]->draw(kRectangleFile);
}


/**
 * @brief Initializes list of shared pointers of obstacles
 * 
 */
void Scene::initObstacles()
{
    shared_ptr<Pole> pole = make_shared<Pole>();
    shared_ptr<Cuboid> cuboid = make_shared<Cuboid>();
    shared_ptr<Rectangle> rec = make_shared<Rectangle>();

    objects.push_back(pole);
    objects.push_back(cuboid);
    objects.push_back(rec);
}

/**
 * @brief Checks whether any of the obstacles collides with the drone
 * 
 * @return true     if there's a collision
 * @return false    if there's no collison
 */
bool Scene::checkCollision() const
{
    for(const auto& obstacle : objects){
        if(obstacle->checkCollision(*drone))
        {
            cout << "Watch out! You almost hit a  "; obstacle->getName();
            cout << endl;
            return 1;
        }
    }
    return 0;
}