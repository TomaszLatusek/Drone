#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "gnuplot_link.hh"
#include "cuboid.hh"

using namespace std;


const string kDroneFile("solid/drone.dat");

int main()
{
    Cuboid cuboid;        // To tylko przykladowe definicje zmiennej
    PzG::GnuplotLink link; // Ta zmienna jest potrzebna do wizualizacji

    link.Init();
    link.AddFilename(kDroneFile.c_str(), PzG::LS_CONTINUOUS, 1);
    link.SetDrawingMode(PzG::DM_3D);

    cuboid.draw(kDroneFile);


    link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
    cout << "Naciśnij ENTER, aby kontynuowac" << endl;
    cin.ignore(100000, '\n');


    Vector3D translation;
    translation[0] = 50;
    translation[1] = 50;
    translation[2] = 50;

    cuboid.rotate(45);
    cuboid.translate(translation);
    cuboid.draw(kDroneFile);


    link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
    cout << "Naciśnij ENTER, aby kontynuowac" << endl;
    cin.ignore(100000, '\n'); 
}
