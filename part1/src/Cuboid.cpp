#include "Cuboid.hh"
#include "Matrix3D.hh"
#include "Matrix.hh"
#include "gnuplot_link.hh"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

/**
 * @brief Construct a new Cuboid:: Cuboid object
 * Sets angle value to 0 by default.
 * Initializes points with values from solid/model.dat
 */
Cuboid::Cuboid() : angle{0}
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
        counter++;
    }
    inputFile.close();
}

/**
 * @brief Saves rotated and translated points to a new file
 * 
 * @param filename name of the file you want gnuplot to draw from
 */
void Cuboid::draw(std::string filename) const
{
    ofstream outputFile;
    outputFile.open(filename);
    if (!outputFile.is_open())
    {
        cerr << "Unable to open drone file!" << endl;
        return;
    }

    Matrix3D rotation(angle);

    for (unsigned i = 0; i < points.size(); ++i)
    {
        outputFile << (rotation * points[i]) + translation << endl;
        if (i % 4 == 3) //triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
    }
}

/**
 * @brief Calculates the translation vector according to
 * the rotation angle, rise/dive angle and the distance.
 * 
 * @param angleXY rise(+) or dive(-) angle
 * @param distance 
 */
void Cuboid::move(double angleXY, double distance)
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
}

/**
 * @brief Used to stop the animation when it hits the bottom
 * or reaches the surface
 * 
 * @return true, if it hits the bottom or reach the surface
 * @return false, if everything is alright
 */
bool Cuboid::position() const
{
    if (translation[2] >= 175) //175 is the "sea" level
    {
        cout << "You made it to the surface!" << endl;
        return 1;
    }
    else if (translation[2] <= -200) //-200 is the bottom level
    {
        cout << "You hit the bottom!" << endl;
        return 1;
    }
    return 0;
}