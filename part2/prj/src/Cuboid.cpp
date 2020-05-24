#include "Cuboid.hh"
#include <fstream>


using namespace std;

/**
 * @brief Construct a new Cuboid:: Cuboid object
 * 
 * Initializes points with values from solid/cuboidRead.dat
 */
Cuboid::Cuboid()
{
    ifstream inputFile;
    inputFile.open(kModelCuboid);
    if (!inputFile.is_open())
    {
        cerr << "Unable to load model Cuboid file!"
             << endl;
        return;
    }

    Vector3D point;
    while (inputFile >> point)
    {
        points.push_back(point);
        counterCurrent++;
    }
    inputFile.close();
}

/**
 * @brief Destroy the Cuboid:: Cuboid object
 * 
 */
Cuboid::~Cuboid()
{
    for (int i = 0; i < points.size(); i++)
    {
        points.pop_back();
        counterCurrent--;
    }
}

/**
 * @brief Saves points values to a new file which gnuplot can use
 * 
 * @param filename name of the file you want gnuplot to draw from
 */
void Cuboid::draw(string filename) const
{
    ofstream outputFile;
    outputFile.open(filename);
    if (!outputFile.is_open())
    {
        cerr << "Unable to open Cuboid file!" << endl;
        return;
    }

    for (unsigned i = 0; i < points.size(); ++i)
    {
        outputFile << points[i] << endl;
        if (i % 4 == 3) //triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
        counterTotal++;
    }
}

/**
 * @brief Calculates whether drone and objects collide
 * 
 * @param drone 
 * @return true     if there's a collision
 * @return false    if there's no collision
 */
bool Cuboid::checkCollision(const Drone &drone) const
{
    double maxXob, maxYob, maxZob;
           maxXob = maxYob = maxZob = -500;
    double minXob, minYob, minZob;
           minXob = minYob = minZob = 500;

    for (int i = 0; i < points.size(); i++)
    {
        if(maxXob < points[i][0]){
            maxXob = points[i][0];
        }
        if(maxYob < points[i][1]){
            maxYob = points[i][1];
        }
        if(maxZob < points[i][2]){
            maxZob = points[i][2];
        }
        if(minXob > points[i][0]){
            minXob = points[i][0];
        }
        if(minYob > points[i][1]){
            minYob = points[i][1];
        }
        if(minZob > points[i][2]){
            minZob = points[i][2];
        }
    }

    double maxXdr, maxYdr, maxZdr;
        maxXdr = maxYdr = maxZdr = -500;
    double minXdr, minYdr, minZdr;
        minXdr = minYdr = minZdr = 500;

    for (int i = 0; i < drone.contour.size(); i++)
    {
        double X = drone.contour[i][0];
        double Y = drone.contour[i][1];
        double Z = drone.contour[i][2];
        
        if(maxXdr < X){
            maxXdr = X;
        }
        if(maxYdr < Y){
            maxYdr = Y;
        }
        if(maxZdr < Z){
            maxZdr = Z;
        }
        if(minXdr > X){
            minXdr = X;
        }
        if(minYdr > Y){
            minYdr = Y;
        }
        if(minZdr > Z){
            minZdr = Z;
        }
    }

     int counter = 0;
    //X
    for(int i = minXob; i <= maxXob; i++){
        if(i <= maxXdr && i >= minXdr){
            counter++;
            break;
        }
    }
    //Y
    for(int i = minYob; i <= maxYob; i++){
        if(i <= maxYdr && i >= minYdr){
            counter++;
            break;
        }
    }
    //Z
    for(int i = minZob; i <= maxZob; i++){
        if(i <= maxZdr && i >= minZdr){
            counter++;
            break;
        }
    }

    if(counter >= 3){
        return 1;
    }else return 0;
}