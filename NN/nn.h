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
	RELU_1()
	--------
*/
inline double ReLU_1(double input)
	{
	return std::max(input, 0.0);
	}

/*
	RELU()
	------
*/
inline matrix ReLU(matrix input)
	{
	matrix answer(input.rows, input.columns);

	for (size_t row = 0; row < input.rows; row++)
		for (size_t column = 0; column < input.columns; column++)
			answer(row, column) = std::max(input(row, column), 0.0);

	return answer;
	}


/*
	CLASS NN
	--------
*/
class nn
	{
	private:
		matrix training_data;
		matrix training_answers;
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
		nn(matrix &training_data, matrix &training_answers) :
			training_data(training_data),
			training_answers(training_answers),
			learning_parameter(0.1)
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
			NN::EXECUTE()
			-------------
		*/
		void execute(vector &output, vector &input)
			{
			if (depth == 0 || depth == 1)
				output = input;
			else if (depth == 2)
				input.multiply(output, network[1]->weights, network[1]->bias, ReLU_1);
			else
				{
				size_t level;
				input.multiply(network[1]->values, network[1]->weights, network[1]->bias, ReLU_1);

				for (level = 2; level < depth - 1; level++)
					network[level - 1]->values.multiply(network[level]->values, network[level]->weights, network[level]->bias, ReLU_1);

				network[level - 1]->values.multiply(output, network[level]->weights, network[level]->bias, ReLU_1);
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
			training_data.multiply(out_1, network[1]->weights, network[1]->bias, ReLU_1);

std::cout << "result\n" << out_1 << '\n';
//std::cout << "\n==\n";
//
//			matrix times = training_data * network[1]->weights;
//std::cout << "training_data=\n"<< training_data << '\n';
//std::cout << "weights=\n" << network[1]->weights  << '\n';
//std::cout << "T*W=\n" << times << '\n';
//			matrix times_wb = times + network[1]->bias;
//std::cout << "B=\n" << network[1]->bias << '\n';
//std::cout << "+BIAS=\n" << times_wb << '\n';
//
//std::cout << "\n==\n";
//			matrix another_result = ReLU(training_data * network[1]->weights + network[1]->bias);
//std::cout << "another-result\n" << another_result << '\n';
//std::cout << "\n==\n";

std::cout << "should be\n" << training_answers << '\n';

			matrix error = training_answers - out_1;

std::cout << "errror\n" << error << '\n';

			matrix out_1_t = ~out_1;

			matrix deltas(error.rows, out_1_t.columns);
			deltas = out_1 * error;

std::cout << "deltas\n" << deltas << '\n';

			matrix adjustments = deltas * learning_parameter;

std::cout << "adjustments\n" << adjustments << '\n';

			int x = 0;
			}

		/*
			NN::UNITTEST()
			--------------
		*/
		static void unittest(void);
	};
