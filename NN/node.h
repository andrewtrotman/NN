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
		matrix bias;

	public:
		/*
			NODE::NODE()
			------------
		*/
		node(size_t input_units) :
			values(input_units, 1),
			weights(0, 0),
			bias(input_units, 1)
			{
			/* Nothing */
			}

		/*
			NODE::NODE()
			------------
		*/
		node(node &previous, size_t nodes) :
			values(nodes, 1),
			weights(previous.values.rows, nodes),
			bias(nodes, 1)
			{
			for (size_t entry = 0; entry < nodes * previous.values.rows; entry++)
				weights.values[entry] = drand48();

			for (size_t entry = 0; entry < nodes; entry++)
				bias(entry, 1) = drand48();
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
