#ifndef EQUATION_HPP
# define EQUATION_HPP

#include <utility>
#include <vector>
#include <string>

class	Equation
{
	private:
		std::vector<std::pair<unsigned, unsigned>>	left;
		std::vector<std::pair<unsigned, unsigned>>	right;
		
	public:
		Equation();
		Equation(const std::string &s);
};

#endif
