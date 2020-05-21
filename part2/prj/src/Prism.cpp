#include "Prism.hh"
#include <fstream>

using namespace std;

Prism::Prism(std::string filename)
{
    ifstream inputFile;
    inputFile.open(filename);
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

void Prism::draw(string filename) const
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