/*
	NN.H
	----
*/
#pragma once

#include <algorithm>

#include "matrix.h"
#include "vector.h"

/*
	CLASS NN
	--------
*/
class nn
	{
	private:
		matrix training_data;
		vector training_answers;
		vector final_answers;
		double learning_parameter;

	public:
		/*
			NN::NN()
			--------
		*/
		nn(matrix &training_data, vector &training_answers) :
			training_data(training_data),
			training_answers(training_answers),
			final_answers(training_answers.size()),
			learning_parameter(0.001)
			{
			/*	Nothing */
			}

		/*
			NN::MEAN_SQUARED_ERROR()
			------------------------
		*/
		double mean_squared_error(void)
			{
			double sum = 0;
			for (size_t element = 0; element < training_answers.size(); element++)
				{
				double single_error = training_answers[element] - final_answers[element];
				sum += single_error * single_error;
				}
			return sum / (2.0 * training_answers.size());
			}

		/*
			NN::UNITTEST()
			--------------
		*/
		static void unittest(void);
	};

/*
	RELU()
	------
*/
inline double ReLU(double input)
	{
	return std::max(input, 0.0);
	}
