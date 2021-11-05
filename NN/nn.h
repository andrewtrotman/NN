/*
	NN.H
	----
	Copyright (c) 2021 Andrew Trotman
	Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)
*/
/*!
	@file
	@brief Simple multilayer preceptron neural network.
	@author Andrew Trotman
	@copyright 2021 Andrew Trotman
*/
#pragma once

#include <math.h>
#include <algorithm>

#include "matrix.h"

/*
	RELU()
	------
*/
/*!
	@brief Rectified Linear Unit (ReLU)
	@param input [in] The value to apply ReLU to.
	@return 0 if input <= 0, else input.
*/
inline double ReLU(double input)
	{
	return std::max(input, 0.0);
	}

/*
	RELU_DERIVERATIVE()
	-------------------
*/
/*!
	@brief The derivitive of the Rectified Linear Unit (ReLU) functon
	@param input [in] The value to apply ReLU to.
	@return 1 if input > 0 else 0.
*/
inline double ReLU_derivitive(double input)
	{
	return input > 0 ? 1 : 0;
	}

/*
	CLASS NN
	--------
*/
/*!
	@class nn
	@brief Simple multilayer preceptron neural network.
*/
class nn
	{
	private:
		/*
			CLASS NN::LAYER
			--------------
		*/
		/*!
			@class layer
			@brief A single layer in the multi-layer perceptron
		*/
		class layer
			{
			public:
				matrix values;					// the values stored in each of the units at this level of the network
				matrix weights_space;			// storage space for the current in-use set of weights ((switches using weights and weights_next)
				matrix weights_next_space;		// storage space for the next set of weights (switches using weights and weights_next)
				matrix *weights;				// the current set of weights
				matrix *weights_next;			// the set of weights to use next iteration
				matrix derivitive;				// the derivitive of the weights
				matrix delta;					// the error at this level of the network

			public:
				/*
					LAYER::LAYER()
					--------------
				*/
				layer(matrix &training_data) :
					values(training_data.rows, training_data.columns),
					weights_space(0, 0),
					weights_next_space(0, 0),
					derivitive(0, 0),
					delta(0,0)
					{
					weights = &weights_space;
					weights_next = &weights_next_space;

					values = training_data;
					}

				/*
					LAYER::LAYER()
					--------------
				*/
				layer(layer &previous, size_t units) :
					values(previous.values.rows, units),
					weights_space(previous.values.columns, units),
					weights_next_space(previous.values.columns, units),
					derivitive(previous.values.rows, units),
					delta(previous.values.rows, units)
					{
					weights = &weights_space;
					weights_next = &weights_next_space;

					for (size_t entry = 0; entry < previous.values.columns * units; entry++)
						weights->values[entry] = drand48();
					}
			};

	private:
		matrix training_data;
		matrix training_answers;
		double learning_parameter;

		layer **network;
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
			network = (layer **)malloc(sizeof(*network));
			network[0] = new layer(training_data);
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
			network = (layer **)realloc(network, sizeof(*network) * (depth + 1));
			network[depth] = new layer(*network[depth - 1], units);
			depth++;
			}

		/*
			NN::EXECUTE()
			-------------
		*/
		void execute(void)
			{
			for (size_t level = 1;  level < depth; level++)
				network[level - 1]->values.feed_forward(network[level]->values, *network[level]->weights, ReLU);

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
				network[level - 1]->values.feed_forward_ready_for_backprop(network[level]->values, network[level]->derivitive, *network[level]->weights, ReLU, ReLU_derivitive);

			/*
				Compute the deltas through back propagation
			*/
//#define EXPENSIVE 1
#ifdef EXPENSIVE
         	network[depth - 1]->delta = (network[depth - 1]->values - training_answers).hadamard_product(network[depth - 1]->derivitive);
#else
			network[depth - 1]->values.subtract_then_hadamard_product(network[depth - 1]->delta, training_answers, network[depth - 1]->derivitive);
#endif
			for (size_t level = depth - 2; level > 0; level--)
				{
#ifdef EXPENSIVE
	         	network[level]->delta = (network[level + 1]->delta * ~(*network[level + 1]->weights)).hadamard_product(network[level]->derivitive);
#else
				network[level + 1]->delta.dot_transpose_hadamard(network[level]->delta , *network[level + 1]->weights, network[level]->derivitive);
#endif
				}

			/*
				Update the weights
			*/
			for (size_t level = 1;  level < depth; level++)
				{
#ifdef EXPENSIVE
				*network[level]->weights = *network[level]->weights - (~network[level - 1]->values * network[level]->delta * learning_parameter);
#else

				network[level]->weights->minus_transpose_dot_times(*network[level]->weights_next, network[level - 1]->values, network[level]->delta, learning_parameter);
				std::swap(network[level]->weights, network[level]->weights_next);
#endif
				}
			}

		/*
			NN::UNITTEST()
			--------------
		*/
		static void unittest(void);
	};
