#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>

#include "gnuplot_link.hh"
#include "Cuboid.hh"
#include "BottomSurface.hh"
#include "WaterSurface.hh"
#include "Scene.hh"


using namespace std;

const string kDroneFile("solid/drone.dat");
const string kBottomFile("solid/bottom.dat");
const string kWaterFile("solid/water.dat");

int main()
{
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;      // nanoseconds, system_clock, seconds
    
    Cuboid cuboid;  
    WaterSurface water;                 
    BottomSurface bottom;
    Scene scene(cuboid,water,bottom);
    PzG::GnuplotLink link;            // Ta zmienna jest potrzebna do wizualizacji
    
    link.Init();
    link.AddFilename(kDroneFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.AddFilename(kWaterFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.AddFilename(kBottomFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.SetDrawingMode(PzG::DM_3D);

    cuboid.draw(kDroneFile);
    water.draw(kWaterFile);
    bottom.draw(kBottomFile);

    link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
    cout << "Press ENTER to continue." << endl;
    cin.ignore(100000, '\n');

    char option;
    double angleZ = 0, angleXY, distance;
    int i = 1;

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
            i--;
        }
        cout << "Your choice> ";
        cin >> option;

        switch (option)
        {
        case 'o':
            cout << "Enter the angle of rotation" << endl
                 << "> ";
            cin >> angleZ;
            for (int i = 0; i < abs(angleZ); i++)
            {
                if(angleZ > 0)
                    {cuboid.rotate(1);}
                else{cuboid.rotate(-1);}
                cuboid.draw(kDroneFile);
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
            for (int i = 0; i < abs(distance); i++)
            {
                
                if(distance > 0)
                    {cuboid.move(angleXY, 1);}
                else{cuboid.move(angleXY, -1);}
                if(!cuboid.position()){
                    cuboid.draw(kDroneFile);
                    link.Draw();
                    sleep_for(milliseconds(5));
                    sleep_until(system_clock::now());
                } else break;
            }
            break;
        case 'm':
            i++;
            break;
        case 'k':
            return 0;
            break;
        default:
            cout << "[!] No such option." << endl;
        }

    } while (option != 'k');

    return 1;
}
