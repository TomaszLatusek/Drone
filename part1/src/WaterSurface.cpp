#include "WaterSurface.hh"
#include <fstream>


using namespace std;

WaterSurface::WaterSurface()
{
    ifstream inputFile;
    inputFile.open(kModelWater);
    if (!inputFile.is_open())
    {
        cerr << "Unable to load model Surface file!"
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


void WaterSurface::draw(std::string filename) const
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
            if (i % 4 == 3) // triggers after every 4 points
            {
                outputFile << "#\n\n";
            }
        }
}