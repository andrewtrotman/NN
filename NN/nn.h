/*
	NN.H
	----
*/
#pragma once

#include <algorithm>

template <typename TYPE, size_t FEATURES, size_t TRAIN_SIZE>
class nn
	{
	};

inline double ReLU(double input)
	{
	return std::max(input, 0.0);
	}
