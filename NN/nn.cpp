/*
	NN.CPP
	-----
*/
#include "nn.h"

/*
	NN::UNITTEST()
	--------------
*/
void nn::unittest(void)
	{
	}

/*
	NN::MEAN_SQUARED_ERROR()
	------------------------
*/
double nn::mean_squared_error(void)
	{
	double sum = 0;
	for (size_t element = 0; element < training_answers.size(); element++)
		{
		double single_error = training_answers[element] - final_answers[element];
		sum += single_error * single_error;
		}
	return sum / (2.0 * training_answers.size());
	}
