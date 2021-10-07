// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <exception>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize() const { return Size; } // размер вектора
  int GetStartIndex() const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  const ValType& operator[](int pos) const;
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val) const;   // прибавить скаляр
  TVector  operator-(const ValType &val) const;   // вычесть скаляр
  TVector  operator*(const ValType &val) const;   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v) const;     // сложение
  TVector  operator-(const TVector &v) const;     // вычитание
  ValType  operator*(const TVector &v) const;     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
	  for (int i = 0; i < v.Size; i++)
		  in >> v.pVector[i];
	  return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	  for (int i = 0; i < v.GetStartIndex(); ++i)
	  {
		  out << '\t';
	  }
	  for (int i = 0; i < v.Size; i++)
		  out << v.pVector[i] << '\t';
	  return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
	: Size(s), StartIndex(si)
{
	if (Size <= 0 || Size > MAX_VECTOR_SIZE)
	{
		throw std::runtime_error("Invalid size for vector");
	}
	if (StartIndex < 0)
	{
		throw std::runtime_error("Invalid start index");
	}
	pVector = new ValType[Size];
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
	: Size(v.Size), StartIndex(v.StartIndex)
{
	pVector = new ValType[Size];
	for (int i = 0; i < Size; ++i)
	{
		pVector[i] = v.pVector[i];
	}
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	pos -= StartIndex;
	if (pos < 0 || pos >= Size)
	{
		throw std::runtime_error("Invalid index in operator[]");
	}
	return pVector[pos];
} /*-------------------------------------------------------------------------*/

template<class ValType>
const ValType & TVector<ValType>::operator[](int pos) const
{
	return const_cast<const ValType&>(const_cast<TVector<ValType>&>(*this)[pos]);
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size || StartIndex != v.StartIndex)
	{
		return false;
	}
	for (int i = 0; i < Size; ++i)
	{
		if (pVector[i] != v.pVector[i])
		{
			return false;
		}
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v)
	{
		if (Size != v.Size)
		{
			Size = v.Size;
			delete[] pVector;
			pVector = new ValType[Size];
		}
		for (int i = 0; i < Size; ++i)
		{
			pVector[i] = v.pVector[i];
		}
		StartIndex = v.StartIndex;
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val) const
{
	TVector<ValType> aResult = *this;
	for (int i = 0; i < GetSize(); ++i)
	{
		aResult.pVector[i] += val;
	}
	return aResult;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val) const
{
	TVector<ValType> aResult = *this;
	for (int i = 0; i < GetSize(); ++i)
	{
		aResult.pVector[i] -= val;
	}
	return aResult;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val) const
{
	TVector<ValType> aResult = *this;
	for (int i = 0; i < GetSize(); ++i)
	{
		aResult.pVector[i] *= val;
	}
	return aResult;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v) const
{
	if (GetSize() != v.GetSize())
	{
		throw std::runtime_error("Can't add vector with different size");
	}
	TVector<ValType> aResult = *this;
	for (int i = 0; i < GetSize(); ++i)
	{
		aResult.pVector[i] += v[i];
	}
	return aResult;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v) const
{
	if (GetSize() != v.GetSize())
	{
		throw std::runtime_error("Can't substract vector with different size");
	}
	TVector<ValType> aResult = *this;
	for (int i = 0; i < GetSize(); ++i)
	{
		aResult.pVector[i] -= v[i];
	}
	return aResult;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v) const
{
	if (GetSize() != v.GetSize())
	{
		throw std::runtime_error("Can't find dot product for vector with different size");
	}
	ValType aResult = 0;
	for (int i = 0; i < GetSize(); ++i)
	{
		aResult += pVector[i] * v.pVector[i];
	}
	return aResult;
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
	  for (int i = 0; i < mt.Size; i++)
		  in >> mt.pVector[i];
	  return in;
  }
  friend ostream & operator<<(ostream &out, const TMatrix &mt)
  {
	  for (int i = 0; i < mt.Size; i++)
		  out << mt.pVector[i] << endl;
	  return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s)
	: TVector<TVector<ValType>>(s)
{
	if (Size < 0 || Size >= MAX_MATRIX_SIZE)
	{
		throw std::runtime_error("Invalid size for matrix");
	}
	for (int i = 0; i < GetSize(); ++i)
	{
		pVector[i] = TVector<ValType>(s - i, i);
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt)
  : TMatrix((const TVector<TVector<ValType>>&)mt)
{
}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt)
	: TVector<TVector<ValType> >(mt.GetSize())
{
	if (Size < 0 || Size >= MAX_MATRIX_SIZE)
	{
		throw std::runtime_error("Invalid size for matrix");
	}
	for (int i = 0; i < GetSize(); ++i)
	{
		(*this)[i] = mt[i];
	}
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (GetSize() != mt.GetSize() || StartIndex != mt.StartIndex)
	{
		return false;
	}

	for (int i = 0; i < GetSize(); ++i)
	{
		if (pVector[i].GetSize() != mt.pVector[i].GetSize() || pVector[i].GetStartIndex() != mt.pVector[i].GetStartIndex())
		{
			return false;
		}
		for (int j = i; j < pVector[i].GetSize(); ++j)
		{
			if (pVector[i][j] != mt.pVector[i][j])
			{
				return false;
			}
		}
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !(*this == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this != &mt)
	{
		*((TVector<TVector<ValType> >*)this) = *((const TVector<TVector<ValType> >*)&mt);
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (GetSize() != mt.GetSize())
	{
		throw std::runtime_error("Can't add matrix with different size");
	}
	TMatrix<ValType> aResult = *this;
	for (int i = 0; i < GetSize(); ++i)
	{
		for (int j = i; j < GetSize(); ++j)
		{
			aResult[i][j] += mt[i][j];
		}
	}
	return aResult;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (GetSize() != mt.GetSize())
	{
		throw std::runtime_error("Can't substract matrix with different size");
	}
	TMatrix<ValType> aResult = *this;
	for (int i = 0; i < GetSize(); ++i)
	{
		for (int j = i; j < GetSize(); ++j)
		{
			aResult[i][j] -= mt[i][j];
		}
	}
	return aResult;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
