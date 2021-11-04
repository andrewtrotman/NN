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

/*
	RELU()
	------
*/
inline double ReLU(double input)
	{
	return std::max(input, 0.0);
	}

/*
	RELU_DERIVERATIVE()
	-------------------
*/
inline double ReLU_derivitive(double input)
	{
	return input > 0 ? 1 : 0;
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
			learning_parameter(0.001)
			{
			network = (node **)malloc(sizeof(*network));
			network[0] = new node(training_data);
			depth = 1;
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
			network = (node **)realloc(network, sizeof(*network) * (depth + 1));
			network[depth] = new node(*network[depth - 1], units);
			depth++;
			}

		/*
			NN::EXECUTE()
			-------------
		*/
		void execute(void)
			{
			for (size_t level = 1;  level < depth; level++)
				network[level - 1]->values.neural_multiply(network[level]->values, network[level]->weights, ReLU);

			std::cout << "Answer:\n" << network[depth - 1]->values << '\n';
			}

		/*
			NN::TRAIN()
			-----------
		*/
		void train(size_t epocs)
			{
			/*
				Forward propagate the training set
			*/
			for (size_t level = 1;  level < depth; level++)
				network[level - 1]->values.multiply(network[level]->values, network[level]->derivitive, network[level]->weights, ReLU, ReLU_derivitive);

			/*
				Compute the deltas through back propagation
			*/
			network[depth - 1]->values.subtract_then_hadamard_product(network[depth - 1]->delta, training_answers, network[depth - 1]->derivitive);
			for (size_t level = depth - 2; level > 0; level--)
				network[level + 1]->delta.dot_transpose_hadamard(network[level]->delta , network[level + 1]->weights, network[level]->derivitive);

			/*
				Update the weights
			*/
			for (size_t level = 1;  level < depth; level++)
				{
				matrix into(network[level]->weights.rows, network[level]->weights.columns);

				network[level]->weights = network[level]->weights - (~network[level - 1]->values * network[level]->delta * learning_parameter);
//				network[level]->weights.minus_transpose_dot_times(into, network[level - 1]->values, network[level]->delta, learning_parameter);
//				network[level]->weights = into;
				}
			}

		/*
			NN::UNITTEST()
			--------------
		*/
		static void unittest(void);
	};
