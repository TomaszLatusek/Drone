#pragma once

#include <iostream>
///////////////////////////////////////////////////////////////////
///////////////////* Vector class template *///////////////////////
///////////////////////////////////////////////////////////////////
/**
 * @brief Vector representation 
 * 
 * @tparam T      vector data type
 * @tparam SIZE   vector size
 */
template <typename T, int SIZE>
class Vector{
  T coordinates[SIZE];
public:
/* getters overloads */
  const T &operator[](int index) const;
  T &operator[](int index);
/* operation overloads */
  Vector<T, SIZE> operator+(Vector<T, SIZE> vec2) const;
  Vector<T, SIZE> operator-(Vector<T, SIZE> vec2) const;
  Vector<T, SIZE> operator-(T arg) const;
  T operator*(Vector<T, SIZE> vec2) const;
  Vector<T, SIZE> operator*(T arg);
  Vector<T, SIZE> operator/(T arg) const;
  Vector<T,SIZE> operator+=(T arg);
};





///////////////////////////////////////////////////////////////////
////////////////////////////* methods *////////////////////////////
///////////////////////////////////////////////////////////////////
/**
 * @brief Gets specific vector element 
 *        (const version)
 * 
 * @tparam T        vector data type
 * @tparam SIZE     vector size
 * @param index     number of element -1
 * @return const T& value of the element 
 */
template <typename T, int SIZE>
const T &Vector<T, SIZE>::operator[](int index) const
{
  if (index < 0 || index >= SIZE)
  {
    std::cerr << "Warning! Vector index out of range" << std::endl;
  }
  return coordinates[index];
}

/**
 * @brief Gets specific vector element 
 *        (non-const version)
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param index      number of element -1
 * @return T&        value of the element 
 */
template <typename T, int SIZE>
T &Vector<T, SIZE>::operator[](int index)
{
  return const_cast<T &>(const_cast<const Vector<T, SIZE> *>(this)->operator[](index));
}




/**
 * @brief Vector addition
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param vec2       vector
 * @return Vector<T, SIZE> summary 
 */
template <typename T, int SIZE>
Vector<T, SIZE> Vector<T, SIZE>::operator+(Vector<T, SIZE> vec2) const
{
  for (int i = 0; i < SIZE; i++)
  {
    vec2[i] += coordinates[i];
  }

  return vec2;
}




/**
 * @brief Vector subtraction
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param vec2        vector
 * @return Vector<T, SIZE>  difference
 */
template <typename T, int SIZE> 
Vector<T, SIZE> Vector<T, SIZE>::operator-(Vector<T, SIZE> vec2) const
{
  for (int i = 0; i < SIZE; i++)
  {
    vec2[i] -= coordinates[i];
    vec2[i] *= -1;
  }

  return vec2;
}



/**
 * @brief Normal subtraction
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param vec2        vector
 * @return Vector<T, SIZE>  difference
 */
template <typename T, int SIZE> 
Vector<T, SIZE> Vector<T, SIZE>::operator-(T arg) const
{
  Vector<T, SIZE> result;
  for (int i = 0; i < SIZE; i++)
  {
    result[i] = coordinates[i] - arg;
  }

  return result;
}


/**
 * @brief Scalar multiplication
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param vec2        vector
 * @return T          scalar product
 */
template <typename T, int SIZE>
T Vector<T, SIZE>::operator*(Vector<T, SIZE> vec2) const
{
  T result = 0;

  for (int i = 0; i < SIZE; i++)
  {
    result += coordinates[i] * vec2[i];
  }

  return result;
}




/**
 * @brief Multiplying the vector by the number
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param arg        the number
 * @return Vector<T, SIZE>  result
 */
template <typename T, int SIZE>
Vector<T, SIZE> Vector<T, SIZE>::operator*(T arg)
{
  Vector<T, SIZE> result;

  for (int i = 0; i < SIZE; i++)
  {
    result[i] = coordinates[i] * arg;
  }

  return result;
}




/**
 * @brief Dividing a vector by a number
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param arg        the number (can't be 0!)
 * @return Vector<T, SIZE>  result
 */
template <typename T, int SIZE>
Vector<T, SIZE> Vector<T, SIZE>::operator/(T arg) const
{
  Vector<T, SIZE> result;

  if (arg == 0.0)
  {
    std::cerr << "[!] Cannot divide by zero." << std::endl;
    arg = 1;
  }

  for (int i = 0; i < SIZE; i++)
  {
    result[i] = coordinates[i] / arg;
  }

  return result;
}



/**
 * @brief += overload
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param arg        the number
 * @return Vector<T,SIZE> summary 
 */
template <typename T, int SIZE>
Vector<T,SIZE> Vector<T,SIZE>::operator+=(T arg)
{
  for(int i = 0; i < SIZE; i++)
  {
    coordinates[i] += arg[i];
  }
  return this;
}



///////////////////////////////////////////////////////////////////
////////////////////* iostream overloads */////////////////////////
///////////////////////////////////////////////////////////////////
/**
 * @brief Saves values from input to the vector
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param stream     input stream
 * @param vec        the vector
 * @return std::istream& 
 */
template <typename T, int SIZE>
std::istream &operator>>(std::istream &stream, Vector<T, SIZE> &vec)
{
  for (int i = 0; i < SIZE; i++)
  {
    stream >> vec[i];
  }

  return stream;
}



/* Realizuje wyswietlnie wspolrzednych wektora na ekranie.
 * Argumenty:
 *    stream - output stream,
 *    vec - wektor.
 * Uwaga:
 *    wartosci wspolrzednych wektora (vec.coordinates[])
 *    moga byc tylko liczbami
 */

/**
 * @brief Writes the vector to output stream
 * 
 * @tparam T         vector data type
 * @tparam SIZE      vector size
 * @param stream     output stream
 * @param vec        the vector
 * @return std::ostream& 
 */
template <typename T, int SIZE>
std::ostream &operator<<(std::ostream &stream, const Vector<T, SIZE> &vec)
{
  for (int i = 0; i < SIZE; i++)
  {
    stream << vec[i] << " ";
  }

  return stream;
}

/**
 * @brief Vector3D alias 
 * 
 */
using Vector3D = Vector<double,3>;



