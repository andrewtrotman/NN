/*
	MATRIX.H
	--------
*/
#pragma once

#include "vector.h"

/*
	CLASS MATRIX
	------------
*/
template <typename TYPE, size_t ROWS, size_t COLUMNS>
class matrix
	{
	template <typename TYPE1, size_t ROWS1, size_t COLUMNS1> friend std::ostream &operator<<(std::ostream &stream, const matrix<TYPE1, ROWS1, COLUMNS1> &data);

	public:
		TYPE values[ROWS][COLUMNS];

	public:
		/*
			MATRIX::MATRIX()
			----------------
		*/
		matrix()
			{
			/* Nothing */
			}

		/*
			MATRIX::MATRIX()
			----------------
		*/
		matrix(std::initializer_list<TYPE> initial)
			{
			size_t row = 0;
			size_t column = 0;

			for (TYPE value : initial)
				{
				values[row][column] = value;
				column++;
				if (column >= COLUMNS)
					{
					row++;
					column = 0;
					}
				}
			}



		/*
			MATRIX::~MATRIX()
			----------------
		*/
		virtual ~matrix()
			{
			/* Nothing */
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		vector<TYPE, ROWS> multiply(vector<TYPE, COLUMNS> &with)
			{
			vector<TYPE, ROWS> answer;

			for (size_t row = 0; row < ROWS; row++)
				{
				answer[row] = 0;
				for (size_t column = 0; column < COLUMNS; column++)
					answer[row] += values[row][column] * with[column];
				}

			return answer;
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		template <typename FUNCTOR>
		vector<TYPE, ROWS> multiply(vector<TYPE, COLUMNS> &with, FUNCTOR &f)
			{
			vector<TYPE, ROWS> answer;

			for (size_t row = 0; row < ROWS; row++)
				{
				answer[row] = 0;
				for (size_t column = 0; column < COLUMNS; column++)
					answer[row] += values[row][column] * with[column];
				answer[row] = f(answer[row]);
				}

			return answer;
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		template <size_t ROWS2 = COLUMNS, size_t COLUMNS2>
		matrix<TYPE, ROWS, COLUMNS2> multiply(matrix<TYPE, ROWS2, COLUMNS2> &with)
			{
			matrix<TYPE, ROWS, COLUMNS2> answer;

			for (size_t row = 0; row < ROWS; row++)
				for (size_t other_column = 0; other_column < COLUMNS2; other_column++)
					{
					answer.values[row][other_column] = 0;
					for (size_t column = 0; column < COLUMNS; column++)
						answer.values[row][other_column] += values[row][column] * with.values[column][other_column];
					}

			return answer;
			}

	};

/*
	OPERATOR<<()
	------------
*/
template <typename TYPE, size_t ROWS, size_t COLUMNS>
std::ostream &operator<<(std::ostream &stream, const matrix<TYPE, ROWS, COLUMNS> &data)
	{
	stream << '{';
	for (size_t row = 0; row < ROWS; row++)
		{
		if (row != 0)
			stream << '\n';
		for (size_t column = 0; column < COLUMNS; column++)
			{
			if (column != 0)
				stream << ", ";
			stream << data.values[row][column];
			}
		}
	stream << '}';

	return stream;
	}
