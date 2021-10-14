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

	nn network(training_data, training_answers);
	network.add_layer(3);		// input layer
	network.add_layer(1);		// output layer

	matrix net_answer(1, 1);
	matrix net_input(2, 1);
	net_input = {1,0};

	for (size_t epoc = 0; epoc < 50; epoc++)
		network.train(1);

	network.execute(net_answer, net_input);

	std::cout << "NN answer = ";
	std::cout << net_answer << '\n';

	return 0;
	}
