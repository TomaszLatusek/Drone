#include "cuboid.hh"
#include "Matrix.hh"
#include <fstream>
#include <iostream>
#include <cmath>
#define M_PI 3.14159265358979323846

using namespace std;
using Matrix3D = Matrix<double,3>;


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
    for (unsigned i = 0; i < points.size(); ++i)
    {
        outputFile << points[i] + translation << endl;
        if (i % 4 == 3) // triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
    }
}

void Cuboid::rotate(char axis, double angle)
{
    angle *= M_PI / 180;
    Matrix3D rotateMatrix(axis,angle);
 
    for (int i = 0; i < points.size(); i++)
    {
        points[i] = rotateMatrix * points[i];
    }
}

void Cuboid::move(double angleZ, double angleXY, double distance)
{
    angleXY *= M_PI / 180;
    angleZ *= M_PI / 180;
    Vector3D change;

    for(int i=0;i<points.size();i++){
        change[0] = distance*cos(angleXY)*cos(angleZ);
        change[1] = distance*cos(angleXY)*sin(angleZ);
        if(angle>=0){
            change[2] = distance * sin(angleXY);  
        }else{
            change[2] = distance * cos(angleXY); 
        }
    }
    translate(change);
}