#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "Vector2D.hh"
#include "Matrix2x2.hh"
#include "Rectangle.hh"
#include "gnuplot_link.hh"



using namespace std;

/*
 * Tu definiujemy pozostale funkcje.
 * Lepiej jednak stworzyc dodatkowy modul
 * i tam je umiescic. Ten przyklad pokazuje
 * jedynie absolutne minimum.
 */


const int kShorterEdgesLength = 100;
const int kLongerEdgesLength = 150;





/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do strumienia wyjściowego.
 * Dane sa odpowiednio sformatowane, tzn. przyjęto notację stałoprzecinkową
 * z dokładnością do 10 miejsca po przecinku. Szerokość wyświetlanego pola 
 * to 16 miejsc, sposób wyrównywania - do prawej strony.
 * \param[in] output_stream - strumien wyjsciowy, do ktorego maja zostac 
 *                            zapisane kolejne wspolrzedne.
 * \param[in] offset - ten parameter jest tylko po to, aby pokazać
 *                     mozliwosc zmiany wspolrzednych i prostokata
 *                     i zmiane jego polorzenia na okienku graficznym
 *                     rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
void WriteToStreamExample(ostream& output_stream, double offset)
{
   //---------------------------------------------------------------
   // To tylko przyklad !!!
   // W programie nalezy uzywać pojęcia wektora, a nie oddzielnych 
   // zmiennych do reprezentowania wspolrzednych!
   //
  double  x1, y1, x2, y2, x3, y3, x4, y4; 

  x1 = y1 = 10;
  x2 = x1 + kLongerEdgesLength;  y2 = y1;
  x3 = x2;  y3 = y2 + kShorterEdgesLength;
  x4 = x3 - kLongerEdgesLength; y4 = y3;


  output_stream << setw(16) << fixed << setprecision(10) << x1+offset 
         << setw(16) << fixed << setprecision(10) << y1+offset << endl;
  output_stream << setw(16) << fixed << setprecision(10) << x2+offset 
         << setw(16) << fixed << setprecision(10) << y2+offset << endl;
  output_stream << setw(16) << fixed << setprecision(10) << x3+offset 
         << setw(16) << fixed << setprecision(10) << y3+offset << endl;
  output_stream << setw(16) << fixed << setprecision(10) << x4+offset 
         << setw(16) << fixed << setprecision(10) << y4+offset << endl;
  output_stream << setw(16) << fixed << setprecision(10) << x1+offset 
         << setw(16) << fixed << setprecision(10) << y1+offset << endl; 
                             // Jeszcze raz zapisujemy pierwszy punkt,
                             // aby gnuplot narysowal zamkniętą linię.
}



/*!
 * Przyklad zapisu wspolrzednych zbioru punktow do pliku, z ktorego
 * dane odczyta program gnuplot i narysuje je w swoim oknie graficznym.
 * \param[in] filename - nazwa pliku, do którego zostana zapisane
 *                       wspolrzędne punktów.
 * \param[in] offset - ten parameter jest tylko po to, aby pokazać
 *                     mozliwosc zmiany wspolrzednych i prostokata
 *                     i zmiane jego polorzenia na okienku graficznym
 *                     rysownym przez gnuplota.
 * \retval true - gdy operacja zapisu powiodła się,
 * \retval false - w przypadku przeciwnym.
 */
bool WriteToFileExample(string filename, double offset)
{
  ofstream  file_stream;

  file_stream.open(filename);
  if (!file_stream.is_open())  {
    cerr << ":(  Operacja otwarcia do zapisu \"" << filename << "\"" << endl
	 << ":(  nie powiodla sie." << endl;
    return false;
  }

  WriteToStreamExample(file_stream,offset);

  file_stream.close();
  return !file_stream.fail();
}



int main()
{
  Rectangle         rect;   // To tylko przykladowe definicje zmiennej
  PzG::GnuplotLink  link;  // Ta zmienna jest potrzebna do wizualizacji
                                // rysunku prostokata

   //-------------------------------------------------------
   //  Wspolrzedne wierzcholkow beda zapisywane w pliku "prostokat.dat"
   //  Ponizsze metody powoduja, ze dane z pliku beda wizualizowane
   //  na dwa sposoby:
   //   1. Rysowane jako linia ciagl o grubosci 2 piksele
   //
  link.AddFilename("prostokat.dat",PzG::LS_CONTINUOUS,2);
   //
   //   2. Rysowane jako zbior punktow reprezentowanych przez kwadraty,
   //      których połowa długości boku wynosi 2.
   //
  link.AddFilename("prostokat.dat",PzG::LS_SCATTERED,2);
   //
   //  Ustawienie trybu rysowania 2D, tzn. rysowany zbiór punktów
   //  znajduje się na wspólnej płaszczyźnie. Z tego powodu powoduj
   //  jako wspolrzedne punktow podajemy tylko x,y.
   //
  link.SetDrawingMode(PzG::DM_2D);

  
  WriteToStreamExample(cout,0);
  if (!WriteToFileExample("prostokat.dat",0)) return 1;
  link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  cout << "Naciśnij ENTER, aby kontynuowac" << endl;
  cin.ignore(100000,'\n');

   //----------------------------------------------------------
   // Ponownie wypisuje wspolrzedne i rysuje prostokąt w innym miejscu.
   //
  WriteToStreamExample(cout,50);
  if (!WriteToFileExample("prostokat.dat",50)) return 1;
  link.Draw(); // <- Tutaj gnuplot rysuje, to co zapisaliśmy do pliku
  cout << "Naciśnij ENTER, aby kontynuowac" << endl;
  cin.ignore(100000,'\n');
}
