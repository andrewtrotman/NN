/*
	MATRIX.H
	--------
*/
#pragma once

#include <stddef.h>
#include <string.h>

#include <iostream>
#include <initializer_list>

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
			memset(values, 0, sizeof(*values) * rows * columns);
			}

		/*
			MATRIX::MATRIX()
			----------------
		*/
		matrix(matrix &from) :
			rows(from.rows),
			columns(from.columns)
			{
			values = new double[rows * columns];
			memcpy(values, from.values, sizeof(*values) * rows * columns);
			}


		/*
			MATRIX::MATRIX()
			----------------
		*/
		matrix(matrix &&from) :
			rows(from.rows),
			columns(from.columns)
			{
			values = new double[rows * columns];
			memcpy(values, from.values, sizeof(*values) * rows * columns);
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
		double &operator()(size_t row, size_t column) const
			{
			return values[row * columns + column];
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
			MATRIX::OPERATOR=()
			-------------------
		*/
		matrix &operator=(matrix &what)
			{
			delete [] values;
			this->rows = what.rows;
			this->columns = what.columns;
			this->values = new double [rows * columns];

			memcpy(values, what.values, sizeof(*values) * rows * columns);

			return *this;
			}

		/*
			MATRIX::OPERATOR=()
			-------------------
		*/
		matrix &operator=(matrix &&what)
			{
			delete [] values;
			rows = what.rows;
			columns = what.columns;
			values = new double [rows * columns];

			memcpy(values, what.values, sizeof(*values) * rows * columns);
			
			return *this;
			}

		/*
			MATRIX::SUBTRACT()
			------------------
		*/
		void subtract(matrix &answer, matrix &right_hand_side)
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(row, column) = operator()(row, column) - right_hand_side(row, column);
			}

		/*
			MATRIX::OPERATOR-()
			-------------------
		*/
		matrix operator-(matrix &with)
			{
			matrix answer(with.rows, with.columns);
			subtract(answer, with);

			return answer;
			}

		/*
			MATRIX::ADD()
			-------------
		*/
		void add(matrix &answer, matrix &right_hand_side)
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(row, column) = operator()(row, column) + right_hand_side(row, column);
			}

		/*
			MATRIX::OPERATOR+()
			-------------------
		*/
		matrix operator+(matrix &with)
			{
			matrix answer(with.rows, with.columns);
			add(answer, with);

			return answer;
			}

		/*
			MATRIX::MEMBER_WISE_MULTIPLY()
			------------------------------
		*/
		void member_wise_multiply(matrix &answer, matrix &right_hand_side)
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(row, column) = operator()(row, column) * right_hand_side(row, column);
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		template <typename FUNCTOR>
		void multiply(matrix &answer, matrix &with, FUNCTOR &f)
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t other_column = 0; other_column < with.columns; other_column++)
					{
					double score = 0;
					for (size_t column = 0; column < columns; column++)
						score += (*this)(row, column) * with(column, other_column);
					answer(row, other_column) = f(score);
					}
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		void multiply(matrix &answer, matrix &with)
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t other_column = 0; other_column < with.columns; other_column++)
					{
					answer(row, other_column) = 0;
					for (size_t column = 0; column < columns; column++)
						answer(row, other_column) += (*this)(row, column) * with(column, other_column);
					}
			}

		/*
			MATRIX::OPERATOR*()
			-------------------
		*/
		matrix operator*(matrix &with)
			{
			matrix answer(rows, with.columns);
			multiply(answer, with);

			return answer;
			}

		/*
			MATRIX::OPERATOR*()
			-------------------
		*/
		matrix operator*(double with)
			{
			matrix answer(rows, columns);

			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(row, column) = operator()(row, column) * with;

			return answer;
			}


		/*
			MATRIX::TRANSPOSE()
			-------------------
		*/
		void transpose(matrix &answer)
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(column, row) = operator()(row, column);
			}

		/*
			MATRIX::OPERATOR~()
			-------------------
		*/
		matrix operator~()
			{
			matrix answer(columns, rows);
			transpose(answer);

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
