#include <iostream>
#include <string>
#include "Equation.hpp"

#include "Fraction.hpp"
int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./computorv1 \"[equation]\"\n";
		return 1;
	}

	Equation	eq;

	try
	{
		eq = Equation(argv[1]);
		std::cout << "\n";
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	//return 0;
	Fraction	a(1,4);
	Fraction	b(1,3);

	std::cout << a * b << "\n";
	a *= b;
	std::cout << a << "\n";
	std::cout << b << "\n";
	try
	{
		throw std::make_pair(std::runtime_error("wow"), 2.);
	}
	catch (std::pair<std::runtime_error, double> &a)
	{
		std::cout << a.first.what() << "\n";
	}
}
