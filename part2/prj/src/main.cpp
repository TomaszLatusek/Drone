#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include "gnuplot_link.hh"
#include "Scene.hh"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono;      // nanoseconds, system_clock, seconds

int main()
{
    Scene* scene = new Scene; 
    PzG::GnuplotLink link;        // Variable needed for vizualization
    
    // gnuplot stuff
    link.Init();
    link.AddFilename(kDroneFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.AddFilename(kWaterFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.AddFilename(kBottomFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.AddFilename(kCuboidFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.AddFilename(kPoleFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.AddFilename(kRectangleFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.SetDrawingMode(PzG::DM_3D);

    //drawing time
    scene->initObstacles();
    scene->draw();

    link.Draw(); // <- Here gnuplot draws what we saved to file
    cout << "Press ENTER to continue." << endl;
    cin.ignore(100000, '\n');

    char option;
    double angleZ = 0, angleXY, distance;
    int i = 1; // =1 to show menu in the first "do while" loop

    do
    {
        if (i) 
        {
            cout << endl
                 << "r - movement" << endl
                 << "o - rotation" << endl
                 << "m - menu" << endl
                 << endl
                 << "k - exit" << endl
                 << endl;
            i--;    // doesn't show menu unless "m" is chosen
        }
        cout << "Your choice> ";
        cin >> option;

        switch (option)
        {
        case 'o':
            cout << "Enter the angle of rotation" << endl
                 << "> ";
            cin >> angleZ;
            // animation part
            for (int i = 0; i < abs(angleZ); i++)
            {
                if(angleZ > 0)
                    {scene->rotateDrone(1);}
                else{scene->rotateDrone(-1);}
                scene->drawDrone();
                link.Draw();
                sleep_for(milliseconds(5));
                sleep_until(system_clock::now());
            }
            break;
        case 'r':
            cout << "Enter the angle of movement (up/down)" << endl
                 << "> ";
            cin >> angleXY;
            cout << "Enter the distance" << endl
                 << "> ";
            cin >> distance;
            // animation part
            for (int i = 0; i < abs(distance); i++)
            {
                if(distance > 0)
                    {scene->moveDrone(angleXY, 1);}
                else{scene->moveDrone(angleXY, -1);}
                // checking the height
                if(!scene->dronePosition()){
                    scene->drawDrone();
                    link.Draw();
                    sleep_for(milliseconds(5));
                    sleep_until(system_clock::now());
                } else break;
            }
            break;
        case 'm': // shows menu again
            i++;
            break;
        case 'k': // exits
            delete scene;
            break;
        default:
            cout << "[!] No such option." << endl;
        }

        cout << "Number of current Vector3D objects: " << Shape::counterCurrent << endl;
        cout << "Number of Vector3D objects in total: " << Shape::counterTotal << endl
        << endl;
    } while (option != 'k');

    return 1;
}
