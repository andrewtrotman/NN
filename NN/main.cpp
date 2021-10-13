/*
	MAIN.CPP
	--------
*/
#include <iostream>

#include "matrix.h"
#include "nn.h"

int main(int argc, const char * argv[])
	{
	vector x = {2, 1, 0};
	matrix y(2,3);
	y =
		{
		1.0, -1.0, 2.0,
		0.0, -3.0, 1.0
		};

	matrix a(2, 3);
	a =
		{
		1, 2, 3,
		4, 5, 6
		};


	matrix b(3, 4);
	b =
		{
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1,
		};

	vector bias = {1, 1};

	std::cout << "x = \n" << x << '\n';
	std::cout << "y = \n" << y << '\n';

	auto z = y.multiply(x);
	std::cout << "ans = \n" << z << "\n\n";

	std::cout << "a = \n" << a << '\n';
	std::cout << "b = \n" << b << '\n';

	auto c = a.multiply(b);
	std::cout << "ans = \n" << c << "\n\n";


	/*
		Test the neural network
	*/
	matrix training_data(4, 2);
	training_data =
		{
		0, 0,
		0, 1,
		1, 0,
		1, 1
		};

	vector training_answers = {0, 1, 1, 0};

	nn network(training_data, training_answers);
	network.add_layer(2);		// input layer
	network.add_layer(1);		// output layer

	vector net_answer(1);
	vector net_input = {1,0};

	network.train(1);

	network.execute(net_answer, net_input);

	std::cout << "NN answer = ";
	std::cout << net_answer << '\n';

	return 0;
	}
