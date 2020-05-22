#include "Rectangle.hh"
#include <fstream>

using namespace std;

Rectangle::Rectangle()
{
    ifstream inputFile;
    inputFile.open(kModelRectangle);
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

Rectangle::~Rectangle()
{
    for (int i = 0; i < points.size(); i++)
    {
        points.pop_back();
        counterCurrent--;
    }
}


void Rectangle::draw(string filename) const
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


bool Rectangle::checkCollision(const Drone &drone) const
{
    double maxXob, maxYob, maxZob;
           maxXob = maxYob = maxZob = 0;
    double minXob, minYob, minZob;
           minXob = minYob = minZob = 500;

    for (int i = 0; i < points.size(); i++)
    {
        if(maxXob < points[i][0]){
            maxXob = points[i][0];
        }
        if(maxYob < points[i][1]){
            maxYob = points[i][1];
        }
        if(maxZob < points[i][2]){
            maxZob = points[i][2];
        }
        if(minXob > points[i][0]){
            minXob = points[i][0];
        }
        if(minYob > points[i][1]){
            minYob = points[i][1];
        }
        if(minZob > points[i][2]){
            minZob = points[i][2];
        }
    }

    double maxXdr, maxYdr, maxZdr;
        maxXdr = maxYdr = maxZdr = 0;
    double minXdr, minYdr, minZdr;
        minXdr = minYdr = minZdr = 500;

    for (int i = 0; i < 8; i++)
    {
        double X = drone.contour->getVector(i)[0];
        double Y = drone.contour->getVector(i)[1];
        double Z = drone.contour->getVector(i)[2];
        
        if(maxXdr < X){
            maxXdr = X;
        }
        if(maxYdr < Y){
            maxYdr = Y;
        }
        if(maxZdr < Z){
            maxZdr = Z;
        }
        if(minXdr > X){
            minXdr = X;
        }
        if(minYdr > Y){
            minYdr = Y;
        }
        if(minZdr > Z){
            minZdr = Z;
        }
    }

    for(int i = 0; i < 8; i++){
        double X = drone.contour->getVector(i)[0];
        double Y = drone.contour->getVector(i)[1];
        double Z = drone.contour->getVector(i)[2];
        if(X < maxXdr && X > minXob &&
           Y < maxYdr && Y > minYob &&
           Z < maxZdr && Z > minZob){
               cerr << "[!]Collision detected." << endl;
               return 1;
        }
    }

    return 0;
}