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
		size = 2;
		elements.resize(size);
		orientation = vertical;
		int i;
		for (i = 0; i < size; i++)
		{
			elements[i] = 0;
		}
	}
	mathVect(int size)
	{
		this->size = size;
		elements.resize(size);
		orientation = vertical;
		int i;
		for (i = 0; i < size; i++)
		{
			elements[i] = 0;
		}
	}
	mathVect(const std::vector<T> &inV, VectorOrientation orientation)
	{
		size = inV.size();
		elements.resize(size);
		elements = inV;
		this->orientation = orientation;
		int i;
		for (i = 0; i < size; i++)
		{
			elements[i] = 0;
		}
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
	void SetSize(int newSize)
	{
		size = newSize;
		elements.resize(newSize);
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
		collumnVectors.resize(height);
		ResizeCollumns();
		ResizeRows();
		rowVectors[0](0) = (T)0; rowVectors[0](1) = (T)0; rowVectors[0](2) = (T)0
		rowVectors[1](0) = (T)0; rowVectors[1](1) = (T)0; rowVectors[1](2) = (T)0;
		rowVectors[2](0) = (T)0; rowVectors[2](1) = (T)0; rowVectors[2](2) = (T)0;
		lastUpdated = horizontal;
	}
	gMatrix(int width, int height)
	{

			this->width = width;
			this->height = height;
			rowVectors.resize(width);
			collumnVectors.resize(height);
			
			ResizeCollumns();
			ResizeRows();
			int i, j;
			for (i = 0; i < width; i++)
			{
				for (j = 0; j < height; j++)
				{
					rowVectors[j](i) = (T)0;
				}
				
			}
			lastUpdated = horizontal;
	}
	//Operators
	T& operator()(int row, int collumn)
	{
		UpdateCollumns();
		mathVect<T> *rowVect = &rowVectors[row];

		return (*rowVect)(collumn);
	}
	mathVect<T>& operator()(int index, VectorOrientation orientation)
	{
		if (orientation == vertical)
		{
			
			UpdateCollumns();

			return collumnVectors[index];
		}
		UpdateRows();
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
	void UpdateRows()
	{
		if (lastUpdated == vertical)
		{
			int i, j;
			for (j = 0; j < height; j++)
			{
				for (i = 0; i < width; i++)
				{
					rowVectors[j](i) = collumnVectors[i](j);

				}
			}
		}
		lastUpdated = horizontal;
	}
	void UpdateCollumns()
	{
		if (lastUpdated == horizontal)
		{
			int i, j;
			for (j = 0; j < height; j++)
			{
				for (i = 0; i < width; i++)
				{
					collumnVectors[j](i) = rowVectors[i](j);

				}
			}
		}
		lastUpdated = vertical;
	}
	void ResizeCollumns()
	{
		int i;
		for (i = 0; i < width; i++)
		{
			collumnVectors[i].SetSize(height);
		}
	}
	void ResizeRows()
	{
		int i;
		for (i = 0; i < height; i++)
		{
			collumnVectors[i].SetSize(width);
		}
	}
	std::vector<mathVect<T>> rowVectors;
	std::vector<mathVect<T>> collumnVectors;
	VectorOrientation lastUpdated;
	int width;
	int height;
};