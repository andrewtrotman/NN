/*
	NN.H
	----
*/
#pragma once

#include <algorithm>

class nn
	{
	public:
		/*
			NN::RELU()
			----------
		*/
		static double ReLU(double input)
			{
			return std::max(input, 0.0);
			}
	};
