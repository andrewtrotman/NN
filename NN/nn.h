/*
	NN.H
	----
*/
#pragma once

#include <math.h>
#include <algorithm>

#include "nn.h"
#include "node.h"
#include "matrix.h"
#include "vector.h"

/*
	RELU()
	------
*/
inline double ReLU(double input)
	{
	return std::max(input, 0.0);
	}

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

		node **network;
		size_t depth;

	private:
		nn() = delete;

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
			network = nullptr;
			depth = 0;
			}

		/*
			NN::~NN()
			--------
		*/
		~nn()
			{
			free(network);
			}

		/*
			NN::ADD_LAYER()
			---------------
		*/
		void add_layer(size_t units)
			{
			depth++;
			network = (node **)realloc(network, sizeof(*network) * depth);

			if (depth == 1)
				network[depth - 1] = new node(units);
			else
				network[depth - 1] = new node(*network[depth - 2], units);
			}

		/*
			NN::MEAN_SQUARED_ERROR()
			------------------------
		*/
		double mean_squared_error(void);

		/*
			NN::EXECUTE()
			-------------
		*/
		void execute(vector &output, vector &input)
			{
			if (depth == 0 || depth == 1)
				output = input;
			else if (depth == 2)
				input.multiply(output, network[1]->weights, network[1]->bias, ReLU);
			else
				{
				size_t level;
				input.multiply(network[1]->values, network[1]->weights, network[1]->bias, ReLU);

				for (level = 2; level < depth - 1; level++)
					network[level - 1]->values.multiply(network[level]->values, network[level]->weights, network[level]->bias, ReLU);

				network[level - 1]->values.multiply(output, network[level]->weights, network[level]->bias, ReLU);
				}
			}

		/*
			NN::TRAIN()
			-----------
		*/
		void train(size_t epocs)
			{
std::cout << "training\n" << training_data << '\n';
std::cout << "weights\n" << network[1]->weights << '\n';
std::cout << "bias\n" << network[1]->bias << '\n';

			matrix out_1(training_data.rows, network[1]->weights.columns);
			training_data.multiply(out_1, network[1]->weights, network[1]->bias, ReLU);

std::cout << "result\n" << out_1 << '\n';


std::cout << "should be\n" << training_answers << '\n';

			int x = 0;
			}

		/*
			NN::UNITTEST()
			--------------
		*/
		static void unittest(void);
	};
