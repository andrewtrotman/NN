/*
	MAIN.CPP
	--------
*/
#include <iostream>

#include "matrix.h"
#include "nn.h"

int main(int argc, const char * argv[])
	{
	vector<double, 3> x = {2, 1, 0};
	matrix<double, 2, 3> y =
		{
		1, -1, 2,
		0, -3, 1
		};

	matrix<double, 2, 3> a =
		{
		1, 2, 3,
		4, 5, 6
		};


	matrix<double, 3, 4> b =
		{
		1, 1, 1, 1,
		1, 1, 1, 1,
		1, 1, 1, 1,
		};

	std::cout << "x = \n" << x << '\n';
	std::cout << "y = \n" << y << '\n';

	auto z = y.multiply(x);
	std::cout << "ans = \n" << z << "\n\n";

	auto d = y.multiply(x, nn::ReLU);
	std::cout << "ans = \n" << d << "\n\n";

	std::cout << "a = \n" << a << '\n';
	std::cout << "b = \n" << b << '\n';

	auto c = a.multiply(b);
	std::cout << "ans = \n" << c << "\n\n";

	return 0;
	}
