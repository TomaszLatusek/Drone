#include "Pole.hh"
#include <fstream>

using namespace std;

Pole::Pole()
{
    ifstream inputFile;
    inputFile.open(kModelPole);
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

Pole::~Pole()
{
    for (int i = 0; i < points.size(); i++)
    {
        points.pop_back();
        counterCurrent--;
    }
}

void Pole::draw(string filename) const
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
        counterTotal++;
    }
}