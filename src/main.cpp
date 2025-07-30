#include <iostream>
#include <string>
#include "Equation.hpp"

#include "Fraction.hpp"
//FIXME
//les doubles prennent juste trop de place
//fix soit bigint (huh) soit parse a partir du string
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
	//std::cout << a + 2 << "\n";
	try
	{
		throw std::make_pair(std::runtime_error("wow"), 2.);
	}
	catch (std::pair<std::runtime_error, double> &a)
	{
		std::cout << a.first.what() << "\n";
	}
	Fraction	frac = Fraction(0.001);
	std::cout << frac << "\n";
	std::cout << frac.todouble() << "\n";
	frac *= 800;
	std::cout << frac << "\n";
	std::cout << frac.todouble() << "\n";
	frac /= 800;
	std::cout << frac << "\n";
	std::cout << frac.todouble() << "\n";
}
