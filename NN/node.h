/*
	NODE.H
	------
*/
#pragma once

#include "vector.h"
#include "matrix.h"

/*
	CLASS NODE
	----------
*/
class node
	{
	public:
		vector values;
		matrix weights;
		vector bias;

	public:
		/*
			NODE::NODE()
			------------
		*/
		node(size_t input_units) :
			values(input_units),
			weights(0, 0),
			bias(input_units)
			{
			/* Nothing */
			}

		/*
			NODE::NODE()
			------------
		*/
		node(node &previous, size_t nodes) :
			values(nodes),
			weights(previous.values.size(), nodes),
			bias(nodes)
			{
			for (size_t entry = 0; entry < nodes * previous.values.size(); entry++)
				weights.values[entry] = drand48();

			for (size_t entry = 0; entry < nodes; entry++)
				bias[entry] = drand48();
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
