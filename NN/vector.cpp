/*
	VECTOR.CPP
	----------
*/
#include "matrix.h"

void vector::multiply(vector &answer, matrix &with, vector &bias, double (*f)(double))
	{
	for (size_t column = 0; column < with.columns; column++)
		{
		double score = 0;
		for (size_t row = 0; row < size(); row++)
			{
//			std::cout << values[row] << " * " << with(row, column) << " + ";
			score += values[row] * with(row, column);
			}
//		std::cout << bias[column] << "\n";
		answer[column] = f(score + bias[column]);
		}
	}
