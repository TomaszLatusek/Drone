#include "Cuboid.hh"
#include "Matrix3D.hh"
#include "Matrix.hh"
#include "gnuplot_link.hh"
#include <fstream>
#include <iostream>
#include <cmath>


using namespace std;

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
    }
    inputFile.close();

    counter++;
}

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
            if (i % 4 == 3) // triggers after every 4 points
            {
                outputFile << "#\n\n";
            }
        }
}

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