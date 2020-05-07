#include "cuboid.hh"
#include "Matrix.hh"
#include <fstream>
#include <iostream>
#include <cmath>

using namespace std;

Cuboid::Cuboid(): angle{0}
{
    ifstream inputFile;
    inputFile.open(kModelCuboid);
    if(!inputFile.is_open())
    {
        cerr << "Unable to load model Cuboid file!" 
             << endl;
        return;
    }

    Vector3D point;
    while(inputFile >> point)
    {
        points.push_back(point);
    }
    inputFile.close();
}

void Cuboid::draw(std::string filename) const
{
    ofstream outputFile;
    outputFile.open(filename);
    if(!outputFile.is_open())
    {
        cerr << "Unable to open drone file!" << endl;
        return;
    }
    for(unsigned i = 0; i < points.size(); ++i)
    {
        outputFile << points[i] + translation << endl;
        if(i % 4 == 3) // triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
    }
}

void Cuboid::rotate(double angle)
{
    /* Wstepna proba czy to w ogole dziala */
    for(int i=0;i<points.size();i++){
        double x = points[i][0];
        double y = points[i][1];
            points[i][0] = x*cos(angle) - y*sin(angle);
            points[i][1] = x*sin(angle) + y*cos(angle);
    }
}