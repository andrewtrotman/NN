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
template <typename TYPE, size_t SIZE>
class vector
	{
	template <typename TYPE1, size_t SIZE1> friend std::ostream &operator<<(std::ostream &stream, const vector<TYPE1, SIZE1> &data);

	private:
		TYPE values[SIZE];
		
	public:
		/*
			VECTOR::VECTOR()
			----------------
		*/
		vector()
			{
			memset(values, 0, sizeof(values));
			}

		/*
			VECTOR::VECTOR()
			----------------
		*/
		vector(std::initializer_list<TYPE> initial)
			{
			size_t which = 0;

			for (TYPE value : initial)
				values[which++] = value;
			}

		/*
			VECTOR::~VECTOR()
			-----------------
		*/
		virtual ~vector()
			{
			/* Nothing */
			}

		/*
			VECTOR::OPERATOR[]()
			--------------------
		*/
		TYPE &operator[](size_t index)
			{
			return values[index];
			}
	};

/*
	OPERATOR<<()
	------------
*/
template <typename TYPE, size_t SIZE>
std::ostream &operator<<(std::ostream &stream, const vector<TYPE, SIZE> &data)
	{
	stream << '{';
	for (size_t index = 0; index < SIZE; index++)
		{
		if (index != 0)
			stream << ", ";
		stream << data.values[index];
		}
	stream << '}';

	return stream;
	}
