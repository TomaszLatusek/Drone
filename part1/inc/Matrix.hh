#pragma once

#include <iostream>
#include "Vector.hh"
#include <cmath>
#define ERR 0.000000001

///////////////////////////////////////////////////////////////////
///////////////* Szablon klasy dla macierzy *//////////////////////
///////////////////////////////////////////////////////////////////
template <typename T, int SIZE>
class Matrix
{
  /* macierz kwadratowa przedstawiona w postaci tablicy wektorow (kolumn)
   * SIZE wektorow SIZE-wymiarowych*/
  Vector<T, SIZE> data[SIZE];

public:
  Matrix(char axis, double angle);
  /* przeciazenia nawiasow do indeksowania */
  const T &operator()(int row, int column) const;
  T &operator()(int row, int column);
  /* do wyciagania kolumn macierzy */
  Vector<T, SIZE> &operator[](int index);
  /* obliczanie wyznacznika macierzy */
  T determinant() const;
  /* mnozenie macierzy przez wektor */
  Vector<T, SIZE> operator*(Vector<T, SIZE> vec) const;
  /* Hadamard */
  Matrix<T, SIZE> hadamard(const Matrix<T, SIZE> &arg) const;
};



///////////////////////////////////////////////////////////////////
////////////////////////* ciala metod *////////////////////////////
///////////////////////////////////////////////////////////////////
template <typename T, int SIZE>
Matrix<T,SIZE>::Matrix(char axis, double angle)
{
  switch(axis){
    case 'z':
    data[0][0] = cos(angle);
    data[0][1] = sin(angle);
    data[0][2] = 0;
    data[1][0] = -sin(angle);
    data[1][1] = cos(angle);
    data[1][2] = 0;
    data[2][0] = 0;
    data[2][1] = 0;
    data[2][2] = 1;
    break;
    case 'x':
    data[0][0] = 1;
    data[0][1] = 0;
    data[0][2] = 0;
    data[1][0] = 0;
    data[1][1] = cos(angle);
    data[1][2] = sin(angle);
    data[2][0] = 0;
    data[2][1] = -sin(angle);
    data[2][2] = cos(angle);
    break;
  }
}


/* Operator indeksowania macierzy.
 * Argumenty:
 *      row - nr wiersza - 1,
 *      column - nr kolumn - 1.
 * Zwraca:
 *      wartosc danego wyrazu macierzy
 * 
 * Wersja const
 */
template <typename T, int SIZE>
const T &Matrix<T, SIZE>::operator()(int row, int column) const
{
  if (row < 0 || row >= SIZE || column < 0 || column >= SIZE)
  {
    std::cerr << "Warning! Matrix index out of range" << std::endl;
  }
  return data[column][row];
}
/*  Wersja nie-const */
template <typename T, int SIZE>
T &Matrix<T, SIZE>::operator()(int row, int column)
{
  return const_cast<T &>(const_cast<const Matrix<T, SIZE> *>(this)->operator()(row, column));
}



/* Operator indeksowania kolumn macierzy.
 * Argumenty:
 *      index - nr kolumny -1.
 * Zwraca:
 *      wektor kolumny macierzy
 */
template <typename T, int SIZE>
Vector<T, SIZE> &Matrix<T, SIZE>::operator[](int index)
{
  return data[index];
}



/* Realizuje obliczanie wyznacznika macierzy.
 * Argumenty:
 *    w domysle macierz
 * Zwraca:
 *    wyznacznik macierzy
 */using std::abs;
template <typename T, int SIZE>
T Matrix<T, SIZE>::determinant() const
{
  Matrix<T, SIZE> copy = *this;

  T temp1, temp2; //pomocnicze
  int verseSwitch = 1; //zmiana znaku wyznacznika
  T det;      //wyznacznik
  int i, j;

  /* Zamiana wierszy w przypadku,
     * gdy pierwszy element jest zerem */
  if (abs(copy(0, 0)) < ERR)
  {
    for (i = 0; i < SIZE; i++)
    {
      if (abs(copy(i, 0)) > ERR)
      {
        verseSwitch *= -1;
        for (j = 0; j < SIZE; j++)
        {
          temp1 = copy(i, j);
          temp2 = copy(0, j);
          copy(0, j) = temp1;
          copy(i, j) = temp2;
        }
      }
    }
  }
  /* Wlasciwa eliminacja */
  for (i = j = 0; i < SIZE - 1 && j < SIZE - 1; i++, j++)
  {
    for (int m = i + 1; m < SIZE; m++)
    {
      for (int n = SIZE - 1; n >= j; n--)
      {
        copy(m, n) -= (copy(m, j) / copy(i, j) * copy(i, n));
      }
    }
  }
  /* Obliczzenie wyznacznika */
  det = copy(0,0);

  for (i = j = 1; i < SIZE && j < SIZE; i++, j++)
  {
    det *= copy(i, j);
  }

  if(!verseSwitch)
  {
    det *= -1;
  }

  return det;
}



/* Realizuje mnozenie macierzy przez wektor.
 * Argumenty:
 *    niejawny wskaznik na klase Matrix - pierwszy skladnik mnozenia,
 *    vec - wektor, drugi skladnik mnozenia.
 * Zwraca:
 *    result - wektor wynikowy.
 */
template <typename T, int SIZE>
Vector<T, SIZE> Matrix<T, SIZE>::operator*(Vector<T, SIZE> vec) const
{
  Vector<T, SIZE> result;

  for (int i = 0; i < SIZE; i++)
  {
    /* wyzerowanie */
    result[i] = this->operator()(i, i) - this->operator()(i, i);
    for (int j = 0; j < SIZE; j++)
    {
      result[i] += this->operator()(i, j) * vec[j];
    }
  }

  return result;
}



/* Realizuje mnozenie Hadamarda.
 * Argumenty:
 *    niejawny wskaznik na klase Matrix - pierwszy skladnik mnozenia,
 *    arg - macierz, drugi skladnik mnozenia.
 * Zwraca:
 *    result - macierz wynikowa.
 */
template <typename T, int SIZE>
Matrix<T, SIZE> Matrix<T, SIZE>::hadamard(const Matrix<T, SIZE> &arg) const
{
  Matrix<T, SIZE> result;

  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      result(i, j) = operator()(i, j) * arg(i, j);
    }
  }
  return result;
}



///////////////////////////////////////////////////////////////////
///////////* przeciazenia operatorow "strumieniowych" *////////////
///////////////////////////////////////////////////////////////////

/* Realizuje wczytywanie wartosci wyrazow macierzy
 * ze standardowego wejscia.
 * Argumenty:
 *    stream - input stream,
 *    matrix - macierz.
 * Uwaga:
 *    na wejscie nalezy podac postac transponowana macierzy
 */
template <typename T, int SIZE>
std::istream &operator>>(std::istream &stream, Matrix<T, SIZE> &matrix)
{
  for (int i = 0; i < SIZE; i++)
  {
    stream >> matrix[i];
  }
  return stream;
}

/* Realizuje wyswietlnie macierzy na ekranie.
 * Argumenty:
 *    stream - output stream,
 *    matrix - macierz.
 * Uwaga:
 *    wyswietla macierz oryginalna, nie transponowana 
 *    jak ta podana na wejsiu.
 */
template <typename T, int SIZE>
std::ostream &operator<<(std::ostream &stream, const Matrix<T, SIZE> &matrix)
{
  for (int i = 0; i < SIZE; i++)
  {
    stream << "     ";
    for (int j = 0; j < SIZE; j++)
    {
      stream << matrix(i, j) << " ";
    }
    stream << std::endl;
  }

  return stream;
}