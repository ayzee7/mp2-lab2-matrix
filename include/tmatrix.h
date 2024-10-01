// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>
#include <exception>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
      if (sz == 0)
          throw out_of_range("Vector size should be greater than zero");
      if (sz > MAX_VECTOR_SIZE)
          throw out_of_range("Exceeded maximum vector size");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      sz = v.sz;
      pMem = new T[sz];
      memcpy(pMem, v.pMem, sz);
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      v.sz = 0;
      pMem = v.pMem;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (&v != this) {
          sz = v.sz;
          delete[] pMem;
          pMem = new T[sz];
          for (int i = 0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (&v != this) {
          pMem = v.pMem;
          v.pMem = nullptr;
          sz = v.sz;
          v.sz = 0;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < 0 || ind >= sz) {
          throw exception("Out of bounds index");
      }
      return pMem[ind];
  }
  const T& at(size_t ind) const
  {
      if (ind < 0 || ind >= sz) {
          throw exception("Out of bounds index");
      }
      return pMem[ind];
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      int cmpres = memcmp(pMem, v.pMem, sz);
      if (sz != v.sz) {
          return false;
      }
      else if (cmpres) {
          return false;
      }
      else {
          return true;
      }
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      int cmpres = memcmp(pMem, v.pMem, sz);
      if (sz != v.sz) {
          return true;
      }
      else if (cmpres) {
          return true;
      }
      else {
          return false;
      }
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] + val;
      }
      return res;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] - val;
      }
      return res;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] * val;
      }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw exception("Invalid vector size");
      }
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] + v.pMem[i];
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz) {
          throw exception("Invalid vector size");
      }
      TDynamicVector res(sz);
      for (int i = 0; i < sz; i++) {
          res[i] = pMem[i] - v.pMem[i];
      }
      return res;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz) {
          throw exception("Invalid vector size");
      }
      T res = 0;
      for (int i = 0; i < sz; i++) {
          res += pMem[i] * v.pMem[i];
      }
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
  }

  // матрично-скалярные операции
  TDynamicVector<T> operator*(const T& val)
  {
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
  }
};

#endif
