#include <iostream>
#include <string>
#include "Equation.hpp"

#include <algorithm>
#include "Factor.hpp"
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

	std::string s = argv[1];
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
	try
	{
		//eq = Equation(argv[1]);
		//std::cout << "\n";
		Factor	fac = Factor(s);
		std::cout << fac << "\n";
		return 0;
	}
	catch (std::pair<std::runtime_error, size_t> &p)
	{
		std::cerr << s << "\n";
		for (int i = 0; i < p.second; ++i)
			std::cout << " ";
		std::cout << "^\n";
		std::cerr << "Error: " << p.first.what() << "\n";
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
	try
	{
		Fraction	frac = Fraction(std::stod(argv[1]));
		std::cout << frac << "\n";
		std::cout << frac.todouble() << "\n";
	}
	catch (...)
	{
		std::cout << "nuhuh\n";
	}
	try
	{
		Fraction	frac2 = stofrac(argv[1], NULL);
		std::cout << frac2 << "\n";
		std::cout << frac2.todouble() << "\n";
	}
	catch (...)
	{
		std::cout << "nuhuh\n";
	}
}
