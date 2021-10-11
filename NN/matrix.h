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
class matrix
	{
	friend std::ostream &operator<<(std::ostream &stream, const matrix &data);

	public:
		double *values;
		size_t rows;
		size_t columns;

	private:
		matrix() = delete;

	public:
		/*
			MATRIX::MATRIX()
			----------------
		*/
		matrix(size_t rows, size_t columns) :
			rows(rows),
			columns(columns)
			{
			values = new double[rows * columns];
			memset(values, 0, sizeof(double) * rows * columns);
			}

		/*
			MATRIX::~MATRIX()
			----------------
		*/
		virtual ~matrix()
			{
			delete [] values;
			}

		/*
			MATRIX::OPERATOR()()
			--------------------
		*/
		double &operator()(size_t y, size_t x) const
			{
			return values[y * columns + x];
			}

		/*
			MATRIX::OPERATOR=()
			-------------------
		*/
		matrix &operator=(std::initializer_list<double> &&data)
			{
			size_t index = 0;
			for (double value : data)
				values[index++] = value;

			return *this;
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		vector multiply(vector &with)
			{
			vector answer(rows);

			for (size_t row = 0; row < rows; row++)
				{
				answer[row] = 0;
				for (size_t column = 0; column < columns; column++)
					answer[row] += (*this)(row, column) * with[column];
				}

			return answer;
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		template <typename FUNCTOR>
		void multiply(vector &answer, vector &with, vector &bias, FUNCTOR &f)
			{
			memset(answer.values, 0, sizeof(answer.values) * answer.size);		// initialise to 0
			for (size_t row = 0; row < rows; row++)
				{
				for (size_t column = 0; column < columns; column++)
					answer[row] += (*this)(row, column) * with[column];
				answer[row] = f(answer[row] + bias[row]);
				}
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		matrix multiply(matrix &with)
			{
			matrix answer(rows, with.columns);

			for (size_t row = 0; row < rows; row++)
				for (size_t other_column = 0; other_column < with.columns; other_column++)
					{
					answer(row, other_column) = 0;
					for (size_t column = 0; column < columns; column++)
						answer(row, other_column) += (*this)(row, column) * with(column, other_column);
					}

			return answer;
			}
	};

/*
	OPERATOR<<()
	------------
*/
inline std::ostream &operator<<(std::ostream &stream, const matrix &data)
	{
	stream << '{';
	for (size_t row = 0; row < data.rows; row++)
		{
		if (row != 0)
			stream << '\n';
		for (size_t column = 0; column < data.columns; column++)
			{
			if (column != 0)
				stream << ", ";
			stream << data(row, column);
			}
		}
	stream << '}';

	return stream;
	}
