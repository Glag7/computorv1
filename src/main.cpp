#include <iostream>
#include <string>
#include "Equation.hpp"

int	main(int argc, char **argv)
{
	if (argc > 2)
	{
		std::cerr << "Usage: ./computorv1 \"[equation]\"\n";
		return 1;
	}

	do
	{
		Equation	eq;
		std::string	s;

		if (argc == 1)
		{
			if (!std::getline(std::cin, s))
				break;
		}
		else
			s = argv[1];
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
			eq.solve(std::cout);
		}
		catch (std::pair<std::runtime_error, size_t> &p)
		{
			std::cerr << s << "\n";
			for (size_t i = 0; i < p.second; ++i)
				std::cout << " ";
			std::cout << "^\n";
			std::cerr << "Error: " << p.first.what() << "\n";
		}
	}
	while (argc == 1);
	return 0;
}
