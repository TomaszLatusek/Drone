#include "Drone.hh"
#include "Matrix3D.hh"
#include "Matrix.hh"
#include "gnuplot_link.hh"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief Construct a new Drone:: Drone object
 * 
 * Sets angle value to 0 by default.
 * Initializes points with values from solid/model.dat
 */
Drone::Drone() : angle{0}
{
    ifstream inputFile;
    inputFile.open(kModelDrone);
    if (!inputFile.is_open())
    {
        cerr << "Unable to load model Drone file!"
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

    leftRotor = new Prism;
    rightRotor = new Prism;

    inputFile.open("solid/contour.dat");
    if (!inputFile.is_open())
    {
        cerr << "Unable to load \"collision cage\" file!"
             << endl;
        return;
    }
    while (inputFile >> point)
    {
        contour.push_back(point);
    }
    inputFile.close();
    
}

/**
 * @brief Destroy the Drone:: Drone object
 * 
 */
Drone::~Drone()
{
    for (int i = 0; i < points.size(); i++)
    {
        points.pop_back();
        counterCurrent--;
    }
    delete rightRotor;
    delete leftRotor;
}

/**
 * @brief Saves rotated and translated points to a new file
 * 
 * @param filename name of the file you want gnuplot to draw from
 */
void Drone::draw(std::string filename) const
{
    ofstream outputFile;
    outputFile.open(filename);
    if (!outputFile.is_open())
    {
        cerr << "Unable to open Drone file!" << endl;
        return;
    }

    Matrix3D rotation('z',angle);

    for (unsigned i = 0; i < points.size(); ++i)
    {
        outputFile << (rotation * points[i]) + translation << endl;
        if (i % 4 == 3) //triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
        counterTotal++;
    }
    // making rotors follow the hull
    leftRotor->followDrone(kLPrismFile,angle,translation);
    rightRotor->followDrone(kRPrismFile,angle,translation);
}

/**
 * @brief Calculates the translation vector according to
 * the rotation angle, rise/dive angle and the distance.
 * 
 * @param angleXY rise(+) or dive(-) angle
 * @param distance 
 */
void Drone::move(double angleXY, double distance)
{
    angleXY *= M_PI / 180; //degrees to radians
    Vector3D change;

    for (int i = 0; i < points.size(); i++)
    {
        change[0] = distance * cos(angleXY) * cos(angle);
        change[1] = distance * cos(angleXY) * sin(angle);
        change[2] = distance * sin(angleXY);
    }
    translate(change);

    // moves the "collision cage" around the drone
    for (int i = 0; i < contour.size(); i++)
    {
        contour[i] = contour[i] + change;
    }
    
}

/**
 * @brief Used to stop the animation when it hits the bottom
 * or reaches the surface
 * 
 * @return true, if it hits the bottom or reach the surface
 * @return false, if everything is alright
 */
bool Drone::position() const
{
    if (translation[2] >= 175) //175 is the "sea" level
    {
        cout << "You made it to the surface!" << endl;
        return 1;
    }
    else if (translation[2] <= -180) //-200 is the bottom level
    {
        cout << "You hit the bottom!" << endl;
        return 1;
    }
    return 0;
}