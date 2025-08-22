#include <iostream>
#include <string>
#include "Equation.hpp"

int	main(int argc, char **argv)
{
	//pas de math !!!!!
	//si argc 1 entree standard
	if (argc != 2)//concatener args ?
	{
		std::cerr << "Usage: ./computorv1 \"[equation]\"\n";
		return 1;
	}

	Equation	eq;
	std::string	s = argv[1];

	try
	{
		eq = Equation(s);
		std::cout << s << "\n";
		std::cout << eq << "\n";
		if (eq.sort())
			std::cout << eq << "\n";
		if (eq.simplify())
			std::cout << eq << "\n";
		if (eq.oneside())
			std::cout << eq << "\n";
		if (eq.simplify())
			std::cout << eq << "\n";
	}
	catch (std::pair<std::runtime_error, size_t> &p)
	{
		std::cerr << s << "\n";
		for (size_t i = 0; i < p.second; ++i)
			std::cout << " ";
		std::cout << "^\n";
		std::cerr << "Error: " << p.first.what() << "\n";
		return 1;
	}
	return 0;
}
