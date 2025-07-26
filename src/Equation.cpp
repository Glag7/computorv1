#include <iostream>
#include <algorithm>
#include "Equation.hpp"

Equation::Equation()
{
}

Equation::Equation(const std::string &s2)
{
	std::string s = s2;
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
	std::cout << s;
}

//[a][*][x[^b]]
