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
		matrix values;
		matrix weights;
		matrix derivitive;
		matrix delta;

	public:
		/*
			NODE::NODE()
			------------
		*/
		node(size_t input_units) :
			values(input_units, 1),
			weights(0, 0),
			derivitive(0,0),
			delta(0,0)
			{
			/* Nothing */
			}

		/*
			NODE::NODE()
			------------
		*/
		node(matrix &training_data) :
			values(training_data.rows, training_data.columns),
			weights(0, 0),
			derivitive(0, 0),
			delta(0,0)
			{
			values = training_data;
			}

		/*
			NODE::NODE()
			------------
		*/
		node(node &previous, size_t units) :
			values(previous.values.rows, units),
			weights(previous.values.columns, units),
			derivitive(previous.values.rows, units),
			delta(previous.values.rows, units)
			{
			for (size_t entry = 0; entry < previous.values.columns * units; entry++)
				weights.values[entry] = drand48();
			}

		/*
			NODE::~NODE()
			------------
		*/
		virtual ~node()
			{
			/* Nothing */
			}
	};
