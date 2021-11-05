/*
	NODE.H
	------
*/
#pragma once

#include "matrix.h"

/*
	CLASS NODE
	----------
*/
class node
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
			NODE::NODE()
			------------
		*/
		node(matrix &training_data) :
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
			NODE::NODE()
			------------
		*/
		node(node &previous, size_t units) :
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
