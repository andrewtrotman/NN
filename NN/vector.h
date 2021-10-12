/*
	VECTOR.H
	--------
*/
#pragma once

#include <stddef.h>

#include <iostream>
#include <initializer_list>

/*
	CLASS VECTOR
	------------
*/
class vector
	{
	friend std::ostream &operator<<(std::ostream &stream, const vector &data);
	friend class matrix;

	private:
		double *values;
		size_t dimensions;

	private:
		vector() = delete;

	public:
		/*
			VECTOR::VECTOR()
			----------------
		*/
		vector(size_t dimensions) :
			dimensions(dimensions)
			{
			values = new double[dimensions];
			memset(values, 0, sizeof(*values) * dimensions);
			}

		/*
			VECTOR::VECTOR()
			----------------
		*/
		vector(vector &from) :
			dimensions(from.dimensions)
			{
			values = new double[dimensions];
			memcpy(values, from.values, sizeof(*values) * dimensions);
			}

		/*
			VECTOR::VECTOR()
			----------------
		*/
		vector(std::initializer_list<double> initial):
			dimensions(initial.size())
			{
			values = new double[dimensions];

			size_t which = 0;
			for (double value : initial)
				values[which++] = value;
			}

		/*
			VECTOR::~VECTOR()
			-----------------
		*/
		virtual ~vector()
			{
			delete [] values;
			}

		/*
			VECTOR::OPERATOR[]()
			--------------------
		*/
		double &operator[](size_t index) const
			{
			return values[index];
			}

		/*
			VECTOR::SIZE()
			--------------
		*/
		size_t size(void) const
			{
			return dimensions;
			}
	};

/*
	OPERATOR<<()
	------------
*/
inline std::ostream &operator<<(std::ostream &stream, const vector &data)
	{
	stream << '{';
	for (size_t index = 0; index < data.dimensions; index++)
		{
		if (index != 0)
			stream << ", ";
		stream << data.values[index];
		}
	stream << '}';

	return stream;
	}
