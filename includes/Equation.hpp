#ifndef EQUATION_HPP
# define EQUATION_HPP

#include <ostream>
#include <vector>
#include <string>
#include "Factor.hpp"

class	Equation
{
	private:
		std::vector<Factor>	left;
		std::vector<Factor>	right;

		void	simplifySide(std::vector<Factor> &side);
		
	public:
		Equation();
		Equation(const std::string &s);

		void	sort();
		void	simplify();
		void	oneside();

		friend std::ostream	&operator<<(std::ostream &o, const Equation &e);
};

std::ostream	&operator<<(std::ostream &o, const Equation &e);

#endif
