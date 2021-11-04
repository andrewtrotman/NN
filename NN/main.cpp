/*
	MAIN.CPP
	--------
*/
#include <iostream>

#include "matrix.h"
#include "nn.h"

int main(int argc, const char * argv[])
	{
	/*
		Test the neural network
	*/
	matrix training_data(4, 3);
	training_data =
		{
		1, 0, 0,
		1, 0, 1,
		1, 1, 0,
		1, 1, 1
		};

	matrix training_answers(4, 1);
	training_answers =
		{
		0,
		1,
		1,
		2
		};

	nn network(training_data, training_answers);		// the training data defines the input layer.
//	network.add_layer(3);		// hidden layer
//	network.add_layer(5);		// hidden layer
	network.add_layer(3);		// hidden layer
	network.add_layer(1);		// output layer is a single value

	for (size_t epoc = 0; epoc < 100000; epoc++)
		network.train(1);

	network.execute();

	return 0;
	}
