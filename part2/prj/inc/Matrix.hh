#pragma once

#include <iostream>
#include "Vector.hh"
#include <cmath>
#define ERR 0.000000001

///////////////////////////////////////////////////////////////////
////////////////////* Matrix class template *//////////////////////
///////////////////////////////////////////////////////////////////
/**
 * @brief  Squared matrix consisting of vectors (columns) 
 * 
 * @tparam T      matrix data type 
 * @tparam SIZE   matrix size
 */
template <typename T, int SIZE>
class Matrix{
protected:
  Vector<T, SIZE> data[SIZE];

public:
  /* getters overloads */
  const T &operator()(int row, int column) const;
  T &operator()(int row, int column);
  Vector<T, SIZE> &operator[](int index);
  
  T determinant() const;
  Vector<T, SIZE> operator*(Vector<T, SIZE> vec) const;
  Matrix<T, SIZE> hadamard(const Matrix<T, SIZE> &arg) const;
};



///////////////////////////////////////////////////////////////////
////////////////////////////* methods *////////////////////////////
///////////////////////////////////////////////////////////////////
/**
 * @brief Gets specific matrix element
 * 
 * @tparam T        matrix data type
 * @tparam SIZE     matrix size
 * @param row       number of row -1
 * @param column    number of column -1
 * @return const T& value of the element 
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




/**
 * @brief Gets column of a matrix
 * 
 * @tparam T          data type
 * @tparam SIZE       size
 * @param index       number od column -1
 * @return Vector<T, SIZE>&   a column
 */
template <typename T, int SIZE>
Vector<T, SIZE> &Matrix<T, SIZE>::operator[](int index)
{
  return data[index];
}


/**
 * @brief Calculates determinant of the matrix
 * 
 */
using std::abs;
template <typename T, int SIZE>
T Matrix<T, SIZE>::determinant() const
{
  Matrix<T, SIZE> copy = *this;

  T temp1, temp2; //temporary
  int verseSwitch = 1; //determinant change +/-
  T det;      //determinant
  int i, j;

  /* Switching verses when the first element 
      is equal to zero */
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
  /* Elimination */
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
  /* Calculating determinant */
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




/**
 * @brief Matrix and vector multiplication
 * 
 * @tparam T        vector data type
 * @tparam SIZE     vector size
 * @param vec       vector
 * @return Vector<T, SIZE>  result
 */
template <typename T, int SIZE>
Vector<T, SIZE> Matrix<T, SIZE>::operator*(Vector<T, SIZE> vec) const
{
  Vector<T, SIZE> result;

  for (int i = 0; i < SIZE; i++)
  {
    /* makes it equal to 0 */
    result[i] = this->operator()(i, i) - this->operator()(i, i);
    for (int j = 0; j < SIZE; j++)
    {
      result[i] += this->operator()(i, j) * vec[j];
    }
  }

  return result;
}




/**
 * @brief Calculates Hadamard product
 * 
 * @tparam T         matrix data type
 * @tparam SIZE      matrix size
 * @param arg        matrix
 * @return Matrix<T, SIZE>   the Hadamard product
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
////////////////////* iostream overloads */////////////////////////
///////////////////////////////////////////////////////////////////

/**
 * @brief Saves values from input to the matrix
 * 
 * @tparam T        matrix data type
 * @tparam SIZE     matrix size
 * @param stream    input stream
 * @param matrix    the matrix
 * @return std::istream& 
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

/**
 * @brief Writes the matrix to output stream
 * 
 * @tparam T        matrix data type
 * @tparam SIZE     matrix size
 * @param stream    output stream
 * @param matrix    the matrix
 * @return std::ostream& 
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