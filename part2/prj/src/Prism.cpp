#include "Prism.hh"
#include "Matrix3D.hh"
#include <fstream>

using namespace std;

Prism::Prism() : angleX{0}
{
    ifstream inputFile;
    inputFile.open(kModelPrism);
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
}

Prism::~Prism()
{
    for (int i = 0; i < points.size(); i++)
    {
        points.pop_back();
        counterCurrent--;
    }
}

Vector3D Prism::fitToDrone(double y) const
{
    Vector3D change;
    change[0] = -37;
    change[1] = y;
    change[2] = 0;

    return change;
}

void Prism::followDrone(string filename, double angleZ, Vector3D change)
{
    ofstream outputFile;
    outputFile.open(filename);
    if (!outputFile.is_open())
    {
        cerr << "Unable to open drone file!" << endl;
        return;
    }

    if (angleX < 180) // rotor rotation angle
    {
        angleX += M_PI / 180;
    }
    else
    {
        angleX = 0;
    }

    Matrix3D rotationZ('z', angleZ);
    Matrix3D rotationX('x', angleX);
    Vector3D v, w;

    for (unsigned i = 0; i < points.size(); ++i)
    {
        v = rotationX * points[i];
        if (filename == "solid/rotorLeft.dat")
        {
            w = v + fitToDrone(20);
        }
        else if (filename == "solid/rotorRight.dat")
        {
            w = v + fitToDrone(-20);
        }

        outputFile << (rotationZ * w) + change << endl;
        if (i % 4 == 3) //triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
        counterTotal++;
    }
}