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
		return elements[index];// elements(index);
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

private:
	std::vector<T> elements;
	int size;
	VectorOrientation orientation;
};

