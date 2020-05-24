#include "BottomSurface.hh"
#include <fstream>

using namespace std;

/**
 * @brief Construct a new Bottom Surface:: Bottom Surface object
 * 
 * Initializes points with values from solid/bottomRead.dat
 * Simple zigzag pattern
 */
BottomSurface::BottomSurface()
{
    ifstream inputFile;
    inputFile.open(kModelBottom);
    if (!inputFile.is_open())
    {
        cerr << "Unable to load model Bottom file!"
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

/**
 * @brief Destroy the Bottom Surface:: Bottom Surface object
 * 
 */
BottomSurface::~BottomSurface()
{
    int z = points.size();
    for (int i = 0; i < z; i++)
    {
        points.pop_back();
        counterCurrent--;
    }
}

/**
 * @brief Saves points values to a new file which gnuplot can use
 * 
 * @param filename name of the file you want gnuplot to draw from
 */
void BottomSurface::draw(std::string filename) const
{
    ofstream outputFile;
    outputFile.open(filename);
    if (!outputFile.is_open())
    {
        cerr << "Unable to open Bottom file!" << endl;
        return;
    }

    for (unsigned i = 0; i < points.size(); ++i)
    {
        outputFile << points[i] << endl;
        counterTotal++;
    }
}
