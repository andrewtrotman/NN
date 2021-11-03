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
		matrix(size_t rows, size_t columns) noexcept :
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
		matrix(matrix &from) noexcept :
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
		matrix(matrix &&from) noexcept :
			rows(from.rows),
			columns(from.columns)
			{
			values = from.values;
			from.values = nullptr;
			}

		/*
			MATRIX::~MATRIX()
			----------------
		*/
		virtual ~matrix() noexcept
			{
			delete [] values;
			}

		/*
			MATRIX::OPERATOR()()
			--------------------
		*/
		double &operator()(size_t row, size_t column) const noexcept
			{
			return values[row * columns + column];
			}

		/*
			MATRIX::OPERATOR=()
			-------------------
		*/
		matrix &operator=(std::initializer_list<double> &&data) noexcept
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
		matrix &operator=(matrix &what) noexcept
			{
			if (rows != what.rows || columns != what.columns)
				{
				delete [] values;
				values = new double [rows * columns];
				}

			rows = what.rows;
			columns = what.columns;

			memcpy(values, what.values, sizeof(*values) * rows * columns);

			return *this;
			}

		/*
			MATRIX::OPERATOR=()
			-------------------
		*/
		matrix &operator=(matrix &&what) noexcept
			{
			delete [] values;
			values = what.values;
			what.values = nullptr;

			rows = what.rows;
			columns = what.columns;

			return *this;
			}

		/*
			MATRIX::SUBTRACT()
			------------------
		*/
		void subtract(matrix &answer, matrix &right_hand_side) const noexcept
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(row, column) = operator()(row, column) - right_hand_side(row, column);
			}

		/*
			MATRIX::OPERATOR-()
			-------------------
		*/
		matrix operator-(matrix &with) const noexcept
			{
			matrix answer(with.rows, with.columns);
			subtract(answer, with);

			return answer;
			}

		/*
			MATRIX::OPERATOR-()
			-------------------
		*/
		matrix operator-(matrix &&with) const noexcept
			{
			matrix answer(with.rows, with.columns);
			subtract(answer, with);

			return answer;
			}

		/*
			MATRIX::ADD()
			-------------
		*/
		void add(matrix &answer, matrix &right_hand_side) const noexcept
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(row, column) = operator()(row, column) + right_hand_side(row, column);
			}

		/*
			MATRIX::OPERATOR+()
			-------------------
		*/
		matrix operator+(matrix &with)  const noexcept
			{
			matrix answer(with.rows, with.columns);
			add(answer, with);

			return answer;
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		template <typename FUNCTOR>
		void multiply(matrix &answer, matrix &derivitive, matrix &with, FUNCTOR &f, FUNCTOR &derivitive_of_f)  const noexcept
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t other_column = 0; other_column < with.columns; other_column++)
					{
					double score = 0;
					for (size_t column = 0; column < columns; column++)
						score += operator()(row, column) * with(column, other_column);
					answer(row, other_column) = f(score);
					derivitive(row, other_column) = derivitive_of_f(score);
					}
			}

		/*
			MATRIX::MULTIPLY()
			------------------
		*/
		void multiply(matrix &answer, matrix &with)  const noexcept
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t other_column = 0; other_column < with.columns; other_column++)
					{
					answer(row, other_column) = 0;
					for (size_t column = 0; column < columns; column++)
						answer(row, other_column) += operator()(row, column) * with(column, other_column);
					}
			}

		/*
			MATRIX::OPERATOR*()
			-------------------
		*/
		matrix operator*(matrix &with)  const noexcept
			{
			matrix answer(rows, with.columns);
			multiply(answer, with);

			return answer;
			}

		/*
			MATRIX::OPERATOR*()
			-------------------
		*/
		matrix operator*(matrix &&with)  const noexcept
			{
			matrix answer(rows, with.columns);
			multiply(answer, with);

			return answer;
			}

		/*
			MATRIX::OPERATOR*()
			-------------------
		*/
		matrix operator*(double with)  const noexcept
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
		void transpose(matrix &answer)  const noexcept
			{
			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(column, row) = operator()(row, column);
			}

		/*
			MATRIX::OPERATOR~()
			-------------------
		*/
		matrix operator~()  const noexcept
			{
			matrix answer(columns, rows);
			transpose(answer);

			return answer;
			}

		/*
			HADAMARD_PRODUCT()
			------------------
		*/
		matrix hadamard_product(matrix &right_hand_side)
			{
			matrix answer(rows, columns);
			for (size_t row = 0; row < rows; row++)
				for (size_t column = 0; column < columns; column++)
					answer(row, column) = operator()(row, column) * right_hand_side(row, column);

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
