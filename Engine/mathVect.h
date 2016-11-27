#pragma once
#include <vector>

enum VectorOrientation : bool
{
	horizontal = true,
	vertical = false
};

template<typename T> class mathVect
{
public:
	//Constructors
	mathVect()
	{
		size = 3;
		elements.resize(size);
		orientation = vertical;
	}
	mathVect(const std::vector<T> &inV, VectorOrientation orientation)
	{
		size = inV.size();
		elements.resize(size);
		elements = inV;
		this->orientation = orientation;
	}
	
	//Vector operations
	void Transpose()
	{
		orientation = !orientation;
	}
	//Methods
	void SetElements(const std::vector<T> &inV)
	{
		size = inV.size();
		elements.resize(size);
		elements = inV;
	}


	//Information retrieval
	const int Size()
	{
		return size;
	}
	const VectorOrientation Orientation()
	{
		return orientation;
	}
	const float Length()
	{
		return (float)sqrt((*this)*(*this));
	}
	//Operators
	T& operator()(int index)
	{
		return elements[index];
	}
	mathVect<T> operator+(mathVect<T> &vectB)
	{
		mathVect<T> result;
		if (size != vectB.Size() ||vectB.Orientation() != orientation )
		{
			return result;
		}
		
		int i;
		for (i = 0; i < size; i++)
		{
			result(i) = elements[i] + vectB(i);
		}
		
		return result;
	}
	mathVect<T> operator-(mathVect<T> &vectB)
	{
		mathVect<T> result;
		if (size != vectB.Size() || vectB.Orientation() != orientation)
		{
			return result;
		}

		int i;
		for (i = 0; i < size; i++)
		{
			result(i) = elements[i] - vectB(i);
		}

		return result;
	}
	void operator+=(mathVect<T> &vectB)
	{
		if (size != vectB.Size() || vectB.Orientation() != orientation)
		{
			return;
		}

		int i;
		for (i = 0; i < size; i++)
		{
			elements[i] += vectB(i);
		}

		return;
	}
	void operator-=(mathVect<T> &vectB)
	{
		if (size != vectB.Size() || vectB.Orientation() != orientation)
		{
			return;
		}

		int i;
		for (i = 0; i < size; i++)
		{
			elements[i] -= vectB(i);
		}

		return;
	}
	T operator*(mathVect<T> &vectB)
	{
		if (size != vectB.Size())
			return (T)0;
		int i;
		T result = 0;
		for (i = 0; i < size; i++)
		{
			result += elements[i] * vectB(i);
		}
		return result;
	}
	mathVect<T> operator*(T scalar)
	{
		int i;
		mathVect<T> result;
		for (i = 0; i < size; i++)
		{
			result(i) = elements[i] * scalar;
		}
		return result;
	}
	void operator=(mathVect<T> &vectB)
	{
		size = vectB.Size();
		int i;
		for (i = 0; i < size; i++)
		{
			elements[i] = vectB(i);
		}
	}
	void operator=(std::vector<T> &vectB)
	{
		size = vectB.Size();
		int i;
		for (i = 0; i < size; i++)
		{
			elements(i) = vectB(i);
		}
	}
	//Data
private:
	std::vector<T> elements;
	int size;
	VectorOrientation orientation;
};

template<typename T> class gMatrix
{
public :
	gMatrix()
	{
		width = 3;
		height = 3;
		rowVectors.resize(width);
		rowVectors.resize(height);
		rowVectors[0](0) = (T)17; rowVectors[0](1) = (T)6; rowVectors[0](2) = (T)543;
		rowVectors[1](0) = (T)-9; rowVectors[1](1) = (T)65; rowVectors[1](2) = (T)432;
		rowVectors[2](0) = (T)-77; rowVectors[2](1) = (T)-453; rowVectors[2](2) = (T)33.4;
	}

	//Operators
	T& operator()(int row, int collumn)
	{
		mathVect<T> *rowVect = &rowVectors[row];
		return (*rowVect)(collumn);
	}
	mathVect<T>& operator()(int index, VectorOrientation orientation)
	{
		if (orientation = vertical)
		{
			return collumnVectors[index];
		}
		return rowVectors[index];
		
	}
	mathVect<T> operator*(mathVect<T> pVect)
	{
		mathVect<T> result;
		if (pVect.Size() != width)
		{
			return result;
		}
		int i, j;
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				result(i) += rowVectors[i](j)*pVect(j);
			}
		}
		return result;

	}

private:
	std::vector<mathVect<T>> rowVectors;
	std::vector<mathVect<T>> collumnVectors;
	int width;
	int height;
};