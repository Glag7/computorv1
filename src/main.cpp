#include <iostream>
#include <string>
#include "Equation.hpp"

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
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << "\n";
		return 1;
	}
	return 0;
}
