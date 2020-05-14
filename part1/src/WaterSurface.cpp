#include "WaterSurface.hh"
#include <fstream>


using namespace std;

/**
 * @brief Construct a new Water Surface:: Water Surface object
 * 
 * Initializes points with values from solid/bottomRead.dat
 * Simple zigzag pattern
 */
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
        counter++;
    }
    inputFile.close();
}


/**
 * @brief Saves points values to a new file which gnuplot can use
 * 
 * @param filename name of the file you want gnuplot to draw from
 */
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
        }
}
