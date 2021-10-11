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
		size_t size;

	private:
		vector() = delete;

	public:
		/*
			VECTOR::VECTOR()
			----------------
		*/
		vector(size_t size) :
			size(size)
			{
			values = new double[size];
			memset(values, 0, sizeof(*values) * size);
			}

		/*
			VECTOR::VECTOR()
			----------------
		*/
		vector(std::initializer_list<double> initial):
			size(initial.size())
			{
			values = new double[size];

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
		double &operator[](size_t index)
			{
			return values[index];
			}
	};

/*
	OPERATOR<<()
	------------
*/
inline std::ostream &operator<<(std::ostream &stream, const vector &data)
	{
	stream << '{';
	for (size_t index = 0; index < data.size; index++)
		{
		if (index != 0)
			stream << ", ";
		stream << data.values[index];
		}
	stream << '}';

	return stream;
	}
