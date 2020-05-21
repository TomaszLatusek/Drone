#include "Cuboid.hh"
#include <fstream>


using namespace std;

Cuboid::Cuboid()
{
    ifstream inputFile;
    inputFile.open(kModelCuboid);
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

Cuboid::~Cuboid()
{
    for (int i = 0; i < points.size(); i++)
    {
        points.pop_back();
        counterCurrent--;
    }
}

void Cuboid::draw(string filename) const
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
        outputFile << points[i] << endl;
        if (i % 4 == 3) //triggers after every 4 points
        {
            outputFile << "#\n\n";
        }
        counterTotal++;
    }
}